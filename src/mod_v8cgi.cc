/**
 * v8cgi - apache module
 */
#include <stdlib.h>
#include <string.h>

#include "httpd.h"
#include "http_config.h"
#include "http_log.h"
#include "http_protocol.h"
#include "util_script.h"
#include "apr_pools.h"

#include "js_app.h"
#include "js_macros.h"

typedef struct {
	char * config;
} v8cgi_config;

extern "C" module AP_MODULE_DECLARE_DATA v8cgi_module; /* first declaration */


class v8cgi_Module : public v8cgi_App {
public:
	size_t reader(char * destination, size_t amount) {
		return (size_t) ap_get_client_block(this->request, destination, amount);
	}

	size_t writer(const char * data, size_t amount) {
		if (this->output_started) { /* response data */
			return (size_t) ap_rwrite(data, amount, this->request);
		} else { /* header or content separator */
			char * end = strchr((char *) data, '\r');
			if (!end) { end = strchr((char *) data, '\n'); }
			if (!end) { return 0; } /* header or separator must end with a newline */
			
			if (end == data) { /* content separator */
				this->output_started = true;
				return 0;
			} else { /* header */
				char * colon = strchr((char *) data, ':');
				if (!colon) { return 0; } /* header without colon is a bad header */
				size_t namelen = colon - data;
				
				if ((size_t) (colon-data+1) < amount && *(colon+1) == ' ') { colon++; } /* skip space after colon */
				
				size_t valuelen = end - colon - 1;
				char * name = (char *) apr_palloc(request->pool, namelen + 1);
				char * value = (char *) apr_palloc(request->pool, valuelen + 1);
				name[namelen] = '\0';
				value[valuelen] = '\0';
				strncpy(name, data, namelen);
				strncpy(value, colon+1, valuelen);
				
				this->header(name, value);
				return (size_t) amount;
			}
		}
	}

	void error(const char * data, const char * file, int line) {
		ap_log_rerror(file, line, APLOG_ERR, 0, this->request, "%s", data);
	}

	int execute(request_rec * request) {
		this->output_started = false;
		this->request = request;
		return v8cgi_App::execute(true);
	}
	
	int init(int argc, char ** argv) { return 0; }
	
	void apacheConfig(v8cgi_config * cfg) {
		this->cfgfile = cfg->config;
	}

private:
	request_rec * request;
	bool output_started;

	void header(const char * name, const char * value) {
		if (strcasecmp(name, "content-type") == 0) {
			char * ct =  (char *) apr_palloc(request->pool, strlen(value)+1);
			strcpy(ct, value);
			this->request->content_type = ct;
		} else if (strcasecmp(name, "status") == 0) {
			char * line = (char *) apr_palloc(request->pool, strlen(value)+1);
			strcpy(line, value);
			this->request->status_line = line;
			this->request->status = atoi(value);
		} else {
			apr_table_set(this->request->headers_out, name, value);
		}
	}
	
};

static v8cgi_Module app;

static int mod_v8cgi_handler(request_rec *r) {
    const apr_array_header_t *arr;
    const apr_table_entry_t *elts;

    if (!r->handler || strcmp(r->handler, "v8cgi-script")) { return DECLINED; }

	ap_setup_client_block(r, REQUEST_CHUNKED_DECHUNK);
    ap_add_common_vars(r);
    ap_add_cgi_vars(r);

    /* extract the CGI environment  */
    arr = apr_table_elts(r->subprocess_env);
    elts = (const apr_table_entry_t*) arr->elts;
	
	char ** envp = new char *[arr->nelts + 1];
	envp[arr->nelts] = NULL;
	
	size_t size = 0;
	size_t len1 = 0;
	size_t len2 = 0;
    for (int i=0;i<arr->nelts;i++) {
		len1 = strlen(elts[i].key);
		len2 = strlen(elts[i].val);
		size = len1 + len2 + 2;
		
		envp[i] = new char[size];
		envp[i][size-1] = '\0';
		envp[i][len1] = '=';
		
		strncpy(envp[i], elts[i].key, len1);
		strncpy(&(envp[i][len1+1]), elts[i].val, len2);
    }

	int result = app.execute(r);
	
	for (int i=0;i<arr->nelts;i++) {
		free(envp[i]);
	}
	free(envp);
	
	if (result) {
		return HTTP_INTERNAL_SERVER_ERROR;
	} else {
		return OK;
	}
}

static int mod_v8cgi_init_handler(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s) { /* module initialization */
    ap_add_version_component(p, "mod_v8cgi");
	v8cgi_config * cfg = (v8cgi_config *) ap_get_module_config(s->module_config, &v8cgi_module);
	app.init(0, NULL);
	app.apacheConfig(cfg);
    return OK;
}

static void mod_v8cgi_child_init(apr_pool_t *p, server_rec *s) { /* child initialization */
}


static void mod_v8cgi_register_hooks(apr_pool_t *p ) { /* hook registration */
    ap_hook_handler(mod_v8cgi_handler, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config(mod_v8cgi_init_handler, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_child_init(mod_v8cgi_child_init, NULL, NULL, APR_HOOK_MIDDLE);
}

static void * mod_v8cgi_create_config(apr_pool_t *p, server_rec *s) { /* initial configuration values */
	v8cgi_config * newcfg = (v8cgi_config *) apr_pcalloc(p, sizeof(v8cgi_config));
	newcfg->config = STRING(CONFIG_PATH);
	return (void *) newcfg;
}

static const char * set_v8cgi_config(cmd_parms * parms, void * mconfig, const char * arg) { /* callback for configuration change */
	v8cgi_config * cfg = (v8cgi_config *) ap_get_module_config(parms->server->module_config, &v8cgi_module);
	cfg->config = (char *) arg;
	return NULL;
}

typedef const char * (* CONFIG_HANDLER) ();
static const command_rec mod_v8cgi_cmds[] = { /* list of configurations */
	AP_INIT_TAKE1(
		"v8cgi_Config",
		(CONFIG_HANDLER) set_v8cgi_config,
		NULL,
		RSRC_CONF,
		"Path to v8cgi configuration file."
	),
	{NULL}
};

extern "C" { /* module declaration */
	module AP_MODULE_DECLARE_DATA v8cgi_module = {
		STANDARD20_MODULE_STUFF,
		NULL,
		NULL,
		mod_v8cgi_create_config,
		NULL,
		mod_v8cgi_cmds,
		mod_v8cgi_register_hooks,
	};
}

/**
 * v8cgi - apache module. 
 * Extends v8cgi_App by adding customized initialization and (std)IO routines
 */
#include <stdlib.h>
#include <string.h>

#include "httpd.h"
#include "http_config.h"
#include "http_log.h"
#include "http_protocol.h"
#include "util_script.h"
#include "apr_pools.h"

#include "apr_base64.h"
#include "apr_strings.h"


#include "app.h"
#include "path.h"
#include "macros.h"

typedef struct {
	const char * config;
} v8cgi_config;

/**
 * First module declaration 
 */
extern "C" module AP_MODULE_DECLARE_DATA v8cgi_module; 

class v8cgi_Module : public v8cgi_App {
public:
	size_t reader(char * destination, size_t amount) {
		size_t read = 0;
		long part = 0;
		do {
			part = ap_get_client_block(this->request, destination+read, amount-read);
			if(part<0) { break; }
			read += part;
		} while (part>0 && read<amount);
		return read;
	}

	size_t writer(const char * data, size_t amount) {
		return (size_t) ap_rwrite(data, amount, this->request);
	}

	/**
	 * We log errors to apache errorlog
	 */
	void error(const char * data, const char * file, int line) {
		ap_log_rerror(file, line, APLOG_ERR, 0, this->request, "%s", data);
	}
	
	bool flush() {
		return true; /* FIXME? */
	}

	/** 
	 * Remember apache request structure and continue as usually
	 */
	int execute(request_rec * request, char ** envp) {
		this->request = request;
		this->mainfile = std::string(request->filename);
		int chdir_result = path_chdir(path_dirname(this->mainfile));
		if (chdir_result == -1) { return chdir_result; }
		return v8cgi_App::execute(envp);
	}
	
	void init(v8cgi_config * cfg) { 
		v8cgi_App::init();
		this->cfgfile = cfg->config;
	}

	/**
	 * Set a HTTP response header
	 * @param {char *} name
	 * @param {char *} value
	 */
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
			char * n = (char *) apr_palloc(request->pool, strlen(name)+1);
			char * v = (char *) apr_palloc(request->pool, strlen(value)+1);
			strcpy(n, name);
			strcpy(v, value);
			apr_table_addn(this->request->headers_out, n, v);
		}
	}

protected:
	void prepare(char ** envp);

private:
	request_rec * request;

	const char * instanceType() {
		return "module";
	}

	const char * executableName() {
		return "?";
	}
};

JS_METHOD(_header) {
	v8cgi_Module * app = (v8cgi_Module *) APP_PTR;
	v8::String::Utf8Value name(args[0]);
	v8::String::Utf8Value value(args[1]);
	app->header(*name, *value);
	return v8::Undefined();
}

void v8cgi_Module::prepare(char ** envp) {
	v8cgi_App::prepare(envp);

	v8::HandleScope handle_scope;
	v8::Handle<v8::Object> g = JS_GLOBAL;
	v8::Handle<v8::Object> apache = v8::Object::New();
	g->Set(JS_STR("apache"), apache);
	apache->Set(JS_STR("header"), v8::FunctionTemplate::New(_header)->GetFunction());
}

/**
 * This is called from Apache every time request arrives
 */
static int mod_v8cgi_handler(request_rec *r) {
	const apr_array_header_t *arr;
	const apr_table_entry_t *elts;

	if (!r->handler || strcmp(r->handler, "v8cgi-script")) { return DECLINED; }

	ap_setup_client_block(r, REQUEST_CHUNKED_DECHUNK);
	ap_add_common_vars(r);
	ap_add_cgi_vars(r);

	if (r->headers_in) {
		const char *auth;
		auth = apr_table_get(r->headers_in, "Authorization");
		if (auth && auth[0] != 0 && strncmp(auth, "Basic ", 6) == 0) {
			
			char *user = NULL;
			char *pass = NULL;
			int length;

			user = (char *)apr_palloc(r->pool, apr_base64_decode_len(auth+6) + 1);
			length = apr_base64_decode(user, auth + 6);

			/* Null-terminate the string. */
			user[length] = '\0';
			
			if (user) {
				pass = strchr(user, ':');
				if (pass) {
					*pass++ = '\0';

					apr_table_setn(r->subprocess_env, "AUTH_USER", user);
					apr_table_setn(r->subprocess_env, "AUTH_PW", pass);
				}
		    }
		} 
    }
	
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

	v8cgi_config * cfg = (v8cgi_config *) ap_get_module_config(r->server->module_config, &v8cgi_module);
	v8cgi_Module app;
	app.init(cfg);
	app.execute(r, envp);
	
	for (int i=0;i<arr->nelts;i++) {
		delete[] envp[i];
	}
	delete[] envp;
	
//  Ok is safer, because HTTP_INTERNAL_SERVER_ERROR overwrites any content already generated
//	if (result) {
//		return HTTP_INTERNAL_SERVER_ERROR;
//	} else {
		return OK;
//	}
}

/**
 * Module initialization 
 */
static int mod_v8cgi_init_handler(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s) {
	std::string version;
	version += "mod_v8cgi/";
	version += STRING(VERSION);
	ap_add_version_component(p, version.c_str());
    return OK;
}

/**
 * Child initialization 
 * FIXME: what is this for?
 */
static void mod_v8cgi_child_init(apr_pool_t *p, server_rec *s) { 
}

/**
 * Register relevant hooks
 */
static void mod_v8cgi_register_hooks(apr_pool_t *p ) {
	ap_hook_handler(mod_v8cgi_handler, NULL, NULL, APR_HOOK_MIDDLE);
	ap_hook_post_config(mod_v8cgi_init_handler, NULL, NULL, APR_HOOK_MIDDLE);
	ap_hook_child_init(mod_v8cgi_child_init, NULL, NULL, APR_HOOK_MIDDLE);
}

/**
 * Create initial configuration values 
 */
static void * mod_v8cgi_create_config(apr_pool_t *p, server_rec *s) { 
	v8cgi_config * newcfg = (v8cgi_config *) apr_pcalloc(p, sizeof(v8cgi_config));
	newcfg->config = STRING(CONFIG_PATH);
	return (void *) newcfg;
}

/**
 * Callback executed for every configuration change 
 */
static const char * set_v8cgi_config(cmd_parms * parms, void * mconfig, const char * arg) { 
	v8cgi_config * cfg = (v8cgi_config *) ap_get_module_config(parms->server->module_config, &v8cgi_module);
	cfg->config = (char *) arg;
	return NULL;
}

typedef const char * (* CONFIG_HANDLER) ();
/* list of configurations */
static const command_rec mod_v8cgi_cmds[] = { 
	AP_INIT_TAKE1(
		"v8cgi_Config",
		(CONFIG_HANDLER) set_v8cgi_config,
		NULL,
		RSRC_CONF,
		"Path to v8cgi configuration file."
	),
	{NULL}
};

/**
 * Module (re-)declaration
 */
extern "C" { 
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

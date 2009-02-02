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

extern char ** environ;
static request_rec * request;

size_t reader_function(char * destination, size_t amount) {
	return ap_get_client_block(request, destination, amount);
}

size_t writer_function(const char * data, size_t amount) {
	return ap_rwrite(data, amount, request);
}

void error_function(const char * data, const char * file, int line) {
	ap_log_rerror(file, line, APLOG_DEBUG, 1, request, "%s", data);
}

void header_function(const char * name, const char * value) {
	if (strcasecmp(name, "content-type") == 0) {
  		char * ct =  (char *) apr_palloc(request->pool, strlen(value)+1);
		strcpy(ct, value);
  		request->content_type = ct;
	} else if (strcasecmp(name, "status") == 0) {
  		char * line =  (char *) apr_palloc(request->pool, strlen(value)+1);
		strcpy(line, value);
		request->status_line = line;
		request->status = atoi(value);
	} else {
		apr_table_set(request->headers_out, name, value);
	}
}

static int mod_v8cgi_handler(request_rec *r) {
    const apr_array_header_t *arr;
    const apr_table_entry_t *elts;

	request = r;
    if (!r->handler || strcmp(r->handler, "v8cgi-script")) { return DECLINED; }

	ap_setup_client_block(r, REQUEST_CHUNKED_DECHUNK);
    ap_add_common_vars(r);
    ap_add_cgi_vars(r);

    /* set apache headers */
    /* TODO - let the script do this. */
    r->content_type = "text/html";
	
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

	int result = app_cycle(envp);
	
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

static int mod_v8cgi_init_handler(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s) {
    ap_add_version_component(p, "mod_v8cgi");
	app_initialize(0, NULL, reader_function, writer_function, error_function, header_function);
    return OK;
}

static void mod_v8cgi_child_init(apr_pool_t *p, server_rec *s) {
}


static void mod_v8cgi_register_hooks(apr_pool_t *p ) {
    ap_hook_handler(mod_v8cgi_handler, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config(mod_v8cgi_init_handler, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_child_init(mod_v8cgi_child_init, NULL, NULL, APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA v8cgi_module = {
    STANDARD20_MODULE_STUFF,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    mod_v8cgi_register_hooks,
};

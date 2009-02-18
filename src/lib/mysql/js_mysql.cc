#include <v8.h>
#include "js_macros.h"

#ifdef windows
#	include <my_global.h>
#endif

#include <mysql.h>
#include <stdlib.h>
#include <string>

v8::Persistent<v8::FunctionTemplate> rest;

JS_METHOD(_mysql) {
	if (args.This()->InternalFieldCount() == 0) {
		return JS_EXCEPTION("Invalid call format. Use 'new MySQL()'");
	}
	SAVE_VALUE(0, JS_BOOL(false));
	
	return args.This();
}

JS_METHOD(_connect) {
	if (args.Length() < 4) {
		return JS_EXCEPTION("Invalid call format. Use 'mysql.connect(host, user, pass, db)'");
	}

	MYSQL *conn;
	
	v8::String::Utf8Value host(args[0]);
	v8::String::Utf8Value user(args[1]);
	v8::String::Utf8Value pass(args[2]);
	v8::String::Utf8Value db(args[3]);

	conn = mysql_init(NULL);

	if (!mysql_real_connect(conn, *host, *user, *pass, *db, 0, NULL, 0)) {
		return JS_BOOL(false);
	} else {
		mysql_query(conn, "SET NAMES 'utf8'");				 
		SAVE_PTR(0, conn);
		return args.This();
	}	
}

JS_METHOD(_query) {
	v8::Handle<v8::Value> c = LOAD_VALUE(0);
	if (c->IsFalse()) {
		return JS_EXCEPTION("No connection established");
	}		
	if (args.Length() < 1) {
		return JS_EXCEPTION("No query specified");
	}
	v8::String::Utf8Value q(args[0]);
	
	int qc = args.This()->Get(JS_STR("queryCount"))->ToInteger()->Int32Value();
	args.This()->Set(JS_STR("queryCount"), JS_INT(qc+1));
	MYSQL * conn = LOAD_PTR(0, MYSQL *);
	MYSQL_RES *res;
	int code = mysql_real_query(conn, *q, q.length());
	if (code != 0) { return JS_BOOL(false); }
	
	res = mysql_store_result(conn);
	
	if (res) {
		v8::Handle<v8::Value> resargs[] = { v8::External::New((void *) res) };
		return rest->GetFunction()->NewInstance(1, resargs);
	} else {
		if (mysql_field_count(conn)) {
			return JS_BOOL(false);
		} else {
			return JS_BOOL(true);
		}
	}
}

JS_METHOD(_error) {
	v8::Handle<v8::Value> c = LOAD_VALUE(0);
	if (c->IsFalse()) {
		return JS_EXCEPTION("No connection established");
	}

	MYSQL * conn = LOAD_PTR(0, MYSQL *);

	return JS_STR(mysql_error(conn));
}

JS_METHOD(_errno) {
	v8::Handle<v8::Value> c = LOAD_VALUE(0);
	if (c->IsFalse()) {
		return JS_EXCEPTION("No connection established");
	}
	
	MYSQL * conn = LOAD_PTR(0, MYSQL *);

	return JS_INT(mysql_errno(conn));
}

JS_METHOD(_affectedrows) {
	v8::Handle<v8::Value> c = LOAD_VALUE(0);
	if (c->IsFalse()) {
		return JS_EXCEPTION("No connection established");
	}
		
	MYSQL * conn = LOAD_PTR(0, MYSQL *)

	return JS_INT(mysql_affected_rows(conn));
}

JS_METHOD(_insertid) {
	v8::Handle<v8::Value> c = LOAD_VALUE(0);
	if (c->IsFalse()) {
		return JS_EXCEPTION("No connection established");
	}

	MYSQL * conn = LOAD_PTR(0, MYSQL *);

	return JS_INT(mysql_insert_id(conn));
}

JS_METHOD(_escape) {
	v8::Handle<v8::Value> c = LOAD_VALUE(0);
	if (c->IsFalse()) {
		return JS_EXCEPTION("No connection established");
	}
	if (args.Length() < 1) {
		return JS_EXCEPTION("Nothing to escape");
	}
	v8::String::Utf8Value str(args[0]);
	
	int len = args[0]->ToString()->Utf8Length();
	char * result = new char[2*len + 1];
	
	MYSQL * conn = LOAD_PTR(0, MYSQL *);

	int length = mysql_real_escape_string(conn, result, *str, len);
	v8::Handle<v8::Value> output = JS_STR(result, length);
	delete[] result;
	return output;
}

JS_METHOD(_qualify) {
	if (args.Length() < 1) {
		return JS_EXCEPTION("Nothing to qualify");
	}

	v8::String::Utf8Value str(args[0]);
	std::string result = "`";
	result += *str;
	result += "`";
	
	v8::Handle<v8::Value> output = JS_STR(result.c_str());
	return output;
}

JS_METHOD(_result) {
	SAVE_VALUE(0, args[0]);
	return args.This();
}

JS_METHOD(_numrows) {
	MYSQL_RES * res = LOAD_PTR(0, MYSQL_RES *);

	return JS_INT(mysql_num_rows(res));
}

JS_METHOD(_numfields) {
	MYSQL_RES * res = LOAD_PTR(0, MYSQL_RES *);

	return JS_INT(mysql_num_fields(res));
}

JS_METHOD(_fetchnames) {
	MYSQL_RES * res = LOAD_PTR(0, MYSQL_RES *);

	int cnt = mysql_num_fields(res);
	MYSQL_FIELD * fields = mysql_fetch_fields(res);
	v8::Handle<v8::Array> result = v8::Array::New(cnt);
	
	for(int i = 0; i < cnt; i++) {
		result->Set(JS_INT(i), JS_STR(fields[i].name));
	}
	
	return result;
}

JS_METHOD(_fetcharrays) {
	MYSQL_RES * res = LOAD_PTR(0, MYSQL_RES *);
	mysql_data_seek(res, 0);

	int x = mysql_num_fields(res);
	int y = mysql_num_rows(res);
	MYSQL_ROW row;
	v8::Handle<v8::Array> result = v8::Array::New(y);
	
	for (int i = 0; i < y; i++) {
		row = mysql_fetch_row(res);
		v8::Handle<v8::Array> item = v8::Array::New(x);
		result->Set(JS_INT(i), item);
		for (int j=0; j<x; j++) {
			if (row[j] == NULL) {
				item->Set(JS_INT(j), v8::Null());
			} else {
				item->Set(JS_INT(j), JS_STR(row[j]));
			}
		}
	}
	
	return result;
}

JS_METHOD(_fetchobjects) {
	MYSQL_RES * res = LOAD_PTR(0, MYSQL_RES *);
	mysql_data_seek(res, 0);

	int x = mysql_num_fields(res);
	int y = mysql_num_rows(res);
	MYSQL_FIELD * fields = mysql_fetch_fields(res);
	MYSQL_ROW row;
	v8::Handle<v8::Array> result = v8::Array::New(y);
	
	for (int i = 0; i < y; i++) {
		row = mysql_fetch_row(res);
		v8::Handle<v8::Object> item = v8::Object::New();
		result->Set(JS_INT(i), item);
		for (int j=0; j<x; j++) {
			if (row[j] == NULL) {
				item->Set(JS_STR(fields[j].name), v8::Null());
			} else {
				item->Set(JS_STR(fields[j].name), JS_STR(row[j]));
			}
		}
	}
	
	return result;
}

SHARED_INIT() {
	v8::HandleScope handle_scope;
	v8::Handle<v8::FunctionTemplate> ft = v8::FunctionTemplate::New(_mysql);
	ft->SetClassName(JS_STR("MySQL"));

	v8::Handle<v8::ObjectTemplate> ot = ft->InstanceTemplate();
	ot->SetInternalFieldCount(1); /* connection */
	ot->Set(JS_STR("queryCount"), JS_INT(0));
		 
	v8::Handle<v8::ObjectTemplate> pt = ft->PrototypeTemplate();
	pt->Set(JS_STR("connect"), v8::FunctionTemplate::New(_connect));
	pt->Set(JS_STR("query"), v8::FunctionTemplate::New(_query));
	pt->Set(JS_STR("error"), v8::FunctionTemplate::New(_error));
	pt->Set(JS_STR("errno"), v8::FunctionTemplate::New(_errno));
	pt->Set(JS_STR("affectedRows"), v8::FunctionTemplate::New(_affectedrows));
	pt->Set(JS_STR("escape"), v8::FunctionTemplate::New(_escape));
	pt->Set(JS_STR("qualify"), v8::FunctionTemplate::New(_qualify));
	pt->Set(JS_STR("insertId"), v8::FunctionTemplate::New(_insertid));
	
	rest = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(_result));
	rest->SetClassName(JS_STR("Result"));
	
	v8::Handle<v8::ObjectTemplate> resinst = rest->InstanceTemplate();
	resinst->SetInternalFieldCount(1);
	
	v8::Handle<v8::ObjectTemplate> resproto = rest->PrototypeTemplate();
	resproto->Set(JS_STR("numRows"), v8::FunctionTemplate::New(_numrows));
	resproto->Set(JS_STR("numFields"), v8::FunctionTemplate::New(_numfields));
	resproto->Set(JS_STR("fetchNames"), v8::FunctionTemplate::New(_fetchnames));
	resproto->Set(JS_STR("fetchArrays"), v8::FunctionTemplate::New(_fetcharrays));
	resproto->Set(JS_STR("fetchObjects"), v8::FunctionTemplate::New(_fetchobjects));

	exports->Set(JS_STR("MySQL"), ft->GetFunction());
}

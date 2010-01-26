#include <v8.h>
#include "macros.h"
#include "gc.h"

#ifdef windows
#	include <my_global.h>
#endif

#include <mysql.h>
#include <stdlib.h>
#include <string>

#define MYSQL_ERROR mysql_error(conn)
#define ASSERT_CONNECTED if (!conn) { return JS_EXCEPTION("No connection established yet."); }
#define MYSQL_PTR MYSQL * conn = LOAD_PTR(0, MYSQL *)


namespace {

v8::Persistent<v8::FunctionTemplate> rest;

void destroy(v8::Handle<v8::Object> obj) {
	v8::Handle<v8::Function> fun = v8::Handle<v8::Function>::Cast(obj->Get(JS_STR("close")));
	fun->Call(obj, 0, NULL);
}

v8::Handle<v8::Value> createResult(MYSQL * conn) {
	MYSQL_RES * res = mysql_store_result(conn);
	
	if (res) {
		v8::Handle<v8::Value> resargs[] = { v8::External::New((void *) res) };
		return rest->GetFunction()->NewInstance(1, resargs);
	} else {
		if (mysql_field_count(conn)) {
			return JS_EXCEPTION(MYSQL_ERROR);
		} else {
			return JS_BOOL(true);
		}
	}
}

/**
 * MySQL constructor does basically nothing. It just adds "this.close()" method to global GC
 */
JS_METHOD(_mysql) {
	ASSERT_CONSTRUCTOR;
	SAVE_PTR(0, NULL);
	GC * gc = GC_PTR;
	gc->add(args.This(), destroy);
	return args.This();
}

/**
 * Close DB connection
 */ 
JS_METHOD(_close) {
	MYSQL_PTR;
	if (conn) {
		mysql_close(conn);
		SAVE_PTR(0, NULL);
	}
	return args.This();
}

/**
 * Should be called ASAP: new MySQL().connect("host", "user", "pass", "db")
 */ 
JS_METHOD(_connect) {
	if (args.Length() < 4) {
		return JS_EXCEPTION("Invalid call format. Use 'mysql.connect(host, user, pass, db)'");
	}
	
	MYSQL * conn;
	
	v8::String::Utf8Value host(args[0]);
	v8::String::Utf8Value user(args[1]);
	v8::String::Utf8Value pass(args[2]);
	v8::String::Utf8Value db(args[3]);

	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, *host, *user, *pass, *db, 0, NULL, CLIENT_MULTI_STATEMENTS)) {
		return JS_EXCEPTION(MYSQL_ERROR);
	} else {
		mysql_query(conn, "SET NAMES 'utf8'");
		SAVE_PTR(0, conn);
		return args.This();
	}	
}

/**
 * Query takes a string argument and returns an instance of Result object
 */ 
JS_METHOD(_query) {
	MYSQL_PTR;
	ASSERT_CONNECTED;
	if (args.Length() < 1) {
		return JS_EXCEPTION("No query specified");
	}
	v8::String::Utf8Value q(args[0]);
	
	int code = mysql_real_query(conn, *q, q.length());
	if (code != 0) { return JS_EXCEPTION(MYSQL_ERROR); }
	
	int qc = args.This()->Get(JS_STR("queryCount"))->ToInteger()->Int32Value();
	args.This()->Set(JS_STR("queryCount"), JS_INT(qc+1));
	
	return createResult(conn);
}

/**
 * Fetch next result from a multi-result set
 */
JS_METHOD(_nextresult) {
	MYSQL_PTR;
	ASSERT_CONNECTED;
	
	int status = mysql_next_result(conn);
	
	if (status == -1) { return JS_NULL; }
	if (status > 0) { return JS_EXCEPTION(MYSQL_ERROR); }
	return createResult(conn);
}

JS_METHOD(_affectedrows) {
	MYSQL_PTR;
	ASSERT_CONNECTED;
	return JS_INT(mysql_affected_rows(conn));
}

JS_METHOD(_insertid) {
	MYSQL_PTR;
	ASSERT_CONNECTED;
	return JS_INT(mysql_insert_id(conn));
}

JS_METHOD(_escape) {
	MYSQL_PTR;
	ASSERT_CONNECTED;
	
	if (args.Length() < 1) {
		return JS_EXCEPTION("Nothing to escape");
	}
	v8::String::Utf8Value str(args[0]);
	
	int len = args[0]->ToString()->Utf8Length();
	char * result = new char[2*len + 1];
	

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

/**
 * Return result data as an array of JS arrays
 */ 
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

/**
 * Return result data as an array of JS objects, indexed with column names
 */ 
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

} /* end namespace */

SHARED_INIT() {
	v8::HandleScope handle_scope;
	v8::Handle<v8::FunctionTemplate> ft = v8::FunctionTemplate::New(_mysql);
	ft->SetClassName(JS_STR("MySQL"));

	v8::Handle<v8::ObjectTemplate> ot = ft->InstanceTemplate();
	ot->SetInternalFieldCount(1); /* connection */
	
	/**
	 * Static property, useful for stats gathering
	 */
	ot->Set(JS_STR("queryCount"), JS_INT(0));
		 
	v8::Handle<v8::ObjectTemplate> pt = ft->PrototypeTemplate();

	/**
	 * MySQL prototype methods (new MySQL().*)
	 */
	pt->Set(JS_STR("connect"), v8::FunctionTemplate::New(_connect));
	pt->Set(JS_STR("close"), v8::FunctionTemplate::New(_close));
	pt->Set(JS_STR("query"), v8::FunctionTemplate::New(_query));
	pt->Set(JS_STR("nextResult"), v8::FunctionTemplate::New(_nextresult));
	pt->Set(JS_STR("affectedRows"), v8::FunctionTemplate::New(_affectedrows));
	pt->Set(JS_STR("escape"), v8::FunctionTemplate::New(_escape));
	pt->Set(JS_STR("qualify"), v8::FunctionTemplate::New(_qualify));
	pt->Set(JS_STR("insertId"), v8::FunctionTemplate::New(_insertid));
	
	rest = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(_result));
	rest->SetClassName(JS_STR("Result"));
	
	v8::Handle<v8::ObjectTemplate> resinst = rest->InstanceTemplate();
	resinst->SetInternalFieldCount(1);
	
	v8::Handle<v8::ObjectTemplate> resproto = rest->PrototypeTemplate();

	/**
	 * Result prototype methods (new MySQL().query().*)
	 */
	resproto->Set(JS_STR("numRows"), v8::FunctionTemplate::New(_numrows));
	resproto->Set(JS_STR("numFields"), v8::FunctionTemplate::New(_numfields));
	resproto->Set(JS_STR("fetchNames"), v8::FunctionTemplate::New(_fetchnames));
	resproto->Set(JS_STR("fetchArrays"), v8::FunctionTemplate::New(_fetcharrays));
	resproto->Set(JS_STR("fetchObjects"), v8::FunctionTemplate::New(_fetchobjects));

	exports->Set(JS_STR("MySQL"), ft->GetFunction());
}

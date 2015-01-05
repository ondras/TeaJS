#include <v8.h>
#include "macros.h"
#include "gc.h"

#ifdef windows
#	include <my_global.h>
#endif

#include <mysql.h>
#include <stdlib.h>
#include <string>
#include <map>

#define MYSQL_ERROR mysql_error(conn)
#define ASSERT_CONNECTED if (!conn) { JS_ERROR("No connection established yet."); return; }
#define ASSERT_RESULT if (!res) { JS_ERROR("Result set already closed."); return; }
#define MYSQL_PTR MYSQL * conn = LOAD_PTR(0, MYSQL *)


namespace {

v8::Persistent<v8::FunctionTemplate> _rest;
v8::Persistent<v8::FunctionTemplate> _mysqlt;

typedef std::map<std::string, void *> persistent_connection_t;
persistent_connection_t persistent_connections;


void finalize(v8::Handle<v8::Object> obj) {
	if (obj->GetInternalField(1)->IsFalse()) {
		v8::Handle<v8::Function> fun = v8::Handle<v8::Function>::Cast(obj->Get(JS_STR("close")));
		fun->Call(obj, 0, NULL);
	}
}

void result_finalize(v8::Handle<v8::Object> obj) {
	v8::Handle<v8::Function> fun = v8::Handle<v8::Function>::Cast(obj->Get(JS_STR("close")));
	fun->Call(obj, 0, NULL);
}

void createResult(MYSQL * conn, const v8::FunctionCallbackInfo<v8::Value>& args) {
	MYSQL_RES * res = mysql_store_result(conn);
	
	if (res) {
		v8::Handle<v8::Value> resargs[] = { v8::External::New(JS_ISOLATE, (void *) res) };
		v8::Local<v8::FunctionTemplate> rest = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, _rest);
		args.GetReturnValue().Set(rest->GetFunction()->NewInstance(1, resargs));
	} else {
		if (mysql_field_count(conn)) {
			JS_ERROR(MYSQL_ERROR);
		} else {
			args.GetReturnValue().Set(JS_BOOL(true));
		}
	}
}

/**
 * MySQL constructor does basically nothing. It just adds "this.close()" method to global GC
 */
JS_METHOD(_mysql) {
	ASSERT_CONSTRUCTOR;
	SAVE_PTR(0, NULL);

	SAVE_VALUE(1, JS_BOOL(args[0]->IsTrue()));

	GC * gc = GC_PTR;
	gc->add(args.This(), finalize);
	args.GetReturnValue().Set(args.This());
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
	args.GetReturnValue().Set(args.This());
}

/**
 * Should be called ASAP: new MySQL().connect("host", "user", "pass", "db")
 */ 
JS_METHOD(_connect) {
	if (args.Length() < 4) {
		JS_TYPE_ERROR("Invalid call format. Use 'mysql.connect(host, user, pass, db)'");
		return;
	}
	
	MYSQL * conn;
	
	v8::String::Utf8Value host(args[0]);
	v8::String::Utf8Value user(args[1]);
	v8::String::Utf8Value pass(args[2]);
	v8::String::Utf8Value db(args[3]);
	
	std::string fullhost(*host);
	std::string onlyhost;
	int port = 0;
	
	size_t index = fullhost.find(':');
	if (index != std::string::npos) {
		onlyhost = fullhost.substr(0, index);
		port = atoi(fullhost.substr(index+1, fullhost.length()-index-1).c_str());
	} else {
		onlyhost = fullhost;
	}
	
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, onlyhost.c_str(), *user, *pass, *db, port, NULL, CLIENT_MULTI_STATEMENTS)) {
		JS_ERROR(MYSQL_ERROR);
	} else {
		mysql_query(conn, "SET NAMES 'utf8'");
		SAVE_PTR(0, conn);
		args.GetReturnValue().Set(args.This());
	}
}

/**
 * Query takes a string argument and returns an instance of Result object
 */ 
JS_METHOD(_query) {
	MYSQL_PTR;
	ASSERT_CONNECTED;
	if (args.Length() < 1) {
		JS_ERROR("No query specified");
		return;
	}
	v8::String::Utf8Value q(args[0]);
	
	int code = mysql_real_query(conn, *q, q.length());
	if (code != 0) { JS_ERROR(MYSQL_ERROR); return; }
	
	int qc = args.This()->Get(JS_STR("queryCount"))->ToInteger()->Int32Value();
	args.This()->Set(JS_STR("queryCount"), JS_INT(qc+1));
	
	createResult(conn, args);
}

/**
 * Fetch next result from a multi-result set
 */
JS_METHOD(_nextresult) {
	MYSQL_PTR;
	ASSERT_CONNECTED;
	
	int status = mysql_next_result(conn);
	
	if (status == -1) { args.GetReturnValue().SetNull(); return; }
	if (status > 0) { JS_ERROR(MYSQL_ERROR); return; }
	createResult(conn, args);
}

JS_METHOD(_affectedrows) {
	MYSQL_PTR;
	ASSERT_CONNECTED;
	args.GetReturnValue().Set(JS_INT(mysql_affected_rows(conn)));
}

JS_METHOD(_insertid) {
	MYSQL_PTR;
	ASSERT_CONNECTED;
	args.GetReturnValue().Set(JS_INT(mysql_insert_id(conn)));
}

JS_METHOD(_escape) {
	MYSQL_PTR;
	ASSERT_CONNECTED;
	
	if (args.Length() < 1) {
		JS_TYPE_ERROR("Nothing to escape");
		return;
	}
	v8::String::Utf8Value str(args[0]);
	
	int len = args[0]->ToString()->Utf8Length();
	char * result = new char[2*len + 1];
	

	int length = mysql_real_escape_string(conn, result, *str, len);
	v8::Handle<v8::Value> output = JS_STR_LEN(result, length);
	delete[] result;
	args.GetReturnValue().Set(output);
}

JS_METHOD(_qualify) {
	if (args.Length() < 1) {
		JS_TYPE_ERROR("Nothing to qualify");
		return;
	}

	v8::String::Utf8Value str(args[0]);
	std::string result = "`";
	result += *str;
	result += "`";
	
	v8::Handle<v8::Value> output = JS_STR(result.c_str());
	args.GetReturnValue().Set(output);
}

JS_METHOD(_result) {
	SAVE_VALUE(0, args[0]);

	GC * gc = GC_PTR;
	gc->add(args.This(), result_finalize);

	args.GetReturnValue().Set(args.This());
}

JS_METHOD(_numrows) {
	MYSQL_RES * res = LOAD_PTR(0, MYSQL_RES *);
	ASSERT_RESULT;

	args.GetReturnValue().Set(JS_INT(mysql_num_rows(res)));
}

JS_METHOD(_numfields) {
	MYSQL_RES * res = LOAD_PTR(0, MYSQL_RES *);
	ASSERT_RESULT;

	args.GetReturnValue().Set(JS_INT(mysql_num_fields(res)));
}

JS_METHOD(_fetchnames) {
	MYSQL_RES * res = LOAD_PTR(0, MYSQL_RES *);
	ASSERT_RESULT;

	int cnt = mysql_num_fields(res);
	MYSQL_FIELD * fields = mysql_fetch_fields(res);
	v8::Handle<v8::Array> result = v8::Array::New(JS_ISOLATE, cnt);
	
	for(int i = 0; i < cnt; i++) {
		result->Set(JS_INT(i), JS_STR(fields[i].name));
	}

	args.GetReturnValue().Set(result);
}

/**
 * Converts string representations of values in MySQL result sets (the format in
 * which MySQL returns data) to JavaScript values.
 *
 * @param mysql_value  A string (or NULL) value fetched from MySQL.
 * @param field        The column the value came from.  Its type is used to
 *                     determine, e.g., whether to convert the value to a
 *                     number.
 */
v8::Handle<v8::Value> _mysqltojs(const char* mysql_value, const MYSQL_FIELD& field) {
	if (mysql_value == NULL) {
		return v8::Null(JS_ISOLATE);
	}

        // For type list, see http://www.google.com/codesearch/p#RGCD84x9Jg0/trunk/xbmc/lib/libcmyth/Win32/include/mysql/mysql_com.h&q=enum_field_types
	switch (field.type) {
		case MYSQL_TYPE_DECIMAL:
		case MYSQL_TYPE_TINY:
		case MYSQL_TYPE_SHORT:
		case MYSQL_TYPE_LONG:
		case MYSQL_TYPE_LONGLONG:
		case MYSQL_TYPE_INT24:
		case MYSQL_TYPE_BIT:
		case MYSQL_TYPE_NEWDECIMAL:
		case MYSQL_TYPE_ENUM:
		case MYSQL_TYPE_FLOAT:
		case MYSQL_TYPE_DOUBLE:
			return JS_STR(mysql_value)->ToNumber();

		case MYSQL_TYPE_TIMESTAMP:
		case MYSQL_TYPE_DATE:
		case MYSQL_TYPE_TIME:
		case MYSQL_TYPE_DATETIME:
		case MYSQL_TYPE_YEAR:
		case MYSQL_TYPE_NEWDATE:
			return JS_STR(mysql_value);  // TODO: handle dates appropriately

		default:
			return JS_STR(mysql_value);
        }
}

/**
 * Return result data as an array of JS arrays
 */ 
JS_METHOD(_fetcharrays) {
	MYSQL_RES * res = LOAD_PTR(0, MYSQL_RES *);
	ASSERT_RESULT;
	mysql_data_seek(res, 0);

	int x = mysql_num_fields(res);
	int y = mysql_num_rows(res);
	MYSQL_FIELD * fields = mysql_fetch_fields(res);
	MYSQL_ROW row;
	v8::Handle<v8::Array> result = v8::Array::New(JS_ISOLATE, y);
	
	for (int i = 0; i < y; i++) {
		row = mysql_fetch_row(res);
		v8::Handle<v8::Array> item = v8::Array::New(JS_ISOLATE, x);
		result->Set(JS_INT(i), item);
		for (int j=0; j<x; j++) {
			item->Set(JS_INT(j), _mysqltojs(row[j], fields[j]));
			}
		}
	
	args.GetReturnValue().Set(result);
}

/**
 * Return result data as an array of JS objects, indexed with column names
 */ 
JS_METHOD(_fetchobjects) {
	MYSQL_RES * res = LOAD_PTR(0, MYSQL_RES *);
	ASSERT_RESULT;
	mysql_data_seek(res, 0);

	int x = mysql_num_fields(res);
	int y = mysql_num_rows(res);
	MYSQL_FIELD * fields = mysql_fetch_fields(res);
	MYSQL_ROW row;
	v8::Handle<v8::Array> result = v8::Array::New(JS_ISOLATE, y);
	
	for (int i = 0; i < y; i++) {
		row = mysql_fetch_row(res);
		v8::Handle<v8::Object> item = v8::Object::New(JS_ISOLATE);
		result->Set(JS_INT(i), item);
		for (int j=0; j<x; j++) {
			item->Set(JS_STR(fields[j].name), _mysqltojs(row[j], fields[j]));
			}
		}
	
	args.GetReturnValue().Set(result);
}

JS_METHOD(_result_close) {
	MYSQL_RES * res = LOAD_PTR(0, MYSQL_RES *);
	if (res) {
		mysql_free_result(res);
		SAVE_PTR(0, NULL);
		args.GetReturnValue().Set(true);
	} else {
		args.GetReturnValue().Set(false);
	}
}


JS_METHOD(_storeConnection) {
	v8::String::Utf8Value name(args[0]);
	std::string str_name(*name);

	persistent_connection_t::iterator it = persistent_connections.find(str_name);
	if (args[1]->ToBoolean()->IsFalse()) { /* delete */
		persistent_connections.erase(it);
		args.GetReturnValue().SetUndefined();
		return;
	}

	if (!args[1]->IsObject()) { JS_TYPE_ERROR("Invalid argument"); return; }
	v8::Handle<v8::Object> inst = v8::Handle<v8::Object>::Cast(args[1]);
	if (inst->InternalFieldCount() < 1) { JS_TYPE_ERROR("Invalid argument"); return; }

	if (it != persistent_connections.end()) { JS_ERROR("Connection name already used"); return; }

	persistent_connections[str_name] = LOAD_PTR_FROM(inst, 0, void *);

	args.GetReturnValue().SetUndefined();
}

JS_METHOD(_loadConnection) {
	v8::String::Utf8Value name(args[0]);
	std::string str_name(*name);

	persistent_connection_t::iterator it = persistent_connections.find(str_name);
	if (it == persistent_connections.end()) { args.GetReturnValue().SetNull(); return; }

	MYSQL * conn = (MYSQL *) (it->second);
	
	v8::Handle<v8::Value> newArgs[1] = {JS_BOOL(true)};
	v8::Local<v8::FunctionTemplate> mysqlt = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, _mysqlt);
	v8::Handle<v8::Object> inst = mysqlt->GetFunction()->NewInstance(1, newArgs);
	SAVE_PTR_TO(inst, 0, (void *)conn);

	args.GetReturnValue().Set(inst);
}

} /* end namespace */

SHARED_INIT() {
	v8::HandleScope handle_scope(JS_ISOLATE);
	v8::Handle<v8::FunctionTemplate> mysqlt = v8::FunctionTemplate::New(JS_ISOLATE, _mysql);
	mysqlt->SetClassName(JS_STR("MySQL"));

	v8::Handle<v8::ObjectTemplate> ot = mysqlt->InstanceTemplate();
	ot->SetInternalFieldCount(2); /* connection, do-not-auto-close */
	
	/**
	 * Static property, useful for stats gathering
	 */
	ot->Set(JS_STR("queryCount"), JS_INT(0));

	/**
	 * Persistent connection storage
	 */
	mysqlt->Set(JS_STR("storeConnection"), v8::FunctionTemplate::New(JS_ISOLATE, _storeConnection));
	mysqlt->Set(JS_STR("loadConnection"), v8::FunctionTemplate::New(JS_ISOLATE, _loadConnection));
		 
	v8::Handle<v8::ObjectTemplate> pt = mysqlt->PrototypeTemplate();

	_mysqlt.Reset(JS_ISOLATE, mysqlt);

	/**
	 * MySQL prototype methods (new MySQL().*)
	 */
	pt->Set(JS_STR("connect"), v8::FunctionTemplate::New(JS_ISOLATE, _connect));
	pt->Set(JS_STR("close"), v8::FunctionTemplate::New(JS_ISOLATE, _close));
	pt->Set(JS_STR("query"), v8::FunctionTemplate::New(JS_ISOLATE, _query));
	pt->Set(JS_STR("nextResult"), v8::FunctionTemplate::New(JS_ISOLATE, _nextresult));
	pt->Set(JS_STR("affectedRows"), v8::FunctionTemplate::New(JS_ISOLATE, _affectedrows));
	pt->Set(JS_STR("escape"), v8::FunctionTemplate::New(JS_ISOLATE, _escape));
	pt->Set(JS_STR("qualify"), v8::FunctionTemplate::New(JS_ISOLATE, _qualify));
	pt->Set(JS_STR("insertId"), v8::FunctionTemplate::New(JS_ISOLATE, _insertid));

	v8::Handle<v8::FunctionTemplate> rest = v8::FunctionTemplate::New(JS_ISOLATE, _result);
	rest->SetClassName(JS_STR("Result"));
	
	v8::Handle<v8::ObjectTemplate> resinst = rest->InstanceTemplate();
	resinst->SetInternalFieldCount(1);
	
	v8::Handle<v8::ObjectTemplate> resproto = rest->PrototypeTemplate();

	_rest.Reset(JS_ISOLATE, rest);

	/**
	 * Result prototype methods (new MySQL().query().*)
	 */
	resproto->Set(JS_STR("numRows"), v8::FunctionTemplate::New(JS_ISOLATE, _numrows));
	resproto->Set(JS_STR("numFields"), v8::FunctionTemplate::New(JS_ISOLATE, _numfields));
	resproto->Set(JS_STR("fetchNames"), v8::FunctionTemplate::New(JS_ISOLATE, _fetchnames));
	resproto->Set(JS_STR("fetchArrays"), v8::FunctionTemplate::New(JS_ISOLATE, _fetcharrays));
	resproto->Set(JS_STR("fetchObjects"), v8::FunctionTemplate::New(JS_ISOLATE, _fetchobjects));
	resproto->Set(JS_STR("close"), v8::FunctionTemplate::New(JS_ISOLATE, _result_close));

	exports->Set(JS_STR("MySQL"), mysqlt->GetFunction());
}

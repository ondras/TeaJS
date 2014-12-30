#include <v8.h>
#include "macros.h"
#include "gc.h"

#include <sqlite3.h>

#define SQLITE_PTR sqlite3 * db = LOAD_PTR(0, sqlite3 *)
#define SQLITE_ERRMSG sqlite3_errmsg(db)
#define ASSERT_CONNECTED if (!db) { JS_ERROR("No database opened yet."); return; }

namespace {

v8::Persistent<v8::FunctionTemplate> _rest;

void destroy(v8::Handle<v8::Object> obj) {
	v8::Handle<v8::Function> fun = v8::Handle<v8::Function>::Cast(obj->Get(JS_STR("close")));
	fun->Call(obj, 0, NULL);
}

/**
 * SQLite constructor does basically nothing. It just adds "this.close()" method to global GC
 */
JS_METHOD(_sqlite) {
	ASSERT_CONSTRUCTOR;
	sqlite3 * db = NULL;

	SAVE_PTR(0, db);
	GC * gc = GC_PTR;
	gc->add(args.This(), destroy);
	args.GetReturnValue().Set(args.This());
}

/**
 * Close DB connection
 */ 
JS_METHOD(_close) {
	SQLITE_PTR;
	
	if (db) {
		int result = sqlite3_close(db);
		if (result != SQLITE_OK) { JS_ERROR(SQLITE_ERRMSG); return; }
		SAVE_PTR(0, NULL);
	}

	args.GetReturnValue().Set(args.This());
}

/**
 * Should be called ASAP: new SQLite().open("dbfile")
 */ 
JS_METHOD(_open) {
	if (args.Length() < 1) {
		JS_TYPE_ERROR("Invalid call format. Use 'sqlite.open(filename)'");
		return;
	}
	v8::String::Utf8Value filename(args[0]);
	SQLITE_PTR;

	int result = sqlite3_open(*filename, &db);
	
	if (result != SQLITE_OK) { JS_ERROR(SQLITE_ERRMSG); return; }

	SAVE_PTR(0, db);

	args.GetReturnValue().Set(args.This());
}

/**
 * Query takes a string argument and returns an instance of Result object
 */ 
JS_METHOD(_query) {
	SQLITE_PTR;
	ASSERT_CONNECTED;
	if (args.Length() < 1) {
		JS_TYPE_ERROR("No query specified");
		return;
	}
	v8::String::Utf8Value q(args[0]);

	char ** results;
	int rows;
	int cols;
	char * someerror;
	
	int result = sqlite3_get_table(db, *q, &results, &rows, &cols, &someerror);
	if (result != SQLITE_OK) { JS_ERROR(SQLITE_ERRMSG); return; }
	
	int qc = args.This()->Get(JS_STR("queryCount"))->ToInteger()->Int32Value();
	args.This()->Set(JS_STR("queryCount"), JS_INT(qc+1));
	
	int items = cols * (rows+1);
	v8::Handle<v8::Array> data = v8::Array::New(JS_ISOLATE, items);
	for (int i=0;i<items;i++) {
		if (results[i] == NULL) {
			data->Set(JS_INT(i), v8::Null(JS_ISOLATE));
		} else {
			data->Set(JS_INT(i), JS_STR(results[i]));
		}
	}
	sqlite3_free_table(results);
	
	v8::Handle<v8::Value> resargs[] = { data, JS_INT(rows), JS_INT(cols) };
	v8::Local<v8::FunctionTemplate> rest = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, _rest);
	args.GetReturnValue().Set(rest->GetFunction()->NewInstance(3, resargs));
}

JS_METHOD(_changes) {
	SQLITE_PTR;
	ASSERT_CONNECTED;
	args.GetReturnValue().Set(JS_INT(sqlite3_changes(db)));
}

JS_METHOD(_insertid) {
	SQLITE_PTR;
	ASSERT_CONNECTED;
	args.GetReturnValue().Set(JS_INT(sqlite3_last_insert_rowid(db)));
}

JS_METHOD(_result) {
	SAVE_VALUE(0, args[0]);
	SAVE_VALUE(1, args[1]);
	SAVE_VALUE(2, args[2]);

	args.GetReturnValue().Set(args.This());
}

JS_METHOD(_numrows) {
	args.GetReturnValue().Set(LOAD_VALUE(1));
}

JS_METHOD(_numfields) {
	args.GetReturnValue().Set(LOAD_VALUE(2));
}

JS_METHOD(_fetchnames) {
	v8::Handle<v8::Array> data = v8::Handle<v8::Array>::Cast(LOAD_VALUE(0));
	v8::Handle<v8::Value> cols = LOAD_VALUE(2);
	
	int c = cols->ToInteger()->Int32Value();
	v8::Handle<v8::Array> result = v8::Array::New(JS_ISOLATE, c);
	for (int i=0;i<c;i++) {
		result->Set(JS_INT(i), data->Get(JS_INT(i)));
	}

	args.GetReturnValue().Set(result);
}

/**
 * Return result data as an array of JS arrays
 */ 
JS_METHOD(_fetcharrays) {
	v8::Handle<v8::Array> data = v8::Handle<v8::Array>::Cast(LOAD_VALUE(0));
	v8::Handle<v8::Value> rows = LOAD_VALUE(1);
	v8::Handle<v8::Value> cols = LOAD_VALUE(2);
	
	int r = rows->ToInteger()->Int32Value();
	int c = cols->ToInteger()->Int32Value();
	int index;
	
	v8::Handle<v8::Array> result = v8::Array::New(JS_ISOLATE, r);
	for (int i=0;i<r;i++) {
		v8::Handle<v8::Array> item = v8::Array::New(JS_ISOLATE, c);
		result->Set(JS_INT(i), item);
		for (int j=0; j<c; j++) {
			index = j + (i+1)*c;
			item->Set(JS_INT(j), data->Get(JS_INT(index)));
		}
	}

	args.GetReturnValue().Set(result);
}

/**
 * Return result data as an array of JS objects, indexed with column names
 */ 
JS_METHOD(_fetchobjects) {
	v8::Handle<v8::Array> data = v8::Handle<v8::Array>::Cast(LOAD_VALUE(0));
	v8::Handle<v8::Value> rows = LOAD_VALUE(1);
	v8::Handle<v8::Value> cols = LOAD_VALUE(2);
	
	int r = rows->ToInteger()->Int32Value();
	int c = cols->ToInteger()->Int32Value();
	int index;

	v8::Handle<v8::Array> result = v8::Array::New(JS_ISOLATE, r);
	if (c == 0) {
		args.GetReturnValue().Set(result);
		return;
	}

	v8::Handle<v8::Value> f = args.This()->Get(JS_STR("fetchNames"));
	v8::Handle<v8::Function> fun = v8::Handle<v8::Function>::Cast(f);
	v8::Handle<v8::Array> names = v8::Handle<v8::Array>::Cast(fun->Call(args.This(), 0, NULL));

	for (int i=0;i<r;i++) {
		v8::Handle<v8::Object> item = v8::Object::New(JS_ISOLATE);
		result->Set(JS_INT(i), item);
		for (int j=0; j<c; j++) {
			index = j + (i+1)*c;
			item->Set(names->Get(JS_INT(j)), data->Get(JS_INT(index)));
		}
	}

	args.GetReturnValue().Set(result);
}

} /* end namespace */

SHARED_INIT() {
	v8::HandleScope handle_scope(JS_ISOLATE);
	v8::Handle<v8::FunctionTemplate> ft = v8::FunctionTemplate::New(JS_ISOLATE, _sqlite);
	ft->SetClassName(JS_STR("SQLite"));

	v8::Handle<v8::ObjectTemplate> ot = ft->InstanceTemplate();
	ot->SetInternalFieldCount(1); /* database */
	
	/**
	 * Static property, useful for stats gathering
	 */
	ot->Set(JS_STR("queryCount"), JS_INT(0));
	
	v8::Handle<v8::ObjectTemplate> pt = ft->PrototypeTemplate();

	/**
	 * SQLite prototype methods (new SQLite().*)
	 */
	pt->Set(JS_STR("open"), v8::FunctionTemplate::New(JS_ISOLATE, _open));
	pt->Set(JS_STR("close"), v8::FunctionTemplate::New(JS_ISOLATE, _close));
	pt->Set(JS_STR("query"), v8::FunctionTemplate::New(JS_ISOLATE, _query));
	pt->Set(JS_STR("changes"), v8::FunctionTemplate::New(JS_ISOLATE, _changes));
	pt->Set(JS_STR("insertId"), v8::FunctionTemplate::New(JS_ISOLATE, _insertid));
	
	v8::Handle<v8::FunctionTemplate> rest = v8::FunctionTemplate::New(JS_ISOLATE, _result);
	rest->SetClassName(JS_STR("Result"));

	v8::Handle<v8::ObjectTemplate> resinst = rest->InstanceTemplate();
	resinst->SetInternalFieldCount(3); /* data, rows, columns */
	
	v8::Handle<v8::ObjectTemplate> resproto = rest->PrototypeTemplate();

	_rest.Reset(JS_ISOLATE, rest);

	/**
	 * Result prototype methods (new SQLite().query().*)
	 */
	resproto->Set(JS_STR("numRows"), v8::FunctionTemplate::New(JS_ISOLATE, _numrows));
	resproto->Set(JS_STR("numFields"), v8::FunctionTemplate::New(JS_ISOLATE, _numfields));
	resproto->Set(JS_STR("fetchNames"), v8::FunctionTemplate::New(JS_ISOLATE, _fetchnames));
	resproto->Set(JS_STR("fetchArrays"), v8::FunctionTemplate::New(JS_ISOLATE, _fetcharrays));
	resproto->Set(JS_STR("fetchObjects"), v8::FunctionTemplate::New(JS_ISOLATE, _fetchobjects));

	exports->Set(JS_STR("SQLite"), ft->GetFunction());
}

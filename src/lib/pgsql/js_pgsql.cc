/**
 * PostgreSQL database module for v8cgi
 *
 * Based on the corresponding MySQL and SQLite modules
 * "js_mysql.cc" and "js_sqlite.cc", respectively, from
 * v8cgi release 0.6.0; see also:
 * 1. http://www.postgresql.org/docs/8.4/static/libpq-exec.html
 * 2. http://www.postgresql.org/docs/8.4/static/libpq-async.html
 *
 * Initial version: 2009-08-17, Ryan RAFFERTY
 */

#include <v8.h>
#include "js_macros.h"
#include "js_gc.h"

#include <postgres_fe.h>
#include <libpq-fe.h>
#include <stdlib.h>
#include <string>
#include <sstream>

#define PGSQL_ERROR PQerrorMessage(conn)
#define ASSERT_CONNECTED if (!conn) { return JS_EXCEPTION("No connection established yet."); }
#define ASSERT_RESULT if (!res) { return JS_EXCEPTION("No result returned yet."); }
#define PGSQL_PTR_CON PGconn * conn = LOAD_PTR(0, PGconn *)
#define PGSQL_PTR_RES PGresult * res = LOAD_PTR(1, PGresult *)

namespace {

  v8::Persistent<v8::FunctionTemplate> rest;

  /**
   *	PostgreSQL constructor:
   * 	- Adds "this.close()" method to global GC
   */
  JS_METHOD(_pgsql) {
    ASSERT_CONSTRUCTOR;
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "close");
    return args.This();
  }

  /**
   *	CLOSE method
   *	- Closes connection to database server
   */ 
  JS_METHOD(_close) {
    PGSQL_PTR_CON;
    PGSQL_PTR_RES;
    if (conn) {
      if (res) {
	PQclear(res);
	SAVE_PTR(1, NULL);
      }
      PQfinish(conn);
      SAVE_PTR(0, NULL);
    }
    return args.This();
  }

  /**
   *	CONNECT method
   *	- call format: new PostgreSQL().connect("host", "user", "pass", "db")
   */ 
  JS_METHOD(_connect) {
    if (args.Length() < 1 and args.Length() != 5) {
      return JS_EXCEPTION("Invalid call format. Use either 'pgsql.connect(\"hostaddr=host port=port dbname=dbname user=user password=pass\")' or 'pgsql.connect(host, port, db, user, password)'");
    }
    PGconn * conn;
    if (args.Length() == 1) {
      v8::String::Utf8Value connstr(args[0]);
      conn = PQconnectdb(*connstr);
    }
    else {
      v8::String::Utf8Value pghost(args[0]);
      v8::String::Utf8Value pgport(args[1]);
      v8::String::Utf8Value pgdb(args[2]);
      v8::String::Utf8Value pguser(args[3]);
      v8::String::Utf8Value pgpass(args[4]);
      char * tmpstr = strdup("");
      sprintf(tmpstr, "hostaddr=%s port=%s db=%s user=%s password=%s connect_timeout=5", *pghost, *pgport, *pgdb, *pguser, *pgpass);
      v8::String::Utf8Value connstr(JS_STR(tmpstr));
      conn = PQconnectdb(*connstr);
    }
    if (PQstatus(conn) != CONNECTION_OK) {
      std::string ex = PGSQL_ERROR;
      if (conn) {
	PQfinish(conn);
	SAVE_PTR(0, NULL);
      }
      return JS_EXCEPTION(ex.c_str());
    }
    else {
      SAVE_PTR(0, conn);
      return args.This();
    }
  }

  /**
   *	QUERY method
   *	- accepts a string as its input argument,
   *	  and returns an instance of the Result class
   *	- alternatively, accepts a string and an object
   *	  as its input argument, in which the string and
   *	  object members are used as a prepared SQL
   *	  statement (c.f. "pg_query_params()" in PHP)
   */
  JS_METHOD(_query) {
    PGSQL_PTR_CON;
    ASSERT_CONNECTED;
    if (args.Length() < 1) {
      return JS_EXCEPTION("No query specified");
    }
    if (args.Length() > 1) {
      return JS_EXCEPTION("Too many input parameters");
    }
    v8::String::Utf8Value q(args[0]);
    PGresult *res;
    res = PQexec(conn, *q);
    int code = -1;
    if (!(!res)) {
      code = PQresultStatus(res);
    }
    if (code != PGRES_COMMAND_OK && code != PGRES_TUPLES_OK) {
      const char * errPrefix = "[js_pgsql.cc @ _query] ERROR: ";
      const char * errPostfix = ")";
      char errTmp[10];
      sprintf(errTmp, "%d", code);
      const char * errMid = strdup(errTmp);
      char * errMsg = strdup(errPrefix);
      strcat(errMsg, PGSQL_ERROR);
      strcat(errMsg, " (");
      strcat(errMsg, errMid);
      strcat(errMsg, errPostfix);
      PQclear(res);
      return JS_EXCEPTION(errMsg);
    }
    int qc = args.This()->Get(JS_STR("queryCount"))->ToInteger()->Int32Value();
    args.This()->Set(JS_STR("queryCount"), JS_INT(qc+1));
    if (res) {
      v8::Handle<v8::Value> resargs[] = { v8::External::New((void *) res) };
      SAVE_PTR(1, res);
      return rest->GetFunction()->NewInstance(1, resargs);
    } else {
      if (PQntuples(res)) {
	PQclear(res);
	std::string ex = PGSQL_ERROR;
	if (conn) {
	  PQfinish(conn);
	  SAVE_PTR(0, NULL);
	}
	return JS_EXCEPTION(ex.c_str());
      } else {
	SAVE_PTR(1, res);
        return args.This();
      }
    }
  }

  /**
   *	QUERYPARAMS method
   *	- accepts a string as its input argument,
   *	  and returns an instance of the Result class
   *	- alternatively, accepts a string and an object
   *	  as its input argument, in which the string and
   *	  object members are used as a prepared SQL
   *	  statement (c.f. "pg_query_params()" in PHP)
   */
  JS_METHOD(_queryparams) {
    PGSQL_PTR_CON;
    ASSERT_CONNECTED;
    if (args.Length() < 2) {
      return JS_EXCEPTION("Too few input parameters");
    }
    if (args.Length() > 2) {
      return JS_EXCEPTION("Too many input parameters");
    }
    PGresult *res;
    v8::String::Utf8Value q(args[0]);
    v8::Handle<v8::Array> tarray = v8::Handle<v8::Array>::Cast(args[1]->ToObject());
    v8::Handle<v8::Object> parray = args[1]->ToObject();
    int nparams = tarray->Length();
    char ** params = (char **)malloc(nparams);
    size_t n = 0;
    for(int i = 0; i < nparams; i++) {
	n = tarray->Get(JS_INT(i))->ToString()->Utf8Length();
	v8::String::Utf8Value tval(tarray->Get(JS_INT(i))->ToString());
	params[i] = new char[n + 1];
	params[i] = strdup(*tval);
    }
    res = PQexecParams(conn, *q, nparams, NULL, params, NULL, NULL, 0);
    int code = -1;
    if (!(!res)) {
      code = PQresultStatus(res);
    }
    if (code != PGRES_COMMAND_OK && code != PGRES_TUPLES_OK) {
      std::string str(PQresultErrorMessage(res));
      PQclear(res);
      std::string ex = PGSQL_ERROR;
      if (conn) {
	PQfinish(conn);
	SAVE_PTR(0, NULL);
      }
      return JS_EXCEPTION(ex.c_str());
    }
    int qc = args.This()->Get(JS_STR("queryCount"))->ToInteger()->Int32Value();
    args.This()->Set(JS_STR("queryCount"), JS_INT(qc+1));
    if (res) {
      v8::Handle<v8::Value> resargs[] = { v8::External::New((void *) res) };
      SAVE_PTR(1, res);
      return rest->GetFunction()->NewInstance(1, resargs);
    }
    else {
      if (PQntuples(res)) {
	std::string ex = PGSQL_ERROR;
	if (conn) {
	  PQfinish(conn);
	  SAVE_PTR(0, NULL);
	  SAVE_PTR(1, NULL);
	}
	return JS_EXCEPTION(ex.c_str());
      }
      else {
	SAVE_PTR(1, NULL);
	return args.This();
      }
    }
  }

  /**
   *	SENDQUERY method
   *	- asynchronous
   *	- accepts a string as its input argument,
   *	  which is sent to the SQL server for
   *	  processing as a SQL statement
   */
  JS_METHOD(_sendquery) {
    PGSQL_PTR_CON;
    ASSERT_CONNECTED;
    if (args.Length() < 1) {
      return JS_EXCEPTION("No query specified");
    }
    if (args.Length() > 1) {
      return JS_EXCEPTION("Too many input parameters");
    }
    v8::String::Utf8Value q(args[0]);
    int code = -1;
    code = PQsendQuery(conn, *q);
    if (code != 1) {
      std::string str(PQerrorMessage(conn));
      const char * cstr = str.c_str();
      return JS_EXCEPTION(cstr);
    }
    int qc = args.This()->Get(JS_STR("queryCount"))->ToInteger()->Int32Value();
    args.This()->Set(JS_STR("queryCount"), JS_INT(qc+1));
    return JS_BOOL(code);
  }

  /**
   *	SENDQUERYPARAMS method
   *	- asynchronous
   *	- accepts a string as its input argument,
   *	  which is sent to the SQL server for
   *	  processing as a SQL statement
   */
  JS_METHOD(_sendqueryparams) {
    PGSQL_PTR_CON;
    ASSERT_CONNECTED;
    if (args.Length() < 1) {
      return JS_EXCEPTION("No query specified");
    }
    if (args.Length() > 1) {
      return JS_EXCEPTION("Too many input parameters");
    }
    v8::String::Utf8Value q(args[0]);
    v8::Handle<v8::Array> tarray = v8::Handle<v8::Array>::Cast(args[1]->ToObject());
    v8::Handle<v8::Object> parray = args[1]->ToObject();
    int nparams = tarray->Length();
    char ** params = (char **)malloc(nparams);
    size_t n = 0;
    for(int i = 0; i < nparams; i++) {
	n = tarray->Get(JS_INT(i))->ToString()->Utf8Length();
	v8::String::Utf8Value tval(tarray->Get(JS_INT(i))->ToString());
	params[i] = new char[n + 1];
	params[i] = strdup(*tval);
    }
    int code = PQsendQueryParams(conn, *q, nparams, NULL, params, NULL, NULL, 0);
    if (code != 1) {
      std::string str(PQerrorMessage(conn));
      const char * cstr = str.c_str();
      return JS_EXCEPTION(cstr);
    }
    int qc = args.This()->Get(JS_STR("queryCount"))->ToInteger()->Int32Value();
    args.This()->Set(JS_STR("queryCount"), JS_INT(qc+1));
    return JS_BOOL(code);
  }

  /**
   *	GETRESULT method
   *	- asynchronous
   */
  JS_METHOD(_getresult) {
    PGSQL_PTR_CON;
    ASSERT_CONNECTED;
    PGresult *res;
    res = PQgetResult(conn);
    int code = -1;
    if (!(!res)) {
      code = PQresultStatus(res);
    }
    if (code != PGRES_COMMAND_OK && code != PGRES_TUPLES_OK) {
      std::string str(PQresultErrorMessage(res));
      PQclear(res);
      std::stringstream buf;
	buf << "(";
	buf << code;
	buf << ") ";
	buf << str;
      str = buf.str();
      const char * cstr = str.c_str();
      return JS_EXCEPTION(cstr);
    }
    SAVE_PTR(1, res);
    if (res) {
      v8::Handle<v8::Value> resargs[] = { v8::External::New((void *) res) };
      return rest->GetFunction()->NewInstance(1, resargs);
    } else {
      if (PQntuples(res)) {
        return JS_EXCEPTION(PGSQL_ERROR);
      } else {
        return args.This();
      }
    }
  }

  /**
   *	ISBUSY method
   *	- asynchronous
   */
  JS_METHOD(_isbusy) {
    PGSQL_PTR_CON;
    ASSERT_CONNECTED;
    return JS_BOOL(PQisBusy(conn));
  }

  /**
   *	CONSUMEINPUT method
   *	- asynchronous
   */
  JS_METHOD(_consumeinput) {
    PGSQL_PTR_CON;
    ASSERT_CONNECTED;
    return JS_BOOL(PQconsumeInput(conn));
  }

  JS_METHOD(_escape) {
    PGSQL_PTR_CON;
    ASSERT_CONNECTED;
    if (args.Length() < 1) {
      return JS_EXCEPTION("Nothing to escape");
    }
    v8::String::Utf8Value str(args[0]);
    int len = args[0]->ToString()->Utf8Length();
    char * result = new char[2*len + 1];
    int length = PQescapeStringConn(conn, result, *str, len, NULL);
    v8::Handle<v8::Value> output = JS_STR(result, length);
    delete[] result;
    return output;
  }

  JS_METHOD(_escapebytea) {
    PGSQL_PTR_CON;
    ASSERT_CONNECTED;
    if (args.Length() < 1) {
      return JS_EXCEPTION("Nothing to escape");
    }
    v8::String::Utf8Value str(args[0]);
    int len = args[0]->ToString()->Utf8Length();
    size_t * length = NULL;
    char * result = (char *)PQescapeByteaConn(conn, (const unsigned char *)*str, len, length);
    v8::Handle<v8::Value> output = JS_STR(result, *length);
    delete[] result;
    return output;
  }

  JS_METHOD(_unescapebytea) {
    PGSQL_PTR_CON;
    ASSERT_CONNECTED;
    if (args.Length() < 1) {
      return JS_EXCEPTION("Nothing to escape");
    }
    v8::String::Utf8Value str(args[0]);
    size_t * length = NULL;
    char * result = (char *)PQunescapeBytea((const unsigned char *)*str, length);
    v8::Handle<v8::Value> output = JS_STR(result, *length);
    delete[] result;
    return output;
  }

  JS_METHOD(_result) {
    SAVE_VALUE(0, args[0]);
    return args.This();
  }

  JS_METHOD(_numrows) {
    PGresult * res = LOAD_PTR(0, PGresult *);
    ASSERT_RESULT;
    return JS_INT(PQntuples(res));
  }

  JS_METHOD(_numfields) {
    PGresult * res = LOAD_PTR(0, PGresult *);
    ASSERT_RESULT;
    return JS_INT(PQnfields(res));
  }

  JS_METHOD(_numaffectedrows) {
    PGresult * res = LOAD_PTR(0, PGresult *);
    ASSERT_RESULT;
    return JS_INT(atoi(PQcmdTuples(res)));
  }

  JS_METHOD(_fetchnames) {
    PGresult * res = LOAD_PTR(0, PGresult *);
    ASSERT_RESULT;
    int cnt = PQnfields(res);
    v8::Handle<v8::Array> result = v8::Array::New(cnt);
    for(int i = 0; i < cnt; i++) {
      result->Set(JS_INT(i), JS_STR(PQfname(res, i)));
    }
    return result;
  }

  /**
   * Return indicated result value
   */
  JS_METHOD(_fetchresult) {
    PGresult * res = LOAD_PTR(0, PGresult *);
    ASSERT_RESULT;
    int x = PQnfields(res);
    int y = PQntuples(res);
    v8::String::Utf8Value a(args[0]);
    v8::String::Utf8Value b(args[1]);
    int i = atoi(*a);
    int j = atoi(*b);
    if (i > x || i < 0) {
      return JS_EXCEPTION("Row number out of bounds");
    }
    if (j > y || j < 0) {
      return JS_EXCEPTION("Column number out of bounds");
    }
    return JS_STR(PQgetvalue(res,i,j));
  }

  /**
   * Return indicated result value
   */
  JS_METHOD(_fetchfield) {
    PGresult * res = LOAD_PTR(0, PGresult *);
    ASSERT_RESULT;
    int x = PQnfields(res);
    int y = PQntuples(res);
    v8::String::Utf8Value a(args[0]);
    v8::String::Utf8Value b(args[1]);
    int i = atoi(*a);
    int j = PQfnumber(res,*b);
    if (i > x || i < 0) {
      return JS_EXCEPTION("Row number out of bounds");
    }
    if (j > y || j < 0) {
      return JS_EXCEPTION("Column name does not exist");
    }
    return JS_STR(PQgetvalue(res,i,j));
  }

  /**
   * Return all rows of result data as a two-dimensional JS array
   */
  JS_METHOD(_fetchall) {
    PGresult * res = LOAD_PTR(0, PGresult *);
    ASSERT_RESULT;
    int x = PQnfields(res);
    int y = PQntuples(res);
    v8::Handle<v8::Array> result = v8::Array::New(y);
    for (int i = 0; i < y; i++) {
      v8::Handle<v8::Array> item = v8::Array::New(x);
      result->Set(JS_INT(i), item);
      for (int j=0; j<x; j++) {
	if (PQgetisnull(res, i, j)) {
	  item->Set(JS_INT(j), v8::Null());
	}
	else {
	  item->Set(JS_INT(j), JS_STR(PQgetvalue(res, i, j)));
	}
      }
    }
    return result;
  }

  /**
   * Return one row of result data as a JS array
   */
  JS_METHOD(_fetchrow) {
    PGresult * res = LOAD_PTR(0, PGresult *);
    ASSERT_RESULT;
    int x = PQnfields(res);
    int y = PQntuples(res);
    int i = 0;
    if (args.Length() > 0) {
      v8::String::Utf8Value a(args[0]);
      i = atoi(*a);
    }
    v8::Handle<v8::Array> result = v8::Array::New(y);
    for (int j=0; j<x; j++) {
      if (PQgetisnull(res, i, j)) {
        result->Set(JS_INT(j), v8::Null());
      }
      else {
        result->Set(JS_INT(j), JS_STR(PQgetvalue(res, i, j)));
      }
    }
    return result;
  }

  /**
   * Return all rows of result data as a two-dimensional JS hash object,
   * indexed by column name
   */ 
  JS_METHOD(_fetchallobjects) {
    PGresult * res = LOAD_PTR(0, PGresult *);
    ASSERT_RESULT;
    int x = PQnfields(res);
    int y = PQntuples(res);
    int cnt = PQnfields(res);
    v8::Handle<v8::Array> fieldnames = v8::Array::New(cnt);
    for(int u = 0; u < cnt; u++) {
      fieldnames->Set(JS_INT(u), JS_STR(PQfname(res, u)));
    }
    v8::Handle<v8::Array> result = v8::Array::New(y);
    for (int i = 0; i < y; i++) {
      v8::Handle<v8::Object> item = v8::Object::New();
      result->Set(JS_INT(i), item);
      for (int j=0; j<x; j++) {
	if (PQgetisnull(res, i, j)) {
	  item->Set(fieldnames->Get(JS_INT(j)), v8::Null());
	} 
	else {
	  item->Set(fieldnames->Get(JS_INT(j)), JS_STR(PQgetvalue(res, i, j)));
	}
      }
    }
    return result;
  }

  /**
   * Return one row of result data as a JS hash object,
   * indexed by column name
   */ 
  JS_METHOD(_fetchrowobject) {
    PGresult * res = LOAD_PTR(0, PGresult *);
    ASSERT_RESULT;
    int x = PQnfields(res);
    int y = PQntuples(res);
    int cnt = PQnfields(res);
    int i = 0;
    if (args.Length() > 0) {
      v8::String::Utf8Value a(args[0]);
      i = atoi(*a);
    }
    v8::Handle<v8::Array> fieldnames = v8::Array::New(cnt);
    for(int u = 0; u < cnt; u++) {
      fieldnames->Set(JS_INT(u), JS_STR(PQfname(res, u)));
    }
    v8::Handle<v8::Array> result = v8::Array::New(y);
    for (int j=0; j<x; j++) {
      if (PQgetisnull(res, i, j)) {
        result->Set(fieldnames->Get(JS_INT(j)), v8::Null());
      } 
      else {
        result->Set(fieldnames->Get(JS_INT(j)), JS_STR(PQgetvalue(res, i, j)));
      }
    }
    return result;
  }

} /* end namespace */

SHARED_INIT() {
  v8::HandleScope handle_scope;
  v8::Handle<v8::FunctionTemplate> ft = v8::FunctionTemplate::New(_pgsql);
  ft->SetClassName(JS_STR("PostgreSQL"));

  v8::Handle<v8::ObjectTemplate> ot = ft->InstanceTemplate();
  ot->SetInternalFieldCount(2); /* connection, result */

  /**
   * Static property, useful for stats gathering
   */
  ot->Set(JS_STR("queryCount"), JS_INT(0));

  v8::Handle<v8::ObjectTemplate> pt = ft->PrototypeTemplate();

  /**
   * PostgreSQL prototype methods (new PostgreSQL().*)
   */
  pt->Set(JS_STR("connect"), v8::FunctionTemplate::New(_connect));
  pt->Set(JS_STR("close"), v8::FunctionTemplate::New(_close));
  pt->Set(JS_STR("query"), v8::FunctionTemplate::New(_query));
  pt->Set(JS_STR("queryParams"), v8::FunctionTemplate::New(_queryparams));
  pt->Set(JS_STR("escape"), v8::FunctionTemplate::New(_escape));
  pt->Set(JS_STR("escapeBytea"), v8::FunctionTemplate::New(_escapebytea));
  pt->Set(JS_STR("sendQuery"), v8::FunctionTemplate::New(_sendquery));
  pt->Set(JS_STR("sendQueryParams"), v8::FunctionTemplate::New(_sendqueryparams));
  pt->Set(JS_STR("getResult"), v8::FunctionTemplate::New(_getresult));
  pt->Set(JS_STR("isBusy"), v8::FunctionTemplate::New(_isbusy));
  pt->Set(JS_STR("consumeInput"), v8::FunctionTemplate::New(_consumeinput));

  rest = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(_result));
  rest->SetClassName(JS_STR("Result"));

  v8::Handle<v8::ObjectTemplate> resinst = rest->InstanceTemplate();
  resinst->SetInternalFieldCount(1);

  v8::Handle<v8::ObjectTemplate> resproto = rest->PrototypeTemplate();

  /**
   * Result prototype methods (new PostgreSQL().query().*)
   */
  resproto->Set(JS_STR("numRows"), v8::FunctionTemplate::New(_numrows));
  resproto->Set(JS_STR("numFields"), v8::FunctionTemplate::New(_numfields));
  resproto->Set(JS_STR("numAffectedRows"), v8::FunctionTemplate::New(_numaffectedrows));
  resproto->Set(JS_STR("fetchNames"), v8::FunctionTemplate::New(_fetchnames));
  resproto->Set(JS_STR("fetchResult"), v8::FunctionTemplate::New(_fetchresult));
  resproto->Set(JS_STR("fetchField"), v8::FunctionTemplate::New(_fetchfield));
  resproto->Set(JS_STR("fetchRow"), v8::FunctionTemplate::New(_fetchrow));
  resproto->Set(JS_STR("fetchRowObject"), v8::FunctionTemplate::New(_fetchrowobject));
  resproto->Set(JS_STR("fetchAll"), v8::FunctionTemplate::New(_fetchall));
  resproto->Set(JS_STR("fetchAllObjects"), v8::FunctionTemplate::New(_fetchallobjects));
  resproto->Set(JS_STR("unescapeBytea"), v8::FunctionTemplate::New(_unescapebytea));

  exports->Set(JS_STR("PostgreSQL"), ft->GetFunction());
}

#include <v8.h>
#include <mysql.h>
#include <stdlib.h>

v8::Handle<v8::FunctionTemplate> rest;

v8::Handle<v8::Value> _mysql(const v8::Arguments& args) {
  v8::HandleScope handle_scope;
  if (args.This()->InternalFieldCount() == 0) {
    return v8::ThrowException(v8::String::New("Invalid call format. Use 'new MySQL()'"));
  }
  args.This()->SetInternalField(0, v8::Boolean::New(false));
    
  return args.This();
}

v8::Handle<v8::Value> _connect(const v8::Arguments& args) {
  v8::HandleScope handle_scope;
  if (args.Length() < 4) {
    return v8::ThrowException(v8::String::New("Invalid call format. Use 'mysql.connect(host, user, pass, db)'"));
  }

  MYSQL *conn;
  
  v8::String::Utf8Value host(args[0]);
  v8::String::Utf8Value user(args[1]);
  v8::String::Utf8Value pass(args[2]);
  v8::String::Utf8Value db(args[3]);
	      
  conn = mysql_init(NULL);

  if (!mysql_real_connect(conn, *host, *user, *pass, *db, 0, NULL, 0)){
    return v8::Boolean::New(false);
  } else {
    mysql_query(conn, "SET NAMES 'utf8'");				 
    args.This()->SetInternalField(0, v8::External::New((void *)conn));
    return args.This();
  }  
}

v8::Handle<v8::Value> _query(const v8::Arguments &args) {
  v8::HandleScope handle_scope;
  v8::Handle<v8::Value> c = args.This()->GetInternalField(0);
  if (c->IsFalse()) {
    return v8::ThrowException(v8::String::New("No connection established"));
  }		
  if (args.Length() < 1) {
    return v8::ThrowException(v8::String::New("No query specified"));
  }
  v8::String::Utf8Value q(args[0]);
  
  MYSQL * conn = reinterpret_cast<MYSQL *>(v8::Handle<v8::External>::Cast(c)->Value());
  MYSQL_RES *res;
  mysql_query(conn, *q);
  res = mysql_store_result(conn);
  
  if (res) {
    v8::Handle<v8::Value> resargs[] = { v8::External::New((void *) res) };
    return rest->GetFunction()->NewInstance(1, resargs);
  } else {
    return v8::Boolean::New(false);
  }
}

v8::Handle<v8::Value> _error(const v8::Arguments &args) {
  v8::HandleScope handle_scope;
  v8::Handle<v8::Value> c = args.This()->GetInternalField(0);
  if (c->IsFalse()) {
    return v8::ThrowException(v8::String::New("No connection established"));
  }
	    	  
  MYSQL * conn = reinterpret_cast<MYSQL *>(v8::Handle<v8::External>::Cast(c)->Value());

  return v8::String::New(mysql_error(conn));
}

v8::Handle<v8::Value> _errno(const v8::Arguments &args) {
  v8::HandleScope handle_scope;
  v8::Handle<v8::Value> c = args.This()->GetInternalField(0);
  if (c->IsFalse()) {
    return v8::ThrowException(v8::String::New("No connection established"));
  }
    
  MYSQL * conn = reinterpret_cast<MYSQL *>(v8::Handle<v8::External>::Cast(c)->Value());

  return v8::Integer::New(mysql_errno(conn));
}

v8::Handle<v8::Value> _affectedrows(const v8::Arguments &args) {
  v8::HandleScope handle_scope;
  v8::Handle<v8::Value> c = args.This()->GetInternalField(0);
  if (c->IsFalse()) {
    return v8::ThrowException(v8::String::New("No connection established"));
  }
	    
  MYSQL * conn = reinterpret_cast<MYSQL *>(v8::Handle<v8::External>::Cast(c)->Value());

  return v8::Integer::New(mysql_affected_rows(conn));
}

v8::Handle<v8::Value> _insertid(const v8::Arguments &args) {
  v8::HandleScope handle_scope;
  v8::Handle<v8::Value> c = args.This()->GetInternalField(0);
  if (c->IsFalse()) {
    return v8::ThrowException(v8::String::New("No connection established"));
  }

  MYSQL * conn = reinterpret_cast<MYSQL *>(v8::Handle<v8::External>::Cast(c)->Value());

  return v8::Integer::New(mysql_insert_id(conn));
}

v8::Handle<v8::Value> _escape(const v8::Arguments &args) {
  v8::HandleScope handle_scope;
  v8::Handle<v8::Value> c = args.This()->GetInternalField(0);
  if (c->IsFalse()) {
    return v8::ThrowException(v8::String::New("No connection established"));
  }
  if (args.Length() < 1) {
    return v8::ThrowException(v8::String::New("Nothing to escape"));
  }
  v8::String::Utf8Value str(args[0]);
  
  int len = args[0]->ToString()->Utf8Length();
  char * result = (char *) malloc((2*len+1) * sizeof(char));
  
  MYSQL * conn = reinterpret_cast<MYSQL *>(v8::Handle<v8::External>::Cast(c)->Value());

  int length = mysql_real_escape_string(conn, result, *str, len);

  return v8::String::New(result, length);
}

v8::Handle<v8::Value> _result(const v8::Arguments & args) {
  v8::HandleScope handle_scope;
  args.This()->SetInternalField(0, args[0]);
  return args.This();
}

v8::Handle<v8::Value> _numrows(const v8::Arguments & args) {
  v8::HandleScope handle_scope;
  v8::Handle<v8::Value> r = args.This()->GetInternalField(0);
  MYSQL_RES * res = reinterpret_cast<MYSQL_RES *>(v8::Handle<v8::External>::Cast(r)->Value());

  return v8::Integer::New(mysql_num_rows(res));
}

v8::Handle<v8::Value> _numfields(const v8::Arguments & args) {
  v8::HandleScope handle_scope;
  v8::Handle<v8::Value> r = args.This()->GetInternalField(0);
  MYSQL_RES * res = reinterpret_cast<MYSQL_RES *>(v8::Handle<v8::External>::Cast(r)->Value());

  return v8::Integer::New(mysql_num_fields(res));
}

v8::Handle<v8::Value> _fetchnames(const v8::Arguments & args) {
  v8::HandleScope handle_scope;
  v8::Handle<v8::Value> r = args.This()->GetInternalField(0);
  MYSQL_RES * res = reinterpret_cast<MYSQL_RES *>(v8::Handle<v8::External>::Cast(r)->Value());

  int cnt = mysql_num_fields(res);
  MYSQL_FIELD * fields = mysql_fetch_fields(res);
  v8::Handle<v8::Array> result = v8::Array::New(cnt);
  
  for(int i = 0; i < cnt; i++) {
    result->Set(v8::Integer::New(i), v8::String::New(fields[i].name));
  }
  
  return result;
}

v8::Handle<v8::Value> _fetcharrays(const v8::Arguments & args) {
  v8::HandleScope handle_scope;
  v8::Handle<v8::Value> r = args.This()->GetInternalField(0);
  MYSQL_RES * res = reinterpret_cast<MYSQL_RES *>(v8::Handle<v8::External>::Cast(r)->Value());
  mysql_data_seek(res, 0);

  int x = mysql_num_fields(res);
  int y = mysql_num_rows(res);
  MYSQL_ROW row;
  v8::Handle<v8::Array> result = v8::Array::New(y);
  
  for (int i = 0; i < y; i++) {
    row = mysql_fetch_row(res);
    v8::Handle<v8::Array> item = v8::Array::New(x);
    result->Set(v8::Integer::New(i), item);
    for (int j=0; j<x; j++) {
      if (row[j] == NULL) {
        item->Set(v8::Integer::New(j), v8::Null());
      } else {
        item->Set(v8::Integer::New(j), v8::String::New(row[j]));
      }
    }
  }
  
  return result;
}

v8::Handle<v8::Value> _fetchobjects(const v8::Arguments & args) {
  v8::HandleScope handle_scope;
  v8::Handle<v8::Value> r = args.This()->GetInternalField(0);
  MYSQL_RES * res = reinterpret_cast<MYSQL_RES *>(v8::Handle<v8::External>::Cast(r)->Value());
  mysql_data_seek(res, 0);

  int x = mysql_num_fields(res);
  int y = mysql_num_rows(res);
  MYSQL_FIELD * fields = mysql_fetch_fields(res);
  MYSQL_ROW row;
  v8::Handle<v8::Array> result = v8::Array::New(y);
  
  for (int i = 0; i < y; i++) {
    row = mysql_fetch_row(res);
    v8::Handle<v8::Object> item = v8::Object::New();
    result->Set(v8::Integer::New(i), item);
    for (int j=0; j<x; j++) {
      if (row[j] == NULL) {
        item->Set(v8::String::New(fields[j].name), v8::Null());
      } else {
        item->Set(v8::String::New(fields[j].name), v8::String::New(row[j]));
      }
    }
  }
  
  return result;
}

void setup_mysql(v8::Handle<v8::Object> target) {
//  v8::HandleScope handle_scope;

  v8::Handle<v8::FunctionTemplate> ft = v8::FunctionTemplate::New(_mysql);
  ft->SetClassName(v8::String::New("MySQL"));

  v8::Handle<v8::ObjectTemplate> ot = ft->InstanceTemplate();
  ot->SetInternalFieldCount(1); /* connection */
       
  v8::Handle<v8::ObjectTemplate> pt = ft->PrototypeTemplate();
  pt->Set(v8::String::New("connect"), v8::FunctionTemplate::New(_connect));
  pt->Set(v8::String::New("query"), v8::FunctionTemplate::New(_query));
  pt->Set(v8::String::New("error"), v8::FunctionTemplate::New(_error));
  pt->Set(v8::String::New("errno"), v8::FunctionTemplate::New(_errno));
  pt->Set(v8::String::New("affectedRows"), v8::FunctionTemplate::New(_affectedrows));
  pt->Set(v8::String::New("escape"), v8::FunctionTemplate::New(_escape));
  pt->Set(v8::String::New("insertId"), v8::FunctionTemplate::New(_insertid));
  
  rest = v8::FunctionTemplate::New(_result);
  rest->SetClassName(v8::String::New("Result"));
  
  v8::Handle<v8::ObjectTemplate> resinst = rest->InstanceTemplate();
  resinst->SetInternalFieldCount(1);
  
  v8::Handle<v8::ObjectTemplate> resproto = rest->PrototypeTemplate();
  resproto->Set(v8::String::New("numRows"), v8::FunctionTemplate::New(_numrows));
  resproto->Set(v8::String::New("numFields"), v8::FunctionTemplate::New(_numfields));
  resproto->Set(v8::String::New("fetchNames"), v8::FunctionTemplate::New(_fetchnames));
  resproto->Set(v8::String::New("fetchArrays"), v8::FunctionTemplate::New(_fetcharrays));
  resproto->Set(v8::String::New("fetchObjects"), v8::FunctionTemplate::New(_fetchobjects));

  target->Set(v8::String::New("MySQL"), ft->GetFunction());
}

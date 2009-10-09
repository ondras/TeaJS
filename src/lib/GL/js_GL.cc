/*
 *	OpenGL module for v8cgi
 *
 *	Based on Nicolas Garcia Belmonte's V8-GL project
 *	(http://github.com/philogb/v8-gl/tree/master#readme)
 *
 *	Initial version: 2009-10-07, Ryan RAFFERTY
 */

#include <stdlib.h>
#include <map>
#include <stdio.h>
#include <stropts.h>
#include <string.h>
#include <sstream>

#include <v8.h>
#include "js_macros.h"
#include "js_gc.h"
#include "js_GL.hpp"

namespace GLv8 {

  JS_METHOD(_gl) {
    Handle<ObjectTemplate> obj( GlFactory::createGl() );
    Handle<Value> ret(obj->NewInstance());
    return ret;
  }

  JS_METHOD(_glu) {
    //Handle<ObjectTemplate> obj( GluFactory::createGlu() );
    //Handle<Value> ret(obj->NewInstance());
    return args.This();
  }

  JS_METHOD(_gles) {
    Handle<ObjectTemplate> obj( GlesFactory::createGles() );
    Handle<Value> ret(obj->NewInstance());
    return ret;
  }

  JS_METHOD(_glut) {
    int pargc = 0;
    char** argv = NULL;
    v8::Handle<v8::Object> sys = JS_GLOBAL->Get(JS_STR("system"))->ToObject();
    v8::Handle<v8::Value> targs = sys->Get(JS_STR("args"));
    v8::Handle<v8::Array> arr( v8::Handle<v8::Array>::Cast(targs) );
    pargc = arr->Length();
    argv = new char*[(pargc+1)];
    std::string ctmp( "test" );
    argv[0] = strdup(ctmp.c_str());
    for (int i = 0; i < pargc; i++) {
      std::string tmp( *String::Utf8Value( arr->Get(JS_INT(i))->ToString() ) );
      argv[(i+1)] = strdup(tmp.c_str());
      fprintf(stdout,"argv[%d] : %s\n",i,argv[i]);
    }
    Handle<ObjectTemplate> object_template;
    object_template = GlutFactory::createGlut(&pargc, (char **)argv);
    Handle<Value> ret(object_template->NewInstance());
    args.This()->Set(JS_STR("obj"),ret);
    return args.This();
  }

}

SHARED_INIT() {

// void jsGL() {

  using namespace GLv8;

  // Create a handle scope to hold temporary references.
  HandleScope handle_scope;

  // Create a template for the global object where we set the
  // built-in global functions.
  Handle<Object> global = JS_GLOBAL;
  
  int * pargc = NULL;
  pargc = new int[1];
  char** argv = NULL;
  v8::Handle<v8::Object> sys = JS_GLOBAL->Get(JS_STR("system"))->ToObject();
  v8::Handle<v8::Value> targs = sys->Get(JS_STR("args"));
  v8::Handle<v8::Array> arr( v8::Handle<v8::Array>::Cast(targs) );

  *pargc = arr->Length();
  argv = new char*[(*pargc+1)];
  std::string ctmp( "./v8cgi" );
  argv[0] = strdup(ctmp.c_str());
  for (int i = 0; i < *pargc; i++) {
    std::string tmp( *String::Utf8Value( arr->Get(JS_INT(i))->ToString() ) );
    argv[(i+1)] = strdup(tmp.c_str());
  }

  // Each processor gets its own context so different processors
  // don't affect each other.
  //
  Handle<ObjectTemplate> Gl_t = GlFactory::createGl();
  Handle<ObjectTemplate> Gles_t = GlesFactory::createGles();
  Handle<ObjectTemplate> Glu_t = createGlu();
  Handle<ObjectTemplate> Glut_t = GlutFactory::createGlut(pargc, argv);

  Handle<FunctionTemplate> ftGl = FunctionTemplate::New(_gl);
  Handle<FunctionTemplate> ftGles = FunctionTemplate::New(_gles);
  Handle<FunctionTemplate> ftGlu = FunctionTemplate::New(_glu);
  Handle<FunctionTemplate> ftGlut = FunctionTemplate::New(_glut);
  ftGl->SetClassName(JS_STR("Gl"));
  ftGles->SetClassName(JS_STR("Gles"));
  ftGlu->SetClassName(JS_STR("Glu"));
  ftGlut->SetClassName(JS_STR("Glut"));

  Handle<ObjectTemplate> otGl = ftGl->InstanceTemplate();
  Handle<ObjectTemplate> otGles = ftGles->InstanceTemplate();
  Handle<ObjectTemplate> otGlu = ftGlu->InstanceTemplate();
  Handle<ObjectTemplate> otGlut = ftGlut->InstanceTemplate();

  Handle<Object> Gl = Gl_t->NewInstance();
  Handle<Object> Glu = Glu_t->NewInstance();
  Handle<Object> Gles = Gles_t->NewInstance();
  Handle<Object> Glut = Glut_t->NewInstance();

  exports->Set(String::New("Gl"), Gl);
  exports->Set(String::New("Gles"), Gles);
  global->Set(String::New("Glu"), ftGlu->GetFunction());
  global->Set(String::New("Glut"), ftGlut->GetFunction());

  global->Set(JS_STR("Gl"), Gl);
  global->Set(JS_STR("Glu"), Glu);
  global->Set(JS_STR("Gles"), Gles);
  global->Set(JS_STR("Glut"), Glut);

  Handle<Context> context ( Context::GetCurrent() );

  GlutFactory::glut_persistent_context = Persistent<Context>::New(context);
  GlesFactory::gles_persistent_context = Persistent<Context>::New(context);

  // Enter the new context so all the following operations take place
  // within it.
  Context::Scope context_scope(context);

  //Append *this* as Gl static variable so we can do dot-this-dot-that stuff
  GlFactory::self_ = Persistent<Object>::New(Gl_t->NewInstance());
  GlesFactory::self_ = Persistent<Object>::New(Gles_t->NewInstance());

  //Set the root_path for opening shader files with
  //relative paths
  //take path from executable
  char* pch = strrchr(argv[0], '/');
  int last_index = pch - argv[0] +1;
  char* tmp_exec_path = new char[last_index +1];
  strncpy(tmp_exec_path, argv[0], last_index);
  tmp_exec_path[last_index] = '\0';

  //take relative path from javascript file
  char* p1ch = strrchr(argv[1], '/');
  int last_index1 = p1ch - argv[1] +1;
  char* tmp_js_path = new char[last_index1 +1];
  strncpy(tmp_js_path, argv[1], last_index1);
  tmp_js_path[last_index1] = '\0';

  GlesFactory::root_path = new char[last_index + last_index1 +1];
  strcpy(GlesFactory::root_path, tmp_exec_path);
  strcat(GlesFactory::root_path, tmp_js_path);

  //GlesFactory::root_path = new char[3];
  //strcpy(GlesFactory::root_path,"./");

  delete[] tmp_exec_path;
  delete[] tmp_js_path;

  //exports->Set(JS_STR("GL"), Gl->GetFunction());
  //exports->Set(JS_STR("Glut"), ftGlut->GetFunction());

  //exports->Set(JS_STR("Gl"), ftGl->GetFunction());
  //exports->Set(JS_STR("Gles"), ftGles->GetFunction());
  //exports->Set(JS_STR("Glut"), ftGlut->GetFunction());
  //exports->Set(JS_STR("Glut"), Glut);
}

//jsGL();

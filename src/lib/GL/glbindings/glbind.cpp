
#include "glbind.h"

#if defined(V8_GL_USE_GLEW)
#include "GL/glew.h"
#elif defined(__APPLE__)
#include <GLUT/glut.h>
#else
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#endif

using namespace v8;

Persistent<Object> GlFactory::self_;


void GLglAccumCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glAccum((GLenum) arg0, (GLfloat) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglAlphaFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glAlphaFunc((GLenum) arg0, (GLclampf) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglAreTexturesResidentCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLuint* arg1 = new  GLuint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLuint aux = ( GLuint)arg->Uint32Value();
      arg1[j] = aux; 
  }
    
    
    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLboolean* arg2 = new GLboolean[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLboolean aux = (GLboolean)arg->Uint32Value();
      arg2[j] = aux; 
  }
    
    
  //make call
  args.GetReturnValue().Set(glAreTexturesResident((GLsizei) arg0, (const GLuint*) arg1, (GLboolean*) arg2));
}




void GLglArrayElementCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glArrayElement((GLint) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglBeginCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glBegin((GLenum) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglBindTextureCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  unsigned int arg1 = args[1]->Uint32Value();

  //make call
  glBindTexture((GLenum) arg0, (GLuint) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglBitmapCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 7) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();
  double arg4 = args[4]->NumberValue();
  double arg5 = args[5]->NumberValue();

    
  Handle<Array> arrHandle6 = Handle<Array>::Cast(args[6]);
   GLubyte* arg6 = new  GLubyte[arrHandle6->Length()];
  for (unsigned j = 0; j < arrHandle6->Length(); j++) {
      Handle<Value> arg(arrHandle6->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLubyte aux = ( GLubyte)arg->Uint32Value();
      arg6[j] = aux; 
  }
    
    
  //make call
  glBitmap((GLsizei) arg0, (GLsizei) arg1, (GLfloat) arg2, (GLfloat) arg3, (GLfloat) arg4, (GLfloat) arg5, (const GLubyte*) arg6);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglBlendColorCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();

  //make call
  glBlendColor((GLclampf) arg0, (GLclampf) arg1, (GLclampf) arg2, (GLclampf) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglBlendEquationCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glBlendEquation((GLenum) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglBlendEquationSeparateCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glBlendEquationSeparate((GLenum) arg0, (GLenum) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglBlendFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glBlendFunc((GLenum) arg0, (GLenum) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglCallListCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  glCallList((GLuint) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglClearCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  glClear((GLbitfield) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglClearAccumCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();

  //make call
  glClearAccum((GLfloat) arg0, (GLfloat) arg1, (GLfloat) arg2, (GLfloat) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglClearColorCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();

  //make call
  glClearColor((GLclampf) arg0, (GLclampf) arg1, (GLclampf) arg2, (GLclampf) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglClearDepthCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();

  //make call
  glClearDepth((GLclampd) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglClearIndexCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();

  //make call
  glClearIndex((GLfloat) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglClearStencilCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glClearStencil((GLint) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglClipPlaneCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLdouble* arg1 = new  GLdouble[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glClipPlane((GLenum) arg0, (const GLdouble*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor3bCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glColor3b((GLbyte) arg0, (GLbyte) arg1, (GLbyte) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor3bvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLbyte* arg0 = new  GLbyte[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLbyte aux = ( GLbyte)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glColor3bv((const GLbyte*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor3dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glColor3d((GLdouble) arg0, (GLdouble) arg1, (GLdouble) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor3dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glColor3dv((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor3fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glColor3f((GLfloat) arg0, (GLfloat) arg1, (GLfloat) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor3fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glColor3fv((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor3iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glColor3i((GLint) arg0, (GLint) arg1, (GLint) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor3ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLint* arg0 = new  GLint[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glColor3iv((const GLint*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor3sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glColor3s((GLshort) arg0, (GLshort) arg1, (GLshort) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor3svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLshort* arg0 = new  GLshort[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glColor3sv((const GLshort*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor3ubCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  unsigned int arg1 = args[1]->Uint32Value();
  unsigned int arg2 = args[2]->Uint32Value();

  //make call
  glColor3ub((GLubyte) arg0, (GLubyte) arg1, (GLubyte) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor3ubvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLubyte* arg0 = new  GLubyte[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLubyte aux = ( GLubyte)arg->Uint32Value();
      arg0[j] = aux; 
  }
    
    
  //make call
  glColor3ubv((const GLubyte*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor3uiCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  unsigned int arg1 = args[1]->Uint32Value();
  unsigned int arg2 = args[2]->Uint32Value();

  //make call
  glColor3ui((GLuint) arg0, (GLuint) arg1, (GLuint) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor3uivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLuint* arg0 = new  GLuint[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLuint aux = ( GLuint)arg->Uint32Value();
      arg0[j] = aux; 
  }
    
    
  //make call
  glColor3uiv((const GLuint*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor3usCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  unsigned int arg1 = args[1]->Uint32Value();
  unsigned int arg2 = args[2]->Uint32Value();

  //make call
  glColor3us((GLushort) arg0, (GLushort) arg1, (GLushort) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor3usvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLushort* arg0 = new  GLushort[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLushort aux = ( GLushort)arg->Uint32Value();
      arg0[j] = aux; 
  }
    
    
  //make call
  glColor3usv((const GLushort*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor4bCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glColor4b((GLbyte) arg0, (GLbyte) arg1, (GLbyte) arg2, (GLbyte) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor4bvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLbyte* arg0 = new  GLbyte[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLbyte aux = ( GLbyte)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glColor4bv((const GLbyte*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor4dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();

  //make call
  glColor4d((GLdouble) arg0, (GLdouble) arg1, (GLdouble) arg2, (GLdouble) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor4dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glColor4dv((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor4fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();

  //make call
  glColor4f((GLfloat) arg0, (GLfloat) arg1, (GLfloat) arg2, (GLfloat) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor4fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glColor4fv((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor4iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glColor4i((GLint) arg0, (GLint) arg1, (GLint) arg2, (GLint) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor4ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLint* arg0 = new  GLint[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glColor4iv((const GLint*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor4sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glColor4s((GLshort) arg0, (GLshort) arg1, (GLshort) arg2, (GLshort) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor4svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLshort* arg0 = new  GLshort[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glColor4sv((const GLshort*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor4ubCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  unsigned int arg1 = args[1]->Uint32Value();
  unsigned int arg2 = args[2]->Uint32Value();
  unsigned int arg3 = args[3]->Uint32Value();

  //make call
  glColor4ub((GLubyte) arg0, (GLubyte) arg1, (GLubyte) arg2, (GLubyte) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor4ubvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLubyte* arg0 = new  GLubyte[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLubyte aux = ( GLubyte)arg->Uint32Value();
      arg0[j] = aux; 
  }
    
    
  //make call
  glColor4ubv((const GLubyte*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor4uiCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  unsigned int arg1 = args[1]->Uint32Value();
  unsigned int arg2 = args[2]->Uint32Value();
  unsigned int arg3 = args[3]->Uint32Value();

  //make call
  glColor4ui((GLuint) arg0, (GLuint) arg1, (GLuint) arg2, (GLuint) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor4uivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLuint* arg0 = new  GLuint[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLuint aux = ( GLuint)arg->Uint32Value();
      arg0[j] = aux; 
  }
    
    
  //make call
  glColor4uiv((const GLuint*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor4usCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  unsigned int arg1 = args[1]->Uint32Value();
  unsigned int arg2 = args[2]->Uint32Value();
  unsigned int arg3 = args[3]->Uint32Value();

  //make call
  glColor4us((GLushort) arg0, (GLushort) arg1, (GLushort) arg2, (GLushort) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColor4usvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLushort* arg0 = new  GLushort[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLushort aux = ( GLushort)arg->Uint32Value();
      arg0[j] = aux; 
  }
    
    
  //make call
  glColor4usv((const GLushort*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColorMaskCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  unsigned int arg1 = args[1]->Uint32Value();
  unsigned int arg2 = args[2]->Uint32Value();
  unsigned int arg3 = args[3]->Uint32Value();

  //make call
  glColorMask((GLboolean) arg0, (GLboolean) arg1, (GLboolean) arg2, (GLboolean) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColorMaterialCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glColorMaterial((GLenum) arg0, (GLenum) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColorTableParameterfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLfloat* arg2 = new  GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glColorTableParameterfv((GLenum) arg0, (GLenum) arg1, (const GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglColorTableParameterivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLint* arg2 = new  GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glColorTableParameteriv((GLenum) arg0, (GLenum) arg1, (const GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglConvolutionParameterfCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glConvolutionParameterf((GLenum) arg0, (GLenum) arg1, (GLfloat) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglConvolutionParameterfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLfloat* arg2 = new  GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glConvolutionParameterfv((GLenum) arg0, (GLenum) arg1, (const GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglConvolutionParameteriCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glConvolutionParameteri((GLenum) arg0, (GLenum) arg1, (GLint) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglConvolutionParameterivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLint* arg2 = new  GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glConvolutionParameteriv((GLenum) arg0, (GLenum) arg1, (const GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglCopyColorSubTableCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 5) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();
  int arg4 = args[4]->IntegerValue();

  //make call
  glCopyColorSubTable((GLenum) arg0, (GLsizei) arg1, (GLint) arg2, (GLint) arg3, (GLsizei) arg4);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglCopyColorTableCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 5) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();
  int arg4 = args[4]->IntegerValue();

  //make call
  glCopyColorTable((GLenum) arg0, (GLenum) arg1, (GLint) arg2, (GLint) arg3, (GLsizei) arg4);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglCopyConvolutionFilter1DCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 5) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();
  int arg4 = args[4]->IntegerValue();

  //make call
  glCopyConvolutionFilter1D((GLenum) arg0, (GLenum) arg1, (GLint) arg2, (GLint) arg3, (GLsizei) arg4);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglCopyConvolutionFilter2DCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 6) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();
  int arg4 = args[4]->IntegerValue();
  int arg5 = args[5]->IntegerValue();

  //make call
  glCopyConvolutionFilter2D((GLenum) arg0, (GLenum) arg1, (GLint) arg2, (GLint) arg3, (GLsizei) arg4, (GLsizei) arg5);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglCopyPixelsCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 5) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();
  int arg4 = args[4]->IntegerValue();

  //make call
  glCopyPixels((GLint) arg0, (GLint) arg1, (GLsizei) arg2, (GLsizei) arg3, (GLenum) arg4);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglCopyTexImage1DCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 7) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();
  int arg4 = args[4]->IntegerValue();
  int arg5 = args[5]->IntegerValue();
  int arg6 = args[6]->IntegerValue();

  //make call
  glCopyTexImage1D((GLenum) arg0, (GLint) arg1, (GLenum) arg2, (GLint) arg3, (GLint) arg4, (GLsizei) arg5, (GLint) arg6);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglCopyTexImage2DCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 8) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();
  int arg4 = args[4]->IntegerValue();
  int arg5 = args[5]->IntegerValue();
  int arg6 = args[6]->IntegerValue();
  int arg7 = args[7]->IntegerValue();

  //make call
  glCopyTexImage2D((GLenum) arg0, (GLint) arg1, (GLenum) arg2, (GLint) arg3, (GLint) arg4, (GLsizei) arg5, (GLsizei) arg6, (GLint) arg7);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglCopyTexSubImage1DCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 6) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();
  int arg4 = args[4]->IntegerValue();
  int arg5 = args[5]->IntegerValue();

  //make call
  glCopyTexSubImage1D((GLenum) arg0, (GLint) arg1, (GLint) arg2, (GLint) arg3, (GLint) arg4, (GLsizei) arg5);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglCopyTexSubImage2DCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 8) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();
  int arg4 = args[4]->IntegerValue();
  int arg5 = args[5]->IntegerValue();
  int arg6 = args[6]->IntegerValue();
  int arg7 = args[7]->IntegerValue();

  //make call
  glCopyTexSubImage2D((GLenum) arg0, (GLint) arg1, (GLint) arg2, (GLint) arg3, (GLint) arg4, (GLint) arg5, (GLsizei) arg6, (GLsizei) arg7);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglCopyTexSubImage3DCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 9) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();
  int arg4 = args[4]->IntegerValue();
  int arg5 = args[5]->IntegerValue();
  int arg6 = args[6]->IntegerValue();
  int arg7 = args[7]->IntegerValue();
  int arg8 = args[8]->IntegerValue();

  //make call
  glCopyTexSubImage3D((GLenum) arg0, (GLint) arg1, (GLint) arg2, (GLint) arg3, (GLint) arg4, (GLint) arg5, (GLint) arg6, (GLsizei) arg7, (GLsizei) arg8);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglCullFaceCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glCullFace((GLenum) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglDeleteListsCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  int arg1 = args[1]->IntegerValue();

  //make call
  glDeleteLists((GLuint) arg0, (GLsizei) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglDeleteTexturesCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLuint* arg1 = new  GLuint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLuint aux = ( GLuint)arg->Uint32Value();
      arg1[j] = aux; 
  }
    
    
  //make call
  glDeleteTextures((GLsizei) arg0, (const GLuint*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglDepthFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glDepthFunc((GLenum) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglDepthMaskCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  glDepthMask((GLboolean) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglDepthRangeCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glDepthRange((GLclampd) arg0, (GLclampd) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglDisableCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glDisable((GLenum) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglDisableClientStateCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glDisableClientState((GLenum) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglDrawArraysCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glDrawArrays((GLenum) arg0, (GLint) arg1, (GLsizei) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglDrawBufferCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glDrawBuffer((GLenum) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglEdgeFlagCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  glEdgeFlag((GLboolean) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglEdgeFlagvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLboolean* arg0 = new  GLboolean[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLboolean aux = ( GLboolean)arg->Uint32Value();
      arg0[j] = aux; 
  }
    
    
  //make call
  glEdgeFlagv((const GLboolean*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglEnableCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glEnable((GLenum) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglEnableClientStateCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glEnableClientState((GLenum) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglEndCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glEnd();
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglEndListCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glEndList();
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglEvalCoord1dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();

  //make call
  glEvalCoord1d((GLdouble) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglEvalCoord1dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glEvalCoord1dv((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglEvalCoord1fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();

  //make call
  glEvalCoord1f((GLfloat) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglEvalCoord1fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glEvalCoord1fv((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglEvalCoord2dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glEvalCoord2d((GLdouble) arg0, (GLdouble) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglEvalCoord2dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glEvalCoord2dv((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglEvalCoord2fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glEvalCoord2f((GLfloat) arg0, (GLfloat) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglEvalCoord2fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glEvalCoord2fv((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglEvalMesh1Callback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glEvalMesh1((GLenum) arg0, (GLint) arg1, (GLint) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglEvalMesh2Callback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 5) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();
  int arg4 = args[4]->IntegerValue();

  //make call
  glEvalMesh2((GLenum) arg0, (GLint) arg1, (GLint) arg2, (GLint) arg3, (GLint) arg4);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglEvalPoint1Callback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glEvalPoint1((GLint) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglEvalPoint2Callback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glEvalPoint2((GLint) arg0, (GLint) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglFeedbackBufferCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLfloat* arg2 = new GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLfloat aux = (GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glFeedbackBuffer((GLsizei) arg0, (GLenum) arg1, (GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglFinishCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glFinish();
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglFlushCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glFlush();
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglFogfCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glFogf((GLenum) arg0, (GLfloat) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglFogfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLfloat* arg1 = new  GLfloat[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glFogfv((GLenum) arg0, (const GLfloat*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglFogiCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glFogi((GLenum) arg0, (GLint) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglFogivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLint* arg1 = new  GLint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glFogiv((GLenum) arg0, (const GLint*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglFrontFaceCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glFrontFace((GLenum) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglFrustumCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 6) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();
  double arg4 = args[4]->NumberValue();
  double arg5 = args[5]->NumberValue();

  //make call
  glFrustum((GLdouble) arg0, (GLdouble) arg1, (GLdouble) arg2, (GLdouble) arg3, (GLdouble) arg4, (GLdouble) arg5);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGenListsCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  args.GetReturnValue().Set(glGenLists((GLsizei) arg0));
}




void GLglGenTexturesCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
  GLuint* arg1 = new GLuint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLuint aux = (GLuint)arg->Uint32Value();
      arg1[j] = aux; 
  }
    
    
  //make call
  glGenTextures((GLsizei) arg0, (GLuint*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetBooleanvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
  GLboolean* arg1 = new GLboolean[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLboolean aux = (GLboolean)arg->Uint32Value();
      arg1[j] = aux; 
  }
    
    
  //make call
  glGetBooleanv((GLenum) arg0, (GLboolean*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetClipPlaneCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
  GLdouble* arg1 = new GLdouble[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLdouble aux = (GLdouble)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glGetClipPlane((GLenum) arg0, (GLdouble*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetColorTableParameterfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLfloat* arg2 = new GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLfloat aux = (GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetColorTableParameterfv((GLenum) arg0, (GLenum) arg1, (GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetColorTableParameterivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLint* arg2 = new GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetColorTableParameteriv((GLenum) arg0, (GLenum) arg1, (GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetConvolutionParameterfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLfloat* arg2 = new GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLfloat aux = (GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetConvolutionParameterfv((GLenum) arg0, (GLenum) arg1, (GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetConvolutionParameterivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLint* arg2 = new GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetConvolutionParameteriv((GLenum) arg0, (GLenum) arg1, (GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetDoublevCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
  GLdouble* arg1 = new GLdouble[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLdouble aux = (GLdouble)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glGetDoublev((GLenum) arg0, (GLdouble*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetErrorCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  args.GetReturnValue().Set(glGetError());
}




void GLglGetFloatvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
  GLfloat* arg1 = new GLfloat[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLfloat aux = (GLfloat)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glGetFloatv((GLenum) arg0, (GLfloat*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetHistogramParameterfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLfloat* arg2 = new GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLfloat aux = (GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetHistogramParameterfv((GLenum) arg0, (GLenum) arg1, (GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetHistogramParameterivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLint* arg2 = new GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetHistogramParameteriv((GLenum) arg0, (GLenum) arg1, (GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetIntegervCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
  GLint* arg1 = new GLint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glGetIntegerv((GLenum) arg0, (GLint*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetLightfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLfloat* arg2 = new GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLfloat aux = (GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetLightfv((GLenum) arg0, (GLenum) arg1, (GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetLightivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLint* arg2 = new GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetLightiv((GLenum) arg0, (GLenum) arg1, (GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetMapdvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLdouble* arg2 = new GLdouble[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLdouble aux = (GLdouble)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetMapdv((GLenum) arg0, (GLenum) arg1, (GLdouble*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetMapfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLfloat* arg2 = new GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLfloat aux = (GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetMapfv((GLenum) arg0, (GLenum) arg1, (GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetMapivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLint* arg2 = new GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetMapiv((GLenum) arg0, (GLenum) arg1, (GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetMaterialfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLfloat* arg2 = new GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLfloat aux = (GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetMaterialfv((GLenum) arg0, (GLenum) arg1, (GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetMaterialivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLint* arg2 = new GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetMaterialiv((GLenum) arg0, (GLenum) arg1, (GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetMinmaxParameterfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLfloat* arg2 = new GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLfloat aux = (GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetMinmaxParameterfv((GLenum) arg0, (GLenum) arg1, (GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetMinmaxParameterivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLint* arg2 = new GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetMinmaxParameteriv((GLenum) arg0, (GLenum) arg1, (GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetPixelMapfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
  GLfloat* arg1 = new GLfloat[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLfloat aux = (GLfloat)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glGetPixelMapfv((GLenum) arg0, (GLfloat*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetPixelMapuivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
  GLuint* arg1 = new GLuint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLuint aux = (GLuint)arg->Uint32Value();
      arg1[j] = aux; 
  }
    
    
  //make call
  glGetPixelMapuiv((GLenum) arg0, (GLuint*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetPixelMapusvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
  GLushort* arg1 = new GLushort[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLushort aux = (GLushort)arg->Uint32Value();
      arg1[j] = aux; 
  }
    
    
  //make call
  glGetPixelMapusv((GLenum) arg0, (GLushort*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetPolygonStippleCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
  GLubyte* arg0 = new GLubyte[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLubyte aux = (GLubyte)arg->Uint32Value();
      arg0[j] = aux; 
  }
    
    
  //make call
  glGetPolygonStipple((GLubyte*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetTexEnvfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLfloat* arg2 = new GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLfloat aux = (GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetTexEnvfv((GLenum) arg0, (GLenum) arg1, (GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetTexEnvivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLint* arg2 = new GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetTexEnviv((GLenum) arg0, (GLenum) arg1, (GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetTexGendvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLdouble* arg2 = new GLdouble[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLdouble aux = (GLdouble)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetTexGendv((GLenum) arg0, (GLenum) arg1, (GLdouble*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetTexGenfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLfloat* arg2 = new GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLfloat aux = (GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetTexGenfv((GLenum) arg0, (GLenum) arg1, (GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetTexGenivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLint* arg2 = new GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetTexGeniv((GLenum) arg0, (GLenum) arg1, (GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetTexLevelParameterfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

    
  Handle<Array> arrHandle3 = Handle<Array>::Cast(args[3]);
  GLfloat* arg3 = new GLfloat[arrHandle3->Length()];
  for (unsigned j = 0; j < arrHandle3->Length(); j++) {
      Handle<Value> arg(arrHandle3->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLfloat aux = (GLfloat)arg->NumberValue();
      arg3[j] = aux; 
  }
    
    
  //make call
  glGetTexLevelParameterfv((GLenum) arg0, (GLint) arg1, (GLenum) arg2, (GLfloat*) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetTexLevelParameterivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

    
  Handle<Array> arrHandle3 = Handle<Array>::Cast(args[3]);
  GLint* arg3 = new GLint[arrHandle3->Length()];
  for (unsigned j = 0; j < arrHandle3->Length(); j++) {
      Handle<Value> arg(arrHandle3->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg3[j] = aux; 
  }
    
    
  //make call
  glGetTexLevelParameteriv((GLenum) arg0, (GLint) arg1, (GLenum) arg2, (GLint*) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetTexParameterfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLfloat* arg2 = new GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLfloat aux = (GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetTexParameterfv((GLenum) arg0, (GLenum) arg1, (GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetTexParameterivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLint* arg2 = new GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetTexParameteriv((GLenum) arg0, (GLenum) arg1, (GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglHintCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glHint((GLenum) arg0, (GLenum) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglHistogramCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  unsigned int arg3 = args[3]->Uint32Value();

  //make call
  glHistogram((GLenum) arg0, (GLsizei) arg1, (GLenum) arg2, (GLboolean) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglIndexMaskCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  glIndexMask((GLuint) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglIndexdCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();

  //make call
  glIndexd((GLdouble) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglIndexdvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glIndexdv((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglIndexfCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();

  //make call
  glIndexf((GLfloat) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglIndexfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glIndexfv((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglIndexiCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glIndexi((GLint) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglIndexivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLint* arg0 = new  GLint[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glIndexiv((const GLint*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglIndexsCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glIndexs((GLshort) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglIndexsvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLshort* arg0 = new  GLshort[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glIndexsv((const GLshort*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglIndexubCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  glIndexub((GLubyte) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglIndexubvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLubyte* arg0 = new  GLubyte[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLubyte aux = ( GLubyte)arg->Uint32Value();
      arg0[j] = aux; 
  }
    
    
  //make call
  glIndexubv((const GLubyte*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglInitNamesCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glInitNames();
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglIsEnabledCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  args.GetReturnValue().Set(glIsEnabled((GLenum) arg0));
}




void GLglIsListCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  args.GetReturnValue().Set(glIsList((GLuint) arg0));
}




void GLglIsTextureCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  args.GetReturnValue().Set(glIsTexture((GLuint) arg0));
}




void GLglLightModelfCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glLightModelf((GLenum) arg0, (GLfloat) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglLightModelfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLfloat* arg1 = new  GLfloat[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glLightModelfv((GLenum) arg0, (const GLfloat*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglLightModeliCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glLightModeli((GLenum) arg0, (GLint) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglLightModelivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLint* arg1 = new  GLint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glLightModeliv((GLenum) arg0, (const GLint*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglLightfCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glLightf((GLenum) arg0, (GLenum) arg1, (GLfloat) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglLightfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLfloat* arg2 = new  GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glLightfv((GLenum) arg0, (GLenum) arg1, (const GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglLightiCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glLighti((GLenum) arg0, (GLenum) arg1, (GLint) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglLightivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLint* arg2 = new  GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glLightiv((GLenum) arg0, (GLenum) arg1, (const GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglLineStippleCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  unsigned int arg1 = args[1]->Uint32Value();

  //make call
  glLineStipple((GLint) arg0, (GLushort) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglLineWidthCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();

  //make call
  glLineWidth((GLfloat) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglListBaseCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  glListBase((GLuint) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglLoadIdentityCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glLoadIdentity();
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglLoadMatrixdCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glLoadMatrixd((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglLoadMatrixfCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glLoadMatrixf((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglLoadNameCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  glLoadName((GLuint) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglLogicOpCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glLogicOp((GLenum) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMap1dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 6) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  int arg3 = args[3]->IntegerValue();
  int arg4 = args[4]->IntegerValue();

    
  Handle<Array> arrHandle5 = Handle<Array>::Cast(args[5]);
   GLdouble* arg5 = new  GLdouble[arrHandle5->Length()];
  for (unsigned j = 0; j < arrHandle5->Length(); j++) {
      Handle<Value> arg(arrHandle5->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg5[j] = aux; 
  }
    
    
  //make call
  glMap1d((GLenum) arg0, (GLdouble) arg1, (GLdouble) arg2, (GLint) arg3, (GLint) arg4, (const GLdouble*) arg5);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMap1fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 6) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  int arg3 = args[3]->IntegerValue();
  int arg4 = args[4]->IntegerValue();

    
  Handle<Array> arrHandle5 = Handle<Array>::Cast(args[5]);
   GLfloat* arg5 = new  GLfloat[arrHandle5->Length()];
  for (unsigned j = 0; j < arrHandle5->Length(); j++) {
      Handle<Value> arg(arrHandle5->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg5[j] = aux; 
  }
    
    
  //make call
  glMap1f((GLenum) arg0, (GLfloat) arg1, (GLfloat) arg2, (GLint) arg3, (GLint) arg4, (const GLfloat*) arg5);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMap2dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 10) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  int arg3 = args[3]->IntegerValue();
  int arg4 = args[4]->IntegerValue();
  double arg5 = args[5]->NumberValue();
  double arg6 = args[6]->NumberValue();
  int arg7 = args[7]->IntegerValue();
  int arg8 = args[8]->IntegerValue();

    
  Handle<Array> arrHandle9 = Handle<Array>::Cast(args[9]);
   GLdouble* arg9 = new  GLdouble[arrHandle9->Length()];
  for (unsigned j = 0; j < arrHandle9->Length(); j++) {
      Handle<Value> arg(arrHandle9->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg9[j] = aux; 
  }
    
    
  //make call
  glMap2d((GLenum) arg0, (GLdouble) arg1, (GLdouble) arg2, (GLint) arg3, (GLint) arg4, (GLdouble) arg5, (GLdouble) arg6, (GLint) arg7, (GLint) arg8, (const GLdouble*) arg9);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMap2fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 10) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  int arg3 = args[3]->IntegerValue();
  int arg4 = args[4]->IntegerValue();
  double arg5 = args[5]->NumberValue();
  double arg6 = args[6]->NumberValue();
  int arg7 = args[7]->IntegerValue();
  int arg8 = args[8]->IntegerValue();

    
  Handle<Array> arrHandle9 = Handle<Array>::Cast(args[9]);
   GLfloat* arg9 = new  GLfloat[arrHandle9->Length()];
  for (unsigned j = 0; j < arrHandle9->Length(); j++) {
      Handle<Value> arg(arrHandle9->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg9[j] = aux; 
  }
    
    
  //make call
  glMap2f((GLenum) arg0, (GLfloat) arg1, (GLfloat) arg2, (GLint) arg3, (GLint) arg4, (GLfloat) arg5, (GLfloat) arg6, (GLint) arg7, (GLint) arg8, (const GLfloat*) arg9);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMapGrid1dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glMapGrid1d((GLint) arg0, (GLdouble) arg1, (GLdouble) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMapGrid1fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glMapGrid1f((GLint) arg0, (GLfloat) arg1, (GLfloat) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMapGrid2dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 6) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  int arg3 = args[3]->IntegerValue();
  double arg4 = args[4]->NumberValue();
  double arg5 = args[5]->NumberValue();

  //make call
  glMapGrid2d((GLint) arg0, (GLdouble) arg1, (GLdouble) arg2, (GLint) arg3, (GLdouble) arg4, (GLdouble) arg5);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMapGrid2fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 6) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  int arg3 = args[3]->IntegerValue();
  double arg4 = args[4]->NumberValue();
  double arg5 = args[5]->NumberValue();

  //make call
  glMapGrid2f((GLint) arg0, (GLfloat) arg1, (GLfloat) arg2, (GLint) arg3, (GLfloat) arg4, (GLfloat) arg5);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMaterialfCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glMaterialf((GLenum) arg0, (GLenum) arg1, (GLfloat) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMaterialfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLfloat* arg2 = new  GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glMaterialfv((GLenum) arg0, (GLenum) arg1, (const GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMaterialiCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glMateriali((GLenum) arg0, (GLenum) arg1, (GLint) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMaterialivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLint* arg2 = new  GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glMaterialiv((GLenum) arg0, (GLenum) arg1, (const GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMatrixModeCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glMatrixMode((GLenum) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMinmaxCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  unsigned int arg2 = args[2]->Uint32Value();

  //make call
  glMinmax((GLenum) arg0, (GLenum) arg1, (GLboolean) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultMatrixdCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glMultMatrixd((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultMatrixfCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glMultMatrixf((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglNewListCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  int arg1 = args[1]->IntegerValue();

  //make call
  glNewList((GLuint) arg0, (GLenum) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglNormal3bCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glNormal3b((GLbyte) arg0, (GLbyte) arg1, (GLbyte) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglNormal3bvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLbyte* arg0 = new  GLbyte[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLbyte aux = ( GLbyte)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glNormal3bv((const GLbyte*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglNormal3dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glNormal3d((GLdouble) arg0, (GLdouble) arg1, (GLdouble) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglNormal3dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glNormal3dv((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglNormal3fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glNormal3f((GLfloat) arg0, (GLfloat) arg1, (GLfloat) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglNormal3fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glNormal3fv((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglNormal3iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glNormal3i((GLint) arg0, (GLint) arg1, (GLint) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglNormal3ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLint* arg0 = new  GLint[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glNormal3iv((const GLint*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglNormal3sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glNormal3s((GLshort) arg0, (GLshort) arg1, (GLshort) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglNormal3svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLshort* arg0 = new  GLshort[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glNormal3sv((const GLshort*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglOrthoCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 6) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();
  double arg4 = args[4]->NumberValue();
  double arg5 = args[5]->NumberValue();

  //make call
  glOrtho((GLdouble) arg0, (GLdouble) arg1, (GLdouble) arg2, (GLdouble) arg3, (GLdouble) arg4, (GLdouble) arg5);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPassThroughCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();

  //make call
  glPassThrough((GLfloat) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPixelMapfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLfloat* arg2 = new  GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glPixelMapfv((GLenum) arg0, (GLint) arg1, (const GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPixelMapuivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLuint* arg2 = new  GLuint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLuint aux = ( GLuint)arg->Uint32Value();
      arg2[j] = aux; 
  }
    
    
  //make call
  glPixelMapuiv((GLenum) arg0, (GLint) arg1, (const GLuint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPixelMapusvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLushort* arg2 = new  GLushort[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLushort aux = ( GLushort)arg->Uint32Value();
      arg2[j] = aux; 
  }
    
    
  //make call
  glPixelMapusv((GLenum) arg0, (GLint) arg1, (const GLushort*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPixelStorefCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glPixelStoref((GLenum) arg0, (GLfloat) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPixelStoreiCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glPixelStorei((GLenum) arg0, (GLint) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPixelTransferfCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glPixelTransferf((GLenum) arg0, (GLfloat) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPixelTransferiCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glPixelTransferi((GLenum) arg0, (GLint) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPixelZoomCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glPixelZoom((GLfloat) arg0, (GLfloat) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPointSizeCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();

  //make call
  glPointSize((GLfloat) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPolygonModeCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glPolygonMode((GLenum) arg0, (GLenum) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPolygonOffsetCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glPolygonOffset((GLfloat) arg0, (GLfloat) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPolygonStippleCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLubyte* arg0 = new  GLubyte[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLubyte aux = ( GLubyte)arg->Uint32Value();
      arg0[j] = aux; 
  }
    
    
  //make call
  glPolygonStipple((const GLubyte*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPopAttribCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glPopAttrib();
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPopClientAttribCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glPopClientAttrib();
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPopMatrixCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glPopMatrix();
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPopNameCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glPopName();
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPrioritizeTexturesCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLuint* arg1 = new  GLuint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLuint aux = ( GLuint)arg->Uint32Value();
      arg1[j] = aux; 
  }
    
    
    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLclampf* arg2 = new  GLclampf[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLclampf aux = ( GLclampf)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glPrioritizeTextures((GLsizei) arg0, (const GLuint*) arg1, (const GLclampf*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPushAttribCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  glPushAttrib((GLbitfield) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPushClientAttribCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  glPushClientAttrib((GLbitfield) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPushMatrixCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glPushMatrix();
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPushNameCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  glPushName((GLuint) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos2dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glRasterPos2d((GLdouble) arg0, (GLdouble) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos2dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glRasterPos2dv((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos2fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glRasterPos2f((GLfloat) arg0, (GLfloat) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos2fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glRasterPos2fv((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos2iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glRasterPos2i((GLint) arg0, (GLint) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos2ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLint* arg0 = new  GLint[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glRasterPos2iv((const GLint*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos2sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glRasterPos2s((GLshort) arg0, (GLshort) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos2svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLshort* arg0 = new  GLshort[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glRasterPos2sv((const GLshort*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos3dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glRasterPos3d((GLdouble) arg0, (GLdouble) arg1, (GLdouble) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos3dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glRasterPos3dv((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos3fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glRasterPos3f((GLfloat) arg0, (GLfloat) arg1, (GLfloat) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos3fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glRasterPos3fv((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos3iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glRasterPos3i((GLint) arg0, (GLint) arg1, (GLint) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos3ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLint* arg0 = new  GLint[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glRasterPos3iv((const GLint*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos3sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glRasterPos3s((GLshort) arg0, (GLshort) arg1, (GLshort) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos3svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLshort* arg0 = new  GLshort[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glRasterPos3sv((const GLshort*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos4dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();

  //make call
  glRasterPos4d((GLdouble) arg0, (GLdouble) arg1, (GLdouble) arg2, (GLdouble) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos4dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glRasterPos4dv((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos4fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();

  //make call
  glRasterPos4f((GLfloat) arg0, (GLfloat) arg1, (GLfloat) arg2, (GLfloat) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos4fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glRasterPos4fv((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos4iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glRasterPos4i((GLint) arg0, (GLint) arg1, (GLint) arg2, (GLint) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos4ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLint* arg0 = new  GLint[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glRasterPos4iv((const GLint*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos4sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glRasterPos4s((GLshort) arg0, (GLshort) arg1, (GLshort) arg2, (GLshort) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRasterPos4svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLshort* arg0 = new  GLshort[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glRasterPos4sv((const GLshort*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglReadBufferCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glReadBuffer((GLenum) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRectdCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();

  //make call
  glRectd((GLdouble) arg0, (GLdouble) arg1, (GLdouble) arg2, (GLdouble) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRectdvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLdouble* arg1 = new  GLdouble[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glRectdv((const GLdouble*) arg0, (const GLdouble*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRectfCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();

  //make call
  glRectf((GLfloat) arg0, (GLfloat) arg1, (GLfloat) arg2, (GLfloat) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRectfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLfloat* arg1 = new  GLfloat[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glRectfv((const GLfloat*) arg0, (const GLfloat*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRectiCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glRecti((GLint) arg0, (GLint) arg1, (GLint) arg2, (GLint) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRectivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLint* arg0 = new  GLint[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLint* arg1 = new  GLint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glRectiv((const GLint*) arg0, (const GLint*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRectsCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glRects((GLshort) arg0, (GLshort) arg1, (GLshort) arg2, (GLshort) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRectsvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLshort* arg0 = new  GLshort[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLshort* arg1 = new  GLshort[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glRectsv((const GLshort*) arg0, (const GLshort*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRenderModeCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  args.GetReturnValue().Set(glRenderMode((GLenum) arg0));
}




void GLglResetHistogramCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glResetHistogram((GLenum) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglResetMinmaxCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glResetMinmax((GLenum) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRotatedCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();

  //make call
  glRotated((GLdouble) arg0, (GLdouble) arg1, (GLdouble) arg2, (GLdouble) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglRotatefCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();

  //make call
  glRotatef((GLfloat) arg0, (GLfloat) arg1, (GLfloat) arg2, (GLfloat) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglScaledCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glScaled((GLdouble) arg0, (GLdouble) arg1, (GLdouble) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglScalefCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glScalef((GLfloat) arg0, (GLfloat) arg1, (GLfloat) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglScissorCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glScissor((GLint) arg0, (GLint) arg1, (GLsizei) arg2, (GLsizei) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglSelectBufferCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
  GLuint* arg1 = new GLuint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLuint aux = (GLuint)arg->Uint32Value();
      arg1[j] = aux; 
  }
    
    
  //make call
  glSelectBuffer((GLsizei) arg0, (GLuint*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglShadeModelCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glShadeModel((GLenum) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglStencilFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  unsigned int arg2 = args[2]->Uint32Value();

  //make call
  glStencilFunc((GLenum) arg0, (GLint) arg1, (GLuint) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglStencilMaskCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  glStencilMask((GLuint) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglStencilOpCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glStencilOp((GLenum) arg0, (GLenum) arg1, (GLenum) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord1dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();

  //make call
  glTexCoord1d((GLdouble) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord1dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glTexCoord1dv((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord1fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();

  //make call
  glTexCoord1f((GLfloat) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord1fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glTexCoord1fv((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord1iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glTexCoord1i((GLint) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord1ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLint* arg0 = new  GLint[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glTexCoord1iv((const GLint*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord1sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glTexCoord1s((GLshort) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord1svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLshort* arg0 = new  GLshort[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glTexCoord1sv((const GLshort*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord2dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glTexCoord2d((GLdouble) arg0, (GLdouble) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord2dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glTexCoord2dv((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord2fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glTexCoord2f((GLfloat) arg0, (GLfloat) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord2fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glTexCoord2fv((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord2iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glTexCoord2i((GLint) arg0, (GLint) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord2ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLint* arg0 = new  GLint[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glTexCoord2iv((const GLint*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord2sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glTexCoord2s((GLshort) arg0, (GLshort) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord2svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLshort* arg0 = new  GLshort[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glTexCoord2sv((const GLshort*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord3dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glTexCoord3d((GLdouble) arg0, (GLdouble) arg1, (GLdouble) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord3dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glTexCoord3dv((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord3fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glTexCoord3f((GLfloat) arg0, (GLfloat) arg1, (GLfloat) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord3fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glTexCoord3fv((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord3iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glTexCoord3i((GLint) arg0, (GLint) arg1, (GLint) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord3ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLint* arg0 = new  GLint[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glTexCoord3iv((const GLint*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord3sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glTexCoord3s((GLshort) arg0, (GLshort) arg1, (GLshort) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord3svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLshort* arg0 = new  GLshort[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glTexCoord3sv((const GLshort*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord4dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();

  //make call
  glTexCoord4d((GLdouble) arg0, (GLdouble) arg1, (GLdouble) arg2, (GLdouble) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord4dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glTexCoord4dv((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord4fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();

  //make call
  glTexCoord4f((GLfloat) arg0, (GLfloat) arg1, (GLfloat) arg2, (GLfloat) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord4fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glTexCoord4fv((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord4iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glTexCoord4i((GLint) arg0, (GLint) arg1, (GLint) arg2, (GLint) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord4ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLint* arg0 = new  GLint[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glTexCoord4iv((const GLint*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord4sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glTexCoord4s((GLshort) arg0, (GLshort) arg1, (GLshort) arg2, (GLshort) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexCoord4svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLshort* arg0 = new  GLshort[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glTexCoord4sv((const GLshort*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexEnvfCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glTexEnvf((GLenum) arg0, (GLenum) arg1, (GLfloat) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexEnvfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLfloat* arg2 = new  GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glTexEnvfv((GLenum) arg0, (GLenum) arg1, (const GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexEnviCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glTexEnvi((GLenum) arg0, (GLenum) arg1, (GLint) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexEnvivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLint* arg2 = new  GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glTexEnviv((GLenum) arg0, (GLenum) arg1, (const GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexGendCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glTexGend((GLenum) arg0, (GLenum) arg1, (GLdouble) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexGendvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLdouble* arg2 = new  GLdouble[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glTexGendv((GLenum) arg0, (GLenum) arg1, (const GLdouble*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexGenfCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glTexGenf((GLenum) arg0, (GLenum) arg1, (GLfloat) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexGenfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLfloat* arg2 = new  GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glTexGenfv((GLenum) arg0, (GLenum) arg1, (const GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexGeniCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glTexGeni((GLenum) arg0, (GLenum) arg1, (GLint) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexGenivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLint* arg2 = new  GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glTexGeniv((GLenum) arg0, (GLenum) arg1, (const GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexParameterfCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glTexParameterf((GLenum) arg0, (GLenum) arg1, (GLfloat) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexParameterfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLfloat* arg2 = new  GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glTexParameterfv((GLenum) arg0, (GLenum) arg1, (const GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexParameteriCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glTexParameteri((GLenum) arg0, (GLenum) arg1, (GLint) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTexParameterivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLint* arg2 = new  GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glTexParameteriv((GLenum) arg0, (GLenum) arg1, (const GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTranslatedCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glTranslated((GLdouble) arg0, (GLdouble) arg1, (GLdouble) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglTranslatefCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glTranslatef((GLfloat) arg0, (GLfloat) arg1, (GLfloat) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex2dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glVertex2d((GLdouble) arg0, (GLdouble) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex2dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glVertex2dv((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex2fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glVertex2f((GLfloat) arg0, (GLfloat) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex2fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glVertex2fv((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex2iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glVertex2i((GLint) arg0, (GLint) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex2ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLint* arg0 = new  GLint[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glVertex2iv((const GLint*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex2sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glVertex2s((GLshort) arg0, (GLshort) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex2svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLshort* arg0 = new  GLshort[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glVertex2sv((const GLshort*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex3dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glVertex3d((GLdouble) arg0, (GLdouble) arg1, (GLdouble) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex3dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glVertex3dv((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex3fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glVertex3f((GLfloat) arg0, (GLfloat) arg1, (GLfloat) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex3fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glVertex3fv((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex3iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glVertex3i((GLint) arg0, (GLint) arg1, (GLint) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex3ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLint* arg0 = new  GLint[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glVertex3iv((const GLint*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex3sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glVertex3s((GLshort) arg0, (GLshort) arg1, (GLshort) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex3svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLshort* arg0 = new  GLshort[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glVertex3sv((const GLshort*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex4dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();

  //make call
  glVertex4d((GLdouble) arg0, (GLdouble) arg1, (GLdouble) arg2, (GLdouble) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex4dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glVertex4dv((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex4fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();

  //make call
  glVertex4f((GLfloat) arg0, (GLfloat) arg1, (GLfloat) arg2, (GLfloat) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex4fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glVertex4fv((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex4iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glVertex4i((GLint) arg0, (GLint) arg1, (GLint) arg2, (GLint) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex4ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLint* arg0 = new  GLint[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glVertex4iv((const GLint*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex4sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glVertex4s((GLshort) arg0, (GLshort) arg1, (GLshort) arg2, (GLshort) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertex4svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLshort* arg0 = new  GLshort[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glVertex4sv((const GLshort*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglViewportCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glViewport((GLint) arg0, (GLint) arg1, (GLsizei) arg2, (GLsizei) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglSampleCoverageCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  unsigned int arg1 = args[1]->Uint32Value();

  //make call
  glSampleCoverage((GLclampf) arg0, (GLboolean) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglLoadTransposeMatrixfCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glLoadTransposeMatrixf((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglLoadTransposeMatrixdCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glLoadTransposeMatrixd((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultTransposeMatrixfCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glMultTransposeMatrixf((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultTransposeMatrixdCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glMultTransposeMatrixd((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglActiveTextureCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glActiveTexture((GLenum) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglClientActiveTextureCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glClientActiveTexture((GLenum) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord1dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glMultiTexCoord1d((GLenum) arg0, (GLdouble) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord1dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLdouble* arg1 = new  GLdouble[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glMultiTexCoord1dv((GLenum) arg0, (const GLdouble*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord1fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glMultiTexCoord1f((GLenum) arg0, (GLfloat) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord1fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLfloat* arg1 = new  GLfloat[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glMultiTexCoord1fv((GLenum) arg0, (const GLfloat*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord1iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glMultiTexCoord1i((GLenum) arg0, (GLint) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord1ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLint* arg1 = new  GLint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glMultiTexCoord1iv((GLenum) arg0, (const GLint*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord1sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glMultiTexCoord1s((GLenum) arg0, (GLshort) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord1svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLshort* arg1 = new  GLshort[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glMultiTexCoord1sv((GLenum) arg0, (const GLshort*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord2dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glMultiTexCoord2d((GLenum) arg0, (GLdouble) arg1, (GLdouble) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord2dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLdouble* arg1 = new  GLdouble[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glMultiTexCoord2dv((GLenum) arg0, (const GLdouble*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord2fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glMultiTexCoord2f((GLenum) arg0, (GLfloat) arg1, (GLfloat) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord2fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLfloat* arg1 = new  GLfloat[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glMultiTexCoord2fv((GLenum) arg0, (const GLfloat*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord2iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glMultiTexCoord2i((GLenum) arg0, (GLint) arg1, (GLint) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord2ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLint* arg1 = new  GLint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glMultiTexCoord2iv((GLenum) arg0, (const GLint*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord2sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glMultiTexCoord2s((GLenum) arg0, (GLshort) arg1, (GLshort) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord2svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLshort* arg1 = new  GLshort[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glMultiTexCoord2sv((GLenum) arg0, (const GLshort*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord3dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();

  //make call
  glMultiTexCoord3d((GLenum) arg0, (GLdouble) arg1, (GLdouble) arg2, (GLdouble) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord3dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLdouble* arg1 = new  GLdouble[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glMultiTexCoord3dv((GLenum) arg0, (const GLdouble*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord3fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();

  //make call
  glMultiTexCoord3f((GLenum) arg0, (GLfloat) arg1, (GLfloat) arg2, (GLfloat) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord3fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLfloat* arg1 = new  GLfloat[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glMultiTexCoord3fv((GLenum) arg0, (const GLfloat*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord3iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glMultiTexCoord3i((GLenum) arg0, (GLint) arg1, (GLint) arg2, (GLint) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord3ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLint* arg1 = new  GLint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glMultiTexCoord3iv((GLenum) arg0, (const GLint*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord3sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glMultiTexCoord3s((GLenum) arg0, (GLshort) arg1, (GLshort) arg2, (GLshort) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord3svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLshort* arg1 = new  GLshort[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glMultiTexCoord3sv((GLenum) arg0, (const GLshort*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord4dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 5) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();
  double arg4 = args[4]->NumberValue();

  //make call
  glMultiTexCoord4d((GLenum) arg0, (GLdouble) arg1, (GLdouble) arg2, (GLdouble) arg3, (GLdouble) arg4);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord4dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLdouble* arg1 = new  GLdouble[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glMultiTexCoord4dv((GLenum) arg0, (const GLdouble*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord4fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 5) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();
  double arg4 = args[4]->NumberValue();

  //make call
  glMultiTexCoord4f((GLenum) arg0, (GLfloat) arg1, (GLfloat) arg2, (GLfloat) arg3, (GLfloat) arg4);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord4fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLfloat* arg1 = new  GLfloat[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glMultiTexCoord4fv((GLenum) arg0, (const GLfloat*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord4ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLint* arg1 = new  GLint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glMultiTexCoord4iv((GLenum) arg0, (const GLint*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord4sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 5) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();
  int arg4 = args[4]->IntegerValue();

  //make call
  glMultiTexCoord4s((GLenum) arg0, (GLshort) arg1, (GLshort) arg2, (GLshort) arg3, (GLshort) arg4);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiTexCoord4svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLshort* arg1 = new  GLshort[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glMultiTexCoord4sv((GLenum) arg0, (const GLshort*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglFogCoordfCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();

  //make call
  glFogCoordf((GLfloat) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglFogCoordfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glFogCoordfv((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglFogCoorddCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();

  //make call
  glFogCoordd((GLdouble) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglSecondaryColor3bCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glSecondaryColor3b((GLbyte) arg0, (GLbyte) arg1, (GLbyte) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglSecondaryColor3bvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLbyte* arg0 = new  GLbyte[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLbyte aux = ( GLbyte)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glSecondaryColor3bv((const GLbyte*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglSecondaryColor3dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glSecondaryColor3d((GLdouble) arg0, (GLdouble) arg1, (GLdouble) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglSecondaryColor3dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glSecondaryColor3dv((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglSecondaryColor3fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glSecondaryColor3f((GLfloat) arg0, (GLfloat) arg1, (GLfloat) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglSecondaryColor3fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glSecondaryColor3fv((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglSecondaryColor3iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glSecondaryColor3i((GLint) arg0, (GLint) arg1, (GLint) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglSecondaryColor3ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLint* arg0 = new  GLint[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glSecondaryColor3iv((const GLint*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglSecondaryColor3sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glSecondaryColor3s((GLshort) arg0, (GLshort) arg1, (GLshort) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglSecondaryColor3svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLshort* arg0 = new  GLshort[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glSecondaryColor3sv((const GLshort*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglSecondaryColor3ubCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  unsigned int arg1 = args[1]->Uint32Value();
  unsigned int arg2 = args[2]->Uint32Value();

  //make call
  glSecondaryColor3ub((GLubyte) arg0, (GLubyte) arg1, (GLubyte) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglSecondaryColor3ubvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLubyte* arg0 = new  GLubyte[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLubyte aux = ( GLubyte)arg->Uint32Value();
      arg0[j] = aux; 
  }
    
    
  //make call
  glSecondaryColor3ubv((const GLubyte*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglSecondaryColor3uiCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  unsigned int arg1 = args[1]->Uint32Value();
  unsigned int arg2 = args[2]->Uint32Value();

  //make call
  glSecondaryColor3ui((GLuint) arg0, (GLuint) arg1, (GLuint) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglSecondaryColor3uivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLuint* arg0 = new  GLuint[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLuint aux = ( GLuint)arg->Uint32Value();
      arg0[j] = aux; 
  }
    
    
  //make call
  glSecondaryColor3uiv((const GLuint*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglSecondaryColor3usCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  unsigned int arg1 = args[1]->Uint32Value();
  unsigned int arg2 = args[2]->Uint32Value();

  //make call
  glSecondaryColor3us((GLushort) arg0, (GLushort) arg1, (GLushort) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglSecondaryColor3usvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLushort* arg0 = new  GLushort[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLushort aux = ( GLushort)arg->Uint32Value();
      arg0[j] = aux; 
  }
    
    
  //make call
  glSecondaryColor3usv((const GLushort*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPointParameterfCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glPointParameterf((GLenum) arg0, (GLfloat) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPointParameterfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
  GLfloat* arg1 = new GLfloat[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLfloat aux = (GLfloat)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glPointParameterfv((GLenum) arg0, (GLfloat*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPointParameteriCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glPointParameteri((GLenum) arg0, (GLint) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglPointParameterivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
  GLint* arg1 = new GLint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glPointParameteriv((GLenum) arg0, (GLint*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglBlendFuncSeparateCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glBlendFuncSeparate((GLenum) arg0, (GLenum) arg1, (GLenum) arg2, (GLenum) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglMultiDrawArraysCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
  GLint* arg1 = new GLint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLsizei* arg2 = new GLsizei[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLsizei aux = (GLsizei)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
      int arg3 = args[3]->IntegerValue();

  //make call
  glMultiDrawArrays((GLenum) arg0, (GLint*) arg1, (GLsizei*) arg2, (GLsizei) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglWindowPos2dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glWindowPos2d((GLdouble) arg0, (GLdouble) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglWindowPos2dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glWindowPos2dv((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglWindowPos2fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glWindowPos2f((GLfloat) arg0, (GLfloat) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglWindowPos2fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glWindowPos2fv((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglWindowPos2iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glWindowPos2i((GLint) arg0, (GLint) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglWindowPos2ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLint* arg0 = new  GLint[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glWindowPos2iv((const GLint*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglWindowPos2sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glWindowPos2s((GLshort) arg0, (GLshort) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglWindowPos2svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLshort* arg0 = new  GLshort[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glWindowPos2sv((const GLshort*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglWindowPos3dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glWindowPos3d((GLdouble) arg0, (GLdouble) arg1, (GLdouble) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglWindowPos3dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLdouble* arg0 = new  GLdouble[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glWindowPos3dv((const GLdouble*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglWindowPos3fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glWindowPos3f((GLfloat) arg0, (GLfloat) arg1, (GLfloat) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglWindowPos3fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLfloat* arg0 = new  GLfloat[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glWindowPos3fv((const GLfloat*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglWindowPos3iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glWindowPos3i((GLint) arg0, (GLint) arg1, (GLint) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglWindowPos3ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLint* arg0 = new  GLint[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glWindowPos3iv((const GLint*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglWindowPos3sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glWindowPos3s((GLshort) arg0, (GLshort) arg1, (GLshort) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglWindowPos3svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

    
  Handle<Array> arrHandle0 = Handle<Array>::Cast(args[0]);
   GLshort* arg0 = new  GLshort[arrHandle0->Length()];
  for (unsigned j = 0; j < arrHandle0->Length(); j++) {
      Handle<Value> arg(arrHandle0->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg0[j] = aux; 
  }
    
    
  //make call
  glWindowPos3sv((const GLshort*) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGenQueriesCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
  GLuint* arg1 = new GLuint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLuint aux = (GLuint)arg->Uint32Value();
      arg1[j] = aux; 
  }
    
    
  //make call
  glGenQueries((GLsizei) arg0, (GLuint*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglDeleteQueriesCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLuint* arg1 = new  GLuint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLuint aux = ( GLuint)arg->Uint32Value();
      arg1[j] = aux; 
  }
    
    
  //make call
  glDeleteQueries((GLsizei) arg0, (const GLuint*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglIsQueryCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  args.GetReturnValue().Set(glIsQuery((GLuint) arg0));
}




void GLglBeginQueryCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  unsigned int arg1 = args[1]->Uint32Value();

  //make call
  glBeginQuery((GLenum) arg0, (GLuint) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglEndQueryCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glEndQuery((GLenum) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetQueryivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLint* arg2 = new GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetQueryiv((GLenum) arg0, (GLenum) arg1, (GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetQueryObjectivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLint* arg2 = new GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetQueryObjectiv((GLuint) arg0, (GLenum) arg1, (GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetQueryObjectuivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLuint* arg2 = new GLuint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLuint aux = (GLuint)arg->Uint32Value();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetQueryObjectuiv((GLuint) arg0, (GLenum) arg1, (GLuint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglBindBufferCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  unsigned int arg1 = args[1]->Uint32Value();

  //make call
  glBindBuffer((GLenum) arg0, (GLuint) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglDeleteBuffersCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLuint* arg1 = new  GLuint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLuint aux = ( GLuint)arg->Uint32Value();
      arg1[j] = aux; 
  }
    
    
  //make call
  glDeleteBuffers((GLsizei) arg0, (const GLuint*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGenBuffersCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
  GLuint* arg1 = new GLuint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLuint aux = (GLuint)arg->Uint32Value();
      arg1[j] = aux; 
  }
    
    
  //make call
  glGenBuffers((GLsizei) arg0, (GLuint*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglIsBufferCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  args.GetReturnValue().Set(glIsBuffer((GLuint) arg0));
}




void GLglUnmapBufferCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  args.GetReturnValue().Set(glUnmapBuffer((GLenum) arg0));
}




void GLglGetBufferParameterivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLint* arg2 = new GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetBufferParameteriv((GLenum) arg0, (GLenum) arg1, (GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglDrawBuffersCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLenum* arg1 = new  GLenum[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLenum aux = ( GLenum)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glDrawBuffers((GLsizei) arg0, (const GLenum*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib1dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  double arg1 = args[1]->NumberValue();

  //make call
  glVertexAttrib1d((GLuint) arg0, (GLdouble) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib1dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLdouble* arg1 = new  GLdouble[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib1dv((GLuint) arg0, (const GLdouble*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib1fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  double arg1 = args[1]->NumberValue();

  //make call
  glVertexAttrib1f((GLuint) arg0, (GLfloat) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib1fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLfloat* arg1 = new  GLfloat[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib1fv((GLuint) arg0, (const GLfloat*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib1sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  int arg1 = args[1]->IntegerValue();

  //make call
  glVertexAttrib1s((GLuint) arg0, (GLshort) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib1svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLshort* arg1 = new  GLshort[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib1sv((GLuint) arg0, (const GLshort*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib2dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glVertexAttrib2d((GLuint) arg0, (GLdouble) arg1, (GLdouble) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib2dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLdouble* arg1 = new  GLdouble[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib2dv((GLuint) arg0, (const GLdouble*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib2fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glVertexAttrib2f((GLuint) arg0, (GLfloat) arg1, (GLfloat) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib2fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLfloat* arg1 = new  GLfloat[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib2fv((GLuint) arg0, (const GLfloat*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib2sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glVertexAttrib2s((GLuint) arg0, (GLshort) arg1, (GLshort) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib2svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLshort* arg1 = new  GLshort[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib2sv((GLuint) arg0, (const GLshort*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib3dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();

  //make call
  glVertexAttrib3d((GLuint) arg0, (GLdouble) arg1, (GLdouble) arg2, (GLdouble) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib3dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLdouble* arg1 = new  GLdouble[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib3dv((GLuint) arg0, (const GLdouble*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib3fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();

  //make call
  glVertexAttrib3f((GLuint) arg0, (GLfloat) arg1, (GLfloat) arg2, (GLfloat) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib3fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLfloat* arg1 = new  GLfloat[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib3fv((GLuint) arg0, (const GLfloat*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib3sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glVertexAttrib3s((GLuint) arg0, (GLshort) arg1, (GLshort) arg2, (GLshort) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib3svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLshort* arg1 = new  GLshort[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib3sv((GLuint) arg0, (const GLshort*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib4NbvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLbyte* arg1 = new  GLbyte[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLbyte aux = ( GLbyte)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib4Nbv((GLuint) arg0, (const GLbyte*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib4NivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLint* arg1 = new  GLint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib4Niv((GLuint) arg0, (const GLint*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib4NsvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLshort* arg1 = new  GLshort[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib4Nsv((GLuint) arg0, (const GLshort*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib4NubCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 5) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  unsigned int arg1 = args[1]->Uint32Value();
  unsigned int arg2 = args[2]->Uint32Value();
  unsigned int arg3 = args[3]->Uint32Value();
  unsigned int arg4 = args[4]->Uint32Value();

  //make call
  glVertexAttrib4Nub((GLuint) arg0, (GLubyte) arg1, (GLubyte) arg2, (GLubyte) arg3, (GLubyte) arg4);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib4NubvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLubyte* arg1 = new  GLubyte[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLubyte aux = ( GLubyte)arg->Uint32Value();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib4Nubv((GLuint) arg0, (const GLubyte*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib4NuivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLuint* arg1 = new  GLuint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLuint aux = ( GLuint)arg->Uint32Value();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib4Nuiv((GLuint) arg0, (const GLuint*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib4NusvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLushort* arg1 = new  GLushort[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLushort aux = ( GLushort)arg->Uint32Value();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib4Nusv((GLuint) arg0, (const GLushort*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib4bvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLbyte* arg1 = new  GLbyte[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLbyte aux = ( GLbyte)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib4bv((GLuint) arg0, (const GLbyte*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib4dCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 5) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();
  double arg4 = args[4]->NumberValue();

  //make call
  glVertexAttrib4d((GLuint) arg0, (GLdouble) arg1, (GLdouble) arg2, (GLdouble) arg3, (GLdouble) arg4);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib4dvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLdouble* arg1 = new  GLdouble[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLdouble aux = ( GLdouble)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib4dv((GLuint) arg0, (const GLdouble*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib4fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 5) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();
  double arg4 = args[4]->NumberValue();

  //make call
  glVertexAttrib4f((GLuint) arg0, (GLfloat) arg1, (GLfloat) arg2, (GLfloat) arg3, (GLfloat) arg4);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib4fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLfloat* arg1 = new  GLfloat[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib4fv((GLuint) arg0, (const GLfloat*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib4ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLint* arg1 = new  GLint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib4iv((GLuint) arg0, (const GLint*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib4sCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 5) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();
  int arg4 = args[4]->IntegerValue();

  //make call
  glVertexAttrib4s((GLuint) arg0, (GLshort) arg1, (GLshort) arg2, (GLshort) arg3, (GLshort) arg4);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib4svCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLshort* arg1 = new  GLshort[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLshort aux = ( GLshort)arg->IntegerValue();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib4sv((GLuint) arg0, (const GLshort*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib4ubvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLubyte* arg1 = new  GLubyte[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLubyte aux = ( GLubyte)arg->Uint32Value();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib4ubv((GLuint) arg0, (const GLubyte*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib4uivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLuint* arg1 = new  GLuint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLuint aux = ( GLuint)arg->Uint32Value();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib4uiv((GLuint) arg0, (const GLuint*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglVertexAttrib4usvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

    
  Handle<Array> arrHandle1 = Handle<Array>::Cast(args[1]);
   GLushort* arg1 = new  GLushort[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLushort aux = ( GLushort)arg->Uint32Value();
      arg1[j] = aux; 
  }
    
    
  //make call
  glVertexAttrib4usv((GLuint) arg0, (const GLushort*) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglEnableVertexAttribArrayCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  glEnableVertexAttribArray((GLuint) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglDisableVertexAttribArrayCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  glDisableVertexAttribArray((GLuint) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetVertexAttribdvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLdouble* arg2 = new GLdouble[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLdouble aux = (GLdouble)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetVertexAttribdv((GLuint) arg0, (GLenum) arg1, (GLdouble*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetVertexAttribfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLfloat* arg2 = new GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLfloat aux = (GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetVertexAttribfv((GLuint) arg0, (GLenum) arg1, (GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetVertexAttribivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLint* arg2 = new GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetVertexAttribiv((GLuint) arg0, (GLenum) arg1, (GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglDeleteShaderCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  glDeleteShader((GLuint) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglDetachShaderCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  unsigned int arg1 = args[1]->Uint32Value();

  //make call
  glDetachShader((GLuint) arg0, (GLuint) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglCreateShaderCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  args.GetReturnValue().Set(glCreateShader((GLenum) arg0));
}




void GLglCompileShaderCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  glCompileShader((GLuint) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglCreateProgramCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  args.GetReturnValue().Set(glCreateProgram());
}




void GLglAttachShaderCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  unsigned int arg1 = args[1]->Uint32Value();

  //make call
  glAttachShader((GLuint) arg0, (GLuint) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglLinkProgramCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  glLinkProgram((GLuint) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUseProgramCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  glUseProgram((GLuint) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglDeleteProgramCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  glDeleteProgram((GLuint) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglValidateProgramCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  glValidateProgram((GLuint) arg0);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniform1fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();

  //make call
  glUniform1f((GLint) arg0, (GLfloat) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniform2fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();

  //make call
  glUniform2f((GLint) arg0, (GLfloat) arg1, (GLfloat) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniform3fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();

  //make call
  glUniform3f((GLint) arg0, (GLfloat) arg1, (GLfloat) arg2, (GLfloat) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniform4fCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 5) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();
  double arg4 = args[4]->NumberValue();

  //make call
  glUniform4f((GLint) arg0, (GLfloat) arg1, (GLfloat) arg2, (GLfloat) arg3, (GLfloat) arg4);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniform1iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glUniform1i((GLint) arg0, (GLint) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniform2iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glUniform2i((GLint) arg0, (GLint) arg1, (GLint) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniform3iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glUniform3i((GLint) arg0, (GLint) arg1, (GLint) arg2, (GLint) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniform4iCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 5) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();
  int arg4 = args[4]->IntegerValue();

  //make call
  glUniform4i((GLint) arg0, (GLint) arg1, (GLint) arg2, (GLint) arg3, (GLint) arg4);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniform1fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLfloat* arg2 = new  GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glUniform1fv((GLint) arg0, (GLsizei) arg1, (const GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniform2fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLfloat* arg2 = new  GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glUniform2fv((GLint) arg0, (GLsizei) arg1, (const GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniform3fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLfloat* arg2 = new  GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glUniform3fv((GLint) arg0, (GLsizei) arg1, (const GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniform4fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLfloat* arg2 = new  GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glUniform4fv((GLint) arg0, (GLsizei) arg1, (const GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniform1ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLint* arg2 = new  GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glUniform1iv((GLint) arg0, (GLsizei) arg1, (const GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniform2ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLint* arg2 = new  GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glUniform2iv((GLint) arg0, (GLsizei) arg1, (const GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniform3ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLint* arg2 = new  GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glUniform3iv((GLint) arg0, (GLsizei) arg1, (const GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniform4ivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLint* arg2 = new  GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glUniform4iv((GLint) arg0, (GLsizei) arg1, (const GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniformMatrix2fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  unsigned int arg2 = args[2]->Uint32Value();

    
  Handle<Array> arrHandle3 = Handle<Array>::Cast(args[3]);
   GLfloat* arg3 = new  GLfloat[arrHandle3->Length()];
  for (unsigned j = 0; j < arrHandle3->Length(); j++) {
      Handle<Value> arg(arrHandle3->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg3[j] = aux; 
  }
    
    
  //make call
  glUniformMatrix2fv((GLint) arg0, (GLsizei) arg1, (GLboolean) arg2, (const GLfloat*) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniformMatrix3fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  unsigned int arg2 = args[2]->Uint32Value();

    
  Handle<Array> arrHandle3 = Handle<Array>::Cast(args[3]);
   GLfloat* arg3 = new  GLfloat[arrHandle3->Length()];
  for (unsigned j = 0; j < arrHandle3->Length(); j++) {
      Handle<Value> arg(arrHandle3->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg3[j] = aux; 
  }
    
    
  //make call
  glUniformMatrix3fv((GLint) arg0, (GLsizei) arg1, (GLboolean) arg2, (const GLfloat*) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniformMatrix4fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  unsigned int arg2 = args[2]->Uint32Value();

    
  Handle<Array> arrHandle3 = Handle<Array>::Cast(args[3]);
   GLfloat* arg3 = new  GLfloat[arrHandle3->Length()];
  for (unsigned j = 0; j < arrHandle3->Length(); j++) {
      Handle<Value> arg(arrHandle3->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg3[j] = aux; 
  }
    
    
  //make call
  glUniformMatrix4fv((GLint) arg0, (GLsizei) arg1, (GLboolean) arg2, (const GLfloat*) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglIsShaderCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  args.GetReturnValue().Set(glIsShader((GLuint) arg0));
}




void GLglIsProgramCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  args.GetReturnValue().Set(glIsProgram((GLuint) arg0));
}




void GLglGetShaderivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLint* arg2 = new GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetShaderiv((GLuint) arg0, (GLenum) arg1, (GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetProgramivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLint* arg2 = new GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetProgramiv((GLuint) arg0, (GLenum) arg1, (GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetAttachedShadersCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLsizei* arg2 = new GLsizei[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLsizei aux = (GLsizei)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
    
  Handle<Array> arrHandle3 = Handle<Array>::Cast(args[3]);
  GLuint* arg3 = new GLuint[arrHandle3->Length()];
  for (unsigned j = 0; j < arrHandle3->Length(); j++) {
      Handle<Value> arg(arrHandle3->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLuint aux = (GLuint)arg->Uint32Value();
      arg3[j] = aux; 
  }
    
    
  //make call
  glGetAttachedShaders((GLuint) arg0, (GLsizei) arg1, (GLsizei*) arg2, (GLuint*) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetUniformfvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLfloat* arg2 = new GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLfloat aux = (GLfloat)arg->NumberValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetUniformfv((GLuint) arg0, (GLint) arg1, (GLfloat*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglGetUniformivCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  int arg1 = args[1]->IntegerValue();

    
  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
  GLint* arg2 = new GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg2[j] = aux; 
  }
    
    
  //make call
  glGetUniformiv((GLuint) arg0, (GLint) arg1, (GLint*) arg2);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglStencilFuncSeparateCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  unsigned int arg3 = args[3]->Uint32Value();

  //make call
  glStencilFuncSeparate((GLenum) arg0, (GLenum) arg1, (GLint) arg2, (GLuint) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglStencilOpSeparateCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glStencilOpSeparate((GLenum) arg0, (GLenum) arg1, (GLenum) arg2, (GLenum) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglStencilMaskSeparateCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  unsigned int arg1 = args[1]->Uint32Value();

  //make call
  glStencilMaskSeparate((GLenum) arg0, (GLuint) arg1);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniformMatrix2x3fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  unsigned int arg2 = args[2]->Uint32Value();

    
  Handle<Array> arrHandle3 = Handle<Array>::Cast(args[3]);
   GLfloat* arg3 = new  GLfloat[arrHandle3->Length()];
  for (unsigned j = 0; j < arrHandle3->Length(); j++) {
      Handle<Value> arg(arrHandle3->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg3[j] = aux; 
  }
    
    
  //make call
  glUniformMatrix2x3fv((GLint) arg0, (GLsizei) arg1, (GLboolean) arg2, (const GLfloat*) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniformMatrix3x2fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  unsigned int arg2 = args[2]->Uint32Value();

    
  Handle<Array> arrHandle3 = Handle<Array>::Cast(args[3]);
   GLfloat* arg3 = new  GLfloat[arrHandle3->Length()];
  for (unsigned j = 0; j < arrHandle3->Length(); j++) {
      Handle<Value> arg(arrHandle3->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg3[j] = aux; 
  }
    
    
  //make call
  glUniformMatrix3x2fv((GLint) arg0, (GLsizei) arg1, (GLboolean) arg2, (const GLfloat*) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniformMatrix2x4fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  unsigned int arg2 = args[2]->Uint32Value();

    
  Handle<Array> arrHandle3 = Handle<Array>::Cast(args[3]);
   GLfloat* arg3 = new  GLfloat[arrHandle3->Length()];
  for (unsigned j = 0; j < arrHandle3->Length(); j++) {
      Handle<Value> arg(arrHandle3->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg3[j] = aux; 
  }
    
    
  //make call
  glUniformMatrix2x4fv((GLint) arg0, (GLsizei) arg1, (GLboolean) arg2, (const GLfloat*) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniformMatrix4x2fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  unsigned int arg2 = args[2]->Uint32Value();

    
  Handle<Array> arrHandle3 = Handle<Array>::Cast(args[3]);
   GLfloat* arg3 = new  GLfloat[arrHandle3->Length()];
  for (unsigned j = 0; j < arrHandle3->Length(); j++) {
      Handle<Value> arg(arrHandle3->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg3[j] = aux; 
  }
    
    
  //make call
  glUniformMatrix4x2fv((GLint) arg0, (GLsizei) arg1, (GLboolean) arg2, (const GLfloat*) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniformMatrix3x4fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  unsigned int arg2 = args[2]->Uint32Value();

    
  Handle<Array> arrHandle3 = Handle<Array>::Cast(args[3]);
   GLfloat* arg3 = new  GLfloat[arrHandle3->Length()];
  for (unsigned j = 0; j < arrHandle3->Length(); j++) {
      Handle<Value> arg(arrHandle3->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg3[j] = aux; 
  }
    
    
  //make call
  glUniformMatrix3x4fv((GLint) arg0, (GLsizei) arg1, (GLboolean) arg2, (const GLfloat*) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




void GLglUniformMatrix4x3fvCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  unsigned int arg2 = args[2]->Uint32Value();

    
  Handle<Array> arrHandle3 = Handle<Array>::Cast(args[3]);
   GLfloat* arg3 = new  GLfloat[arrHandle3->Length()];
  for (unsigned j = 0; j < arrHandle3->Length(); j++) {
      Handle<Value> arg(arrHandle3->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg3[j] = aux; 
  }
    
    
  //make call
  glUniformMatrix4x3fv((GLint) arg0, (GLsizei) arg1, (GLboolean) arg2, (const GLfloat*) arg3);
  Local<Object> res = Local<Object>::New(v8::Isolate::GetCurrent(), GlFactory::self_);
  args.GetReturnValue().Set(res);
}




Handle<ObjectTemplate> GlFactory::createGl(void) {
      Handle<ObjectTemplate> Gl = ObjectTemplate::New(v8::Isolate::GetCurrent());
      
      Gl->SetInternalFieldCount(1);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LOGIC_OP"), Uint32::New(v8::Isolate::GetCurrent(), GL_LOGIC_OP), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_COMPONENTS"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_COMPONENTS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERSION_1_1"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERSION_1_1), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERSION_1_2"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERSION_1_2), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERSION_1_3"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERSION_1_3), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERSION_1_4"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERSION_1_4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERSION_1_5"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERSION_1_5), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERSION_2_0"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERSION_2_0), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERSION_2_1"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERSION_2_1), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ACCUM"), Uint32::New(v8::Isolate::GetCurrent(), GL_ACCUM), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LOAD"), Uint32::New(v8::Isolate::GetCurrent(), GL_LOAD), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RETURN"), Uint32::New(v8::Isolate::GetCurrent(), GL_RETURN), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MULT"), Uint32::New(v8::Isolate::GetCurrent(), GL_MULT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ADD"), Uint32::New(v8::Isolate::GetCurrent(), GL_ADD), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NEVER"), Uint32::New(v8::Isolate::GetCurrent(), GL_NEVER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LESS"), Uint32::New(v8::Isolate::GetCurrent(), GL_LESS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EQUAL"), Uint32::New(v8::Isolate::GetCurrent(), GL_EQUAL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LEQUAL"), Uint32::New(v8::Isolate::GetCurrent(), GL_LEQUAL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GREATER"), Uint32::New(v8::Isolate::GetCurrent(), GL_GREATER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NOTEQUAL"), Uint32::New(v8::Isolate::GetCurrent(), GL_NOTEQUAL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GEQUAL"), Uint32::New(v8::Isolate::GetCurrent(), GL_GEQUAL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ALWAYS"), Uint32::New(v8::Isolate::GetCurrent(), GL_ALWAYS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURRENT_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_CURRENT_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POINT_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_POINT_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINE_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINE_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POLYGON_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_POLYGON_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POLYGON_STIPPLE_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_POLYGON_STIPPLE_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_MODE_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_MODE_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LIGHTING_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_LIGHTING_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_BUFFER_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_BUFFER_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ACCUM_BUFFER_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_ACCUM_BUFFER_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_BUFFER_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_BUFFER_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VIEWPORT_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_VIEWPORT_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TRANSFORM_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_TRANSFORM_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ENABLE_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_ENABLE_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_BUFFER_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_BUFFER_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "HINT_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_HINT_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EVAL_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_EVAL_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LIST_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_LIST_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SCISSOR_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_SCISSOR_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ALL_ATTRIB_BITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_ALL_ATTRIB_BITS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POINTS"), Uint32::New(v8::Isolate::GetCurrent(), GL_POINTS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINES"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINES), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINE_LOOP"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINE_LOOP), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINE_STRIP"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINE_STRIP), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TRIANGLES"), Uint32::New(v8::Isolate::GetCurrent(), GL_TRIANGLES), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TRIANGLE_STRIP"), Uint32::New(v8::Isolate::GetCurrent(), GL_TRIANGLE_STRIP), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TRIANGLE_FAN"), Uint32::New(v8::Isolate::GetCurrent(), GL_TRIANGLE_FAN), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "QUADS"), Uint32::New(v8::Isolate::GetCurrent(), GL_QUADS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "QUAD_STRIP"), Uint32::New(v8::Isolate::GetCurrent(), GL_QUAD_STRIP), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POLYGON"), Uint32::New(v8::Isolate::GetCurrent(), GL_POLYGON), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ZERO"), Uint32::New(v8::Isolate::GetCurrent(), GL_ZERO), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ONE"), Uint32::New(v8::Isolate::GetCurrent(), GL_ONE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SRC_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_SRC_COLOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ONE_MINUS_SRC_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_ONE_MINUS_SRC_COLOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SRC_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_SRC_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ONE_MINUS_SRC_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_ONE_MINUS_SRC_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DST_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_DST_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ONE_MINUS_DST_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_ONE_MINUS_DST_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DST_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_DST_COLOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ONE_MINUS_DST_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_ONE_MINUS_DST_COLOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SRC_ALPHA_SATURATE"), Uint32::New(v8::Isolate::GetCurrent(), GL_SRC_ALPHA_SATURATE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TRUE"), Uint32::New(v8::Isolate::GetCurrent(), GL_TRUE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FALSE"), Uint32::New(v8::Isolate::GetCurrent(), GL_FALSE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CLIP_PLANE0"), Uint32::New(v8::Isolate::GetCurrent(), GL_CLIP_PLANE0), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CLIP_PLANE1"), Uint32::New(v8::Isolate::GetCurrent(), GL_CLIP_PLANE1), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CLIP_PLANE2"), Uint32::New(v8::Isolate::GetCurrent(), GL_CLIP_PLANE2), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CLIP_PLANE3"), Uint32::New(v8::Isolate::GetCurrent(), GL_CLIP_PLANE3), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CLIP_PLANE4"), Uint32::New(v8::Isolate::GetCurrent(), GL_CLIP_PLANE4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CLIP_PLANE5"), Uint32::New(v8::Isolate::GetCurrent(), GL_CLIP_PLANE5), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BYTE"), Uint32::New(v8::Isolate::GetCurrent(), GL_BYTE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNSIGNED_BYTE"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNSIGNED_BYTE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SHORT"), Uint32::New(v8::Isolate::GetCurrent(), GL_SHORT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNSIGNED_SHORT"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNSIGNED_SHORT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INT"), Uint32::New(v8::Isolate::GetCurrent(), GL_INT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNSIGNED_INT"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNSIGNED_INT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FLOAT"), Uint32::New(v8::Isolate::GetCurrent(), GL_FLOAT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "2_BYTES"), Uint32::New(v8::Isolate::GetCurrent(), GL_2_BYTES), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "3_BYTES"), Uint32::New(v8::Isolate::GetCurrent(), GL_3_BYTES), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "4_BYTES"), Uint32::New(v8::Isolate::GetCurrent(), GL_4_BYTES), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DOUBLE"), Uint32::New(v8::Isolate::GetCurrent(), GL_DOUBLE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NONE"), Uint32::New(v8::Isolate::GetCurrent(), GL_NONE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FRONT_LEFT"), Uint32::New(v8::Isolate::GetCurrent(), GL_FRONT_LEFT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FRONT_RIGHT"), Uint32::New(v8::Isolate::GetCurrent(), GL_FRONT_RIGHT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BACK_LEFT"), Uint32::New(v8::Isolate::GetCurrent(), GL_BACK_LEFT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BACK_RIGHT"), Uint32::New(v8::Isolate::GetCurrent(), GL_BACK_RIGHT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FRONT"), Uint32::New(v8::Isolate::GetCurrent(), GL_FRONT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BACK"), Uint32::New(v8::Isolate::GetCurrent(), GL_BACK), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LEFT"), Uint32::New(v8::Isolate::GetCurrent(), GL_LEFT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RIGHT"), Uint32::New(v8::Isolate::GetCurrent(), GL_RIGHT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FRONT_AND_BACK"), Uint32::New(v8::Isolate::GetCurrent(), GL_FRONT_AND_BACK), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "AUX0"), Uint32::New(v8::Isolate::GetCurrent(), GL_AUX0), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "AUX1"), Uint32::New(v8::Isolate::GetCurrent(), GL_AUX1), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "AUX2"), Uint32::New(v8::Isolate::GetCurrent(), GL_AUX2), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "AUX3"), Uint32::New(v8::Isolate::GetCurrent(), GL_AUX3), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NO_ERROR"), Uint32::New(v8::Isolate::GetCurrent(), GL_NO_ERROR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INVALID_ENUM"), Uint32::New(v8::Isolate::GetCurrent(), GL_INVALID_ENUM), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INVALID_VALUE"), Uint32::New(v8::Isolate::GetCurrent(), GL_INVALID_VALUE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STACK_OVERFLOW"), Uint32::New(v8::Isolate::GetCurrent(), GL_STACK_OVERFLOW), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STACK_UNDERFLOW"), Uint32::New(v8::Isolate::GetCurrent(), GL_STACK_UNDERFLOW), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "OUT_OF_MEMORY"), Uint32::New(v8::Isolate::GetCurrent(), GL_OUT_OF_MEMORY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "2D"), Uint32::New(v8::Isolate::GetCurrent(), GL_2D), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "3D"), Uint32::New(v8::Isolate::GetCurrent(), GL_3D), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "3D_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_3D_COLOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "3D_COLOR_TEXTURE"), Uint32::New(v8::Isolate::GetCurrent(), GL_3D_COLOR_TEXTURE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "4D_COLOR_TEXTURE"), Uint32::New(v8::Isolate::GetCurrent(), GL_4D_COLOR_TEXTURE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PASS_THROUGH_TOKEN"), Uint32::New(v8::Isolate::GetCurrent(), GL_PASS_THROUGH_TOKEN), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POINT_TOKEN"), Uint32::New(v8::Isolate::GetCurrent(), GL_POINT_TOKEN), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINE_TOKEN"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINE_TOKEN), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POLYGON_TOKEN"), Uint32::New(v8::Isolate::GetCurrent(), GL_POLYGON_TOKEN), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BITMAP_TOKEN"), Uint32::New(v8::Isolate::GetCurrent(), GL_BITMAP_TOKEN), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DRAW_PIXEL_TOKEN"), Uint32::New(v8::Isolate::GetCurrent(), GL_DRAW_PIXEL_TOKEN), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COPY_PIXEL_TOKEN"), Uint32::New(v8::Isolate::GetCurrent(), GL_COPY_PIXEL_TOKEN), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINE_RESET_TOKEN"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINE_RESET_TOKEN), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EXP"), Uint32::New(v8::Isolate::GetCurrent(), GL_EXP), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EXP2"), Uint32::New(v8::Isolate::GetCurrent(), GL_EXP2), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CW"), Uint32::New(v8::Isolate::GetCurrent(), GL_CW), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CCW"), Uint32::New(v8::Isolate::GetCurrent(), GL_CCW), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COEFF"), Uint32::New(v8::Isolate::GetCurrent(), GL_COEFF), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ORDER"), Uint32::New(v8::Isolate::GetCurrent(), GL_ORDER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DOMAIN"), Uint32::New(v8::Isolate::GetCurrent(), GL_DOMAIN), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURRENT_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_CURRENT_COLOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURRENT_INDEX"), Uint32::New(v8::Isolate::GetCurrent(), GL_CURRENT_INDEX), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURRENT_NORMAL"), Uint32::New(v8::Isolate::GetCurrent(), GL_CURRENT_NORMAL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURRENT_TEXTURE_COORDS"), Uint32::New(v8::Isolate::GetCurrent(), GL_CURRENT_TEXTURE_COORDS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURRENT_RASTER_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_CURRENT_RASTER_COLOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURRENT_RASTER_INDEX"), Uint32::New(v8::Isolate::GetCurrent(), GL_CURRENT_RASTER_INDEX), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURRENT_RASTER_TEXTURE_COORDS"), Uint32::New(v8::Isolate::GetCurrent(), GL_CURRENT_RASTER_TEXTURE_COORDS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURRENT_RASTER_POSITION"), Uint32::New(v8::Isolate::GetCurrent(), GL_CURRENT_RASTER_POSITION), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURRENT_RASTER_POSITION_VALID"), Uint32::New(v8::Isolate::GetCurrent(), GL_CURRENT_RASTER_POSITION_VALID), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURRENT_RASTER_DISTANCE"), Uint32::New(v8::Isolate::GetCurrent(), GL_CURRENT_RASTER_DISTANCE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POINT_SMOOTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_POINT_SMOOTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POINT_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_POINT_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POINT_SIZE_RANGE"), Uint32::New(v8::Isolate::GetCurrent(), GL_POINT_SIZE_RANGE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POINT_SIZE_GRANULARITY"), Uint32::New(v8::Isolate::GetCurrent(), GL_POINT_SIZE_GRANULARITY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINE_SMOOTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINE_SMOOTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINE_WIDTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINE_WIDTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINE_WIDTH_RANGE"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINE_WIDTH_RANGE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINE_WIDTH_GRANULARITY"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINE_WIDTH_GRANULARITY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINE_STIPPLE"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINE_STIPPLE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINE_STIPPLE_PATTERN"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINE_STIPPLE_PATTERN), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINE_STIPPLE_REPEAT"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINE_STIPPLE_REPEAT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LIST_MODE"), Uint32::New(v8::Isolate::GetCurrent(), GL_LIST_MODE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_LIST_NESTING"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_LIST_NESTING), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LIST_BASE"), Uint32::New(v8::Isolate::GetCurrent(), GL_LIST_BASE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LIST_INDEX"), Uint32::New(v8::Isolate::GetCurrent(), GL_LIST_INDEX), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POLYGON_MODE"), Uint32::New(v8::Isolate::GetCurrent(), GL_POLYGON_MODE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POLYGON_SMOOTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_POLYGON_SMOOTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POLYGON_STIPPLE"), Uint32::New(v8::Isolate::GetCurrent(), GL_POLYGON_STIPPLE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EDGE_FLAG"), Uint32::New(v8::Isolate::GetCurrent(), GL_EDGE_FLAG), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CULL_FACE"), Uint32::New(v8::Isolate::GetCurrent(), GL_CULL_FACE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CULL_FACE_MODE"), Uint32::New(v8::Isolate::GetCurrent(), GL_CULL_FACE_MODE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FRONT_FACE"), Uint32::New(v8::Isolate::GetCurrent(), GL_FRONT_FACE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LIGHTING"), Uint32::New(v8::Isolate::GetCurrent(), GL_LIGHTING), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LIGHT_MODEL_LOCAL_VIEWER"), Uint32::New(v8::Isolate::GetCurrent(), GL_LIGHT_MODEL_LOCAL_VIEWER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LIGHT_MODEL_TWO_SIDE"), Uint32::New(v8::Isolate::GetCurrent(), GL_LIGHT_MODEL_TWO_SIDE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LIGHT_MODEL_AMBIENT"), Uint32::New(v8::Isolate::GetCurrent(), GL_LIGHT_MODEL_AMBIENT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SHADE_MODEL"), Uint32::New(v8::Isolate::GetCurrent(), GL_SHADE_MODEL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_MATERIAL_FACE"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_MATERIAL_FACE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_MATERIAL_PARAMETER"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_MATERIAL_PARAMETER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_MATERIAL"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_MATERIAL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG_INDEX"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG_INDEX), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG_DENSITY"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG_DENSITY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG_START"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG_START), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG_END"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG_END), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG_MODE"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG_MODE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG_COLOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_RANGE"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_RANGE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_TEST"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_TEST), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_WRITEMASK"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_WRITEMASK), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_CLEAR_VALUE"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_CLEAR_VALUE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_FUNC"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_FUNC), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ACCUM_CLEAR_VALUE"), Uint32::New(v8::Isolate::GetCurrent(), GL_ACCUM_CLEAR_VALUE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_TEST"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_TEST), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_CLEAR_VALUE"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_CLEAR_VALUE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_FUNC"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_FUNC), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_VALUE_MASK"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_VALUE_MASK), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_FAIL"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_FAIL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_PASS_DEPTH_FAIL"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_PASS_DEPTH_FAIL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_PASS_DEPTH_PASS"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_PASS_DEPTH_PASS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_REF"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_REF), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_WRITEMASK"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_WRITEMASK), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MATRIX_MODE"), Uint32::New(v8::Isolate::GetCurrent(), GL_MATRIX_MODE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NORMALIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_NORMALIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VIEWPORT"), Uint32::New(v8::Isolate::GetCurrent(), GL_VIEWPORT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MODELVIEW_STACK_DEPTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_MODELVIEW_STACK_DEPTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PROJECTION_STACK_DEPTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_PROJECTION_STACK_DEPTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_STACK_DEPTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_STACK_DEPTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MODELVIEW_MATRIX"), Uint32::New(v8::Isolate::GetCurrent(), GL_MODELVIEW_MATRIX), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PROJECTION_MATRIX"), Uint32::New(v8::Isolate::GetCurrent(), GL_PROJECTION_MATRIX), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_MATRIX"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_MATRIX), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ATTRIB_STACK_DEPTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_ATTRIB_STACK_DEPTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CLIENT_ATTRIB_STACK_DEPTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_CLIENT_ATTRIB_STACK_DEPTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ALPHA_TEST"), Uint32::New(v8::Isolate::GetCurrent(), GL_ALPHA_TEST), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ALPHA_TEST_FUNC"), Uint32::New(v8::Isolate::GetCurrent(), GL_ALPHA_TEST_FUNC), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ALPHA_TEST_REF"), Uint32::New(v8::Isolate::GetCurrent(), GL_ALPHA_TEST_REF), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DITHER"), Uint32::New(v8::Isolate::GetCurrent(), GL_DITHER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLEND_DST"), Uint32::New(v8::Isolate::GetCurrent(), GL_BLEND_DST), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLEND_SRC"), Uint32::New(v8::Isolate::GetCurrent(), GL_BLEND_SRC), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLEND"), Uint32::New(v8::Isolate::GetCurrent(), GL_BLEND), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LOGIC_OP_MODE"), Uint32::New(v8::Isolate::GetCurrent(), GL_LOGIC_OP_MODE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INDEX_LOGIC_OP"), Uint32::New(v8::Isolate::GetCurrent(), GL_INDEX_LOGIC_OP), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_LOGIC_OP"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_LOGIC_OP), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "AUX_BUFFERS"), Uint32::New(v8::Isolate::GetCurrent(), GL_AUX_BUFFERS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DRAW_BUFFER"), Uint32::New(v8::Isolate::GetCurrent(), GL_DRAW_BUFFER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "READ_BUFFER"), Uint32::New(v8::Isolate::GetCurrent(), GL_READ_BUFFER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SCISSOR_BOX"), Uint32::New(v8::Isolate::GetCurrent(), GL_SCISSOR_BOX), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SCISSOR_TEST"), Uint32::New(v8::Isolate::GetCurrent(), GL_SCISSOR_TEST), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INDEX_CLEAR_VALUE"), Uint32::New(v8::Isolate::GetCurrent(), GL_INDEX_CLEAR_VALUE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INDEX_WRITEMASK"), Uint32::New(v8::Isolate::GetCurrent(), GL_INDEX_WRITEMASK), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_CLEAR_VALUE"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_CLEAR_VALUE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_WRITEMASK"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_WRITEMASK), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INDEX_MODE"), Uint32::New(v8::Isolate::GetCurrent(), GL_INDEX_MODE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGBA_MODE"), Uint32::New(v8::Isolate::GetCurrent(), GL_RGBA_MODE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DOUBLEBUFFER"), Uint32::New(v8::Isolate::GetCurrent(), GL_DOUBLEBUFFER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STEREO"), Uint32::New(v8::Isolate::GetCurrent(), GL_STEREO), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RENDER_MODE"), Uint32::New(v8::Isolate::GetCurrent(), GL_RENDER_MODE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PERSPECTIVE_CORRECTION_HINT"), Uint32::New(v8::Isolate::GetCurrent(), GL_PERSPECTIVE_CORRECTION_HINT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POINT_SMOOTH_HINT"), Uint32::New(v8::Isolate::GetCurrent(), GL_POINT_SMOOTH_HINT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINE_SMOOTH_HINT"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINE_SMOOTH_HINT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POLYGON_SMOOTH_HINT"), Uint32::New(v8::Isolate::GetCurrent(), GL_POLYGON_SMOOTH_HINT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG_HINT"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG_HINT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_GEN_S"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_GEN_S), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_GEN_T"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_GEN_T), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_GEN_R"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_GEN_R), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_GEN_Q"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_GEN_Q), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_MAP_I_TO_I"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_MAP_I_TO_I), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_MAP_S_TO_S"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_MAP_S_TO_S), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_MAP_I_TO_R"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_MAP_I_TO_R), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_MAP_I_TO_G"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_MAP_I_TO_G), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_MAP_I_TO_B"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_MAP_I_TO_B), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_MAP_I_TO_A"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_MAP_I_TO_A), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_MAP_R_TO_R"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_MAP_R_TO_R), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_MAP_G_TO_G"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_MAP_G_TO_G), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_MAP_B_TO_B"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_MAP_B_TO_B), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_MAP_A_TO_A"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_MAP_A_TO_A), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_MAP_I_TO_I_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_MAP_I_TO_I_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_MAP_S_TO_S_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_MAP_S_TO_S_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_MAP_I_TO_R_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_MAP_I_TO_R_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_MAP_I_TO_G_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_MAP_I_TO_G_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_MAP_I_TO_B_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_MAP_I_TO_B_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_MAP_I_TO_A_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_MAP_I_TO_A_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_MAP_R_TO_R_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_MAP_R_TO_R_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_MAP_G_TO_G_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_MAP_G_TO_G_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_MAP_B_TO_B_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_MAP_B_TO_B_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_MAP_A_TO_A_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_MAP_A_TO_A_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNPACK_SWAP_BYTES"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNPACK_SWAP_BYTES), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNPACK_LSB_FIRST"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNPACK_LSB_FIRST), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNPACK_ROW_LENGTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNPACK_ROW_LENGTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNPACK_SKIP_ROWS"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNPACK_SKIP_ROWS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNPACK_SKIP_PIXELS"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNPACK_SKIP_PIXELS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNPACK_ALIGNMENT"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNPACK_ALIGNMENT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PACK_SWAP_BYTES"), Uint32::New(v8::Isolate::GetCurrent(), GL_PACK_SWAP_BYTES), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PACK_LSB_FIRST"), Uint32::New(v8::Isolate::GetCurrent(), GL_PACK_LSB_FIRST), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PACK_ROW_LENGTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_PACK_ROW_LENGTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PACK_SKIP_ROWS"), Uint32::New(v8::Isolate::GetCurrent(), GL_PACK_SKIP_ROWS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PACK_SKIP_PIXELS"), Uint32::New(v8::Isolate::GetCurrent(), GL_PACK_SKIP_PIXELS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PACK_ALIGNMENT"), Uint32::New(v8::Isolate::GetCurrent(), GL_PACK_ALIGNMENT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP_COLOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP_STENCIL"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP_STENCIL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INDEX_SHIFT"), Uint32::New(v8::Isolate::GetCurrent(), GL_INDEX_SHIFT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INDEX_OFFSET"), Uint32::New(v8::Isolate::GetCurrent(), GL_INDEX_OFFSET), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RED_SCALE"), Uint32::New(v8::Isolate::GetCurrent(), GL_RED_SCALE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RED_BIAS"), Uint32::New(v8::Isolate::GetCurrent(), GL_RED_BIAS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ZOOM_X"), Uint32::New(v8::Isolate::GetCurrent(), GL_ZOOM_X), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ZOOM_Y"), Uint32::New(v8::Isolate::GetCurrent(), GL_ZOOM_Y), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GREEN_SCALE"), Uint32::New(v8::Isolate::GetCurrent(), GL_GREEN_SCALE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GREEN_BIAS"), Uint32::New(v8::Isolate::GetCurrent(), GL_GREEN_BIAS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLUE_SCALE"), Uint32::New(v8::Isolate::GetCurrent(), GL_BLUE_SCALE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLUE_BIAS"), Uint32::New(v8::Isolate::GetCurrent(), GL_BLUE_BIAS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ALPHA_SCALE"), Uint32::New(v8::Isolate::GetCurrent(), GL_ALPHA_SCALE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ALPHA_BIAS"), Uint32::New(v8::Isolate::GetCurrent(), GL_ALPHA_BIAS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_SCALE"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_SCALE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_BIAS"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_BIAS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_EVAL_ORDER"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_EVAL_ORDER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_LIGHTS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_LIGHTS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_CLIP_PLANES"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_CLIP_PLANES), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_TEXTURE_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_TEXTURE_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_PIXEL_MAP_TABLE"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_PIXEL_MAP_TABLE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_ATTRIB_STACK_DEPTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_ATTRIB_STACK_DEPTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_MODELVIEW_STACK_DEPTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_MODELVIEW_STACK_DEPTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_NAME_STACK_DEPTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_NAME_STACK_DEPTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_PROJECTION_STACK_DEPTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_PROJECTION_STACK_DEPTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_TEXTURE_STACK_DEPTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_TEXTURE_STACK_DEPTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_VIEWPORT_DIMS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_VIEWPORT_DIMS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_CLIENT_ATTRIB_STACK_DEPTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_CLIENT_ATTRIB_STACK_DEPTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SUBPIXEL_BITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_SUBPIXEL_BITS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INDEX_BITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_INDEX_BITS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RED_BITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_RED_BITS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GREEN_BITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_GREEN_BITS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLUE_BITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_BLUE_BITS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ALPHA_BITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_ALPHA_BITS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_BITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_BITS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_BITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_BITS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ACCUM_RED_BITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_ACCUM_RED_BITS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ACCUM_GREEN_BITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_ACCUM_GREEN_BITS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ACCUM_BLUE_BITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_ACCUM_BLUE_BITS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ACCUM_ALPHA_BITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_ACCUM_ALPHA_BITS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NAME_STACK_DEPTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_NAME_STACK_DEPTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "AUTO_NORMAL"), Uint32::New(v8::Isolate::GetCurrent(), GL_AUTO_NORMAL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP1_COLOR_4"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP1_COLOR_4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP1_INDEX"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP1_INDEX), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP1_NORMAL"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP1_NORMAL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP1_TEXTURE_COORD_1"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP1_TEXTURE_COORD_1), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP1_TEXTURE_COORD_2"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP1_TEXTURE_COORD_2), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP1_TEXTURE_COORD_3"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP1_TEXTURE_COORD_3), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP1_TEXTURE_COORD_4"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP1_TEXTURE_COORD_4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP1_VERTEX_3"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP1_VERTEX_3), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP1_VERTEX_4"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP1_VERTEX_4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP2_COLOR_4"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP2_COLOR_4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP2_INDEX"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP2_INDEX), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP2_NORMAL"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP2_NORMAL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP2_TEXTURE_COORD_1"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP2_TEXTURE_COORD_1), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP2_TEXTURE_COORD_2"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP2_TEXTURE_COORD_2), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP2_TEXTURE_COORD_3"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP2_TEXTURE_COORD_3), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP2_TEXTURE_COORD_4"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP2_TEXTURE_COORD_4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP2_VERTEX_3"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP2_VERTEX_3), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP2_VERTEX_4"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP2_VERTEX_4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP1_GRID_DOMAIN"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP1_GRID_DOMAIN), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP1_GRID_SEGMENTS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP1_GRID_SEGMENTS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP2_GRID_DOMAIN"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP2_GRID_DOMAIN), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAP2_GRID_SEGMENTS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAP2_GRID_SEGMENTS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_1D"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_1D), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_2D"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_2D), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FEEDBACK_BUFFER_POINTER"), Uint32::New(v8::Isolate::GetCurrent(), GL_FEEDBACK_BUFFER_POINTER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FEEDBACK_BUFFER_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_FEEDBACK_BUFFER_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FEEDBACK_BUFFER_TYPE"), Uint32::New(v8::Isolate::GetCurrent(), GL_FEEDBACK_BUFFER_TYPE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SELECTION_BUFFER_POINTER"), Uint32::New(v8::Isolate::GetCurrent(), GL_SELECTION_BUFFER_POINTER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SELECTION_BUFFER_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_SELECTION_BUFFER_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_WIDTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_WIDTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_HEIGHT"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_HEIGHT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_INTERNAL_FORMAT"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_INTERNAL_FORMAT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_BORDER_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_BORDER_COLOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_BORDER"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_BORDER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DONT_CARE"), Uint32::New(v8::Isolate::GetCurrent(), GL_DONT_CARE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FASTEST"), Uint32::New(v8::Isolate::GetCurrent(), GL_FASTEST), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NICEST"), Uint32::New(v8::Isolate::GetCurrent(), GL_NICEST), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LIGHT0"), Uint32::New(v8::Isolate::GetCurrent(), GL_LIGHT0), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LIGHT1"), Uint32::New(v8::Isolate::GetCurrent(), GL_LIGHT1), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LIGHT2"), Uint32::New(v8::Isolate::GetCurrent(), GL_LIGHT2), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LIGHT3"), Uint32::New(v8::Isolate::GetCurrent(), GL_LIGHT3), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LIGHT4"), Uint32::New(v8::Isolate::GetCurrent(), GL_LIGHT4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LIGHT5"), Uint32::New(v8::Isolate::GetCurrent(), GL_LIGHT5), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LIGHT6"), Uint32::New(v8::Isolate::GetCurrent(), GL_LIGHT6), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LIGHT7"), Uint32::New(v8::Isolate::GetCurrent(), GL_LIGHT7), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "AMBIENT"), Uint32::New(v8::Isolate::GetCurrent(), GL_AMBIENT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DIFFUSE"), Uint32::New(v8::Isolate::GetCurrent(), GL_DIFFUSE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SPECULAR"), Uint32::New(v8::Isolate::GetCurrent(), GL_SPECULAR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POSITION"), Uint32::New(v8::Isolate::GetCurrent(), GL_POSITION), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SPOT_DIRECTION"), Uint32::New(v8::Isolate::GetCurrent(), GL_SPOT_DIRECTION), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SPOT_EXPONENT"), Uint32::New(v8::Isolate::GetCurrent(), GL_SPOT_EXPONENT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SPOT_CUTOFF"), Uint32::New(v8::Isolate::GetCurrent(), GL_SPOT_CUTOFF), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COMPILE"), Uint32::New(v8::Isolate::GetCurrent(), GL_COMPILE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COMPILE_AND_EXECUTE"), Uint32::New(v8::Isolate::GetCurrent(), GL_COMPILE_AND_EXECUTE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CLEAR"), Uint32::New(v8::Isolate::GetCurrent(), GL_CLEAR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "AND"), Uint32::New(v8::Isolate::GetCurrent(), GL_AND), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "AND_REVERSE"), Uint32::New(v8::Isolate::GetCurrent(), GL_AND_REVERSE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COPY"), Uint32::New(v8::Isolate::GetCurrent(), GL_COPY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "AND_INVERTED"), Uint32::New(v8::Isolate::GetCurrent(), GL_AND_INVERTED), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NOOP"), Uint32::New(v8::Isolate::GetCurrent(), GL_NOOP), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "XOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_XOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "OR"), Uint32::New(v8::Isolate::GetCurrent(), GL_OR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_NOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EQUIV"), Uint32::New(v8::Isolate::GetCurrent(), GL_EQUIV), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INVERT"), Uint32::New(v8::Isolate::GetCurrent(), GL_INVERT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "OR_REVERSE"), Uint32::New(v8::Isolate::GetCurrent(), GL_OR_REVERSE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COPY_INVERTED"), Uint32::New(v8::Isolate::GetCurrent(), GL_COPY_INVERTED), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "OR_INVERTED"), Uint32::New(v8::Isolate::GetCurrent(), GL_OR_INVERTED), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NAND"), Uint32::New(v8::Isolate::GetCurrent(), GL_NAND), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SET"), Uint32::New(v8::Isolate::GetCurrent(), GL_SET), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EMISSION"), Uint32::New(v8::Isolate::GetCurrent(), GL_EMISSION), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SHININESS"), Uint32::New(v8::Isolate::GetCurrent(), GL_SHININESS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "AMBIENT_AND_DIFFUSE"), Uint32::New(v8::Isolate::GetCurrent(), GL_AMBIENT_AND_DIFFUSE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_INDEXES"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_INDEXES), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MODELVIEW"), Uint32::New(v8::Isolate::GetCurrent(), GL_MODELVIEW), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PROJECTION"), Uint32::New(v8::Isolate::GetCurrent(), GL_PROJECTION), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_INDEX"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_INDEX), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_INDEX"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_INDEX), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_COMPONENT"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_COMPONENT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RED"), Uint32::New(v8::Isolate::GetCurrent(), GL_RED), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GREEN"), Uint32::New(v8::Isolate::GetCurrent(), GL_GREEN), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLUE"), Uint32::New(v8::Isolate::GetCurrent(), GL_BLUE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGB"), Uint32::New(v8::Isolate::GetCurrent(), GL_RGB), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGBA"), Uint32::New(v8::Isolate::GetCurrent(), GL_RGBA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LUMINANCE"), Uint32::New(v8::Isolate::GetCurrent(), GL_LUMINANCE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LUMINANCE_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_LUMINANCE_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BITMAP"), Uint32::New(v8::Isolate::GetCurrent(), GL_BITMAP), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POINT"), Uint32::New(v8::Isolate::GetCurrent(), GL_POINT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINE"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FILL"), Uint32::New(v8::Isolate::GetCurrent(), GL_FILL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RENDER"), Uint32::New(v8::Isolate::GetCurrent(), GL_RENDER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FEEDBACK"), Uint32::New(v8::Isolate::GetCurrent(), GL_FEEDBACK), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SELECT"), Uint32::New(v8::Isolate::GetCurrent(), GL_SELECT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FLAT"), Uint32::New(v8::Isolate::GetCurrent(), GL_FLAT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SMOOTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_SMOOTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEEP"), Uint32::New(v8::Isolate::GetCurrent(), GL_KEEP), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "REPLACE"), Uint32::New(v8::Isolate::GetCurrent(), GL_REPLACE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INCR"), Uint32::New(v8::Isolate::GetCurrent(), GL_INCR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DECR"), Uint32::New(v8::Isolate::GetCurrent(), GL_DECR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VENDOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_VENDOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RENDERER"), Uint32::New(v8::Isolate::GetCurrent(), GL_RENDERER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERSION"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERSION), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EXTENSIONS"), Uint32::New(v8::Isolate::GetCurrent(), GL_EXTENSIONS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "S"), Uint32::New(v8::Isolate::GetCurrent(), GL_S), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "T"), Uint32::New(v8::Isolate::GetCurrent(), GL_T), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "R"), Uint32::New(v8::Isolate::GetCurrent(), GL_R), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Q"), Uint32::New(v8::Isolate::GetCurrent(), GL_Q), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MODULATE"), Uint32::New(v8::Isolate::GetCurrent(), GL_MODULATE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DECAL"), Uint32::New(v8::Isolate::GetCurrent(), GL_DECAL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_ENV_MODE"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_ENV_MODE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_ENV_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_ENV_COLOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_ENV"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_ENV), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EYE_LINEAR"), Uint32::New(v8::Isolate::GetCurrent(), GL_EYE_LINEAR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "OBJECT_LINEAR"), Uint32::New(v8::Isolate::GetCurrent(), GL_OBJECT_LINEAR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SPHERE_MAP"), Uint32::New(v8::Isolate::GetCurrent(), GL_SPHERE_MAP), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_GEN_MODE"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_GEN_MODE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "OBJECT_PLANE"), Uint32::New(v8::Isolate::GetCurrent(), GL_OBJECT_PLANE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EYE_PLANE"), Uint32::New(v8::Isolate::GetCurrent(), GL_EYE_PLANE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NEAREST"), Uint32::New(v8::Isolate::GetCurrent(), GL_NEAREST), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINEAR"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINEAR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NEAREST_MIPMAP_NEAREST"), Uint32::New(v8::Isolate::GetCurrent(), GL_NEAREST_MIPMAP_NEAREST), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINEAR_MIPMAP_NEAREST"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINEAR_MIPMAP_NEAREST), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NEAREST_MIPMAP_LINEAR"), Uint32::New(v8::Isolate::GetCurrent(), GL_NEAREST_MIPMAP_LINEAR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINEAR_MIPMAP_LINEAR"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINEAR_MIPMAP_LINEAR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_MAG_FILTER"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_MAG_FILTER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_MIN_FILTER"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_MIN_FILTER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_WRAP_S"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_WRAP_S), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_WRAP_T"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_WRAP_T), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CLAMP"), Uint32::New(v8::Isolate::GetCurrent(), GL_CLAMP), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "REPEAT"), Uint32::New(v8::Isolate::GetCurrent(), GL_REPEAT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CLIENT_PIXEL_STORE_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_CLIENT_PIXEL_STORE_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CLIENT_VERTEX_ARRAY_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_CLIENT_VERTEX_ARRAY_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CLIENT_ALL_ATTRIB_BITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_CLIENT_ALL_ATTRIB_BITS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POLYGON_OFFSET_FACTOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_POLYGON_OFFSET_FACTOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POLYGON_OFFSET_UNITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_POLYGON_OFFSET_UNITS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POLYGON_OFFSET_POINT"), Uint32::New(v8::Isolate::GetCurrent(), GL_POLYGON_OFFSET_POINT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POLYGON_OFFSET_LINE"), Uint32::New(v8::Isolate::GetCurrent(), GL_POLYGON_OFFSET_LINE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POLYGON_OFFSET_FILL"), Uint32::New(v8::Isolate::GetCurrent(), GL_POLYGON_OFFSET_FILL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ALPHA4"), Uint32::New(v8::Isolate::GetCurrent(), GL_ALPHA4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ALPHA8"), Uint32::New(v8::Isolate::GetCurrent(), GL_ALPHA8), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ALPHA12"), Uint32::New(v8::Isolate::GetCurrent(), GL_ALPHA12), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ALPHA16"), Uint32::New(v8::Isolate::GetCurrent(), GL_ALPHA16), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LUMINANCE4"), Uint32::New(v8::Isolate::GetCurrent(), GL_LUMINANCE4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LUMINANCE8"), Uint32::New(v8::Isolate::GetCurrent(), GL_LUMINANCE8), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LUMINANCE12"), Uint32::New(v8::Isolate::GetCurrent(), GL_LUMINANCE12), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LUMINANCE16"), Uint32::New(v8::Isolate::GetCurrent(), GL_LUMINANCE16), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LUMINANCE4_ALPHA4"), Uint32::New(v8::Isolate::GetCurrent(), GL_LUMINANCE4_ALPHA4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LUMINANCE6_ALPHA2"), Uint32::New(v8::Isolate::GetCurrent(), GL_LUMINANCE6_ALPHA2), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LUMINANCE8_ALPHA8"), Uint32::New(v8::Isolate::GetCurrent(), GL_LUMINANCE8_ALPHA8), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LUMINANCE12_ALPHA4"), Uint32::New(v8::Isolate::GetCurrent(), GL_LUMINANCE12_ALPHA4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LUMINANCE12_ALPHA12"), Uint32::New(v8::Isolate::GetCurrent(), GL_LUMINANCE12_ALPHA12), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LUMINANCE16_ALPHA16"), Uint32::New(v8::Isolate::GetCurrent(), GL_LUMINANCE16_ALPHA16), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INTENSITY"), Uint32::New(v8::Isolate::GetCurrent(), GL_INTENSITY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INTENSITY4"), Uint32::New(v8::Isolate::GetCurrent(), GL_INTENSITY4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INTENSITY8"), Uint32::New(v8::Isolate::GetCurrent(), GL_INTENSITY8), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INTENSITY12"), Uint32::New(v8::Isolate::GetCurrent(), GL_INTENSITY12), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INTENSITY16"), Uint32::New(v8::Isolate::GetCurrent(), GL_INTENSITY16), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "R3_G3_B2"), Uint32::New(v8::Isolate::GetCurrent(), GL_R3_G3_B2), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGB4"), Uint32::New(v8::Isolate::GetCurrent(), GL_RGB4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGB5"), Uint32::New(v8::Isolate::GetCurrent(), GL_RGB5), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGB8"), Uint32::New(v8::Isolate::GetCurrent(), GL_RGB8), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGB10"), Uint32::New(v8::Isolate::GetCurrent(), GL_RGB10), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGB12"), Uint32::New(v8::Isolate::GetCurrent(), GL_RGB12), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGB16"), Uint32::New(v8::Isolate::GetCurrent(), GL_RGB16), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGBA2"), Uint32::New(v8::Isolate::GetCurrent(), GL_RGBA2), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGBA4"), Uint32::New(v8::Isolate::GetCurrent(), GL_RGBA4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGB5_A1"), Uint32::New(v8::Isolate::GetCurrent(), GL_RGB5_A1), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGBA8"), Uint32::New(v8::Isolate::GetCurrent(), GL_RGBA8), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGB10_A2"), Uint32::New(v8::Isolate::GetCurrent(), GL_RGB10_A2), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGBA12"), Uint32::New(v8::Isolate::GetCurrent(), GL_RGBA12), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGBA16"), Uint32::New(v8::Isolate::GetCurrent(), GL_RGBA16), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_RED_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_RED_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_GREEN_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_GREEN_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_BLUE_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_BLUE_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_ALPHA_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_ALPHA_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_LUMINANCE_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_LUMINANCE_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_INTENSITY_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_INTENSITY_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PROXY_TEXTURE_1D"), Uint32::New(v8::Isolate::GetCurrent(), GL_PROXY_TEXTURE_1D), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PROXY_TEXTURE_2D"), Uint32::New(v8::Isolate::GetCurrent(), GL_PROXY_TEXTURE_2D), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_PRIORITY"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_PRIORITY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_RESIDENT"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_RESIDENT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_BINDING_1D"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_BINDING_1D), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_BINDING_2D"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_BINDING_2D), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_BINDING_3D"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_BINDING_3D), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_ARRAY"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_ARRAY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NORMAL_ARRAY"), Uint32::New(v8::Isolate::GetCurrent(), GL_NORMAL_ARRAY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_ARRAY"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_ARRAY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INDEX_ARRAY"), Uint32::New(v8::Isolate::GetCurrent(), GL_INDEX_ARRAY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_COORD_ARRAY"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_COORD_ARRAY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EDGE_FLAG_ARRAY"), Uint32::New(v8::Isolate::GetCurrent(), GL_EDGE_FLAG_ARRAY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_ARRAY_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_ARRAY_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_ARRAY_TYPE"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_ARRAY_TYPE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_ARRAY_STRIDE"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_ARRAY_STRIDE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NORMAL_ARRAY_TYPE"), Uint32::New(v8::Isolate::GetCurrent(), GL_NORMAL_ARRAY_TYPE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NORMAL_ARRAY_STRIDE"), Uint32::New(v8::Isolate::GetCurrent(), GL_NORMAL_ARRAY_STRIDE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_ARRAY_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_ARRAY_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_ARRAY_TYPE"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_ARRAY_TYPE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_ARRAY_STRIDE"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_ARRAY_STRIDE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INDEX_ARRAY_TYPE"), Uint32::New(v8::Isolate::GetCurrent(), GL_INDEX_ARRAY_TYPE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INDEX_ARRAY_STRIDE"), Uint32::New(v8::Isolate::GetCurrent(), GL_INDEX_ARRAY_STRIDE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_COORD_ARRAY_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_COORD_ARRAY_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_COORD_ARRAY_TYPE"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_COORD_ARRAY_TYPE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_COORD_ARRAY_STRIDE"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_COORD_ARRAY_STRIDE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EDGE_FLAG_ARRAY_STRIDE"), Uint32::New(v8::Isolate::GetCurrent(), GL_EDGE_FLAG_ARRAY_STRIDE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_ARRAY_POINTER"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_ARRAY_POINTER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NORMAL_ARRAY_POINTER"), Uint32::New(v8::Isolate::GetCurrent(), GL_NORMAL_ARRAY_POINTER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_ARRAY_POINTER"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_ARRAY_POINTER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INDEX_ARRAY_POINTER"), Uint32::New(v8::Isolate::GetCurrent(), GL_INDEX_ARRAY_POINTER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_COORD_ARRAY_POINTER"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_COORD_ARRAY_POINTER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EDGE_FLAG_ARRAY_POINTER"), Uint32::New(v8::Isolate::GetCurrent(), GL_EDGE_FLAG_ARRAY_POINTER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "V2F"), Uint32::New(v8::Isolate::GetCurrent(), GL_V2F), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "V3F"), Uint32::New(v8::Isolate::GetCurrent(), GL_V3F), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "C4UB_V2F"), Uint32::New(v8::Isolate::GetCurrent(), GL_C4UB_V2F), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "C4UB_V3F"), Uint32::New(v8::Isolate::GetCurrent(), GL_C4UB_V3F), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "C3F_V3F"), Uint32::New(v8::Isolate::GetCurrent(), GL_C3F_V3F), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "N3F_V3F"), Uint32::New(v8::Isolate::GetCurrent(), GL_N3F_V3F), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "C4F_N3F_V3F"), Uint32::New(v8::Isolate::GetCurrent(), GL_C4F_N3F_V3F), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "T2F_V3F"), Uint32::New(v8::Isolate::GetCurrent(), GL_T2F_V3F), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "T4F_V4F"), Uint32::New(v8::Isolate::GetCurrent(), GL_T4F_V4F), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "T2F_C4UB_V3F"), Uint32::New(v8::Isolate::GetCurrent(), GL_T2F_C4UB_V3F), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "T2F_C3F_V3F"), Uint32::New(v8::Isolate::GetCurrent(), GL_T2F_C3F_V3F), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "T2F_N3F_V3F"), Uint32::New(v8::Isolate::GetCurrent(), GL_T2F_N3F_V3F), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "T2F_C4F_N3F_V3F"), Uint32::New(v8::Isolate::GetCurrent(), GL_T2F_C4F_N3F_V3F), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "T4F_C4F_N3F_V4F"), Uint32::New(v8::Isolate::GetCurrent(), GL_T4F_C4F_N3F_V4F), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BGR"), Uint32::New(v8::Isolate::GetCurrent(), GL_BGR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BGRA"), Uint32::New(v8::Isolate::GetCurrent(), GL_BGRA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CONSTANT_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_CONSTANT_COLOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ONE_MINUS_CONSTANT_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_ONE_MINUS_CONSTANT_COLOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CONSTANT_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_CONSTANT_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ONE_MINUS_CONSTANT_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_ONE_MINUS_CONSTANT_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLEND_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_BLEND_COLOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FUNC_ADD"), Uint32::New(v8::Isolate::GetCurrent(), GL_FUNC_ADD), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MIN"), Uint32::New(v8::Isolate::GetCurrent(), GL_MIN), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FUNC_SUBTRACT"), Uint32::New(v8::Isolate::GetCurrent(), GL_FUNC_SUBTRACT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FUNC_REVERSE_SUBTRACT"), Uint32::New(v8::Isolate::GetCurrent(), GL_FUNC_REVERSE_SUBTRACT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_MATRIX"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_MATRIX), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_MATRIX_STACK_DEPTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_MATRIX_STACK_DEPTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_COLOR_MATRIX_STACK_DEPTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_COLOR_MATRIX_STACK_DEPTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POST_COLOR_MATRIX_RED_SCALE"), Uint32::New(v8::Isolate::GetCurrent(), GL_POST_COLOR_MATRIX_RED_SCALE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POST_COLOR_MATRIX_GREEN_SCALE"), Uint32::New(v8::Isolate::GetCurrent(), GL_POST_COLOR_MATRIX_GREEN_SCALE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POST_COLOR_MATRIX_BLUE_SCALE"), Uint32::New(v8::Isolate::GetCurrent(), GL_POST_COLOR_MATRIX_BLUE_SCALE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POST_COLOR_MATRIX_ALPHA_SCALE"), Uint32::New(v8::Isolate::GetCurrent(), GL_POST_COLOR_MATRIX_ALPHA_SCALE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POST_COLOR_MATRIX_RED_BIAS"), Uint32::New(v8::Isolate::GetCurrent(), GL_POST_COLOR_MATRIX_RED_BIAS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POST_COLOR_MATRIX_GREEN_BIAS"), Uint32::New(v8::Isolate::GetCurrent(), GL_POST_COLOR_MATRIX_GREEN_BIAS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POST_COLOR_MATRIX_BLUE_BIAS"), Uint32::New(v8::Isolate::GetCurrent(), GL_POST_COLOR_MATRIX_BLUE_BIAS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POST_COLOR_MATRIX_ALPHA_BIAS"), Uint32::New(v8::Isolate::GetCurrent(), GL_POST_COLOR_MATRIX_ALPHA_BIAS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_TABLE"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_TABLE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POST_CONVOLUTION_COLOR_TABLE"), Uint32::New(v8::Isolate::GetCurrent(), GL_POST_CONVOLUTION_COLOR_TABLE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POST_COLOR_MATRIX_COLOR_TABLE"), Uint32::New(v8::Isolate::GetCurrent(), GL_POST_COLOR_MATRIX_COLOR_TABLE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PROXY_COLOR_TABLE"), Uint32::New(v8::Isolate::GetCurrent(), GL_PROXY_COLOR_TABLE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PROXY_POST_CONVOLUTION_COLOR_TABLE"), Uint32::New(v8::Isolate::GetCurrent(), GL_PROXY_POST_CONVOLUTION_COLOR_TABLE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PROXY_POST_COLOR_MATRIX_COLOR_TABLE"), Uint32::New(v8::Isolate::GetCurrent(), GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_TABLE_SCALE"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_TABLE_SCALE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_TABLE_BIAS"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_TABLE_BIAS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_TABLE_FORMAT"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_TABLE_FORMAT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_TABLE_WIDTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_TABLE_WIDTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_TABLE_RED_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_TABLE_RED_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_TABLE_GREEN_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_TABLE_GREEN_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_TABLE_BLUE_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_TABLE_BLUE_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_TABLE_ALPHA_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_TABLE_ALPHA_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_TABLE_LUMINANCE_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_TABLE_LUMINANCE_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_TABLE_INTENSITY_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_TABLE_INTENSITY_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CONVOLUTION_1D"), Uint32::New(v8::Isolate::GetCurrent(), GL_CONVOLUTION_1D), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CONVOLUTION_2D"), Uint32::New(v8::Isolate::GetCurrent(), GL_CONVOLUTION_2D), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SEPARABLE_2D"), Uint32::New(v8::Isolate::GetCurrent(), GL_SEPARABLE_2D), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CONVOLUTION_BORDER_MODE"), Uint32::New(v8::Isolate::GetCurrent(), GL_CONVOLUTION_BORDER_MODE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CONVOLUTION_FILTER_SCALE"), Uint32::New(v8::Isolate::GetCurrent(), GL_CONVOLUTION_FILTER_SCALE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CONVOLUTION_FILTER_BIAS"), Uint32::New(v8::Isolate::GetCurrent(), GL_CONVOLUTION_FILTER_BIAS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "REDUCE"), Uint32::New(v8::Isolate::GetCurrent(), GL_REDUCE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CONVOLUTION_FORMAT"), Uint32::New(v8::Isolate::GetCurrent(), GL_CONVOLUTION_FORMAT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CONVOLUTION_WIDTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_CONVOLUTION_WIDTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CONVOLUTION_HEIGHT"), Uint32::New(v8::Isolate::GetCurrent(), GL_CONVOLUTION_HEIGHT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_CONVOLUTION_WIDTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_CONVOLUTION_WIDTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_CONVOLUTION_HEIGHT"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_CONVOLUTION_HEIGHT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POST_CONVOLUTION_RED_SCALE"), Uint32::New(v8::Isolate::GetCurrent(), GL_POST_CONVOLUTION_RED_SCALE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POST_CONVOLUTION_GREEN_SCALE"), Uint32::New(v8::Isolate::GetCurrent(), GL_POST_CONVOLUTION_GREEN_SCALE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POST_CONVOLUTION_BLUE_SCALE"), Uint32::New(v8::Isolate::GetCurrent(), GL_POST_CONVOLUTION_BLUE_SCALE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POST_CONVOLUTION_ALPHA_SCALE"), Uint32::New(v8::Isolate::GetCurrent(), GL_POST_CONVOLUTION_ALPHA_SCALE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POST_CONVOLUTION_RED_BIAS"), Uint32::New(v8::Isolate::GetCurrent(), GL_POST_CONVOLUTION_RED_BIAS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POST_CONVOLUTION_GREEN_BIAS"), Uint32::New(v8::Isolate::GetCurrent(), GL_POST_CONVOLUTION_GREEN_BIAS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POST_CONVOLUTION_BLUE_BIAS"), Uint32::New(v8::Isolate::GetCurrent(), GL_POST_CONVOLUTION_BLUE_BIAS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POST_CONVOLUTION_ALPHA_BIAS"), Uint32::New(v8::Isolate::GetCurrent(), GL_POST_CONVOLUTION_ALPHA_BIAS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CONSTANT_BORDER"), Uint32::New(v8::Isolate::GetCurrent(), GL_CONSTANT_BORDER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "REPLICATE_BORDER"), Uint32::New(v8::Isolate::GetCurrent(), GL_REPLICATE_BORDER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CONVOLUTION_BORDER_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_CONVOLUTION_BORDER_COLOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_ELEMENTS_VERTICES"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_ELEMENTS_VERTICES), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_ELEMENTS_INDICES"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_ELEMENTS_INDICES), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "HISTOGRAM"), Uint32::New(v8::Isolate::GetCurrent(), GL_HISTOGRAM), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PROXY_HISTOGRAM"), Uint32::New(v8::Isolate::GetCurrent(), GL_PROXY_HISTOGRAM), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "HISTOGRAM_WIDTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_HISTOGRAM_WIDTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "HISTOGRAM_FORMAT"), Uint32::New(v8::Isolate::GetCurrent(), GL_HISTOGRAM_FORMAT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "HISTOGRAM_RED_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_HISTOGRAM_RED_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "HISTOGRAM_GREEN_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_HISTOGRAM_GREEN_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "HISTOGRAM_BLUE_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_HISTOGRAM_BLUE_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "HISTOGRAM_ALPHA_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_HISTOGRAM_ALPHA_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "HISTOGRAM_LUMINANCE_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_HISTOGRAM_LUMINANCE_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "HISTOGRAM_SINK"), Uint32::New(v8::Isolate::GetCurrent(), GL_HISTOGRAM_SINK), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MINMAX"), Uint32::New(v8::Isolate::GetCurrent(), GL_MINMAX), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MINMAX_FORMAT"), Uint32::New(v8::Isolate::GetCurrent(), GL_MINMAX_FORMAT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MINMAX_SINK"), Uint32::New(v8::Isolate::GetCurrent(), GL_MINMAX_SINK), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TABLE_TOO_LARGE"), Uint32::New(v8::Isolate::GetCurrent(), GL_TABLE_TOO_LARGE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNSIGNED_BYTE_3_3_2"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNSIGNED_BYTE_3_3_2), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNSIGNED_SHORT_4_4_4_4"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNSIGNED_SHORT_4_4_4_4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNSIGNED_SHORT_5_5_5_1"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNSIGNED_SHORT_5_5_5_1), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNSIGNED_INT_8_8_8_8"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNSIGNED_INT_8_8_8_8), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNSIGNED_INT_10_10_10_2"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNSIGNED_INT_10_10_10_2), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNSIGNED_BYTE_2_3_3_REV"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNSIGNED_BYTE_2_3_3_REV), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNSIGNED_SHORT_5_6_5"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNSIGNED_SHORT_5_6_5), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNSIGNED_SHORT_5_6_5_REV"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNSIGNED_SHORT_5_6_5_REV), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNSIGNED_SHORT_4_4_4_4_REV"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNSIGNED_SHORT_4_4_4_4_REV), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNSIGNED_SHORT_1_5_5_5_REV"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNSIGNED_SHORT_1_5_5_5_REV), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNSIGNED_INT_8_8_8_8_REV"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNSIGNED_INT_8_8_8_8_REV), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNSIGNED_INT_2_10_10_10_REV"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNSIGNED_INT_2_10_10_10_REV), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RESCALE_NORMAL"), Uint32::New(v8::Isolate::GetCurrent(), GL_RESCALE_NORMAL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LIGHT_MODEL_COLOR_CONTROL"), Uint32::New(v8::Isolate::GetCurrent(), GL_LIGHT_MODEL_COLOR_CONTROL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SINGLE_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_SINGLE_COLOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SEPARATE_SPECULAR_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_SEPARATE_SPECULAR_COLOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PACK_SKIP_IMAGES"), Uint32::New(v8::Isolate::GetCurrent(), GL_PACK_SKIP_IMAGES), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PACK_IMAGE_HEIGHT"), Uint32::New(v8::Isolate::GetCurrent(), GL_PACK_IMAGE_HEIGHT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNPACK_SKIP_IMAGES"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNPACK_SKIP_IMAGES), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNPACK_IMAGE_HEIGHT"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNPACK_IMAGE_HEIGHT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_3D"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_3D), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PROXY_TEXTURE_3D"), Uint32::New(v8::Isolate::GetCurrent(), GL_PROXY_TEXTURE_3D), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_DEPTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_DEPTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_WRAP_R"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_WRAP_R), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_3D_TEXTURE_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_3D_TEXTURE_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CLAMP_TO_EDGE"), Uint32::New(v8::Isolate::GetCurrent(), GL_CLAMP_TO_EDGE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CLAMP_TO_BORDER"), Uint32::New(v8::Isolate::GetCurrent(), GL_CLAMP_TO_BORDER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_MIN_LOD"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_MIN_LOD), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_MAX_LOD"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_MAX_LOD), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_BASE_LEVEL"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_BASE_LEVEL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_MAX_LEVEL"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_MAX_LEVEL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SMOOTH_POINT_SIZE_RANGE"), Uint32::New(v8::Isolate::GetCurrent(), GL_SMOOTH_POINT_SIZE_RANGE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SMOOTH_POINT_SIZE_GRANULARITY"), Uint32::New(v8::Isolate::GetCurrent(), GL_SMOOTH_POINT_SIZE_GRANULARITY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SMOOTH_LINE_WIDTH_RANGE"), Uint32::New(v8::Isolate::GetCurrent(), GL_SMOOTH_LINE_WIDTH_RANGE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SMOOTH_LINE_WIDTH_GRANULARITY"), Uint32::New(v8::Isolate::GetCurrent(), GL_SMOOTH_LINE_WIDTH_GRANULARITY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ALIASED_POINT_SIZE_RANGE"), Uint32::New(v8::Isolate::GetCurrent(), GL_ALIASED_POINT_SIZE_RANGE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ALIASED_LINE_WIDTH_RANGE"), Uint32::New(v8::Isolate::GetCurrent(), GL_ALIASED_LINE_WIDTH_RANGE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE0"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE0), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE1"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE1), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE2"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE2), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE3"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE3), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE4"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE5"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE5), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE6"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE6), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE7"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE7), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE8"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE8), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE9"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE9), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE10"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE10), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE11"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE11), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE12"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE12), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE13"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE13), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE14"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE14), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE15"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE15), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE16"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE16), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE17"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE17), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE18"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE18), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE19"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE19), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE20"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE20), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE21"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE21), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE22"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE22), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE23"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE23), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE24"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE24), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE25"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE25), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE26"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE26), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE27"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE27), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE28"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE28), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE29"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE29), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE30"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE30), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE31"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE31), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ACTIVE_TEXTURE"), Uint32::New(v8::Isolate::GetCurrent(), GL_ACTIVE_TEXTURE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CLIENT_ACTIVE_TEXTURE"), Uint32::New(v8::Isolate::GetCurrent(), GL_CLIENT_ACTIVE_TEXTURE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_TEXTURE_UNITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_TEXTURE_UNITS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COMBINE"), Uint32::New(v8::Isolate::GetCurrent(), GL_COMBINE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COMBINE_RGB"), Uint32::New(v8::Isolate::GetCurrent(), GL_COMBINE_RGB), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COMBINE_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_COMBINE_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGB_SCALE"), Uint32::New(v8::Isolate::GetCurrent(), GL_RGB_SCALE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ADD_SIGNED"), Uint32::New(v8::Isolate::GetCurrent(), GL_ADD_SIGNED), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INTERPOLATE"), Uint32::New(v8::Isolate::GetCurrent(), GL_INTERPOLATE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CONSTANT"), Uint32::New(v8::Isolate::GetCurrent(), GL_CONSTANT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PRIMARY_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_PRIMARY_COLOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PREVIOUS"), Uint32::New(v8::Isolate::GetCurrent(), GL_PREVIOUS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SUBTRACT"), Uint32::New(v8::Isolate::GetCurrent(), GL_SUBTRACT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SRC0_RGB"), Uint32::New(v8::Isolate::GetCurrent(), GL_SRC0_RGB), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SRC1_RGB"), Uint32::New(v8::Isolate::GetCurrent(), GL_SRC1_RGB), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SRC2_RGB"), Uint32::New(v8::Isolate::GetCurrent(), GL_SRC2_RGB), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SRC0_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_SRC0_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SRC1_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_SRC1_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SRC2_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_SRC2_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SOURCE0_RGB"), Uint32::New(v8::Isolate::GetCurrent(), GL_SOURCE0_RGB), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SOURCE1_RGB"), Uint32::New(v8::Isolate::GetCurrent(), GL_SOURCE1_RGB), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SOURCE2_RGB"), Uint32::New(v8::Isolate::GetCurrent(), GL_SOURCE2_RGB), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SOURCE0_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_SOURCE0_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SOURCE1_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_SOURCE1_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SOURCE2_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_SOURCE2_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "OPERAND0_RGB"), Uint32::New(v8::Isolate::GetCurrent(), GL_OPERAND0_RGB), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "OPERAND1_RGB"), Uint32::New(v8::Isolate::GetCurrent(), GL_OPERAND1_RGB), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "OPERAND2_RGB"), Uint32::New(v8::Isolate::GetCurrent(), GL_OPERAND2_RGB), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "OPERAND0_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_OPERAND0_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "OPERAND1_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_OPERAND1_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "OPERAND2_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_OPERAND2_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DOT3_RGB"), Uint32::New(v8::Isolate::GetCurrent(), GL_DOT3_RGB), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DOT3_RGBA"), Uint32::New(v8::Isolate::GetCurrent(), GL_DOT3_RGBA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TRANSPOSE_MODELVIEW_MATRIX"), Uint32::New(v8::Isolate::GetCurrent(), GL_TRANSPOSE_MODELVIEW_MATRIX), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TRANSPOSE_PROJECTION_MATRIX"), Uint32::New(v8::Isolate::GetCurrent(), GL_TRANSPOSE_PROJECTION_MATRIX), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TRANSPOSE_TEXTURE_MATRIX"), Uint32::New(v8::Isolate::GetCurrent(), GL_TRANSPOSE_TEXTURE_MATRIX), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TRANSPOSE_COLOR_MATRIX"), Uint32::New(v8::Isolate::GetCurrent(), GL_TRANSPOSE_COLOR_MATRIX), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NORMAL_MAP"), Uint32::New(v8::Isolate::GetCurrent(), GL_NORMAL_MAP), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "REFLECTION_MAP"), Uint32::New(v8::Isolate::GetCurrent(), GL_REFLECTION_MAP), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_CUBE_MAP"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_CUBE_MAP), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_BINDING_CUBE_MAP"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_BINDING_CUBE_MAP), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_CUBE_MAP_POSITIVE_X"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_CUBE_MAP_POSITIVE_X), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_CUBE_MAP_POSITIVE_Y"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_CUBE_MAP_POSITIVE_Y), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_CUBE_MAP_POSITIVE_Z"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_CUBE_MAP_POSITIVE_Z), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PROXY_TEXTURE_CUBE_MAP"), Uint32::New(v8::Isolate::GetCurrent(), GL_PROXY_TEXTURE_CUBE_MAP), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_CUBE_MAP_TEXTURE_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_CUBE_MAP_TEXTURE_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COMPRESSED_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_COMPRESSED_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COMPRESSED_LUMINANCE"), Uint32::New(v8::Isolate::GetCurrent(), GL_COMPRESSED_LUMINANCE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COMPRESSED_LUMINANCE_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_COMPRESSED_LUMINANCE_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COMPRESSED_INTENSITY"), Uint32::New(v8::Isolate::GetCurrent(), GL_COMPRESSED_INTENSITY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COMPRESSED_RGB"), Uint32::New(v8::Isolate::GetCurrent(), GL_COMPRESSED_RGB), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COMPRESSED_RGBA"), Uint32::New(v8::Isolate::GetCurrent(), GL_COMPRESSED_RGBA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_COMPRESSION_HINT"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_COMPRESSION_HINT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_COMPRESSED_IMAGE_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_COMPRESSED_IMAGE_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_COMPRESSED"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_COMPRESSED), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NUM_COMPRESSED_TEXTURE_FORMATS"), Uint32::New(v8::Isolate::GetCurrent(), GL_NUM_COMPRESSED_TEXTURE_FORMATS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COMPRESSED_TEXTURE_FORMATS"), Uint32::New(v8::Isolate::GetCurrent(), GL_COMPRESSED_TEXTURE_FORMATS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MULTISAMPLE"), Uint32::New(v8::Isolate::GetCurrent(), GL_MULTISAMPLE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SAMPLE_ALPHA_TO_COVERAGE"), Uint32::New(v8::Isolate::GetCurrent(), GL_SAMPLE_ALPHA_TO_COVERAGE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SAMPLE_ALPHA_TO_ONE"), Uint32::New(v8::Isolate::GetCurrent(), GL_SAMPLE_ALPHA_TO_ONE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SAMPLE_COVERAGE"), Uint32::New(v8::Isolate::GetCurrent(), GL_SAMPLE_COVERAGE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SAMPLE_BUFFERS"), Uint32::New(v8::Isolate::GetCurrent(), GL_SAMPLE_BUFFERS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SAMPLES"), Uint32::New(v8::Isolate::GetCurrent(), GL_SAMPLES), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SAMPLE_COVERAGE_VALUE"), Uint32::New(v8::Isolate::GetCurrent(), GL_SAMPLE_COVERAGE_VALUE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SAMPLE_COVERAGE_INVERT"), Uint32::New(v8::Isolate::GetCurrent(), GL_SAMPLE_COVERAGE_INVERT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MULTISAMPLE_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_MULTISAMPLE_BIT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_COMPONENT16"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_COMPONENT16), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_COMPONENT24"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_COMPONENT24), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_COMPONENT32"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_COMPONENT32), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_DEPTH_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_DEPTH_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_TEXTURE_MODE"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_TEXTURE_MODE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_COMPARE_MODE"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_COMPARE_MODE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_COMPARE_FUNC"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_COMPARE_FUNC), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COMPARE_R_TO_TEXTURE"), Uint32::New(v8::Isolate::GetCurrent(), GL_COMPARE_R_TO_TEXTURE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "QUERY_COUNTER_BITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_QUERY_COUNTER_BITS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURRENT_QUERY"), Uint32::New(v8::Isolate::GetCurrent(), GL_CURRENT_QUERY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "QUERY_RESULT"), Uint32::New(v8::Isolate::GetCurrent(), GL_QUERY_RESULT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "QUERY_RESULT_AVAILABLE"), Uint32::New(v8::Isolate::GetCurrent(), GL_QUERY_RESULT_AVAILABLE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SAMPLES_PASSED"), Uint32::New(v8::Isolate::GetCurrent(), GL_SAMPLES_PASSED), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG_COORD_SRC"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG_COORD_SRC), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG_COORD"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG_COORD), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FRAGMENT_DEPTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_FRAGMENT_DEPTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURRENT_FOG_COORD"), Uint32::New(v8::Isolate::GetCurrent(), GL_CURRENT_FOG_COORD), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG_COORD_ARRAY_TYPE"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG_COORD_ARRAY_TYPE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG_COORD_ARRAY_STRIDE"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG_COORD_ARRAY_STRIDE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG_COORD_ARRAY_POINTER"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG_COORD_ARRAY_POINTER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG_COORD_ARRAY"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG_COORD_ARRAY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG_COORDINATE_SOURCE"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG_COORDINATE_SOURCE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG_COORDINATE"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG_COORDINATE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURRENT_FOG_COORDINATE"), Uint32::New(v8::Isolate::GetCurrent(), GL_CURRENT_FOG_COORDINATE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG_COORDINATE_ARRAY_TYPE"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG_COORDINATE_ARRAY_TYPE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG_COORDINATE_ARRAY_STRIDE"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG_COORDINATE_ARRAY_STRIDE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG_COORDINATE_ARRAY_POINTER"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG_COORDINATE_ARRAY_POINTER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG_COORDINATE_ARRAY"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG_COORDINATE_ARRAY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_SUM"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_SUM), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURRENT_SECONDARY_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_CURRENT_SECONDARY_COLOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SECONDARY_COLOR_ARRAY_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_SECONDARY_COLOR_ARRAY_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SECONDARY_COLOR_ARRAY_TYPE"), Uint32::New(v8::Isolate::GetCurrent(), GL_SECONDARY_COLOR_ARRAY_TYPE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SECONDARY_COLOR_ARRAY_STRIDE"), Uint32::New(v8::Isolate::GetCurrent(), GL_SECONDARY_COLOR_ARRAY_STRIDE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SECONDARY_COLOR_ARRAY_POINTER"), Uint32::New(v8::Isolate::GetCurrent(), GL_SECONDARY_COLOR_ARRAY_POINTER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SECONDARY_COLOR_ARRAY"), Uint32::New(v8::Isolate::GetCurrent(), GL_SECONDARY_COLOR_ARRAY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POINT_SIZE_MIN"), Uint32::New(v8::Isolate::GetCurrent(), GL_POINT_SIZE_MIN), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POINT_SIZE_MAX"), Uint32::New(v8::Isolate::GetCurrent(), GL_POINT_SIZE_MAX), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POINT_FADE_THRESHOLD_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_POINT_FADE_THRESHOLD_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLEND_DST_RGB"), Uint32::New(v8::Isolate::GetCurrent(), GL_BLEND_DST_RGB), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLEND_SRC_RGB"), Uint32::New(v8::Isolate::GetCurrent(), GL_BLEND_SRC_RGB), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLEND_DST_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_BLEND_DST_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLEND_SRC_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_BLEND_SRC_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GENERATE_MIPMAP"), Uint32::New(v8::Isolate::GetCurrent(), GL_GENERATE_MIPMAP), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GENERATE_MIPMAP_HINT"), Uint32::New(v8::Isolate::GetCurrent(), GL_GENERATE_MIPMAP_HINT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INCR_WRAP"), Uint32::New(v8::Isolate::GetCurrent(), GL_INCR_WRAP), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DECR_WRAP"), Uint32::New(v8::Isolate::GetCurrent(), GL_DECR_WRAP), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MIRRORED_REPEAT"), Uint32::New(v8::Isolate::GetCurrent(), GL_MIRRORED_REPEAT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_TEXTURE_LOD_BIAS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_TEXTURE_LOD_BIAS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_FILTER_CONTROL"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_FILTER_CONTROL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_LOD_BIAS"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_LOD_BIAS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ARRAY_BUFFER"), Uint32::New(v8::Isolate::GetCurrent(), GL_ARRAY_BUFFER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ELEMENT_ARRAY_BUFFER"), Uint32::New(v8::Isolate::GetCurrent(), GL_ELEMENT_ARRAY_BUFFER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ARRAY_BUFFER_BINDING"), Uint32::New(v8::Isolate::GetCurrent(), GL_ARRAY_BUFFER_BINDING), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ELEMENT_ARRAY_BUFFER_BINDING"), Uint32::New(v8::Isolate::GetCurrent(), GL_ELEMENT_ARRAY_BUFFER_BINDING), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_ARRAY_BUFFER_BINDING"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_ARRAY_BUFFER_BINDING), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NORMAL_ARRAY_BUFFER_BINDING"), Uint32::New(v8::Isolate::GetCurrent(), GL_NORMAL_ARRAY_BUFFER_BINDING), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_ARRAY_BUFFER_BINDING"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_ARRAY_BUFFER_BINDING), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INDEX_ARRAY_BUFFER_BINDING"), Uint32::New(v8::Isolate::GetCurrent(), GL_INDEX_ARRAY_BUFFER_BINDING), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_COORD_ARRAY_BUFFER_BINDING"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EDGE_FLAG_ARRAY_BUFFER_BINDING"), Uint32::New(v8::Isolate::GetCurrent(), GL_EDGE_FLAG_ARRAY_BUFFER_BINDING), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SECONDARY_COLOR_ARRAY_BUFFER_BINDING"), Uint32::New(v8::Isolate::GetCurrent(), GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG_COORD_ARRAY_BUFFER_BINDING"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG_COORD_ARRAY_BUFFER_BINDING), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WEIGHT_ARRAY_BUFFER_BINDING"), Uint32::New(v8::Isolate::GetCurrent(), GL_WEIGHT_ARRAY_BUFFER_BINDING), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_ATTRIB_ARRAY_BUFFER_BINDING"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STREAM_DRAW"), Uint32::New(v8::Isolate::GetCurrent(), GL_STREAM_DRAW), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STREAM_READ"), Uint32::New(v8::Isolate::GetCurrent(), GL_STREAM_READ), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STREAM_COPY"), Uint32::New(v8::Isolate::GetCurrent(), GL_STREAM_COPY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DYNAMIC_DRAW"), Uint32::New(v8::Isolate::GetCurrent(), GL_DYNAMIC_DRAW), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DYNAMIC_READ"), Uint32::New(v8::Isolate::GetCurrent(), GL_DYNAMIC_READ), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DYNAMIC_COPY"), Uint32::New(v8::Isolate::GetCurrent(), GL_DYNAMIC_COPY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "READ_ONLY"), Uint32::New(v8::Isolate::GetCurrent(), GL_READ_ONLY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WRITE_ONLY"), Uint32::New(v8::Isolate::GetCurrent(), GL_WRITE_ONLY), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "READ_WRITE"), Uint32::New(v8::Isolate::GetCurrent(), GL_READ_WRITE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BUFFER_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_BUFFER_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BUFFER_USAGE"), Uint32::New(v8::Isolate::GetCurrent(), GL_BUFFER_USAGE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BUFFER_ACCESS"), Uint32::New(v8::Isolate::GetCurrent(), GL_BUFFER_ACCESS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BUFFER_MAPPED"), Uint32::New(v8::Isolate::GetCurrent(), GL_BUFFER_MAPPED), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BUFFER_MAP_POINTER"), Uint32::New(v8::Isolate::GetCurrent(), GL_BUFFER_MAP_POINTER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FOG_COORDINATE_ARRAY_BUFFER_BINDING"), Uint32::New(v8::Isolate::GetCurrent(), GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURRENT_PROGRAM"), Uint32::New(v8::Isolate::GetCurrent(), GL_CURRENT_PROGRAM), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SHADER_TYPE"), Uint32::New(v8::Isolate::GetCurrent(), GL_SHADER_TYPE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DELETE_STATUS"), Uint32::New(v8::Isolate::GetCurrent(), GL_DELETE_STATUS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COMPILE_STATUS"), Uint32::New(v8::Isolate::GetCurrent(), GL_COMPILE_STATUS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINK_STATUS"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINK_STATUS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VALIDATE_STATUS"), Uint32::New(v8::Isolate::GetCurrent(), GL_VALIDATE_STATUS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INFO_LOG_LENGTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_INFO_LOG_LENGTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ATTACHED_SHADERS"), Uint32::New(v8::Isolate::GetCurrent(), GL_ATTACHED_SHADERS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ACTIVE_UNIFORMS"), Uint32::New(v8::Isolate::GetCurrent(), GL_ACTIVE_UNIFORMS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ACTIVE_UNIFORM_MAX_LENGTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_ACTIVE_UNIFORM_MAX_LENGTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SHADER_SOURCE_LENGTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_SHADER_SOURCE_LENGTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FLOAT_VEC2"), Uint32::New(v8::Isolate::GetCurrent(), GL_FLOAT_VEC2), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FLOAT_VEC3"), Uint32::New(v8::Isolate::GetCurrent(), GL_FLOAT_VEC3), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FLOAT_VEC4"), Uint32::New(v8::Isolate::GetCurrent(), GL_FLOAT_VEC4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INT_VEC2"), Uint32::New(v8::Isolate::GetCurrent(), GL_INT_VEC2), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INT_VEC3"), Uint32::New(v8::Isolate::GetCurrent(), GL_INT_VEC3), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INT_VEC4"), Uint32::New(v8::Isolate::GetCurrent(), GL_INT_VEC4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BOOL"), Uint32::New(v8::Isolate::GetCurrent(), GL_BOOL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BOOL_VEC2"), Uint32::New(v8::Isolate::GetCurrent(), GL_BOOL_VEC2), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BOOL_VEC3"), Uint32::New(v8::Isolate::GetCurrent(), GL_BOOL_VEC3), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BOOL_VEC4"), Uint32::New(v8::Isolate::GetCurrent(), GL_BOOL_VEC4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FLOAT_MAT2"), Uint32::New(v8::Isolate::GetCurrent(), GL_FLOAT_MAT2), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FLOAT_MAT3"), Uint32::New(v8::Isolate::GetCurrent(), GL_FLOAT_MAT3), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FLOAT_MAT4"), Uint32::New(v8::Isolate::GetCurrent(), GL_FLOAT_MAT4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SAMPLER_1D"), Uint32::New(v8::Isolate::GetCurrent(), GL_SAMPLER_1D), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SAMPLER_2D"), Uint32::New(v8::Isolate::GetCurrent(), GL_SAMPLER_2D), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SAMPLER_3D"), Uint32::New(v8::Isolate::GetCurrent(), GL_SAMPLER_3D), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SAMPLER_CUBE"), Uint32::New(v8::Isolate::GetCurrent(), GL_SAMPLER_CUBE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SAMPLER_1D_SHADOW"), Uint32::New(v8::Isolate::GetCurrent(), GL_SAMPLER_1D_SHADOW), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SAMPLER_2D_SHADOW"), Uint32::New(v8::Isolate::GetCurrent(), GL_SAMPLER_2D_SHADOW), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SHADING_LANGUAGE_VERSION"), Uint32::New(v8::Isolate::GetCurrent(), GL_SHADING_LANGUAGE_VERSION), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_SHADER"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_SHADER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_VERTEX_UNIFORM_COMPONENTS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_VERTEX_UNIFORM_COMPONENTS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_VARYING_FLOATS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_VARYING_FLOATS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_VERTEX_TEXTURE_IMAGE_UNITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_COMBINED_TEXTURE_IMAGE_UNITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ACTIVE_ATTRIBUTES"), Uint32::New(v8::Isolate::GetCurrent(), GL_ACTIVE_ATTRIBUTES), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ACTIVE_ATTRIBUTE_MAX_LENGTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_ACTIVE_ATTRIBUTE_MAX_LENGTH), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FRAGMENT_SHADER"), Uint32::New(v8::Isolate::GetCurrent(), GL_FRAGMENT_SHADER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_FRAGMENT_UNIFORM_COMPONENTS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_FRAGMENT_UNIFORM_COMPONENTS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_VERTEX_ATTRIBS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_VERTEX_ATTRIBS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_ATTRIB_ARRAY_ENABLED"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_ATTRIB_ARRAY_ENABLED), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_ATTRIB_ARRAY_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_ATTRIB_ARRAY_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_ATTRIB_ARRAY_STRIDE"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_ATTRIB_ARRAY_STRIDE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_ATTRIB_ARRAY_TYPE"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_ATTRIB_ARRAY_TYPE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_ATTRIB_ARRAY_NORMALIZED"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_ATTRIB_ARRAY_NORMALIZED), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURRENT_VERTEX_ATTRIB"), Uint32::New(v8::Isolate::GetCurrent(), GL_CURRENT_VERTEX_ATTRIB), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_ATTRIB_ARRAY_POINTER"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_ATTRIB_ARRAY_POINTER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_PROGRAM_POINT_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_PROGRAM_POINT_SIZE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_PROGRAM_TWO_SIDE"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_PROGRAM_TWO_SIDE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_TEXTURE_COORDS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_TEXTURE_COORDS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_TEXTURE_IMAGE_UNITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_TEXTURE_IMAGE_UNITS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_DRAW_BUFFERS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_DRAW_BUFFERS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DRAW_BUFFER0"), Uint32::New(v8::Isolate::GetCurrent(), GL_DRAW_BUFFER0), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DRAW_BUFFER1"), Uint32::New(v8::Isolate::GetCurrent(), GL_DRAW_BUFFER1), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DRAW_BUFFER2"), Uint32::New(v8::Isolate::GetCurrent(), GL_DRAW_BUFFER2), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DRAW_BUFFER3"), Uint32::New(v8::Isolate::GetCurrent(), GL_DRAW_BUFFER3), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DRAW_BUFFER4"), Uint32::New(v8::Isolate::GetCurrent(), GL_DRAW_BUFFER4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DRAW_BUFFER5"), Uint32::New(v8::Isolate::GetCurrent(), GL_DRAW_BUFFER5), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DRAW_BUFFER6"), Uint32::New(v8::Isolate::GetCurrent(), GL_DRAW_BUFFER6), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DRAW_BUFFER7"), Uint32::New(v8::Isolate::GetCurrent(), GL_DRAW_BUFFER7), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DRAW_BUFFER8"), Uint32::New(v8::Isolate::GetCurrent(), GL_DRAW_BUFFER8), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DRAW_BUFFER9"), Uint32::New(v8::Isolate::GetCurrent(), GL_DRAW_BUFFER9), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DRAW_BUFFER10"), Uint32::New(v8::Isolate::GetCurrent(), GL_DRAW_BUFFER10), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DRAW_BUFFER11"), Uint32::New(v8::Isolate::GetCurrent(), GL_DRAW_BUFFER11), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DRAW_BUFFER12"), Uint32::New(v8::Isolate::GetCurrent(), GL_DRAW_BUFFER12), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DRAW_BUFFER13"), Uint32::New(v8::Isolate::GetCurrent(), GL_DRAW_BUFFER13), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DRAW_BUFFER14"), Uint32::New(v8::Isolate::GetCurrent(), GL_DRAW_BUFFER14), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DRAW_BUFFER15"), Uint32::New(v8::Isolate::GetCurrent(), GL_DRAW_BUFFER15), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POINT_SPRITE"), Uint32::New(v8::Isolate::GetCurrent(), GL_POINT_SPRITE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COORD_REPLACE"), Uint32::New(v8::Isolate::GetCurrent(), GL_COORD_REPLACE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POINT_SPRITE_COORD_ORIGIN"), Uint32::New(v8::Isolate::GetCurrent(), GL_POINT_SPRITE_COORD_ORIGIN), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LOWER_LEFT"), Uint32::New(v8::Isolate::GetCurrent(), GL_LOWER_LEFT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UPPER_LEFT"), Uint32::New(v8::Isolate::GetCurrent(), GL_UPPER_LEFT), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_BACK_FUNC"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_BACK_FUNC), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_BACK_VALUE_MASK"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_BACK_VALUE_MASK), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_BACK_REF"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_BACK_REF), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_BACK_FAIL"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_BACK_FAIL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_BACK_PASS_DEPTH_FAIL"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_BACK_PASS_DEPTH_FAIL), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_BACK_PASS_DEPTH_PASS"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_BACK_PASS_DEPTH_PASS), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_BACK_WRITEMASK"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_BACK_WRITEMASK), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURRENT_RASTER_SECONDARY_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_CURRENT_RASTER_SECONDARY_COLOR), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_PACK_BUFFER"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_PACK_BUFFER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_UNPACK_BUFFER"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_UNPACK_BUFFER), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_PACK_BUFFER_BINDING"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_PACK_BUFFER_BINDING), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PIXEL_UNPACK_BUFFER_BINDING"), Uint32::New(v8::Isolate::GetCurrent(), GL_PIXEL_UNPACK_BUFFER_BINDING), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FLOAT_MAT2x3"), Uint32::New(v8::Isolate::GetCurrent(), GL_FLOAT_MAT2x3), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FLOAT_MAT2x4"), Uint32::New(v8::Isolate::GetCurrent(), GL_FLOAT_MAT2x4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FLOAT_MAT3x2"), Uint32::New(v8::Isolate::GetCurrent(), GL_FLOAT_MAT3x2), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FLOAT_MAT3x4"), Uint32::New(v8::Isolate::GetCurrent(), GL_FLOAT_MAT3x4), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FLOAT_MAT4x2"), Uint32::New(v8::Isolate::GetCurrent(), GL_FLOAT_MAT4x2), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FLOAT_MAT4x3"), Uint32::New(v8::Isolate::GetCurrent(), GL_FLOAT_MAT4x3), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SRGB"), Uint32::New(v8::Isolate::GetCurrent(), GL_SRGB), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SRGB8"), Uint32::New(v8::Isolate::GetCurrent(), GL_SRGB8), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SRGB_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_SRGB_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SRGB8_ALPHA8"), Uint32::New(v8::Isolate::GetCurrent(), GL_SRGB8_ALPHA8), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SLUMINANCE_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_SLUMINANCE_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SLUMINANCE8_ALPHA8"), Uint32::New(v8::Isolate::GetCurrent(), GL_SLUMINANCE8_ALPHA8), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SLUMINANCE"), Uint32::New(v8::Isolate::GetCurrent(), GL_SLUMINANCE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SLUMINANCE8"), Uint32::New(v8::Isolate::GetCurrent(), GL_SLUMINANCE8), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COMPRESSED_SRGB"), Uint32::New(v8::Isolate::GetCurrent(), GL_COMPRESSED_SRGB), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COMPRESSED_SRGB_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_COMPRESSED_SRGB_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COMPRESSED_SLUMINANCE"), Uint32::New(v8::Isolate::GetCurrent(), GL_COMPRESSED_SLUMINANCE), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COMPRESSED_SLUMINANCE_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_COMPRESSED_SLUMINANCE_ALPHA), ReadOnly);

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Accum"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglAccumCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "AlphaFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglAlphaFuncCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "AreTexturesResident"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglAreTexturesResidentCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ArrayElement"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglArrayElementCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Begin"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglBeginCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BindTexture"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglBindTextureCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Bitmap"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglBitmapCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BlendColor"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglBlendColorCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BlendEquation"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglBlendEquationCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BlendEquationSeparate"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglBlendEquationSeparateCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BlendFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglBlendFuncCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CallList"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglCallListCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Clear"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglClearCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ClearAccum"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglClearAccumCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ClearColor"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglClearColorCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ClearDepth"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglClearDepthCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ClearIndex"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglClearIndexCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ClearStencil"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglClearStencilCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ClipPlane"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglClipPlaneCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color3b"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor3bCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color3bv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor3bvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color3d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor3dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color3dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor3dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color3f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor3fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color3fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor3fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color3i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor3iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color3iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor3ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color3s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor3sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color3sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor3svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color3ub"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor3ubCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color3ubv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor3ubvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color3ui"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor3uiCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color3uiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor3uivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color3us"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor3usCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color3usv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor3usvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color4b"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor4bCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color4bv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor4bvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color4d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor4dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color4dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor4dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color4f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor4fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color4fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor4fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color4i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor4iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color4iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor4ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color4s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor4sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color4sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor4svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color4ub"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor4ubCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color4ubv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor4ubvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color4ui"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor4uiCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color4uiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor4uivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color4us"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor4usCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Color4usv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColor4usvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ColorMask"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColorMaskCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ColorMaterial"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColorMaterialCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ColorTableParameterfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColorTableParameterfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ColorTableParameteriv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglColorTableParameterivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ConvolutionParameterf"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglConvolutionParameterfCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ConvolutionParameterfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglConvolutionParameterfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ConvolutionParameteri"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglConvolutionParameteriCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ConvolutionParameteriv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglConvolutionParameterivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CopyColorSubTable"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglCopyColorSubTableCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CopyColorTable"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglCopyColorTableCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CopyConvolutionFilter1D"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglCopyConvolutionFilter1DCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CopyConvolutionFilter2D"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglCopyConvolutionFilter2DCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CopyPixels"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglCopyPixelsCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CopyTexImage1D"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglCopyTexImage1DCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CopyTexImage2D"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglCopyTexImage2DCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CopyTexSubImage1D"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglCopyTexSubImage1DCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CopyTexSubImage2D"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglCopyTexSubImage2DCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CopyTexSubImage3D"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglCopyTexSubImage3DCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CullFace"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglCullFaceCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DeleteLists"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglDeleteListsCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DeleteTextures"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglDeleteTexturesCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DepthFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglDepthFuncCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DepthMask"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglDepthMaskCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DepthRange"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglDepthRangeCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Disable"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglDisableCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DisableClientState"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglDisableClientStateCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DrawArrays"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglDrawArraysCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DrawBuffer"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglDrawBufferCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EdgeFlag"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglEdgeFlagCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EdgeFlagv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglEdgeFlagvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Enable"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglEnableCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EnableClientState"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglEnableClientStateCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "End"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglEndCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EndList"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglEndListCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EvalCoord1d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglEvalCoord1dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EvalCoord1dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglEvalCoord1dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EvalCoord1f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglEvalCoord1fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EvalCoord1fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglEvalCoord1fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EvalCoord2d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglEvalCoord2dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EvalCoord2dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglEvalCoord2dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EvalCoord2f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglEvalCoord2fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EvalCoord2fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglEvalCoord2fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EvalMesh1"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglEvalMesh1Callback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EvalMesh2"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglEvalMesh2Callback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EvalPoint1"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglEvalPoint1Callback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EvalPoint2"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglEvalPoint2Callback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FeedbackBuffer"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglFeedbackBufferCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Finish"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglFinishCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Flush"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglFlushCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Fogf"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglFogfCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Fogfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglFogfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Fogi"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglFogiCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Fogiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglFogivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FrontFace"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglFrontFaceCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Frustum"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglFrustumCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GenLists"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGenListsCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GenTextures"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGenTexturesCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetBooleanv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetBooleanvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetClipPlane"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetClipPlaneCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetColorTableParameterfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetColorTableParameterfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetColorTableParameteriv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetColorTableParameterivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetConvolutionParameterfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetConvolutionParameterfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetConvolutionParameteriv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetConvolutionParameterivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetDoublev"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetDoublevCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetError"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetErrorCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetFloatv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetFloatvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetHistogramParameterfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetHistogramParameterfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetHistogramParameteriv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetHistogramParameterivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetIntegerv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetIntegervCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetLightfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetLightfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetLightiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetLightivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetMapdv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetMapdvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetMapfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetMapfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetMapiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetMapivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetMaterialfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetMaterialfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetMaterialiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetMaterialivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetMinmaxParameterfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetMinmaxParameterfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetMinmaxParameteriv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetMinmaxParameterivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetPixelMapfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetPixelMapfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetPixelMapuiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetPixelMapuivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetPixelMapusv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetPixelMapusvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetPolygonStipple"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetPolygonStippleCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetTexEnvfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetTexEnvfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetTexEnviv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetTexEnvivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetTexGendv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetTexGendvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetTexGenfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetTexGenfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetTexGeniv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetTexGenivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetTexLevelParameterfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetTexLevelParameterfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetTexLevelParameteriv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetTexLevelParameterivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetTexParameterfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetTexParameterfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetTexParameteriv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetTexParameterivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Hint"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglHintCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Histogram"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglHistogramCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "IndexMask"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglIndexMaskCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Indexd"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglIndexdCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Indexdv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglIndexdvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Indexf"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglIndexfCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Indexfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglIndexfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Indexi"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglIndexiCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Indexiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglIndexivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Indexs"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglIndexsCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Indexsv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglIndexsvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Indexub"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglIndexubCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Indexubv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglIndexubvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "InitNames"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglInitNamesCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "IsEnabled"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglIsEnabledCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "IsList"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglIsListCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "IsTexture"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglIsTextureCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LightModelf"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglLightModelfCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LightModelfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglLightModelfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LightModeli"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglLightModeliCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LightModeliv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglLightModelivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Lightf"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglLightfCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Lightfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglLightfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Lighti"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglLightiCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Lightiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglLightivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LineStipple"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglLineStippleCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LineWidth"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglLineWidthCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ListBase"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglListBaseCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LoadIdentity"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglLoadIdentityCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LoadMatrixd"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglLoadMatrixdCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LoadMatrixf"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglLoadMatrixfCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LoadName"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglLoadNameCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LogicOp"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglLogicOpCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Map1d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMap1dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Map1f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMap1fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Map2d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMap2dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Map2f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMap2fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MapGrid1d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMapGrid1dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MapGrid1f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMapGrid1fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MapGrid2d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMapGrid2dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MapGrid2f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMapGrid2fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Materialf"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMaterialfCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Materialfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMaterialfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Materiali"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMaterialiCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Materialiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMaterialivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MatrixMode"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMatrixModeCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Minmax"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMinmaxCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultMatrixd"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultMatrixdCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultMatrixf"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultMatrixfCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NewList"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglNewListCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Normal3b"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglNormal3bCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Normal3bv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglNormal3bvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Normal3d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglNormal3dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Normal3dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglNormal3dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Normal3f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglNormal3fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Normal3fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglNormal3fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Normal3i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglNormal3iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Normal3iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglNormal3ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Normal3s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglNormal3sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Normal3sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglNormal3svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Ortho"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglOrthoCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PassThrough"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPassThroughCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PixelMapfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPixelMapfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PixelMapuiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPixelMapuivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PixelMapusv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPixelMapusvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PixelStoref"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPixelStorefCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PixelStorei"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPixelStoreiCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PixelTransferf"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPixelTransferfCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PixelTransferi"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPixelTransferiCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PixelZoom"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPixelZoomCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PointSize"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPointSizeCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PolygonMode"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPolygonModeCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PolygonOffset"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPolygonOffsetCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PolygonStipple"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPolygonStippleCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PopAttrib"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPopAttribCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PopClientAttrib"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPopClientAttribCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PopMatrix"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPopMatrixCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PopName"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPopNameCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PrioritizeTextures"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPrioritizeTexturesCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PushAttrib"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPushAttribCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PushClientAttrib"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPushClientAttribCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PushMatrix"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPushMatrixCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PushName"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPushNameCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos2d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos2dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos2dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos2dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos2f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos2fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos2fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos2fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos2i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos2iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos2iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos2ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos2s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos2sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos2sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos2svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos3d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos3dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos3dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos3dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos3f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos3fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos3fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos3fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos3i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos3iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos3iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos3ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos3s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos3sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos3sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos3svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos4d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos4dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos4dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos4dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos4f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos4fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos4fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos4fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos4i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos4iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos4iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos4ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos4s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos4sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RasterPos4sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRasterPos4svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ReadBuffer"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglReadBufferCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Rectd"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRectdCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Rectdv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRectdvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Rectf"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRectfCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Rectfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRectfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Recti"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRectiCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Rectiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRectivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Rects"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRectsCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Rectsv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRectsvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RenderMode"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRenderModeCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ResetHistogram"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglResetHistogramCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ResetMinmax"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglResetMinmaxCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Rotated"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRotatedCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Rotatef"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglRotatefCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Scaled"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglScaledCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Scalef"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglScalefCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Scissor"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglScissorCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SelectBuffer"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglSelectBufferCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ShadeModel"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglShadeModelCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "StencilFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglStencilFuncCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "StencilMask"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglStencilMaskCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "StencilOp"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglStencilOpCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord1d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord1dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord1dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord1dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord1f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord1fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord1fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord1fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord1i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord1iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord1iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord1ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord1s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord1sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord1sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord1svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord2d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord2dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord2dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord2dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord2f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord2fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord2fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord2fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord2i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord2iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord2iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord2ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord2s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord2sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord2sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord2svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord3d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord3dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord3dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord3dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord3f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord3fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord3fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord3fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord3i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord3iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord3iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord3ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord3s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord3sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord3sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord3svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord4d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord4dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord4dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord4dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord4f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord4fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord4fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord4fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord4i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord4iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord4iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord4ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord4s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord4sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexCoord4sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexCoord4svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexEnvf"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexEnvfCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexEnvfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexEnvfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexEnvi"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexEnviCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexEnviv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexEnvivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexGend"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexGendCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexGendv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexGendvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexGenf"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexGenfCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexGenfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexGenfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexGeni"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexGeniCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexGeniv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexGenivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexParameterf"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexParameterfCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexParameterfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexParameterfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexParameteri"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexParameteriCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexParameteriv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTexParameterivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Translated"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTranslatedCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Translatef"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglTranslatefCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex2d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex2dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex2dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex2dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex2f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex2fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex2fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex2fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex2i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex2iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex2iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex2ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex2s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex2sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex2sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex2svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex3d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex3dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex3dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex3dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex3f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex3fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex3fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex3fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex3i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex3iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex3iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex3ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex3s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex3sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex3sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex3svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex4d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex4dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex4dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex4dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex4f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex4fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex4fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex4fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex4i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex4iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex4iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex4ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex4s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex4sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Vertex4sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertex4svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Viewport"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglViewportCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SampleCoverage"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglSampleCoverageCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LoadTransposeMatrixf"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglLoadTransposeMatrixfCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LoadTransposeMatrixd"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglLoadTransposeMatrixdCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultTransposeMatrixf"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultTransposeMatrixfCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultTransposeMatrixd"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultTransposeMatrixdCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ActiveTexture"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglActiveTextureCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ClientActiveTexture"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglClientActiveTextureCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord1d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord1dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord1dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord1dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord1f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord1fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord1fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord1fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord1i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord1iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord1iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord1ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord1s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord1sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord1sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord1svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord2d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord2dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord2dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord2dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord2f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord2fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord2fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord2fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord2i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord2iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord2iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord2ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord2s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord2sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord2sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord2svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord3d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord3dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord3dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord3dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord3f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord3fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord3fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord3fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord3i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord3iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord3iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord3ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord3s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord3sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord3sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord3svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord4d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord4dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord4dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord4dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord4f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord4fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord4fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord4fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord4iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord4ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord4s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord4sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiTexCoord4sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiTexCoord4svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FogCoordf"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglFogCoordfCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FogCoordfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglFogCoordfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FogCoordd"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglFogCoorddCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SecondaryColor3b"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglSecondaryColor3bCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SecondaryColor3bv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglSecondaryColor3bvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SecondaryColor3d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglSecondaryColor3dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SecondaryColor3dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglSecondaryColor3dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SecondaryColor3f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglSecondaryColor3fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SecondaryColor3fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglSecondaryColor3fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SecondaryColor3i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglSecondaryColor3iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SecondaryColor3iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglSecondaryColor3ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SecondaryColor3s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglSecondaryColor3sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SecondaryColor3sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglSecondaryColor3svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SecondaryColor3ub"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglSecondaryColor3ubCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SecondaryColor3ubv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglSecondaryColor3ubvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SecondaryColor3ui"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglSecondaryColor3uiCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SecondaryColor3uiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglSecondaryColor3uivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SecondaryColor3us"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglSecondaryColor3usCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SecondaryColor3usv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglSecondaryColor3usvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PointParameterf"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPointParameterfCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PointParameterfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPointParameterfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PointParameteri"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPointParameteriCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PointParameteriv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglPointParameterivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BlendFuncSeparate"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglBlendFuncSeparateCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MultiDrawArrays"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglMultiDrawArraysCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WindowPos2d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglWindowPos2dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WindowPos2dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglWindowPos2dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WindowPos2f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglWindowPos2fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WindowPos2fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglWindowPos2fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WindowPos2i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglWindowPos2iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WindowPos2iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglWindowPos2ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WindowPos2s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglWindowPos2sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WindowPos2sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglWindowPos2svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WindowPos3d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglWindowPos3dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WindowPos3dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglWindowPos3dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WindowPos3f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglWindowPos3fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WindowPos3fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglWindowPos3fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WindowPos3i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglWindowPos3iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WindowPos3iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglWindowPos3ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WindowPos3s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglWindowPos3sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WindowPos3sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglWindowPos3svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GenQueries"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGenQueriesCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DeleteQueries"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglDeleteQueriesCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "IsQuery"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglIsQueryCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BeginQuery"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglBeginQueryCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EndQuery"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglEndQueryCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetQueryiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetQueryivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetQueryObjectiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetQueryObjectivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetQueryObjectuiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetQueryObjectuivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BindBuffer"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglBindBufferCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DeleteBuffers"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglDeleteBuffersCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GenBuffers"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGenBuffersCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "IsBuffer"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglIsBufferCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UnmapBuffer"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUnmapBufferCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetBufferParameteriv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetBufferParameterivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DrawBuffers"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglDrawBuffersCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib1d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib1dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib1dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib1dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib1f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib1fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib1fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib1fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib1s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib1sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib1sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib1svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib2d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib2dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib2dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib2dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib2f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib2fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib2fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib2fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib2s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib2sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib2sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib2svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib3d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib3dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib3dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib3dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib3f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib3fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib3fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib3fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib3s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib3sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib3sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib3svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib4Nbv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib4NbvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib4Niv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib4NivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib4Nsv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib4NsvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib4Nub"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib4NubCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib4Nubv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib4NubvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib4Nuiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib4NuivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib4Nusv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib4NusvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib4bv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib4bvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib4d"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib4dCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib4dv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib4dvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib4f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib4fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib4fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib4fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib4iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib4ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib4s"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib4sCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib4sv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib4svCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib4ubv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib4ubvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib4uiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib4uivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib4usv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglVertexAttrib4usvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EnableVertexAttribArray"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglEnableVertexAttribArrayCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DisableVertexAttribArray"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglDisableVertexAttribArrayCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetVertexAttribdv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetVertexAttribdvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetVertexAttribfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetVertexAttribfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetVertexAttribiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetVertexAttribivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DeleteShader"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglDeleteShaderCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DetachShader"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglDetachShaderCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CreateShader"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglCreateShaderCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CompileShader"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglCompileShaderCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CreateProgram"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglCreateProgramCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "AttachShader"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglAttachShaderCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LinkProgram"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglLinkProgramCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UseProgram"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUseProgramCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DeleteProgram"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglDeleteProgramCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ValidateProgram"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglValidateProgramCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform1f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniform1fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform2f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniform2fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform3f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniform3fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform4f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniform4fCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform1i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniform1iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform2i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniform2iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform3i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniform3iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform4i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniform4iCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform1fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniform1fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform2fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniform2fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform3fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniform3fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform4fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniform4fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform1iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniform1ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform2iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniform2ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform3iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniform3ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform4iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniform4ivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UniformMatrix2fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniformMatrix2fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UniformMatrix3fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniformMatrix3fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UniformMatrix4fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniformMatrix4fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "IsShader"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglIsShaderCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "IsProgram"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglIsProgramCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetShaderiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetShaderivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetProgramiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetProgramivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetAttachedShaders"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetAttachedShadersCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetUniformfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetUniformfvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetUniformiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglGetUniformivCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "StencilFuncSeparate"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglStencilFuncSeparateCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "StencilOpSeparate"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglStencilOpSeparateCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "StencilMaskSeparate"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglStencilMaskSeparateCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UniformMatrix2x3fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniformMatrix2x3fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UniformMatrix3x2fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniformMatrix3x2fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UniformMatrix2x4fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniformMatrix2x4fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UniformMatrix4x2fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniformMatrix4x2fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UniformMatrix3x4fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniformMatrix3x4fvCallback));

     Gl->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UniformMatrix4x3fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLglUniformMatrix4x3fvCallback));


      // Again, return the result through the current handle scope.
      return Gl;
}    

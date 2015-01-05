
#include "glesbind.h"

#if defined(V8_GL_USE_GLEW)
#include "GL/glew.h"
#include "glew_desktop_shim.h"
#elif defined(__APPLE__)
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include "gles_desktop_shim.h"
#else
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
// If we're running on desktop OpenGL, some ES 2.0 constants don't exist, or
// are under a name with EXT in them, etc.
#include "gles_desktop_shim.h"
#endif

#include <fstream>
#include <string>
#include <string.h>
using namespace v8;


Persistent<Object> GlesFactory::self_;
Persistent<Context> GlesFactory::gles_persistent_context;
char* GlesFactory::root_path;
// glGenBuffers uses an output parameter to return an array of ints.
void GLESglGenBuffersCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() != 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }

  HandleScope handle_scope(v8::Isolate::GetCurrent());
  GLsizei num_buffers = args[0]->Int32Value();

  GLuint* buffers = new GLuint[num_buffers];
  glGenBuffers(num_buffers, buffers);

  // TODO(deanm): There should be a way to initialize the array faster.
  Local<Array> res = Array::New(v8::Isolate::GetCurrent(), num_buffers);
  for (int i = 0; i < num_buffers; ++i) {
    res->Set(Integer::New(v8::Isolate::GetCurrent(), i), Integer::New(v8::Isolate::GetCurrent(), buffers[i]));
  }

  delete[] buffers;

  args.GetReturnValue().Set(res);
}


void GLESglGenRenderbuffersCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
      if (args.Length() != 1) {
        args.GetReturnValue().SetUndefined();
        return;
      }

      HandleScope handle_scope(v8::Isolate::GetCurrent());
	  GLsizei num_buffers = args[0]->Int32Value();

	  GLuint* buffers = new GLuint[num_buffers];
	  glGenRenderbuffers(num_buffers, buffers);

	  // TODO(deanm): There should be a way to initialize the array faster.
	  Local<Array> res = Array::New(v8::Isolate::GetCurrent(), num_buffers);
	  for (int i = 0; i < num_buffers; ++i) {
	    res->Set(Integer::New(v8::Isolate::GetCurrent(), i), Integer::New(v8::Isolate::GetCurrent(), buffers[i]));
	  }

	  delete[] buffers;

	  args.GetReturnValue().Set(res);
}


void GLESglGenFramebuffersCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
      if (args.Length() != 1) {
        args.GetReturnValue().SetUndefined();
        return;
      }

	  HandleScope handle_scope(v8::Isolate::GetCurrent());
	  GLsizei num_buffers = args[0]->Int32Value();

	  GLuint* buffers = new GLuint[num_buffers];
	  glGenFramebuffers(num_buffers, buffers);

	  // TODO(deanm): There should be a way to initialize the array faster.
	  Local<Array> res = Array::New(v8::Isolate::GetCurrent(), num_buffers);
	  for (int i = 0; i < num_buffers; ++i) {
	    res->Set(Integer::New(v8::Isolate::GetCurrent(), i), Integer::New(v8::Isolate::GetCurrent(), buffers[i]));
	  }

	  delete[] buffers;

	  args.GetReturnValue().Set(res);
}

void GLESglGenTexturesCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() != 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }

  HandleScope handle_scope(v8::Isolate::GetCurrent());
  GLsizei num_textures = args[0]->Int32Value();

  GLuint* textures = new GLuint[num_textures];
  glGenTextures(num_textures, textures);

  Local<Array> res = Array::New(v8::Isolate::GetCurrent(), num_textures);
  for (int i = 0; i < num_textures; ++i) {
    res->Set(Integer::New(v8::Isolate::GetCurrent(), i), Integer::New(v8::Isolate::GetCurrent(), textures[i]));
  }

  delete[] textures;

  args.GetReturnValue().Set(res);
}


// glGetShaderiv uses an output parameter to return an int.
void GLESglGetShaderivCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  unsigned int arg0 = args[0]->Uint32Value();
  int arg1 = args[1]->IntegerValue();

  int out;
  glGetShaderiv((GLuint) arg0, (GLenum) arg1, (GLint*)&out);
  v8::Local<v8::Value> val = v8::Integer::New(v8::Isolate::GetCurrent(), out);
  args.GetReturnValue().Set(val);
}


// We expect to be called with a shader id and a single string.
void GLESglShaderSourceCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() != 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }

  HandleScope handle_scope(v8::Isolate::GetCurrent());
  GLuint shader_id = args[0]->Uint32Value();
  // GLSL source is defined as an ASCII subset.
  v8::String::Utf8Value code_ascii(args[1]);
  if (!*code_ascii){
    args.GetReturnValue().SetUndefined();
    return;
  }

  const char* code_str = *code_ascii;
  GLsizei code_len = code_ascii.length();
  glShaderSource(shader_id, 1, &code_str, &code_len);

  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}


void GLESglVertexAttribPointerCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() != 6) {
    args.GetReturnValue().SetUndefined();
    return;
  }

  HandleScope handle_scope(v8::Isolate::GetCurrent());

  unsigned int index = args[0]->Uint32Value();
  unsigned int size = args[1]->Uint32Value();
  unsigned int type = args[2]->Uint32Value();
  unsigned int normalized = args[3]->Uint32Value();
  int stride = args[4]->IntegerValue();
  void* ans;

  if(args[5]->IsArray()) {
	  Handle<Array> data = Handle<Array>::Cast(args[5]);
	  //I guess most of these types could be thrown away
	  switch(type) {
//		  case GL_BYTE:
//			  GLbyte* arg1 = new  GLbyte[data->Length()];
//			  for (unsigned j = 0; j < data->Length(); j++) {
//			      Handle<Value> arg(data->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
//			      arg1[j] = (GLbyte)arg->IntegerValue();
//			  }
//			  ans = (void *)arg1;
//			  break;
//
//		  case GL_UNSIGNED_BYTE:
//			  GLubyte* arg1 = new  GLubyte[data->Length()];
//			  for (unsigned j = 0; j < data->Length(); j++) {
//			      Handle<Value> arg(data->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
//			      arg1[j] = (GLubyte)arg->Uint32Value();
//			  }
//			  ans = (void *)arg1;
//			  break;

		  case GL_SHORT:
		  {
			  GLshort* arg1 = new  GLshort[data->Length()];
			  for (unsigned j = 0; j < data->Length(); j++) {
			      Handle<Value> arg(data->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
			      arg1[j] = (GLshort)arg->IntegerValue();
			  }
			  ans = (void *)arg1;
		  }
		  break;
		  case GL_UNSIGNED_SHORT:
		  {
			  GLushort* arg1 = new  GLushort[data->Length()];
			  for (unsigned j = 0; j < data->Length(); j++) {
			      Handle<Value> arg(data->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
			      arg1[j] = (GLushort)arg->Uint32Value();
			  }
			  ans = (void *)arg1;
		  }
		  break;

		  case GL_FLOAT:
		  {
			  GLfloat* arg1 = new  GLfloat[data->Length()];
			  for (unsigned j = 0; j < data->Length(); j++) {
			      Handle<Value> arg(data->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
			      arg1[j] = (GLfloat)arg->NumberValue();
			  }
			  ans = (void *)arg1;
		  }
		  break;

//		  case GL_FIXED:
//		  {
//			  GLfixed* arg1 = new  GLfixed[data->Length()];
//			  for (unsigned j = 0; j < data->Length(); j++) {
//			      Handle<Value> arg(data->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
//			      arg1[j] = (GLfixed)arg->IntegerValue();
//			  }
//			  ans = (void *)arg1;
//		  }
//		  break;

		  default:
            args.GetReturnValue().SetUndefined();
            return;
	  }
  } else {
	  ans = (void *)args[5]->IntegerValue();
  }

  glVertexAttribPointer((GLuint)index,
		  (GLint)size,
		  (GLenum)type,
		  (GLboolean)normalized,
		  (GLsizei)stride,
		  (const void*)ans);

  //should I delete[] ans?

  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}

void GLESglDrawElementsCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() != 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }

  HandleScope handle_scope(v8::Isolate::GetCurrent());
  unsigned int mode  = args[0]->Uint32Value();
  int count = args[1]->IntegerValue();
  unsigned int type  = args[2]->Uint32Value();
  void* ans;

  if(args[3]->IsArray()) {
	  Handle<Array> data = Handle<Array>::Cast(args[3]);
	  switch(type) {
		  case GL_UNSIGNED_SHORT:
		  {
			  GLushort* arg1 = new  GLushort[data->Length()];
			  for (unsigned j = 0; j < data->Length(); j++) {
			      Handle<Value> arg(data->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
			      arg1[j] = (GLushort)arg->Uint32Value();
			  }
			  ans = (void *)arg1;
		  }
		  break;

		  default:
            args.GetReturnValue().SetUndefined();
            return;
	  }
  } else {
	  ans = (void *)args[3]->IntegerValue();
  }

  glDrawElements((GLenum)mode,
		  (GLsizei)count,
		  (GLenum)type,
		  (const GLvoid*)ans);

  //should I delete[] ans?

  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}

//Accepts GL_UNSIGNED_SHORT and GL_FLOAT as types
//TODO(nico): deal with interleaved data
void GLESglBufferDataCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() != 4 || !args[1]->IsArray()) {
    args.GetReturnValue().SetUndefined();
    return;
  }

  unsigned int target  = args[0]->Uint32Value();
  unsigned int type = args[2]->Uint32Value();
  unsigned int usage  = args[3]->Uint32Value();
  Handle<Array> data = Handle<Array>::Cast(args[1]);
  unsigned int len = data->Length();

  if (type == GL_FLOAT) {
    GLfloat* arg1 = new GLfloat[len];
    for (unsigned j = 0; j < len; j++) {
        Handle<Value> arg(data->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
        arg1[j] = (GLfloat)arg->NumberValue();
    }
    glBufferData((GLenum)target,
                 (GLsizeiptr)(len * sizeof(*arg1)),
                 (const void*)arg1,
                 (GLenum)usage);
    delete[] arg1;
  } else if (type == GL_UNSIGNED_SHORT) {
    GLushort* arg1 = new GLushort[len];
    for (unsigned j = 0; j < len; j++) {
      Handle<Value> arg(data->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      arg1[j] = (GLushort)arg->Uint32Value();
    }
    glBufferData((GLenum)target,
                 (GLsizeiptr)(len * sizeof(*arg1)),
                 (const void*)arg1,
                 (GLenum)usage);
    delete[] arg1;
  }

  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}


//Accepts GL_UNSIGNED_SHORT and GL_FLOAT as types
//TODO(nico): deal with interleaved data
void GLESglBufferSubDataCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() != 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }

  HandleScope handle_scope(v8::Isolate::GetCurrent());
  unsigned int target  = args[0]->Uint32Value();
  unsigned int offset = args[1]->Uint32Value();
  unsigned int type  = args[3]->Uint32Value();

  void* ans;
  if(args[2]->IsArray()) {
	  Handle<Array> data = Handle<Array>::Cast(args[2]);
	  unsigned int len = data->Length();

	  switch(type) {
		  case GL_FLOAT:
		  {
			  GLfloat* arg1 = new  GLfloat[len];
			  for (unsigned j = 0; j < data->Length(); j++) {
			      Handle<Value> arg(data->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
			      arg1[j] = (GLfloat)arg->NumberValue();
			  }
			  ans = (void *)arg1;
		  }
		  break;

		  case GL_UNSIGNED_SHORT:
		  {
			  GLushort* arg1 = new  GLushort[len];
			  for (unsigned j = 0; j < data->Length(); j++) {
			      Handle<Value> arg(data->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
			      arg1[j] = (GLushort)arg->Uint32Value();
			  }
			  ans = (void *)arg1;
		  }
		  break;

		  default:
            args.GetReturnValue().SetUndefined();
            return;

	  }

	  glBufferSubData((GLenum)target,
			  (GLintptr)offset,
			  (GLsizeiptr)len,
			  (const void*)ans);

	  //should I delete[] ans?
  }

  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}

void GLESglReadPixelsCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() != 6) {
    args.GetReturnValue().SetUndefined();
    return;
  }

  HandleScope handle_scope(v8::Isolate::GetCurrent());
  int x = args[0]->IntegerValue();
  int y = args[1]->IntegerValue();
  unsigned width = args[2]->Uint32Value();
  unsigned height = args[3]->Uint32Value();
  unsigned format = args[4]->Uint32Value();
  unsigned type = args[5]->Uint32Value();

  //TODO(nico): should support other formats also
  if(format == GL_RGB && type == GL_UNSIGNED_BYTE) {
	  unsigned len = width * height * 3;
	  GLubyte *ans = new GLubyte[len];
	  glReadPixels((GLint)x,
			  (GLint)y,
			  (GLsizei)width,
			  (GLsizei)height,
			  (GLenum)format,
			  (GLenum)type, ans);

	  Local<Array> res = Array::New(v8::Isolate::GetCurrent(), len);
	  for (unsigned i = 0; i < len; ++i) {
	    res->Set(Integer::New(v8::Isolate::GetCurrent(), i), Integer::New(v8::Isolate::GetCurrent(), ans[i]));
	  }

	  delete[] ans;
	  args.GetReturnValue().Set(res);
  }

  args.GetReturnValue().SetUndefined();
}

void GLESglGetActiveAttribCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() != 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }

  HandleScope handle_scope(v8::Isolate::GetCurrent());

  unsigned program = args[0]->Uint32Value();
  unsigned index = args[1]->Uint32Value();

  char name[256];
  int length = 0;
  int size = 0;
  unsigned type = 0;

  glGetActiveAttrib((GLuint)program,
		  (GLuint)index,
		  (GLsizei)sizeof(name),
		  (GLsizei*)&length,
		  (GLint*)&size,
		  (GLenum*)&type,
		  (GLchar*)name);

  Handle<Object> ans = Object::New(v8::Isolate::GetCurrent());
  ans->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "type"), Uint32::New(v8::Isolate::GetCurrent(), type));
  ans->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "size"), Integer::New(v8::Isolate::GetCurrent(), size));
  ans->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "name"), String::NewFromUtf8(v8::Isolate::GetCurrent(), name, v8::String::kNormalString, length));
  args.GetReturnValue().Set(ans);
}

void GLESglGetActiveUniformCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() != 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }

  HandleScope handle_scope(v8::Isolate::GetCurrent());

  unsigned program = args[0]->Uint32Value();
  unsigned index = args[1]->Uint32Value();

  char name[256];
  int length = 0;
  int size = 0;
  unsigned type = 0;

  glGetActiveUniform((GLuint)program,
		  (GLuint)index,
		  (GLsizei)sizeof(name),
		  (GLsizei*)&length,
		  (GLint*)&size,
		  (GLenum*)&type,
		  (GLchar*)name);

  // Create a template for the answer object that'll hold
  // type/size/name as properties
  Handle<Object> ans = Object::New(v8::Isolate::GetCurrent());
  ans->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "type"), Uint32::New(v8::Isolate::GetCurrent(), type));
  ans->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "size"), Integer::New(v8::Isolate::GetCurrent(), size));
  ans->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "name"), String::NewFromUtf8(v8::Isolate::GetCurrent(), name));
  args.GetReturnValue().Set(ans);
}

void GLESglGetAttachedShadersCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
      if (args.Length() != 1) {
        args.GetReturnValue().SetUndefined();
        return;
      }

  HandleScope handle_scope(v8::Isolate::GetCurrent());
  unsigned program = args[0]->Uint32Value();

  int maxcount = 500;
  int count = 0;
  unsigned* shaders = new unsigned[maxcount];

  glGetAttachedShaders((GLuint)program,
		  (GLsizei)maxcount,
		  (GLsizei*)&count,
		  (GLuint*)shaders);

  Local<Array> res = Array::New(v8::Isolate::GetCurrent(), count);
  for (int i = 0; i < count; ++i) {
    res->Set(Integer::New(v8::Isolate::GetCurrent(), i), Uint32::New(v8::Isolate::GetCurrent(), shaders[i]));
  }

  delete[] shaders;

  args.GetReturnValue().Set(res);
}

void GLESglGetBufferParameterivCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned target = args[0]->IntegerValue();
  unsigned pname = args[1]->IntegerValue();
  int ans = 0;
  //TODO(nico): does this return an array or just GLint?
  glGetBufferParameteriv((GLenum)target,
		  (GLenum)pname,
		  (GLint*)&ans);

  args.GetReturnValue().Set(Integer::New(v8::Isolate::GetCurrent(), ans));
}

//GetBooleanv, GetIntegerv, GetString, GetFloatv, GetDoublev should map here.
void GLESglGetParameterCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned pname = args[0]->Uint32Value();


  switch(pname) {
  //return 1 int value
  case GL_ALPHA_TEST_FUNC:
  case GL_ACCUM_ALPHA_BITS:
  case GL_ACCUM_BLUE_BITS:
  case GL_ACCUM_GREEN_BITS:
  case GL_ACCUM_RED_BITS:
  case GL_ALPHA_BITS:
  case GL_ATTRIB_STACK_DEPTH:
  case GL_AUX_BUFFERS:
  case GL_BLEND_DST:
  case GL_BLEND_EQUATION_EXT:
  case GL_BLEND_SRC:
  case GL_BLUE_BITS:
  case GL_SUBPIXEL_BITS:
  case GL_CLIENT_ATTRIB_STACK_DEPTH:
  case GL_COLOR_ARRAY_SIZE:
  case GL_COLOR_ARRAY_STRIDE:
  case GL_COLOR_ARRAY_TYPE:
  case GL_COLOR_MATERIAL_FACE:
  case GL_COLOR_MATERIAL_PARAMETER:
  case GL_CULL_FACE_MODE:
  case GL_DEPTH_BITS:
  case GL_DEPTH_FUNC:
  case GL_DRAW_BUFFER:
  case GL_EDGE_FLAG_ARRAY_STRIDE:
  case GL_FOG_HINT:
  case GL_FOG_MODE:
  case GL_FRONT_FACE:
  case GL_GREEN_BITS:
  case GL_INDEX_ARRAY_STRIDE:
  case GL_INDEX_ARRAY_TYPE:
  case GL_INDEX_BITS:
  case GL_INDEX_WRITEMASK:
  case GL_LINE_SMOOTH_HINT:
  case GL_LINE_STIPPLE_PATTERN:
  case GL_LINE_STIPPLE_REPEAT:
  case GL_LIST_BASE:
  case GL_LIST_INDEX: //name of the display list
  case GL_LIST_MODE:
  case GL_LOGIC_OP_MODE:
  case GL_MAP1_GRID_SEGMENTS:
  case GL_MATRIX_MODE:
  case GL_MAX_CLIENT_ATTRIB_STACK_DEPTH:
  case GL_MAX_ATTRIB_STACK_DEPTH:
  case GL_MAX_CLIP_PLANES:
  case GL_MAX_EVAL_ORDER:
  case GL_MAX_LIGHTS:
  case GL_MAX_LIST_NESTING:
  case GL_MAX_MODELVIEW_STACK_DEPTH:
  case GL_MAX_NAME_STACK_DEPTH:
  case GL_MAX_PIXEL_MAP_TABLE:
  case GL_MAX_PROJECTION_STACK_DEPTH:
  case GL_MAX_TEXTURE_SIZE:
  case GL_MAX_TEXTURE_STACK_DEPTH:
  case GL_MODELVIEW_STACK_DEPTH:
  case GL_NAME_STACK_DEPTH:
  case GL_NORMAL_ARRAY_STRIDE:
  case GL_NORMAL_ARRAY_TYPE:
  case GL_PACK_ALIGNMENT:
  case GL_PACK_ROW_LENGTH:
  case GL_PACK_SKIP_PIXELS:
  case GL_PACK_SKIP_ROWS:
  case GL_PERSPECTIVE_CORRECTION_HINT:
  case GL_PIXEL_MAP_A_TO_A_SIZE:
  case GL_PIXEL_MAP_B_TO_B_SIZE:
  case GL_PIXEL_MAP_G_TO_G_SIZE:
  case GL_PIXEL_MAP_I_TO_A_SIZE:
  case GL_PIXEL_MAP_I_TO_B_SIZE:
  case GL_PIXEL_MAP_I_TO_G_SIZE:
  case GL_PIXEL_MAP_I_TO_I_SIZE:
  case GL_PIXEL_MAP_I_TO_R_SIZE:
  case GL_PIXEL_MAP_R_TO_R_SIZE:
  case GL_PIXEL_MAP_S_TO_S_SIZE:
  case GL_POINT_SMOOTH_HINT:
  case GL_POLYGON_SMOOTH_HINT:
  case GL_PROJECTION_STACK_DEPTH:
  case GL_RED_BITS:
  case GL_RENDER_MODE:
  case GL_SHADE_MODEL:
  case GL_STENCIL_BITS:
  case GL_STENCIL_CLEAR_VALUE:
  case GL_STENCIL_FAIL:
  case GL_STENCIL_FUNC:
  case GL_STENCIL_PASS_DEPTH_FAIL:
  case GL_STENCIL_PASS_DEPTH_PASS:
  case GL_STENCIL_REF:
  case GL_STENCIL_VALUE_MASK:
  case GL_STENCIL_WRITEMASK:
//  case GL_TEXTURE_1D_BINDING:
//  case GL_TEXTURE_2D_BINDING:
  case GL_TEXTURE_COORD_ARRAY_SIZE:
  case GL_TEXTURE_COORD_ARRAY_STRIDE:
  case GL_TEXTURE_COORD_ARRAY_TYPE:
  case GL_TEXTURE_STACK_DEPTH:
  case GL_UNPACK_ALIGNMENT:
  case GL_UNPACK_ROW_LENGTH:
  case GL_UNPACK_SKIP_PIXELS:
  case GL_UNPACK_SKIP_ROWS:
  case GL_VERTEX_ARRAY_SIZE:
  case GL_VERTEX_ARRAY_STRIDE:
  case GL_VERTEX_ARRAY_TYPE:
  {
	  int ans = 0;
	  glGetIntegerv((GLenum)pname, (GLint*)&ans);
	  args.GetReturnValue().Set(Integer::New(v8::Isolate::GetCurrent(), ans));
  }
  //2 values int
  case GL_LINE_WIDTH_RANGE:
  case GL_MAP2_GRID_SEGMENTS:
  case GL_MAX_VIEWPORT_DIMS:
  case GL_POLYGON_MODE:
  {
	  int* ans = new int[2];
	  glGetIntegerv((GLenum)pname, ans);

	  Local<Array> res = Array::New(v8::Isolate::GetCurrent(), 2);
	  for (int i = 0; i < 2; ++i) {
	    res->Set(Integer::New(v8::Isolate::GetCurrent(), i), Integer::New(v8::Isolate::GetCurrent(), ans[i]));
	  }

	  delete[] ans;

	  args.GetReturnValue().Set(res);
  }
  //4 values int
  case GL_SCISSOR_BOX:
  case GL_VIEWPORT:
  {
	  int* ans = new int[4];
	  glGetIntegerv((GLenum)pname, ans);

	  Local<Array> res = Array::New(v8::Isolate::GetCurrent(), 4);
	  for (int i = 0; i < 4; ++i) {
	    res->Set(Integer::New(v8::Isolate::GetCurrent(), i), Integer::New(v8::Isolate::GetCurrent(), ans[i]));
	  }

	  delete[] ans;

	  args.GetReturnValue().Set(res);
  }

  //1 value boolean
  case GL_ALPHA_TEST:
  case GL_AUTO_NORMAL:
  case GL_BLEND:
  case GL_DEPTH_TEST:
//  case GL_CLIP_PLANEi:
  case GL_COLOR_ARRAY:
  case GL_COLOR_LOGIC_OP:
  case GL_COLOR_MATERIAL:
  case GL_CULL_FACE:
  case GL_CURRENT_RASTER_POSITION_VALID:
  case GL_DEPTH_WRITEMASK:
  case GL_DITHER:
  case GL_DOUBLEBUFFER:
  case GL_EDGE_FLAG:
  case GL_EDGE_FLAG_ARRAY:
  case GL_FOG:
  case GL_INDEX_ARRAY:
  case GL_INDEX_LOGIC_OP:
  case GL_INDEX_MODE:
//  case GL_LIGHTi:
  case GL_LIGHTING:
  case GL_LIGHT_MODEL_LOCAL_VIEWER:
  case GL_LIGHT_MODEL_TWO_SIDE:
  case GL_LINE_SMOOTH:
  case GL_LINE_STIPPLE:
  case GL_MAP1_COLOR_4:
  case GL_MAP1_INDEX:
  case GL_MAP1_NORMAL:
  case GL_MAP1_TEXTURE_COORD_1:
  case GL_MAP1_TEXTURE_COORD_2:
  case GL_MAP1_TEXTURE_COORD_3:
  case GL_MAP1_TEXTURE_COORD_4:
  case GL_MAP1_VERTEX_3:
  case GL_MAP1_VERTEX_4:
  case GL_MAP2_COLOR_4:
  case GL_MAP2_INDEX:
  case GL_MAP2_NORMAL:
  case GL_MAP2_TEXTURE_COORD_1:
  case GL_MAP2_TEXTURE_COORD_2:
  case GL_MAP2_TEXTURE_COORD_3:
  case GL_MAP2_TEXTURE_COORD_4:
  case GL_MAP2_VERTEX_3:
  case GL_MAP2_VERTEX_4:
  case GL_MAP_COLOR:
  case GL_MAP_STENCIL:
  case GL_NORMAL_ARRAY:
  case GL_NORMALIZE:
  case GL_PACK_LSB_FIRST:
  case GL_PACK_SWAP_BYTES:
  case GL_POINT_SMOOTH:
  case GL_POLYGON_OFFSET_FILL:
  case GL_POLYGON_OFFSET_LINE:
  case GL_POLYGON_OFFSET_POINT:
  case GL_POLYGON_SMOOTH:
  case GL_POLYGON_STIPPLE:
  case GL_READ_BUFFER:
  case GL_RGBA_MODE:
  case GL_SCISSOR_TEST:
  case GL_STENCIL_TEST:
  case GL_STEREO:
  case GL_TEXTURE_1D:
  case GL_TEXTURE_2D:
  case GL_TEXTURE_COORD_ARRAY:
  case GL_TEXTURE_GEN_Q:
  case GL_TEXTURE_GEN_R:
  case GL_TEXTURE_GEN_S:
  case GL_TEXTURE_GEN_T:
  case GL_UNPACK_LSB_FIRST:
  case GL_VERTEX_ARRAY:
  case GL_UNPACK_SWAP_BYTES:
  {
	  GLboolean ans = 0;
	  glGetBooleanv((GLenum)pname, &ans);
	  args.GetReturnValue().Set(Boolean::New(v8::Isolate::GetCurrent(), ans != GL_FALSE));
  }

  //1 value float
  case GL_ALPHA_BIAS:
  case GL_ALPHA_SCALE:
  case GL_BLUE_BIAS:
  case GL_BLUE_SCALE:
  case GL_RED_BIAS:
  case GL_RED_SCALE:
  case GL_GREEN_BIAS:
  case GL_GREEN_SCALE:
  case GL_DEPTH_BIAS:
  case GL_DEPTH_SCALE:
  case GL_ALPHA_TEST_REF:
  case GL_ZOOM_X:
  case GL_ZOOM_Y:
  case GL_CURRENT_INDEX:
  case GL_CURRENT_RASTER_DISTANCE:
  case GL_CURRENT_RASTER_INDEX:
  case GL_DEPTH_CLEAR_VALUE:
  case GL_FOG_DENSITY:
  case GL_FOG_END:
  case GL_FOG_INDEX:
  case GL_FOG_START:
  case GL_INDEX_CLEAR_VALUE:
  case GL_INDEX_OFFSET:
  case GL_INDEX_SHIFT:
  case GL_LINE_WIDTH:
  case GL_LINE_WIDTH_GRANULARITY:
  case GL_POINT_SIZE:
  case GL_POINT_SIZE_GRANULARITY:
  {
	  float ans = 0.0f;
	  glGetFloatv((GLenum)pname, &ans);
	  args.GetReturnValue().Set(Number::New(v8::Isolate::GetCurrent(), ans));
  }

  //4 values float
  case GL_BLEND_COLOR_EXT:
  case GL_ACCUM_CLEAR_VALUE:
  case GL_COLOR_CLEAR_VALUE:
  case GL_CURRENT_COLOR:
  case GL_CURRENT_RASTER_COLOR:
  case GL_CURRENT_RASTER_POSITION:
  case GL_CURRENT_RASTER_TEXTURE_COORDS:
  case GL_CURRENT_TEXTURE_COORDS:
  case GL_FOG_COLOR:
  case GL_LIGHT_MODEL_AMBIENT:
  case GL_MAP2_GRID_DOMAIN:
  case GL_POLYGON_OFFSET_FACTOR:
  case GL_POLYGON_OFFSET_UNITS:
  {
	  float* ans = new float[4];
	  glGetFloatv((GLenum)pname, ans);

	  Local<Array> res = Array::New(v8::Isolate::GetCurrent(), 4);
	  for (int i = 0; i < 4; ++i) {
	    res->Set(Integer::New(v8::Isolate::GetCurrent(), i), Number::New(v8::Isolate::GetCurrent(), ans[i]));
	  }

	  delete[] ans;

	  args.GetReturnValue().Set(res);
  }

   //3 values float
  case GL_CURRENT_NORMAL:
  {
	  float* ans = new float[3];
	  glGetFloatv((GLenum)pname, ans);

	  Local<Array> res = Array::New(v8::Isolate::GetCurrent(), 3);
	  for (int i = 0; i < 3; ++i) {
	    res->Set(Integer::New(v8::Isolate::GetCurrent(), i), Number::New(v8::Isolate::GetCurrent(), ans[i]));
	  }

	  delete[] ans;

	  args.GetReturnValue().Set(res);
  }

  //2 values float
  case GL_DEPTH_RANGE:
  case GL_MAP1_GRID_DOMAIN:
  case GL_POINT_SIZE_RANGE:
  {
	  float* ans = new float[2];
	  glGetFloatv((GLenum)pname, ans);

	  Local<Array> res = Array::New(v8::Isolate::GetCurrent(), 2);
	  for (int i = 0; i < 2; ++i) {
	    res->Set(Integer::New(v8::Isolate::GetCurrent(), i), Number::New(v8::Isolate::GetCurrent(), ans[i]));
	  }

	  delete[] ans;

	  args.GetReturnValue().Set(res);
  }

  //16 values float
  case GL_MODELVIEW_MATRIX:
  case GL_PROJECTION_MATRIX:
  case GL_TEXTURE_MATRIX:
  {
	  float* ans = new float[16];
	  glGetFloatv((GLenum)pname, ans);

	  Local<Array> res = Array::New(v8::Isolate::GetCurrent(), 16);
	  for (int i = 0; i < 16; ++i) {
	    res->Set(Integer::New(v8::Isolate::GetCurrent(), i), Number::New(v8::Isolate::GetCurrent(), ans[i]));
	  }

	  delete[] ans;

	  args.GetReturnValue().Set(res);
  }

  //4 values boolean
  case GL_COLOR_WRITEMASK:
  {
	  GLboolean* ans = new GLboolean[4];
	  glGetBooleanv((GLenum)pname, ans);

	  Local<Array> res = Array::New(v8::Isolate::GetCurrent(), 4);
	  for (int i = 0; i < 4; ++i) {
	    res->Set(Integer::New(v8::Isolate::GetCurrent(), i), Boolean::New(v8::Isolate::GetCurrent(), ans[i] != GL_FALSE));
	  }

	  delete[] ans;

	  args.GetReturnValue().Set(res);
  }

  }
  args.GetReturnValue().SetUndefined();
}


void GLESglGetProgramivCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() != 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned program = args[0]->Uint32Value();
  unsigned pname = args[1]->Uint32Value();
  int ans;

  //TODO(nico): I haven't seen any case where this function might return
  //an array.
  glGetProgramiv((GLuint)program, (GLenum)pname, (GLint*) &ans);

  args.GetReturnValue().Set(Integer::New(v8::Isolate::GetCurrent(), ans));
}

void GLESglGetProgramInfoLogCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {

  if (args.Length() != 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned program = args[0]->Uint32Value();

  //query string length
  int len = 0;
  glGetProgramiv((GLuint)program, GL_INFO_LOG_LENGTH, &len);

  char* log = new char[len];
  glGetProgramInfoLog((GLuint)program, (GLsizei)len, NULL, log);

  args.GetReturnValue().Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), log));
}

void GLESglGetTexParameterCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {

  if (args.Length() != 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned target = args[0]->Uint32Value();
  unsigned pname = args[1]->Uint32Value();

  switch(pname) {
  //1 int
  case GL_TEXTURE_MAG_FILTER:
  case GL_TEXTURE_MIN_FILTER:
  case GL_TEXTURE_WRAP_S:
  case GL_TEXTURE_WRAP_T:
  {
	  int ans = 0;
	  glTexParameteriv((GLenum)target, (GLenum)pname, (GLint*) &ans);
	  args.GetReturnValue().Set(Integer::New(v8::Isolate::GetCurrent(), ans));
  }
	  //4 floats
  case GL_TEXTURE_BORDER_COLOR:
  {
	  float* ans = new float[4];
	  glTexParameterfv((GLenum)target, (GLenum)pname, (GLfloat*) ans);

	  Local<Array> res = Array::New(v8::Isolate::GetCurrent(), 4);
	  for (int i = 0; i < 4; ++i) {
	    res->Set(Integer::New(v8::Isolate::GetCurrent(), i), Number::New(v8::Isolate::GetCurrent(), ans[i]));
	  }

	  delete[] ans;

	  args.GetReturnValue().Set(res);
  }
	  //1 float
  case GL_TEXTURE_PRIORITY:
  {
	  float ans = 0;
	  glTexParameterfv((GLenum)target, (GLenum)pname, (GLfloat*) &ans);
	  args.GetReturnValue().Set(Number::New(v8::Isolate::GetCurrent(), ans));
  }
	  //1 boolean
  case GL_TEXTURE_RESIDENT:
  {
	  int ans = 0;
	  glTexParameteriv((GLenum)target, (GLenum)pname, (GLint*) &ans);
	  args.GetReturnValue().Set(Boolean::New(v8::Isolate::GetCurrent(), ans != GL_FALSE));
  }

  }
  args.GetReturnValue().SetUndefined();
}

void GLESglGetVertexAttribCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {

  if (args.Length() != 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned index = args[0]->Uint32Value();
  unsigned pname = args[1]->Uint32Value();

  switch(pname) {
  //1 int value
  case GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING:
  case GL_VERTEX_ATTRIB_ARRAY_SIZE:
  case GL_VERTEX_ATTRIB_ARRAY_STRIDE:
  case GL_VERTEX_ATTRIB_ARRAY_TYPE:
  {
	  GLint ans = 0;
	  glGetVertexAttribiv((GLuint)index, (GLenum)pname, &ans);
	  args.GetReturnValue().Set(Integer::New(v8::Isolate::GetCurrent(), ans));
  }

  //1 boolean value
  case GL_VERTEX_ATTRIB_ARRAY_ENABLED:
  case GL_VERTEX_ATTRIB_ARRAY_NORMALIZED:
  {
	  GLint ans = 0;
	  glGetVertexAttribiv((GLuint)index, (GLenum)pname, &ans);
	  args.GetReturnValue().Set(Boolean::New(v8::Isolate::GetCurrent(), ans != GL_FALSE));
  }

  //4 float values
  case GL_CURRENT_VERTEX_ATTRIB: //(?)
  {
	  GLfloat* ans = new GLfloat[4];
	  glGetVertexAttribfv((GLuint)index, (GLenum)pname, ans);

	  Local<Array> res = Array::New(v8::Isolate::GetCurrent(), 4);
	  for (int i = 0; i < 4; ++i) {
	    res->Set(Integer::New(v8::Isolate::GetCurrent(), i), Integer::New(v8::Isolate::GetCurrent(), ans[i]));
	  }

	  delete[] ans;

	  args.GetReturnValue().Set(res);
  }
  }

  args.GetReturnValue().SetUndefined();
}

void GLESglTexImage2DCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {

  if (args.Length() != 9) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned target = args[0]->Uint32Value();
  int level = args[1]->IntegerValue();
  int internal_format = args[2]->IntegerValue();
  int width = args[3]->IntegerValue();
  int height = args[4]->IntegerValue();
  int border = args[5]->IntegerValue();
  unsigned format = args[6]->Uint32Value();
  unsigned type = args[7]->Uint32Value();

  if(args[8]->IsArray()) {
	  Handle<Array> arr_handle = Handle<Array>::Cast(args[8]);

	  if( type == GL_UNSIGNED_BYTE ) {
		  GLubyte* pixels = new  GLubyte[arr_handle->Length()];
		  for (unsigned j = 0; j < arr_handle->Length(); j++) {
		      Handle<Value> arg(arr_handle->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
		      GLubyte aux = (GLubyte)arg->Uint32Value();
		      pixels[j] = aux;
		  }
		  glTexImage2D((GLenum)target,
				  (GLint)level,
				  (GLenum)internal_format,
				  (GLsizei)width,
				  (GLsizei)height,
				  (GLint)border,
				  (GLenum)format,
				  (GLenum)type,
				  (const void*)pixels);

		  delete[] pixels;
	  } else if( type == GL_BYTE ) {
		  GLbyte* pixels = new  GLbyte[arr_handle->Length()];
		  for (unsigned j = 0; j < arr_handle->Length(); j++) {
		      Handle<Value> arg(arr_handle->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
		      GLbyte aux = (GLbyte)arg->Uint32Value();
		      pixels[j] = aux;
		  }
		  glTexImage2D((GLenum)target,
				  (GLint)level,
				  (GLenum)internal_format,
				  (GLsizei)width,
				  (GLsizei)height,
				  (GLint)border,
				  (GLenum)format,
				  (GLenum)type,
				  (const void*)pixels);

		  delete[] pixels;

	  } else if( type == GL_BITMAP ) {
		  GLbitfield* pixels = new  GLbitfield[arr_handle->Length()];
		  for (unsigned j = 0; j < arr_handle->Length(); j++) {
		      Handle<Value> arg(arr_handle->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
		      GLbitfield aux = (GLbitfield)arg->IntegerValue();
		      pixels[j] = aux;
		  }
		  glTexImage2D((GLenum)target,
				  (GLint)level,
				  (GLenum)internal_format,
				  (GLsizei)width,
				  (GLsizei)height,
				  (GLint)border,
				  (GLenum)format,
				  (GLenum)type,
				  (const void*)pixels);

		  delete[] pixels;

	  } else if( type == GL_UNSIGNED_SHORT ) {
		  GLushort* pixels = new  GLushort[arr_handle->Length()];
		  for (unsigned j = 0; j < arr_handle->Length(); j++) {
		      Handle<Value> arg(arr_handle->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
		      GLushort aux = (GLushort)arg->Uint32Value();
		      pixels[j] = aux;
		  }
		  glTexImage2D((GLenum)target,
				  (GLint)level,
				  (GLenum)internal_format,
				  (GLsizei)width,
				  (GLsizei)height,
				  (GLint)border,
				  (GLenum)format,
				  (GLenum)type,
				  (const void*)pixels);

		  delete[] pixels;

	  } else if( type == GL_SHORT ) {
		  GLshort* pixels = new  GLshort[arr_handle->Length()];
		  for (unsigned j = 0; j < arr_handle->Length(); j++) {
		      Handle<Value> arg(arr_handle->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
		      GLshort aux = (GLshort)arg->IntegerValue();
		      pixels[j] = aux;
		  }
		  glTexImage2D((GLenum)target,
				  (GLint)level,
				  (GLenum)internal_format,
				  (GLsizei)width,
				  (GLsizei)height,
				  (GLint)border,
				  (GLenum)format,
				  (GLenum)type,
				  (const void*)pixels);

		  delete[] pixels;

	  } else if( type == GL_UNSIGNED_INT ) {
		  GLuint* pixels = new  GLuint[arr_handle->Length()];
		  for (unsigned j = 0; j < arr_handle->Length(); j++) {
		      Handle<Value> arg(arr_handle->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
		      GLuint aux = (GLuint)arg->Uint32Value();
		      pixels[j] = aux;
		  }
		  glTexImage2D((GLenum)target,
				  (GLint)level,
				  (GLenum)internal_format,
				  (GLsizei)width,
				  (GLsizei)height,
				  (GLint)border,
				  (GLenum)format,
				  (GLenum)type,
				  (const void*)pixels);

		  delete[] pixels;

	  } else if( type == GL_INT ) {
		  GLint* pixels = new  GLint[arr_handle->Length()];
		  for (unsigned j = 0; j < arr_handle->Length(); j++) {
		      Handle<Value> arg(arr_handle->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
		      GLint aux = (GLint)arg->IntegerValue();
		      pixels[j] = aux;
		  }
		  glTexImage2D((GLenum)target,
				  (GLint)level,
				  (GLenum)internal_format,
				  (GLsizei)width,
				  (GLsizei)height,
				  (GLint)border,
				  (GLenum)format,
				  (GLenum)type,
				  (const void*)pixels);

		  delete[] pixels;

	  } else if( type == GL_FLOAT ) {
		  GLfloat* pixels = new  GLfloat[arr_handle->Length()];
		  for (unsigned j = 0; j < arr_handle->Length(); j++) {
		      Handle<Value> arg(arr_handle->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
		      GLfloat aux = (GLfloat)arg->NumberValue();
		      pixels[j] = aux;
		  }
		  glTexImage2D((GLenum)target,
				  (GLint)level,
				  (GLenum)internal_format,
				  (GLsizei)width,
				  (GLsizei)height,
				  (GLint)border,
				  (GLenum)format,
				  (GLenum)type,
				  (const void*)pixels);

		  delete[] pixels;
	  }
  }

  args.GetReturnValue().SetUndefined();
}



void GLESglTexSubImage2DCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {

  if (args.Length() != 9) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned target = args[0]->Uint32Value();
  int level = args[1]->IntegerValue();
  int xoffset = args[2]->IntegerValue();
  int yoffset = args[3]->IntegerValue();
  int width = args[4]->IntegerValue();
  int height = args[5]->IntegerValue();
  unsigned format = args[6]->Uint32Value();
  unsigned type = args[7]->Uint32Value();

  if(args[8]->IsArray()) {
	  Handle<Array> arr_handle = Handle<Array>::Cast(args[8]);

	  switch(type) {
	  case GL_UNSIGNED_BYTE:
	  {
		  GLubyte* pixels = new  GLubyte[arr_handle->Length()];
		  for (unsigned j = 0; j < arr_handle->Length(); j++) {
		      Handle<Value> arg(arr_handle->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
		      GLubyte aux = (GLubyte)arg->Uint32Value();
		      pixels[j] = aux;
		  }
		  glTexSubImage2D((GLenum)target,
				  (GLint)level,
				  (GLint)xoffset,
				  (GLint)yoffset,
				  (GLsizei)width,
				  (GLsizei)height,
				  (GLenum)format,
				  (GLenum)type,
				  (const void*)pixels);

		  delete[] pixels;
	  }
	  break;

	  case GL_BYTE:
	  {
		  GLbyte* pixels = new  GLbyte[arr_handle->Length()];
		  for (unsigned j = 0; j < arr_handle->Length(); j++) {
		      Handle<Value> arg(arr_handle->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
		      GLbyte aux = (GLbyte)arg->Uint32Value();
		      pixels[j] = aux;
		  }
		  glTexSubImage2D((GLenum)target,
				  (GLint)level,
				  (GLint)xoffset,
				  (GLint)yoffset,
				  (GLsizei)width,
				  (GLsizei)height,
				  (GLenum)format,
				  (GLenum)type,
				  (const void*)pixels);

		  delete[] pixels;
	  }
	  break;

	  case GL_BITMAP:
	  {
		  GLbitfield* pixels = new  GLbitfield[arr_handle->Length()];
		  for (unsigned j = 0; j < arr_handle->Length(); j++) {
		      Handle<Value> arg(arr_handle->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
		      GLbitfield aux = (GLbitfield)arg->IntegerValue();
		      pixels[j] = aux;
		  }
		  glTexSubImage2D((GLenum)target,
				  (GLint)level,
				  (GLint)xoffset,
				  (GLint)yoffset,
				  (GLsizei)width,
				  (GLsizei)height,
				  (GLenum)format,
				  (GLenum)type,
				  (const void*)pixels);

		  delete[] pixels;
	  }
	  break;

	  case GL_UNSIGNED_SHORT:
	  {
		  GLushort* pixels = new  GLushort[arr_handle->Length()];
		  for (unsigned j = 0; j < arr_handle->Length(); j++) {
		      Handle<Value> arg(arr_handle->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
		      GLushort aux = (GLushort)arg->Uint32Value();
		      pixels[j] = aux;
		  }
		  glTexSubImage2D((GLenum)target,
				  (GLint)level,
				  (GLint)xoffset,
				  (GLint)yoffset,
				  (GLsizei)width,
				  (GLsizei)height,
				  (GLenum)format,
				  (GLenum)type,
				  (const void*)pixels);

		  delete[] pixels;
	  }
	  break;

	  case GL_SHORT:
	  {
		  GLshort* pixels = new  GLshort[arr_handle->Length()];
		  for (unsigned j = 0; j < arr_handle->Length(); j++) {
		      Handle<Value> arg(arr_handle->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
		      GLshort aux = (GLshort)arg->IntegerValue();
		      pixels[j] = aux;
		  }
		  glTexSubImage2D((GLenum)target,
				  (GLint)level,
				  (GLint)xoffset,
				  (GLint)yoffset,
				  (GLsizei)width,
				  (GLsizei)height,
				  (GLenum)format,
				  (GLenum)type,
				  (const void*)pixels);

		  delete[] pixels;
	  }
	  break;

	  case GL_UNSIGNED_INT:
	  {
		  GLuint* pixels = new  GLuint[arr_handle->Length()];
		  for (unsigned j = 0; j < arr_handle->Length(); j++) {
		      Handle<Value> arg(arr_handle->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
		      GLuint aux = (GLuint)arg->Uint32Value();
		      pixels[j] = aux;
		  }
		  glTexSubImage2D((GLenum)target,
				  (GLint)level,
				  (GLint)xoffset,
				  (GLint)yoffset,
				  (GLsizei)width,
				  (GLsizei)height,
				  (GLenum)format,
				  (GLenum)type,
				  (const void*)pixels);

		  delete[] pixels;
	  }
	  break;

	  case GL_INT:
	  {
		  GLint* pixels = new  GLint[arr_handle->Length()];
		  for (unsigned j = 0; j < arr_handle->Length(); j++) {
		      Handle<Value> arg(arr_handle->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
		      GLint aux = (GLint)arg->IntegerValue();
		      pixels[j] = aux;
		  }
		  glTexSubImage2D((GLenum)target,
				  (GLint)level,
				  (GLint)xoffset,
				  (GLint)yoffset,
				  (GLsizei)width,
				  (GLsizei)height,
				  (GLenum)format,
				  (GLenum)type,
				  (const void*)pixels);

		  delete[] pixels;
	  }
	  break;

	  case GL_FLOAT:
	  {
		  GLfloat* pixels = new  GLfloat[arr_handle->Length()];
		  for (unsigned j = 0; j < arr_handle->Length(); j++) {
		      Handle<Value> arg(arr_handle->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
		      GLfloat aux = (GLfloat)arg->NumberValue();
		      pixels[j] = aux;
		  }
		  glTexSubImage2D((GLenum)target,
				  (GLint)level,
				  (GLint)xoffset,
				  (GLint)yoffset,
				  (GLsizei)width,
				  (GLsizei)height,
				  (GLenum)format,
				  (GLenum)type,
				  (const void*)pixels);

		  delete[] pixels;
	  }
	  break;
	  }
  }

  args.GetReturnValue().SetUndefined();
}


void GLESglGetRenderbufferParameterCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() != 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned target = args[0]->Uint32Value();
  unsigned pname = args[1]->Uint32Value();

  switch(pname) {
  //1 int value
  case GL_RENDERBUFFER_WIDTH:
  case GL_RENDERBUFFER_HEIGHT:
  case GL_RENDERBUFFER_INTERNAL_FORMAT:
  case GL_RENDERBUFFER_RED_SIZE:
  case GL_RENDERBUFFER_GREEN_SIZE:
  case GL_RENDERBUFFER_BLUE_SIZE:
  case GL_RENDERBUFFER_ALPHA_SIZE:
  case GL_RENDERBUFFER_DEPTH_SIZE:
  case  GL_RENDERBUFFER_STENCIL_SIZE:
  {
	  int ans = 0;
	  glGetRenderbufferParameteriv((GLenum)target, (GLenum)pname, (GLint*)&ans);
	  args.GetReturnValue().Set(Integer::New(v8::Isolate::GetCurrent(), ans));
  }
  }

  args.GetReturnValue().SetUndefined();
  return;
}

void GLESglGetFramebufferAttachmentParameterCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() != 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned target = args[0]->Uint32Value();
  unsigned attachment = args[1]->Uint32Value();
  unsigned pname = args[2]->Uint32Value();

//  switch(pname) {
//  case FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE:
//  case FRAMEBUFFER_ATTACHMENT_OBJECT_NAME:
//  case FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL:
//  case FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE:
//  {
	  int ans = 0;
	  glGetFramebufferAttachmentParameteriv((GLenum)target,
			  (GLenum)attachment,
			  (GLenum)pname,
			  (GLint*)&ans);

	  args.GetReturnValue().Set(Integer::New(v8::Isolate::GetCurrent(), ans));
//  }
//  }

  args.GetReturnValue().SetUndefined();
}

void GLESglGetShaderInfoLogCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {

  if (args.Length() != 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned shader = args[0]->Uint32Value();

  //query string length
  int len = 0;
  glGetShaderiv((GLuint)shader, GL_INFO_LOG_LENGTH, &len);

  char* log = new char[len];
  glGetShaderInfoLog((GLuint)shader, (GLsizei)len, NULL, log);

  args.GetReturnValue().Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), log));
}

void GLESglGetShaderSourceCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {

  if (args.Length() != 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned shader = args[0]->Uint32Value();

  //query string length
  int len = 0;
  glGetShaderiv((GLuint)shader, GL_SHADER_SOURCE_LENGTH, &len);

  char* log = new char[len];
  glGetShaderSource((GLuint)shader, (GLsizei)len, NULL, log);

  args.GetReturnValue().Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), log));
}

// We expect to be called with a shader id and a single string.
void GLESglShaderSourceFileCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() != 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }

  HandleScope handle_scope(v8::Isolate::GetCurrent());
  GLuint shader_id = args[0]->Uint32Value();
  // GLSL source is defined as an ASCII subset.
  v8::String::Utf8Value filepath_ascii(args[1]);
  if (!*filepath_ascii) {
    args.GetReturnValue().SetUndefined();
    return;
  }

  char* filepath_str = *filepath_ascii;

  //read the file source
  char* filename = NULL;
  if(filepath_str[0] != '/') {
	  filename = new char[strlen(GlesFactory::root_path) + strlen(filepath_str) +1];
	  strcpy(filename, GlesFactory::root_path);
	  strcat(filename, filepath_str);
  } else {
	  filename = new char[strlen(filepath_str) +1];
	  strcpy(filename, filepath_str);
  }

  std::ifstream in_file(filename);

  if(!in_file.is_open()) {
    args.GetReturnValue().SetUndefined();
    return;
  }

  std::string line, full_text = "";
  while (! in_file.eof() ) {
    std::getline (in_file, line);
    full_text += line + "\n";
  }

  char* ans = new char[full_text.length() +1];
  strcpy(ans, full_text.c_str());

  GLsizei code_len = full_text.length();
  glShaderSource(shader_id, 1, (const GLchar**) &ans, &code_len);

  delete[] ans;
  delete[] filename;

  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}



void GLESglActiveTextureCallback(const FunctionCallbackInfo<Value>& args) {
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
  glActiveTexture((GLenum) arg0);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglAttachShaderCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglBindAttribLocationCallback(const FunctionCallbackInfo<Value>& args) {
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
  String::Utf8Value value2(args[2]);
  char* arg2 = *value2;

  //make call
  glBindAttribLocation((GLuint) arg0, (GLuint) arg1, (const char*) arg2);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglBindBufferCallback(const FunctionCallbackInfo<Value>& args) {
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
  glBindBuffer((GLenum) arg0, (GLuint) arg1);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglBindFramebufferCallback(const FunctionCallbackInfo<Value>& args) {
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
  glBindFramebuffer((GLenum) arg0, (GLuint) arg1);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglBindRenderbufferCallback(const FunctionCallbackInfo<Value>& args) {
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
  glBindRenderbuffer((GLenum) arg0, (GLuint) arg1);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglBindTextureCallback(const FunctionCallbackInfo<Value>& args) {
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
  glBindTexture((GLenum) arg0, (GLuint) arg1);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglBlendColorCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglBlendEquationCallback(const FunctionCallbackInfo<Value>& args) {
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
  glBlendEquation((GLenum) arg0);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglBlendEquationSeparateCallback(const FunctionCallbackInfo<Value>& args) {
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
  glBlendEquationSeparate((GLenum) arg0, (GLenum) arg1);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglBlendFuncCallback(const FunctionCallbackInfo<Value>& args) {
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
  glBlendFunc((GLenum) arg0, (GLenum) arg1);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglBlendFuncSeparateCallback(const FunctionCallbackInfo<Value>& args) {
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
  glBlendFuncSeparate((GLenum) arg0, (GLenum) arg1, (GLenum) arg2, (GLenum) arg3);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglCheckFramebufferStatusCallback(const FunctionCallbackInfo<Value>& args) {
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
  args.GetReturnValue().Set(glCheckFramebufferStatus((GLenum) arg0));
}




void GLESglClearCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglClearColorCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglClearDepthfCallback(const FunctionCallbackInfo<Value>& args) {
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
  glClearDepthf((GLclampf) arg0);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglClearStencilCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglColorMaskCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglCompileShaderCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglCopyTexImage2DCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 8) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  int arg1 = args[1]->IntegerValue();
  unsigned int arg2 = args[2]->Uint32Value();
  int arg3 = args[3]->IntegerValue();
  int arg4 = args[4]->IntegerValue();
  int arg5 = args[5]->IntegerValue();
  int arg6 = args[6]->IntegerValue();
  int arg7 = args[7]->IntegerValue();

  //make call
  glCopyTexImage2D((GLenum) arg0, (GLint) arg1, (GLenum) arg2, (GLint) arg3, (GLint) arg4, (GLsizei) arg5, (GLsizei) arg6, (GLint) arg7);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglCopyTexSubImage2DCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 8) {
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
  int arg5 = args[5]->IntegerValue();
  int arg6 = args[6]->IntegerValue();
  int arg7 = args[7]->IntegerValue();

  //make call
  glCopyTexSubImage2D((GLenum) arg0, (GLint) arg1, (GLint) arg2, (GLint) arg3, (GLint) arg4, (GLint) arg5, (GLsizei) arg6, (GLsizei) arg7);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglCreateProgramCallback(const FunctionCallbackInfo<Value>& args) {
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




void GLESglCreateShaderCallback(const FunctionCallbackInfo<Value>& args) {
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
  args.GetReturnValue().Set(glCreateShader((GLenum) arg0));
}




void GLESglCullFaceCallback(const FunctionCallbackInfo<Value>& args) {
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
  glCullFace((GLenum) arg0);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglDeleteBuffersCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglDeleteFramebuffersCallback(const FunctionCallbackInfo<Value>& args) {
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
  glDeleteFramebuffers((GLsizei) arg0, (const GLuint*) arg1);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglDeleteProgramCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglDeleteRenderbuffersCallback(const FunctionCallbackInfo<Value>& args) {
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
  glDeleteRenderbuffers((GLsizei) arg0, (const GLuint*) arg1);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglDeleteShaderCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglDeleteTexturesCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglDepthFuncCallback(const FunctionCallbackInfo<Value>& args) {
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
  glDepthFunc((GLenum) arg0);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglDepthMaskCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglDepthRangefCallback(const FunctionCallbackInfo<Value>& args) {
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
  glDepthRangef((GLclampf) arg0, (GLclampf) arg1);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglDetachShaderCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglDisableCallback(const FunctionCallbackInfo<Value>& args) {
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
  glDisable((GLenum) arg0);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglDisableVertexAttribArrayCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglDrawArraysCallback(const FunctionCallbackInfo<Value>& args) {
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
  glDrawArrays((GLenum) arg0, (GLint) arg1, (GLsizei) arg2);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglEnableCallback(const FunctionCallbackInfo<Value>& args) {
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
  glEnable((GLenum) arg0);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglEnableVertexAttribArrayCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglFinishCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglFlushCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglFramebufferRenderbufferCallback(const FunctionCallbackInfo<Value>& args) {
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
  glFramebufferRenderbuffer((GLenum) arg0, (GLenum) arg1, (GLenum) arg2, (GLuint) arg3);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglFramebufferTexture2DCallback(const FunctionCallbackInfo<Value>& args) {
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
  int arg4 = args[4]->IntegerValue();

  //make call
  glFramebufferTexture2D((GLenum) arg0, (GLenum) arg1, (GLenum) arg2, (GLuint) arg3, (GLint) arg4);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglFrontFaceCallback(const FunctionCallbackInfo<Value>& args) {
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
  glFrontFace((GLenum) arg0);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglGenerateMipmapCallback(const FunctionCallbackInfo<Value>& args) {
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
  glGenerateMipmap((GLenum) arg0);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglGetAttribLocationCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  String::Utf8Value value1(args[1]);
  char* arg1 = *value1;

  //make call
  args.GetReturnValue().Set(glGetAttribLocation((GLuint) arg0, (const char*) arg1));
}




void GLESglGetBooleanvCallback(const FunctionCallbackInfo<Value>& args) {
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
  GLboolean* arg1 = new GLboolean[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLboolean aux = (GLboolean)arg->Uint32Value();
      arg1[j] = aux;
  }


  //make call
  glGetBooleanv((GLenum) arg0, (GLboolean*) arg1);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglGetErrorCallback(const FunctionCallbackInfo<Value>& args) {
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




void GLESglGetFloatvCallback(const FunctionCallbackInfo<Value>& args) {
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
  GLfloat* arg1 = new GLfloat[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLfloat aux = (GLfloat)arg->NumberValue();
      arg1[j] = aux;
  }


  //make call
  glGetFloatv((GLenum) arg0, (GLfloat*) arg1);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglGetFramebufferAttachmentParameterivCallback(const FunctionCallbackInfo<Value>& args) {
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


  Handle<Array> arrHandle3 = Handle<Array>::Cast(args[3]);
  GLint* arg3 = new GLint[arrHandle3->Length()];
  for (unsigned j = 0; j < arrHandle3->Length(); j++) {
      Handle<Value> arg(arrHandle3->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg3[j] = aux;
  }


  //make call
  glGetFramebufferAttachmentParameteriv((GLenum) arg0, (GLenum) arg1, (GLenum) arg2, (GLint*) arg3);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglGetIntegervCallback(const FunctionCallbackInfo<Value>& args) {
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
  GLint* arg1 = new GLint[arrHandle1->Length()];
  for (unsigned j = 0; j < arrHandle1->Length(); j++) {
      Handle<Value> arg(arrHandle1->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
      GLint aux = (GLint)arg->IntegerValue();
      arg1[j] = aux;
  }


  //make call
  glGetIntegerv((GLenum) arg0, (GLint*) arg1);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglGetUniformivCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglGetUniformLocationCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope handle_scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();
  String::Utf8Value value1(args[1]);
  char* arg1 = *value1;

  //make call
  args.GetReturnValue().Set(glGetUniformLocation((GLuint) arg0, (const char*) arg1));
}




void GLESglHintCallback(const FunctionCallbackInfo<Value>& args) {
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
  glHint((GLenum) arg0, (GLenum) arg1);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglIsBufferCallback(const FunctionCallbackInfo<Value>& args) {
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




void GLESglIsEnabledCallback(const FunctionCallbackInfo<Value>& args) {
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
  args.GetReturnValue().Set(glIsEnabled((GLenum) arg0));
}




void GLESglIsFramebufferCallback(const FunctionCallbackInfo<Value>& args) {
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
  args.GetReturnValue().Set(glIsFramebuffer((GLuint) arg0));
}




void GLESglIsProgramCallback(const FunctionCallbackInfo<Value>& args) {
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




void GLESglIsRenderbufferCallback(const FunctionCallbackInfo<Value>& args) {
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
  args.GetReturnValue().Set(glIsRenderbuffer((GLuint) arg0));
}




void GLESglIsShaderCallback(const FunctionCallbackInfo<Value>& args) {
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




void GLESglIsTextureCallback(const FunctionCallbackInfo<Value>& args) {
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




void GLESglLineWidthCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglLinkProgramCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglPixelStoreiCallback(const FunctionCallbackInfo<Value>& args) {
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
  glPixelStorei((GLenum) arg0, (GLint) arg1);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglPolygonOffsetCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglRenderbufferStorageCallback(const FunctionCallbackInfo<Value>& args) {
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
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glRenderbufferStorage((GLenum) arg0, (GLenum) arg1, (GLsizei) arg2, (GLsizei) arg3);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglSampleCoverageCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglScissorCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglStencilFuncCallback(const FunctionCallbackInfo<Value>& args) {
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
  unsigned int arg2 = args[2]->Uint32Value();

  //make call
  glStencilFunc((GLenum) arg0, (GLint) arg1, (GLuint) arg2);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglStencilFuncSeparateCallback(const FunctionCallbackInfo<Value>& args) {
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
  int arg2 = args[2]->IntegerValue();
  unsigned int arg3 = args[3]->Uint32Value();

  //make call
  glStencilFuncSeparate((GLenum) arg0, (GLenum) arg1, (GLint) arg2, (GLuint) arg3);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglStencilMaskCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglStencilMaskSeparateCallback(const FunctionCallbackInfo<Value>& args) {
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
  glStencilMaskSeparate((GLenum) arg0, (GLuint) arg1);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglStencilOpCallback(const FunctionCallbackInfo<Value>& args) {
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
  glStencilOp((GLenum) arg0, (GLenum) arg1, (GLenum) arg2);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglStencilOpSeparateCallback(const FunctionCallbackInfo<Value>& args) {
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
  glStencilOpSeparate((GLenum) arg0, (GLenum) arg1, (GLenum) arg2, (GLenum) arg3);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglTexParameterfCallback(const FunctionCallbackInfo<Value>& args) {
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
  double arg2 = args[2]->NumberValue();

  //make call
  glTexParameterf((GLenum) arg0, (GLenum) arg1, (GLfloat) arg2);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglTexParameterfvCallback(const FunctionCallbackInfo<Value>& args) {
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


  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLfloat* arg2 = new  GLfloat[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLfloat aux = ( GLfloat)arg->NumberValue();
      arg2[j] = aux;
  }


  //make call
  glTexParameterfv((GLenum) arg0, (GLenum) arg1, (const GLfloat*) arg2);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglTexParameteriCallback(const FunctionCallbackInfo<Value>& args) {
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
  int arg2 = args[2]->IntegerValue();

  //make call
  glTexParameteri((GLenum) arg0, (GLenum) arg1, (GLint) arg2);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglTexParameterivCallback(const FunctionCallbackInfo<Value>& args) {
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


  Handle<Array> arrHandle2 = Handle<Array>::Cast(args[2]);
   GLint* arg2 = new  GLint[arrHandle2->Length()];
  for (unsigned j = 0; j < arrHandle2->Length(); j++) {
      Handle<Value> arg(arrHandle2->Get(Integer::New(v8::Isolate::GetCurrent(), j)));
       GLint aux = ( GLint)arg->IntegerValue();
      arg2[j] = aux;
  }


  //make call
  glTexParameteriv((GLenum) arg0, (GLenum) arg1, (const GLint*) arg2);
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglUniform1fCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglUniform1fvCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglUniform1iCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglUniform1ivCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglUniform2fCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglUniform2fvCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglUniform2iCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglUniform2ivCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglUniform3fCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglUniform3fvCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglUniform3iCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglUniform3ivCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglUniform4fCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglUniform4fvCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglUniform4iCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglUniform4ivCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglUniformMatrix2fvCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglUniformMatrix3fvCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglUniformMatrix4fvCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglUseProgramCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglValidateProgramCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglVertexAttrib1fCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglVertexAttrib1fvCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglVertexAttrib2fCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglVertexAttrib2fvCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglVertexAttrib3fCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglVertexAttrib3fvCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglVertexAttrib4fCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglVertexAttrib4fvCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




void GLESglViewportCallback(const FunctionCallbackInfo<Value>& args) {
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
  Handle<Object> res(Local<Object>::New(v8::Isolate::GetCurrent(), GlesFactory::self_));
  args.GetReturnValue().Set(res);
}




Handle<ObjectTemplate> GlesFactory::createGles(void) {
      HandleScope handle_scope(v8::Isolate::GetCurrent());

      Handle<ObjectTemplate> Gles = ObjectTemplate::New();
      
      Gles->SetInternalFieldCount(1);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ES_VERSION_2_0"), Uint32::New(v8::Isolate::GetCurrent(), GL_ES_VERSION_2_0), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_BUFFER_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_BUFFER_BIT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_BUFFER_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_BUFFER_BIT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_BUFFER_BIT"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_BUFFER_BIT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FALSE"), Uint32::New(v8::Isolate::GetCurrent(), GL_FALSE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TRUE"), Uint32::New(v8::Isolate::GetCurrent(), GL_TRUE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POINTS"), Uint32::New(v8::Isolate::GetCurrent(), GL_POINTS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINES"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINES), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINE_LOOP"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINE_LOOP), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINE_STRIP"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINE_STRIP), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TRIANGLES"), Uint32::New(v8::Isolate::GetCurrent(), GL_TRIANGLES), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TRIANGLE_STRIP"), Uint32::New(v8::Isolate::GetCurrent(), GL_TRIANGLE_STRIP), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TRIANGLE_FAN"), Uint32::New(v8::Isolate::GetCurrent(), GL_TRIANGLE_FAN), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ZERO"), Uint32::New(v8::Isolate::GetCurrent(), GL_ZERO), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ONE"), Uint32::New(v8::Isolate::GetCurrent(), GL_ONE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SRC_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_SRC_COLOR), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ONE_MINUS_SRC_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_ONE_MINUS_SRC_COLOR), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SRC_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_SRC_ALPHA), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ONE_MINUS_SRC_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_ONE_MINUS_SRC_ALPHA), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DST_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_DST_ALPHA), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ONE_MINUS_DST_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_ONE_MINUS_DST_ALPHA), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DST_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_DST_COLOR), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ONE_MINUS_DST_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_ONE_MINUS_DST_COLOR), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SRC_ALPHA_SATURATE"), Uint32::New(v8::Isolate::GetCurrent(), GL_SRC_ALPHA_SATURATE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FUNC_ADD"), Uint32::New(v8::Isolate::GetCurrent(), GL_FUNC_ADD), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLEND_EQUATION"), Uint32::New(v8::Isolate::GetCurrent(), GL_BLEND_EQUATION), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLEND_EQUATION_RGB"), Uint32::New(v8::Isolate::GetCurrent(), GL_BLEND_EQUATION_RGB), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLEND_EQUATION_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_BLEND_EQUATION_ALPHA), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FUNC_SUBTRACT"), Uint32::New(v8::Isolate::GetCurrent(), GL_FUNC_SUBTRACT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FUNC_REVERSE_SUBTRACT"), Uint32::New(v8::Isolate::GetCurrent(), GL_FUNC_REVERSE_SUBTRACT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLEND_DST_RGB"), Uint32::New(v8::Isolate::GetCurrent(), GL_BLEND_DST_RGB), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLEND_SRC_RGB"), Uint32::New(v8::Isolate::GetCurrent(), GL_BLEND_SRC_RGB), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLEND_DST_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_BLEND_DST_ALPHA), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLEND_SRC_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_BLEND_SRC_ALPHA), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CONSTANT_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_CONSTANT_COLOR), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ONE_MINUS_CONSTANT_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_ONE_MINUS_CONSTANT_COLOR), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CONSTANT_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_CONSTANT_ALPHA), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ONE_MINUS_CONSTANT_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_ONE_MINUS_CONSTANT_ALPHA), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLEND_COLOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_BLEND_COLOR), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ARRAY_BUFFER"), Uint32::New(v8::Isolate::GetCurrent(), GL_ARRAY_BUFFER), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ELEMENT_ARRAY_BUFFER"), Uint32::New(v8::Isolate::GetCurrent(), GL_ELEMENT_ARRAY_BUFFER), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ARRAY_BUFFER_BINDING"), Uint32::New(v8::Isolate::GetCurrent(), GL_ARRAY_BUFFER_BINDING), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ELEMENT_ARRAY_BUFFER_BINDING"), Uint32::New(v8::Isolate::GetCurrent(), GL_ELEMENT_ARRAY_BUFFER_BINDING), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STREAM_DRAW"), Uint32::New(v8::Isolate::GetCurrent(), GL_STREAM_DRAW), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STATIC_DRAW"), Uint32::New(v8::Isolate::GetCurrent(), GL_STATIC_DRAW), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DYNAMIC_DRAW"), Uint32::New(v8::Isolate::GetCurrent(), GL_DYNAMIC_DRAW), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BUFFER_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_BUFFER_SIZE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BUFFER_USAGE"), Uint32::New(v8::Isolate::GetCurrent(), GL_BUFFER_USAGE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURRENT_VERTEX_ATTRIB"), Uint32::New(v8::Isolate::GetCurrent(), GL_CURRENT_VERTEX_ATTRIB), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FRONT"), Uint32::New(v8::Isolate::GetCurrent(), GL_FRONT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BACK"), Uint32::New(v8::Isolate::GetCurrent(), GL_BACK), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FRONT_AND_BACK"), Uint32::New(v8::Isolate::GetCurrent(), GL_FRONT_AND_BACK), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_2D"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_2D), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CULL_FACE"), Uint32::New(v8::Isolate::GetCurrent(), GL_CULL_FACE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLEND"), Uint32::New(v8::Isolate::GetCurrent(), GL_BLEND), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DITHER"), Uint32::New(v8::Isolate::GetCurrent(), GL_DITHER), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_TEST"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_TEST), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_TEST"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_TEST), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SCISSOR_TEST"), Uint32::New(v8::Isolate::GetCurrent(), GL_SCISSOR_TEST), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POLYGON_OFFSET_FILL"), Uint32::New(v8::Isolate::GetCurrent(), GL_POLYGON_OFFSET_FILL), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SAMPLE_ALPHA_TO_COVERAGE"), Uint32::New(v8::Isolate::GetCurrent(), GL_SAMPLE_ALPHA_TO_COVERAGE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SAMPLE_COVERAGE"), Uint32::New(v8::Isolate::GetCurrent(), GL_SAMPLE_COVERAGE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NO_ERROR"), Uint32::New(v8::Isolate::GetCurrent(), GL_NO_ERROR), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INVALID_ENUM"), Uint32::New(v8::Isolate::GetCurrent(), GL_INVALID_ENUM), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INVALID_VALUE"), Uint32::New(v8::Isolate::GetCurrent(), GL_INVALID_VALUE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INVALID_OPERATION"), Uint32::New(v8::Isolate::GetCurrent(), GL_INVALID_OPERATION), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "OUT_OF_MEMORY"), Uint32::New(v8::Isolate::GetCurrent(), GL_OUT_OF_MEMORY), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CW"), Uint32::New(v8::Isolate::GetCurrent(), GL_CW), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CCW"), Uint32::New(v8::Isolate::GetCurrent(), GL_CCW), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINE_WIDTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINE_WIDTH), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ALIASED_POINT_SIZE_RANGE"), Uint32::New(v8::Isolate::GetCurrent(), GL_ALIASED_POINT_SIZE_RANGE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ALIASED_LINE_WIDTH_RANGE"), Uint32::New(v8::Isolate::GetCurrent(), GL_ALIASED_LINE_WIDTH_RANGE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CULL_FACE_MODE"), Uint32::New(v8::Isolate::GetCurrent(), GL_CULL_FACE_MODE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FRONT_FACE"), Uint32::New(v8::Isolate::GetCurrent(), GL_FRONT_FACE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_RANGE"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_RANGE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_WRITEMASK"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_WRITEMASK), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_CLEAR_VALUE"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_CLEAR_VALUE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_FUNC"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_FUNC), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_CLEAR_VALUE"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_CLEAR_VALUE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_FUNC"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_FUNC), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_FAIL"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_FAIL), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_PASS_DEPTH_FAIL"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_PASS_DEPTH_FAIL), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_PASS_DEPTH_PASS"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_PASS_DEPTH_PASS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_REF"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_REF), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_VALUE_MASK"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_VALUE_MASK), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_WRITEMASK"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_WRITEMASK), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_BACK_FUNC"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_BACK_FUNC), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_BACK_FAIL"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_BACK_FAIL), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_BACK_PASS_DEPTH_FAIL"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_BACK_PASS_DEPTH_FAIL), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_BACK_PASS_DEPTH_PASS"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_BACK_PASS_DEPTH_PASS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_BACK_REF"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_BACK_REF), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_BACK_VALUE_MASK"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_BACK_VALUE_MASK), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_BACK_WRITEMASK"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_BACK_WRITEMASK), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VIEWPORT"), Uint32::New(v8::Isolate::GetCurrent(), GL_VIEWPORT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SCISSOR_BOX"), Uint32::New(v8::Isolate::GetCurrent(), GL_SCISSOR_BOX), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_CLEAR_VALUE"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_CLEAR_VALUE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_WRITEMASK"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_WRITEMASK), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNPACK_ALIGNMENT"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNPACK_ALIGNMENT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PACK_ALIGNMENT"), Uint32::New(v8::Isolate::GetCurrent(), GL_PACK_ALIGNMENT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_TEXTURE_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_TEXTURE_SIZE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_VIEWPORT_DIMS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_VIEWPORT_DIMS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SUBPIXEL_BITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_SUBPIXEL_BITS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RED_BITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_RED_BITS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GREEN_BITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_GREEN_BITS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLUE_BITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_BLUE_BITS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ALPHA_BITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_ALPHA_BITS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_BITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_BITS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_BITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_BITS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POLYGON_OFFSET_UNITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_POLYGON_OFFSET_UNITS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "POLYGON_OFFSET_FACTOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_POLYGON_OFFSET_FACTOR), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_BINDING_2D"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_BINDING_2D), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SAMPLE_BUFFERS"), Uint32::New(v8::Isolate::GetCurrent(), GL_SAMPLE_BUFFERS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SAMPLES"), Uint32::New(v8::Isolate::GetCurrent(), GL_SAMPLES), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SAMPLE_COVERAGE_VALUE"), Uint32::New(v8::Isolate::GetCurrent(), GL_SAMPLE_COVERAGE_VALUE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SAMPLE_COVERAGE_INVERT"), Uint32::New(v8::Isolate::GetCurrent(), GL_SAMPLE_COVERAGE_INVERT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NUM_COMPRESSED_TEXTURE_FORMATS"), Uint32::New(v8::Isolate::GetCurrent(), GL_NUM_COMPRESSED_TEXTURE_FORMATS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COMPRESSED_TEXTURE_FORMATS"), Uint32::New(v8::Isolate::GetCurrent(), GL_COMPRESSED_TEXTURE_FORMATS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DONT_CARE"), Uint32::New(v8::Isolate::GetCurrent(), GL_DONT_CARE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FASTEST"), Uint32::New(v8::Isolate::GetCurrent(), GL_FASTEST), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NICEST"), Uint32::New(v8::Isolate::GetCurrent(), GL_NICEST), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GENERATE_MIPMAP_HINT"), Uint32::New(v8::Isolate::GetCurrent(), GL_GENERATE_MIPMAP_HINT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BYTE"), Uint32::New(v8::Isolate::GetCurrent(), GL_BYTE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNSIGNED_BYTE"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNSIGNED_BYTE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SHORT"), Uint32::New(v8::Isolate::GetCurrent(), GL_SHORT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNSIGNED_SHORT"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNSIGNED_SHORT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INT"), Uint32::New(v8::Isolate::GetCurrent(), GL_INT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNSIGNED_INT"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNSIGNED_INT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FLOAT"), Uint32::New(v8::Isolate::GetCurrent(), GL_FLOAT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FIXED"), Uint32::New(v8::Isolate::GetCurrent(), GL_FIXED), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_COMPONENT"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_COMPONENT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_ALPHA), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGB"), Uint32::New(v8::Isolate::GetCurrent(), GL_RGB), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGBA"), Uint32::New(v8::Isolate::GetCurrent(), GL_RGBA), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LUMINANCE"), Uint32::New(v8::Isolate::GetCurrent(), GL_LUMINANCE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LUMINANCE_ALPHA"), Uint32::New(v8::Isolate::GetCurrent(), GL_LUMINANCE_ALPHA), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNSIGNED_SHORT_4_4_4_4"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNSIGNED_SHORT_4_4_4_4), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNSIGNED_SHORT_5_5_5_1"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNSIGNED_SHORT_5_5_5_1), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UNSIGNED_SHORT_5_6_5"), Uint32::New(v8::Isolate::GetCurrent(), GL_UNSIGNED_SHORT_5_6_5), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FRAGMENT_SHADER"), Uint32::New(v8::Isolate::GetCurrent(), GL_FRAGMENT_SHADER), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_SHADER"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_SHADER), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_VERTEX_ATTRIBS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_VERTEX_ATTRIBS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_VERTEX_UNIFORM_VECTORS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_VERTEX_UNIFORM_VECTORS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_VARYING_VECTORS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_VARYING_VECTORS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_COMBINED_TEXTURE_IMAGE_UNITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_VERTEX_TEXTURE_IMAGE_UNITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_TEXTURE_IMAGE_UNITS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_TEXTURE_IMAGE_UNITS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_FRAGMENT_UNIFORM_VECTORS"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_FRAGMENT_UNIFORM_VECTORS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SHADER_TYPE"), Uint32::New(v8::Isolate::GetCurrent(), GL_SHADER_TYPE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DELETE_STATUS"), Uint32::New(v8::Isolate::GetCurrent(), GL_DELETE_STATUS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINK_STATUS"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINK_STATUS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VALIDATE_STATUS"), Uint32::New(v8::Isolate::GetCurrent(), GL_VALIDATE_STATUS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ATTACHED_SHADERS"), Uint32::New(v8::Isolate::GetCurrent(), GL_ATTACHED_SHADERS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ACTIVE_UNIFORMS"), Uint32::New(v8::Isolate::GetCurrent(), GL_ACTIVE_UNIFORMS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ACTIVE_UNIFORM_MAX_LENGTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_ACTIVE_UNIFORM_MAX_LENGTH), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ACTIVE_ATTRIBUTES"), Uint32::New(v8::Isolate::GetCurrent(), GL_ACTIVE_ATTRIBUTES), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ACTIVE_ATTRIBUTE_MAX_LENGTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_ACTIVE_ATTRIBUTE_MAX_LENGTH), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SHADING_LANGUAGE_VERSION"), Uint32::New(v8::Isolate::GetCurrent(), GL_SHADING_LANGUAGE_VERSION), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURRENT_PROGRAM"), Uint32::New(v8::Isolate::GetCurrent(), GL_CURRENT_PROGRAM), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NEVER"), Uint32::New(v8::Isolate::GetCurrent(), GL_NEVER), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LESS"), Uint32::New(v8::Isolate::GetCurrent(), GL_LESS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EQUAL"), Uint32::New(v8::Isolate::GetCurrent(), GL_EQUAL), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LEQUAL"), Uint32::New(v8::Isolate::GetCurrent(), GL_LEQUAL), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GREATER"), Uint32::New(v8::Isolate::GetCurrent(), GL_GREATER), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NOTEQUAL"), Uint32::New(v8::Isolate::GetCurrent(), GL_NOTEQUAL), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GEQUAL"), Uint32::New(v8::Isolate::GetCurrent(), GL_GEQUAL), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ALWAYS"), Uint32::New(v8::Isolate::GetCurrent(), GL_ALWAYS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEEP"), Uint32::New(v8::Isolate::GetCurrent(), GL_KEEP), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "REPLACE"), Uint32::New(v8::Isolate::GetCurrent(), GL_REPLACE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INCR"), Uint32::New(v8::Isolate::GetCurrent(), GL_INCR), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DECR"), Uint32::New(v8::Isolate::GetCurrent(), GL_DECR), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INVERT"), Uint32::New(v8::Isolate::GetCurrent(), GL_INVERT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INCR_WRAP"), Uint32::New(v8::Isolate::GetCurrent(), GL_INCR_WRAP), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DECR_WRAP"), Uint32::New(v8::Isolate::GetCurrent(), GL_DECR_WRAP), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VENDOR"), Uint32::New(v8::Isolate::GetCurrent(), GL_VENDOR), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RENDERER"), Uint32::New(v8::Isolate::GetCurrent(), GL_RENDERER), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERSION"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERSION), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EXTENSIONS"), Uint32::New(v8::Isolate::GetCurrent(), GL_EXTENSIONS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NEAREST"), Uint32::New(v8::Isolate::GetCurrent(), GL_NEAREST), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINEAR"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINEAR), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NEAREST_MIPMAP_NEAREST"), Uint32::New(v8::Isolate::GetCurrent(), GL_NEAREST_MIPMAP_NEAREST), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINEAR_MIPMAP_NEAREST"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINEAR_MIPMAP_NEAREST), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NEAREST_MIPMAP_LINEAR"), Uint32::New(v8::Isolate::GetCurrent(), GL_NEAREST_MIPMAP_LINEAR), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LINEAR_MIPMAP_LINEAR"), Uint32::New(v8::Isolate::GetCurrent(), GL_LINEAR_MIPMAP_LINEAR), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_MAG_FILTER"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_MAG_FILTER), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_MIN_FILTER"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_MIN_FILTER), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_WRAP_S"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_WRAP_S), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_WRAP_T"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_WRAP_T), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_CUBE_MAP"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_CUBE_MAP), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_BINDING_CUBE_MAP"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_BINDING_CUBE_MAP), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_CUBE_MAP_POSITIVE_X"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_CUBE_MAP_POSITIVE_X), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_CUBE_MAP_NEGATIVE_X"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_CUBE_MAP_NEGATIVE_X), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_CUBE_MAP_POSITIVE_Y"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_CUBE_MAP_POSITIVE_Y), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_CUBE_MAP_NEGATIVE_Y"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_CUBE_MAP_NEGATIVE_Y), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_CUBE_MAP_POSITIVE_Z"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_CUBE_MAP_POSITIVE_Z), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE_CUBE_MAP_NEGATIVE_Z"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE_CUBE_MAP_NEGATIVE_Z), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_CUBE_MAP_TEXTURE_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_CUBE_MAP_TEXTURE_SIZE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE0"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE0), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE1"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE1), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE2"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE2), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE3"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE3), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE4"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE4), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE5"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE5), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE6"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE6), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE7"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE7), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE8"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE8), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE9"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE9), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE10"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE10), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE11"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE11), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE12"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE12), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE13"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE13), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE14"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE14), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE15"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE15), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE16"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE16), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE17"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE17), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE18"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE18), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE19"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE19), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE20"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE20), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE21"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE21), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE22"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE22), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE23"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE23), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE24"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE24), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE25"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE25), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE26"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE26), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE27"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE27), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE28"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE28), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE29"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE29), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE30"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE30), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TEXTURE31"), Uint32::New(v8::Isolate::GetCurrent(), GL_TEXTURE31), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ACTIVE_TEXTURE"), Uint32::New(v8::Isolate::GetCurrent(), GL_ACTIVE_TEXTURE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "REPEAT"), Uint32::New(v8::Isolate::GetCurrent(), GL_REPEAT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CLAMP_TO_EDGE"), Uint32::New(v8::Isolate::GetCurrent(), GL_CLAMP_TO_EDGE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MIRRORED_REPEAT"), Uint32::New(v8::Isolate::GetCurrent(), GL_MIRRORED_REPEAT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FLOAT_VEC2"), Uint32::New(v8::Isolate::GetCurrent(), GL_FLOAT_VEC2), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FLOAT_VEC3"), Uint32::New(v8::Isolate::GetCurrent(), GL_FLOAT_VEC3), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FLOAT_VEC4"), Uint32::New(v8::Isolate::GetCurrent(), GL_FLOAT_VEC4), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INT_VEC2"), Uint32::New(v8::Isolate::GetCurrent(), GL_INT_VEC2), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INT_VEC3"), Uint32::New(v8::Isolate::GetCurrent(), GL_INT_VEC3), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INT_VEC4"), Uint32::New(v8::Isolate::GetCurrent(), GL_INT_VEC4), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BOOL"), Uint32::New(v8::Isolate::GetCurrent(), GL_BOOL), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BOOL_VEC2"), Uint32::New(v8::Isolate::GetCurrent(), GL_BOOL_VEC2), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BOOL_VEC3"), Uint32::New(v8::Isolate::GetCurrent(), GL_BOOL_VEC3), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BOOL_VEC4"), Uint32::New(v8::Isolate::GetCurrent(), GL_BOOL_VEC4), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FLOAT_MAT2"), Uint32::New(v8::Isolate::GetCurrent(), GL_FLOAT_MAT2), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FLOAT_MAT3"), Uint32::New(v8::Isolate::GetCurrent(), GL_FLOAT_MAT3), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FLOAT_MAT4"), Uint32::New(v8::Isolate::GetCurrent(), GL_FLOAT_MAT4), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SAMPLER_2D"), Uint32::New(v8::Isolate::GetCurrent(), GL_SAMPLER_2D), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SAMPLER_CUBE"), Uint32::New(v8::Isolate::GetCurrent(), GL_SAMPLER_CUBE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_ATTRIB_ARRAY_ENABLED"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_ATTRIB_ARRAY_ENABLED), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_ATTRIB_ARRAY_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_ATTRIB_ARRAY_SIZE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_ATTRIB_ARRAY_STRIDE"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_ATTRIB_ARRAY_STRIDE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_ATTRIB_ARRAY_TYPE"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_ATTRIB_ARRAY_TYPE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_ATTRIB_ARRAY_NORMALIZED"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_ATTRIB_ARRAY_NORMALIZED), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_ATTRIB_ARRAY_POINTER"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_ATTRIB_ARRAY_POINTER), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VERTEX_ATTRIB_ARRAY_BUFFER_BINDING"), Uint32::New(v8::Isolate::GetCurrent(), GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COMPILE_STATUS"), Uint32::New(v8::Isolate::GetCurrent(), GL_COMPILE_STATUS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INFO_LOG_LENGTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_INFO_LOG_LENGTH), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SHADER_SOURCE_LENGTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_SHADER_SOURCE_LENGTH), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SHADER_COMPILER"), Uint32::New(v8::Isolate::GetCurrent(), GL_SHADER_COMPILER), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SHADER_BINARY_FORMATS"), Uint32::New(v8::Isolate::GetCurrent(), GL_SHADER_BINARY_FORMATS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NUM_SHADER_BINARY_FORMATS"), Uint32::New(v8::Isolate::GetCurrent(), GL_NUM_SHADER_BINARY_FORMATS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LOW_FLOAT"), Uint32::New(v8::Isolate::GetCurrent(), GL_LOW_FLOAT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MEDIUM_FLOAT"), Uint32::New(v8::Isolate::GetCurrent(), GL_MEDIUM_FLOAT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "HIGH_FLOAT"), Uint32::New(v8::Isolate::GetCurrent(), GL_HIGH_FLOAT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LOW_INT"), Uint32::New(v8::Isolate::GetCurrent(), GL_LOW_INT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MEDIUM_INT"), Uint32::New(v8::Isolate::GetCurrent(), GL_MEDIUM_INT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "HIGH_INT"), Uint32::New(v8::Isolate::GetCurrent(), GL_HIGH_INT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FRAMEBUFFER"), Uint32::New(v8::Isolate::GetCurrent(), GL_FRAMEBUFFER), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RENDERBUFFER"), Uint32::New(v8::Isolate::GetCurrent(), GL_RENDERBUFFER), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGBA4"), Uint32::New(v8::Isolate::GetCurrent(), GL_RGBA4), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGB5_A1"), Uint32::New(v8::Isolate::GetCurrent(), GL_RGB5_A1), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGB565"), Uint32::New(v8::Isolate::GetCurrent(), GL_RGB565), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_COMPONENT16"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_COMPONENT16), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_INDEX"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_INDEX), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_INDEX8"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_INDEX8), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RENDERBUFFER_WIDTH"), Uint32::New(v8::Isolate::GetCurrent(), GL_RENDERBUFFER_WIDTH), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RENDERBUFFER_HEIGHT"), Uint32::New(v8::Isolate::GetCurrent(), GL_RENDERBUFFER_HEIGHT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RENDERBUFFER_INTERNAL_FORMAT"), Uint32::New(v8::Isolate::GetCurrent(), GL_RENDERBUFFER_INTERNAL_FORMAT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RENDERBUFFER_RED_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_RENDERBUFFER_RED_SIZE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RENDERBUFFER_GREEN_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_RENDERBUFFER_GREEN_SIZE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RENDERBUFFER_BLUE_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_RENDERBUFFER_BLUE_SIZE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RENDERBUFFER_ALPHA_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_RENDERBUFFER_ALPHA_SIZE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RENDERBUFFER_DEPTH_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_RENDERBUFFER_DEPTH_SIZE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RENDERBUFFER_STENCIL_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_RENDERBUFFER_STENCIL_SIZE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE"), Uint32::New(v8::Isolate::GetCurrent(), GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FRAMEBUFFER_ATTACHMENT_OBJECT_NAME"), Uint32::New(v8::Isolate::GetCurrent(), GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL"), Uint32::New(v8::Isolate::GetCurrent(), GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE"), Uint32::New(v8::Isolate::GetCurrent(), GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "COLOR_ATTACHMENT0"), Uint32::New(v8::Isolate::GetCurrent(), GL_COLOR_ATTACHMENT0), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH_ATTACHMENT"), Uint32::New(v8::Isolate::GetCurrent(), GL_DEPTH_ATTACHMENT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL_ATTACHMENT"), Uint32::New(v8::Isolate::GetCurrent(), GL_STENCIL_ATTACHMENT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NONE"), Uint32::New(v8::Isolate::GetCurrent(), GL_NONE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FRAMEBUFFER_COMPLETE"), Uint32::New(v8::Isolate::GetCurrent(), GL_FRAMEBUFFER_COMPLETE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FRAMEBUFFER_INCOMPLETE_ATTACHMENT"), Uint32::New(v8::Isolate::GetCurrent(), GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"), Uint32::New(v8::Isolate::GetCurrent(), GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FRAMEBUFFER_INCOMPLETE_DIMENSIONS"), Uint32::New(v8::Isolate::GetCurrent(), GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FRAMEBUFFER_UNSUPPORTED"), Uint32::New(v8::Isolate::GetCurrent(), GL_FRAMEBUFFER_UNSUPPORTED), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FRAMEBUFFER_BINDING"), Uint32::New(v8::Isolate::GetCurrent(), GL_FRAMEBUFFER_BINDING), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RENDERBUFFER_BINDING"), Uint32::New(v8::Isolate::GetCurrent(), GL_RENDERBUFFER_BINDING), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MAX_RENDERBUFFER_SIZE"), Uint32::New(v8::Isolate::GetCurrent(), GL_MAX_RENDERBUFFER_SIZE), ReadOnly);

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ActiveTexture"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglActiveTextureCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "AttachShader"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglAttachShaderCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BindAttribLocation"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglBindAttribLocationCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BindBuffer"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglBindBufferCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BindFramebuffer"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglBindFramebufferCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BindRenderbuffer"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglBindRenderbufferCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BindTexture"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglBindTextureCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BlendColor"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglBlendColorCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BlendEquation"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglBlendEquationCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BlendEquationSeparate"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglBlendEquationSeparateCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BlendFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglBlendFuncCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BlendFuncSeparate"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglBlendFuncSeparateCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BufferData"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglBufferDataCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BufferSubData"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglBufferSubDataCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CheckFramebufferStatus"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglCheckFramebufferStatusCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Clear"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglClearCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ClearColor"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglClearColorCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ClearDepthf"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglClearDepthfCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ClearStencil"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglClearStencilCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ColorMask"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglColorMaskCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CompileShader"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglCompileShaderCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CopyTexImage2D"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglCopyTexImage2DCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CopyTexSubImage2D"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglCopyTexSubImage2DCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CreateProgram"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglCreateProgramCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CreateShader"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglCreateShaderCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CullFace"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglCullFaceCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DeleteBuffers"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglDeleteBuffersCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DeleteFramebuffers"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglDeleteFramebuffersCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DeleteProgram"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglDeleteProgramCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DeleteRenderbuffers"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglDeleteRenderbuffersCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DeleteShader"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglDeleteShaderCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DeleteTextures"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglDeleteTexturesCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DepthFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglDepthFuncCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DepthMask"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglDepthMaskCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DepthRangef"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglDepthRangefCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DetachShader"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglDetachShaderCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Disable"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglDisableCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DisableVertexAttribArray"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglDisableVertexAttribArrayCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DrawArrays"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglDrawArraysCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DrawElements"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglDrawElementsCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Enable"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglEnableCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EnableVertexAttribArray"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglEnableVertexAttribArrayCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Finish"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglFinishCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Flush"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglFlushCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FramebufferRenderbuffer"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglFramebufferRenderbufferCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FramebufferTexture2D"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglFramebufferTexture2DCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FrontFace"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglFrontFaceCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GenBuffers"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGenBuffersCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GenerateMipmap"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGenerateMipmapCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GenFramebuffers"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGenFramebuffersCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GenRenderbuffers"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGenRenderbuffersCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GenTextures"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGenTexturesCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetActiveAttrib"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGetActiveAttribCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetActiveUniform"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGetActiveUniformCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetAttachedShaders"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGetAttachedShadersCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetAttribLocation"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGetAttribLocationCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetBooleanv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGetBooleanvCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetBufferParameteriv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGetBufferParameterivCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetError"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGetErrorCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetFloatv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGetFloatvCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetFramebufferAttachmentParameteriv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGetFramebufferAttachmentParameterivCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetIntegerv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGetIntegervCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetProgramiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGetProgramivCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetProgramInfoLog"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGetProgramInfoLogCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetShaderiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGetShaderivCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetShaderInfoLog"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGetShaderInfoLogCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetShaderSource"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGetShaderSourceCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetUniformiv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGetUniformivCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetUniformLocation"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGetUniformLocationCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Hint"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglHintCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "IsBuffer"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglIsBufferCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "IsEnabled"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglIsEnabledCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "IsFramebuffer"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglIsFramebufferCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "IsProgram"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglIsProgramCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "IsRenderbuffer"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglIsRenderbufferCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "IsShader"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglIsShaderCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "IsTexture"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglIsTextureCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LineWidth"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglLineWidthCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LinkProgram"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglLinkProgramCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PixelStorei"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglPixelStoreiCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PolygonOffset"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglPolygonOffsetCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ReadPixels"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglReadPixelsCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RenderbufferStorage"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglRenderbufferStorageCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SampleCoverage"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglSampleCoverageCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Scissor"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglScissorCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ShaderSource"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglShaderSourceCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "StencilFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglStencilFuncCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "StencilFuncSeparate"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglStencilFuncSeparateCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "StencilMask"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglStencilMaskCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "StencilMaskSeparate"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglStencilMaskSeparateCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "StencilOp"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglStencilOpCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "StencilOpSeparate"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglStencilOpSeparateCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexImage2D"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglTexImage2DCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexParameterf"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglTexParameterfCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexParameterfv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglTexParameterfvCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexParameteri"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglTexParameteriCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexParameteriv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglTexParameterivCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TexSubImage2D"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglTexSubImage2DCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform1f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglUniform1fCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform1fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglUniform1fvCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform1i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglUniform1iCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform1iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglUniform1ivCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform2f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglUniform2fCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform2fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglUniform2fvCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform2i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglUniform2iCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform2iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglUniform2ivCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform3f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglUniform3fCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform3fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglUniform3fvCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform3i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglUniform3iCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform3iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglUniform3ivCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform4f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglUniform4fCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform4fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglUniform4fvCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform4i"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglUniform4iCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Uniform4iv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglUniform4ivCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UniformMatrix2fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglUniformMatrix2fvCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UniformMatrix3fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglUniformMatrix3fvCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UniformMatrix4fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglUniformMatrix4fvCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UseProgram"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglUseProgramCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ValidateProgram"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglValidateProgramCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib1f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglVertexAttrib1fCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib1fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglVertexAttrib1fvCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib2f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglVertexAttrib2fCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib2fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglVertexAttrib2fvCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib3f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglVertexAttrib3fCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib3fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglVertexAttrib3fvCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib4f"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglVertexAttrib4fCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttrib4fv"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglVertexAttrib4fvCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VertexAttribPointer"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglVertexAttribPointerCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Viewport"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglViewportCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetParameter"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGetParameterCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetTexParameter"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGetTexParameterCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetVertexAttrib"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGetVertexAttribCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetRenderbufferParameter"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglGetRenderbufferParameterCallback));

     Gles->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ShaderSourceFile"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLESglShaderSourceFileCallback));


      // Again, return the result through the current handle scope.
      return Gles;
}    

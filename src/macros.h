/**
 * Shorthands for various lengthy V8 syntaxt constructs.
 */

#ifndef _JS_MACROS_H
#define _JS_MACROS_H

#define _STRING(x) #x
#define STRING(x) _STRING(x)

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

#define SAVE_PTR(index, ptr) args.This()->SetPointerInInternalField(index, (void *)(ptr))
#define LOAD_PTR(index, type) reinterpret_cast<type>(args.This()->GetPointerFromInternalField(index))
#define SAVE_VALUE(index, val) args.This()->SetInternalField(index, val)
#define LOAD_VALUE(index) args.This()->GetInternalField(index)
#define JS_STR(...) v8::String::New(__VA_ARGS__)
#define JS_INT(val) v8::Integer::New(val)
#define JS_FLOAT(val) v8::Number::New(val)
#define JS_BOOL(val) v8::Boolean::New(val)
#define JS_NULL v8::Null()
#define JS_UNDEFINED v8::Undefined()
#define JS_METHOD(name) v8::Handle<v8::Value> name(const v8::Arguments& args)
#define INSTANCEOF(obj, func) func->HasInstance(obj)

#define JS_THROW(type, reason) v8::ThrowException(v8::Exception::type(JS_STR(reason)))
#define JS_ERROR(reason) JS_THROW(Error, reason)
#define JS_TYPE_ERROR(reason) JS_THROW(TypeError, reason)
#define JS_RANGE_ERROR(reason) JS_THROW(RangeError, reason)
#define JS_SYNTAX_ERROR(reason) JS_THROW(SyntaxError, reason)
#define JS_REFERENCE_ERROR(reason) JS_THROW(ReferenceError, reason)
#define JS_RETHROW(tc) v8::Local<v8::Value>::New(tc.Exception());

#define JS_GLOBAL v8::Context::GetCurrent()->Global()
#define GLOBAL_PROTO v8::Handle<v8::Object>::Cast(JS_GLOBAL->GetPrototype())
#define APP_PTR reinterpret_cast<v8cgi_App *>(v8::Handle<v8::External>::Cast(GLOBAL_PROTO->GetInternalField(0))->Value());
#define GC_PTR reinterpret_cast<GC *>(v8::Handle<v8::External>::Cast(GLOBAL_PROTO->GetInternalField(1))->Value());

#define ASSERT_CONSTRUCTOR if (!args.IsConstructCall()) { return JS_ERROR("Invalid call format. Please use the 'new' operator."); }
#define ASSERT_NOT_CONSTRUCTOR if (args.IsConstructCall()) { return JS_ERROR("Invalid call format. Please do not use the 'new' operator."); }
#define RETURN_CONSTRUCT_CALL \
	std::vector< v8::Handle<v8::Value> > params(args.Length()); \
	for (size_t i=0; i<params.size(); i++) { params[i] = args[i]; } \
	return args.Callee()->NewInstance(args.Length(), &params[0]);

#ifdef _WIN32
#   define SHARED_INIT() extern "C" __declspec(dllexport) void init(v8::Handle<v8::Function> require, v8::Handle<v8::Object> exports, v8::Handle<v8::Object> module)
#else
#   define SHARED_INIT() extern "C" void init(v8::Handle<v8::Function> require, v8::Handle<v8::Object> exports, v8::Handle<v8::Object> module)
#endif

#endif

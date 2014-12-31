

#include "glutbind.h"

int* pargc_;
char** argv_;
map<const char*, void*> font_;
Persistent<Context> GlutFactory::glut_persistent_context;
    
    

void GetGLUT_APIENTRY_DEFINED(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_APIENTRY_DEFINED));
}




void GetGLUT_WINGDIAPI_DEFINED(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINGDIAPI_DEFINED));
}




void GetGLUT_API_VERSION(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_API_VERSION));
}




void GetGLUT_XLIB_IMPLEMENTATION(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_XLIB_IMPLEMENTATION));
}




void GetGLUT_MACOSX_IMPLEMENTATION(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_MACOSX_IMPLEMENTATION));
}




void GetGLUT_RGB(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_RGB));
}




void GetGLUT_RGBA(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_RGBA));
}




void GetGLUT_INDEX(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_INDEX));
}




void GetGLUT_SINGLE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_SINGLE));
}




void GetGLUT_DOUBLE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_DOUBLE));
}




void GetGLUT_ACCUM(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_ACCUM));
}




void GetGLUT_ALPHA(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_ALPHA));
}




void GetGLUT_DEPTH(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_DEPTH));
}




void GetGLUT_STENCIL(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_STENCIL));
}




void GetGLUT_MULTISAMPLE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_MULTISAMPLE));
}




void GetGLUT_STEREO(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_STEREO));
}




void GetGLUT_LUMINANCE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_LUMINANCE));
}




void GetGLUT_NO_RECOVERY(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_NO_RECOVERY));
}




void GetGLUT_LEFT_BUTTON(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_LEFT_BUTTON));
}




void GetGLUT_MIDDLE_BUTTON(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_MIDDLE_BUTTON));
}




void GetGLUT_RIGHT_BUTTON(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_RIGHT_BUTTON));
}




void GetGLUT_DOWN(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_DOWN));
}




void GetGLUT_UP(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_UP));
}




void GetGLUT_KEY_F1(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_F1));
}




void GetGLUT_KEY_F2(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_F2));
}




void GetGLUT_KEY_F3(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_F3));
}




void GetGLUT_KEY_F4(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_F4));
}




void GetGLUT_KEY_F5(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_F5));
}




void GetGLUT_KEY_F6(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_F6));
}




void GetGLUT_KEY_F7(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_F7));
}




void GetGLUT_KEY_F8(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_F8));
}




void GetGLUT_KEY_F9(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_F9));
}




void GetGLUT_KEY_F10(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_F10));
}




void GetGLUT_KEY_F11(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_F11));
}




void GetGLUT_KEY_F12(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_F12));
}




void GetGLUT_KEY_LEFT(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_LEFT));
}




void GetGLUT_KEY_UP(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_UP));
}




void GetGLUT_KEY_RIGHT(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_RIGHT));
}




void GetGLUT_KEY_DOWN(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_DOWN));
}




void GetGLUT_KEY_PAGE_UP(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_PAGE_UP));
}




void GetGLUT_KEY_PAGE_DOWN(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_PAGE_DOWN));
}




void GetGLUT_KEY_HOME(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_HOME));
}




void GetGLUT_KEY_END(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_END));
}




void GetGLUT_KEY_INSERT(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_INSERT));
}




void GetGLUT_LEFT(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_LEFT));
}




void GetGLUT_ENTERED(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_ENTERED));
}




void GetGLUT_MENU_NOT_IN_USE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_MENU_NOT_IN_USE));
}




void GetGLUT_MENU_IN_USE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_MENU_IN_USE));
}




void GetGLUT_NOT_VISIBLE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_NOT_VISIBLE));
}




void GetGLUT_VISIBLE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_VISIBLE));
}




void GetGLUT_HIDDEN(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_HIDDEN));
}




void GetGLUT_FULLY_RETAINED(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_FULLY_RETAINED));
}




void GetGLUT_PARTIALLY_RETAINED(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_PARTIALLY_RETAINED));
}




void GetGLUT_FULLY_COVERED(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_FULLY_COVERED));
}




void GetGLUT_RED(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_RED));
}




void GetGLUT_GREEN(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_GREEN));
}




void GetGLUT_BLUE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_BLUE));
}




void GetGLUT_NORMAL(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_NORMAL));
}




void GetGLUT_OVERLAY(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_OVERLAY));
}




void GetGLUT_STROKE_ROMAN(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STROKE_ROMAN"));

}




void GetGLUT_STROKE_MONO_ROMAN(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STROKE_MONO_ROMAN"));

}




void GetGLUT_BITMAP_9_BY_15(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BITMAP_9_BY_15"));

}




void GetGLUT_BITMAP_8_BY_13(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BITMAP_8_BY_13"));

}




void GetGLUT_BITMAP_TIMES_ROMAN_10(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BITMAP_TIMES_ROMAN_10"));

}




void GetGLUT_BITMAP_TIMES_ROMAN_24(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BITMAP_TIMES_ROMAN_24"));

}




void GetGLUT_BITMAP_HELVETICA_10(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BITMAP_HELVETICA_10"));

}




void GetGLUT_BITMAP_HELVETICA_12(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BITMAP_HELVETICA_12"));

}




void GetGLUT_BITMAP_HELVETICA_18(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BITMAP_HELVETICA_18"));

}




void GetGLUT_WINDOW_X(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_X));
}




void GetGLUT_WINDOW_Y(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_Y));
}




void GetGLUT_WINDOW_WIDTH(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_WIDTH));
}




void GetGLUT_WINDOW_HEIGHT(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_HEIGHT));
}




void GetGLUT_WINDOW_BUFFER_SIZE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_BUFFER_SIZE));
}




void GetGLUT_WINDOW_STENCIL_SIZE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_STENCIL_SIZE));
}




void GetGLUT_WINDOW_DEPTH_SIZE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_DEPTH_SIZE));
}




void GetGLUT_WINDOW_RED_SIZE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_RED_SIZE));
}




void GetGLUT_WINDOW_GREEN_SIZE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_GREEN_SIZE));
}




void GetGLUT_WINDOW_BLUE_SIZE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_BLUE_SIZE));
}




void GetGLUT_WINDOW_ALPHA_SIZE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_ALPHA_SIZE));
}




void GetGLUT_WINDOW_ACCUM_RED_SIZE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_ACCUM_RED_SIZE));
}




void GetGLUT_WINDOW_ACCUM_GREEN_SIZE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_ACCUM_GREEN_SIZE));
}




void GetGLUT_WINDOW_ACCUM_BLUE_SIZE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_ACCUM_BLUE_SIZE));
}




void GetGLUT_WINDOW_ACCUM_ALPHA_SIZE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_ACCUM_ALPHA_SIZE));
}




void GetGLUT_WINDOW_DOUBLEBUFFER(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_DOUBLEBUFFER));
}




void GetGLUT_WINDOW_RGBA(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_RGBA));
}




void GetGLUT_WINDOW_PARENT(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_PARENT));
}




void GetGLUT_WINDOW_NUM_CHILDREN(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_NUM_CHILDREN));
}




void GetGLUT_WINDOW_COLORMAP_SIZE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_COLORMAP_SIZE));
}




void GetGLUT_WINDOW_NUM_SAMPLES(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_NUM_SAMPLES));
}




void GetGLUT_WINDOW_STEREO(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_STEREO));
}




void GetGLUT_WINDOW_CURSOR(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_CURSOR));
}




void GetGLUT_SCREEN_WIDTH(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_SCREEN_WIDTH));
}




void GetGLUT_SCREEN_HEIGHT(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_SCREEN_HEIGHT));
}




void GetGLUT_SCREEN_WIDTH_MM(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_SCREEN_WIDTH_MM));
}




void GetGLUT_SCREEN_HEIGHT_MM(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_SCREEN_HEIGHT_MM));
}




void GetGLUT_MENU_NUM_ITEMS(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_MENU_NUM_ITEMS));
}




void GetGLUT_DISPLAY_MODE_POSSIBLE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_DISPLAY_MODE_POSSIBLE));
}




void GetGLUT_INIT_WINDOW_X(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_INIT_WINDOW_X));
}




void GetGLUT_INIT_WINDOW_Y(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_INIT_WINDOW_Y));
}




void GetGLUT_INIT_WINDOW_WIDTH(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_INIT_WINDOW_WIDTH));
}




void GetGLUT_INIT_WINDOW_HEIGHT(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_INIT_WINDOW_HEIGHT));
}




void GetGLUT_INIT_DISPLAY_MODE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_INIT_DISPLAY_MODE));
}




void GetGLUT_ELAPSED_TIME(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_ELAPSED_TIME));
}




void GetGLUT_WINDOW_FORMAT_ID(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_WINDOW_FORMAT_ID));
}




void GetGLUT_HAS_KEYBOARD(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_HAS_KEYBOARD));
}




void GetGLUT_HAS_MOUSE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_HAS_MOUSE));
}




void GetGLUT_HAS_SPACEBALL(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_HAS_SPACEBALL));
}




void GetGLUT_HAS_DIAL_AND_BUTTON_BOX(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_HAS_DIAL_AND_BUTTON_BOX));
}




void GetGLUT_HAS_TABLET(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_HAS_TABLET));
}




void GetGLUT_NUM_MOUSE_BUTTONS(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_NUM_MOUSE_BUTTONS));
}




void GetGLUT_NUM_SPACEBALL_BUTTONS(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_NUM_SPACEBALL_BUTTONS));
}




void GetGLUT_NUM_BUTTON_BOX_BUTTONS(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_NUM_BUTTON_BOX_BUTTONS));
}




void GetGLUT_NUM_DIALS(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_NUM_DIALS));
}




void GetGLUT_NUM_TABLET_BUTTONS(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_NUM_TABLET_BUTTONS));
}




void GetGLUT_DEVICE_IGNORE_KEY_REPEAT(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_DEVICE_IGNORE_KEY_REPEAT));
}




void GetGLUT_DEVICE_KEY_REPEAT(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_DEVICE_KEY_REPEAT));
}




void GetGLUT_HAS_JOYSTICK(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_HAS_JOYSTICK));
}




void GetGLUT_OWNS_JOYSTICK(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_OWNS_JOYSTICK));
}




void GetGLUT_JOYSTICK_BUTTONS(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_JOYSTICK_BUTTONS));
}




void GetGLUT_JOYSTICK_AXES(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_JOYSTICK_AXES));
}




void GetGLUT_JOYSTICK_POLL_RATE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_JOYSTICK_POLL_RATE));
}




void GetGLUT_OVERLAY_POSSIBLE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_OVERLAY_POSSIBLE));
}




void GetGLUT_LAYER_IN_USE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_LAYER_IN_USE));
}




void GetGLUT_HAS_OVERLAY(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_HAS_OVERLAY));
}




void GetGLUT_TRANSPARENT_INDEX(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_TRANSPARENT_INDEX));
}




void GetGLUT_NORMAL_DAMAGED(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_NORMAL_DAMAGED));
}




void GetGLUT_OVERLAY_DAMAGED(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_OVERLAY_DAMAGED));
}




void GetGLUT_VIDEO_RESIZE_POSSIBLE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_VIDEO_RESIZE_POSSIBLE));
}




void GetGLUT_VIDEO_RESIZE_IN_USE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_VIDEO_RESIZE_IN_USE));
}




void GetGLUT_VIDEO_RESIZE_X_DELTA(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_VIDEO_RESIZE_X_DELTA));
}




void GetGLUT_VIDEO_RESIZE_Y_DELTA(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_VIDEO_RESIZE_Y_DELTA));
}




void GetGLUT_VIDEO_RESIZE_WIDTH_DELTA(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_VIDEO_RESIZE_WIDTH_DELTA));
}




void GetGLUT_VIDEO_RESIZE_HEIGHT_DELTA(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_VIDEO_RESIZE_HEIGHT_DELTA));
}




void GetGLUT_VIDEO_RESIZE_X(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_VIDEO_RESIZE_X));
}




void GetGLUT_VIDEO_RESIZE_Y(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_VIDEO_RESIZE_Y));
}




void GetGLUT_VIDEO_RESIZE_WIDTH(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_VIDEO_RESIZE_WIDTH));
}




void GetGLUT_VIDEO_RESIZE_HEIGHT(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_VIDEO_RESIZE_HEIGHT));
}




void GetGLUT_ACTIVE_SHIFT(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_ACTIVE_SHIFT));
}




void GetGLUT_ACTIVE_CTRL(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_ACTIVE_CTRL));
}




void GetGLUT_ACTIVE_ALT(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_ACTIVE_ALT));
}




void GetGLUT_CURSOR_RIGHT_ARROW(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_RIGHT_ARROW));
}




void GetGLUT_CURSOR_LEFT_ARROW(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_LEFT_ARROW));
}




void GetGLUT_CURSOR_INFO(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_INFO));
}




void GetGLUT_CURSOR_DESTROY(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_DESTROY));
}




void GetGLUT_CURSOR_HELP(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_HELP));
}




void GetGLUT_CURSOR_CYCLE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_CYCLE));
}




void GetGLUT_CURSOR_SPRAY(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_SPRAY));
}




void GetGLUT_CURSOR_WAIT(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_WAIT));
}




void GetGLUT_CURSOR_TEXT(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_TEXT));
}




void GetGLUT_CURSOR_CROSSHAIR(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_CROSSHAIR));
}




void GetGLUT_CURSOR_UP_DOWN(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_UP_DOWN));
}




void GetGLUT_CURSOR_LEFT_RIGHT(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_LEFT_RIGHT));
}




void GetGLUT_CURSOR_TOP_SIDE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_TOP_SIDE));
}




void GetGLUT_CURSOR_BOTTOM_SIDE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_BOTTOM_SIDE));
}




void GetGLUT_CURSOR_LEFT_SIDE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_LEFT_SIDE));
}




void GetGLUT_CURSOR_RIGHT_SIDE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_RIGHT_SIDE));
}




void GetGLUT_CURSOR_TOP_LEFT_CORNER(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_TOP_LEFT_CORNER));
}




void GetGLUT_CURSOR_TOP_RIGHT_CORNER(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_TOP_RIGHT_CORNER));
}




void GetGLUT_CURSOR_BOTTOM_RIGHT_CORNER(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_BOTTOM_RIGHT_CORNER));
}




void GetGLUT_CURSOR_BOTTOM_LEFT_CORNER(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_BOTTOM_LEFT_CORNER));
}




void GetGLUT_CURSOR_INHERIT(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_INHERIT));
}




void GetGLUT_CURSOR_NONE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_NONE));
}




void GetGLUT_CURSOR_FULL_CROSSHAIR(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_CURSOR_FULL_CROSSHAIR));
}



void GLUTInitCallback(const FunctionCallbackInfo<Value>& args) {
  glutInit(( int* ) pargc_, ( char** ) argv_);
  args.GetReturnValue().SetUndefined();
}



void GLUTInitDisplayModeCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int arg0 = args[0]->Uint32Value();

  //make call
  glutInitDisplayMode((unsigned int)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTInitDisplayStringCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  String::Utf8Value value0(args[0]);
  char* arg0 = *value0;

  //make call
  glutInitDisplayString((const char*)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTInitWindowPositionCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glutInitWindowPosition((int)arg0, (int)arg1);
  args.GetReturnValue().SetUndefined();
}




void GLUTInitWindowSizeCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glutInitWindowSize((int)arg0, (int)arg1);
  args.GetReturnValue().SetUndefined();
}




void GLUTMainLoopCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutMainLoop();
  args.GetReturnValue().SetUndefined();
}




void GLUTCreateWindowCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  String::Utf8Value value0(args[0]);
  char* arg0 = *value0;

  //make call
  glutCreateWindow((const char*)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTCreateSubWindowCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 5) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();
  int arg4 = args[4]->IntegerValue();

  //make call
  glutCreateSubWindow((int)arg0, (int)arg1, (int)arg2, (int)arg3, (int)arg4);
  args.GetReturnValue().SetUndefined();
}




void GLUTDestroyWindowCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glutDestroyWindow((int)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTPostRedisplayCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutPostRedisplay();
  args.GetReturnValue().SetUndefined();
}




void GLUTPostWindowRedisplayCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glutPostWindowRedisplay((int)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTSwapBuffersCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutSwapBuffers();
  args.GetReturnValue().SetUndefined();
}




void GLUTGetWindowCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutGetWindow();
  args.GetReturnValue().SetUndefined();
}




void GLUTSetWindowCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glutSetWindow((int)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTSetWindowTitleCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  String::Utf8Value value0(args[0]);
  char* arg0 = *value0;

  //make call
  glutSetWindowTitle((const char*)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTSetIconTitleCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  String::Utf8Value value0(args[0]);
  char* arg0 = *value0;

  //make call
  glutSetIconTitle((const char*)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTPositionWindowCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glutPositionWindow((int)arg0, (int)arg1);
  args.GetReturnValue().SetUndefined();
}




void GLUTReshapeWindowCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glutReshapeWindow((int)arg0, (int)arg1);
  args.GetReturnValue().SetUndefined();
}




void GLUTPopWindowCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutPopWindow();
  args.GetReturnValue().SetUndefined();
}




void GLUTPushWindowCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutPushWindow();
  args.GetReturnValue().SetUndefined();
}




void GLUTIconifyWindowCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutIconifyWindow();
  args.GetReturnValue().SetUndefined();
}




void GLUTShowWindowCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutShowWindow();
  args.GetReturnValue().SetUndefined();
}




void GLUTHideWindowCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutHideWindow();
  args.GetReturnValue().SetUndefined();
}




void GLUTFullScreenCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutFullScreen();
  args.GetReturnValue().SetUndefined();
}




void GLUTSetCursorCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glutSetCursor((int)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTWarpPointerCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glutWarpPointer((int)arg0, (int)arg1);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentWMCloseFunc;

void funcWMCloseFunc ( ) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[0];

  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localWMCloseFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentWMCloseFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localWMCloseFunc->Call(glut_persistent_context->Global(), 0, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in WMCloseFunc: %s\n", *error);
  }
}

void GLUTWMCloseFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentWMCloseFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentWMCloseFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutWMCloseFunc((void (*)(void)) funcWMCloseFunc);
  args.GetReturnValue().SetUndefined();
}




void GLUTCheckLoopCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutCheckLoop();
  args.GetReturnValue().SetUndefined();
}




void GLUTEstablishOverlayCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutEstablishOverlay();
  args.GetReturnValue().SetUndefined();
}




void GLUTRemoveOverlayCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutRemoveOverlay();
  args.GetReturnValue().SetUndefined();
}




void GLUTUseLayerCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glutUseLayer((GLenum)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTPostOverlayRedisplayCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutPostOverlayRedisplay();
  args.GetReturnValue().SetUndefined();
}




void GLUTPostWindowOverlayRedisplayCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glutPostWindowOverlayRedisplay((int)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTShowOverlayCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutShowOverlay();
  args.GetReturnValue().SetUndefined();
}




void GLUTHideOverlayCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutHideOverlay();
  args.GetReturnValue().SetUndefined();
}




void GLUTCreateMenuCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  void* arg0 = *value0;

  //make call
  glutCreateMenu((void (*)(int))arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTDestroyMenuCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glutDestroyMenu((int)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTGetMenuCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutGetMenu();
  args.GetReturnValue().SetUndefined();
}




void GLUTSetMenuCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glutSetMenu((int)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTAddMenuEntryCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  String::Utf8Value value0(args[0]);
  char* arg0 = *value0;
  int arg1 = args[1]->IntegerValue();

  //make call
  glutAddMenuEntry((const char*)arg0, (int)arg1);
  args.GetReturnValue().SetUndefined();
}




void GLUTAddSubMenuCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  String::Utf8Value value0(args[0]);
  char* arg0 = *value0;
  int arg1 = args[1]->IntegerValue();

  //make call
  glutAddSubMenu((const char*)arg0, (int)arg1);
  args.GetReturnValue().SetUndefined();
}




void GLUTChangeToMenuEntryCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  String::Utf8Value value1(args[1]);
  char* arg1 = *value1;
  int arg2 = args[2]->IntegerValue();

  //make call
  glutChangeToMenuEntry((int)arg0, (const char*)arg1, (int)arg2);
  args.GetReturnValue().SetUndefined();
}




void GLUTChangeToSubMenuCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  String::Utf8Value value1(args[1]);
  char* arg1 = *value1;
  int arg2 = args[2]->IntegerValue();

  //make call
  glutChangeToSubMenu((int)arg0, (const char*)arg1, (int)arg2);
  args.GetReturnValue().SetUndefined();
}




void GLUTRemoveMenuItemCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glutRemoveMenuItem((int)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTAttachMenuCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glutAttachMenu((int)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTDetachMenuCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glutDetachMenu((int)arg0);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentDisplayFunc;

void funcDisplayFunc ( ) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[0];

  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localDisplayFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentDisplayFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localDisplayFunc->Call(glut_persistent_context->Global(), 0, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in DisplayFunc: %s\n", *error);
  }
}

void GLUTDisplayFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentDisplayFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentDisplayFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutDisplayFunc((void (*)(void)) funcDisplayFunc);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentReshapeFunc;

void funcReshapeFunc ( int arg0,int arg1) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[2];
  valueArr[0] = Integer::New(v8::Isolate::GetCurrent(), arg0);
  valueArr[1] = Integer::New(v8::Isolate::GetCurrent(), arg1);
  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localReshapeFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentReshapeFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localReshapeFunc->Call(glut_persistent_context->Global(), 2, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in ReshapeFunc: %s\n", *error);
  }
}

void GLUTReshapeFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentReshapeFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentReshapeFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutReshapeFunc((void (*)(int width, int height)) funcReshapeFunc);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentKeyboardFunc;

void funcKeyboardFunc ( unsigned char arg0,int arg1,int arg2) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[3];
  valueArr[0] = Integer::New(v8::Isolate::GetCurrent(), arg0);
  valueArr[1] = Integer::New(v8::Isolate::GetCurrent(), arg1);
  valueArr[2] = Integer::New(v8::Isolate::GetCurrent(), arg2);
  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localKeyboardFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentKeyboardFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localKeyboardFunc->Call(glut_persistent_context->Global(), 3, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in KeyboardFunc: %s\n", *error);
  }
}

void GLUTKeyboardFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentKeyboardFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentKeyboardFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutKeyboardFunc((void (*)(unsigned char key, int x, int y)) funcKeyboardFunc);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentMouseFunc;

void funcMouseFunc ( int arg0,int arg1,int arg2,int arg3) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[4];
  valueArr[0] = Integer::New(v8::Isolate::GetCurrent(), arg0);
  valueArr[1] = Integer::New(v8::Isolate::GetCurrent(), arg1);
  valueArr[2] = Integer::New(v8::Isolate::GetCurrent(), arg2);
  valueArr[3] = Integer::New(v8::Isolate::GetCurrent(), arg3);
  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localMouseFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentMouseFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localMouseFunc->Call(glut_persistent_context->Global(), 4, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in MouseFunc: %s\n", *error);
  }
}

void GLUTMouseFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentMouseFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentMouseFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutMouseFunc((void (*)(int button, int state, int x, int y)) funcMouseFunc);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentMotionFunc;

void funcMotionFunc ( int arg0,int arg1) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[2];
  valueArr[0] = Integer::New(v8::Isolate::GetCurrent(), arg0);
  valueArr[1] = Integer::New(v8::Isolate::GetCurrent(), arg1);
  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localMotionFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentMotionFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localMotionFunc->Call(glut_persistent_context->Global(), 2, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in MotionFunc: %s\n", *error);
  }
}

void GLUTMotionFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentMotionFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentMotionFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutMotionFunc((void (*)(int x, int y)) funcMotionFunc);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentPassiveMotionFunc;

void funcPassiveMotionFunc ( int arg0,int arg1) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[2];
  valueArr[0] = Integer::New(v8::Isolate::GetCurrent(), arg0);
  valueArr[1] = Integer::New(v8::Isolate::GetCurrent(), arg1);
  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localPassiveMotionFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentPassiveMotionFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localPassiveMotionFunc->Call(glut_persistent_context->Global(), 2, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in PassiveMotionFunc: %s\n", *error);
  }
}

void GLUTPassiveMotionFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentPassiveMotionFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentPassiveMotionFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutPassiveMotionFunc((void (*)(int x, int y)) funcPassiveMotionFunc);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentEntryFunc;

void funcEntryFunc ( int arg0) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[1];
  valueArr[0] = Integer::New(v8::Isolate::GetCurrent(), arg0);
  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localEntryFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentEntryFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localEntryFunc->Call(glut_persistent_context->Global(), 1, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in EntryFunc: %s\n", *error);
  }
}

void GLUTEntryFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentEntryFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentEntryFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutEntryFunc((void (*)(int state)) funcEntryFunc);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentVisibilityFunc;

void funcVisibilityFunc ( int arg0) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[1];
  valueArr[0] = Integer::New(v8::Isolate::GetCurrent(), arg0);
  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localVisibilityFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentVisibilityFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localVisibilityFunc->Call(glut_persistent_context->Global(), 1, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in VisibilityFunc: %s\n", *error);
  }
}

void GLUTVisibilityFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentVisibilityFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentVisibilityFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutVisibilityFunc((void (*)(int state)) funcVisibilityFunc);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentIdleFunc;

void funcIdleFunc ( ) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[0];

  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localIdleFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentIdleFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localIdleFunc->Call(glut_persistent_context->Global(), 0, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in IdleFunc: %s\n", *error);
  }
}

void GLUTIdleFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentIdleFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentIdleFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutIdleFunc((void (*)(void)) funcIdleFunc);
  args.GetReturnValue().SetUndefined();
}



typedef struct {
    int value;
    Persistent<Function> timerFunc;
} timerData;

timerData * persistentTimers[50] = { NULL };

void callbackTimerFunc(int value) {
    timerData * elem = persistentTimers[value];
    if(elem != NULL) {
      //define handle scope
      HandleScope scope(v8::Isolate::GetCurrent());
      Handle<Value> args[1];
      args[0] = Integer::New(v8::Isolate::GetCurrent(), elem->value);
      Local<Function> timer = Local<Function>::New(v8::Isolate::GetCurrent(), elem->timerFunc);
      Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
      timer->Call(glut_persistent_context->Global(), 1, args);

      delete elem;
      persistentTimers[value] = NULL;
    }
}

void GLUTTimerFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  unsigned int millisec = args[0]->Uint32Value();
  int timerId = args[2]->IntegerValue();

  //find an empty timer spot and place the function there.
  int i = 0;
  bool found = false;
  for(; i < 50; i++) {
      if(persistentTimers[i] == NULL) {
          //get the function
          Handle<Function> value = Handle<Function>::Cast(args[1]);
          //assign callback and value values.
          timerData * structElem = new timerData;
          structElem->value = timerId;
          structElem->timerFunc.Reset(v8::Isolate::GetCurrent(), value);
          persistentTimers[i] = structElem;
          found = true;
          break;
      }
  }

  //TODO add dynamic resize for persistent Timers
  if(!found) {
    args.GetReturnValue().SetUndefined();
    return;
  }

  //make call
  //Don't pass the actual *value*, but an id to our persistent Function
  glutTimerFunc(( unsigned int ) millisec, (  void (* )( int )) callbackTimerFunc, ( int ) i);
  args.GetReturnValue().SetUndefined();
}



Persistent<Function> persistentMenuStateFunc;

void funcMenuStateFunc ( int arg0) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[1];
  valueArr[0] = Integer::New(v8::Isolate::GetCurrent(), arg0);
  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localMenuStateFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentMenuStateFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localMenuStateFunc->Call(glut_persistent_context->Global(), 1, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in MenuStateFunc: %s\n", *error);
  }
}

void GLUTMenuStateFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentMenuStateFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentMenuStateFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutMenuStateFunc((void (*)(int state)) funcMenuStateFunc);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentSpecialFunc;

void funcSpecialFunc ( int arg0,int arg1,int arg2) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[3];
  valueArr[0] = Integer::New(v8::Isolate::GetCurrent(), arg0);
  valueArr[1] = Integer::New(v8::Isolate::GetCurrent(), arg1);
  valueArr[2] = Integer::New(v8::Isolate::GetCurrent(), arg2);
  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localSpecialFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentSpecialFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localSpecialFunc->Call(glut_persistent_context->Global(), 3, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in SpecialFunc: %s\n", *error);
  }
}

void GLUTSpecialFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentSpecialFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentSpecialFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutSpecialFunc((void (*)(int key, int x, int y)) funcSpecialFunc);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentSpaceballMotionFunc;

void funcSpaceballMotionFunc ( int arg0,int arg1,int arg2) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[3];
  valueArr[0] = Integer::New(v8::Isolate::GetCurrent(), arg0);
  valueArr[1] = Integer::New(v8::Isolate::GetCurrent(), arg1);
  valueArr[2] = Integer::New(v8::Isolate::GetCurrent(), arg2);
  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localSpaceballMotionFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentSpaceballMotionFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localSpaceballMotionFunc->Call(glut_persistent_context->Global(), 3, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in SpaceballMotionFunc: %s\n", *error);
  }
}

void GLUTSpaceballMotionFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentSpaceballMotionFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentSpaceballMotionFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutSpaceballMotionFunc((void (*)(int x, int y, int z)) funcSpaceballMotionFunc);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentSpaceballRotateFunc;

void funcSpaceballRotateFunc ( int arg0,int arg1,int arg2) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[3];
  valueArr[0] = Integer::New(v8::Isolate::GetCurrent(), arg0);
  valueArr[1] = Integer::New(v8::Isolate::GetCurrent(), arg1);
  valueArr[2] = Integer::New(v8::Isolate::GetCurrent(), arg2);
  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localSpaceballRotateFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentSpaceballRotateFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localSpaceballRotateFunc->Call(glut_persistent_context->Global(), 3, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in SpaceballRotateFunc: %s\n", *error);
  }
}

void GLUTSpaceballRotateFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentSpaceballRotateFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentSpaceballRotateFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutSpaceballRotateFunc((void (*)(int x, int y, int z)) funcSpaceballRotateFunc);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentSpaceballButtonFunc;

void funcSpaceballButtonFunc ( int arg0,int arg1) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[2];
  valueArr[0] = Integer::New(v8::Isolate::GetCurrent(), arg0);
  valueArr[1] = Integer::New(v8::Isolate::GetCurrent(), arg1);
  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localSpaceballButtonFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentSpaceballButtonFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localSpaceballButtonFunc->Call(glut_persistent_context->Global(), 2, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in SpaceballButtonFunc: %s\n", *error);
  }
}

void GLUTSpaceballButtonFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentSpaceballButtonFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentSpaceballButtonFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutSpaceballButtonFunc((void (*)(int button, int state)) funcSpaceballButtonFunc);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentButtonBoxFunc;

void funcButtonBoxFunc ( int arg0,int arg1) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[2];
  valueArr[0] = Integer::New(v8::Isolate::GetCurrent(), arg0);
  valueArr[1] = Integer::New(v8::Isolate::GetCurrent(), arg1);
  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localButtonBoxFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentButtonBoxFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localButtonBoxFunc->Call(glut_persistent_context->Global(), 2, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in ButtonBoxFunc: %s\n", *error);
  }
}

void GLUTButtonBoxFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentButtonBoxFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentButtonBoxFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutButtonBoxFunc((void (*)(int button, int state)) funcButtonBoxFunc);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentDialsFunc;

void funcDialsFunc ( int arg0,int arg1) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[2];
  valueArr[0] = Integer::New(v8::Isolate::GetCurrent(), arg0);
  valueArr[1] = Integer::New(v8::Isolate::GetCurrent(), arg1);
  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localDialsFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentDialsFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localDialsFunc->Call(glut_persistent_context->Global(), 2, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in DialsFunc: %s\n", *error);
  }
}

void GLUTDialsFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentDialsFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentDialsFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutDialsFunc((void (*)(int dial, int value)) funcDialsFunc);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentTabletMotionFunc;

void funcTabletMotionFunc ( int arg0,int arg1) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[2];
  valueArr[0] = Integer::New(v8::Isolate::GetCurrent(), arg0);
  valueArr[1] = Integer::New(v8::Isolate::GetCurrent(), arg1);
  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localTabletMotionFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentTabletMotionFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localTabletMotionFunc->Call(glut_persistent_context->Global(), 2, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in TabletMotionFunc: %s\n", *error);
  }
}

void GLUTTabletMotionFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentTabletMotionFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentTabletMotionFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutTabletMotionFunc((void (*)(int x, int y)) funcTabletMotionFunc);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentTabletButtonFunc;

void funcTabletButtonFunc ( int arg0,int arg1,int arg2,int arg3) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[4];
  valueArr[0] = Integer::New(v8::Isolate::GetCurrent(), arg0);
  valueArr[1] = Integer::New(v8::Isolate::GetCurrent(), arg1);
  valueArr[2] = Integer::New(v8::Isolate::GetCurrent(), arg2);
  valueArr[3] = Integer::New(v8::Isolate::GetCurrent(), arg3);
  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localTabletButtonFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentTabletButtonFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localTabletButtonFunc->Call(glut_persistent_context->Global(), 4, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in TabletButtonFunc: %s\n", *error);
  }
}

void GLUTTabletButtonFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentTabletButtonFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentTabletButtonFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutTabletButtonFunc((void (*)(int button, int state, int x, int y)) funcTabletButtonFunc);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentMenuStatusFunc;

void funcMenuStatusFunc ( int arg0,int arg1,int arg2) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[3];
  valueArr[0] = Integer::New(v8::Isolate::GetCurrent(), arg0);
  valueArr[1] = Integer::New(v8::Isolate::GetCurrent(), arg1);
  valueArr[2] = Integer::New(v8::Isolate::GetCurrent(), arg2);
  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localMenuStatusFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentMenuStatusFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localMenuStatusFunc->Call(glut_persistent_context->Global(), 3, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in MenuStatusFunc: %s\n", *error);
  }
}

void GLUTMenuStatusFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentMenuStatusFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentMenuStatusFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutMenuStatusFunc((void (*)(int status, int x, int y)) funcMenuStatusFunc);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentOverlayDisplayFunc;

void funcOverlayDisplayFunc ( ) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[0];

  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localOverlayDisplayFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentOverlayDisplayFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localOverlayDisplayFunc->Call(glut_persistent_context->Global(), 0, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in OverlayDisplayFunc: %s\n", *error);
  }
}

void GLUTOverlayDisplayFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentOverlayDisplayFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentOverlayDisplayFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutOverlayDisplayFunc((void (*)(void)) funcOverlayDisplayFunc);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentWindowStatusFunc;

void funcWindowStatusFunc ( int arg0) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[1];
  valueArr[0] = Integer::New(v8::Isolate::GetCurrent(), arg0);
  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localWindowStatusFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentWindowStatusFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localWindowStatusFunc->Call(glut_persistent_context->Global(), 1, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in WindowStatusFunc: %s\n", *error);
  }
}

void GLUTWindowStatusFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentWindowStatusFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentWindowStatusFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutWindowStatusFunc((void (*)(int state)) funcWindowStatusFunc);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentKeyboardUpFunc;

void funcKeyboardUpFunc ( unsigned char arg0,int arg1,int arg2) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[3];
  valueArr[0] = Integer::New(v8::Isolate::GetCurrent(), arg0);
  valueArr[1] = Integer::New(v8::Isolate::GetCurrent(), arg1);
  valueArr[2] = Integer::New(v8::Isolate::GetCurrent(), arg2);
  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localKeyboardUpFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentKeyboardUpFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localKeyboardUpFunc->Call(glut_persistent_context->Global(), 3, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in KeyboardUpFunc: %s\n", *error);
  }
}

void GLUTKeyboardUpFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentKeyboardUpFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentKeyboardUpFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutKeyboardUpFunc((void (*)(unsigned char key, int x, int y)) funcKeyboardUpFunc);
  args.GetReturnValue().SetUndefined();
}




Persistent<Function> persistentSpecialUpFunc;

void funcSpecialUpFunc ( int arg0,int arg1,int arg2) {
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());

  Handle<Value> valueArr[3];
  valueArr[0] = Integer::New(v8::Isolate::GetCurrent(), arg0);
  valueArr[1] = Integer::New(v8::Isolate::GetCurrent(), arg1);
  valueArr[2] = Integer::New(v8::Isolate::GetCurrent(), arg2);
  
  TryCatch try_catch(v8::Isolate::GetCurrent());
  Local<Function> localSpecialUpFunc = Local<Function>::New(v8::Isolate::GetCurrent(), persistentSpecialUpFunc);
  Local<Context> glut_persistent_context = Local<Context>::New(v8::Isolate::GetCurrent(), GlutFactory::glut_persistent_context);
  Handle<Value> result = localSpecialUpFunc->Call(glut_persistent_context->Global(), 3, valueArr);
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    fprintf(stderr, "Exception in SpecialUpFunc: %s\n", *error);
  }
}

void GLUTSpecialUpFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1 || !args[0]->IsFunction()) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //get arguments
  //delete previous assigned function
  persistentSpecialUpFunc.Reset();
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  persistentSpecialUpFunc.Reset(v8::Isolate::GetCurrent(), value0);

  //make call
  glutSpecialUpFunc((void (*)(int key, int x, int y)) funcSpecialUpFunc);
  args.GetReturnValue().SetUndefined();
}




void GLUTJoystickFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  Handle<Function> value0 = Handle<Function>::Cast(args[0]);
  void* arg0 = *value0;
  int arg1 = args[1]->IntegerValue();

  //make call
  glutJoystickFunc((void (*)(unsigned int buttonMask, int x, int y, int z))arg0, (int)arg1);
  args.GetReturnValue().SetUndefined();
}




void GLUTSetColorCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  double arg1 = args[1]->NumberValue();
  double arg2 = args[2]->NumberValue();
  double arg3 = args[3]->NumberValue();

  //make call
  glutSetColor((int)arg0, (GLfloat)arg1, (GLfloat)arg2, (GLfloat)arg3);
  args.GetReturnValue().SetUndefined();
}




void GLUTGetColorCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();

  //make call
  glutGetColor((int)arg0, (int)arg1);
  args.GetReturnValue().SetUndefined();
}




void GLUTCopyColormapCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glutCopyColormap((int)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTGetCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glutGet((GLenum)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTDeviceGetCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glutDeviceGet((GLenum)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTExtensionSupportedCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  String::Utf8Value value0(args[0]);
  char* arg0 = *value0;

  //make call
  glutExtensionSupported((const char*)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTGetModifiersCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutGetModifiers();
  args.GetReturnValue().SetUndefined();
}




void GLUTLayerGetCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glutLayerGet((GLenum)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTBitmapCharacterCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  String::Utf8Value value0(args[0]);
  char* key0 = *value0;
  void* arg0 = font_[key0];
  int arg1 = args[1]->IntegerValue();

  //make call
  glutBitmapCharacter((void*)arg0, (int)arg1);
  args.GetReturnValue().SetUndefined();
}




void GLUTBitmapWidthCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  String::Utf8Value value0(args[0]);
  char* key0 = *value0;
  void* arg0 = font_[key0];
  int arg1 = args[1]->IntegerValue();

  //make call
  glutBitmapWidth((void*)arg0, (int)arg1);
  args.GetReturnValue().SetUndefined();
}




void GLUTStrokeCharacterCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  String::Utf8Value value0(args[0]);
  char* key0 = *value0;
  void* arg0 = font_[key0];
  int arg1 = args[1]->IntegerValue();

  //make call
  glutStrokeCharacter((void*)arg0, (int)arg1);
  args.GetReturnValue().SetUndefined();
}




void GLUTStrokeWidthCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  String::Utf8Value value0(args[0]);
  char* key0 = *value0;
  void* arg0 = font_[key0];
  int arg1 = args[1]->IntegerValue();

  //make call
  glutStrokeWidth((void*)arg0, (int)arg1);
  args.GetReturnValue().SetUndefined();
}




void GLUTBitmapLengthCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  String::Utf8Value value0(args[0]);
  char* key0 = *value0;
  void* arg0 = font_[key0];
  String::Utf8Value value1(args[1]);
  char* arg1 = *value1;

  //make call
  glutBitmapLength((void*)arg0, (const unsigned char*)arg1);
  args.GetReturnValue().SetUndefined();
}




void GLUTStrokeLengthCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 2) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  String::Utf8Value value0(args[0]);
  char* key0 = *value0;
  void* arg0 = font_[key0];
  String::Utf8Value value1(args[1]);
  char* arg1 = *value1;

  //make call
  glutStrokeLength((void*)arg0, (const unsigned char*)arg1);
  args.GetReturnValue().SetUndefined();
}




void GLUTWireSphereCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glutWireSphere((GLdouble)arg0, (GLint)arg1, (GLint)arg2);
  args.GetReturnValue().SetUndefined();
}




void GLUTSolidSphereCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 3) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();

  //make call
  glutSolidSphere((GLdouble)arg0, (GLint)arg1, (GLint)arg2);
  args.GetReturnValue().SetUndefined();
}




void GLUTWireConeCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glutWireCone((GLdouble)arg0, (GLdouble)arg1, (GLint)arg2, (GLint)arg3);
  args.GetReturnValue().SetUndefined();
}




void GLUTSolidConeCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glutSolidCone((GLdouble)arg0, (GLdouble)arg1, (GLint)arg2, (GLint)arg3);
  args.GetReturnValue().SetUndefined();
}




void GLUTWireCubeCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();

  //make call
  glutWireCube((GLdouble)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTSolidCubeCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();

  //make call
  glutSolidCube((GLdouble)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTWireTorusCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glutWireTorus((GLdouble)arg0, (GLdouble)arg1, (GLint)arg2, (GLint)arg3);
  args.GetReturnValue().SetUndefined();
}




void GLUTSolidTorusCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glutSolidTorus((GLdouble)arg0, (GLdouble)arg1, (GLint)arg2, (GLint)arg3);
  args.GetReturnValue().SetUndefined();
}




void GLUTWireDodecahedronCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutWireDodecahedron();
  args.GetReturnValue().SetUndefined();
}




void GLUTSolidDodecahedronCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutSolidDodecahedron();
  args.GetReturnValue().SetUndefined();
}




void GLUTWireTeapotCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();

  //make call
  glutWireTeapot((GLdouble)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTSolidTeapotCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  double arg0 = args[0]->NumberValue();

  //make call
  glutSolidTeapot((GLdouble)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTWireOctahedronCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutWireOctahedron();
  args.GetReturnValue().SetUndefined();
}




void GLUTSolidOctahedronCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutSolidOctahedron();
  args.GetReturnValue().SetUndefined();
}




void GLUTWireTetrahedronCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutWireTetrahedron();
  args.GetReturnValue().SetUndefined();
}




void GLUTSolidTetrahedronCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutSolidTetrahedron();
  args.GetReturnValue().SetUndefined();
}




void GLUTWireIcosahedronCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutWireIcosahedron();
  args.GetReturnValue().SetUndefined();
}




void GLUTSolidIcosahedronCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutSolidIcosahedron();
  args.GetReturnValue().SetUndefined();
}




void GLUTVideoResizeGetCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glutVideoResizeGet((GLenum)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTSetupVideoResizingCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutSetupVideoResizing();
  args.GetReturnValue().SetUndefined();
}




void GLUTStopVideoResizingCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutStopVideoResizing();
  args.GetReturnValue().SetUndefined();
}




void GLUTVideoResizeCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glutVideoResize((int)arg0, (int)arg1, (int)arg2, (int)arg3);
  args.GetReturnValue().SetUndefined();
}




void GLUTVideoPanCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 4) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();
  int arg1 = args[1]->IntegerValue();
  int arg2 = args[2]->IntegerValue();
  int arg3 = args[3]->IntegerValue();

  //make call
  glutVideoPan((int)arg0, (int)arg1, (int)arg2, (int)arg3);
  args.GetReturnValue().SetUndefined();
}




void GLUTReportErrorsCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutReportErrors();
  args.GetReturnValue().SetUndefined();
}




void GetGLUT_KEY_REPEAT_OFF(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_REPEAT_OFF));
}




void GetGLUT_KEY_REPEAT_ON(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_REPEAT_ON));
}




void GetGLUT_KEY_REPEAT_DEFAULT(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_KEY_REPEAT_DEFAULT));
}




void GetGLUT_JOYSTICK_BUTTON_A(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_JOYSTICK_BUTTON_A));
}




void GetGLUT_JOYSTICK_BUTTON_B(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_JOYSTICK_BUTTON_B));
}




void GetGLUT_JOYSTICK_BUTTON_C(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_JOYSTICK_BUTTON_C));
}




void GetGLUT_JOYSTICK_BUTTON_D(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_JOYSTICK_BUTTON_D));
}




void GLUTIgnoreKeyRepeatCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glutIgnoreKeyRepeat((int)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTSetKeyRepeatCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glutSetKeyRepeat((int)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTForceJoystickFuncCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutForceJoystickFunc();
  args.GetReturnValue().SetUndefined();
}




void GetGLUT_GAME_MODE_ACTIVE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_GAME_MODE_ACTIVE));
}




void GetGLUT_GAME_MODE_POSSIBLE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_GAME_MODE_POSSIBLE));
}




void GetGLUT_GAME_MODE_WIDTH(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_GAME_MODE_WIDTH));
}




void GetGLUT_GAME_MODE_HEIGHT(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_GAME_MODE_HEIGHT));
}




void GetGLUT_GAME_MODE_PIXEL_DEPTH(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_GAME_MODE_PIXEL_DEPTH));
}




void GetGLUT_GAME_MODE_REFRESH_RATE(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_GAME_MODE_REFRESH_RATE));
}




void GetGLUT_GAME_MODE_DISPLAY_CHANGED(Local<String> property,
                      const PropertyCallbackInfo<Value> &info) {
    info.GetReturnValue().Set(Uint32::New(v8::Isolate::GetCurrent(), GLUT_GAME_MODE_DISPLAY_CHANGED));
}




void GLUTGameModeStringCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  String::Utf8Value value0(args[0]);
  char* arg0 = *value0;

  //make call
  glutGameModeString((const char*)arg0);
  args.GetReturnValue().SetUndefined();
}




void GLUTEnterGameModeCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutEnterGameMode();
  args.GetReturnValue().SetUndefined();
}




void GLUTLeaveGameModeCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 0) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments

  //make call
  glutLeaveGameMode();
  args.GetReturnValue().SetUndefined();
}




void GLUTGameModeGetCallback(const FunctionCallbackInfo<Value>& args) {
  //if less that nbr of formal parameters then do nothing
  if (args.Length() < 1) {
    args.GetReturnValue().SetUndefined();
    return;
  }
  //define handle scope
  HandleScope scope(v8::Isolate::GetCurrent());
  //get arguments
  int arg0 = args[0]->IntegerValue();

  //make call
  glutGameModeGet((GLenum)arg0);
  args.GetReturnValue().SetUndefined();
}



Handle<ObjectTemplate> GlutFactory::createGlut(int* pargc, char** argv) {
      pargc_ = pargc;
      argv_  = argv;
      
      Handle<ObjectTemplate> Glut = ObjectTemplate::New();
      Glut->SetInternalFieldCount(1);

     font_["STROKE_ROMAN"] = GLUT_STROKE_ROMAN;

     font_["STROKE_MONO_ROMAN"] = GLUT_STROKE_MONO_ROMAN;

     font_["BITMAP_9_BY_15"] = GLUT_BITMAP_9_BY_15;

     font_["BITMAP_8_BY_13"] = GLUT_BITMAP_8_BY_13;

     font_["BITMAP_TIMES_ROMAN_10"] = GLUT_BITMAP_TIMES_ROMAN_10;

     font_["BITMAP_TIMES_ROMAN_24"] = GLUT_BITMAP_TIMES_ROMAN_24;

     font_["BITMAP_HELVETICA_10"] = GLUT_BITMAP_HELVETICA_10;

     font_["BITMAP_HELVETICA_12"] = GLUT_BITMAP_HELVETICA_12;

     font_["BITMAP_HELVETICA_18"] = GLUT_BITMAP_HELVETICA_18;
     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "APIENTRY_DEFINED"), GetGLUT_APIENTRY_DEFINED);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINGDIAPI_DEFINED"), GetGLUT_WINGDIAPI_DEFINED);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "API_VERSION"), GetGLUT_API_VERSION);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "XLIB_IMPLEMENTATION"), GetGLUT_XLIB_IMPLEMENTATION);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MACOSX_IMPLEMENTATION"), GetGLUT_MACOSX_IMPLEMENTATION);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGB"), GetGLUT_RGB);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RGBA"), GetGLUT_RGBA);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INDEX"), GetGLUT_INDEX);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SINGLE"), GetGLUT_SINGLE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DOUBLE"), GetGLUT_DOUBLE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ACCUM"), GetGLUT_ACCUM);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ALPHA"), GetGLUT_ALPHA);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEPTH"), GetGLUT_DEPTH);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STENCIL"), GetGLUT_STENCIL);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MULTISAMPLE"), GetGLUT_MULTISAMPLE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STEREO"), GetGLUT_STEREO);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LUMINANCE"), GetGLUT_LUMINANCE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NO_RECOVERY"), GetGLUT_NO_RECOVERY);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LEFT_BUTTON"), GetGLUT_LEFT_BUTTON);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MIDDLE_BUTTON"), GetGLUT_MIDDLE_BUTTON);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RIGHT_BUTTON"), GetGLUT_RIGHT_BUTTON);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DOWN"), GetGLUT_DOWN);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UP"), GetGLUT_UP);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_F1"), GetGLUT_KEY_F1);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_F2"), GetGLUT_KEY_F2);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_F3"), GetGLUT_KEY_F3);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_F4"), GetGLUT_KEY_F4);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_F5"), GetGLUT_KEY_F5);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_F6"), GetGLUT_KEY_F6);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_F7"), GetGLUT_KEY_F7);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_F8"), GetGLUT_KEY_F8);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_F9"), GetGLUT_KEY_F9);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_F10"), GetGLUT_KEY_F10);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_F11"), GetGLUT_KEY_F11);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_F12"), GetGLUT_KEY_F12);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_LEFT"), GetGLUT_KEY_LEFT);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_UP"), GetGLUT_KEY_UP);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_RIGHT"), GetGLUT_KEY_RIGHT);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_DOWN"), GetGLUT_KEY_DOWN);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_PAGE_UP"), GetGLUT_KEY_PAGE_UP);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_PAGE_DOWN"), GetGLUT_KEY_PAGE_DOWN);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_HOME"), GetGLUT_KEY_HOME);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_END"), GetGLUT_KEY_END);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_INSERT"), GetGLUT_KEY_INSERT);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LEFT"), GetGLUT_LEFT);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ENTERED"), GetGLUT_ENTERED);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MENU_NOT_IN_USE"), GetGLUT_MENU_NOT_IN_USE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MENU_IN_USE"), GetGLUT_MENU_IN_USE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NOT_VISIBLE"), GetGLUT_NOT_VISIBLE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VISIBLE"), GetGLUT_VISIBLE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "HIDDEN"), GetGLUT_HIDDEN);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FULLY_RETAINED"), GetGLUT_FULLY_RETAINED);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PARTIALLY_RETAINED"), GetGLUT_PARTIALLY_RETAINED);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FULLY_COVERED"), GetGLUT_FULLY_COVERED);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RED"), GetGLUT_RED);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GREEN"), GetGLUT_GREEN);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BLUE"), GetGLUT_BLUE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NORMAL"), GetGLUT_NORMAL);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "OVERLAY"), GetGLUT_OVERLAY);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STROKE_ROMAN"), GetGLUT_STROKE_ROMAN);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "STROKE_MONO_ROMAN"), GetGLUT_STROKE_MONO_ROMAN);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BITMAP_9_BY_15"), GetGLUT_BITMAP_9_BY_15);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BITMAP_8_BY_13"), GetGLUT_BITMAP_8_BY_13);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BITMAP_TIMES_ROMAN_10"), GetGLUT_BITMAP_TIMES_ROMAN_10);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BITMAP_TIMES_ROMAN_24"), GetGLUT_BITMAP_TIMES_ROMAN_24);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BITMAP_HELVETICA_10"), GetGLUT_BITMAP_HELVETICA_10);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BITMAP_HELVETICA_12"), GetGLUT_BITMAP_HELVETICA_12);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BITMAP_HELVETICA_18"), GetGLUT_BITMAP_HELVETICA_18);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_X"), GetGLUT_WINDOW_X);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_Y"), GetGLUT_WINDOW_Y);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_WIDTH"), GetGLUT_WINDOW_WIDTH);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_HEIGHT"), GetGLUT_WINDOW_HEIGHT);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_BUFFER_SIZE"), GetGLUT_WINDOW_BUFFER_SIZE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_STENCIL_SIZE"), GetGLUT_WINDOW_STENCIL_SIZE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_DEPTH_SIZE"), GetGLUT_WINDOW_DEPTH_SIZE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_RED_SIZE"), GetGLUT_WINDOW_RED_SIZE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_GREEN_SIZE"), GetGLUT_WINDOW_GREEN_SIZE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_BLUE_SIZE"), GetGLUT_WINDOW_BLUE_SIZE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_ALPHA_SIZE"), GetGLUT_WINDOW_ALPHA_SIZE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_ACCUM_RED_SIZE"), GetGLUT_WINDOW_ACCUM_RED_SIZE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_ACCUM_GREEN_SIZE"), GetGLUT_WINDOW_ACCUM_GREEN_SIZE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_ACCUM_BLUE_SIZE"), GetGLUT_WINDOW_ACCUM_BLUE_SIZE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_ACCUM_ALPHA_SIZE"), GetGLUT_WINDOW_ACCUM_ALPHA_SIZE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_DOUBLEBUFFER"), GetGLUT_WINDOW_DOUBLEBUFFER);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_RGBA"), GetGLUT_WINDOW_RGBA);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_PARENT"), GetGLUT_WINDOW_PARENT);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_NUM_CHILDREN"), GetGLUT_WINDOW_NUM_CHILDREN);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_COLORMAP_SIZE"), GetGLUT_WINDOW_COLORMAP_SIZE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_NUM_SAMPLES"), GetGLUT_WINDOW_NUM_SAMPLES);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_STEREO"), GetGLUT_WINDOW_STEREO);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_CURSOR"), GetGLUT_WINDOW_CURSOR);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SCREEN_WIDTH"), GetGLUT_SCREEN_WIDTH);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SCREEN_HEIGHT"), GetGLUT_SCREEN_HEIGHT);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SCREEN_WIDTH_MM"), GetGLUT_SCREEN_WIDTH_MM);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SCREEN_HEIGHT_MM"), GetGLUT_SCREEN_HEIGHT_MM);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MENU_NUM_ITEMS"), GetGLUT_MENU_NUM_ITEMS);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DISPLAY_MODE_POSSIBLE"), GetGLUT_DISPLAY_MODE_POSSIBLE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INIT_WINDOW_X"), GetGLUT_INIT_WINDOW_X);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INIT_WINDOW_Y"), GetGLUT_INIT_WINDOW_Y);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INIT_WINDOW_WIDTH"), GetGLUT_INIT_WINDOW_WIDTH);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INIT_WINDOW_HEIGHT"), GetGLUT_INIT_WINDOW_HEIGHT);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "INIT_DISPLAY_MODE"), GetGLUT_INIT_DISPLAY_MODE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ELAPSED_TIME"), GetGLUT_ELAPSED_TIME);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WINDOW_FORMAT_ID"), GetGLUT_WINDOW_FORMAT_ID);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "HAS_KEYBOARD"), GetGLUT_HAS_KEYBOARD);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "HAS_MOUSE"), GetGLUT_HAS_MOUSE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "HAS_SPACEBALL"), GetGLUT_HAS_SPACEBALL);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "HAS_DIAL_AND_BUTTON_BOX"), GetGLUT_HAS_DIAL_AND_BUTTON_BOX);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "HAS_TABLET"), GetGLUT_HAS_TABLET);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NUM_MOUSE_BUTTONS"), GetGLUT_NUM_MOUSE_BUTTONS);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NUM_SPACEBALL_BUTTONS"), GetGLUT_NUM_SPACEBALL_BUTTONS);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NUM_BUTTON_BOX_BUTTONS"), GetGLUT_NUM_BUTTON_BOX_BUTTONS);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NUM_DIALS"), GetGLUT_NUM_DIALS);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NUM_TABLET_BUTTONS"), GetGLUT_NUM_TABLET_BUTTONS);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEVICE_IGNORE_KEY_REPEAT"), GetGLUT_DEVICE_IGNORE_KEY_REPEAT);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DEVICE_KEY_REPEAT"), GetGLUT_DEVICE_KEY_REPEAT);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "HAS_JOYSTICK"), GetGLUT_HAS_JOYSTICK);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "OWNS_JOYSTICK"), GetGLUT_OWNS_JOYSTICK);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "JOYSTICK_BUTTONS"), GetGLUT_JOYSTICK_BUTTONS);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "JOYSTICK_AXES"), GetGLUT_JOYSTICK_AXES);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "JOYSTICK_POLL_RATE"), GetGLUT_JOYSTICK_POLL_RATE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "OVERLAY_POSSIBLE"), GetGLUT_OVERLAY_POSSIBLE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LAYER_IN_USE"), GetGLUT_LAYER_IN_USE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "HAS_OVERLAY"), GetGLUT_HAS_OVERLAY);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TRANSPARENT_INDEX"), GetGLUT_TRANSPARENT_INDEX);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "NORMAL_DAMAGED"), GetGLUT_NORMAL_DAMAGED);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "OVERLAY_DAMAGED"), GetGLUT_OVERLAY_DAMAGED);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VIDEO_RESIZE_POSSIBLE"), GetGLUT_VIDEO_RESIZE_POSSIBLE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VIDEO_RESIZE_IN_USE"), GetGLUT_VIDEO_RESIZE_IN_USE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VIDEO_RESIZE_X_DELTA"), GetGLUT_VIDEO_RESIZE_X_DELTA);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VIDEO_RESIZE_Y_DELTA"), GetGLUT_VIDEO_RESIZE_Y_DELTA);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VIDEO_RESIZE_WIDTH_DELTA"), GetGLUT_VIDEO_RESIZE_WIDTH_DELTA);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VIDEO_RESIZE_HEIGHT_DELTA"), GetGLUT_VIDEO_RESIZE_HEIGHT_DELTA);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VIDEO_RESIZE_X"), GetGLUT_VIDEO_RESIZE_X);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VIDEO_RESIZE_Y"), GetGLUT_VIDEO_RESIZE_Y);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VIDEO_RESIZE_WIDTH"), GetGLUT_VIDEO_RESIZE_WIDTH);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VIDEO_RESIZE_HEIGHT"), GetGLUT_VIDEO_RESIZE_HEIGHT);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ACTIVE_SHIFT"), GetGLUT_ACTIVE_SHIFT);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ACTIVE_CTRL"), GetGLUT_ACTIVE_CTRL);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ACTIVE_ALT"), GetGLUT_ACTIVE_ALT);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_RIGHT_ARROW"), GetGLUT_CURSOR_RIGHT_ARROW);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_LEFT_ARROW"), GetGLUT_CURSOR_LEFT_ARROW);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_INFO"), GetGLUT_CURSOR_INFO);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_DESTROY"), GetGLUT_CURSOR_DESTROY);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_HELP"), GetGLUT_CURSOR_HELP);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_CYCLE"), GetGLUT_CURSOR_CYCLE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_SPRAY"), GetGLUT_CURSOR_SPRAY);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_WAIT"), GetGLUT_CURSOR_WAIT);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_TEXT"), GetGLUT_CURSOR_TEXT);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_CROSSHAIR"), GetGLUT_CURSOR_CROSSHAIR);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_UP_DOWN"), GetGLUT_CURSOR_UP_DOWN);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_LEFT_RIGHT"), GetGLUT_CURSOR_LEFT_RIGHT);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_TOP_SIDE"), GetGLUT_CURSOR_TOP_SIDE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_BOTTOM_SIDE"), GetGLUT_CURSOR_BOTTOM_SIDE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_LEFT_SIDE"), GetGLUT_CURSOR_LEFT_SIDE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_RIGHT_SIDE"), GetGLUT_CURSOR_RIGHT_SIDE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_TOP_LEFT_CORNER"), GetGLUT_CURSOR_TOP_LEFT_CORNER);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_TOP_RIGHT_CORNER"), GetGLUT_CURSOR_TOP_RIGHT_CORNER);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_BOTTOM_RIGHT_CORNER"), GetGLUT_CURSOR_BOTTOM_RIGHT_CORNER);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_BOTTOM_LEFT_CORNER"), GetGLUT_CURSOR_BOTTOM_LEFT_CORNER);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_INHERIT"), GetGLUT_CURSOR_INHERIT);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_NONE"), GetGLUT_CURSOR_NONE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CURSOR_FULL_CROSSHAIR"), GetGLUT_CURSOR_FULL_CROSSHAIR);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_REPEAT_OFF"), GetGLUT_KEY_REPEAT_OFF);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_REPEAT_ON"), GetGLUT_KEY_REPEAT_ON);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KEY_REPEAT_DEFAULT"), GetGLUT_KEY_REPEAT_DEFAULT);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "JOYSTICK_BUTTON_A"), GetGLUT_JOYSTICK_BUTTON_A);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "JOYSTICK_BUTTON_B"), GetGLUT_JOYSTICK_BUTTON_B);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "JOYSTICK_BUTTON_C"), GetGLUT_JOYSTICK_BUTTON_C);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "JOYSTICK_BUTTON_D"), GetGLUT_JOYSTICK_BUTTON_D);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GAME_MODE_ACTIVE"), GetGLUT_GAME_MODE_ACTIVE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GAME_MODE_POSSIBLE"), GetGLUT_GAME_MODE_POSSIBLE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GAME_MODE_WIDTH"), GetGLUT_GAME_MODE_WIDTH);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GAME_MODE_HEIGHT"), GetGLUT_GAME_MODE_HEIGHT);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GAME_MODE_PIXEL_DEPTH"), GetGLUT_GAME_MODE_PIXEL_DEPTH);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GAME_MODE_REFRESH_RATE"), GetGLUT_GAME_MODE_REFRESH_RATE);

     Glut->SetAccessor(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GAME_MODE_DISPLAY_CHANGED"), GetGLUT_GAME_MODE_DISPLAY_CHANGED);
     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Init"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTInitCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "InitDisplayMode"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTInitDisplayModeCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "InitDisplayString"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTInitDisplayStringCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "InitWindowPosition"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTInitWindowPositionCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "InitWindowSize"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTInitWindowSizeCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MainLoop"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTMainLoopCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CreateWindow"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTCreateWindowCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CreateSubWindow"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTCreateSubWindowCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DestroyWindow"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTDestroyWindowCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PostRedisplay"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTPostRedisplayCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PostWindowRedisplay"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTPostWindowRedisplayCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SwapBuffers"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSwapBuffersCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetWindow"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTGetWindowCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SetWindow"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSetWindowCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SetWindowTitle"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSetWindowTitleCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SetIconTitle"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSetIconTitleCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PositionWindow"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTPositionWindowCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ReshapeWindow"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTReshapeWindowCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PopWindow"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTPopWindowCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PushWindow"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTPushWindowCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "IconifyWindow"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTIconifyWindowCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ShowWindow"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTShowWindowCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "HideWindow"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTHideWindowCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "FullScreen"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTFullScreenCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SetCursor"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSetCursorCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WarpPointer"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTWarpPointerCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WMCloseFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTWMCloseFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CheckLoop"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTCheckLoopCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EstablishOverlay"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTEstablishOverlayCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RemoveOverlay"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTRemoveOverlayCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "UseLayer"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTUseLayerCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PostOverlayRedisplay"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTPostOverlayRedisplayCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PostWindowOverlayRedisplay"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTPostWindowOverlayRedisplayCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ShowOverlay"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTShowOverlayCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "HideOverlay"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTHideOverlayCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CreateMenu"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTCreateMenuCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DestroyMenu"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTDestroyMenuCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetMenu"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTGetMenuCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SetMenu"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSetMenuCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "AddMenuEntry"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTAddMenuEntryCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "AddSubMenu"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTAddSubMenuCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ChangeToMenuEntry"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTChangeToMenuEntryCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ChangeToSubMenu"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTChangeToSubMenuCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "RemoveMenuItem"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTRemoveMenuItemCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "AttachMenu"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTAttachMenuCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DetachMenu"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTDetachMenuCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DisplayFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTDisplayFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ReshapeFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTReshapeFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KeyboardFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTKeyboardFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MouseFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTMouseFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MotionFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTMotionFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "PassiveMotionFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTPassiveMotionFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EntryFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTEntryFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VisibilityFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTVisibilityFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "IdleFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTIdleFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TimerFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTTimerFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MenuStateFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTMenuStateFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SpecialFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSpecialFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SpaceballMotionFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSpaceballMotionFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SpaceballRotateFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSpaceballRotateFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SpaceballButtonFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSpaceballButtonFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ButtonBoxFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTButtonBoxFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DialsFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTDialsFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TabletMotionFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTTabletMotionFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "TabletButtonFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTTabletButtonFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "MenuStatusFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTMenuStatusFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "OverlayDisplayFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTOverlayDisplayFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WindowStatusFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTWindowStatusFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "KeyboardUpFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTKeyboardUpFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SpecialUpFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSpecialUpFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "JoystickFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTJoystickFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SetColor"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSetColorCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetColor"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTGetColorCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "CopyColormap"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTCopyColormapCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Get"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTGetCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "DeviceGet"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTDeviceGetCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ExtensionSupported"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTExtensionSupportedCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GetModifiers"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTGetModifiersCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LayerGet"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTLayerGetCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BitmapCharacter"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTBitmapCharacterCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BitmapWidth"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTBitmapWidthCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "StrokeCharacter"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTStrokeCharacterCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "StrokeWidth"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTStrokeWidthCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "BitmapLength"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTBitmapLengthCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "StrokeLength"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTStrokeLengthCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WireSphere"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTWireSphereCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SolidSphere"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSolidSphereCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WireCone"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTWireConeCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SolidCone"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSolidConeCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WireCube"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTWireCubeCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SolidCube"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSolidCubeCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WireTorus"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTWireTorusCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SolidTorus"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSolidTorusCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WireDodecahedron"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTWireDodecahedronCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SolidDodecahedron"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSolidDodecahedronCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WireTeapot"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTWireTeapotCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SolidTeapot"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSolidTeapotCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WireOctahedron"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTWireOctahedronCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SolidOctahedron"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSolidOctahedronCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WireTetrahedron"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTWireTetrahedronCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SolidTetrahedron"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSolidTetrahedronCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "WireIcosahedron"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTWireIcosahedronCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SolidIcosahedron"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSolidIcosahedronCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VideoResizeGet"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTVideoResizeGetCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SetupVideoResizing"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSetupVideoResizingCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "StopVideoResizing"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTStopVideoResizingCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VideoResize"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTVideoResizeCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "VideoPan"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTVideoPanCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ReportErrors"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTReportErrorsCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "IgnoreKeyRepeat"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTIgnoreKeyRepeatCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SetKeyRepeat"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTSetKeyRepeatCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "ForceJoystickFunc"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTForceJoystickFuncCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GameModeString"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTGameModeStringCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "EnterGameMode"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTEnterGameModeCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "LeaveGameMode"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTLeaveGameModeCallback));

     Glut->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "GameModeGet"), FunctionTemplate::New(v8::Isolate::GetCurrent(), GLUTGameModeGetCallback));


      // Again, return the result through the current handle scope.
      return Glut;
}    

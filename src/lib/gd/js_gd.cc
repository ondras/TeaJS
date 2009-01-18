#include <v8.h>
#include "js_macros.h"

#include <gd.h>
#define GD_TRUECOLOR 0
#define GD_PALETTE 1
#define GD_JPEG 2
#define GD_PNG 3
#define GD_GIF 4
#define GD_PTR gdImagePtr ptr = LOAD_PTR(0, gdImagePtr)

JS_METHOD(_image) {
	v8::HandleScope handle_scope;
	if (args.This()->InternalFieldCount() == 0) {
		return JS_EXCEPTION("Invalid call format. Use 'new Image(type, params)'");
	}
	
	int32_t type = args[0]->Int32Value();
	gdImagePtr ptr;
	
	int x = args[1]->Int32Value();
	int y = args[2]->Int32Value();
	FILE * f = NULL;

	if (type == GD_JPEG || type == GD_PNG || type == GD_GIF) {
		v8::String::Utf8Value name(args[1]);
		f = fopen(*name, "rb");
		if (f == NULL) { return JS_EXCEPTION("Cannot open file"); }
	}

	switch (type) {
		case GD_TRUECOLOR:
			ptr = gdImageCreateTrueColor(x, y);
		break;
		case GD_PALETTE:
			ptr = gdImageCreate(x, y);
		break;
		case GD_JPEG:
			ptr = gdImageCreateFromJpeg(f);
		break;
		case GD_PNG:
			ptr = gdImageCreateFromPng(f);
		break;
		case GD_GIF:
			ptr = gdImageCreateFromGif(f);
		break;
		default:
			return JS_EXCEPTION("Unknown image type");
		break;
	}
	
	if (f != NULL) { fclose(f); }
	SAVE_PTR(0, ptr);
	return args.This();
}

JS_METHOD(_destroy) {
	v8::HandleScope handle_scope;
	GD_PTR;
	gdImageDestroy(ptr);
	return v8::Undefined();
}

JS_METHOD(_save) {
	v8::HandleScope handle_scope;
	GD_PTR;

	if (args.Length() < 1) {
		return JS_EXCEPTION("Invalid call format. Use 'image.save(type, [file])'");
	}
	
	int32_t type = args[0]->Int32Value();
	bool tofile = args[1]->BooleanValue();
	int q = args[2]->Int32Value();
	if (q == 0) { q = 95; }


	if (tofile) {
		v8::String::Utf8Value name(args[1]);
		FILE * f = fopen(*name, "wb");
		if (f == NULL) { return JS_EXCEPTION("Cannot open file"); }
		switch (type) {
			case GD_JPEG:
				gdImageJpeg(ptr, f, q);
			break;
			
			case GD_GIF:
				gdImageGif(ptr, f);
			break;

			case GD_PNG:
				gdImagePng(ptr, f);
			break;

			default:
				return JS_EXCEPTION("Unknown image type");
			break;
		}
		if (f != NULL) { fclose(f); }
		return v8::Undefined();
	} else {
		int size = 0;
		void * data = NULL;
		switch (type) {
			case GD_JPEG:
				data = gdImageJpegPtr(ptr, &size, q);
			break;
			
			case GD_GIF:
				data = gdImageGifPtr(ptr, &size);
			break;

			case GD_PNG:
				data = gdImagePngPtr(ptr, &size);
			break;

			default:
				return JS_EXCEPTION("Unknown image type");
			break;
		}
		return JS_CHARARRAY((char *)data, size);
	}
}

SHARED_INIT() {
	v8::HandleScope handle_scope;
	v8::Handle<v8::FunctionTemplate> ft = v8::FunctionTemplate::New(_image);
	ft->SetClassName(JS_STR("Image"));
	ft->Set(JS_STR("Truecolor"), JS_INT(GD_TRUECOLOR));
	ft->Set(JS_STR("Palette"), JS_INT(GD_PALETTE));
	ft->Set(JS_STR("JPEG"), JS_INT(GD_JPEG));
	ft->Set(JS_STR("PNG"), JS_INT(GD_PNG));
	ft->Set(JS_STR("GIF"), JS_INT(GD_GIF));

	v8::Handle<v8::ObjectTemplate> it = ft->InstanceTemplate();
	it->SetInternalFieldCount(1);

	v8::Handle<v8::ObjectTemplate> pt = ft->PrototypeTemplate();
	pt->Set(JS_STR("save"), v8::FunctionTemplate::New(_save));
	
	target->Set(JS_STR("Image"), ft->GetFunction());		 
}

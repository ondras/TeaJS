#include <v8.h>
#include "macros.h"
#include "common.h"

#include <gd.h>
#define GD_TRUECOLOR 0
#define GD_PALETTE 1
#define GD_JPEG 2
#define GD_PNG 3
#define GD_GIF 4
#define GD_PTR gdImagePtr ptr = LOAD_PTR(0, gdImagePtr)
#define GD_COLOR(offset) int color = args[offset]->Int32Value();
#define GD_RGB \
	int r = args[0]->Int32Value(); \
	int g = args[1]->Int32Value(); \
	int b = args[2]->Int32Value()
#define GD_RGBA \
	GD_RGB; \
	int a = args[3]->Int32Value()
#define GD_SECOND \
	v8::Handle<v8::Object> __second = args[0]->ToObject(); \
	gdImagePtr ptr2 = reinterpret_cast<gdImagePtr>(v8::Handle<v8::External>::Cast(__second->GetInternalField(0))->Value())

namespace {

/**
 * Creates a GD points structure from JS array of {x:..., y:...} objects
 */
gdPointPtr gdPoints(v8::Handle<v8::Array> arr) {
	v8::HandleScope handle_scope;
	unsigned int len = arr->Length();
	gdPointPtr points = new gdPoint[len];
	v8::Handle<v8::Object> item;
	
	for (unsigned int i=0;i<len;i++) {
		item = arr->Get(JS_INT(i))->ToObject();
		points[i].x = item->Get(JS_STR("x"))->Int32Value();
		points[i].y = item->Get(JS_STR("y"))->Int32Value();
	}
	
	return points;
}

/**
 * Image constructor works in two modes:
 * a) new Image(Image.JPG|PNG|GIF, "filename.ext")
 * b) new Image(Image.TRUECOLOR|PALETTE, width, height)
 */
JS_METHOD(_image) {
	ASSERT_CONSTRUCTOR;

	int32_t type = args[0]->Int32Value();
	gdImagePtr ptr;
	
	int x = args[1]->Int32Value();
	int y = args[2]->Int32Value();
	
	void * data = NULL;
	size_t size = 0;
	
	if (type == GD_JPEG || type == GD_PNG || type == GD_GIF) {
		v8::String::Utf8Value name(args[1]);
		data = mmap_read(*name, &size);
		if (data == NULL) { return JS_EXCEPTION("Cannot open file"); }
	}

	switch (type) {
		case GD_TRUECOLOR:
			ptr = gdImageCreateTrueColor(x, y);
		break;
		case GD_PALETTE:
			ptr = gdImageCreate(x, y);
		break;
		case GD_JPEG:
			ptr = gdImageCreateFromJpegPtr(size, data);
		break;
		case GD_PNG:
			ptr = gdImageCreateFromPngPtr(size, data);
		break;
		case GD_GIF:
			ptr = gdImageCreateFromGifPtr(size, data);
		break;
		default:
			return JS_EXCEPTION("Unknown image type");
		break;
	}
	
	mmap_free((char *)data, size);
	SAVE_PTR(0, ptr);
	return args.This();
}

/**
 * @param {int} type Image.JPEG|PNG|GIF
 * @param {string} [file] File name. If not present, image data is returned as array of byte numers.
 */
JS_METHOD(_save) {
	GD_PTR;

	if (args.Length() < 1) {
		return JS_EXCEPTION("Invalid call format. Use 'image.save(type, [file])'");
	}
	
	int32_t type = args[0]->Int32Value();
	bool tofile = args[1]->BooleanValue();
	int q = args[2]->Int32Value();
	if (q == 0) { q = 95; }

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

	if (tofile) {
		v8::String::Utf8Value name(args[1]);
		int result = mmap_write(*name, (void *)data, size);
		gdFree(data);
		if (result == -1) { return JS_EXCEPTION("Cannot open file"); }
		return v8::Undefined();
	} else {
		v8::Handle<v8::Array> arr = JS_CHARARRAY((char *)data, size);
		gdFree(data);
		return arr;
	}
}

/**
 * All following functions are simple wrappers around gd* methods
 */

/**/

JS_METHOD(_truecolor) {
	GD_RGB;
	int result = gdTrueColor(r, g, b);
	return JS_INT(result);
}

JS_METHOD(_truecoloralpha) {
	GD_RGBA;
	int result = gdTrueColorAlpha(r, g, b, a);
	return JS_INT(result);
}

/**/

JS_METHOD(_destroy) {
	GD_PTR;
	gdImageDestroy(ptr);
	return v8::Undefined();
}

JS_METHOD(_colorallocate) {
	GD_PTR;
	GD_RGB;
	
	int result = gdImageColorAllocate(ptr, r, g, b);
	if (result == -1) {
		return JS_EXCEPTION("Cannot allocate color");
	} else {
		return JS_INT(result);
	}
}

JS_METHOD(_colorallocatealpha) {
	GD_PTR;
	GD_RGBA;
	
	int result = gdImageColorAllocateAlpha(ptr, r, g, b, a);
	if (result == -1) {
		return JS_EXCEPTION("Cannot allocate color");
	} else {
		return JS_INT(result);
	}
}

JS_METHOD(_colorclosest) {
	GD_PTR;
	GD_RGB;
	
	int result = gdImageColorClosest(ptr, r, g, b);
	if (result == -1) {
		return JS_EXCEPTION("No collors allocated");
	} else {
		return JS_INT(result);
	}
}

JS_METHOD(_colorclosestalpha) {
	GD_PTR;
	GD_RGBA;
	
	int result = gdImageColorClosestAlpha(ptr, r, g, b, a);
	if (result == -1) {
		return JS_EXCEPTION("No collors allocated");
	} else {
		return JS_INT(result);
	}
}

JS_METHOD(_colorclosesthwb) {
	GD_PTR;
	GD_RGB;
	
	int result = gdImageColorClosestHWB(ptr, r, g, b);
	if (result == -1) {
		return JS_EXCEPTION("No collors allocated");
	} else {
		return JS_INT(result);
	}
}

JS_METHOD(_colorexact) {
	GD_PTR;
	GD_RGB;
	
	int result = gdImageColorExact(ptr, r, g, b);
	return JS_INT(result);
}

JS_METHOD(_colorresolve) {
	GD_PTR;
	GD_RGB;
	
	int result = gdImageColorResolve(ptr, r, g, b);
	return JS_INT(result);
}

JS_METHOD(_colorresolvealpha) {
	GD_PTR;
	GD_RGBA;
	
	int result = gdImageColorResolveAlpha(ptr, r, g, b, a);
	return JS_INT(result);
}

JS_METHOD(_colorstotal) {
	GD_PTR;
	
	int result = gdImageColorsTotal(ptr);
	return JS_INT(result);
}

JS_METHOD(_red) {
	GD_PTR;
	int c = args[0]->Int32Value();
	
	int result = gdImageRed(ptr, c);
	return JS_INT(result);
}

JS_METHOD(_green) {
	GD_PTR;
	int c = args[0]->Int32Value();
	
	int result = gdImageGreen(ptr, c);
	return JS_INT(result);
}

JS_METHOD(_blue) {
	GD_PTR;
	int c = args[0]->Int32Value();
	
	int result = gdImageBlue(ptr, c);
	return JS_INT(result);
}

JS_METHOD(_getinterlaced) {
	GD_PTR;
	
	int result = gdImageGetInterlaced(ptr);
	return JS_BOOL(result);
}

JS_METHOD(_gettransparent) {
	GD_PTR;
	
	int result = gdImageGetTransparent(ptr);
	return JS_INT(result);
}

JS_METHOD(_colordeallocate) {
	GD_PTR;
	int c = args[0]->Int32Value();
	
	gdImageColorDeallocate(ptr, c);
	return args.This();
}

JS_METHOD(_colortransparent) {
	GD_PTR;
	int c = args[0]->Int32Value();
	
	gdImageColorTransparent(ptr, c);
	return args.This();
}

JS_METHOD(_alpha) {
	GD_PTR;
	int c = args[0]->Int32Value();
	
	int result = gdImageAlpha(ptr, c);
	return JS_INT(result);
}

JS_METHOD(_getpixel) {
	GD_PTR;
	int x = args[0]->Int32Value();
	int y = args[1]->Int32Value();
	
	int result = gdImageGetPixel(ptr, x, y);
	return JS_INT(result);
}

JS_METHOD(_boundssafe) {
	GD_PTR;
	int x = args[0]->Int32Value();
	int y = args[1]->Int32Value();
	
	int result = gdImageBoundsSafe(ptr, x, y);
	return JS_BOOL(result);
}

JS_METHOD(_sx) {
	GD_PTR;
	
	int result = gdImageSX(ptr);
	return JS_INT(result);
}

JS_METHOD(_sy) {
	GD_PTR;
	
	int result = gdImageSY(ptr);
	return JS_INT(result);
}

JS_METHOD(_imagetruecolor) {
	GD_PTR;
	
	int result = gdImageTrueColor(ptr);
	return JS_BOOL(result);
}

/**/

JS_METHOD(_setpixel) {
	GD_PTR;
	GD_COLOR(2);
	int x = args[0]->Int32Value();
	int y = args[1]->Int32Value();
	
	gdImageSetPixel(ptr, x, y, color);
	return args.This();
}

JS_METHOD(_line) {
	GD_PTR;
	GD_COLOR(4);
	int x1 = args[0]->Int32Value();
	int y1 = args[1]->Int32Value();
	int x2 = args[2]->Int32Value();
	int y2 = args[3]->Int32Value();
	
	gdImageLine(ptr, x1, y1, x2, y2, color);
	return args.This();
}

JS_METHOD(_polygon) {
	GD_PTR;
	GD_COLOR(1);

	if (!args[0]->IsArray()) { return JS_EXCEPTION("Non-array argument passed to polygon()"); }
	v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(args[0]);
	gdPointPtr points = gdPoints(arr);
	gdImagePolygon(ptr, points, arr->Length(), color);
	delete[] points;
	return args.This();
}

JS_METHOD(_openpolygon) {
	GD_PTR;
	GD_COLOR(1);
	
	if (!args[0]->IsArray()) { return JS_EXCEPTION("Non-array argument passed to openPolygon()"); }
	v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(args[0]);
	gdPointPtr points = gdPoints(arr);
	gdImageOpenPolygon(ptr, points, arr->Length(), color);
	delete[] points;
	return args.This();
}

JS_METHOD(_rectangle) {
	GD_PTR;
	GD_COLOR(4);
	
	int x1 = args[0]->Int32Value();
	int y1 = args[1]->Int32Value();
	int x2 = args[2]->Int32Value();
	int y2 = args[3]->Int32Value();
	
	gdImageRectangle(ptr, x1, y1, x2, y2, color);
	return args.This();
}

JS_METHOD(_filledrectangle) {
	GD_PTR;
	GD_COLOR(4);
	
	int x1 = args[0]->Int32Value();
	int y1 = args[1]->Int32Value();
	int x2 = args[2]->Int32Value();
	int y2 = args[3]->Int32Value();
	
	gdImageFilledRectangle(ptr, x1, y1, x2, y2, color);
	return args.This();
}

JS_METHOD(_filledpolygon) {
	GD_PTR;
	GD_COLOR(1);
	
	if (!args[0]->IsArray()) { return JS_EXCEPTION("Non-array argument passed to filledPolygon()"); }
	v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(args[0]);
	gdPointPtr points = gdPoints(arr);
	gdImageFilledPolygon(ptr, points, arr->Length(), color);
	delete[] points;
	return args.This();
}

JS_METHOD(_arc) {
	GD_PTR;
	GD_COLOR(6);
	int cx = args[0]->Int32Value();
	int cy = args[1]->Int32Value();
	int w = args[2]->Int32Value();
	int h = args[3]->Int32Value();
	int s = args[4]->Int32Value();
	int e = args[5]->Int32Value();
	
	gdImageArc(ptr, cx, cy, w, h, s, e, color);
	return args.This();
}

JS_METHOD(_filledarc) {
	GD_PTR;
	GD_COLOR(6);
	int cx = args[0]->Int32Value();
	int cy = args[1]->Int32Value();
	int w = args[2]->Int32Value();
	int h = args[3]->Int32Value();
	int s = args[4]->Int32Value();
	int e = args[5]->Int32Value();
	int style = args[7]->Int32Value();
	
	gdImageFilledArc(ptr, cx, cy, w, h, s, e, color, style);
	return args.This();
}

JS_METHOD(_filledellipse) {
	GD_PTR;
	GD_COLOR(4);
	int cx = args[0]->Int32Value();
	int cy = args[1]->Int32Value();
	int w = args[2]->Int32Value();
	int h = args[3]->Int32Value();
	
	gdImageFilledEllipse(ptr, cx, cy, w, h, color);
	return args.This();
}

JS_METHOD(_filltoborder) {
	GD_PTR;
	GD_COLOR(3);
	int x = args[0]->Int32Value();
	int y = args[1]->Int32Value();
	int border = args[2]->Int32Value();
	
	gdImageFillToBorder(ptr, x, y, border, color);
	return args.This();
}

JS_METHOD(_fill) {
	GD_PTR;
	GD_COLOR(2);
	int x = args[0]->Int32Value();
	int y = args[1]->Int32Value();
	
	gdImageFill(ptr, x, y, color);
	return args.This();
}

JS_METHOD(_setantialiased) {
	GD_PTR;
	GD_COLOR(0);
	
	gdImageSetAntiAliased(ptr, color);
	return args.This();
}

JS_METHOD(_setantialiaseddontblend) {
	GD_PTR;
	GD_COLOR(0);
	int color2 = args[1]->Int32Value();
	
	gdImageSetAntiAliasedDontBlend(ptr, color, color2);
	return args.This();
}

JS_METHOD(_setbrush) {
	GD_PTR;
	GD_SECOND;
	
	gdImageSetBrush(ptr, ptr2);
	return args.This();
}

JS_METHOD(_settile) {
	GD_PTR;
	GD_SECOND;
	
	gdImageSetTile(ptr, ptr2);
	return args.This();
}

JS_METHOD(_setstyle) {
	GD_PTR;
	if (!args[0]->IsArray()) { return JS_EXCEPTION("Non-array argument passed to setStyle()"); }
	v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(args[0]);
	unsigned int len = arr->Length();
	
	int * style = new int[len];
	for (unsigned i=0;i<len;i++) {
		style[i] = arr->Get(JS_INT(i))->Int32Value();
	}
	 
	gdImageSetStyle(ptr, style, len);
	delete[] style;
	
	return args.This();
}

JS_METHOD(_setthickness) {
	GD_PTR;
	int t = args[0]->Int32Value();
	 
	gdImageSetThickness(ptr, t);
	return args.This();
}

JS_METHOD(_alphablending) {
	GD_PTR;
	int mode = args[0]->Int32Value();
	 
	gdImageAlphaBlending(ptr, mode);
	return args.This();
}

JS_METHOD(_savealpha) {
	GD_PTR;
	int mode = args[0]->Int32Value();
	 
	gdImageSaveAlpha(ptr, mode);
	return args.This();
}

JS_METHOD(_setclip) {
	GD_PTR;
	int x1 = args[0]->Int32Value();
	int y1 = args[1]->Int32Value();
	int x2 = args[2]->Int32Value();
	int y2 = args[3]->Int32Value();
	 
	gdImageSetClip(ptr, x1, y1, x2, y2);
	return args.This();
}

JS_METHOD(_getclip) {
	GD_PTR;
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;
	 
	gdImageGetClip(ptr, &x1, &y1, &x2, &y2);
	v8::Handle<v8::Array> arr = v8::Array::New(4);
	
	arr->Set(JS_INT(0), JS_INT(x1));
	arr->Set(JS_INT(1), JS_INT(y1));
	arr->Set(JS_INT(2), JS_INT(x2));
	arr->Set(JS_INT(3), JS_INT(y2));
	return arr;
}

JS_METHOD(_string) {
	GD_PTR;
	GD_COLOR(0);

	int brect[8];
	v8::String::Utf8Value font(args[1]);
	double size = args[2]->NumberValue();
	double angle = args[3]->NumberValue();
	int x = args[4]->Int32Value();
	int y = args[5]->Int32Value();
	v8::String::Utf8Value str(args[6]);
	
	char * result = gdImageStringFT(ptr, &(brect[0]), color, *font, size, angle, x, y, *str);
	if (result == NULL) {
		v8::Handle<v8::Array> arr = v8::Array::New(8);
		for (int i=0;i<8;i++) {
			arr->Set(JS_INT(i), JS_INT(brect[i]));
		}
		return arr;
	} else {
		return JS_EXCEPTION(result);
	}
}

JS_METHOD(_copy) {
	GD_PTR;
	GD_SECOND;
	
	int dstx = args[1]->Int32Value();
	int dsty = args[2]->Int32Value();
	int srcx = args[3]->Int32Value();
	int srcy = args[4]->Int32Value();
	int w = args[5]->Int32Value();
	int h = args[6]->Int32Value();

	gdImageCopy(ptr, ptr2, dstx, dsty, srcx, srcy, w, h);
	return args.This();
}

JS_METHOD(_copyresized) {
	GD_PTR;
	GD_SECOND;
	
	int dstx = args[1]->Int32Value();
	int dsty = args[2]->Int32Value();
	int srcx = args[3]->Int32Value();
	int srcy = args[4]->Int32Value();
	int dstw = args[5]->Int32Value();
	int dsth = args[6]->Int32Value();
	int srcw = args[7]->Int32Value();
	int srch = args[8]->Int32Value();

	gdImageCopyResized(ptr, ptr2, dstx, dsty, srcx, srcy, dstw, dsth, srcw, srch);
	return args.This();
}

JS_METHOD(_copyresampled) {
	GD_PTR;
	GD_SECOND;
	
	int dstx = args[1]->Int32Value();
	int dsty = args[2]->Int32Value();
	int srcx = args[3]->Int32Value();
	int srcy = args[4]->Int32Value();
	int dstw = args[5]->Int32Value();
	int dsth = args[6]->Int32Value();
	int srcw = args[7]->Int32Value();
	int srch = args[8]->Int32Value();

	gdImageCopyResampled(ptr, ptr2, dstx, dsty, srcx, srcy, dstw, dsth, srcw, srch);
	return args.This();
}

JS_METHOD(_copyrotated) {
	GD_PTR;
	GD_SECOND;
	
	double dstx = args[1]->NumberValue();
	double dsty = args[2]->NumberValue();
	int srcx = args[3]->Int32Value();
	int srcy = args[4]->Int32Value();
	int srcw = args[5]->Int32Value();
	int srch = args[6]->Int32Value();
	int angle = args[7]->Int32Value();

	gdImageCopyRotated(ptr, ptr2, dstx, dsty, srcx, srcy, srcw, srch, angle);
	return args.This();
}

JS_METHOD(_copymerge) {
	GD_PTR;
	GD_SECOND;
	
	int dstx = args[1]->Int32Value();
	int dsty = args[2]->Int32Value();
	int srcx = args[3]->Int32Value();
	int srcy = args[4]->Int32Value();
	int w = args[5]->Int32Value();
	int h = args[6]->Int32Value();
	int pct = args[7]->Int32Value();

	gdImageCopyMerge(ptr, ptr2, dstx, dsty, srcx, srcy, w, h, pct);
	return args.This();
}

JS_METHOD(_copymergegray) {
	GD_PTR;
	GD_SECOND;
	
	int dstx = args[1]->Int32Value();
	int dsty = args[2]->Int32Value();
	int srcx = args[3]->Int32Value();
	int srcy = args[4]->Int32Value();
	int w = args[5]->Int32Value();
	int h = args[6]->Int32Value();
	int pct = args[7]->Int32Value();

	gdImageCopyMergeGray(ptr, ptr2, dstx, dsty, srcx, srcy, w, h, pct);
	return args.This();
}

JS_METHOD(_copypalette) {
	GD_PTR;
	GD_SECOND;
	
	gdImagePaletteCopy(ptr, ptr2);
	return args.This();
}

JS_METHOD(_squaretocircle) {
	GD_PTR;
	
	int radius = args[0]->Int32Value();
	gdImageSquareToCircle(ptr, radius);
	return args.This();
}

JS_METHOD(_sharpen) {
	GD_PTR;
	
	int pct = args[0]->Int32Value();
	gdImageSharpen(ptr, pct);
	return args.This();
}

}
/**/ 

SHARED_INIT() {
	v8::HandleScope handle_scope;
	v8::Handle<v8::FunctionTemplate> ft = v8::FunctionTemplate::New(_image);
	ft->SetClassName(JS_STR("Image"));
	
	/**
	 * Constants (Image.*)
	 */
	ft->Set(JS_STR("TRUECOLOR"), JS_INT(GD_TRUECOLOR));
	ft->Set(JS_STR("PALETTE"), JS_INT(GD_PALETTE));
	ft->Set(JS_STR("MAXCOLORS"), JS_INT(gdMaxColors));
	ft->Set(JS_STR("JPEG"), JS_INT(GD_JPEG));
	ft->Set(JS_STR("PNG"), JS_INT(GD_PNG));
	ft->Set(JS_STR("GIF"), JS_INT(GD_GIF));
	ft->Set(JS_STR("ARC_ARC"), JS_INT(gdArc));
	ft->Set(JS_STR("ARC_PIE"), JS_INT(gdPie));
	ft->Set(JS_STR("ARC_CHORD"), JS_INT(gdChord));
	ft->Set(JS_STR("ARC_NOFILL"), JS_INT(gdNoFill));
	ft->Set(JS_STR("ARC_EDGED"), JS_INT(gdEdged));
	ft->Set(JS_STR("COLOR_ANTIALIASED"), JS_INT(gdAntiAliased));
	ft->Set(JS_STR("COLOR_BRUSHED"), JS_INT(gdBrushed));
	ft->Set(JS_STR("COLOR_STYLED"), JS_INT(gdStyled));
	ft->Set(JS_STR("COLOR_STYLEDBRUSHED"), JS_INT(gdStyledBrushed));
	ft->Set(JS_STR("COLOR_TILED"), JS_INT(gdTiled));
	ft->Set(JS_STR("COLOR_TRANSPARENT"), JS_INT(gdTransparent));
	
	/**
	 * Static methods (Image.*)
	 */
	ft->Set(JS_STR("trueColor"), v8::FunctionTemplate::New(_truecolor));
	ft->Set(JS_STR("trueColorAlpha"), v8::FunctionTemplate::New(_truecoloralpha));

	v8::Handle<v8::ObjectTemplate> it = ft->InstanceTemplate();
	it->SetInternalFieldCount(1);

	v8::Handle<v8::ObjectTemplate> pt = ft->PrototypeTemplate();
	
	/**
	 * Prototype methods (new Image().*)
	 */
	pt->Set(JS_STR("save"), v8::FunctionTemplate::New(_save));
	
	pt->Set(JS_STR("colorAllocate"), v8::FunctionTemplate::New(_colorallocate));
	pt->Set(JS_STR("colorAllocateAlpha"), v8::FunctionTemplate::New(_colorallocatealpha));
	pt->Set(JS_STR("colorClosest"), v8::FunctionTemplate::New(_colorclosest));
	pt->Set(JS_STR("colorClosestAlpha"), v8::FunctionTemplate::New(_colorclosestalpha));
	pt->Set(JS_STR("colorClosestHWB"), v8::FunctionTemplate::New(_colorclosesthwb));
	pt->Set(JS_STR("colorExact"), v8::FunctionTemplate::New(_colorexact));
	pt->Set(JS_STR("colorResolve"), v8::FunctionTemplate::New(_colorresolve));
	pt->Set(JS_STR("colorResolveAlpha"), v8::FunctionTemplate::New(_colorresolvealpha));
	pt->Set(JS_STR("colorsTotal"), v8::FunctionTemplate::New(_colorstotal));
	pt->Set(JS_STR("red"), v8::FunctionTemplate::New(_red));
	pt->Set(JS_STR("green"), v8::FunctionTemplate::New(_green));
	pt->Set(JS_STR("blue"), v8::FunctionTemplate::New(_blue));
	pt->Set(JS_STR("getInterlaced"), v8::FunctionTemplate::New(_getinterlaced));
	pt->Set(JS_STR("getTransparent"), v8::FunctionTemplate::New(_gettransparent));
	pt->Set(JS_STR("getPixel"), v8::FunctionTemplate::New(_getpixel));
	pt->Set(JS_STR("colorDeallocate"), v8::FunctionTemplate::New(_colordeallocate));
	pt->Set(JS_STR("colorTransparent"), v8::FunctionTemplate::New(_colortransparent));
	pt->Set(JS_STR("alpha"), v8::FunctionTemplate::New(_alpha));
	pt->Set(JS_STR("boundsSafe"), v8::FunctionTemplate::New(_boundssafe));
	pt->Set(JS_STR("sx"), v8::FunctionTemplate::New(_sx));
	pt->Set(JS_STR("sy"), v8::FunctionTemplate::New(_sy));
	pt->Set(JS_STR("trueColor"), v8::FunctionTemplate::New(_imagetruecolor));

	pt->Set(JS_STR("setPixel"), v8::FunctionTemplate::New(_setpixel));
	pt->Set(JS_STR("line"), v8::FunctionTemplate::New(_line));
	pt->Set(JS_STR("polygon"), v8::FunctionTemplate::New(_polygon));
	pt->Set(JS_STR("openPolygon"), v8::FunctionTemplate::New(_openpolygon));
	pt->Set(JS_STR("rectangle"), v8::FunctionTemplate::New(_rectangle));
	pt->Set(JS_STR("filledPolygon"), v8::FunctionTemplate::New(_filledpolygon));
	pt->Set(JS_STR("filledRectangle"), v8::FunctionTemplate::New(_filledrectangle));
	pt->Set(JS_STR("arc"), v8::FunctionTemplate::New(_arc));
	pt->Set(JS_STR("filledArc"), v8::FunctionTemplate::New(_filledarc));
	pt->Set(JS_STR("filledEllipse"), v8::FunctionTemplate::New(_filledellipse));
	pt->Set(JS_STR("fillToBorder"), v8::FunctionTemplate::New(_filltoborder));
	pt->Set(JS_STR("fill"), v8::FunctionTemplate::New(_fill));
	pt->Set(JS_STR("setAntialiased"), v8::FunctionTemplate::New(_setantialiased));
	pt->Set(JS_STR("setAntialiasedDontBlend"), v8::FunctionTemplate::New(_setantialiaseddontblend));
	pt->Set(JS_STR("setBrush"), v8::FunctionTemplate::New(_setbrush));
	pt->Set(JS_STR("setTile"), v8::FunctionTemplate::New(_settile));
	pt->Set(JS_STR("setStyle"), v8::FunctionTemplate::New(_setstyle));
	pt->Set(JS_STR("setThickness"), v8::FunctionTemplate::New(_setthickness));
	pt->Set(JS_STR("alphaBlending"), v8::FunctionTemplate::New(_alphablending));
	pt->Set(JS_STR("saveAlpha"), v8::FunctionTemplate::New(_savealpha));
	pt->Set(JS_STR("setClip"), v8::FunctionTemplate::New(_setclip));
	pt->Set(JS_STR("getClip"), v8::FunctionTemplate::New(_getclip));
	pt->Set(JS_STR("string"), v8::FunctionTemplate::New(_string));

	pt->Set(JS_STR("copy"), v8::FunctionTemplate::New(_copy));
	pt->Set(JS_STR("copyResized"), v8::FunctionTemplate::New(_copyresized));
	pt->Set(JS_STR("copyResampled"), v8::FunctionTemplate::New(_copyresampled));
	pt->Set(JS_STR("copyRotated"), v8::FunctionTemplate::New(_copyrotated));
	pt->Set(JS_STR("copyMerge"), v8::FunctionTemplate::New(_copymerge));
	pt->Set(JS_STR("copyMergeGray"), v8::FunctionTemplate::New(_copymergegray));
	pt->Set(JS_STR("copyPalette"), v8::FunctionTemplate::New(_copypalette));
	pt->Set(JS_STR("squareToCircle"), v8::FunctionTemplate::New(_squaretocircle));
	pt->Set(JS_STR("sharpen"), v8::FunctionTemplate::New(_sharpen));

	exports->Set(JS_STR("Image"), ft->GetFunction());		 
}

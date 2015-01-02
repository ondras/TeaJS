/*
 *	Server-side DOM module for TeaJS
 *
 *	Initial version: 2009-09-03, Ryan RAFFERTY
 */

#include <stdlib.h>
#include <map>
#include <stdio.h>
#include <string.h>
#include <sstream>

#include <v8.h>
#include <v8-debug.h>
#include "macros.h"
#include "gc.h"

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMMemoryManager.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/framework/MemBufFormatTarget.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/StdInInputSource.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/XMLBuffer.hpp>
#include <xercesc/framework/URLInputSource.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/BinFileInputStream.hpp>
#include <xercesc/util/BinMemInputStream.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

namespace xdom {

  // Establish lock to prevent violation of V8 threading
  // restrictions:
  // v8::Locker global_lock;

  bool initialized = 0;

  //using namespace std;
  using namespace xercesc_3_1;
  //XERCES_CPP_NAMESPACE_USE;

  #include "xdom.hpp"

  //	**********************************************		//
  //	**********************************************		//

  //	DOMException
  //
  JS_METHOD(_domexcpt) {
    v8::TryCatch tc;
    if (args.Length()<1)
      JS_RETURN_ERROR("[_domexcpt()] ERROR: Missing input parameter");
    ASSERT_CONSTRUCTOR;
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMException");
    DOMException * domerr = NULL;
    if (args[0]->IsExternal()) {
      domerr = RECAST(args[0],DOMException *);
    }
    else if (args[0]->IsObject()) {
      domerr = RECAST(args[0]->ToObject()->GetInternalField(0),DOMException *);
    }
    if (domerr==NULL) {
      JS_RETURN_ERROR("[_domexcpt()] ERROR: \"domerr\" is a null pointer");
    }
    else {
      SAVE_PTR(0, domerr);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_domexcpt_destructor) {
    /* v8::TryCatch tc; */
    //DOMERR;
    //XTRY( domerr->~DOMException(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  //	DOMLSException
  //
  JS_METHOD(_domlsexcpt) {
    v8::TryCatch tc;
    if (args.Length()<1)
      JS_RETURN_ERROR("[_domlsexcpt()] ERROR: Missing input parameter");
    ASSERT_CONSTRUCTOR;
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMLSException");
    DOMLSException * domlserr = NULL;
    if (args[0]->IsExternal()) {
      domlserr = RECAST(args[0],DOMLSException *);
    }
    else if (args[0]->IsObject()) {
      domlserr = RECAST(args[0]->ToObject()->GetInternalField(0),DOMLSException *);
    }
    if (domlserr==NULL) {
      JS_RETURN_ERROR("[_domlsexcpt()] ERROR: \"domlserr\" is a null pointer");
    }
    else {
      SAVE_PTR(0, domlserr);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_domlsexcpt_destructor) {
    /* v8::TryCatch tc; */
    //DOMLSERR;
    //XTRY( domlserr->~DOMLSException(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  //	DOMImplementationList
  //
  JS_METHOD(_domlist) {
    v8::TryCatch tc;
    if (args.Length()<1)
      JS_RETURN_ERROR("[_domlist()] ERROR: Missing input parameter");
    ASSERT_CONSTRUCTOR;
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMImplementationList");
    DOMImplementationList * domlist = NULL;
    if (args[0]->IsExternal()) {
      domlist = RECAST(args[0],DOMImplementationList *);
    }
    else if (args[0]->IsObject()) {
      domlist = RECAST(args[0]->ToObject()->GetInternalField(0),DOMImplementationList *);
    }
    if (domlist==NULL) {
      JS_RETURN_ERROR("[_domlist()] ERROR: \"domlist\" is a null pointer");
    }
    else {
      SAVE_PTR(0, domlist);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_domlistitem) {
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_domlistitem()] ERROR: Incorrect number of input parameters");
    }
    DOMLIST;
    DOMImplementation * dom = NULL;
    XMLSize_t index = (XMLSize_t)args[0]->ToInteger()->IntegerValue();
    XTRY( dom = domlist->item(index); );
    if (dom==NULL) {
      JS_RETURN_ERROR("[_domlistitem()] ERROR: \"dom\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)dom) };
      v8::Local<v8::Function> func(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdom)->GetFunction() );
      v8::Handle<v8::Object> ret( func->NewInstance(fargc, fargv) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_domlistgetlength) {
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_domlistgetlength()] ERROR: Incorrect number of input parameters");
    }
    DOMLIST;
    XMLSize_t length = 0;
    XTRY( length = domlist->getLength(); );
    { args.GetReturnValue().Set(JS_INT(length)); return; }
  }

  JS_METHOD(_domlist_destructor) {
    /* v8::TryCatch tc; */
    //DOMERR;
    //XTRY( domlist->~DOMImplementationList(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  //	DOMLocator
  //
  JS_METHOD(_domlocator) {
    v8::TryCatch tc;
    if (args.Length()<1)
      JS_RETURN_ERROR("[_domlocator()] ERROR: Missing input parameter");
    ASSERT_CONSTRUCTOR;
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMLocator");
    DOMLocator * domlocator = NULL;
    if (args[0]->IsExternal()) {
      domlocator = RECAST(args[0],DOMLocator *);
    }
    else if (args[0]->IsObject()) {
      domlocator = RECAST(args[0]->ToObject()->GetInternalField(0),DOMLocator *);
    }
    if (domlocator==NULL) {
      JS_RETURN_ERROR("[_domlocator()] ERROR: \"domlocator\" is a null pointer");
    }
    else {
      SAVE_PTR(0, domlocator);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_domlocatorgetrelatednode) {
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_domlocatorgetrelatednode()] ERROR: Incorrect number of input parameters");
    }
    DOMLOCATOR;
    DOMNode * node = NULL;
    XTRY( node = domlocator->getRelatedNode(); );
    if (node==NULL) {
      JS_RETURN_ERROR("[_domlocatorgetrelatednode()] ERROR: \"node\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)node) };
      v8::Local<v8::Function> func(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction() );
      v8::Handle<v8::Object> ret( func->NewInstance(fargc, fargv) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_domlocatorgetlinenumber) {
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_domlocatorgetlength()] ERROR: Incorrect number of input parameters");
    }
    DOMLOCATOR;
    XMLFileLoc loc = 0;
    XTRY( loc = domlocator->getLineNumber(); );
    { args.GetReturnValue().Set(JS_INT(loc)); return; }
  }

  JS_METHOD(_domlocatorgetcolumnnumber) {
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_domlocatorgetlength()] ERROR: Incorrect number of input parameters");
    }
    DOMLOCATOR;
    XMLFileLoc loc = 0;
    XTRY( loc = domlocator->getColumnNumber(); );
    { args.GetReturnValue().Set(JS_INT(loc)); return; }
  }

  JS_METHOD(_domlocatorgetbyteoffset) {
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_domlocatorgetlength()] ERROR: Incorrect number of input parameters");
    }
    DOMLOCATOR;
    XMLFilePos loc = 0;
    XTRY( loc = domlocator->getByteOffset(); );
    { args.GetReturnValue().Set(JS_INT(loc)); return; }
  }

  JS_METHOD(_domlocatorgetutf16offset) {
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_domlocatorgetlength()] ERROR: Incorrect number of input parameters");
    }
    DOMLOCATOR;
    XMLFilePos loc = 0;
    XTRY( loc = domlocator->getUtf16Offset(); );
    { args.GetReturnValue().Set(JS_INT(loc)); return; }
  }

  JS_METHOD(_domlocatorgeturi) {
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_domlocatorgeturi()] ERROR: Incorrect number of input parameters");
    }
    DOMLOCATOR;
    XS uri = NULL;
    XTRY( uri = (XS)domlocator->getURI(); );
    char * ret = NULL;
    if (uri==NULL) {
      ret = (char *)"";
    }
    else {
      ret = X(uri);
    }
    { args.GetReturnValue().Set(JS_STR(ret)); return; }
  }

  JS_METHOD(_domlocator_destructor) {
    /* v8::TryCatch tc; */
    //DOMERR;
    //XTRY( domlocator->~DOMLocator(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  //	DOMImplementationSource
  //
  JS_METHOD(_domsource) {
    v8::TryCatch tc;
    if (args.Length()!=0 && args.Length()!=1)
      JS_RETURN_ERROR("[_domsource()] ERROR: Incorrect number of input parameters");
    ASSERT_CONSTRUCTOR;
    if (xdom::initialized!=true) {
      xercesc_3_1::XMLPlatformUtils::Initialize();
      xdom::initialized=true;
    }
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMImplementationSource");
    DOMImplementationSource * domsource = NULL;
    if (args[0]->IsExternal()) {
      domsource = RECAST(args[0],DOMImplementationSource *);
    }
    else if (args[0]->IsObject()) {
      domsource = RECAST(args[0]->ToObject()->GetInternalField(0),DOMImplementationSource *);
    }
    if (domsource==NULL) {
      JS_RETURN_ERROR("[_domsource()] ERROR: \"domsource\" is a null pointer");
    }
    else {
      SAVE_PTR(0, domsource);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_domsourcegetdomimplementation) {
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_domsourcegetdomimplementation()] ERROR: Incorrect number of input parameters");
    }
    if (xdom::initialized!=true) {
      xercesc_3_1::XMLPlatformUtils::Initialize();
      xdom::initialized=true;
    }
    DOMSOURCE;
    DOMImplementation * dom = NULL;
    XTRY( dom = domsource->getDOMImplementation(ARGSTR(0)); );
    if (dom==NULL) {
      JS_RETURN_ERROR("[_domsourcegetdomimplementation()] ERROR: \"dom\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)dom) };
      v8::Local<v8::Function> func(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdom)->GetFunction() );
      v8::Handle<v8::Object> ret( func->NewInstance(fargc, fargv) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_domsourcegetdomimplementationlist) {
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_domsourcegetdomimplementationlist()] ERROR: Incorrect number of input parameters");
    }
    if (xdom::initialized!=true) {
      xercesc_3_1::XMLPlatformUtils::Initialize();
      xdom::initialized=true;
    }
    DOMSOURCE;
    DOMImplementationList * domlist = NULL;
    XTRY( domlist = domsource->getDOMImplementationList(ARGSTR(0)); );
    if (domlist==NULL) {
      JS_RETURN_ERROR("[_domsourcegetdomimplementationlist()] ERROR: \"domlist\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)domlist) };
      v8::Local<v8::Function> func(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomlist)->GetFunction() );
      v8::Handle<v8::Object> ret( func->NewInstance(fargc, fargv) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_domsource_destructor) {
    /* v8::TryCatch tc; */
    //DOMERR;
    //XTRY( domsource->~DOMImplementationSource(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  //	DOMImplementationRegistry
  //
  JS_METHOD(_domreg) {
    v8::TryCatch tc;
    if (args.Length()!=1 && args.Length()!=0)
      JS_RETURN_ERROR("[_domreg()] ERROR: Incorrect number of input parameters");
    ASSERT_CONSTRUCTOR;
    if (xdom::initialized!=true) {
      xercesc_3_1::XMLPlatformUtils::Initialize();
      xdom::initialized=true;
    }
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMImplementationRegistry");
    DOMImplementationRegistry * domreg = NULL;
    if (args.Length()==0) {
     // XTRY( domreg = new DOMImplementationRegistry(); );
    }
    else if (args[0]->IsExternal()) {
      domreg = RECAST(args[0],DOMImplementationRegistry *);
    }
    else if (args[0]->IsObject()) {
      domreg = RECAST(args[0]->ToObject()->GetInternalField(0),DOMImplementationRegistry *);
    }
    else if (args[0]->IsString()) {
     // XTRY( domreg = DOMImplementationRegistry::getDOMImplementationList(ARGSTR(0)); );
    }
    if (domreg==NULL) {
      JS_RETURN_ERROR("[_domreg()] ERROR: \"domreg\" is a null pointer");
    }
    else {
      SAVE_PTR(0, domreg);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_domreggetdomimplementation) {
    v8::TryCatch tc;
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_domreggetdomimplementation()] ERROR: Incorrect number of input parameters");
    }
    //DOMREG;
    if (xdom::initialized!=true) {
      xercesc_3_1::XMLPlatformUtils::Initialize();
      xdom::initialized=true;
    }
    DOMImplementation * dom = NULL;
    SS intxt( *v8::String::Utf8Value(args[0]->ToString()) );
    const XMLCh * arg0 = X(intxt.str().c_str());
    XTRY( dom = DOMImplementationRegistry::getDOMImplementation(arg0); );
    if (dom==NULL) {
      JS_RETURN_ERROR("[_domreggetdomimplementation()] ERROR: \"dom\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)dom) };
      v8::Local<v8::Function> func(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdom)->GetFunction() );
      v8::Handle<v8::Object> ret( func->NewInstance(fargc, fargv) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_domreggetdomimplementationlist) {
    v8::TryCatch tc;
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_domreggetdomimplementationlist()] ERROR: Incorrect number of input parameters");
    }
    //DOMREG;
    if (xdom::initialized!=true) {
      xercesc_3_1::XMLPlatformUtils::Initialize();
      xdom::initialized=true;
    }
    DOMImplementationList * domlist = NULL;
    SS intxt( *v8::String::Utf8Value(args[0]->ToString()) );
    const XMLCh * arg0 = X(intxt.str().c_str());
    XTRY( domlist = DOMImplementationRegistry::getDOMImplementationList(arg0); );
    if (domlist==NULL) {
      JS_RETURN_ERROR("[_domreggetdomimplementationlist()] ERROR: \"domlist\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)domlist) };
      v8::Local<v8::Function> func(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomlist)->GetFunction() );
      v8::Handle<v8::Object> ret( func->NewInstance(fargc, fargv) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_domregaddsource) {
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_domregaddsource()] ERROR: Incorrect number of input parameters");
    }
    if (xdom::initialized!=true) {
      xercesc_3_1::XMLPlatformUtils::Initialize();
      xdom::initialized=true;
    }
    DOMREG;
    DOMImplementationSource * src = NULL;
    if (args[0]->IsExternal()) {
      src = RECAST(args[0],DOMImplementationSource *);
    }
    else if (args[0]->IsObject()) {
      src = RECAST(args[0]->ToObject()->GetInternalField(0),DOMImplementationSource *);
    }
    if (src==NULL) {
      JS_RETURN_ERROR("[_domregaddsource()] ERROR: \"src\" is a null pointer");
    }
    else {
      XTRY( domreg->addSource(src); );
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_domreg_destructor) {
    /* v8::TryCatch tc; */
    //DOMERR;
    //XTRY( domreg->~DOMImplementationRegistry(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  //	XMemory
  //
  JS_METHOD(_xmemory) {
    v8::TryCatch tc;
    if (args.Length()<1)
      JS_RETURN_ERROR("[_xmemory()] ERROR: Missing input parameter");
    ASSERT_CONSTRUCTOR;
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~XMemory");
    XMemory * xmemory = NULL;
    if (args[0]->IsExternal()) {
      xmemory = RECAST(args[0],XMemory *);
    }
    else if (args[0]->IsObject()) {
      xmemory = RECAST(args[0]->ToObject()->GetInternalField(0),XMemory *);
    }
    if (xmemory==NULL) {
      JS_RETURN_ERROR("[_xmemory()] ERROR: \"xmemory\" is a null pointer");
    }
    else {
      SAVE_PTR(0, xmemory);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_xmemorynew) {
    v8::TryCatch tc;
    if (args.Length()!=1 && args.Length()!=2) {
      JS_RETURN_ERROR("[_xmemorynew()] ERROR: Incorrect number of input parameters");
    }
    XMEM;
    XMLSize_t size = (XMLSize_t)args[0]->ToInteger()->IntegerValue();
    void * buf = NULL;
    if (args.Length()==1) {
      XTRY( buf = xmem->XMemory::operator new(size); );
    }
    else if (args.Length()==2) {
      MemoryManager * mm = NULL;
      if (args[1]->IsExternal()) {
	mm = RECAST(args[1],MemoryManager *);
      }
      else if (args[1]->IsObject()) {
	mm = RECAST(args[1]->ToObject()->GetInternalField(0),MemoryManager *);
      }
      if (mm==NULL) {
	JS_RETURN_ERROR("[_xmemorynew()] ERROR: \"mm\" is a null pointer");
      }
      else {
	XTRY( buf = mm->allocate(size); );
      }
    }
    if (buf==NULL) {
      JS_RETURN_ERROR("[_xmemorynew()] ERROR: \"buf\" is a null pointer");
    }
    else {
      v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)buf), v8::Integer::New(JS_ISOLATE, size) };
      XMLSize_t fargc = 2;
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fbuffer)->GetFunction()->NewInstance(fargc,fargv) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_xmemorydelete) {
    v8::TryCatch tc;
    if (args.Length()!=1 && args.Length()!=2) {
      JS_RETURN_ERROR("[_xmemorydelete()] ERROR: Incorrect number of input parameters");
    }
    XMEM;
    void * p = NULL;
    if (args[0]->IsExternal()) {
      p = RECAST(args[0],void *);
    }
    else if (args[0]->IsObject()) {
      p = RECAST(args[0]->ToObject()->GetInternalField(0),void *);
    }
    if (args.Length()==1) {
      XTRY( xmem->XMemory::operator delete(p); );
    }
    else if (args.Length()==2) {
      MemoryManager * mm = NULL;
      if (args[1]->IsExternal()) {
	mm = RECAST(args[1],MemoryManager *);
      }
      else if (args[1]->IsObject()) {
	mm = RECAST(args[1]->ToObject()->GetInternalField(0),MemoryManager *);
      }
      if (mm==NULL) {
	JS_RETURN_ERROR("[_xmemorydelete()] ERROR: \"mm\" is a null pointer");
      }
      else {
	XTRY( xmem->XMemory::operator delete(p, mm); );
      }
    }
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_xmemory_destructor) {
    /* v8::TryCatch tc; */
    //XMEM;
    //XTRY( xmem->~XMemory(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }



  //	DOMLSInput
  //
  JS_METHOD(_domlsinput) {
    v8::TryCatch tc;
    if (args.Length()<1)
      JS_RETURN_ERROR("[_domlsinput()] ERROR: Missing input parameter");
    ASSERT_CONSTRUCTOR;
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMLSInput");
    DOMLSInput * domlsinput = NULL;
    if (args[0]->IsExternal()) {
      domlsinput = RECAST(args[0],DOMLSInput *);
    }
    else if (args[0]->IsObject()) {
      std::string domtype( *USTR(args[0]->ToObject()->Get(JS_STR("_domtype_"))->ToString()) );
      if (domtype=="DOMLSInput") {
	domlsinput = RECAST(args[0]->ToObject()->GetInternalField(0),DOMLSInput *);
      }
    }
    if (domlsinput==NULL) {
      JS_RETURN_ERROR("[_domlsinput()] ERROR: \"domlsinput\" is a null pointer");
    }
    else {
      SAVE_PTR(0,domlsinput);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_domlsinputgetstringdata) {
    DOMLSINPUT;
    char * ret = NULL;
    XS data = NULL;
    XLSTRY( data = (XS)domlsinput->getStringData(); );
    if (data==NULL) {
      ret = (char *)"";
    }
    else {
      ret = X(data);
    }
    { args.GetReturnValue().Set(JS_STR(ret)); return; }
  }

  JS_METHOD(_domlsinputgetbytestream) {
    DOMLSINPUT;
    InputSource * src = NULL;
    XLSTRY( src = domlsinput->getByteStream(); );
    if (src==NULL) {
      JS_RETURN_ERROR("[_domlsinputgetbytestream()] ERROR: \"src\" is a null pointer");
    }
    else {
      v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)src) };
      XMLSize_t fargc = 1;
      v8::Handle<v8::Value> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::finputsource)->GetFunction()->NewInstance(fargc, fargv) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_domlsinputgetencoding) {
    DOMLSINPUT;
    char * ret = NULL;
    XS data = NULL;
    XLSTRY( data = (XS)domlsinput->getEncoding(); );
    if (data==NULL) {
      ret = (char *)"";
    }
    else {
      ret = X(data);
    }
    { args.GetReturnValue().Set(JS_STR(ret)); return; }
  }

  JS_METHOD(_domlsinputgetpublicid) {
    DOMLSINPUT;
    char * ret = NULL;
    XS data = NULL;
    XLSTRY( data = (XS)domlsinput->getPublicId(); );
    if (data==NULL) {
      ret = (char *)"";
    }
    else {
      ret = X(data);
    }
    { args.GetReturnValue().Set(JS_STR(ret)); return; }
  }

  JS_METHOD(_domlsinputgetsystemid) {
    DOMLSINPUT;
    char * ret = NULL;
    XS data = NULL;
    XLSTRY( data = (XS)domlsinput->getSystemId(); );
    if (data==NULL) {
      ret = (char *)"";
    }
    else {
      ret = X(data);
    }
    { args.GetReturnValue().Set(JS_STR(ret)); return; }
  }

  JS_METHOD(_domlsinputgetbaseuri) {
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_domlsinputgetbaseuri()] ERROR: incorrect number of input parameters");
    }
    DOMLSINPUT;
    char * ret = NULL;
    XS data = NULL;
    XLSTRY( data = (XS)domlsinput->getBaseURI(); );
    if (data==NULL) {
      ret = (char *)"";
    }
    else {
      ret = X(data);
    }
    { args.GetReturnValue().Set(JS_STR(ret)); return; }
  }

  JS_METHOD(_domlsinputsetstringdata) {
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_domlsinputsetstringdata()] ERROR: incorrect number of input parameters");
    }
    DOMLSINPUT;
    XLSTRY( domlsinput->setStringData(ARGSTR(0)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_domlsinputsetbytestream) {
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_domlsinputsetbytestream()] ERROR: incorrect number of input parameters");
    }
    DOMLSINPUT;
    InputSource * src = NULL;
    if (args[0]->IsExternal()) {
      src = RECAST(args[0],InputSource *);
    }
    else if (args[0]->IsObject()) {
      src = RECAST(args[0]->ToObject()->GetInternalField(0),InputSource *);
    }
    if (src==NULL) {
      JS_RETURN_ERROR("[_domlsinputsetbytestream()] ERROR: \"src\" is a null pointer");
    }
    else {
      XLSTRY( domlsinput->setByteStream(src); );
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_domlsinputsetencoding) {
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_domlsinputsetstringdata()] ERROR: incorrect number of input parameters");
    }
    DOMLSINPUT;
    XLSTRY( domlsinput->setEncoding(ARGSTR(0)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_domlsinputsetpublicid) {
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_domlsinputsetpublicid()] ERROR: incorrect number of input parameters");
    }
    DOMLSINPUT;
    XLSTRY( domlsinput->setPublicId(ARGSTR(0)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_domlsinputsetsystemid) {
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_domlsinputsetsystemid()] ERROR: incorrect number of input parameters");
    }
    DOMLSINPUT;
    XLSTRY( domlsinput->setSystemId(ARGSTR(0)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_domlsinputsetbaseuri) {
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_domlsinputsetbaseuri()] ERROR: incorrect number of input parameters");
    }
    DOMLSINPUT;
    XLSTRY( domlsinput->setBaseURI(ARGSTR(0)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_domlsinputsetissuefatalerrorifnotfound) {
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_domlsinputsetissuefatalerrorifnotfound()] ERROR: incorrect number of input parameters");
    }
    DOMLSINPUT;
    XLSTRY( domlsinput->setIssueFatalErrorIfNotFound(args[0]->ToBoolean()->BooleanValue()); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_domlsinputgetissuefatalerrorifnotfound) {
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_domlsinputgetissuefatalerrorifnotfound()] ERROR: incorrect number of input parameters");
    }
    DOMLSINPUT;
    bool ret = false;
    XLSTRY( ret = domlsinput->getIssueFatalErrorIfNotFound(); );
    { args.GetReturnValue().Set(JS_BOOL(ret)); return; }
  }

  JS_METHOD(_domlsinput_destructor) {
    /* v8::TryCatch tc; */
    //DOMLSINPUT;
    //XLSTRY( domlsinput->~DOMLSInput(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  //	DOMLSOutput
  //
  JS_METHOD(_domlsoutput) {
    v8::TryCatch tc;
    if (args.Length()<1)
      JS_RETURN_ERROR("[_domlsoutput()] ERROR: Missing output parameter");
    ASSERT_CONSTRUCTOR;
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMLSOutput");
    DOMLSOutput * domlsoutput = NULL;
    if (args[0]->IsExternal()) {
      domlsoutput = RECAST(args[0],DOMLSOutput *);
    }
    else if (args[0]->IsObject()) {
      domlsoutput = RECAST(args[0]->ToObject()->GetInternalField(0),DOMLSOutput *);
    }
    if (domlsoutput==NULL) {
      JS_RETURN_ERROR("[_domlsoutput()] ERROR: \"domlsoutput\" is a null pointer");
    }
    else {
      SAVE_PTR(0, domlsoutput);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_domlsoutputgetbytestream) {
    DOMLSOUTPUT;
    XMLFormatTarget * dst = NULL;
    XLSTRY( dst = domlsoutput->getByteStream(); );
    if (dst==NULL) {
      JS_RETURN_ERROR("[_domlsoutputgetbytestream()] ERROR: \"dst\" is a null pointer");
    }
    else {
      v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)dst) };
      XMLSize_t fargc = 1;
      v8::Handle<v8::Value> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fformattarget)->GetFunction()->NewInstance(fargc, fargv) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_domlsoutputgetencoding) {
    DOMLSOUTPUT;
    char * ret = NULL;
    XS data = NULL;
    XLSTRY( data = (XS)domlsoutput->getEncoding(); );
    if (data==NULL) {
      ret = (char *)"";
    }
    else {
      ret = X(data);
    }
    { args.GetReturnValue().Set(JS_STR(ret)); return; }
  }

  JS_METHOD(_domlsoutputgetsystemid) {
    DOMLSOUTPUT;
    char * ret = NULL;
    XS data = NULL;
    XLSTRY( data = (XS)domlsoutput->getSystemId(); );
    if (data==NULL) {
      ret = (char *)"";
    }
    else {
      ret = X(data);
    }
    { args.GetReturnValue().Set(JS_STR(ret)); return; }
  }

  JS_METHOD(_domlsoutputsetencoding) {
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_domlsoutputsetstringdata()] ERROR: incorrect number of output parameters");
    }
    DOMLSOUTPUT;
    XLSTRY( domlsoutput->setEncoding(ARGSTR(0)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_domlsoutputsetsystemid) {
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_domlsoutputsetsystemid()] ERROR: incorrect number of output parameters");
    }
    DOMLSOUTPUT;
    XLSTRY( domlsoutput->setSystemId(ARGSTR(0)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_domlsoutputsetbytestream) {
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_domlsoutputsetbytestream()] ERROR: incorrect number of output parameters");
    }
    DOMLSOUTPUT;
    XMLFormatTarget * target = NULL;
    if (args[0]->IsExternal()) {
      target = RECAST(args[0],XMLFormatTarget *);
    }
    else if (args[0]->IsObject()) {
      target = RECAST(args[0]->ToObject()->GetInternalField(0),XMLFormatTarget *);
    }
    if (target==NULL) {
      JS_RETURN_ERROR("[_domlsoutputsetbytestream()] ERROR: \"target\" is a null pointer");
    }
    else {
      XLSTRY( domlsoutput->setByteStream(target); );
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_domlsoutput_destructor) {
    /* v8::TryCatch tc; */
    //DOMLSOUTPUT;
    //XLSTRY( domlsoutput->~DOMLSOutput(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  //	BinInputStream
  //
  JS_METHOD(_bininput) {
    /* v8::TryCatch tc; */
    if (args.Length()<1)
      JS_RETURN_ERROR("[_bininput()] ERROR: Missing input parameter");
    ASSERT_CONSTRUCTOR;
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~BinInputStream");
    BinInputStream * bininputstream = NULL;
    if (args[0]->IsExternal()) {
      bininputstream = RECAST(args[0],BinInputStream *);
    }
    else if (args[0]->IsObject()) {
      bininputstream = RECAST(args[0]->ToObject()->GetInternalField(0),BinInputStream *);
    }
    if (bininputstream==NULL) {
      JS_RETURN_ERROR("[_bininput()] ERROR: \"bininputstream\" is a null pointer");
    }
    else {
      SAVE_PTR(0, bininputstream);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_bininputcurpos) {
    //BININPUT;
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_bininputreadbytes) {
    //BININPUT;
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_bininputgetcontenttype) {
    //BININPUT;
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_bininput_destructor) {
    /* v8::TryCatch tc; */
    //FILEINPUT;
    //XTRY( xpath->~BinInputStream (); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  //	BinFileInputStream
  //
  JS_METHOD(_binfileinput) {
    /* v8::TryCatch tc; */
    if (args.Length()<1)
      JS_RETURN_ERROR("[_binfileinput()] ERROR: Missing input parameter");
    ASSERT_CONSTRUCTOR;
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~BinFileInputStream");
    BinFileInputStream * binfileinput = NULL;
    if (args[0]->IsExternal()) {
      binfileinput = RECAST(args[0],BinFileInputStream *);
    }
    else if (args[0]->IsObject()) {
      binfileinput = RECAST(args[0]->ToObject()->GetInternalField(0),BinFileInputStream *);
    }
    if (binfileinput==NULL) {
      JS_RETURN_ERROR("[_binfileinput()] ERROR: \"binfileinput\" is a null pointer");
    }
    else {
      SAVE_PTR(0, binfileinput);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_binfileinputgetisopen) {
    //BINFILEINPUT;
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_binfileinputgetsize) {
    //BINFILEINPUT;
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_binfileinputreset) {
    //BINFILEINPUT;
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_binfileinput_destructor) {
    /* v8::TryCatch tc; */
    //FILEINPUT;
    //XTRY( xpath->~BinFileInputStream (); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  //	BinMemInputStream
  //
  JS_METHOD(_binmeminputstream) {
    /* v8::TryCatch tc; */
    if (args.Length()<1)
      JS_RETURN_ERROR("[_binmeminputstream()] ERROR: Missing input parameter");
    ASSERT_CONSTRUCTOR;
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~BinMemInputStream");
    BinMemInputStream * binmeminputstream = NULL;
    if (args[0]->IsExternal()) {
      binmeminputstream = RECAST(args[0],BinMemInputStream *);
    }
    else if (args[0]->IsObject()) {
      binmeminputstream = RECAST(args[0]->ToObject()->GetInternalField(0),BinMemInputStream *);
    }
    if (binmeminputstream==NULL) {
      JS_RETURN_ERROR("[_binmeminputstream()] ERROR: \"binmeminputstream\" is a null pointer");
    }
    else {
      SAVE_PTR(0, binmeminputstream);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_binmeminputstreamgetsize) {
    //BINMEMINPUT;
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_binmeminputstreamreset) {
    //BINMEMINPUT;
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_binmeminputstream_destructor) {
    /* v8::TryCatch tc; */
    //FILEINPUT;
    //XTRY( xpath->~BinMemInputStream (); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  //	Buffer
  //
  JS_METHOD(_buffer) {
    /* v8::TryCatch tc; */
    if (args.Length()<1)
      JS_RETURN_ERROR("[_buffer()] ERROR: Missing input parameter");
    ASSERT_CONSTRUCTOR;
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~Buffer");
    void * buf = NULL;
    XMLSize_t size = 0;
    if (args[0]->IsExternal()) {
      buf = RECAST(args[0],void *);
      size = (XMLSize_t)args[1]->ToInteger()->IntegerValue();
    }
    else if (args[0]->IsObject()) {
      buf = RECAST(args[0]->ToObject()->GetInternalField(0),void *);
      size = (XMLSize_t)args[0]->ToObject()->GetInternalField(1)->ToInteger()->IntegerValue();
    }
    if (buf==NULL) {
      JS_RETURN_ERROR("[_buffer()] ERROR: \"buf\" is a null pointer");
    }
    else {
      SAVE_PTR(0, buf);
      SAVE_PTR(1, (void *)size);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_buffer_destructor) {
    /* v8::TryCatch tc; */
    //FILEINPUT;
    //XTRY( xpath->~BinMemInputStream (); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  //	DOMMemoryManager
  //
  JS_METHOD(_dommemorymanager) {
    v8::TryCatch tc;
    if (args.Length()<1)
      JS_RETURN_ERROR("[_dommemorymanager()] ERROR: Missing input parameter");
    ASSERT_CONSTRUCTOR;
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMMemoryManager");
    DOMMemoryManager * dommm = NULL;
    if (args[0]->IsExternal()) {
      dommm = RECAST(args[0],DOMMemoryManager *);
    }
    else if (args[0]->IsObject()) {
      dommm = RECAST(args[0]->ToObject()->GetInternalField(0),DOMMemoryManager *);
    }
    if (dommm==NULL) {
      JS_RETURN_ERROR("[_dommemorymanager()] ERROR: \"dommm\" is a null pointer");
    }
    else {
      SAVE_PTR(0, dommm);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_dommemorymanagerallocate) {
    v8::TryCatch tc;
    if (args.Length()!=1 && args.Length()!=2) {
      JS_RETURN_ERROR("[_dommemorymanagerallocate()] ERROR: Incorrect number of input parameters");
    }
    DOMMEMMGR;
    XMLSize_t size = (XMLSize_t)args[0]->ToInteger()->IntegerValue();
    void * buf = NULL;
    if (args.Length()==1) {
      XTRY( buf = (void *)dommm->allocate((XMLSize_t)size); );
    }
    else {
      DOMMemoryManager::NodeObjectType atype = (DOMMemoryManager::NodeObjectType)args[1]->ToInteger()->IntegerValue();
      XTRY( buf = (void *)dommm->allocate((XMLSize_t)size,(DOMMemoryManager::NodeObjectType)atype); );
    }
    v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)buf), v8::Integer::New(JS_ISOLATE, size) };
    XMLSize_t fargc = 2;
    v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fbuffer)->GetFunction()->NewInstance(fargc,fargv) );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_dommemorymanagergetmemoryallocationblocksize) {
    v8::TryCatch tc;
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_dommemorymanagergetmemoryallocationblocksize()] ERROR: Incorrect number of input parameters");
    }
    DOMMEMMGR;
    XMLSize_t size = 0;
    XTRY( size = dommm->getMemoryAllocationBlockSize(); );
    { args.GetReturnValue().Set(JS_INT(size)); return; }
  }

  JS_METHOD(_dommemorymanagersetmemoryallocationblocksize) {
    v8::TryCatch tc;
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_dommemorymanagersetmemoryallocationblocksize()] ERROR: Incorrect number of input parameters");
    }
    DOMMEMMGR;
    XMLSize_t size = (XMLSize_t)args[0]->ToInteger()->IntegerValue();
    XTRY( dommm->setMemoryAllocationBlockSize(size); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_dommemorymanagerclonestring) {
    v8::TryCatch tc;
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_dommemorymanagerclonestring()] ERROR: Incorrect number of input parameters");
    }
    DOMMEMMGR;
    XS data = NULL;
    char * ret = NULL;
    XTRY( data = dommm->cloneString(ARGSTR(0)); );
    if (data==NULL) {
      ret = (char *)"";
    }
    else {
      ret = X(data);
    }
    { args.GetReturnValue().Set(JS_STR(ret)); return; }
  }

  JS_METHOD(_dommemorymanager_destructor) {
    /* v8::TryCatch tc; */
    DOMMEMMGR;
    XTRY( dommm->~DOMMemoryManager(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  //	MemoryManager
  //
  JS_METHOD(_memorymanager) {
    v8::TryCatch tc;
    if (args.Length()<1)
      JS_RETURN_ERROR("[_memorymanager()] ERROR: Missing input parameter");
    ASSERT_CONSTRUCTOR;
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~MemoryManager");
    MemoryManager * mm = NULL;
    if (args[0]->IsExternal()) {
      mm = RECAST(args[0],MemoryManager *);
    }
    else if (args[0]->IsObject()) {
      mm = RECAST(args[0]->ToObject()->GetInternalField(0),MemoryManager *);
    }
    if (mm==NULL) {
      JS_RETURN_ERROR("[_memorymanager()] ERROR: \"mm\" is a null pointer");
    }
    else {
      SAVE_PTR(0, mm);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_memorymanagergetexceptionmemorymanager) {
    v8::TryCatch tc;
    MM;
    MemoryManager * exmm = NULL;
    XTRY( exmm = mm->getExceptionMemoryManager(); );
    if (exmm==NULL) {
      JS_RETURN_ERROR("[_memorymanagergetexceptionmemorymanager()] ERROR: \"exmm\" is a null pointer");
    }
    else {
      v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)exmm) };
      XMLSize_t fargc = 1;
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fmemorymanager)->GetFunction()->NewInstance(fargc,fargv) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_memorymanagerallocate) {
    v8::TryCatch tc;
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_memorymanagerallocate()] ERROR: Incorrect number of input parameters");
    }
    MM;
    XMLSize_t size = (XMLSize_t)args[0]->ToInteger()->IntegerValue();
    void * buf = NULL;
    XTRY( buf = mm->allocate(size); );
    v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)buf), v8::Integer::New(JS_ISOLATE, size) };
    XMLSize_t fargc = 2;
    v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fbuffer)->GetFunction()->NewInstance(fargc,fargv) );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_memorymanagerdeallocate) {
    v8::TryCatch tc;
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_memorymanagerallocate()] ERROR: Incorrect number of input parameters");
    }
    MM;
    void * p = NULL;
    if (args[0]->IsExternal()) {
      p = RECAST(args[0],void *);
    }
    else if (args[0]->IsObject()) {
      p = RECAST(args[0]->ToObject()->GetInternalField(0),void *);
    }
    XTRY( mm->deallocate(p); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_memorymanager_destructor) {
    v8::TryCatch tc;
    //FILEINPUT;
    //XTRY( xpath->~BinMemInputStream (); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  /**
   *	InputSource
   **/
  JS_METHOD(_inputsource) {
    v8::TryCatch tc;
    if (args.Length()<1)
      JS_RETURN_ERROR("[_inputsource()] ERROR: Missing input parameter");
    ASSERT_CONSTRUCTOR;
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~InputSource");
    InputSource * inputsource = NULL;
    if (args[0]->IsExternal()) {
      inputsource = RECAST(args[0],InputSource *);
    }
    else if (args[0]->IsObject()) {
      inputsource = RECAST(args[0]->ToObject()->GetInternalField(0),InputSource *);
    }
    if (inputsource==NULL) {
      JS_RETURN_ERROR("[_inputsource()] ERROR: \"inputsource\" is a null pointer");
    }
    else {
      SAVE_PTR(0, inputsource);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_inputsourcemakestream) {
    v8::TryCatch tc;
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_inputsourcemakestream()] ERROR: Too many input parameters");
    }
    INPUTSOURCE;
    v8::Handle<v8::Object> ret;
    BinInputStream * bin = NULL;
    XTRY( bin = inputsource->makeStream(); );
    if (bin==NULL) {
      JS_RETURN_ERROR("[_inputsourcemakestream()] ERROR: \"bin\" is a null pointer");
    }
    else {
      v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)bin) };
      XMLSize_t fargc = 1;
      ret = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fbininput)->GetFunction()->NewInstance(fargc, fargv);
    }
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_inputsourcegetencoding) {
    v8::TryCatch tc;
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_inputsourcegetencoding()] ERROR: Too many input parameters");
    }
    INPUTSOURCE;
    char * ret = NULL;
    XS data = NULL;
    XTRY( data = (XS)inputsource->getEncoding(); );
    if (data==NULL) {
      ret = (char *)"";
    }
    else {
      ret = X(data);
    }
    { args.GetReturnValue().Set(JS_STR(ret)); return; }
  }

  JS_METHOD(_inputsourcegetpublicid) {
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_inputsourcegetpublicid()] ERROR: Too many input parameters");
    }
    INPUTSOURCE;
    char * ret = NULL;
    XS data = NULL;
    XTRY( data = (XS)inputsource->getPublicId(); );
    if (data==NULL) {
      ret = (char *)"";
    }
    else {
      ret = X(data);
    }
    { args.GetReturnValue().Set(JS_STR(ret)); return; }
  }

  JS_METHOD(_inputsourcegetsystemid) {
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_inputsourcegetsystemid()] ERROR: Too many input parameters");
    }
    INPUTSOURCE;
    char * ret = NULL;
    XS data = NULL;
    XTRY( data = (XS)inputsource->getSystemId(); );
    if (data==NULL) {
      ret = (char *)"";
    }
    else {
      ret = X(data);
    }
    { args.GetReturnValue().Set(JS_STR(ret)); return; }
  }

  JS_METHOD(_inputsourcegetissuefatalerrorifnotfound) {
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_inputsourcegetissuefatalerrorifnotfound()] ERROR: Too many input parameters");
    }
    INPUTSOURCE;
    bool ret = false;
    XTRY( ret = inputsource->getIssueFatalErrorIfNotFound(); );
    { args.GetReturnValue().Set(JS_BOOL(ret)); return; }
  }

  JS_METHOD(_inputsourcegetmemorymanager) {
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_inputsourcegetmemorymanager()] ERROR: Too many input parameters");
    }
    INPUTSOURCE;
    v8::Handle<v8::Object> ret;
    MemoryManager * mm = NULL;
    XTRY( mm = inputsource->getMemoryManager(); );
    if (mm==NULL) {
      JS_RETURN_ERROR("[_inputsourcegetmemorymanager()] ERROR: \"mm\" is a null pointer");
    }
    else {
      v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)mm) };
      XMLSize_t fargc = 1;
      ret = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fmemorymanager)->GetFunction()->NewInstance(fargc, fargv);
    }
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_inputsourcesetencoding) {
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_inputsourcesetencoding()] ERROR: Incorrect number of input parameters");
    }
    INPUTSOURCE;
    XTRY( inputsource->setEncoding(ARGSTR(0)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_inputsourcesetpublicid) {
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_inputsourcesetpublicid()] ERROR: Incorrect number of input parameters");
    }
    INPUTSOURCE;
    XTRY( inputsource->setPublicId(ARGSTR(0)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_inputsourcesetsystemid) {
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_inputsourcesetsystemid()] ERROR: Incorrect number of input parameters");
    }
    INPUTSOURCE;
    XTRY( inputsource->setSystemId(ARGSTR(0)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_inputsourcesetissuefatalerrorifnotfound) {
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_inputsourcesetissuefatalerrorifnotfound()] ERROR: Incorrect number of input parameters");
    }
    INPUTSOURCE;
    XTRY( inputsource->setIssueFatalErrorIfNotFound(args[0]->ToBoolean()->BooleanValue()); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_inputsource_destructor) {
    /* v8::TryCatch tc; */
    //INPUTSOURCE;
    //XTRY( xpath->~InputSource (); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  //	LocalFileInputSource
  //
  JS_METHOD(_fileinput) {
    /* v8::TryCatch tc; */
    if (args.Length()<1) {
      JS_RETURN_ERROR("[_fileinput()] ERROR: Missing input parameter");
    }
    ASSERT_CONSTRUCTOR;
    if (xdom::initialized!=true) {
      xercesc_3_1::XMLPlatformUtils::Initialize();
      xdom::initialized=true;
    }
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add( args.This(), "~LocalFileInputSource");
    LocalFileInputSource * fileinput = NULL;
    if (args[0]->IsExternal()) {
      fileinput = RECAST(args[0],LocalFileInputSource *);
    }
    else if (args[0]->IsObject()) {
      fileinput = RECAST(args[0]->ToObject()->GetInternalField(0),LocalFileInputSource *);
    }
    if (fileinput==NULL) {
      JS_RETURN_ERROR("[_fileinput()] ERROR: \"fileinput\" is a null pointer");
    }
    else {
      SAVE_PTR(0, fileinput);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_fileinput_destructor) {
    /* v8::TryCatch tc; */
    //FILEINPUT;
    //XTRY( xpath->~LocalFileInputSource (); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  //	MemBufInputSource
  //
  JS_METHOD(_membufinput) {
    /* v8::TryCatch tc; */
    if (args.Length()<1) {
      JS_RETURN_ERROR("[_membuf()] ERROR: Missing input parameter");
    }
    bool * adopt = new bool;
    *adopt = false;
    ASSERT_CONSTRUCTOR;
    if (xdom::initialized!=true) {
      xercesc_3_1::XMLPlatformUtils::Initialize();
      xdom::initialized=true;
    }
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add( args.This(), "~MemBufInputSource");
    MemBufInputSource * membuf = NULL;
    if (args[0]->IsExternal()) {
      membuf = RECAST(args[0],MemBufInputSource *);
    }
    else if (args[0]->IsObject()) {
      membuf = RECAST(args[0]->ToObject()->GetInternalField(0),MemBufInputSource *);
    }
    else if (args[0]->IsString()) {
      SS tmp( *v8::String::Utf8Value(args[0]->ToString()) );
      char * src = strdup(tmp.str().c_str());
      size_t isize = strlen(src);
      XMLSize_t * len = reinterpret_cast<XMLSize_t *>(&isize);
      membuf = new MemBufInputSource(reinterpret_cast<const XMLByte *>(src),*len,"test",false);
      *adopt = true;
    }
    if (membuf==NULL) {
      JS_RETURN_ERROR("[_membuf()] ERROR: \"membuf\" is a null pointer");
    }
    else {
      SAVE_PTR(0, membuf);
      SAVE_PTR(1, adopt);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_membufinputsetcopybuftostream) {
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_membufinputsetcopybuftostream()] ERROR: Incorrect number of input parameters");
    }
    MEMBUFINPUT;
    const bool newState = args[0]->ToBoolean()->BooleanValue();
    XTRY( membuf->setCopyBufToStream(newState); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_membufinputresetmembufinputsource) {
    if (args.Length()!=1 && args.Length()!=2) {
      JS_RETURN_ERROR("[_membufinputresetmembufinputsource()] ERROR: Incorrect number of input parameters");
    }
    MEMBUFINPUT;
    const XMLByte *const srcDocBytes = reinterpret_cast<const XMLByte *const>(*v8::String::Utf8Value(args[0]->ToString()));
    const XMLSize_t byteCount = strlen((const char *)srcDocBytes);
    XTRY( membuf->resetMemBufInputSource(srcDocBytes,byteCount); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_membufinput_destructor) {
    /* v8::TryCatch tc; */
    MEMBUFINPUT;
    bool * adopt = LOAD_PTR(1,bool *);
    if (*adopt==true) {
      delete membuf;
    }
    { args.GetReturnValue().Set(args.This()); return; };
  }


  //	StdInInputSource
  //
  JS_METHOD(_stdin) {
    /* v8::TryCatch tc; */
    if (args.Length()<1) {
      JS_RETURN_ERROR("[_stdin()] ERROR: Missing input parameter");
    }
    ASSERT_CONSTRUCTOR;
    if (xdom::initialized!=true) {
      xercesc_3_1::XMLPlatformUtils::Initialize();
      xdom::initialized=true;
    }
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add( args.This(), "~StdInInputSource");
    StdInInputSource * my_stdin = NULL;
    if (args[0]->IsExternal()) {
      my_stdin = RECAST(args[0],StdInInputSource *);
    }
    else if (args[0]->IsObject()) {
      my_stdin = RECAST(args[0]->ToObject()->GetInternalField(0),StdInInputSource *);
    }
    if (my_stdin==NULL) {
      JS_RETURN_ERROR("[_stdin()] ERROR: \"my_stdin\" is a null pointer");
    }
    else {
      SAVE_PTR(0, my_stdin);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_stdin_destructor) {
    /* v8::TryCatch tc; */
    STDIN;
    XTRY( my_stdin->~StdInInputSource(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  //	XMLURL
  //
  JS_METHOD(_xmlurl) {
    /* v8::TryCatch tc; */
    if (args.Length()<1) {
      JS_RETURN_ERROR("[_xmlurl()] ERROR: Missing input parameter");
    }
    ASSERT_CONSTRUCTOR;
    if (xdom::initialized!=true) {
      xercesc_3_1::XMLPlatformUtils::Initialize();
      xdom::initialized=true;
    }
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add( args.This(), "~XMLURL");
    XMLURL * xmlurl = NULL;
    if (args[0]->IsExternal()) {
      xmlurl = RECAST(args[0],XMLURL *);
    }
    else if (args[0]->IsObject()) {
      xmlurl = RECAST(args[0]->ToObject()->GetInternalField(0),XMLURL *);
    }
    else if (args[0]->IsString()) {
      XTRY( xmlurl = new XMLURL(ARGSTR(0)); );
    }
    if (xmlurl==NULL) {
      JS_RETURN_ERROR("[_xmlurl()] ERROR: \"xmlurl\" is a null pointer");
    }
    else {
      SAVE_PTR(0, xmlurl);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_xmlurlgetfragment) {
    LXMLURL;
    XS txt = NULL;
    XTRY( txt = (XMLCh *)xmlurl->getFragment(); );
    if (txt==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(txt);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_xmlurlgethost) {
    LXMLURL;
    XS txt = NULL;
    XTRY( txt = (XMLCh *)xmlurl->getHost(); );
    if (txt==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(txt);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_xmlurlgetpassword) {
    LXMLURL;
    XS txt = NULL;
    XTRY( txt = (XMLCh *)xmlurl->getPassword(); );
    if (txt==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(txt);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_xmlurlgetpath) {
    LXMLURL;
    XS txt = NULL;
    XTRY( txt = (XMLCh *)xmlurl->getPath(); );
    if (txt==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(txt);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_xmlurlgetportnum) {
    LXMLURL;
    unsigned int ret = 0;
    XTRY( ret = xmlurl->getPortNum(); );
    { args.GetReturnValue().Set(JS_INT(ret)); return; }
  }

  JS_METHOD(_xmlurlgetprotocol) {
    LXMLURL;
    unsigned int ret = 0;
    XTRY( ret = (unsigned int)xmlurl->getPortNum(); );
    { args.GetReturnValue().Set(JS_INT(ret)); return; }
  }

  JS_METHOD(_xmlurlgetprotocolname) {
    LXMLURL;
    XS txt = NULL;
    XTRY( txt = (XMLCh *)xmlurl->getProtocolName(); );
    if (txt==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(txt);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_xmlurlgetquery) {
    LXMLURL;
    XS txt = NULL;
    XTRY( txt = (XMLCh *)xmlurl->getQuery(); );
    if (txt==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(txt);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_xmlurlgeturltext) {
    LXMLURL;
    XS txt = NULL;
    XTRY( txt = (XMLCh *)xmlurl->getURLText(); );
    if (txt==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(txt);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_xmlurlgetuser) {
    LXMLURL;
    XS txt = NULL;
    XTRY( txt = (XMLCh *)xmlurl->getUser(); );
    if (txt==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(txt);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_xmlurlgetmemorymanager) {
    //LXMLURL;
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_xmlurlseturl) {
    LXMLURL;
    XTRY( xmlurl->setURL(ARGSTR(0)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_xmlurlisrelative) {
    LXMLURL;
    bool ret = false;
    XTRY( ret = xmlurl->isRelative(); );
    { args.GetReturnValue().Set(JS_BOOL(ret)); return; }
  }

  JS_METHOD(_xmlurlhasinvalidchar) {
    LXMLURL;
    bool ret = false;
    XTRY( ret = xmlurl->hasInvalidChar(); );
    { args.GetReturnValue().Set(JS_BOOL(ret)); return; }
  }

  JS_METHOD(_xmlurlmakenewstream) {
    LXMLURL;
    BinInputStream * bin = NULL;
    XTRY( bin = xmlurl->makeNewStream(); );
    if (bin==NULL) {
      args.GetReturnValue().Set(JS_STR("[_xmlurlmakenewstream()] ERROR: \"bin\" is a null pointer"));
      return;
    }
    else {
      XMLSize_t fargc = 1;
      v8::Handle<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)bin) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fbininput)->GetFunction()->NewInstance(fargc, fargv) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_xmlurlmakerelativeto) {
    LXMLURL;
    XMLURL * base = NULL;
    if (args[0]->IsExternal()) {
      base = RECAST(args[0],XMLURL *);
    }
    else if (args[0]->IsString()) {
      XTRY( base = new XMLURL(ARGSTR(0)); );
    }
    else if (args[0]->IsObject()) {
      base = RECAST(args[0]->ToObject()->GetInternalField(0),XMLURL *);
    }
    if (base==NULL) {
      args.GetReturnValue().Set(JS_STR("[_xmlurlmakerelativeto()] ERROR: \"base\" is a null pointer"));
      return;
    }
    else {
      XTRY( xmlurl->makeRelativeTo((const XMLURL)*base); );
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_xmlurllookupbyname) {
    //LXMLURL;
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_xmlurlparse) {
    LXMLURL;
    bool ret = false;
    XMLURL * url = RECAST(args[1],XMLURL *);
    XMLURL tmp = *url;
    XTRY( ret = xmlurl->parse((const XMLCh *)ARGSTR(0),(XMLURL &)*url); );
    { args.GetReturnValue().Set(JS_BOOL(ret)); return; }
  }

  JS_METHOD(_xmlurl_destructor) {
    /* v8::TryCatch tc; */
    //LXMLURL;
    //FILEINPUT;
    //XTRY( xpath->~XMLURL (); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  //	URLInputSource
  //
  JS_METHOD(_urlinput) {
    /* v8::TryCatch tc; */
    if (args.Length()<1) {
      JS_RETURN_ERROR("[_url()] ERROR: Missing input parameter");
    }
    ASSERT_CONSTRUCTOR;
    if (xdom::initialized!=true) {
      xercesc_3_1::XMLPlatformUtils::Initialize();
      xdom::initialized=true;
    }
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add( args.This(), "~URLInputSource");
    URLInputSource * url = NULL;
    if (args[0]->IsExternal()) {
      url = RECAST(args[0],URLInputSource *);
    }
    else if (args[0]->IsObject()) {
      url = RECAST(args[0]->ToObject()->GetInternalField(0),URLInputSource *);
    }
    if (url==NULL) {
      JS_RETURN_ERROR("[_url()] ERROR: \"url\" is a null pointer");
    }
    else {
      SAVE_PTR(0, url);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_urlinputurlsrc) {
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_urlinput_destructor) {
    /* v8::TryCatch tc; */
    //FILEINPUT;
    //XTRY( xpath->~URLInputSource (); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  /**
   *	DOMXPathNamespace
   **/
  JS_METHOD(_xpathnamespace) {
    /* v8::TryCatch tc; */
    if (args.Length()<1)
      JS_RETURN_ERROR("[_xpathnamespace()] ERROR: Missing input parameter");
    ASSERT_CONSTRUCTOR;
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMXPathNamespace");
    DOMXPathNamespace * xpath = NULL;
    if (args[0]->IsExternal()) {
      xpath = RECAST(args[0],DOMXPathNamespace *);
    }
    else if (args[0]->IsObject()) {
      xpath = RECAST(args[0]->ToObject()->GetInternalField(0),DOMXPathNamespace *);
    }
    if (xpath==NULL) {
      JS_RETURN_ERROR("[_xpathnamespace()] ERROR: \"xpath\" is a null pointer");
    }
    else {
      SAVE_PTR(0, xpath);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_xpathgetownerelement) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_xpathgetownerelement()] ERROR: Too many input parameters");
    XPATH;
    DOMElement * el = NULL;
    XTRY( el = xpath->getOwnerElement(); );
    if (el==NULL) {
      JS_RETURN_ERROR("[_xpathgetownerelement()] ERROR: \"el\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)el) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::felement)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_xpathnamespace_destructor) {
    /* v8::TryCatch tc; */
    //XPATH;
    //XTRY( xpath->~DOMXPathNamespace(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  //	**********************************************		//
  //	**********************************************		//

  /**
   *	DOMCDATASection
   **/
  JS_METHOD(_cdatasection) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_cdatasection()] ERROR: Incorrect number of input parameters");
    ASSERT_CONSTRUCTOR;
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMCDATASection");
    DOMCDATASection * cdatasect = NULL;
    if (args[0]->IsExternal()) {
      cdatasect = RECAST(args[0],DOMCDATASection *);
    }
    else if (args[0]->IsObject()) {
      cdatasect = RECAST(args[0]->ToObject()->GetInternalField(0),DOMCDATASection *);
    }
    if (cdatasect==NULL) {
      JS_RETURN_ERROR("[_cdatasection()] ERROR: \"cdatasect\" is a null pointer");
    }
    else {
      SAVE_PTR(0, cdatasect);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_cdatasection_destructor) {
    /* v8::TryCatch tc; */
    //CDATASECT;
    //XTRY( cdatasect->~DOMCDATASection(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  /**
   *	DOMStringList
   **/

  JS_METHOD(_stringlist) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_stringlist()] ERROR: Incorrect number of input parameters");
    ASSERT_CONSTRUCTOR;
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMStringList");
    DOMStringList * dslist = NULL;
    if (args[0]->IsExternal()) {
      dslist = RECAST(args[0],DOMStringList *);
    }
    else if (args[0]->IsObject()) {
      dslist = RECAST(args[0]->ToObject()->GetInternalField(0),DOMStringList *);
    }
    if (dslist==NULL) {
      JS_RETURN_ERROR("[_stringlist()] ERROR: \"dslist\" is a null pointer");
    }
    else {
      SAVE_PTR(0, dslist);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_stringlistitem) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_stringlistitem()] ERROR: Incorrect number of input parameters");
    STRINGLIST;
    XMLSize_t index = (XMLSize_t)(args[0]->ToInteger()->IntegerValue());
    XS val = NULL;
    XTRY( val = (XMLCh *)dslist->item(index); );
    if (val==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(val);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_stringlistgetlength) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_stringlistgetlength()] ERROR: Too many input parameters");
    STRINGLIST;
    XMLSize_t length = 0;
    XTRY( length = dslist->getLength(); );
    { args.GetReturnValue().Set(JS_INT(length)); return; }
  }

  JS_METHOD(_stringlistcontains) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_stringlistcontains()] ERROR: Incorrect number of input parameters");
    STRINGLIST;
    SS val(*v8::String::Utf8Value(args[0]->ToString()));
    bool ret = false;
    XTRY( ret = dslist->contains(X_STR(val)); );
    { args.GetReturnValue().Set(JS_BOOL(ret)); return; }
  }

  JS_METHOD(_stringlist_destructor) {
    /* v8::TryCatch tc; */
    //STRINGLIST;
    XTRY(
	//dslist->release();
	//dslist->~DOMStringList(); 
    );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  /**
   *	DOMNamedNodeMap
   **/

  JS_METHOD(_namednodemap) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_namednodemap()] ERROR: Incorrect number of input parameters");
    ASSERT_CONSTRUCTOR;
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMNamedNodeMap");
      DOMNamedNodeMap * nodemap = NULL;
    if (args[0]->IsExternal()) {
      nodemap = RECAST(args[0],DOMNamedNodeMap *);
    }
    else if (args[0]->IsObject()) {
      nodemap = RECAST(args[0]->ToObject()->GetInternalField(0),DOMNamedNodeMap *);
    }
    if (nodemap==NULL) {
      JS_RETURN_ERROR("[_namednodemap()] ERROR: \"nodemap\" is a null pointer");
    }
    else {
      SAVE_PTR(0, nodemap);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_nodemapitem) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_nodemapitem()] ERROR: Incorrect number of input parameters");
    NODEMAP;
    XMLSize_t index = (XMLSize_t)(args[0]->ToInteger()->IntegerValue());
    DOMNode * item = NULL;
    XTRY( item = nodemap->item(index); );
    if (item==NULL) {
      JS_RETURN_ERROR("[_nodemapitem()] ERROR: \"item\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)item) };
      v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_nodemapgetlength) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodemapgetlength()] ERROR: Too many input parameters");
    NODEMAP;
    XMLSize_t length = 0;
    XTRY( length = nodemap->getLength(); );
    { args.GetReturnValue().Set(JS_INT(length)); return; }
  }

  JS_METHOD(_nodemapgetnameditem) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_nodemapgetnameditem()] ERROR: Incorrect number of input parameters");
    NODEMAP;
    DOMNode * item = NULL;
    XTRY( item = nodemap->getNamedItem(ARGSTR(0)); );
    if (item==NULL) {
      JS_RETURN_ERROR("[_nodemapgetnameditem()] ERROR: \"item\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)item) };
      v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_nodemapgetnameditemns) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_nodemapgetnameditemns()] ERROR: Incorrect number of input parameters");
    NODEMAP;
    DOMNode * item = NULL;
    XTRY( item = nodemap->getNamedItemNS(ARGSTR(0),ARGSTR(1)); );
    if (item==NULL) {
      JS_RETURN_ERROR("[_nodemapgetnameditemns()] ERROR: \"item\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)item) };
      v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_nodemapsetnameditem) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_nodemapsetnameditem()] ERROR: Incorrect number of input parameters");
    NODEMAP;
    DOMNode * arg = NULL;
    if (args[0]->IsExternal()) {
      arg = RECAST(args[0],DOMNode *);
    }
    else if (args[0]->IsObject()) {
      v8::Local<v8::Object> tobj( args[0]->ToObject() );
      arg = RECAST(tobj->GetInternalField(0),DOMNode *);
    }
    if (arg==NULL) {
      JS_RETURN_ERROR("[_nodemapsetnameditem()] ERROR: \"arg\" is a null pointer");
    } else {
      DOMNode * newNode = NULL;
      XTRY( newNode = nodemap->setNamedItem(arg); );
      if (newNode==NULL) {
	JS_RETURN_ERROR("[_nodemapsetnameditem()] ERROR: \"newNode\" is a null pointer");
      }
      else {
	v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)newNode) };
	v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
	{ args.GetReturnValue().Set(ret); return; };
      }
    }
  }

  JS_METHOD(_nodemapsetnameditemns) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_nodemapsetnameditemns()] ERROR: Incorrect number of input parameters");
    NODEMAP;
    DOMNode * arg = NULL;
    if (args[0]->IsExternal()) {
      arg = RECAST(args[0],DOMNode *);
    }
    else if (args[0]->IsObject()) {
      v8::Local<v8::Object> tobj( args[0]->ToObject() );
      arg = RECAST(tobj->GetInternalField(0),DOMNode *);
    }
    if (arg==NULL) {
      JS_RETURN_ERROR("[_nodemapsetnameditem()] ERROR: \"arg\" is a null pointer");
    }
    else {
      DOMNode * newNode = NULL;
      XTRY( newNode = nodemap->setNamedItemNS(arg); );
      if (newNode==NULL) {
	JS_RETURN_ERROR("[_nodemapsetnameditem()] ERROR: \"newNode\" is a null pointer");
      }
      else {
	v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)newNode) };
	v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
	{ args.GetReturnValue().Set(ret); return; };
      }
    }
  }

  JS_METHOD(_nodemapremovenameditem) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_nodemapremovenameditem()] ERROR: Incorrect number of input parameters");
    NODEMAP;
    DOMNode * item = NULL;
    XTRY( item = nodemap->removeNamedItem(ARGSTR(0)); );
    if (item==NULL) {
      JS_RETURN_ERROR("[_nodemapremovenameditem()] ERROR: \"item\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)item) };
      v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_nodemapremovenameditemns) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_nodemapremovenameditemns()] ERROR: Incorrect number of input parameters");
    NODEMAP;
    DOMNode * item = NULL;
    XTRY( item = nodemap->removeNamedItemNS(ARGSTR(0),ARGSTR(1)); );
    if (item==NULL) {
      JS_RETURN_ERROR("[_nodemapremovenameditemns()] ERROR: \"item\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)item) };
      v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_namednodemap_destructor) {
    /* v8::TryCatch tc; */
    NODEMAP;
    XTRY( nodemap->~DOMNamedNodeMap(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  /**
   *	DOMNodeList
   **/

  JS_METHOD(_nodelist) {
    /* v8::TryCatch tc; */
    if (args.Length()<1)
      JS_RETURN_ERROR("[_nodelist()] ERROR: Missing input parameter");
    ASSERT_CONSTRUCTOR;
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMNodeList");
    DOMNodeList * nodelist = RECAST(args[0],DOMNodeList *);
    SAVE_PTR(0, nodelist);
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_nodelistitem) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_nodelistitem()] ERROR: Incorrect number of input parameters");
    NODELIST;
    XMLSize_t index = (XMLSize_t)(args[0]->ToInteger()->IntegerValue());
    DOMNode * item = NULL;
    XTRY( item = nodelist->item(index); );
    if (item==NULL) {
      JS_RETURN_ERROR("[_nodelistitem()] ERROR: \"item\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)item) };
      v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_nodelistgetlength) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodelistgetlength()] ERROR: Too many input parameters");
    NODELIST;
    XMLSize_t length = 0;
    XTRY( length = nodelist->getLength(); );
    { args.GetReturnValue().Set(JS_INT(length)); return; }
  }

  JS_METHOD(_nodelisttoarray) {
    //v8::TryCatch tc;
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodelisttoarray()] ERROR: Too many input parameters");
    NODELIST;
    v8::Handle<v8::Array> ret;
    XMLSize_t len = 0;
    XTRY( len = nodelist->getLength(); );
    if (len > 0) {
      ret = v8::Array::New(JS_ISOLATE, len);
      for (unsigned int i = (int)len; i < len; i++) {
	DOMNode * val = NULL;
	XTRY( val = nodelist->item(i); );
	if (val==NULL) {
	  JS_RETURN_ERROR("[_nodelisttoarray()] ERROR: \"val\" is a null pointer");
	}
	else {
	  v8::Local<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)val) };
	  v8::Handle<v8::Object> tmp(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
	  ret->Set(JS_INT(i), tmp);
	}
      }
    }
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_nodelist_destructor) {
    /* v8::TryCatch tc; */
    NODELIST;
    XTRY( nodelist->~DOMNodeList(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  /**
   *	DOMUserDataHandler
   **/
  JS_METHOD(_domuserdatahandler) {
    /* v8::TryCatch tc; */
    if (args.Length()<1) {
      JS_RETURN_ERROR("[_domuserdatahandler()] ERROR: Missing input parameter");
    }
    ASSERT_CONSTRUCTOR;
    if (xdom::initialized!=true) {
      xercesc_3_1::XMLPlatformUtils::Initialize();
      xdom::initialized=true;
    }
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMUserDataHandler");
    DOMUserDataHandler * dhandler = NULL;
    if (args.Length()>1) {
      
      { args.GetReturnValue().SetUndefined(); return; }
    }
    else {
      if (args[0]->IsExternal()) {
	dhandler = RECAST(args[0],DOMUserDataHandler *);
      }
      else if (args[0]->IsObject()) {
	dhandler = RECAST(args[0]->ToObject()->GetInternalField(0),DOMUserDataHandler *);
      }
      if (dhandler==NULL) {
	JS_RETURN_ERROR("[_domuserdatahandler()] ERROR: \"dhandler\" is a null pointer");
      }
      else {
	SAVE_PTR(0, dhandler);
	{ args.GetReturnValue().Set(args.This()); return; };
      }
    }
  }

  JS_METHOD(_domuserdatahandlerhandle) {
    /* v8::TryCatch tc; */
    if (args.Length()!=5) {
      JS_RETURN_ERROR("[_domuserdatahandlerhandle()] ERROR: Incorrect number of input parameters");
    }
    if (xdom::initialized!=true) {
      xercesc_3_1::XMLPlatformUtils::Initialize();
      xdom::initialized=true;
    }
    USERDATAHANDLER;
    DOMOPTYPE operation = (DOMOPTYPE)args[0]->ToInteger()->IntegerValue();
    void * data = RECAST(args[2],void *);
    DOMNode * src = NULL;
    DOMNode * dst = NULL;
    if (args[3]->IsExternal()) {
      src = RECAST(args[3],DOMNode *);
    }
    else if (args[3]->IsObject()) {
      v8::Local<v8::Object> tobj( args[3]->ToObject() );
      src = RECAST(tobj->GetInternalField(0),DOMNode *);
    }
    if (args[4]->IsExternal()) {
      dst = RECAST(args[4],DOMNode *);
    }
    else if (args[4]->IsObject()) {
      v8::Local<v8::Object> tobj( args[4]->ToObject() );
      dst = RECAST(tobj->GetInternalField(0),DOMNode *);
    }
    if (src==NULL) {
      JS_RETURN_ERROR("[_handle()] ERROR: \"src\" is a null pointer");
    }
    else if (dst==NULL) {
      JS_RETURN_ERROR("[_handle()] ERROR: \"dst\" is a null pointer");
    }
    else {
      XTRY( dhandler->handle(operation,ARGSTR(1),data,src,dst); );
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_domuserdatahandler_destructor) {
    /* v8::TryCatch tc; */
    USERDATAHANDLER;
    XTRY( dhandler->~DOMUserDataHandler(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  /**
   *	DOMImplementationLS constructor:
   *
   **/
  JS_METHOD(_implls) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_implls()] ERROR: Incorrect number of input parameters");
    }
    ASSERT_CONSTRUCTOR;
    if (xdom::initialized!=true) {
      xercesc_3_1::XMLPlatformUtils::Initialize();
      xdom::initialized=true;
    }
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMImplementationLS");
    SAVE_PTR(0,NULL);
    DOMImplementationLS * domls = NULL;
    if (args[0]->IsExternal()) {
      domls = RECAST(args[0],DOMImplementationLS *);
    }
    else if (args[0]->IsObject()) {
      std::string domtype( *USTR((args[0]->ToObject()->Get(JS_STR("_domtype_")))->ToString()) );
      if (domtype=="DOMImplementationLS") {
        domls = RECAST(args[0]->ToObject()->GetInternalField(0),DOMImplementationLS *);
      }
      else if (domtype=="DOMImplementation") {
	DOMImplementation * dom = NULL;
	dom = RECAST(args[0]->ToObject()->GetInternalField(0),DOMImplementation *);
	if (dom==NULL) {
	  JS_RETURN_ERROR("[_implls()] ERROR: \"dom\" is a null pointer");
	}
	else {
	  domls = (DOMImplementationLS *)dom;
	}
      }
    }
    if (domls==NULL) {
      JS_RETURN_ERROR("[_implls()] ERROR: \"domls\" is a null pointer");
    }
    else {
      SAVE_PTR(0,domls);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_impllscreatelsparser) {
    DOMLS;
    DOMImplementationLS::DOMImplementationLSMode mode = DOMImplementationLS::MODE_SYNCHRONOUS;
    if (args.Length()>0) {
      mode = (DOMImplementationLS::DOMImplementationLSMode)args[0]->ToInteger()->IntegerValue();
    }
    XS schemaType = NULL;
    if (args.Length()>1) {
      schemaType = ARGSTR(1);
    }
    MemoryManager * manager = XMLPlatformUtils::fgMemoryManager;
    if (args.Length()>2) {
      if (args[2]->IsExternal()) {
	manager = RECAST(args[2],MemoryManager *);
      }
      else if (args[2]->IsObject()) {
	manager = RECAST(args[2]->ToObject()->GetInternalField(0),MemoryManager *);
      }
    }
    XMLGrammarPool * gramPool = NULL;
    if (args.Length()>3) {
      if (args[2]->IsExternal()) {
	gramPool = RECAST(args[3],XMLGrammarPool *);
      }
      else if (args[3]->IsObject()) {
	gramPool = RECAST(args[3]->ToObject()->GetInternalField(0),XMLGrammarPool *);
      }
    }
    DOMLSParser * parser = NULL;
    XLSTRY( parser = domls->createLSParser(mode,schemaType,manager,gramPool); );
    if (parser==NULL) {
      JS_RETURN_ERROR("[_createlsparser()] ERROR: \"parser\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)parser) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fparser)->GetFunction()->NewInstance(fargc,fargv) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_impllscreatelsserializer) {
    DOMLS;
    MemoryManager * manager = XMLPlatformUtils::fgMemoryManager;
    if (args.Length()>0) {
      if (args[0]->IsExternal()) {
	manager = RECAST(args[0],MemoryManager *);
      }
      else if (args[0]->IsObject()) {
	manager = RECAST(args[0]->ToObject()->GetInternalField(0),MemoryManager *);
      }
    }
    DOMLSSerializer * serializer = NULL;
    XLSTRY( serializer = domls->createLSSerializer(manager); );
    if (serializer==NULL) {
      JS_RETURN_ERROR("[_createlsserializer()] ERROR: \"serializer\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)serializer) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fserializer)->GetFunction()->NewInstance(fargc,fargv) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_impllscreatelsinput) {
    DOMLS;
    MemoryManager * manager = XMLPlatformUtils::fgMemoryManager;
    if (args.Length()>0) {
      if (args[0]->IsExternal()) {
	manager = RECAST(args[0],MemoryManager *);
      }
      else if (args[0]->IsObject()) {
	manager = RECAST(args[0]->ToObject()->GetInternalField(0),MemoryManager *);
      }
    }
    DOMLSInput * lsinput = NULL;
    XLSTRY( lsinput = domls->createLSInput(manager); );
    if (lsinput==NULL) {
      JS_RETURN_ERROR("[_createlsinput()] ERROR: \"lsinput\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)lsinput) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::finput)->GetFunction()->NewInstance(fargc,fargv) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_impllscreatelsoutput) {
    DOMLS;
    MemoryManager * manager = XMLPlatformUtils::fgMemoryManager;
    if (args.Length()>0) {
      if (args[0]->IsExternal()) {
	manager = RECAST(args[0],MemoryManager *);
      }
      else if (args[0]->IsObject()) {
	manager = RECAST(args[0]->ToObject()->GetInternalField(0),MemoryManager *);
      }
    }
    DOMLSOutput * lsoutput = NULL;
    XLSTRY( lsoutput = domls->createLSOutput(manager); );
    if (lsoutput==NULL) {
      JS_RETURN_ERROR("[_createlsoutput()] ERROR: \"lsoutput\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)lsoutput) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::foutput)->GetFunction()->NewInstance(fargc,fargv) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }


  /**
   *	~DOMImplementationLS method
   *	- Destructor for DOMImplementationLS objects
   */ 
  JS_METHOD(_implls_destructor) {
    /* v8::TryCatch tc; */
    SAVE_PTR(0,NULL);
    { args.GetReturnValue().Set(args.This()); return; };
  }


  /**
   *	DOMImplementation constructor:
   * 	- Adds "~DOMImplementation()" destructor method to global Garbage Collector
   **/
  JS_METHOD(_impl) {
    /* v8::TryCatch tc; */
    ASSERT_CONSTRUCTOR;
    // initialize the XML library
    if (xdom::initialized!=true) {
      xercesc_3_1::XMLPlatformUtils::Initialize();
      xdom::initialized=true;
    }
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMImplementation");
    SAVE_PTR(0,NULL);
    DOMImplementation * dom = NULL;
    const XMLCh dfltSchemaType[] = {chLatin_L, chLatin_S, chNull};
    XMLCh * schemaType = (XMLCh *)dfltSchemaType;
    if (args.Length()==0) {
      dom = xercesc_3_1::DOMImplementationRegistry::getDOMImplementation(schemaType);
    }
    else {
      SS attr("");
      if (args[0]->IsExternal()) {
        dom = RECAST(args[0],xercesc_3_1::DOMImplementation *);
      }
      else if (args[0]->IsString()) {
	XTRY( dom = xercesc_3_1::DOMImplementationRegistry::getDOMImplementation((XMLCh *) *v8::String::Utf8Value(args[0]->ToString())); );
      }
      else if (args[0]->IsObject()) {
	if (args[0]->ToObject()->Has(JS_STR("_domtype_"))) {
	  std::string domtype( *USTR(args[0]->ToObject()->Get(JS_STR("_domtype_"))->ToString()) );
	  if (domtype=="DOMImplementation") {
	    dom = RECAST(args[0]->ToObject()->GetInternalField(0),xercesc_3_1::DOMImplementation *);
	  }
	}
	if (dom==NULL) {
	  if (args[0]->ToObject()->Has(JS_STR("DOMImplementation"))) {
	    dom = RECAST(args[0]->ToObject()->Get(JS_STR("DOMImplementation"))->ToObject()->GetInternalField(0),DOMImplementation *);
	  }
	  else if (args[0]->ToObject()->Has(JS_STR("DOM"))) {
	    dom = RECAST(args[0]->ToObject()->Get(JS_STR("DOM"))->ToObject()->GetInternalField(0),DOMImplementation *);
	  }
	  else if (args[0]->ToObject()->Has(JS_STR("dom"))) {
	    dom = RECAST(args[0]->ToObject()->Get(JS_STR("dom"))->ToObject()->GetInternalField(0),DOMImplementation *);
	  }
	  else if (args[0]->ToObject()->Has(JS_STR("implementation"))) {
	    dom = RECAST(args[0]->ToObject()->Get(JS_STR("implementation"))->ToObject()->GetInternalField(0),DOMImplementation *);
	  }
	  else {
	    schemaType = X("LS");
	    if (args[0]->ToObject()->Has(JS_STR("schema"))) {
	      schemaType = (XMLCh *) *v8::String::Utf8Value( args[0]->ToObject()->Get(JS_STR("schema"))->ToString() );
	    }
	    XTRY( dom = xercesc_3_1::DOMImplementationRegistry::getDOMImplementation((const XMLCh *)schemaType); );
	  }
	}
      }
    }
    if (dom==NULL) {
      JS_RETURN_ERROR("[_impl()] ERROR: \"dom\" is a null pointer");
    }
    else {
      SAVE_PTR(0,dom);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_domcreateimplementationls) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_domcreateimplementationls()] ERROR: Too many input parameters");
    DOM;
    v8::Local<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)dom) };
    v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomls)->GetFunction()->NewInstance(1, fargs) );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_domgetimplementation) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_domgetimplementation()] ERROR: Too many input parameters");
    DOM;
    v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)dom) };
    args.GetReturnValue().Set(v8::Handle<v8::Function>::Cast(args.This()->Get(JS_STR("DOMImplementation")))->NewInstance(1, fargs));
  }

  JS_METHOD(_domloaddomexceptionmsg) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_domloaddomexceptionmsg()] ERROR: Incorrect number of input parameters");
    DOM;
    short msgToLoad = (short)args[0]->ToInteger()->Int32Value();
    XS const toFill = ARGSTR(1);
    const XMLSize_t maxChars = sizeof(toFill);
    XTRY( dom->loadDOMExceptionMsg(msgToLoad, toFill, maxChars); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_domhasfeature) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_domhasfeature()] ERROR: Incorrect number of input parameters");
    DOM;
    bool ret = false;
    XTRY( ret = dom->hasFeature(ARGSTR(0),ARGSTR(1)); );
    { args.GetReturnValue().Set(JS_BOOL(ret)); return; }
  }

  JS_METHOD(_domcreateparser) {
    /* v8::TryCatch tc; */
    if (args.Length()>1)
      JS_RETURN_ERROR("[_domcreateparser()] ERROR: Incorrect number of input parameters");
    DOM;
    XS schemaType = NULL;
    if (args.Length()>0) {
      if (args[0]->IsString()) {
	schemaType = ARGSTR(0);
      }
    }
    DOMLSParser * parser = NULL;
    XLSTRY(
	parser = ((DOMImplementationLS *)dom)->createLSParser(xercesc_3_1::DOMImplementationLS::MODE_SYNCHRONOUS, schemaType);
//	parser = ((DOMImplementationLS *)dom)->createLSParser(xercesc_3_1::DOMImplementationLS::MODE_ASYNCHRONOUS, schemaType);
	//DOMConfiguration* dc = parser->getDomConfig();
	//dc->setParameter(XMLUni::fgXercesSchema, true);
	//dc->setParameter(XMLUni::fgXercesCacheGrammarFromParse, true);
	//dc->setParameter(XMLUni::fgXercesUseCachedGrammarInParse, true);
	//dc->setParameter(XMLUni::fgDOMValidate, true);
    );
    if (parser==NULL) {
      JS_RETURN_ERROR("[_impl()] ERROR: \"parser\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)parser), v8::External::New(JS_ISOLATE, (void *)dom) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fparser)->GetFunction()->NewInstance(2, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_domcreatedocumenttype) {
    /* v8::TryCatch tc; */
    if (args.Length()!=3 && args.Length()!=1)
      JS_RETURN_ERROR("[_domcreatedocumenttype()] ERROR: Incorrect number of input parameters");
    DOM;
    XS qualifiedName = X("");
    XS publicId = X("");
    XS systemId = X("");
    if (!(args[0]->IsUndefined())) if (args[0]->IsString()) {
      if (!(args[0]->IsNull()))
	qualifiedName = ARGSTR(0);
    }
    if (!(args[1]->IsUndefined())) if (args[1]->IsString()) {
      if (!(args[1]->IsNull()))
	publicId = ARGSTR(1); // << *v8::String::Utf8Value(args[1]->ToString());
    }
    if (!(args[2]->IsUndefined())) if (args[2]->IsString()) {
      if (!(args[2]->IsNull()))
	systemId = ARGSTR(2); // << *v8::String::Utf8Value(args[2]->ToString());
    }
    DOMDocumentType * docType = NULL;
    if (!(args[0]->IsNull() || args[1]->IsNull() || args[2]->IsNull())) {
      XTRY( docType = dom->createDocumentType(qualifiedName,publicId,systemId); );
    }
    else if (args[1]->IsNull() && !(args[0]->IsNull() || args[2]->IsNull())) {
      XTRY( docType = dom->createDocumentType(qualifiedName,NULL,systemId); );
    }
    else if (args[2]->IsNull() && !(args[0]->IsNull() || args[1]->IsNull())) {
      XTRY( docType = dom->createDocumentType(qualifiedName,publicId,NULL); );
    }
    else if (args[2]->IsNull() && args[1]->IsNull() && !(args[0]->IsNull())) {
      XTRY( docType = dom->createDocumentType(qualifiedName,NULL,NULL); );
    }
    else if (args[2]->IsNull() && args[0]->IsNull() && !(args[1]->IsNull())) {
      XTRY( docType = dom->createDocumentType(NULL,publicId,NULL); );
    }
    else if (args[0]->IsNull() && args[1]->IsNull() && !(args[2]->IsNull())) {
      XTRY( docType = dom->createDocumentType(NULL,NULL,systemId); );
    }
    else if (args[0]->IsNull() && !(args[1]->IsNull() || args[2]->IsNull())) {
      XTRY( docType = dom->createDocumentType(NULL,publicId,systemId); );
    }
    if (docType==NULL) {
      JS_RETURN_ERROR("[_domcreatedocumenttype()] ERROR: \"docType\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (DOMDocumentType *)docType) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdocumenttype)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_domcreatedocument) {
    /* v8::TryCatch tc; */
    if (args.Length()!=3 && args.Length()!=0)
      JS_RETURN_ERROR("[_domcreatedocumenttype()] ERROR: Incorrect number of input parameters");
    DOM;
    DOMDocumentType * docType = NULL;
    DOMDocument * doc = NULL;
    if (args.Length()==0) {
      XTRY( doc = dom->createDocument(); );
    }
    else {
      SS namespaceURI(*v8::String::Utf8Value(args[0]->ToString()));
      SS qualifiedName(*v8::String::Utf8Value(args[1]->ToString()));
      if (args[2]->IsExternal()) {
	docType = RECAST(args[2],DOMDocumentType *);
      }
      else if (args[2]->IsObject()) {
	v8::Handle<v8::Object> tobj = args[2]->ToObject();
	docType = RECAST(tobj->GetInternalField(0),DOMDocumentType *);
      }
      if (docType==NULL) {
	JS_RETURN_ERROR("[_domcreatedocument()] ERROR: \"docType\" is a null pointer");
      }
      else {
	XTRY( doc = dom->createDocument(X_STR(namespaceURI),X_STR(qualifiedName),docType); );
      }
    }
    if (doc==NULL) {
      JS_RETURN_ERROR("[_domcreatedocument()] ERROR: \"doc\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)doc) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdocument)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  /**
   *	~DOM method
   *	- Destructor for DOMImplementation objects
   */ 
  JS_METHOD(_impl_destructor) {
    /* v8::TryCatch tc; */
    DOM;
    if (dom!=NULL) {
      // SAVE_PTR(0,NULL);
      //X TRY( dom->~DOMImplementation(); );
    }
    //XMLPlatformUtils::Terminate();
    //xdom::initialized=false;
    { args.GetReturnValue().Set(args.This()); return; };
  }


  /**
   *	DOMLSSerializer constructor:
   * 	- Adds "~DOMLSSerializer()" method to global GC
   */
  JS_METHOD(_serializer) {
    ///* v8::TryCatch tc; */
    if (args.Length()<1) {
      JS_RETURN_ERROR("[_serializer()] ERROR: Missing input parameter");
    }
    ASSERT_CONSTRUCTOR;
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMLSSerializer");
    DOMImplementation * dom = NULL;
    DOMLSSerializer * serializer = NULL;
    if (args[0]->IsExternal()) {
      serializer = RECAST(args[0], DOMLSSerializer *);
    }
    else if (args[0]->IsObject()) {
      serializer = RECAST(args[0]->ToObject()->GetInternalField(0), DOMLSSerializer *);
    }
    if (args[1]->IsExternal()) {
      dom = RECAST(args[1], DOMImplementation *);
    }
    else if (args[1]->IsObject()) {
      dom = RECAST(args[1]->ToObject()->GetInternalField(0), DOMImplementation *);
    }
    if (serializer==NULL) {
      JS_RETURN_ERROR("[_serializer()] ERROR: \"serializer\" is a null pointer");
    }
    else {
      SAVE_PTR(0,serializer);
      SAVE_PTR(1,dom);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_serializergetdomconfig) {
    /* v8::TryCatch tc; */
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_serializergetdomconfig()] ERROR: Too many input parameters");
    }
    SERIALIZER;
    DOMConfiguration * domconfig = NULL;
    XLSTRY( domconfig = serializer->getDomConfig(); );
    if (domconfig==NULL) {
      JS_RETURN_ERROR("[_serializergetdomconfig()] ERROR: \"domconfig\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)domconfig) };
      v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomconfiguration)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_serializergetfilter) {
    /* v8::TryCatch tc; */
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_serializergetfilter()] ERROR: Too many input parameters");
    }
    SERIALIZER;
    DOMLSSerializerFilter * filter = NULL;
    XLSTRY( filter = (DOMLSSerializerFilter *)serializer->getFilter(); );
    if (filter==NULL) {
      JS_RETURN_ERROR("[_serializergetfilter()] ERROR: \"filter\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)filter) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fserializerfilter)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_serializergetnewline) {
    /* v8::TryCatch tc; */
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_serializergetfilter()] ERROR: Too many input parameters");
    }
    SERIALIZER;
    DOMLSSerializerFilter * filter = NULL;
    XLSTRY( filter = (DOMLSSerializerFilter *)serializer->getFilter(); );
    if (filter==NULL) {
      JS_RETURN_ERROR("[_serializergetfilter()] ERROR: \"filter\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)filter) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fserializerfilter)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_serializersetfilter) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_serializersetfilter()] ERROR: Incorrect number of input parameters");
    }
    SERIALIZER;
    DOMLSSerializerFilter * filter = NULL;
    if (args[0]->IsExternal()) {
      filter = RECAST(args[0],DOMLSSerializerFilter *);
    }
    else if (args[0]->IsObject()) {
      filter = RECAST(args[0]->ToObject()->GetInternalField(0),DOMLSSerializerFilter *);
    }
    if (filter==NULL) {
      JS_RETURN_ERROR("[_serializersetfilter()] ERROR: \"filter\" is a null pointer");
    }
    XLSTRY( serializer->setFilter(filter); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_serializersetnewline) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_serializersetnewline()] ERROR: Incorrect number of input parameters");
    }
    SERIALIZER;
    XLSTRY( serializer->setNewLine(ARGSTR(0)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_serializerwrite) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2) {
      JS_RETURN_ERROR("[_serializerwrite()] ERROR: Incorrect number of input parameters");
    }
    SERIALIZER;
    DOMNode * node = NULL;
    DOMLSOutput * dst = NULL;
    if (args[0]->IsExternal()) {
      node = RECAST(args[0],DOMNode *);
    }
    else if (args[0]->IsObject()) {
      node = RECAST(args[0]->ToObject()->GetInternalField(0),DOMNode *);
    }
    if (node==NULL) {
      JS_RETURN_ERROR("[_serializerwrite()] ERROR: \"node\" is a null pointer");
    }
    if (args[1]->IsExternal()) {
      dst = RECAST(args[1],DOMLSOutput *);
    }
    else if (args[0]->IsObject()) {
      dst = RECAST(args[1]->ToObject()->GetInternalField(1),DOMLSOutput *);
    }
    if (dst==NULL) {
      JS_RETURN_ERROR("[_serializerwrite()] ERROR: \"dst\" is a null pointer");
    }
    XLSTRY( serializer->write(node,dst); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_serializerwritetouri) {
    if (args.Length()!=2) {
      JS_RETURN_ERROR("[_serializerwritetouri()] ERROR: Incorrect number of input parameters");
    }
    SERIALIZER;
    DOMNode * node = NULL;
    XS uri = (XS)ARGSTR(1);
    if (args[0]->IsExternal()) {
      node = RECAST(args[0],DOMNode *);
    }
    else if (args[0]->IsObject()) {
      node = RECAST(args[0]->ToObject()->GetInternalField(0),DOMNode *);
    }
    if (node==NULL) {
      JS_RETURN_ERROR("[_serializerwritetouri()] ERROR: \"node\" is a null pointer");
    }
    XLSTRY( serializer->writeToURI(node,uri); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_serializerwritetostring) {
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_serializerwritetostring()] ERROR: Incorrect number of input parameters");
    }
    SERIALIZER;
    DOMNode * node = NULL;
    char * ret = NULL;
    if (args[0]->IsExternal()) {
      node = RECAST(args[0],DOMNode *);
    }
    else if (args[0]->IsObject()) {
      node = RECAST(args[0]->ToObject()->GetInternalField(0),DOMNode *);
    }
    if (node==NULL) {
      JS_RETURN_ERROR("[_serializerwritetostring()] ERROR: \"node\" is a null pointer");
    }
    XLSTRY( ret = X(serializer->writeToString(node)); );
    if (ret==NULL) {
      JS_RETURN_ERROR("[_serializerwritetostring()] ERROR: \"ret\" is a null pointer");
    }
    else {
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }


  JS_METHOD(_serializer_destructor) {
    /* v8::TryCatch tc; */
    //SERIALIZER_DOM;
    //dom = NULL;
    // SAVE_PTR(0,NULL);
    // SAVE_PTR(1,NULL);
    XLSTRY(
	// serializer->release();
	// serializer->~DOMLSSerializer();
    );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  /**
   *	DOMLSSerializerFilter constructor:
   * 	- Adds "~DOMLSSerializerFilter()" method to global GC
   */
  JS_METHOD(_serializerfilter) {
    // /* v8::TryCatch tc; */
    if (args.Length()<1) {
      JS_RETURN_ERROR("[_serializerfilter()] ERROR: Missing input parameter");
    }
    ASSERT_CONSTRUCTOR;
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMLSSerializerFilter");
    DOMLSSerializerFilter * filter = NULL;
    if (args[0]->IsExternal()) {
      filter = RECAST(args[0], DOMLSSerializerFilter *);
    }
    else if (args[0]->IsObject()) {
      filter = RECAST(args[0]->ToObject()->GetInternalField(0), DOMLSSerializerFilter *);
    }
    if (filter==NULL)
      JS_RETURN_ERROR("[_serializerfilter()] ERROR: \"filter\" is a null pointer")
    else {
      SAVE_PTR(0,filter);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_serializerfiltergetwhattoshow) {
    SERIALIZERFILTER;
    xercesc_3_1::DOMNodeFilter::ShowType ret = 0;
    XTRY( ret = filter->getWhatToShow(); );
    { args.GetReturnValue().Set(JS_INT(ret)); return; }
  }

  /**
   *	~DOMLSSerializerFilter method
   *	- Destructor for DOMLSSerializerFilter objects
   */ 
  JS_METHOD(_serializerfilter_destructor) {
    /* v8::TryCatch tc; */
    SERIALIZERFILTER;
    // SAVE_PTR(0,NULL);
    XLSTRY( filter->~DOMLSSerializerFilter(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  /**
   *	DOMNodeFilter constructor:
   * 	- Adds "~DOMNodeFilter()" method to global GC
   */
  JS_METHOD(_nodefilter) {
    // /* v8::TryCatch tc; */
    if (args.Length()<1) {
      JS_RETURN_ERROR("[_domnodefilter()] ERROR: Missing input parameter");
    }
    ASSERT_CONSTRUCTOR;
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMNodeFilter");
    DOMNodeFilter * filter = NULL;
    if (args[0]->IsExternal()) {
      filter = RECAST(args[0], DOMNodeFilter *);
    }
    else if (args[0]->IsObject()) {
      filter = RECAST(args[0]->ToObject()->GetInternalField(0), DOMNodeFilter *);
    }
    if (filter==NULL)
      JS_RETURN_ERROR("[_domnodefilter()] ERROR: \"filter\" is a null pointer")
    else {
      SAVE_PTR(0,filter);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_nodefilteracceptnode) {
    NODEFILTER;
    xercesc_3_1::DOMNodeFilter::ShowType ret = 0;
    DOMNode * node = NULL;
    if (args[0]->IsExternal()) {
      node = RECAST(args[0],DOMNode *);
    }
    else if (args[0]->IsObject()) {
      node = RECAST(args[0]->ToObject()->GetInternalField(0),DOMNode *);	
    }
    XTRY( ret = filter->acceptNode(node); );
    { args.GetReturnValue().Set(JS_INT(ret)); return; }
  }

  /**
   *	~DOMNodeFilter method
   *	- Destructor for DOMNodeFilter objects
   */ 
  JS_METHOD(_nodefilter_destructor) {
    /* v8::TryCatch tc; */
    NODEFILTER;
    // SAVE_PTR(0,NULL);
    XLSTRY( filter->~DOMNodeFilter(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  /**
   *	DOMLSParser constructor:
   * 	- Adds "~DOMLSParser()" method to global GC
   */
  JS_METHOD(_parser) {
    ///* v8::TryCatch tc; */
    if (args.Length()<1) {
      JS_RETURN_ERROR("[_parser()] ERROR: Missing input parameter");
    }
    ASSERT_CONSTRUCTOR;
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMLSParser");
    DOMImplementation * dom = NULL;
    DOMLSParser * parser = NULL;
    if (args[0]->IsExternal()) {
      parser = RECAST(args[0], DOMLSParser *);
    }
    else if (args[0]->IsObject()) {
      parser = RECAST(args[0]->ToObject()->GetInternalField(0), DOMLSParser *);
    }
    if (args[1]->IsExternal()) {
      dom = RECAST(args[1], DOMImplementation *);
    }
    else if (args[1]->IsObject()) {
      dom = RECAST(args[1]->ToObject()->GetInternalField(0), DOMImplementation *);
    }
    if (parser==NULL) {
      JS_RETURN_ERROR("[_parser()] ERROR: \"parser\" is a null pointer");
    }
    else {
      SAVE_PTR(0,parser);
      SAVE_PTR(1,dom);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_parsergetdomconfig) {
    /* v8::TryCatch tc; */
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_parsergetdomconfig()] ERROR: Too many input parameters");
    }
    PARSER;
    DOMConfiguration * domconfig = NULL;
    XLSTRY( domconfig = parser->getDomConfig(); );
    if (domconfig==NULL) {
      JS_RETURN_ERROR("[_parsergetdomconfig()] ERROR: \"domconfig\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)domconfig) };
      v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomconfiguration)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_parsergetfilter) {
    /* v8::TryCatch tc; */
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_parsergetfilter()] ERROR: Too many input parameters");
    }
    PARSER;
    DOMLSParserFilter * filter = NULL;
    XLSTRY( filter = (DOMLSParserFilter *)parser->getFilter(); );
    if (filter==NULL) {
      JS_RETURN_ERROR("[_parsergetfilter()] ERROR: \"filter\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)filter) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fparserfilter)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_parsergetasync) {
    /* v8::TryCatch tc; */
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_parsergetasync()] ERROR: Too many input parameters");
    }
    PARSER;
    bool async = false;
    XLSTRY( async = parser->getAsync(); );
    v8::Handle<v8::Boolean> ret( JS_BOOL(async) );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_parsergetbusy) {
    /* v8::TryCatch tc; */
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_parsergetbusy()] ERROR: Too many input parameters");
    }
    PARSER;
    bool busy = false;
    XLSTRY( busy = parser->getBusy(); );
    v8::Handle<v8::Boolean> ret( JS_BOOL(busy) );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_parsersetfilter) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_parsersetfilter()] ERROR: Incorrect number of input parameters");
    }
    PARSER;
    DOMLSParserFilter * filter = NULL;
    if (args[0]->IsExternal()) {
      filter = RECAST(args[0],DOMLSParserFilter *);
    }
    else if (args[0]->IsObject()) {
      filter = RECAST(args[0]->ToObject()->GetInternalField(0),DOMLSParserFilter *);
    }
    if (filter==NULL) {
      JS_RETURN_ERROR("[_parsersetfilter()] ERROR: \"filter\" is a null pointer");
    }
    XLSTRY( parser->setFilter(filter); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_parserparse) {
    v8::TryCatch tc;
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_parserparse()] ERROR: Incorrect number of input parameters");
    }
    PARSER_DOM;
    DOMLSInput * inv = NULL;
    if (args[0]->IsExternal()) {
      inv = RECAST(args[0],DOMLSInput *);
    }
    else if (args[0]->IsObject()) {
      v8::Local<v8::Object> tobj( args[0]->ToObject() );
      std::string domtype( *v8::String::Utf8Value(tobj->Get(JS_STR("_domtype_"))->ToString()) );
      if (domtype=="DOMLSInput") {
	inv = RECAST(args[0]->ToObject()->GetInternalField(0),DOMLSInput *);
      }
    }
    else if (args[0]->IsString()) {
      SS tmp( *v8::String::Utf8Value(args[0]->ToString()) );
      char * src = strdup(tmp.str().c_str());
      size_t isize = strlen(src);
      XMLSize_t * len = reinterpret_cast<XMLSize_t *>(&isize);
      MemBufInputSource * mem = new MemBufInputSource(reinterpret_cast<const XMLByte*>(src),*len,"test",false);
      if (dom==NULL) {
        JS_RETURN_ERROR("[_parserparse()] ERROR (1): \"dom\" is a null pointer");
      }
      inv = ((DOMImplementationLS *)dom)->createLSInput();
      mem->setCopyBufToStream(false);
      inv->setByteStream(mem);
      inv->setEncoding(XMLUni::fgUTF8EncodingString);
    }
    if (inv==NULL) {
      JS_RETURN_ERROR("[_parserparse()] ERROR (2): \"inv\" is a null pointer");
    }
    DOMDocument * doc = NULL;
    XLSTRY( doc = parser->parse(inv); );
    if (doc==NULL) {
      JS_RETURN_ERROR("[_parserparse()] ERROR (3): \"doc\" is a null pointer");
    }
    else {
        v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)doc) };
        v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdocument)->GetFunction()->NewInstance(1, fargs) );
        { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_parserparseuri) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_parserparseuri()] ERROR: Incorrect number of input parameters");
    }
    PARSER;
    XMLURL * uri = NULL;
    if (args[0]->IsExternal()) {
      uri = RECAST(args[0],XMLURL *);
    }
    else if (args[0]->IsObject()) {
      uri = RECAST(args[0]->ToObject()->GetInternalField(0),XMLURL *);
    }
    else if (args[0]->IsString()) {
      char * src = NULL;
      SS tmp( *v8::String::Utf8Value(args[0]->ToString()) );
      src = (char *)tmp.str().c_str();
      XLSTRY( uri = new XMLURL((const XMLCh *)ARGSTR(0)); );
    }
    if (uri==NULL) {
      JS_RETURN_ERROR("[_parserparseuri()] ERROR: \"uri\" is a null pointer");
    }
    DOMDocument * doc = NULL;
   // XLSTRY( doc = parser->parseURI((const char *)src); );
    XLSTRY( doc = parser->parseURI(uri->getURLText()); );
    if (doc==NULL) {
      JS_RETURN_ERROR("[_parserparseuri()] ERROR: \"doc\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)doc) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdocument)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_parserparsewithcontext) {
    v8::TryCatch tc;
    if (args.Length()!=3) {
      JS_RETURN_ERROR("[_parserparsewithcontext()] ERROR: Incorrect number of input parameters");
    }
    PARSER;
    DOMLSInput * inv = NULL;
    if (args[0]->IsExternal()) {
      inv = RECAST(args[0],DOMLSInput *);
    }
    else if (args[0]->IsObject()) {
      inv = RECAST(args[0]->ToObject()->GetInternalField(0),DOMLSInput *);
    }
    else if (args[0]->IsString()) {
      SS tmp( *v8::String::Utf8Value(args[0]->ToString()) );
      const char * src = tmp.str().c_str();
      XMLSize_t len = (XMLSize_t)(tmp.str().length() + 1);
      MemBufInputSource mem((const XMLByte *const)src,len,"parsersrc",false);
      mem.setEncoding(X("UTF-8"));
      inv = (DOMLSInput *)(&mem);
    }
    if (inv==NULL) {
      JS_RETURN_ERROR("[_parserparsewithcontext()] ERROR: \"inv\" is a null pointer");
    }
    DOMNode * context = NULL;
    if (args[1]->IsExternal()) {
      context = RECAST(args[1],DOMNode *);
    }
    else if (args[1]->IsObject()) {
      context = RECAST(args[1]->ToObject()->GetInternalField(0),DOMNode *);
    }
    if (context==NULL) {
      JS_RETURN_ERROR("[_parserparsewithcontext()] ERROR: \"context\" is a null pointer");
    }
    else {
      int action = args[2]->ToInteger()->IntegerValue();
      XLSTRY( parser->parseWithContext((const DOMLSInput *)inv,context,(xercesc_3_1::DOMLSParser::ActionType)action); );
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_parserabort) {
    v8::TryCatch tc;
    PARSER;
    XLSTRY( parser->abort(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_parserresetdocumentpool) {
    v8::TryCatch tc;
    PARSER;
    XLSTRY( parser->resetDocumentPool(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_parserloadgrammar) {
    v8::TryCatch tc;
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_parsergetgrammar) {
    v8::TryCatch tc;
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_parsergetrootgrammar) {
    v8::TryCatch tc;
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_parsergeturitext) {
    v8::TryCatch tc;
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_parserresetcachedgrammarpool) {
    v8::TryCatch tc;
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_parsergetsrcoffset) {
    v8::TryCatch tc;
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_parsergetsrcoffset()] ERROR: Too many input parameters");
    }
    PARSER;
    unsigned int pos = 0;
    XLSTRY( pos = parser->getSrcOffset(); );
    { args.GetReturnValue().Set(JS_INT(pos)); return; }
  }

  JS_METHOD(_parsergetimplementation) {
    v8::TryCatch tc;
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_parsergetimplementation()] ERROR: Too many input parameters");
    }
    DOM;
    if (dom==NULL) {
      JS_RETURN_ERROR("[_parsergetimplementation()] ERROR: \"dom\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)dom) };
      v8::Handle<v8::Object> obj(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdom)->GetFunction()->NewInstance(1, fargs) );
      v8::Handle<v8::Value> ret( obj );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  /**
   *	~DOMLSParser method
   *	- Destructor for DOMLSParser objects
   */ 
  JS_METHOD(_parser_destructor) {
    /* v8::TryCatch tc; */
    //PARSER_DOM;
    //dom = NULL;
    // SAVE_PTR(0,NULL);
    // SAVE_PTR(1,NULL);
    XLSTRY(
	// parser->release();
	// parser->~DOMLSParser();
    );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  /**
   *	DOMLSParserFilter constructor:
   * 	- Adds "~DOMLSParserFilter()" method to global GC
   */
  JS_METHOD(_parserfilter) {
    // /* v8::TryCatch tc; */
    if (args.Length()<1) {
      JS_RETURN_ERROR("[_parserfilter()] ERROR: Missing input parameter");
    }
    ASSERT_CONSTRUCTOR;
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMLSParserFilter");
    DOMLSParserFilter * filter = NULL;
    if (args[0]->IsExternal()) {
      filter = RECAST(args[0], DOMLSParserFilter *);
    }
    else if (args[0]->IsObject()) {
      filter = RECAST(args[0]->ToObject()->GetInternalField(0), DOMLSParserFilter *);
    }
    if (filter==NULL)
      JS_RETURN_ERROR("[_parserfilter()] ERROR: \"filter\" is a null pointer")
    else {
      SAVE_PTR(0,filter);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_parserfilterstartelement) {
    PARSERFILTER;
    xercesc_3_1::DOMLSParserFilter::FilterAction ret;
    DOMElement * el = NULL;
    if (args[0]->IsExternal()) {
      el = RECAST(args[0],DOMElement *);
    }
    else if (args[0]->IsObject()) {
      el = RECAST(args[0]->ToObject()->GetInternalField(0),DOMElement *);
    }
    XTRY( ret = filter->startElement(el); );
    { args.GetReturnValue().Set(JS_INT(ret)); return; }
  }

  JS_METHOD(_parserfiltergetwhattoshow) {
    PARSERFILTER;
    xercesc_3_1::DOMNodeFilter::ShowType ret = 0;
    XTRY( ret = filter->getWhatToShow(); );
    { args.GetReturnValue().Set(JS_INT(ret)); return; }
  }

  /**
   *	~DOMLSParserFilter method
   *	- Destructor for DOMLSParserFilter objects
   */ 
  JS_METHOD(_parserfilter_destructor) {
    /* v8::TryCatch tc; */
    PARSERFILTER;
    // SAVE_PTR(0,NULL);
    XLSTRY( filter->~DOMLSParserFilter(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  /**
   *	DOMConfiguration constructor:
   * 	- Adds "DOMConfiguration()" method to global GC
   */
  JS_METHOD(_domconfiguration) {
    ///* v8::TryCatch tc; */
    ASSERT_CONSTRUCTOR;
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMConfiguration");
    DOMConfiguration * domconfig = NULL;
    if (args.Length()>0) {
      if (args[0]->IsExternal()) {
        domconfig = RECAST(args[0],DOMConfiguration *);
      }
      else if (args[0]->IsObject()) {
	v8::Local<v8::Object> tobj( args[0]->ToObject() );
	domconfig = RECAST(tobj->GetInternalField(0),DOMConfiguration *);
      }
    }
    if (domconfig==NULL) {
      JS_RETURN_ERROR("[_domconfiguration()] ERROR: \"domconfig\" is a null pointer");
    }
    else {
      SAVE_PTR(0,domconfig);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_domconfiggetparameter) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_domconfiggetparameter()] ERROR: Incorrect number of input parameters");
    DOMCONFIG;
    SS name(*v8::String::Utf8Value(args[0]->ToString()));
    bool * paramval = NULL;
    XTRY( paramval = (bool *)domconfig->getParameter(X_STR(name)); );
    if (paramval==NULL) {
      JS_RETURN_ERROR("[_domconfiggetparameter()] ERROR: \"paramval\" is a null pointer");
    }
    else {
      args.GetReturnValue().Set(JS_BOOL(*paramval));
    }
  }

  JS_METHOD(_domconfigsetparameter) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_domconfigsetparameter()] ERROR: Incorrect number of input parameters");
    DOMCONFIG;
    SS name (*v8::String::Utf8Value(args[0]->ToString()));
    bool val = args[1]->ToBoolean()->BooleanValue();
    XTRY( domconfig->setParameter(X_STR(name), val); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_domconfigcansetparameter) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_domconfigcansetparameter()] ERROR: Incorrect number of input parameters");
    DOMCONFIG;
    SS name(*v8::String::Utf8Value(args[0]->ToString()));
    bool val = args[1]->ToBoolean()->BooleanValue();
    bool ret = false;
    XTRY( ret = domconfig->canSetParameter(X_STR(name),val); );
    { args.GetReturnValue().Set(JS_BOOL(ret)); return; }
  }

  JS_METHOD(_domconfiggetparameternames) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_domconfiggetparameternames()] ERROR: Too many input parameters");
    DOMCONFIG;
    DOMStringList * dslist = NULL;
    XTRY( dslist = (DOMStringList *)domconfig->getParameterNames(); );
    if (dslist==NULL) {
      JS_RETURN_ERROR("[_domconfiggetparameternames()] ERROR: \"dslist\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)dslist) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fstringlist)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  /**
   *	~DOMConfiguration method
   *	- Destructor for DOM objects
   */ 
  JS_METHOD(_domconfiguration_destructor) {
    /* v8::TryCatch tc; */
    //DOMCONFIG;
    // SAVE_PTR(0,NULL);
    // X TRY( domconfig->~DOMConfiguration(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }
  
  /**
   *	DOMNode constructor:
   * 	- Adds "~DOMNode()" method to global GC
   */
  JS_METHOD(_domnode) {
    /* v8::TryCatch tc; */
    ASSERT_CONSTRUCTOR;
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMNode");
    DOMNode * node = NULL;
    if (args[0]->IsExternal()) {
      node = RECAST(args[0], DOMNode *);
    }
    else if (args[0]->IsObject()) {
      node = RECAST(args[0]->ToObject()->GetInternalField(0), DOMNode *);
    }
    if (node==NULL) {
      JS_RETURN_ERROR("[_node()] ERROR: \"node\" is a null pointer");
    }
    if (args.Length() > 1) {
      if (args[1]->IsBoolean()) {
	if (args[1]->ToBoolean()->BooleanValue()!=true) {
	  SAVE_PTR(0,node);
	  { args.GetReturnValue().Set(args.This()); return; };
	}
      }
    }
    xercesc_3_1::DOMNode::NodeType nodeType = node->getNodeType();
    v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)node) };
    if (nodeType==xercesc_3_1::DOMNode::ELEMENT_NODE) {
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::felement)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
    else if (nodeType==xercesc_3_1::DOMNode::DOCUMENT_TYPE_NODE) {
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdocumenttype)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
    else if (nodeType==xercesc_3_1::DOMNode::DOCUMENT_NODE) {
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdocument)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
    else if (nodeType==xercesc_3_1::DOMNode::DOCUMENT_FRAGMENT_NODE) {
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdocumentfragment)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
    else if (nodeType==xercesc_3_1::DOMNode::ATTRIBUTE_NODE) {
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fattribute)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
    else if (nodeType==xercesc_3_1::DOMNode::TEXT_NODE) {
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::ftext)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
    else if (nodeType==xercesc_3_1::DOMNode::COMMENT_NODE) {
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fcomment)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
    else if (nodeType==xercesc_3_1::DOMNode::CDATA_SECTION_NODE) {
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fcdatasection)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
    else {
      SAVE_PTR(0,node);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_nodegetaselement) {
	/* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodegetaselement()] ERROR: Too many input parameters");
    DOMNode * node = NULL;
    node = RECAST(args.This()->GetInternalField(0),DOMNode *);
    if (node==NULL) {
      JS_RETURN_ERROR("[_nodegetaselement()] ERROR: \"node\" is a null pointer");
    }
    else {
      const int fargc = 2;
      v8::Local<v8::Value> upConvert = v8::Boolean::New(JS_ISOLATE, true);
      v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)node), upConvert };
      v8::Handle<v8::Function> f =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction();
      v8::Handle<v8::Object> ret ( f->NewInstance(fargc, fargv) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_nodeserialize) {
    /* v8::TryCatch tc; */
    NODE;
    DOMDocument * doc = NULL;
    DOMImplementation * dom = NULL;
    DOMLSOutput * pOutput = NULL;
    DOMLSSerializer * pSerializer = NULL;
    bool cleanSer = true;
    bool cleanOut = true;
    if (args.Length()>2) {
      JS_RETURN_ERROR("[_nodeserialize()] ERROR: Too many input parameters");
    }
    SS encoding("UTF-8");
    if (args.Length()>0) {
      if (args[0]->IsString()) {
	encoding.flush() << *v8::String::Utf8Value(args[0]->ToString());
      }
      else if (args[0]->IsObject()) {
	std::string domtype( *USTR(args[0]->ToObject()->Get(JS_STR("_domtype_"))->ToString()) );
	if (domtype=="DOMLSSerializer") {
	  pSerializer = RECAST(args[0]->ToObject()->GetInternalField(0),DOMLSSerializer *);
	  cleanSer = false;
	}
	else if (domtype=="DOMLSOutput") {
	  pOutput = RECAST(args[0]->ToObject()->GetInternalField(0),DOMLSOutput *);
	  cleanOut = false;
	}
      }
    }
    if (args.Length()>1) {
      if (args[1]->IsObject()) {
	std::string domtype( *USTR(args[1]->ToObject()->Get(JS_STR("_domtype_"))->ToString()) );
	if (domtype=="DOMLSSerializer") {
	  pSerializer = RECAST(args[1]->ToObject()->GetInternalField(0),DOMLSSerializer *);
	  cleanSer = false;
	}
	else if (domtype=="DOMLSOutput") {
	  pOutput = RECAST(args[1]->ToObject()->GetInternalField(0),DOMLSOutput *);
	  cleanOut = false;
	}
      }
    }
    XLSTRY(
      MemBufFormatTarget memTarget;
      if (pOutput==NULL || pSerializer==NULL) {
	doc = node->getOwnerDocument();
	dom = doc->getImplementation();
      }
      if (pOutput==NULL) {
	pOutput = ((DOMImplementationLS *)dom)->createLSOutput();
	pOutput->setEncoding(X_STR(encoding));
      }
      if (pSerializer==NULL) {
	pSerializer = ((DOMImplementationLS *)dom)->createLSSerializer();
	pSerializer->setNewLine( XML_STR("\n") );
	DOMConfiguration * config ( pSerializer->getDomConfig() );
	config->setParameter(XMLUni::fgDOMWRTDiscardDefaultContent, true);
	config->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);
      }
      pOutput->setByteStream(&memTarget);

      pSerializer->write(node, pOutput);
//    const char * cstr = (const char *)memTarget.getRawBuffer();
      size_t len = strlen((char *)memTarget.getRawBuffer());
      char * cstr = new char[len];
      memcpy((void *)cstr,(const void *)memTarget.getRawBuffer(),len);
      v8::Handle<v8::String> ret(JS_STR(cstr));
      if (cleanSer==true) {
	pSerializer->release();
      }
      if (cleanOut==true) {
	pOutput->release();
      }
      delete cstr;
      { args.GetReturnValue().Set(ret); return; };
    );
  }

  JS_METHOD(_nodeserializeinner) {
    NODE;
    DOMDocument * doc = NULL;
    DOMImplementation * dom = NULL;
    DOMLSOutput * pOutput = NULL;
    DOMLSSerializer * pSerializer = NULL;
    bool cleanSer = true;
    bool cleanOut = true;
    if (args.Length()>2) {
      JS_RETURN_ERROR("[_nodeserializeinner()] ERROR: Too many input parameters");
    }
    SS encoding("UTF-8");
    if (args.Length()>0) {
      if (args[0]->IsString()) {
	encoding.flush() << *v8::String::Utf8Value(args[0]->ToString());
      }
      else if (args[0]->IsObject()) {
	std::string domtype( *USTR(args[0]->ToObject()->Get(JS_STR("_domtype_"))->ToString()) );
	if (domtype=="DOMLSSerializer") {
	  pSerializer = RECAST(args[0]->ToObject()->GetInternalField(0),DOMLSSerializer *);
	  cleanSer = false;
	}
	else if (domtype=="DOMLSOutput") {
	  pOutput = RECAST(args[0]->ToObject()->GetInternalField(0),DOMLSOutput *);
	  cleanOut = false;
	}
      }
    }
    if (args.Length()>1) {
      if (args[1]->IsObject()) {
	std::string domtype( *USTR(args[1]->ToObject()->Get(JS_STR("_domtype_"))->ToString()) );
	if (domtype=="DOMLSSerializer") {
	  pSerializer = RECAST(args[1]->ToObject()->GetInternalField(0),DOMLSSerializer *);
	  cleanSer = false;
	}
	else if (domtype=="DOMLSOutput") {
	  pOutput = RECAST(args[1]->ToObject()->GetInternalField(0),DOMLSOutput *);
	  cleanOut = false;
	}
      }
    }
    XLSTRY(
      MemBufFormatTarget memTarget;
      if (pOutput==NULL || pSerializer==NULL) {
	doc = node->getOwnerDocument();
	dom = doc->getImplementation();
      }
      if (pOutput==NULL) {
	pOutput = ((DOMImplementationLS *)dom)->createLSOutput();
	pOutput->setEncoding(X_STR(encoding));
      }
      if (pSerializer==NULL) {
	pSerializer = ((DOMImplementationLS *)dom)->createLSSerializer();
	pSerializer->setNewLine( XML_STR("\n") );
	DOMConfiguration * config ( pSerializer->getDomConfig() );
	config->setParameter(XMLUni::fgDOMWRTDiscardDefaultContent, true);
	config->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);
      }
      pOutput->setByteStream(&memTarget);
      DOMNodeList * frags = NULL;
      frags = node->getChildNodes();
      if (frags!=NULL) {
	XMLSize_t len = frags->getLength();
	for (XMLSize_t i=0;i<len;i++) {
	  DOMNode * item = NULL;
	  item = frags->item(i);
	  if (item!=NULL) {
	    pSerializer->write(item, pOutput);
	  }
        }
      }
      size_t clen = strlen((char *)memTarget.getRawBuffer());
      char * cstr = new char[clen];
      memcpy((void *)cstr,(const void *)memTarget.getRawBuffer(),clen);
      v8::Handle<v8::String> ret(JS_STR(cstr));
      if (cleanSer==true) {
	pSerializer->release();
      }
      if (cleanOut==true) {
	pOutput->release();
      }
      delete cstr;
      { args.GetReturnValue().Set(ret); return; };
    );
  }

  JS_METHOD(_nodegetnodename) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodegetnodename()] ERROR: Too many input parameters");
    NODE;
    XS name = NULL;
    XTRY( name = (XMLCh *)node->getNodeName(); );
    if (name==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(name);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_nodegetnodevalue) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodegetnodevalue()] ERROR: Too many input parameters");
    NODE;
    XS val = NULL;
    XTRY( val = (XMLCh *)node->getNodeValue(); );
    if (val==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(val);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_nodegetnodetype) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodegetnodetype()] ERROR: Too many input parameters");
    NODE;
    int ret = -1;
    XTRY( ret = (int)node->getNodeType(); );
    if (ret<0) {
      JS_RETURN_ERROR("[_nodegetnodetype()] ERROR: \"ret\" has an invalid value");
    }
    else {
      { args.GetReturnValue().Set(JS_INT(ret)); return; }
    }
  }

  JS_METHOD(_nodegetparentnode) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodegetparentnode()] ERROR: Too many input parameters");
    NODE;
    DOMNode * parent = NULL;
    XTRY( parent = node->getParentNode(); );
    v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)parent) };
    v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_nodegetchildnodes) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodegetchildnodes()] ERROR: Too many input parameters");
    NODE;
    DOMNodeList * nodelist = NULL;
    XTRY( nodelist = node->getChildNodes(); );
    if (nodelist==NULL) {
      JS_RETURN_ERROR("[_nodegetchildnodes()] ERROR: \"nodelist\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)nodelist) };
      v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnodelist)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_nodegetfirstchild) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodegetfirstchild()] ERROR: Too many input parameters");
    NODE;
    DOMNode * child = NULL;
    XTRY( child = node->getFirstChild(); );
    if (child==NULL) {
      JS_RETURN_ERROR("[_nodegetfirstchild()] ERROR: \"child\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)child) };
      v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_nodegetlastchild) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodegetlastchild()] ERROR: Too many input parameters");
    NODE;
    DOMNode * child = NULL;
    XTRY( child = node->getLastChild(); );
    if (child==NULL) {
      JS_RETURN_ERROR("[_nodegetlastchild()] ERROR: \"child\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)child) };
      v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_nodegetprevioussibling) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodegetprevioussibling()] ERROR: Too many input parameters");
    NODE;
    DOMNode * sib = NULL;
    XTRY( sib = node->getPreviousSibling(); );
    if (sib==NULL) {
      JS_RETURN_ERROR("[_nodegetprevioussibling()] ERROR: \"sib\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)sib) };
      v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_nodegetnextsibling) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodegetnextsibling()] ERROR: Too many input parameters");
    NODE;
    DOMNode * sib = NULL;
    XTRY( sib = node->getNextSibling(); );
    if (sib==NULL) {
      JS_RETURN_ERROR("[_nodegetnextsibling()] ERROR: \"sib\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)sib) };
      v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_nodegetattributes) {
    v8::TryCatch tc;
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodegetattributes()] ERROR: Too many input parameters");
    NODE;
    DOMNamedNodeMap * nodemap = NULL;
    XTRY( nodemap = node->getAttributes(); );
    if (nodemap==NULL) {
      JS_RETURN_ERROR("[_nodegetattributes()] ERROR: \"nodemap\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)nodemap) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnamednodemap)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_nodegetownerdocument) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodegetownerdocument()] ERROR: Too many input parameters");
    NODE;
    DOMDocument * doc = NULL;
    XTRY( doc = node->getOwnerDocument(); );
    if (doc==NULL) {
      JS_RETURN_ERROR("[_nodegetownerdocument()] ERROR: \"doc\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)doc) };
      v8::Handle<v8::Object> ret ( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdocument)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_nodegetownerimplementation) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodegetownerimplementation()] ERROR: Too many input parameters");
    NODE;
    DOMDocument * doc = NULL;
    XTRY( doc = node->getOwnerDocument(); );
    if (doc==NULL) {
      JS_RETURN_ERROR("[_nodegetownerimplementation()] ERROR: \"doc\" is a null pointer");
    }
    else {
      DOMImplementation * impl = NULL;
      XTRY( impl = doc->getImplementation(); );
      if (impl==NULL) {
	JS_RETURN_ERROR("[_nodegetownerimplementation()] ERROR: \"impl\" is a null pointer");
      }
      else {
	v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)impl) };
	v8::Handle<v8::Object> ret (v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdom)->GetFunction()->NewInstance(1, fargs) );
	{ args.GetReturnValue().Set(ret); return; };
      }
    }
  }

  JS_METHOD(_nodeclonenode) {
    /* v8::TryCatch tc; */
    if (args.Length()>1)
      JS_RETURN_ERROR("[_nodeclonenode()] ERROR: Too many input parameters");
    NODE;
    v8::Local<v8::Boolean> inDepth ( args[0]->ToBoolean() );
    DOMNode * clone = NULL;
    XTRY( clone = node->cloneNode(*inDepth); );
    if (clone==NULL) {
      JS_RETURN_ERROR("[_nodeclonenode()] ERROR: \"clone\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)clone) };
      v8::Handle<v8::Object> ret (v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_nodeinsertbefore) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_nodeinsertbefore()] ERROR: Incorrect number of input parameters");
    NODE;
    DOMNode * newChild = RECAST(args[0],DOMNode *);
    DOMNode * refChild = RECAST(args[1],DOMNode *);
    DOMNode * retChild = NULL;
    XTRY( retChild = node->insertBefore(newChild,refChild); );
    if (retChild==NULL) {
      JS_RETURN_ERROR("[_nodeinsertbefore()] ERROR: \"retChild\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)retChild) };
      v8::Handle<v8::Object> ret (v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_nodereplacechild) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_nodereplacechild()] ERROR: Incorrect number of input parameters");
    v8::Handle<v8::Object> ret;
    {
      NODE;
      DOMNode * newChild = RECAST(args[0],DOMNode *);
      DOMNode * oldChild = RECAST(args[1],DOMNode *);
      DOMNode * retChild = NULL;
      XTRY( retChild = node->replaceChild(newChild,oldChild); );
      if (retChild==NULL) {
	JS_RETURN_ERROR("[_nodereplacechild()] ERROR: \"retChild\" is a null pointer");
      }
      else {
	v8::Local<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)retChild) };
	ret =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs);
      }
    }
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_noderemovechild) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_noderemovechild()] ERROR: Incorrect number of input parameters");
    NODE;
    DOMNode * oldChild = RECAST(args[0],DOMNode *);
    DOMNode * retChild = NULL;
    XTRY( retChild = node->removeChild(oldChild); );
    if (retChild==NULL) {
      JS_RETURN_ERROR("[_noderemovechild()] ERROR: \"retChild\" is a null pointer");
    }
    else {
      v8::Local<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)retChild) };
      v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_nodeappendchild) {
    /* v8::TryCatch tc; */
    if (args.Length()<1)
      JS_RETURN_ERROR("[_nodeappendchild()] ERROR: Missing input parameter")
    else if (args.Length()>1)
      JS_RETURN_ERROR("[_nodeappendchild()] ERROR: Too many input parameters")
    NODE;
    DOMNode * newChild = NULL;
    if (args[0]->IsExternal()) {
      newChild = RECAST(args[0],DOMNode *);
    }
    else if (args[0]->IsObject()) {
      newChild = RECAST(args[0]->ToObject()->GetInternalField(0),DOMNode *);
    }
    if (newChild==NULL) {
      JS_RETURN_ERROR("[_nodeappendchild()] ERROR: \"newChild\" is a null pointer");
    }
    else {
      DOMNode * res = NULL;
      XTRY( res = node->appendChild(newChild); );
      if (res==NULL) {
	JS_RETURN_ERROR("[_nodeappendchild()] ERROR: \"res\" is a null pointer");
      }
      else {
	v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)res) };
	v8::Handle<v8::Object> ret (v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
	{ args.GetReturnValue().Set(ret); return; };
      }
    }
  }

  JS_METHOD(_nodehaschildnodes) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodehaschildnodes()] ERROR: Too many input parameters");
    NODE;
    bool ret = false;
    XTRY( ret = node->hasChildNodes(); );
    { args.GetReturnValue().Set(JS_BOOL(ret)); return; }
  }

  JS_METHOD(_nodesetnodevalue) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_nodesetnodevalue()] ERROR: Incorrect number of input parameters");
    NODE;
    SS val( *v8::String::Utf8Value(args[0]->ToString()) );
    XTRY( node->setNodeValue(X_STR(val)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_nodenormalize) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodenormalize()] ERROR: Too many input parameters");
    NODE;
    XTRY( node->normalize(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_nodeissupported) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_nodeissupported()] ERROR: Incorrect number of input parameters");
    NODE;
    bool ret = false;
    SS feature ("");
    SS version ("");
    feature << *v8::String::Utf8Value(args[0]);
    version << *v8::String::Utf8Value(args[1]);
    XTRY( ret = node->isSupported(X_STR(feature),X_STR(version)); );
    { args.GetReturnValue().Set(JS_BOOL(ret)); return; }
  }

  JS_METHOD(_nodegetnamespaceuri) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodegetnamespaceuri()] ERROR: Too many input parameters");
    NODE;
    v8::Handle<v8::String> ret;
    XTRY( ret = JS_STR((char *) node->getNamespaceURI()); );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_nodegetprefix) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodegetprefix()] ERROR: Too many input parameters");
    NODE;
    v8::Handle<v8::String> ret;
    XTRY( ret = JS_STR((char *)node->getPrefix()); );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_nodegetlocalname) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodegetlocalname()] ERROR: Too many input parameters");
    NODE;
    v8::Handle<v8::String> ret;
    XTRY( ret = JS_STR((char *)node->getLocalName()); );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_nodesetprefix) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_nodesetprefix()] ERROR: Incorrect number of input parameters")
    else {
      NODE;
      SS prefix( *v8::String::Utf8Value(args[0]->ToString()) );
      XTRY( node->setPrefix(X_STR(prefix)); );
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_nodehasattributes) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodehasattributes()] ERROR: Too many input parameters");
    NODE;
    bool ret = false;
    XTRY( ret = node->hasAttributes(); );
    { args.GetReturnValue().Set(JS_BOOL(ret)); return; }
  }

  JS_METHOD(_nodeissamenode) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_nodeissamenode()] ERROR: Incorrect number of input parameters");
    NODE;
    DOMNode * other = NULL;
    if (args[0]->IsExternal()) {
      other = RECAST(args[0],DOMNode *);
    }
    else if(args[0]->IsObject())
      other = RECAST(args[0]->ToObject()->GetInternalField(0),DOMNode *);
    if (other==NULL)
      JS_RETURN_ERROR("[_nodeissamenode()] ERROR: \"other\" is a null pointer")
    else {
      bool ret = false;
      XTRY( ret = node->isSameNode(other); );
      { args.GetReturnValue().Set(JS_BOOL(ret)); return; }
    }
  }

  JS_METHOD(_nodeisequalnode) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_nodeisequalnode()] ERROR: Incorrect number of input parameters");
    NODE;
    DOMNode * other = NULL;
    if (args[0]->IsExternal()) {
      other = RECAST(args[0],DOMNode *);
    }
    else if(args[0]->IsObject())
      other = RECAST(args[0]->ToObject()->GetInternalField(0),DOMNode *);
    if (other==NULL)
      JS_RETURN_ERROR("[_nodeisequalnode()] ERROR: \"other\" is a null pointer")
    else {
      bool ret = false;
      XTRY( ret = node->isEqualNode(other); );
      { args.GetReturnValue().Set(JS_BOOL(ret)); return; }
    }
  }

  JS_METHOD(_nodesetuserdata) {
    /* v8::TryCatch tc; */
    if (args.Length()>3 || args.Length()<2)
      JS_RETURN_ERROR("[_nodesetuserdata()] ERROR: Incorrect number of input parameters");
    NODE;
    SS key("");
    key << *v8::String::Utf8Value( args[0] );
    void * data = NULL;
    if (args[1]->IsExternal()) {
      data = RECAST(args[1],void *);
    }
    DOMUserDataHandler * handler = NULL;
    if (args[2]->IsExternal()) {
      handler = RECAST(args[2],DOMUserDataHandler *);
    }
    else if (args[2]->IsObject()) {
      v8::Local<v8::Object> tobj ( args[2]->ToObject() );
      if (tobj->InternalFieldCount()>0) {
	handler = RECAST(tobj->GetInternalField(0),DOMUserDataHandler *);
      }
    }
    XTRY( node->setUserData(X_STR(key),data,handler); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_nodegetuserdata) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_nodegetuserdata()] ERROR: Incorrect number of input parameters");
    NODE;
    SS key("");
    key << *v8::String::Utf8Value( args[0] );
    void * obj_ptr = NULL;
    XTRY( obj_ptr = node->getUserData(X_STR(key)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_nodegetbaseuri) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodegetbaseuri()] ERROR: Too many input parameters");
    NODE;
    XS uri = NULL;
    XTRY( uri = (XMLCh *)node->getBaseURI(); );
    if (uri==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(uri);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_nodecomparedocumentposition) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_nodegetbaseuri()] ERROR: Incorrect number of input parameters");
    NODE;
    DOMNode * other = NULL;
    if (args[0]->IsExternal()) {
      other = RECAST(args[0],DOMNode *);
    }
    else if (args[0]->IsObject()) {
      v8::Local<v8::Object> tobj ( args[0]->ToObject() );
      if (tobj->InternalFieldCount()>0) {
	other = RECAST(tobj->GetInternalField(0),DOMNode *);
      }
    }
    if (other==NULL)
      JS_RETURN_ERROR("[_nodecomparedocumentposition()] ERROR: \"other\" is a null pointer")
    else {
      short ret = 0;
      XTRY( ret = node->compareDocumentPosition(other); );
      { args.GetReturnValue().Set(JS_INT(ret)); return; }
    }
  }

  JS_METHOD(_nodegettextcontent) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_nodegettextcontent()] ERROR: Too many input parameters");
    NODE;
    XS textcontent = NULL;
    XTRY( textcontent = (XMLCh *)node->getTextContent(); );
    if (textcontent==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(textcontent);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_nodesettextcontent) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_nodesettextcontent()] ERROR: Incorrect number of input parameters");
    NODE;
    SS content("");
    content << *v8::String::Utf8Value(args[0]->ToString());
    XTRY( node->setTextContent(X_STR(content)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_nodelookupprefix) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_nodelookupprefix()] ERROR: Incorrect number of input parameters");
    NODE;
    SS prefix("");
    prefix << *v8::String::Utf8Value(args[0]->ToString());
    XS res = NULL;
    XTRY( res = (XMLCh *)node->lookupPrefix(X_STR(prefix)); );
    if (res==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(res);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_nodeisdefaultnamespace) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_nodeisdefaultnamespace()] ERROR: Incorrect number of input parameters");
    NODE;
    SS ns(*v8::String::Utf8Value(args[0]->ToString()));
    bool ret = false;
    XTRY( node->isDefaultNamespace(X_STR(ns)); );
    { args.GetReturnValue().Set(JS_BOOL(ret)); return; }
  }

  JS_METHOD(_nodelookupnamespaceuri) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_nodelookupnamespaceuri()] ERROR: Incorrect number of input parameters");
    NODE;
    SS ns(*v8::String::Utf8Value(args[0]->ToString()));
    XS res = NULL;
    XTRY( res = (XMLCh *)node->lookupNamespaceURI(X_STR(ns)); );
    if (res==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(res);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_nodegetfeature) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_nodegetfeature()] ERROR: Incorrect number of input parameters");
    NODE;
    SS feature ("");
    SS version ("");
    feature << *v8::String::Utf8Value(args[0]);
    version << *v8::String::Utf8Value(args[1]);
    void * res = NULL;
    XTRY( res = (void *)node->getFeature(X_STR(feature),X_STR(version)); );
    v8::Handle<v8::Value> ret ( v8::External::New(JS_ISOLATE, (void *)res) );
    { args.GetReturnValue().Set(ret); return; };
  }
  
    /**
     *	~Node method
     *	- Destructor for Node objects
     */
    JS_METHOD(_domnode_destructor) {
      /* v8::TryCatch tc; */
      //NODE;
      //if (node!=NULL) {
	//SAVE_PTR(0,NULL);
        //XTRY( node->release(); );
	//XTRY( node->~DOMNode(); );
	//{ args.GetReturnValue().Set(args.This()); return; };
      //}
      { args.GetReturnValue().Set(args.This()); return; };
    }
  
  /**
   *	Text constructor:
   * 	- Adds "Text()" method to global GC
   */
  JS_METHOD(_text) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1 && args.Length()!=1)
      JS_RETURN_ERROR("[_text()] ERROR: Incorrect number of input parameters");
    ASSERT_CONSTRUCTOR;
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMText");
    DOMText * text = NULL;
    if (args[0]->IsExternal()) {
      text = RECAST(args[0],DOMText *);
    }
    else if (args[0]->IsObject()) {
      v8::Handle<v8::Object> tobj( args[0]->ToObject() );
      text = RECAST(tobj->GetInternalField(0),DOMText *);
    }
    if (text==NULL)
      JS_RETURN_ERROR("[_text()] ERROR: \"text\" is a null pointer")
    else {
      SAVE_PTR(0,text);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_textsplittext) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_textsplittext] ERROR: Incorrect number of input parameters");
    TEXT;
    XMLSize_t offset = (XMLSize_t)(args[0]->ToInteger()->Uint32Value());
    DOMText * splitText = NULL;
    XTRY( splitText = text->splitText(offset); );
    v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)splitText) };
    v8::Handle<v8::Object> ret ( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::ftext)->GetFunction()->NewInstance(1, fargs) );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_textgetiselementcontentwhitespace) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_textgetiselementcontentwhitespace] ERROR: Too many input parameters");
    TEXT;
    bool ret = false;
    XTRY( ret = text->getIsElementContentWhitespace(); );
    { args.GetReturnValue().Set(JS_BOOL(ret)); return; }
  }

  JS_METHOD(_textgetwholetext) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_textgetwholetext] ERROR: Too many input parameters");
    TEXT;
    XS wholeText = NULL;
    XTRY( wholeText = (XMLCh *)text->getWholeText(); );
    if (wholeText==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(wholeText);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_textreplacewholetext) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_textreplacewholetext] ERROR: Incorrect number of input parameters");
    TEXT;
    SS content( *v8::String::Utf8Value(args[0]->ToString()) );
    DOMText * newText = NULL;
    XTRY( newText = text->replaceWholeText(X_STR(content)); );
    if (newText==NULL)
      JS_RETURN_ERROR("[_textreplacewholetext] ERROR: \"newText\" is a null pointer")
    else
      SAVE_PTR(0,newText);
    XTRY( text->~DOMText(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_textisignorablewhitespace) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_textisignorablewhitespace] ERROR: Too many input parameters");
    TEXT;
    bool ret = false;
    XTRY( ret = text->isIgnorableWhitespace(); );
    { args.GetReturnValue().Set(JS_BOOL(ret)); return; }
  }

  /**
   *	~Text method
   *	- Destructor for Text objects
   */ 
  JS_METHOD(_text_destructor) {
    /* v8::TryCatch tc; */
    //TEXT;
    //XTRY( text->~DOMText(); );
    // SAVE_PTR(0,NULL);
    { args.GetReturnValue().Set(args.This()); return; };
  }


  /**
   *	DocumentType constructor:
   * 	- Adds "DocumentType()" method to global GC
   */
  JS_METHOD(_documenttype) {
    /* v8::TryCatch tc; */
    ASSERT_CONSTRUCTOR;
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMDocumentType");
    DOMDocumentType * docType = NULL;
    if (args[0]->IsExternal()) {
      docType = RECAST(args[0],DOMDocumentType *);
    }
    else if (args[0]->IsObject()) {
      docType = RECAST(args[0]->ToObject()->GetInternalField(0),DOMDocumentType *);
    }
    if (docType==NULL) {
      JS_RETURN_ERROR("[_documenttype()] ERROR: \"docType\" is a null pointer");
    }
    else {
      SAVE_PTR(0,docType);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_dtgetname) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_dtgetname()] ERROR: Too many input parameters");
    DOCTYPE;
    XS name = NULL;
    XTRY( name = (XMLCh *)docType->getName(); );
    if (name==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(name);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_dtgetentities) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_dtgetentities()] ERROR: Too many input parameters");
    DOCTYPE;
    DOMNamedNodeMap * nodemap = NULL;
    XTRY( nodemap = docType->getEntities(); );
    v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (DOMNamedNodeMap *)(nodemap)) };
    v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnamednodemap)->GetFunction()->NewInstance(1, fargs) );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_dtgetnotations) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_dtgetnotations()] ERROR: Too many input parameters");
    DOCTYPE;
    DOMNamedNodeMap * nodemap = NULL;
    XTRY( nodemap = docType->getNotations(); );
    v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (DOMNamedNodeMap *)(nodemap)) };
    v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnamednodemap)->GetFunction()->NewInstance(1, fargs) );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_dtgetpublicid) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_dtgetpublicid()] ERROR: Too many input parameters");
    DOCTYPE;
    XS publicId = NULL;
    XTRY( publicId = (XMLCh *)docType->getPublicId(); );
    if (publicId==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(publicId);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_dtgetsystemid) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_dtgetsystemid()] ERROR: Too many input parameters");
    DOCTYPE;
    XS systemId = NULL;
    XTRY( systemId = (XMLCh *)docType->getSystemId(); );
    if (systemId==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(systemId);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_dtgetinternalsubset) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_dtgetinternalsubset()] ERROR: Too many input parameters");
    DOCTYPE;
    XS subset = NULL;
    XTRY( subset = (XMLCh *)docType->getInternalSubset(); );
    if (subset==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(subset);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  /**
   *	~DocumentType method
   *	- Destructor for DocumentType objects
   */ 
  JS_METHOD(_documenttype_destructor) {
    /* v8::TryCatch tc; */
    //DOCTYPE;
    // SAVE_PTR(0,NULL);
    //XTRY( docType->release(); );
    //XTRY( docType->~DOMDocumentType(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  /**
   *	DocumentFragment constructor:
   * 	- Adds "DocumentFragment()" method to global GC
   */
  JS_METHOD(_documentfragment) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_documentfragment()] ERROR: Incorrect number of input parameters");
    ASSERT_CONSTRUCTOR;
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMDocumentFragment");
    DOMDocumentFragment * frag = NULL;
    if (args[0]->IsExternal()) {
      frag = RECAST(args[0],DOMDocumentFragment *);
    }
    else if (args[0]->IsObject()) {
      v8::Handle<v8::Object> tobj( args[0]->ToObject() );
      frag = RECAST(tobj->GetInternalField(0),DOMDocumentFragment *);
    }
    if (frag==NULL)
      JS_RETURN_ERROR("[_documentfragment()] ERROR: \"frag\" is a null pointer")
    else {
      SAVE_PTR(0,frag);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  /**
   *	~DocumentType method
   *	- Destructor for DocumentType objects
   */ 
  JS_METHOD(_documentfragment_destructor) {
    /* v8::TryCatch tc; */
    //DOCFRAG;
    //XTRY( frag->~DOMDocumentFragment(); );
    // SAVE_PTR(0,NULL)
    { args.GetReturnValue().Set(args.This()); return; };
  }

  /**
   *	Document constructor:
   * 	- Adds "Document()" method to global GC
   */
  JS_METHOD(_document) {
    /* v8::TryCatch tc; */
    ASSERT_CONSTRUCTOR;
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_document()] ERROR: Incorrect number of input parameters");
    }
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMDocument");
    DOMDocument * doc = NULL;
    if (args[0]->IsExternal()) {
      doc = RECAST(args[0],DOMDocument *);
    }
    else if (args[0]->IsObject()) {
      doc = RECAST(args[0]->ToObject()->GetInternalField(0),DOMDocument *);
    }
    if (doc==NULL) {
      JS_RETURN_ERROR("[_document()] ERROR: \"doc\" is a null pointer");
    }
    else {
      SAVE_PTR(0,doc);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_documentcreatelsoutput) {
    DOC;
    SS encoding("UTF-8");
    if (args.Length()>0) {
      if (args[0]->IsString()) {
	encoding.flush() << *v8::String::Utf8Value(args[0]->ToString());
      }
      else if (args[0]->IsObject()) {
	if (args[0]->ToObject()->Has(JS_STR("encoding"))) {
	  encoding.flush() << *v8::String::Utf8Value( args[0]->ToObject()->Get(JS_STR("encoding"))->ToString() );
	}
      }
    }
    DOMLSOutput * target = NULL;
    DOMImplementation * dom = NULL;
    XTRY(
      dom = doc->getImplementation();
      target = ((DOMImplementationLS *)dom)->createLSOutput();
      target->setEncoding(X_STR(encoding));
    );
    if (target==NULL) {
      JS_RETURN_ERROR("[_documentcreatelsoutput()] ERROR: \"target\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)target) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::foutput)->GetFunction()->NewInstance(fargc, fargv) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_documentcreatelsserializer) {
    DOC;
    DOMLSSerializer * ser = NULL;
    DOMImplementation * dom = NULL;
    bool formatprettyprint = true;
    bool discarddefaultcontent = true;
    if (args.Length()>0) {
      if (args[0]->IsBoolean()) {
	formatprettyprint = args[0]->ToBoolean()->BooleanValue();
      }
      else if (args[0]->IsObject()) {
	if (args[0]->ToObject()->Has(JS_STR("prettyPrint"))) {
	  formatprettyprint = args[0]->ToObject()->Get(JS_STR("prettyPrint"))->ToBoolean()->BooleanValue();
	}
	if (args[0]->ToObject()->Has(JS_STR("discardDefaultContent"))) {
	  discarddefaultcontent = args[0]->ToObject()->Get(JS_STR("discardDefaultContent"))->ToBoolean()->BooleanValue();
	}
      }
      if (args.Length()>1) {
	if (args[1]->IsBoolean()) {
	  discarddefaultcontent = args[1]->ToBoolean()->BooleanValue();
	}
      }
    }
    XTRY(
      dom = doc->getImplementation();
      ser = ((DOMImplementationLS *)dom)->createLSSerializer();
      DOMConfiguration * config ( ser->getDomConfig() );
      config->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, formatprettyprint);
      config->setParameter(XMLUni::fgDOMWRTDiscardDefaultContent, discarddefaultcontent);
    );
    if (ser==NULL) {
      JS_RETURN_ERROR("[_documentcreatelsserializer()] ERROR: \"ser\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)ser) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fserializer)->GetFunction()->NewInstance(fargc, fargv) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_documentcreatenode) {
    /* v8::TryCatch tc; */
    // DOC;
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_documentcreateelement) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_documentcreateelement()] ERROR: Incorrect number of input parameters");
    DOC;
    DOMElement * el = NULL;
    XTRY( el = doc->createElement(ARGSTR(0)); );
    if (el==NULL) {
      JS_RETURN_ERROR("[_documentcreateelement()] ERROR: \"el\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)(el)) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::felement)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_documentcreatedocumentfragment) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_documentcreatedocumentfragment()] ERROR: Too many input parameters");
    DOC;
    DOMDocumentFragment * frag = NULL;
    XTRY( frag = doc->createDocumentFragment(); );
    v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)(frag)) };
    v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdocumentfragment)->GetFunction()->NewInstance(1, fargs) );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_documentcreatetextnode) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_documentcreatetextnode()] ERROR: Incorrect number of input parameters");
    DOC;
    DOMText * text = NULL;
    XTRY( text = doc->createTextNode(ARGSTR(0)); );
    v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)(text)) };
    v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::ftext)->GetFunction()->NewInstance(1, fargs) );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_documentcreatecomment) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_documentcreatecomment()] ERROR: Incorrect number of input parameters");
    DOC;
    DOMComment * comment = NULL;
    XTRY( comment = doc->createComment(ARGSTR(0)); );
    v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)(comment)) };
    v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fcomment)->GetFunction()->NewInstance(1, fargs) );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_documentcreatecdatasection) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_documentcreatecdatasection()] ERROR: Incorrect number of input parameters");
    DOC;
    DOMCDATASection * cdata = NULL;
    XTRY( cdata = doc->createCDATASection(ARGSTR(0)); );
    v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)(cdata)) };
    v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fcdatasection)->GetFunction()->NewInstance(1, fargs) );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_documentcreateprocessinginstruction) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_documentcreateprocessinginstruction()] ERROR: Incorrect number of input parameters");
    DOC;
    DOMProcessingInstruction * procinst = NULL;
    XTRY( procinst = doc->createProcessingInstruction(ARGSTR(0),ARGSTR(1)); );
    if (procinst==NULL) {
      JS_RETURN_ERROR("[_documentcreateprocessinginstruction()] ERROR: \"procinst\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (DOMProcessingInstruction *)procinst) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fprocessinginstruction)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_documentcreateattribute) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1 && args.Length()!=2)
      JS_RETURN_ERROR("[_documentcreateattribute()] ERROR: Incorrect number of input parameters");
    DOC;
    SS name(*v8::String::Utf8Value(args[0]->ToString()));
    DOMAttr * attr = NULL;
    XTRY( attr = doc->createAttribute(ARGSTR(0)); );
    if (attr==NULL) {
      JS_RETURN_ERROR("[_documentcreateattribute()] ERROR: \"attr\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (DOMAttr *)attr) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fattribute)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_documentcreateentityreference) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_documentcreateentityreference()] ERROR: Incorrect number of input parameters");
    DOC;
    SS name(*v8::String::Utf8Value(args[0]->ToString()));
    DOMEntityReference * entityref = NULL;
    XTRY( entityref = doc->createEntityReference(X_STR(name)); );
    if (entityref==NULL) {
      JS_RETURN_ERROR("[_documentcreateentityref()] ERROR: \"entityref\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)(entityref)) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fentityreference)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_documentcreateelementns) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_documentcreateelementns()] ERROR: Incorrect number of input parameters");
    DOC;
    DOMElement * el = NULL;
    XTRY( el = doc->createElementNS(ARGSTR(0),ARGSTR(1)); );
    if (el==NULL) {
      JS_RETURN_ERROR("[_documentcreateelementns()] ERROR: \"el\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)el) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::felement)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_documentcreateattributens) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_documentcreateattributens()] ERROR: Incorrect number of input parameters");
    DOC;
    DOMAttr * attr = NULL;
    XTRY( attr = doc->createAttributeNS(ARGSTR(0),ARGSTR(1)); );
    if (attr==NULL) {
      JS_RETURN_ERROR("[_documentcreateattributens()] ERROR: \"attr\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)(attr)) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fattribute)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_documentgetdoctype) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_documentgetdoctype()] ERROR: Too many input parameters");
    DOC;
    DOMDocumentType * docType = NULL;
    XTRY( docType = doc->getDoctype(); );
    if (docType==NULL) {
      JS_RETURN_ERROR("[_documentgetdoctype()] ERROR: \"docType\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)(docType)) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdocumenttype)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_documentgetimplementation) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_documentgetimplementation()] ERROR: Too many input parameters");
    DOC;
    DOMImplementation * dom = NULL;
    XTRY( dom = doc->getImplementation(); );
    if (dom==NULL) {
      JS_RETURN_ERROR("[_documentgetimplementation()] ERROR: \"dom\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)(dom)) };
      v8::Handle<v8::Function> impl( v8::Handle<v8::Function>::Cast(JS_GLOBAL->Get(JS_STR("DOMImplementation"))) );
      v8::Handle<v8::Object> ret( impl->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_documentgetdocumentelement) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_documentgetdocumentelement()] ERROR: Too many input parameters");
    DOC;
    DOMElement * el = NULL;
    XTRY( el = doc->getDocumentElement(); );
    if (el==NULL) {
      JS_RETURN_ERROR("[_documentgetodocumentelement()] ERROR: \"el\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)el) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::felement)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_documentgetelementsbytagname) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_documentgetelementsbytagname()] ERROR: Too many input parameters");
    DOC;
    DOMNodeList * nodelist = NULL;
    XTRY( nodelist = doc->getElementsByTagName(ARGSTR(0)); );
    if (nodelist==NULL) {
      JS_RETURN_ERROR("[_documentgetelementsbytagname()] ERROR: \"nodelist\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)nodelist) };
      v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnodelist)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_documentimportnode) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2 && args.Length()!=1)
      JS_RETURN_ERROR("[_documentgetdoctype()] ERROR: Incorrect number of input parameters");
    DOC;
    bool deep = false;
    if (args.Length()>1)
      deep = args[1]->ToBoolean()->BooleanValue();
    DOMNode * importedNode = NULL;
    if (args[0]->IsExternal()) {
      importedNode = RECAST(args[0],DOMNode *);
    }
    else if (args[0]->IsObject()) {
      v8::Local<v8::Object> tobj( args[0]->ToObject() );
      importedNode = RECAST(tobj->GetInternalField(0),DOMNode *);
    }
    DOMNode * node = NULL;
    XTRY( node = doc->importNode(importedNode, deep); );
    if (node==NULL)
      JS_RETURN_ERROR("[_documentimportnode()] ERROR: \"node\" is a null pointer");
    v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)node) };
    v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_documentgetelementsbytagnamens) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_documentgetelementsbytagnamens()] ERROR: Incorrect number of input parameters");
    DOC;
    SS namespaceURI(*v8::String::Utf8Value(args[0]->ToString()));
    SS localName(*v8::String::Utf8Value(args[1]->ToString()));
    DOMNodeList * nodelist = NULL;
    XTRY( nodelist = doc->getElementsByTagNameNS(X_STR(namespaceURI),X_STR(localName)); );
    v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)nodelist) };
    v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnodelist)->GetFunction()->NewInstance(1, fargs) );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_documentgetelementbyid) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_documentgetelementbyid()] ERROR: Incorrect number of input parameters");
    DOC;
    SS elementId(*v8::String::Utf8Value(args[0]->ToString()));
    DOMElement * el = NULL;
    XTRY( el = doc->getElementById(X_STR(elementId)); );
    if (el==NULL)
      JS_RETURN_ERROR("[_documentgetelementbyid()] ERROR: \"el\" is a null pointer");
    v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)(el)) };
    v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::felement)->GetFunction()->NewInstance(1, fargs) );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_documentgetinputencoding) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_documentgetinputencoding()] ERROR: Too many input parameters");
    DOC;
    XS encoding = NULL;
    XTRY( encoding = (XMLCh *)doc->getInputEncoding(); );
    if (encoding==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(encoding);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_documentgetxmlencoding) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_documentgetxmlencoding()] ERROR: Too many input parameters");
    DOC;
    XS encoding = NULL;
    XTRY( encoding = (XMLCh *)doc->getXmlEncoding(); );
    if (encoding==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(encoding);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_documentgetxmlstandalone) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_documentgetxmlstandalone()] ERROR: Too many input parameters");
    DOC;
    bool ret = false;
    XTRY( ret = doc->getXmlStandalone(); );
    { args.GetReturnValue().Set(JS_BOOL(ret)); return; }
  }

  JS_METHOD(_documentsetxmlstandalone) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_documentsetxmlstandalone()] ERROR: Incorrect number of input parameters");
    DOC;
    bool standalone = args[0]->ToBoolean()->BooleanValue();
    XTRY( doc->setXmlStandalone(standalone); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_documentgetxmlversion) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_documentgetxmlversion()] ERROR: Too many input parameters");
    DOC;
    XS version = NULL;
    XTRY( version = (XMLCh *)doc->getXmlVersion(); );
    if (version==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(version);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_documentsetxmlversion) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_documentsetxmlstandalone()] ERROR: Incorrect number of input parameters");
    DOC;
    SS version(*v8::String::Utf8Value(args[0]->ToString()));
    XTRY( doc->setXmlVersion(X_STR(version)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_documentgetdocumenturi) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_documentgetdocumenturi()] ERROR: Too many input parameters");
    DOC;
    XS uri = NULL;
    XTRY( uri = (XMLCh *)doc->getDocumentURI(); );
    if (uri==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(uri);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_documentsetdocumenturi) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_documentsetxmlstandalone()] ERROR: Incorrect number of input parameters");
    DOC;
    SS uri(*v8::String::Utf8Value(args[0]->ToString()));
    XTRY( doc->setDocumentURI(X_STR(uri)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_documentgetstricterrorchecking) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_documentgetxmlstandalone()] ERROR: Too many input parameters");
    DOC;
    bool ret = false;
    XTRY( ret = doc->getStrictErrorChecking(); );
    { args.GetReturnValue().Set(JS_BOOL(ret)); return; }
  }

  JS_METHOD(_documentsetstricterrorchecking) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_documentsetxmlstandalone()] ERROR: Incorrect number of input parameters");
    DOC;
    bool strict = args[0]->ToBoolean()->BooleanValue();
    XTRY( doc->setStrictErrorChecking(strict); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_documentrenamenode) {
    /* v8::TryCatch tc; */
    if (args.Length()!=3)
      JS_RETURN_ERROR("[_documentrenamenode()] ERROR: Incorrect number of input parameters");
    DOC;
    SS namespaceURI(*v8::String::Utf8Value(args[1]->ToString()));
    SS qualifiedName(*v8::String::Utf8Value(args[2]->ToString()));
    DOMNode * newNode = NULL;
    DOMNode * n = NULL;
    if (args[0]->IsExternal()) {
      n = RECAST(args[0],DOMNode *);
    }
    else if (args[0]->IsObject()) {
      v8::Local<v8::Object> tobj( args[0]->ToObject() );
      n = RECAST(tobj->GetInternalField(0),DOMNode *);
    }
    XTRY( newNode = doc->renameNode(n, X_STR(namespaceURI), X_STR(qualifiedName)); );
    if (newNode==NULL)
      JS_RETURN_ERROR("[_documentrenamenode()] ERROR: \"newNode\" is a null pointer")
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)newNode) };
      v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_documentadoptnode) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_documentadoptnode()] ERROR: Incorrect number of input parameters");
    DOC;
    DOMNode * source = NULL;
    if (args[0]->IsExternal()) {
      source = RECAST(args[0],DOMNode *);
    }
    else if (args[0]->IsObject()) {
      v8::Local<v8::Object> tobj( args[0]->ToObject() );
      source = RECAST(tobj->GetInternalField(0),DOMNode *);
    }
    DOMNode * node = NULL;
    XTRY( node = doc->adoptNode(source); );
    if (node==NULL)
      JS_RETURN_ERROR("[_documentadoptnode()] ERROR: \"node\" is a null pointer");
    v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)node) };
    v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_documentnormalizedocument) {
    /* v8::TryCatch tc; */
    DOC;
    XTRY( doc->normalizeDocument(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_documentgetdomconfig) {
    /* v8::TryCatch tc; */
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_documentgetdomconfig()] ERROR: Too many input parameters");
    }
    DOC;
    DOMConfiguration * domconfig = NULL;
    XTRY( domconfig = doc->getDOMConfig(); );
    if (domconfig==NULL) {
      JS_RETURN_ERROR("[_documentgetdomconfig()] ERROR: \"domconfig\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)domconfig) };
      v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomconfiguration)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_documentcreateentity) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_documentcreateentity()] ERROR: Incorrect number of input parameters");
    DOC;
    SS name(*v8::String::Utf8Value(args[0]->ToString()));
    DOMEntity * entity = NULL;
    XTRY( entity = doc->createEntity(X_STR(name)); );
    if (entity==NULL)
      JS_RETURN_ERROR("[_documentcreateentity()] ERROR: \"entity\" is a null pointer");
    v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)(entity)) };
    v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fentity)->GetFunction()->NewInstance(1, fargs) );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_documentcreatenotation) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_documentcreatenotation()] ERROR: Incorrect number of input parameters");
    DOC;
    SS name(*v8::String::Utf8Value(args[0]->ToString()));
    DOMNotation * notation = NULL;
    XTRY( notation = doc->createNotation(X_STR(name)); );
    v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)(notation)) };
    v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnotation)->GetFunction()->NewInstance(1, fargs) );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_documentcreatedocumenttype) {
    /* v8::TryCatch tc; */
    if (args.Length()!=3 && args.Length()!=1)
      JS_RETURN_ERROR("[_documentcreatedocumenttype()] ERROR: Incorrect number of input parameters");
    DOC;
    DOMDocumentType * docType = NULL;
    SS qName(*v8::String::Utf8Value(args[0]->ToString()));
    if (args.Length()==1) {
      XTRY( docType = doc->createDocumentType(X_STR(qName)); );
    }
    else {
      SS publicId(*v8::String::Utf8Value(args[1]->ToString()));
      SS systemId(*v8::String::Utf8Value(args[2]->ToString()));
      XTRY( docType = doc->createDocumentType(X_STR(qName),X_STR(publicId),X_STR(systemId)); );
    }
    if (docType==NULL)
      JS_RETURN_ERROR("[_documentcreatedocumenttype()] ERROR: \"docType\" is a null pointer");
    v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)docType) };
    v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdocumenttype)->GetFunction()->NewInstance(1, fargs) );
    { args.GetReturnValue().Set(ret); return; };
  }

  JS_METHOD(_documentserialize) {
    DOC;
    DOMImplementation * dom = NULL;
    DOMLSOutput * pOutput = NULL;
    DOMLSSerializer * pSerializer = NULL;
    bool cleanSer = true;
    bool cleanOut = true;
    if (args.Length()>2) {
      JS_RETURN_ERROR("[_documentserialize()] ERROR: Too many input parameters");
    }
    SS encoding("UTF-8");
    if (args.Length()>0) {
      if (args[0]->IsString()) {
	encoding.flush() << *v8::String::Utf8Value(args[0]->ToString());
      }
      else if (args[0]->IsObject()) {
	std::string domtype( *USTR(args[0]->ToObject()->Get(JS_STR("_domtype_"))->ToString()) );
	if (domtype=="DOMLSSerializer") {
	  pSerializer = RECAST(args[0]->ToObject()->GetInternalField(0),DOMLSSerializer *);
	  cleanSer = false;
	}
	else if (domtype=="DOMLSOutput") {
	  pOutput = RECAST(args[0]->ToObject()->GetInternalField(0),DOMLSOutput *);
	  cleanOut = false;
	}
      }
    }
    if (args.Length()>1) {
      if (args[1]->IsObject()) {
	std::string domtype( *USTR(args[1]->ToObject()->Get(JS_STR("_domtype_"))->ToString()) );
	if (domtype=="DOMLSSerializer") {
	  pSerializer = RECAST(args[1]->ToObject()->GetInternalField(0),DOMLSSerializer *);
	  cleanSer = false;
	}
	else if (domtype=="DOMLSOutput") {
	  pOutput = RECAST(args[1]->ToObject()->GetInternalField(0),DOMLSOutput *);
	  cleanOut = false;
	}
      }
    }
    XLSTRY(
      if (pOutput==NULL || pSerializer==NULL) {
	dom = doc->getImplementation();
      }
      if (pOutput==NULL) {
	pOutput = ((DOMImplementationLS *)dom)->createLSOutput();
	pOutput->setEncoding(X_STR(encoding));
      }
      if (pSerializer==NULL) {
	pSerializer = ((DOMImplementationLS *)dom)->createLSSerializer();
	pSerializer->setNewLine( XML_STR("\n") );
	DOMConfiguration * config ( pSerializer->getDomConfig() );
	config->setParameter(XMLUni::fgDOMWRTDiscardDefaultContent, true);
	config->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);
      }
      MemBufFormatTarget memTarget;
      pOutput->setByteStream(&memTarget);
      pSerializer->write(doc, pOutput);
      size_t len = strlen((char *)memTarget.getRawBuffer());
      char * cstr = new char[len];
      memcpy((void *)cstr,(const void *)memTarget.getRawBuffer(),len);
      v8::Handle<v8::String> ret(JS_STR(cstr));
      if (cleanSer==true) {
	pSerializer->release();
      }
      if (cleanOut==true) {
	pOutput->release();
      }
      delete cstr;
      { args.GetReturnValue().Set(ret); return; };
    );
  }

  /**
   *	~DOMDocument method
   *	- Destructor for Document objects
   */ 
  JS_METHOD(_document_destructor) {
    DOC;
    if (doc!=NULL) {
      v8::TryCatch inner;
      //XTRY( doc->~DOMDocument(); );
      if (inner.HasCaught()) {
      }
      // SAVE_PTR(0,NULL);
    }
    { args.GetReturnValue().Set(args.This()); return; };
  }


  /**
   *	PreElement constructor:
   * 	- Adds "~PreElement()" method to global GC
   */
  JS_METHOD(_preelement) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1 && args.Length()!=2)
      JS_RETURN_ERROR("[_preelement()] ERROR: Incorrect number of input parameters");
    ASSERT_CONSTRUCTOR;
    //GC * gc = GC_PTR;
    //gc->add(args.This(), "~PreElement");
    DOMElement * element = NULL;
    if (args[0]->IsExternal()) {
      element = RECAST(args[0],DOMElement *);
    }
    else if (args[0]->IsObject()) {
      v8::Handle<v8::Object> tobj( args[0]->ToObject() );
      element = RECAST(tobj->GetInternalField(0),DOMElement *);
    }
    if (element==NULL) {
      JS_RETURN_ERROR("[_preelement()] ERROR: \"element\" is a null pointer");
    }
    else {
      SAVE_PTR(0,element);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_preelement_destructor) {
    /* v8::TryCatch tc; */
    //ELEMENT;
    //XTRY(
	// element->release();
	// element->~DOMElement();
    //);
    //SAVE_PTR(0,NULL)
    { args.GetReturnValue().Set(args.This()); return; };
  }

  /**
   *	Element constructor:
   * 	- Adds "Element()" method to global GC
   */
  JS_METHOD(_element) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1 && args.Length()!=2)
      JS_RETURN_ERROR("[_element()] ERROR: Incorrect number of input parameters");
    ASSERT_CONSTRUCTOR;
    //GC * gc = GC_PTR;
    //gc->add(args.This(), "~DOMElement");
    DOMElement * element = NULL;
    if (args[0]->IsExternal()) {
      element = RECAST(args[0],DOMElement *);
    }
    else if (args[0]->IsObject()) {
      v8::Handle<v8::Object> tobj( args[0]->ToObject() );
      element = RECAST(tobj->GetInternalField(0),DOMElement *);
    }
    if (element==NULL) {
      JS_RETURN_ERROR("[_element()] ERROR: \"element\" is a null pointer");
    }
    else {
      SAVE_PTR(0,element);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_elementgetasnode) {
	/* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_elementgetasnode()] ERROR: Too many input parameters");
    DOMNode * node = NULL;
    node = RECAST(args.This()->GetInternalField(0),DOMNode *);
    if (node==NULL) {
      JS_RETURN_ERROR("[elementgetasnode()] ERROR: \"node\" is a null pointer");
    }
    else {
      const int fargc = 2;
      v8::Local<v8::Value> upConvert = v8::Boolean::New(JS_ISOLATE, false);
      v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)node), upConvert };
      v8::Handle<v8::Function> f =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction();
      v8::Handle<v8::Object> ret ( f->NewInstance(fargc, fargv) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_elementgettagname) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_elementgettagname()] ERROR: Too many input parameters");
    EL;
    XS name = NULL;
    XTRY( name = (XMLCh *)el->getTagName(); );
    if (name==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(name);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_elementgetattribute) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_elementgetattribute()] ERROR: Incorrect number of input parameters");
    EL;
    XS val = NULL;
    XTRY( val = (XMLCh *)el->getAttribute(ARGSTR(0)); );
    if (val==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(val);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_elementgetattributenode) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_elementgetattributenode()] ERROR: Incorrect number of input parameters");
    EL;
    DOMAttr * attr = NULL;
    XTRY( attr = el->getAttributeNode(ARGSTR(0)); );
    if (attr==NULL) {
      JS_RETURN_ERROR("[_elementgetattributenode()] ERROR: \"attr\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)attr) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fattribute)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_elementgetelementsbytagname) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_elementgetelementsbytagname()] ERROR: Incorrect number of input parameters");
    EL;
    SS name( *v8::String::Utf8Value(args[0]->ToString()) );
    DOMNodeList * nodelist = NULL;
    XTRY( nodelist = el->getElementsByTagName(X_STR(name)); );
    if (nodelist==NULL) {
      JS_RETURN_ERROR("[_elementgetelementsbytagname()] ERROR: \"nodelist\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)nodelist) };
      v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnodelist)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_elementsetattribute) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_elementsetattribute()] ERROR: Incorrect number of input parameters");
    EL;
    XTRY( el->setAttribute(ARGSTR(0),ARGSTR(1)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_elementsetattributenode) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_elementsetattributenode()] ERROR: Incorrect number of input parameters");
    EL;
    DOMAttr * newAttr = NULL;
    if (args[0]->IsExternal()) {
      newAttr = RECAST(args[0],DOMAttr *);
    }
    else if (args[0]->IsObject()) {
      newAttr = RECAST(args[0]->ToObject()->GetInternalField(0),DOMAttr *);
    }
    if (newAttr==NULL) {
      JS_RETURN_ERROR("[_elementsetattributenode()] ERROR: \"newAttr\" is a null pointer");
    }
    DOMAttr * ret = NULL;
    XTRY( ret = el->setAttributeNode(newAttr); );
    if (ret==NULL) {
      args.GetReturnValue().Set(v8::Null(JS_ISOLATE));
      return;
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)ret) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fattribute)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_elementremoveattributenode) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_elementremoveattributenode()] ERROR: Incorrect number of input parameters");
    EL;
    DOMAttr * oldAttr = NULL;
    if (args[0]->IsExternal()) {
      oldAttr = RECAST(args[0],DOMAttr *);
    }
    else if (args[0]->IsObject()) {
      oldAttr = RECAST(args[0]->ToObject()->GetInternalField(0),DOMAttr *);
    }
    if (oldAttr==NULL) {
      JS_RETURN_ERROR("[_elementremoveattributenode()] ERROR: \"oldAttr\" is a null pointer");
    }
    DOMAttr * ret = NULL;
    XTRY( ret = el->removeAttributeNode(oldAttr); );
    if (ret==NULL) {
      JS_RETURN_ERROR("[_elementremoveattributenode()] ERROR: \"ret\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)ret) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fattribute)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_elementremoveattribute) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_elementremoveattribute()] ERROR: Incorrect number of input parameters");
    EL;
    XTRY( el->removeAttribute(ARGSTR(0)); );
    args.GetReturnValue().Set(JS_BOOL(true)); return;
  }

  JS_METHOD(_elementgetattributens) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_elementgetattributens()] ERROR: Incorrect number of input parameters");
    EL;
    XS val = NULL;
    XTRY( val = (XMLCh *)el->getAttributeNS(ARGSTR(0),ARGSTR(1)); );
    if (val==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(val);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }    
  }

  JS_METHOD(_elementsetattributens) {
    /* v8::TryCatch tc; */
    if (args.Length()!=3)
      JS_RETURN_ERROR("[_elementsetattributens()] ERROR: Incorrect number of input parameters");
    EL;
    XTRY( el->setAttributeNS(ARGSTR(0),ARGSTR(1),ARGSTR(2)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_elementremoveattributens) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_elementremoveattributens()] ERROR: Incorrect number of input parameters");
    EL;
    XTRY( el->removeAttributeNS(ARGSTR(0),ARGSTR(1)); );
    args.GetReturnValue().Set(JS_BOOL(true)); return;
  }

  JS_METHOD(_elementgetattributenodens) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_elementgetattributenodens()] ERROR: Incorrect number of input parameters");
    EL;
    DOMAttr * attr = NULL;
    XTRY( attr = el->getAttributeNodeNS(ARGSTR(0),ARGSTR(1)); );
    if (attr==NULL) {
      JS_RETURN_ERROR("[_elementgetattributenodens()] ERROR: \"attr\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)attr) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fattribute)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_elementsetattributenodens) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_elementsetattributenodens()] ERROR: Incorrect number of input parameters");
    EL;
    DOMAttr * newAttr = NULL;
    if (args[0]->IsExternal()) {
      newAttr = RECAST(args[0],DOMAttr *);
    }
    else if (args[0]->IsObject()) {
      newAttr = RECAST(args[0]->ToObject()->GetInternalField(0),DOMAttr *);
    }
    if (newAttr==NULL) {
      JS_RETURN_ERROR("[_elementsetattributenodens()] ERROR: \"newAttr\" is a null pointer");
    }
    DOMAttr * ret = NULL;
    XTRY( ret = el->setAttributeNodeNS(newAttr); );
    if (ret==NULL) {
      { args.GetReturnValue().Set(v8::Null(JS_ISOLATE)); return; }
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)ret) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fattribute)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_elementgetelementsbytagnamens) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_elementgetelementsbytagnamens()] ERROR: Incorrect number of input parameters");
    EL;
    DOMNodeList * nodelist = NULL;
    XTRY( nodelist = el->getElementsByTagNameNS(ARGSTR(0),ARGSTR(1)); );
    if (nodelist==NULL) {
      JS_RETURN_ERROR("[_elementgetelementsbytagnamens()] ERROR: \"nodelist\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)nodelist) };
      v8::Local<v8::Object> ret(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnodelist)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_elementhasattribute) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_elementhasattribute()] ERROR: Incorrect number of input parameters");
    EL;
    bool ret = false;
    XTRY( el->hasAttribute(ARGSTR(0)); );
    { args.GetReturnValue().Set(JS_BOOL(ret)); return; }
  }

  JS_METHOD(_elementhasattributens) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_elementhasattributens()] ERROR: Incorrect number of input parameters");
    EL;
    bool ret = false;
    XTRY( ret = el->hasAttributeNS(ARGSTR(0),ARGSTR(1)); );
    { args.GetReturnValue().Set(JS_BOOL(ret)); return; }    
  }

  JS_METHOD(_elementsetidattribute) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_elementsetidattribute()] ERROR: Incorrect number of input parameters");
    EL;
    bool isId = args[1]->ToBoolean()->BooleanValue();
    XTRY( el->setIdAttribute(ARGSTR(0),isId); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_elementsetidattributens) {
    /* v8::TryCatch tc; */
    if (args.Length()!=3)
      JS_RETURN_ERROR("[_elementsetidattributens()] ERROR: Incorrect number of input parameters");
    EL;
    bool isId = args[2]->ToBoolean()->BooleanValue();
    XTRY( el->setIdAttributeNS(ARGSTR(0),ARGSTR(1),isId); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_elementsetidattributenode) {
    /* v8::TryCatch tc; */
    if (args.Length()!=2)
      JS_RETURN_ERROR("[_elementsetidattributenode()] ERROR: Incorrect number of input parameters");
    EL;
    DOMAttr * newAttr = NULL;
    if (args[0]->IsExternal()) {
      newAttr = RECAST(args[0],DOMAttr *);
    }
    else if (args[0]->IsObject()) {
      newAttr = RECAST(args[0]->ToObject()->GetInternalField(0),DOMAttr *);
    }
    bool isId = args[1]->ToBoolean()->BooleanValue();
    XTRY( el->setIdAttributeNode(newAttr,isId); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_elementgetschematypeinfo) {
    /* v8::TryCatch tc; */
     if (args.Length()>0)
      JS_RETURN_ERROR("[_elementgetschematypeinfo()] ERROR: Too many input parameters");
    EL;
    DOMTypeInfo * typeinfo = NULL;
    XTRY( typeinfo = (DOMTypeInfo *)el->getSchemaTypeInfo(); );
    if (typeinfo==NULL) {
      JS_RETURN_ERROR("[_elementgetschematypeinfo()] ERROR: \"typeinfo\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)typeinfo) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::ftypeinfo)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  /**
   *	~Element method
   *	- Destructor for Element objects
   */ 
  JS_METHOD(_element_destructor) {
    /* v8::TryCatch tc; */
    //ELEMENT;
    XTRY(
	// element->release();
	//element->~DOMElement(); 
    );
    //SAVE_PTR(0,NULL)
    { args.GetReturnValue().Set(args.This()); return; };
  }

  /**
   *	Attribute constructor:
   * 	- Adds "Attribute()" method to global GC
   */
  JS_METHOD(_attribute) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_attribute()] ERROR: Incorrect number of input parameters");
    ASSERT_CONSTRUCTOR;
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMAttr");
    DOMAttr * attr = NULL;
    if (args[0]->IsExternal()) {
      attr = RECAST(args[0],DOMAttr *);
    }
    else if (args[0]->IsObject()) {
      attr = RECAST(args[0]->ToObject()->GetInternalField(0),DOMAttr *);
    }
    if (attr==NULL) {
      JS_RETURN_ERROR("[_attribute()] ERROR: \"attr\" is a null pointer");
    }
    else {
      SAVE_PTR(0,attr);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_attributegetname) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_attributegetname()] ERROR: Too many input parameters");
    ATTRIBUTE;
    XS name = NULL;
    XTRY( name = (XMLCh *)attribute->getName(); );
    if (name==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(name);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_attributegetspecified) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_attributegetspecified()] ERROR: Too many input parameters");
    ATTRIBUTE;
    bool ret = false;
    XTRY( ret = (bool)attribute->getSpecified(); );
    { args.GetReturnValue().Set(JS_BOOL(ret)); return; }
  }

  JS_METHOD(_attributegetvalue) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_attributegetvalue()] ERROR: Too many input parameters");
    ATTRIBUTE;
    XS val = NULL;
    XTRY( val = (XMLCh *)attribute->getValue(); );
    if (val==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(val);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_attributesetvalue) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_attributesetvalue()] ERROR: Incorrect number of input parameters");
    ATTRIBUTE;
    XTRY( attribute->setValue(ARGSTR(0)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_attributegetownerelement) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_attributegetownerelement()] ERROR: Too many input parameters");
    ATTRIBUTE;
    DOMElement * el = NULL;
    XTRY( el = attribute->getOwnerElement(); );
    if (el==NULL) {
      JS_RETURN_ERROR("[_attributegetownerelement()] ERROR: \"el\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)el) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::felement)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  JS_METHOD(_attributeisid) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_attributeisid()] ERROR: Too many input parameters");
    ATTRIBUTE;
    bool ret = false;
    XTRY( ret = attribute->isId(); );
    { args.GetReturnValue().Set(JS_BOOL(ret)); return; }
  }

  JS_METHOD(_attributegetschematypeinfo) {
    /* v8::TryCatch tc; */
    if (args.Length()>0)
      JS_RETURN_ERROR("[_attributegetschematypeinfo()] ERROR: Too many input parameters");
    ATTRIBUTE;
    DOMTypeInfo * typeinfo = NULL;
    XTRY( typeinfo = (DOMTypeInfo *)attribute->getSchemaTypeInfo(); );
    if (typeinfo==NULL) {
      JS_RETURN_ERROR("[_attributegetschematypeinfo()] ERROR: \"typeinfo\" is a null pointer");
    }
    else {
      v8::Handle<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)typeinfo) };
      v8::Handle<v8::Object> ret( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::ftypeinfo)->GetFunction()->NewInstance(1, fargs) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  /**
   *	~Attribute method
   *	- Destructor for Attribute objects
   */
  JS_METHOD(_attribute_destructor) {
    /* v8::TryCatch tc; */
    //ATTRIBUTE;
    //XTRY( attribute->release(); );
    //XTRY( attribute->~DOMAttr(); );
    // SAVE_PTR(0,NULL);
    { args.GetReturnValue().Set(args.This()); return; };
  }

  /**
   *	CDATA constructor:
   * 	- Adds "CDATA()" method to global GC
   */
  JS_METHOD(_cdata) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_cdata()] ERROR: Incorrect number of input parameters");
    ASSERT_CONSTRUCTOR;
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMCharacterData");
    DOMCharacterData * cdata = NULL;
    if (args[0]->IsExternal()) {
      cdata = RECAST(args[0],DOMCharacterData *);
    }
    else if (args[0]->IsObject()) {
      cdata = RECAST(args[0]->ToObject()->GetInternalField(0),DOMCharacterData *);
    }
    if (cdata==NULL) {
      JS_RETURN_ERROR("[_cdata()] ERROR: \"cdata\" is a null pointer");
    }
    else {
      SAVE_PTR(0,cdata);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_cdatagetdata) {
    /* v8::TryCatch tc; */
    CDATA;
    const XS data = NULL;
    XTRY( data = (XMLCh *)cdata->getData(); );
    if (data==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(data);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_cdatagetlength) {
    /* v8::TryCatch tc; */
    CDATA;
    XMLSize_t ret = 0;
    XTRY( ret = cdata->getLength(); );
    { args.GetReturnValue().Set(JS_INT(ret)); return; }
  }

  JS_METHOD(_cdatasubstringdata) {
    /* v8::TryCatch tc; */
    CDATA;
    XMLSize_t offset = (XMLSize_t)args[0]->ToInteger()->IntegerValue();
    XMLSize_t count = (XMLSize_t)args[1]->ToInteger()->IntegerValue();
    XS data = NULL;
    XTRY( data = (XMLCh *)cdata->substringData(offset, count); );
    if (data==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(data);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_cdataappenddata) {
    /* v8::TryCatch tc; */
    CDATA;
    SS data( *v8::String::Utf8Value(args[0]->ToString()) );
    XTRY( cdata->appendData(X_STR(data)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_cdatainsertdata) {
    /* v8::TryCatch tc; */
    CDATA;
    XMLSize_t offset = (XMLSize_t)args[0]->ToInteger()->IntegerValue();
    SS data( *v8::String::Utf8Value(args[1]->ToString()) );
    XTRY( cdata->insertData(offset,X_STR(data)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_cdatadeletedata) {
    /* v8::TryCatch tc; */
    CDATA;
    XMLSize_t offset = (XMLSize_t)args[0]->ToInteger()->IntegerValue();
    XMLSize_t count = (XMLSize_t)args[1]->ToInteger()->IntegerValue();
    XTRY( cdata->deleteData(offset, count); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_cdatareplacedata) {
    /* v8::TryCatch tc; */
    CDATA;
    XMLSize_t offset = (XMLSize_t)args[0]->ToInteger()->IntegerValue();
    XMLSize_t count = (XMLSize_t)args[1]->ToInteger()->IntegerValue();
    SS data( *v8::String::Utf8Value(args[2]->ToString()) );
    XTRY( cdata->replaceData(offset, count, X_STR(data)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_cdatasetdata) {
    /* v8::TryCatch tc; */
    CDATA;
    SS data( *v8::String::Utf8Value(args[0]->ToString()) );
    XTRY( cdata->setData(X_STR(data)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  /**
   *	~CDATA method
   *	- Destructor for CDATA objects
   */ 
  JS_METHOD(_cdata_destructor) {
    /* v8::TryCatch tc; */
    //CDATA;
    //XTRY( cdata->~DOMCharacterData(); );
    // SAVE_PTR(0,NULL);
    { args.GetReturnValue().Set(args.This()); return; };
  }

  /**
   *	Comment constructor:
   * 	- Adds "Comment()" method to global GC
   */
  JS_METHOD(_comment) {
    ASSERT_CONSTRUCTOR;
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMComment");
    DOMComment * comment = NULL;
    if (args[0]->IsExternal()) {
      comment = RECAST(args[0],DOMComment *);
    }
    else if (args[0]->IsObject()) {
      comment = RECAST(args[0]->ToObject()->GetInternalField(0),DOMComment *);
    }
    if (comment==NULL) {
      JS_RETURN_ERROR("[_comment()] ERROR: \"comment\" is a null pointer");
    }
    else {
      SAVE_PTR(0,comment);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  /**
   *	~Comment method
   *	- Destructor for Comment objects
   */ 
  JS_METHOD(_comment_destructor) {
    /* v8::TryCatch tc; */
    //COMMENT;
    //XTRY( comment->~DOMComment(); );
    // SAVE_PTR(0,NULL);
    { args.GetReturnValue().Set(args.This()); return; };
  }

  /**
   *	Entity constructor:
   * 	- Adds "Entity()" method to global GC
   */
  JS_METHOD(_entity) {
    ASSERT_CONSTRUCTOR;
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMEntity");
    DOMEntity * entity = NULL;
    if (args[0]->IsExternal()) {
      entity = RECAST(args[0], DOMEntity *);
    }
    else if (args[0]->IsObject()) {
      entity = RECAST(args[0]->ToObject()->GetInternalField(0), DOMEntity *);
    }
    if (entity==NULL) {
      JS_RETURN_ERROR("[_entity()] ERROR: \"entity\" is a null pointer");
    }
    else {
      SAVE_PTR(0,entity);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_entitygetpublicid) {
    /* v8::TryCatch tc; */
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_entitygetpublicid()] ERROR: Too many input parameters");
    }
    ENTITY;
    XS publicid = NULL;
    XTRY( publicid = (XMLCh *)entity->getPublicId(); );
    if (publicid==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(publicid);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_entitygetsystemid) {
    /* v8::TryCatch tc; */
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_entitygetsystemid()] ERROR: Too many input parameters");
    }
    ENTITY;
    XS systemid = NULL;
    XTRY( systemid = (XMLCh *)entity->getSystemId(); );
    if (systemid==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(systemid);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_entitygetnotationname) {
    /* v8::TryCatch tc; */
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_entitygetnotationname()] ERROR: Too many input parameters");
    }
    ENTITY;
    XS name = NULL;
    XTRY( name = (XMLCh *)entity->getNotationName(); );
    if (name==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(name);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_entitygetinputencoding) {
    /* v8::TryCatch tc; */
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_entitygetinputencoding()] ERROR: Too many input parameters");
    }
    ENTITY;
    XS encoding = NULL;
    XTRY( encoding = (XMLCh *)entity->getInputEncoding(); );
    if (encoding==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(encoding);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_entitygetxmlencoding) {
    /* v8::TryCatch tc; */
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_entitygetxmlencoding()] ERROR: Too many input parameters");
    }
    ENTITY;
    XS encoding = NULL;
    XTRY( encoding = (XMLCh *)entity->getXmlEncoding(); );
    if (encoding==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(encoding);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_entitygetxmlversion) {
    /* v8::TryCatch tc; */
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_entitygetxmlversion()] ERROR: Too many input parameters");
    }
    ENTITY;
    XS version = NULL;
    XTRY( version = (XMLCh *)entity->getXmlVersion(); );
    if (version==NULL) {
      { args.GetReturnValue().Set(JS_STR("")); return; }
    }
    else {
      char * ret = X(version);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  /**
   *	~Entity method
   *	- Destructor for Entity objects
   */ 
  JS_METHOD(_entity_destructor) {
    /* v8::TryCatch tc; */
    //ENTITY;
    //XTRY( entity->~DOMEntity(); );
    // SAVE_PTR(0,NULL);
    { args.GetReturnValue().Set(args.This()); return; };
  }

  /**
   *	EntityReference constructor:
   * 	- Adds "EntityReference()" method to global GC
   */
  JS_METHOD(_entityreference) {
    ASSERT_CONSTRUCTOR;
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMEntityReference");
    DOMEntityReference * entityreference = NULL;
    if (args[0]->IsExternal()) {
      entityreference = RECAST(args[0], DOMEntityReference *);
    }
    else if (args[0]->IsObject()) {
      entityreference = RECAST(args[0]->ToObject()->GetInternalField(0), DOMEntityReference *);
    }
    if (entityreference==NULL)
      JS_RETURN_ERROR("[_entityreference()] ERROR: \"entityreference\" is a null pointer")
    else {
      SAVE_PTR(0,entityreference);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  /**
   *	~EntityReference method
   *	- Destructor for EntityReference objects
   */ 
  JS_METHOD(_entityreference_destructor) {
    /* v8::TryCatch tc; */
    ENTITYREFERENCE;
    XTRY( entityreference->~DOMEntityReference(); );
    // SAVE_PTR(0,NULL);
    { args.GetReturnValue().Set(args.This()); return; };
  }

  /**
   *	Notation constructor:
   * 	- Adds "Notation()" method to global GC
   */
  JS_METHOD(_notation) {
    ASSERT_CONSTRUCTOR;
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMNotation");
    DOMNotation * notation = NULL;
    if (args[0]->IsExternal()) {
      notation = RECAST(args[0], DOMNotation *);
    }
    else if (args[0]->IsObject()) {
      notation = RECAST(args[0]->ToObject()->GetInternalField(0), DOMNotation *);
    }
    if (notation==NULL)
      JS_RETURN_ERROR("[_notation()] ERROR: \"notation\" is a null pointer")
    else {
      SAVE_PTR(0,notation);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_notationgetpublicid) {
    NOTATION;
    char * ret = NULL;
    XS pubid = NULL;
    XTRY( pubid = (XS)notation->getPublicId(); );
    if (pubid==NULL) {
      ret = (char *)"";
    }
    else {
      ret = X(pubid);
    }
    { args.GetReturnValue().Set(JS_STR(ret)); return; }
  }

  JS_METHOD(_notationgetsystemid) {
    NOTATION;
    char * ret = NULL;
    XS sysid = NULL;
    XTRY( sysid = (XS)notation->getSystemId(); );
    if (sysid==NULL) {
      ret = (char *)"";
    }
    else {
      ret = X(sysid);
    }
    { args.GetReturnValue().Set(JS_STR(ret)); return; }
  }

  /**
   *	~Notation method
   *	- Destructor for Notation objects
   */ 
  JS_METHOD(_notation_destructor) {
    /* v8::TryCatch tc; */
    //NOTATION;
    //XTRY( notation->~DOMNotation(); );
    // SAVE_PTR(0,NULL);
    { args.GetReturnValue().Set(args.This()); return; };
  }

  /**
   *	ProcessingInstruction constructor:
   * 	- Adds "ProcessingInstruction()" method to global GC
   */
  JS_METHOD(_processinginstruction) {
    ASSERT_CONSTRUCTOR;
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMProcessingInstruction");
    DOMProcessingInstruction * procinst = NULL;
    if (args[0]->IsExternal()) {
      procinst = RECAST(args[0], DOMProcessingInstruction *);
    }
    else if (args[0]->IsObject()) {
      procinst = RECAST(args[0]->ToObject()->GetInternalField(0), DOMProcessingInstruction *);
    }
    if (procinst==NULL)
      JS_RETURN_ERROR("[_procinst()] ERROR: \"procinst\" is a null pointer")
    else {
      SAVE_PTR(0,procinst);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_processinginstructiongetdata) {
    PROCINST;
    char * ret = NULL;
    XS data = NULL;
    XTRY( data = (XS)procinst->getData(); );
    if (data==NULL) {
      ret = (char *)"";
    }
    else {
      ret = X(data);
    }
    { args.GetReturnValue().Set(JS_STR(ret)); return; }
  }

  JS_METHOD(_processinginstructionsetdata) {
    if (args.Length()!=1) {
      JS_RETURN_ERROR("[_processinginstructionsetdata()] ERROR: Incorrect number of input parameters");
    }
    PROCINST;
    XTRY( procinst->setData(ARGSTR(0)); );
    { args.GetReturnValue().Set(args.This()); return; };
  }

  JS_METHOD(_processinginstructiongettarget) {
    PROCINST;
    char * ret = NULL;
    XS target = NULL;
    XTRY( target = (XS)procinst->getTarget(); );
    if (target==NULL) {
      ret = (char *)"";
    }
    else {
      ret = X(target);
    }
    { args.GetReturnValue().Set(JS_STR(ret)); return; }
  }

  /**
   *	~ProcessingInstruction method
   *	- Destructor for ProcessingInstruction objects
   */ 
  JS_METHOD(_processinginstruction_destructor) {
    /* v8::TryCatch tc; */
    //PROCINST;
    // SAVE_PTR(0,NULL);
    //XTRY( procinst->~DOMProcessingInstruction(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  /**
   *	DOMTypeInfo
   **/
  JS_METHOD(_typeinfo) {
    /* v8::TryCatch tc; */
    if (args.Length()!=1)
      JS_RETURN_ERROR("[_typeinfo()] ERROR: Incorrect number of input parameters");
    ASSERT_CONSTRUCTOR;
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMTypeInfo");
    DOMTypeInfo * typeinfo = NULL;
    if (args[0]->IsExternal()) {
      typeinfo = RECAST(args[0],DOMTypeInfo *);
    }
    else if (args[0]->IsObject()) {
      typeinfo = RECAST(args[0]->ToObject()->GetInternalField(0),DOMTypeInfo *);
    }
    if (typeinfo==NULL) {
      JS_RETURN_ERROR("[_typeinfo()] ERROR: \"typeinfo\" is a null pointer");
    }
    else {
      SAVE_PTR(0, typeinfo);
      { args.GetReturnValue().Set(args.This()); return; };
    }
  }

  JS_METHOD(_typeinfogettypename) {
    /* v8::TryCatch tc; */
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_typeinfogettypename()] ERROR: Too many input parameters");
    }
    TYPEINFO;
    XS name = NULL;
    XTRY( name = (XMLCh *)typeinfo->getTypeName(); );
    if (name==NULL) {
      JS_RETURN_ERROR("[_typeinfogettypename()] ERROR: \"name\" is a null pointer");
    }
    else {
      char * ret = X(name);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_typeinfogettypenamespace) {
    /* v8::TryCatch tc; */
    if (args.Length()>0) {
      JS_RETURN_ERROR("[_typeinfogettypename()] ERROR: Too many input parameters");
    }
    TYPEINFO;
    XS lnamespace = NULL;
    XTRY( lnamespace = (XMLCh *)typeinfo->getTypeNamespace(); );
    if (lnamespace==NULL) {
      JS_RETURN_ERROR("[_typeinfogettypenamespace()] ERROR: \"namespace\" is a null pointer");
    }
    else {
      char * ret = X(lnamespace);
      { args.GetReturnValue().Set(JS_STR(ret)); return; }
    }
  }

  JS_METHOD(_typeinfoisderivedfrom) {
    /* v8::TryCatch tc; */
    if (args.Length()!=3) {
      JS_RETURN_ERROR("[_typeinfogettypename()] ERROR: Incorrect number of input parameters");
    }
    TYPEINFO;
    int derivationMethod = (int)args[2]->ToInteger()->IntegerValue();
    bool ret = false;
    XTRY( ret = typeinfo->isDerivedFrom(ARGSTR(0),ARGSTR(1),(xercesc_3_1::DOMTypeInfo::DerivationMethods)derivationMethod); );
    { args.GetReturnValue().Set(JS_BOOL(ret)); return; }
  }

  JS_METHOD(_typeinfo_destructor) {
    /* v8::TryCatch tc; */
    TYPEINFO;
    //XTRY( typeinfo->release(); );
    XTRY( typeinfo->~DOMTypeInfo(); );
    { args.GetReturnValue().Set(args.This()); return; };
  }


  // * * *
  // * * *	Property accessors
  // * * *

  void echo_data(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& args) {
    v8::Handle<v8::Value> ret( JS_STR(*USTR(args.Data())) );
    { args.GetReturnValue().Set(ret); return; };
  }

  void get_node_type(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& args) {
    /* v8::TryCatch tc; */
    NODE;
    int nodeType = 0;
    XTRY( nodeType = (int)node->getNodeType(); );
    if (nodeType==0) {
      JS_RETURN_ERROR("[get_node_type()] ERROR: nodeType is invalid");
    }
    else {
      v8::Handle<v8::Integer> ret( JS_INT(nodeType) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  void get_node_name(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& args) {
    /* v8::TryCatch tc; */
    NODE;
    XS nodeName = NULL;
    XTRY( nodeName = (XMLCh *)node->getNodeName(); );
    if (nodeName==NULL) {
      JS_RETURN_ERROR("[get_node_name()] ERROR: \"nodeName\" is a null pointer");
    }
    else {
      v8::Handle<v8::String> ret( JS_STR(X(nodeName)) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  void get_node_value(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& args) {
    /* v8::TryCatch tc; */
    NODE;
    XS nodeValue = NULL;
    XTRY( nodeValue = (XMLCh *)node->getNodeValue(); );
    if (nodeValue==NULL) {
      JS_RETURN_ERROR("[get_node_value()] ERROR: \"nodeValue\" is a null pointer");
    }
    else {
      char * tmp = NULL;
      v8::Handle<v8::Value> ret( v8::Undefined(JS_ISOLATE) );
      if (nodeValue!=NULL) {
        tmp = X(nodeValue);
        if (strlen(tmp)<1) {
          ret = v8::Null(JS_ISOLATE);
        }
        else {
          ret = JS_STR(tmp);
        }
      }
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  void get_tag_name(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& args) {
    /* v8::TryCatch tc; */
    EL;
    XS tagName = NULL;
    XTRY( tagName = (XMLCh *)el->getTagName(); );
    if (tagName==NULL) {
      JS_RETURN_ERROR("[get_tag_name()] ERROR: \"tagName\" is a null pointer");
    }
    else {
      char * tmp = NULL;
      v8::Handle<v8::Value> ret( v8::Undefined(JS_ISOLATE) );
      if (tagName!=NULL) {
        tmp = X(tagName);
        if (strlen(tmp)<1) {
          ret = v8::Null(JS_ISOLATE);
        }
        else {
          ret = JS_STR(tmp);
        }
      }
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  void get_property (v8::Local<v8::String> iName, const v8::PropertyCallbackInfo<v8::Value>& args) {
	/* v8::TryCatch tc; */
    std::string name(*v8::String::Utf8Value(iName));
    SS funcname("");
    const int fargc = 0;
    v8::Handle<v8::Value> fargv[] = { };
    if (name=="domConfig" || name=="DomConfig" || name=="DOMConfig" || name=="DOMconfig")
      funcname << "getDomConfig";
    else if (name=="documentElement" || name=="DocumentElement" || name=="rootElement" || name=="RootElement" || name=="root")
      funcname << "getDocumentElement";
    else if (name=="inputEncoding")
      funcname << "getInputEncoding";
    else if (name=="xmlEncoding")
      funcname << "getXmlEncoding";
    else if (name=="xmlStandalone")
      funcname << "getXmlStandalone";
    else if (name=="xmlVersion")
      funcname << "getXmlVersion";
    else if (name=="baseUri" || name=="BaseUri" || name=="baseURI" || name=="BaseURI")
      funcname << "getBaseURI";
    else if (name=="filter" || name=="Filter")
      funcname << "getFilter";
    else if (name=="async" || name=="Async")
      funcname << "getAsync";
    else if (name=="grammar" || name=="Grammar")
      funcname << "getGrammar";
    else if (name=="rootGrammar" || name=="RootGrammar")
      funcname << "getRootGrammar";
    else if (name=="URIText" || name=="URItext" || name=="uriText" || name=="UriText" || name=="uri" || name=="URI" || name=="Uri")
      funcname << "getURIText";
    else if (name=="srcOffset" || name=="SrcOffset")
      funcname << "getSrcOffset";
    else if (name=="implementation" || name=="Implementation" || name=="ownerImplementation" || name=="OwnerImplementation")
      funcname << "getImplementation";
    else if (name=="localName" || name=="v8::LocalName")
      funcname << "getv8::LocalName";
    else if (name=="namespaceURI" || name=="namespaceUri" || name=="NamespaceURI" || name=="NamespaceUri")
      funcname << "getNamespaceURI";
    else if (name=="childNodes" || name=="ChildNodes")
      funcname << "getChildNodes";
    else if (name=="attributes" || name=="Attributes")
      funcname << "getAttributes";
    else if (name=="textContent" || name=="TextContent" || name=="innerText" || name=="InnerText")
      funcname << "getTextContent";
    else if (name=="internalSubset" || name=="InternalSubset")
      funcname << "getInternalSubset";
    else if (name=="prefix" || name=="Prefix")
      funcname << "getPrefix";
    else if (name=="firstChild" || name=="FirstChild")
      funcname << "getFirstChild";
    else if (name=="lastChild" || name=="LastChild")
      funcname << "getLastChild";
    else if (name=="parent" || name=="Parent" || name=="parentNode" || name=="ParentNode")
      funcname << "getParentNode";
    else if (name=="ownerDocument" || name=="OwnerDocument")
      funcname << "getOwnerDocument";
    else if (name=="ownerElement" || name=="OwnerElement")
      funcname << "getOwnerElement";
    else if (name=="nextSibling" || name=="NextSibling")
      funcname << "getNextSibling";
    else if (name=="previousSibling" || name=="PreviousSibling")
      funcname << "getPreviousSibling";
    else if (name=="length" || name=="Length")
      funcname << "getLength";
    else if (name=="value" || name=="v8::Value")
      funcname << "getv8::Value";
    else if (name=="innerHtml" || name=="innerHTML" || name=="innerXml" || name=="innerXML")
      funcname << "getInnerHTML";
    else if (name=="outerHtml" || name=="outerHTML" || name=="outerXml" || name=="outerXML")
      funcname << "serialize";
    else if (name=="parameterNames" || name=="ParameterNames")
      funcname << "getParameterNames";
    else if (name=="publicId" || name=="PublicId")
      funcname << "getPublicId";
    else if (name=="systemId" || name=="SystemId")
      funcname << "getSystemId";
    else if (name=="name" || name=="Name")
      funcname << "getName";
    else if (name=="data" || name=="Data")
      funcname << "getData";
    else if (name=="target" || name=="Target")
      funcname << "getTarget";
    else if (name=="entities" || name=="Entities")
      funcname << "getEntities";
    else if (name=="notations" || name=="Notations")
      funcname << "getNotations";
    else if (name=="documentURI")
      funcname << "getDocumentURI";
    else if (name=="strictErrorChecking")
      funcname << "getStrictErrorChecking";
    else if (name=="domConfig" || name=="DOMConfig")
      funcname << "getDOMConfig";
    else if (name=="specified")
      funcname << "getSpecified";
    else if (name=="schemaTypeInfo")
      funcname << "getSchemaTypeInfo";
    else if (name=="nodevalue" || name=="Nodev8::Value")
      funcname << "getNodev8::Value";
    else if (name=="prefix" || name=="Prefix")
      funcname << "getPrefix";
    v8::Local<v8::Value> f = args.Holder()->Get(JS_STR(CSTR(funcname)));
    v8::Handle<v8::Function> func = v8::Local<v8::Function>::Cast(f);
    v8::Handle<v8::Value> ret ( func->Call(args.Holder(), fargc, fargv) );
    { args.GetReturnValue().Set(ret); return; };
  }

  void set_property (v8::Local<v8::String> iName, v8::Local<v8::Value> iValue, const v8::PropertyCallbackInfo<void>& args) {
	/* v8::TryCatch tc; */
    std::string name(*v8::String::Utf8Value(iName));
    SS funcname("");
    const int fargc = 1;
    v8::Handle<v8::Value> fargv[] = { iValue };
    if (name=="filter" || name=="Filter")
      funcname << "setFilter";
    else if (name=="value" || name=="v8::Value")
      funcname << "setv8::Value";
    else if (name=="data" || name=="Data")
      funcname << "setData";
    else if (name=="textContent" || name=="TextContent" || name=="innerText" || name=="InnerText")
      funcname << "setTextContent";
    else if (name=="innerHtml" || name=="innerHTML" || name=="innerXml" || name=="innerXML")
      funcname << "setInnerXML";
    else if (name=="outerHtml" || name=="outerHTML" || name=="outerXml" || name=="outerXML")
      funcname << "setInnerXML";
    else if (name=="xmlStandalone")
      funcname << "setXmlStandalone";
    else if (name=="xmlVersion")
      funcname << "setXmlVersion";
    else if (name=="documentURI")
      funcname << "setDocumentURI";
    else if (name=="strictErrorChecking")
      funcname << "setStrictErrorChecking";
    else if (name=="nodevalue" || name=="Nodev8::Value")
      funcname << "setNodev8::Value";
    else if (name=="prefix" || name=="Prefix")
      funcname << "setPrefix";
    v8::Local<v8::Value> f = args.This()->Get(JS_STR(CSTR(funcname)));
    v8::Handle<v8::Function> func = v8::Local<v8::Function>::Cast(f);
    func->Call(args.This(), fargc, fargv);
  }


  void get_as_node (v8::Local<v8::String> iName, const v8::PropertyCallbackInfo<v8::Value>& args) {
	/* v8::TryCatch tc; */
    std::string name(*v8::String::Utf8Value(iName));
    DOMNode * node = NULL;
    node = RECAST(args.Holder()->GetInternalField(0),DOMNode *);
    if (node==NULL) {
      JS_RETURN_ERROR("[get_as_node()] ERROR: \"node\" is a null pointer");
    }
    else {
      const int fargc = 2;
      v8::Local<v8::Value> upConvert = v8::Boolean::New(JS_ISOLATE, false);
      v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)node), upConvert };
      v8::Handle<v8::Function> f =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction();
      v8::Handle<v8::Object> ret ( f->NewInstance(fargc, fargv) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  void get_as_element (v8::Local<v8::String> iName, const v8::PropertyCallbackInfo<v8::Value>& args) {
	/* v8::TryCatch tc; */
    std::string name(*v8::String::Utf8Value(iName));
    DOMNode * node = NULL;
    node = RECAST(args.Holder()->GetInternalField(0),DOMNode *);
    if (node==NULL) {
      JS_RETURN_ERROR("[get_as_element()] ERROR: \"node\" is a null pointer");
    }
    else {
      const int fargc = 2;
      v8::Local<v8::Value> upConvert = v8::Boolean::New(JS_ISOLATE, true);
      v8::Local<v8::Value> fargv[] = { v8::External::New(JS_ISOLATE, (void *)node), upConvert };
      v8::Handle<v8::Function> f =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction();
      v8::Handle<v8::Object> ret ( f->NewInstance(fargc, fargv) );
      { args.GetReturnValue().Set(ret); return; };
    }
  }

  //	Indexed property handlers:
  //		(these enable "square bracket"-style dereferencing of items in array-like collections
  //		 such as DOMNodeList, DOMStringList, or DOMNamedNodeMap objects, using an integer as index)

  void indexed_property_get( uint32_t index, const v8::PropertyCallbackInfo<v8::Value>& args ) {
    SS objstream( *v8::String::Utf8Value(args.Data()->ToString()) );
    std::string objtype( objstream.str() );
    v8::Handle<v8::Object> This( args.Holder() );
    v8::Handle<v8::Value> ret;
    XMLSize_t idx = (XMLSize_t)index;
    if (objtype=="domlist") {
      DOMImplementationList * domlist = reinterpret_cast<DOMImplementationList *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      DOMImplementation * val = NULL;
      XTRY( val = (DOMImplementation *)domlist->item(idx); );
      if (val==NULL) {
	// JS_ERROR("[indexed_property_get()] ERROR: (domlist) \"val\" is a null pointer");
	ret = v8::Undefined(JS_ISOLATE);
      }
      else {
	v8::Local<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)val) };
	ret =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdom)->GetFunction()->NewInstance(1, fargs);
      }
    }
    else if (objtype=="stringlist") {
      DOMStringList * stringlist = reinterpret_cast<DOMStringList *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      XMLCh * val = NULL;
      XTRY( val = (XMLCh *)stringlist->item(idx); );
      if (val==NULL) {
	JS_ERROR("[indexed_property_get()] ERROR: (stringlist) \"val\" is a null pointer");
      }
      else {
	ret = JS_STR(X(val));
      }
    }
    else if (objtype=="namednodemap") {
      DOMNamedNodeMap * nodemap = reinterpret_cast<DOMNamedNodeMap *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      DOMNode * val = NULL;
      XTRY( val = nodemap->item(idx); );
      if (val==NULL) {
	//JS_ERROR("[indexed_property_get()] ERROR: (namednodemap) \"val\" is a null pointer");
	ret = v8::Undefined(JS_ISOLATE);
      }
      else {
	v8::Local<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)val) };
	ret =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs);
      }
    }
    else if (objtype=="nodelist") {
      DOMNodeList * nodelist = reinterpret_cast<DOMNodeList *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      DOMNode * val = NULL;
      XTRY( val = nodelist->item(idx); );
      if (val==NULL) {
	//JS_ERROR("[indexed_property_get()] ERROR: (nodelist) \"val\" is a null pointer");
	ret = v8::Undefined(JS_ISOLATE);
      }
      else {
	v8::Local<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)val) };
	ret =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs);
      }
    }
    else {
      JS_RETURN_ERROR("[indexed_property_get()] ERROR: unrecognized object type");
    }
    { args.GetReturnValue().Set(ret); return; };
  }

  void indexed_property_set( uint32_t index, v8::Local<v8::Value> iValue, const v8::PropertyCallbackInfo<v8::Value>& args ) {
    SS objstream( *v8::String::Utf8Value(args.Data()->ToString()) );
    std::string objtype( objstream.str() );
    v8::Handle<v8::Object> This( args.Holder() );
    v8::Handle<v8::Boolean> ret( JS_BOOL(false) );
    if (objtype=="stringlist") {
      JS_RETURN_ERROR("[indexed_property_set()] ERROR");
    }
    else if (objtype=="domlist") {
      JS_RETURN_ERROR("[indexed_property_set()] ERROR");
    }
    else if (objtype=="namednodemap") {
    }
    else if (objtype=="nodelist") {
      JS_RETURN_ERROR("[indexed_property_set()] ERROR");
    }
    else {
      JS_RETURN_ERROR("[indexed_property_set()] ERROR: unrecognized object type");
    }
    { args.GetReturnValue().Set(JS_BOOL(true)); return; }
  }

  void indexed_property_query( uint32_t index, const v8::PropertyCallbackInfo<v8::Integer>& args ) {
    SS objstream( *v8::String::Utf8Value(args.Data()->ToString()) );
    std::string objtype( objstream.str() );
    v8::Handle<v8::Object> This( args.Holder() );
    bool ret = false;
    XMLSize_t idx = (XMLSize_t)index;
    if (objtype=="stringlist") {
     ZTRY(
      DOMImplementationList * domlist = reinterpret_cast<DOMImplementationList *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      const DOMImplementation * val = domlist->item(idx);
      if (val==NULL) {
        ret = false;
      }
      else {
        ret = true;
      }
     );
    }
    else if (objtype=="stringlist") {
     ZTRY(
      DOMStringList * stringlist = reinterpret_cast<DOMStringList *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      const XMLCh * val = stringlist->item(idx);
      if (val==NULL) {
        ret = false;
      }
      else {
        ret = true;
      }
     );
    }
    else if (objtype=="namednodemap") {
     ZTRY(
      DOMNamedNodeMap * nodemap = reinterpret_cast<DOMNamedNodeMap *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      DOMNode * val = NULL;
      try {
	val = nodemap->item(idx);
      }
      catch( xercesc_3_1::DOMException& e ) {
	char * msg = X(e.getMessage());
	JS_ERROR(msg);
      }
      if (val==NULL) {
	ret = false;
      }
      else {
	ret = true;
      }
     );
    }
    else if (objtype=="nodelist") {
     ZTRY(
      DOMNodeList * nodelist = reinterpret_cast<DOMNodeList *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      DOMNode * val = NULL;
      try {
	val = nodelist->item(idx);
      }
      catch( xercesc_3_1::DOMException& e ) {
	char * msg = X(e.getMessage());
	JS_ERROR(msg);
      }
      if (val==NULL) {
	ret = false;
      }
      else {
	ret = true;
      }
     );
    }
    else {
      JS_ERROR("[indexed_property_get()] ERROR: unrecognized object type");
    }
    { args.GetReturnValue().Set(JS_INT(ret)); return; }
  }

  void indexed_property_delete( uint32_t index, const v8::PropertyCallbackInfo<v8::Boolean>& args ) {
    SS objstream( *v8::String::Utf8Value(args.Data()->ToString()) );
    std::string objtype( objstream.str() );
    v8::Handle<v8::Object> This( args.Holder() );
    v8::Handle<v8::Boolean> ret( JS_BOOL(false) );
    XMLSize_t idx = (XMLSize_t)index;
    if (objtype=="namednodemap") {
      DOMNamedNodeMap * nodemap = reinterpret_cast<DOMNamedNodeMap *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      DOMNode * val = NULL;
      try {
	val = nodemap->item(idx);
	if (val!=NULL) {
	  const XS name = val->getLocalName();
          nodemap->removeNamedItem(name);
	}      
      }
      catch( xercesc_3_1::DOMException& e ) {
	char * msg = X(e.getMessage());
	JS_ERROR(msg);
      }
    }
    else {
      JS_ERROR("[indexed_property_delete()] ERROR: unrecognized object type");
    }
    { args.GetReturnValue().Set(JS_BOOL(true)); return; }
  }

  void indexed_property_enumerate( const v8::PropertyCallbackInfo<v8::Array>& args ) {
    SS objstream( *v8::String::Utf8Value(args.Data()->ToString()) );
    std::string objtype( objstream.str() );
    v8::Handle<v8::Object> This( args.Holder() );
    v8::Handle<v8::Array> ret;
    if (objtype=="domlist") {
     ZTRY(
      DOMImplementationList * domlist = reinterpret_cast<DOMImplementationList *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      XMLSize_t len = domlist->getLength();
      ret = v8::Array::New(JS_ISOLATE, len);
      for (unsigned int i = (int)len; i < len; i++) {
	DOMImplementation * val = domlist->item(i);
	v8::Local<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)val) };
	v8::Handle<v8::Object> tmp(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdom)->GetFunction()->NewInstance(1, fargs) );
	ret->Set(JS_INT(i), tmp);
      }
     );
    }
    else if (objtype=="stringlist") {
     ZTRY(
      DOMStringList * stringlist = reinterpret_cast<DOMStringList *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      XMLSize_t len = stringlist->getLength();
      ret = v8::Array::New(JS_ISOLATE, len);
      for (unsigned int i = (int)len; i < len; i++) {
	const XMLCh * val = stringlist->item(i);
	const char * tmp = X(val);
	ret->Set(JS_INT(i), JS_STR(tmp));
      }
     );
    }
    else if (objtype=="namednodemap") {
     ZTRY(
      DOMNamedNodeMap * nodemap = NULL;
      nodemap = reinterpret_cast<DOMNamedNodeMap *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      if (nodemap!=NULL) {
      XMLSize_t len = nodemap->getLength();
      ret = v8::Array::New(JS_ISOLATE, len);
      for (unsigned int i = (int)len; i < len; i++) {
	DOMNode * val = NULL;
	try { val = nodemap->item(i); } catch( DOMException& e ) { char * msg = X(e.getMessage()); JS_ERROR(msg); }
	if (val!=NULL) {
	  v8::Local<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)val) };
	  v8::Handle<v8::Object> tmp(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
	  ret->Set(JS_INT(i), tmp);
	}
      }
      }
     );
    }
    else if (objtype=="nodelist") {
     ZTRY(
      DOMNodeList * nodelist = reinterpret_cast<DOMNodeList *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      XMLSize_t len = nodelist->getLength();
      ret = v8::Array::New(JS_ISOLATE, len);
      for (unsigned int i = (int)len; i < len; i++) {
	DOMNode * val = nodelist->item(i);
	v8::Local<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)val) };
	v8::Handle<v8::Object> tmp(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
	ret->Set(JS_INT(i), tmp);
      }
     );
    }
    else {
      JS_ERROR("[indexed_property_enumerate()] ERROR: unrecognized object type");
    }
    { args.GetReturnValue().Set(ret); return; };
  }


  //	Named property handlers:
  //		(these enable "hash"-style dereferencing of items in hash-like collections such
  //		 as DOMNamedNodeMap objects, using a string as the index instead of an integer)

  void named_property_get( v8::Local<v8::String> index, const v8::PropertyCallbackInfo<v8::Value>& args ) {
    SS objstream( *v8::String::Utf8Value(args.Data()->ToString()) );
    std::string objtype( objstream.str() );
    v8::Handle<v8::Object> This( args.Holder() );
    SS tmp( *v8::String::Utf8Value(index) );
    const char * name = tmp.str().c_str();
    XS idx = X(name);
    v8::Handle<v8::Value> ret;
    if (objtype=="namednodemap") {
      ZTRY(
	DOMNamedNodeMap * nodemap = reinterpret_cast<DOMNamedNodeMap *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
	DOMNode * val = NULL;
	val = nodemap->getNamedItem(idx);
	if (val==NULL) {
	  ret = v8::Undefined(JS_ISOLATE);
	}
	else {
	  v8::Local<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)val) };
	  ret =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs);
	}
      );
    }
    else if (objtype=="element") {
      ZTRY(
	DOMElement * el = reinterpret_cast<DOMElement *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
	DOMElement * pel = el;
	v8::Local<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)pel) };
	v8::Handle<v8::Object> pobj ( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fpreelement)->GetFunction()->NewInstance(1, fargs) );
	v8::Handle<v8::Value> pval ( pobj->Get(index) );
	XS xval = NULL;
	bool hasAttr = false;
	XTRY( hasAttr = el->hasAttribute(idx); );
	if (hasAttr==false) {
	  ret = pval;
	}
	else {
	  XTRY( xval = (XMLCh *)el->getAttribute(idx); );
	  char * ltmp = X(xval);
	  ret = JS_STR(ltmp);
	}
      );
    }
    else {
      JS_RETURN_ERROR("[named_property_get()] ERROR: unrecognized object type");
    }
    { args.GetReturnValue().Set(ret); return; };
  }

  void named_property_set( v8::Local<v8::String> index, v8::Local<v8::Value> iValue, const v8::PropertyCallbackInfo<v8::Value>& args ) {
    SS objstream( *v8::String::Utf8Value(args.Data()->ToString()) );
    std::string objtype( objstream.str() );
    v8::Handle<v8::Object> This( args.Holder() );
    v8::Handle<v8::Value> ret;
    if (objtype=="namednodemap") {
     ZTRY(
      DOMNamedNodeMap * nodemap = reinterpret_cast<DOMNamedNodeMap *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      DOMNode * node = NULL;
      if (iValue->IsExternal()) {
	node = RECAST(iValue,DOMNode *);
      }
      else if (iValue->IsObject()) {
	node = RECAST(iValue->ToObject()->GetInternalField(0),DOMNode *);
      }
      if (node==NULL) {
	JS_RETURN_ERROR("[named_property_set()] ERROR: \"node\" is a null pointer");
      }
      else {
	DOMNode * retval = NULL;
	XTRY( retval = nodemap->setNamedItem(node); );
	if (retval==NULL) {
	  //JS_RETURN_ERROR("[named_property_set()] ERROR: \"retval\" is a null pointer");
	  { args.GetReturnValue().Set(v8::Null(JS_ISOLATE)); return; }
	}
	else {
	  v8::Local<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)retval) };
	  ret =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs);
	  { args.GetReturnValue().Set(ret); return; };
	}
      }
     );
    }
    else if (objtype=="element") {
     ZTRY(
      DOMElement * el = reinterpret_cast<DOMElement *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      DOMElement * pel = el;
      v8::Local<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)pel) };
      v8::Handle<v8::Object> pobj ( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fpreelement)->GetFunction()->NewInstance(1, fargs) );
      bool pval = pobj->Has(index);
      if ( pval==true ) {
        pobj->Set(index, iValue);
      }
      else {
        XMLSize_t fargc = 2;
        v8::Local<v8::Value> fargv[] = { index, iValue };
        v8::Handle<v8::Function> f( v8::Local<v8::Function>::Cast(pobj->Get(JS_STR("setAttribute"))) );
        f->Call(pobj, fargc, fargv );
      }
     );
    }
    else {
      JS_RETURN_ERROR("[named_property_set()] ERROR: unrecognized object type");
    }
    { args.GetReturnValue().SetUndefined(); return; }
  }

  void named_property_query( v8::Local<v8::String> index, const v8::PropertyCallbackInfo<v8::Value>& args ) {
    SS objstream( *v8::String::Utf8Value(args.Data()->ToString()) );
    std::string objtype( objstream.str() );
    v8::Handle<v8::Object> This( args.Holder() );
    SS tmp( *v8::String::Utf8Value(index) );
    XS idx( X(tmp.str().c_str()) );
    bool exists = false;
    if (objtype=="stringlist") {
     ZTRY(
      DOMStringList * stringlist = reinterpret_cast<DOMStringList *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      exists = stringlist->contains(idx);
     );
    }
    else if (objtype=="namednodemap") {
     ZTRY(
      DOMNamedNodeMap * nodemap = reinterpret_cast<DOMNamedNodeMap *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      DOMNode * node = NULL;
      node = nodemap->getNamedItem(idx);
      if (node==NULL) {
	exists = false;
      }
      else {
        exists = true;
      }
     );
    }
    else if (objtype=="element") {
     ZTRY(
      DOMElement * el = reinterpret_cast<DOMElement *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      DOMElement * pel = el;
      v8::Local<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)pel) };
      v8::Handle<v8::Object> pobj ( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fpreelement)->GetFunction()->NewInstance(1, fargs) );
      bool pval = pobj->Has(index);
      if ( pval==true ) {
        { args.GetReturnValue().Set(JS_BOOL(true)); return; }
      }
      else {
        bool hasAttr = false;
        hasAttr = el->hasAttribute(idx);
        v8::Handle<v8::Boolean> tbool( JS_BOOL(hasAttr) );
        { args.GetReturnValue().Set(tbool); return; }
      }
     );
    }
    else {
      JS_ERROR("[named_property_query()] ERROR: unrecognized object type");
    }
    v8::Handle<v8::Boolean> ret( JS_BOOL(exists) );
    { args.GetReturnValue().Set(ret); return; };
  }

  void named_property_delete( v8::Local<v8::String> index, const v8::PropertyCallbackInfo<v8::Value>& args ) {
    SS objstream( *v8::String::Utf8Value(args.Data()->ToString()) );
    std::string objtype( objstream.str() );
    v8::Handle<v8::Object> This( args.Holder() );
    SS tmp( *v8::String::Utf8Value(index) );
    XS idx( X(tmp.str().c_str()) );
    if (objtype=="namednodemap") {
      DOMNamedNodeMap * nodemap = reinterpret_cast<DOMNamedNodeMap *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      try { nodemap->removeNamedItem(idx); } catch( xercesc_3_1::DOMException& e ) { char * msg = X(e.getMessage()); JS_ERROR(msg); }
    }
    else if (objtype=="element") {
      DOMElement * el = reinterpret_cast<DOMElement *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      try { el->removeAttribute(idx); } catch( xercesc_3_1::DOMException& e ) { char * msg = X(e.getMessage()); JS_ERROR(msg); }
    }
    else {
      JS_ERROR("[named_property_delete()] ERROR: unrecognized object type");
    }
    { args.GetReturnValue().Set(JS_BOOL(true)); return; }
  }

  void named_property_enumerate( const v8::PropertyCallbackInfo<v8::Value>& args ) {
    SS objstream( *v8::String::Utf8Value(args.Data()->ToString()) );
    std::string objtype( objstream.str() );
    v8::Handle<v8::Object> This( args.Holder() );
    v8::Handle<v8::Array> ret;
    if (objtype=="stringlist") {
     ZTRY(
      DOMStringList * stringlist = reinterpret_cast<DOMStringList *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      XMLSize_t len = stringlist->getLength();
      for (unsigned int i = (int)len; i < len; i++) {
	const XMLCh * val = stringlist->item(i);
	const char * tmp = X(val);
	ret->Set(JS_INT(i), JS_STR(tmp));
      }
     );
    }
    else if (objtype=="namednodemap") {
     ZTRY(
      DOMNodeList * nodelist = reinterpret_cast<DOMNodeList *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      XMLSize_t len = nodelist->getLength();
      ret = v8::Array::New(JS_ISOLATE, len);
      for (unsigned int i = (int)len; i < len; i++) {
	DOMNode * val = nodelist->item(i);
	v8::Local<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)val) };
	v8::Handle<v8::Object> tmp(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
	ret->Set(JS_INT(i), tmp);
      }
     );
    }
    else if (objtype=="element") {
      DOMElement * el = reinterpret_cast<DOMElement *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      DOMElement * pel = el;
      v8::Local<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)pel) };
      v8::Handle<v8::Object> pobj ( v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fpreelement)->GetFunction()->NewInstance(1, fargs) );
      v8::Local<v8::Array> arr( pobj->GetPropertyNames() );
	XMLSize_t xlen = arr->Length();
      DOMNamedNodeMap * nodemap = NULL;
      try { nodemap = pel->getAttributes(); } catch( DOMException& e ) { char * msg = X(e.getMessage()); JS_ERROR(msg); }
      if (nodemap==NULL) {
	ret = arr;
      }
      else {
	XMLSize_t tlen = (XMLSize_t)nodemap->getLength();
	XMLSize_t len = tlen + xlen;
	ret = v8::Array::New(JS_ISOLATE, len);
	XMLSize_t i = 0;
	for (i = 0; i < xlen; i++) {
	  v8::Handle<v8::Value> val( arr->Get(JS_INT(i)) );
	  ret->Set(JS_INT(i), val);
	}
	for (i = 0; i < tlen; i++) {
	  DOMNode * val = nodemap->item(i);
	  v8::Local<v8::Value> fargs[] = { v8::External::New(JS_ISOLATE, (void *)val) };
	  v8::Handle<v8::Object> tmp(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction()->NewInstance(1, fargs) );
	  ret->Set(JS_INT((i + xlen)), tmp);
	}
      }
    }
    else {
      JS_ERROR("[named_property_enumerate()] ERROR: unrecognized object type");
    }
    { args.GetReturnValue().Set(ret); return; };
  }


} /* end namespace "xdom" */


SHARED_INIT() {


  // ********************************************************
  // *****	BEGIN [[ DOMException ]]		*****
  // *****						*****

    xdom::fdomexcpt.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domexcpt));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomexcpt)->SetClassName(JS_STR("DOMException"));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomexcpt)->Set(JS_STR("INDEX_SIZE_ERR"),JS_INT((unsigned int)xercesc_3_1::DOMException::INDEX_SIZE_ERR));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomexcpt)->Set(JS_STR("DOMSTRING_SIZE_ERR"),JS_INT((unsigned int)xercesc_3_1::DOMException::DOMSTRING_SIZE_ERR));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomexcpt)->Set(JS_STR("HIERARCHY_REQUEST_ERR"),JS_INT((unsigned int)xercesc_3_1::DOMException::HIERARCHY_REQUEST_ERR));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomexcpt)->Set(JS_STR("WRONG_DOCUMENT_ERR"),JS_INT((unsigned int)xercesc_3_1::DOMException::WRONG_DOCUMENT_ERR));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomexcpt)->Set(JS_STR("INVALID_CHARACTER_ERR"),JS_INT((unsigned int)xercesc_3_1::DOMException::INVALID_CHARACTER_ERR));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomexcpt)->Set(JS_STR("NO_DATA_ALLOWED_ERR"),JS_INT((unsigned int)xercesc_3_1::DOMException::NO_DATA_ALLOWED_ERR));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomexcpt)->Set(JS_STR("NO_MODIFICATION_ALLOWED_ERR"),JS_INT((unsigned int)xercesc_3_1::DOMException::NO_MODIFICATION_ALLOWED_ERR));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomexcpt)->Set(JS_STR("NOT_FOUND_ERR"),JS_INT((unsigned int)xercesc_3_1::DOMException::NOT_FOUND_ERR));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomexcpt)->Set(JS_STR("NOT_SUPPORTED_ERR"),JS_INT((unsigned int)xercesc_3_1::DOMException::NOT_SUPPORTED_ERR));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomexcpt)->Set(JS_STR("INUSE_ATTRIBUTE_ERR"),JS_INT((unsigned int)xercesc_3_1::DOMException::INUSE_ATTRIBUTE_ERR));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomexcpt)->Set(JS_STR("INVALID_STATE_ERR"),JS_INT((unsigned int)xercesc_3_1::DOMException::INVALID_STATE_ERR));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomexcpt)->Set(JS_STR("SYNTAX_ERR"),JS_INT((unsigned int)xercesc_3_1::DOMException::SYNTAX_ERR));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomexcpt)->Set(JS_STR("INVALID_MODIFICATION_ERR"),JS_INT((unsigned int)xercesc_3_1::DOMException::INVALID_MODIFICATION_ERR));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomexcpt)->Set(JS_STR("NAMESPACE_ERR"),JS_INT((unsigned int)xercesc_3_1::DOMException::NAMESPACE_ERR));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomexcpt)->Set(JS_STR("INVALID_ACCESS_ERR"),JS_INT((unsigned int)xercesc_3_1::DOMException::INVALID_ACCESS_ERR));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomexcpt)->Set(JS_STR("VALIDATION_ERR"),JS_INT((unsigned int)xercesc_3_1::DOMException::VALIDATION_ERR));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomexcpt)->Set(JS_STR("TYPE_MISMATCH_ERR"),JS_INT((unsigned int)xercesc_3_1::DOMException::TYPE_MISMATCH_ERR));

    v8::Handle<v8::ObjectTemplate> domexcptt =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomexcpt)->InstanceTemplate();
    domexcptt->SetInternalFieldCount(1);
    domexcptt->Set(JS_STR("~DOMException"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domexcpt_destructor));
    /**
     * DOMException property accessors
     */
    domexcptt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMException"));

    v8::Handle<v8::Template> pdomexcpt =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomexcpt)->PrototypeTemplate();

  // *****						*****
  // *****	END   [[ DOMException ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMLSException ]]		*****
  // *****						*****

    xdom::fdomlsexcpt.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsexcpt));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomlsexcpt)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomexcpt));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomlsexcpt)->SetClassName(JS_STR("DOMLSException"));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomlsexcpt)->Set(JS_STR("PARSE_ERR"),JS_INT((unsigned int)xercesc_3_1::DOMLSException::PARSE_ERR));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomlsexcpt)->Set(JS_STR("SERIALIZE_ERR"),JS_INT((unsigned int)xercesc_3_1::DOMLSException::SERIALIZE_ERR));

    v8::Handle<v8::ObjectTemplate> domlsexcptt =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomlsexcpt)->InstanceTemplate();
    domlsexcptt->SetInternalFieldCount(1);
    domlsexcptt->Set(JS_STR("~DOMLSException"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsexcpt_destructor));
    /**
     * DOMLSException property accessors
     */
    domlsexcptt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMLSException"));

    v8::Handle<v8::Template> pdomlsexcpt =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomlsexcpt)->PrototypeTemplate();

  // *****						*****
  // *****	END   [[ DOMLSException ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMImplementationList ]]	*****
  // *****						*****

    xdom::fdomlist.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlist));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomlist)->SetClassName(JS_STR("DOMImplementationList"));

    v8::Handle<v8::ObjectTemplate> domlistt =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomlist)->InstanceTemplate();
    domlistt->SetInternalFieldCount(1);
    domlistt->Set(JS_STR("~DOMImplementationList"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlist_destructor));
    domlistt->SetAccessor(JS_STR("length"), xdom::get_property);

    v8::Handle<v8::String> fdomlistdata( JS_STR("domlist") );
    domlistt->SetIndexedPropertyHandler(xdom::indexed_property_get, xdom::indexed_property_set, xdom::indexed_property_query, xdom::indexed_property_delete, xdom::indexed_property_enumerate, fdomlistdata);
    /**
     * DOMImplementationList property accessors
     */
    domlistt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMImplementationList"));

    v8::Handle<v8::Template> pdomlist =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomlist)->PrototypeTemplate();
    pdomlist->Set(JS_STR("item"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlistitem));
    pdomlist->Set(JS_STR("getLength"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlistgetlength));

  // *****						*****
  // *****	END   [[ DOMImplementationList ]]	*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMImplementationSource ]]	*****
  // *****						*****

    xdom::fdomsource.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domsource));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomsource)->SetClassName(JS_STR("DOMImplementationSource"));

    v8::Handle<v8::ObjectTemplate> domsourcet =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomsource)->InstanceTemplate();
    domsourcet->SetInternalFieldCount(1);
    domsourcet->Set(JS_STR("~DOMImplementationSource"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domsource_destructor));
    /**
     * DOMImplementationSource property accessors
     */
    domsourcet->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMImplementationSource"));

    v8::Handle<v8::Template> pdomsource =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomsource)->PrototypeTemplate();
    pdomsource->Set(JS_STR("getDOMImplementation"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domsourcegetdomimplementation));
    pdomsource->Set(JS_STR("getDOMImplementationList"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domsourcegetdomimplementationlist));

  // *****						*****
  // *****	END   [[ DOMImplementationSource ]]	*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMLocator ]]			*****
  // *****						*****

    xdom::fdomlocator.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlocator));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomlocator)->SetClassName(JS_STR("DOMLocator"));

    v8::Handle<v8::ObjectTemplate> domlocatort =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomlocator)->InstanceTemplate();
    domlocatort->SetInternalFieldCount(1);
    domlocatort->Set(JS_STR("~DOMLocator"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlocator_destructor));

    /**
     * DOMLocator property accessors
     */
    domlocatort->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMLocator"));
    domlocatort->SetAccessor(JS_STR("lineNumber"), xdom::get_property);
    domlocatort->SetAccessor(JS_STR("columnNumber"), xdom::get_property);
    domlocatort->SetAccessor(JS_STR("byteOffset"), xdom::get_property);
    domlocatort->SetAccessor(JS_STR("utf16Offset"), xdom::get_property);
    domlocatort->SetAccessor(JS_STR("relatedNode"), xdom::get_property);
    domlocatort->SetAccessor(JS_STR("uri"), xdom::get_property);

    v8::Handle<v8::Template> pdomlocator =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomlocator)->PrototypeTemplate();
    pdomlocator->Set(JS_STR("getLineNumber"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlocatorgetlinenumber));
    pdomlocator->Set(JS_STR("getColumnNumber"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlocatorgetcolumnnumber));
    pdomlocator->Set(JS_STR("getByteOffset"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlocatorgetbyteoffset));
    pdomlocator->Set(JS_STR("getUtf16Offset"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlocatorgetutf16offset));
    pdomlocator->Set(JS_STR("getRelatedNode"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlocatorgetrelatednode));
    pdomlocator->Set(JS_STR("getURI"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlocatorgeturi));
    

  // *****						*****
  // *****	END   [[ DOMLocator ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMImplementationRegistry ]]	*****
  // *****						*****

    xdom::fdomreg.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domreg));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomreg)->SetClassName(JS_STR("DOMImplementationRegistry"));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomreg)->Set(JS_STR("getDOMImplementation"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domreggetdomimplementation));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomreg)->Set(JS_STR("getDOMImplementationList"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domreggetdomimplementationlist));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomreg)->Set(JS_STR("addSource"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domregaddsource));

    v8::Handle<v8::ObjectTemplate> domregt =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomreg)->InstanceTemplate();
    domregt->SetInternalFieldCount(1);
    domregt->Set(JS_STR("~DOMImplementationRegistry"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domreg_destructor));
    /**
     * DOMImplementationRegistry property accessors
     */
    domregt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMImplementationRegistry"));

    v8::Handle<v8::Template> pdomreg =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomreg)->PrototypeTemplate();

  // *****						*****
  // *****	END   [[ DOMImplementationRegistry ]]	*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMImplementation ]]		*****
  // *****						*****

    //v8::Handle<v8::FunctionTemplate> fdom = v8::FunctionTemplate::New(JS_ISOLATE, xdom::_impl) ;
    xdom::fdom.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_impl));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdom)->SetClassName(JS_STR("DOMImplementation"));

    v8::Handle<v8::ObjectTemplate> domt =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdom)->InstanceTemplate();
    domt->SetInternalFieldCount(1);
    /**
     * DOMImplementation property accessors
     */
    domt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMImplementation"));
    domt->Set(JS_STR("~DOMImplementation"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_impl_destructor));

    v8::Handle<v8::Template> pt =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdom)->PrototypeTemplate();
    /**
     *	DOMImplementation prototype methods
     */
    pt->Set(JS_STR("getImplementation"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domgetimplementation));
    pt->Set(JS_STR("loadDOMExceptionMsg"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domloaddomexceptionmsg));
    pt->Set(JS_STR("hasFeature"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domhasfeature));
    pt->Set(JS_STR("createDocumentType"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domcreatedocumenttype));
    pt->Set(JS_STR("createDocType"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domcreatedocumenttype));
    pt->Set(JS_STR("createDocument"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domcreatedocument));
    pt->Set(JS_STR("createParser"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domcreateparser));
    pt->Set(JS_STR("createImplementationLS"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domcreateimplementationls));


  // *****						*****
  // *****	END   [[ DOMImplementation ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMImplementationLS ]]		*****
  // *****						*****

    //v8::Handle<v8::FunctionTemplate> fdom = v8::FunctionTemplate::New(JS_ISOLATE, xdom::_impl) ;
    xdom::fdomls.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_implls));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomls)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdom));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomls)->SetClassName(JS_STR("DOMImplementationLS"));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomls)->Set(JS_STR("MODE_ASYNCHRONOUS"),JS_INT((unsigned int)xercesc_3_1::DOMImplementationLS::MODE_ASYNCHRONOUS));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomls)->Set(JS_STR("MODE_SYNCHRONOUS"),JS_INT((unsigned int)xercesc_3_1::DOMImplementationLS::MODE_SYNCHRONOUS));

    v8::Handle<v8::ObjectTemplate> domlst =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomls)->InstanceTemplate();
    domlst->SetInternalFieldCount(1);
    domlst->Set(JS_STR("~DOMImplementationLS"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_implls_destructor));
    /**
     * DOMImplementationLS property accessors
     */
    domlst->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMImplementationLS"));

    v8::Handle<v8::Template> plst =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomls)->PrototypeTemplate();
    /**
     * DOMImplementationLS prototype methods
     */
    plst->Set(JS_STR("createLSParser"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_impllscreatelsparser));
    plst->Set(JS_STR("createLSSerializer"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_impllscreatelsserializer));
    plst->Set(JS_STR("createLSOutput"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_impllscreatelsoutput));
    plst->Set(JS_STR("createLSInput"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_impllscreatelsinput));

  // *****						*****
  // *****	END   [[ DOMImplementationLS ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMLSParser ]]			*****
  // *****						*****

    // v8::Handle<v8::FunctionTemplate> fparser = v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parser);
    xdom::fparser.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parser));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fparser)->SetClassName(JS_STR("DOMLSParser"));

    v8::Handle<v8::ObjectTemplate> tparser = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fparser)->InstanceTemplate();
    tparser->SetInternalFieldCount(2);
    tparser->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMLSParser"));

    v8::Handle<v8::Template> parsert = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fparser)->PrototypeTemplate();

    /**
     * DOMLSParser property accessors
     */
    tparser->SetAccessor(JS_STR("domConfig"), xdom::get_property);
    tparser->SetAccessor(JS_STR("filter"), xdom::get_property, xdom::set_property);
    tparser->SetAccessor(JS_STR("async"), xdom::get_property);
    tparser->SetAccessor(JS_STR("grammar"), xdom::get_property);
    tparser->SetAccessor(JS_STR("rootGrammar"), xdom::get_property);
    tparser->SetAccessor(JS_STR("uriText"), xdom::get_property);
    tparser->SetAccessor(JS_STR("uri"), xdom::get_property);
    tparser->SetAccessor(JS_STR("srcOffset"), xdom::get_property);
    tparser->SetAccessor(JS_STR("implementation"), xdom::get_property);

    /**
     * DOMLSParser prototype methods
     */
    tparser->Set(JS_STR("~DOMLSParser"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parser_destructor));
    parsert->Set(JS_STR("getDomConfig"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parsergetdomconfig));
    parsert->Set(JS_STR("getFilter"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parsergetfilter));
    parsert->Set(JS_STR("getAsync"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parsergetasync));
    parsert->Set(JS_STR("getBusy"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parsergetbusy));
    parsert->Set(JS_STR("setFilter"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parsersetfilter));
    parsert->Set(JS_STR("parse"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parserparse));
    parsert->Set(JS_STR("parseURI"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parserparseuri));
    parsert->Set(JS_STR("parseWithContext"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parserparsewithcontext));
    parsert->Set(JS_STR("abort"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parserabort));
    parsert->Set(JS_STR("resetDocumentPool"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parserresetdocumentpool));
    parsert->Set(JS_STR("loadGrammar"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parserloadgrammar));
    parsert->Set(JS_STR("getGrammar"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parsergetgrammar));
    parsert->Set(JS_STR("getRootGrammar"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parsergetrootgrammar));
    parsert->Set(JS_STR("getURIText"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parsergeturitext));
    parsert->Set(JS_STR("resetCachedGrammarPool"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parserresetcachedgrammarpool));
    parsert->Set(JS_STR("getSrcOffset"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parsergetsrcoffset));
    parsert->Set(JS_STR("getImplementation"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parsergetimplementation));

  // *****						*****
  // *****	END   [[ DOMLSParser ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMNodeFilter ]]		*****
  // *****						*****

    xdom::fnodefilter.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodefilter));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnodefilter)->SetClassName(JS_STR("DOMNodeFilter"));

    v8::Handle<v8::ObjectTemplate> tnodefilter =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnodefilter)->InstanceTemplate();
    tnodefilter->SetInternalFieldCount(1);
    tnodefilter->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMNodeFilter"));

    v8::Handle<v8::Template> pnodefilter =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnodefilter)->PrototypeTemplate();
    /**
     *	DOMNodeFilter prototype methods
     */
    tnodefilter->Set(JS_STR("~DOMNodeFilter"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodefilter_destructor));
    pnodefilter->Set(JS_STR("acceptNode"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodefilteracceptnode));

  // *****						*****
  // *****	END   [[ DOMNodeFilter ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMLSParserFilter ]]		*****
  // *****						*****

    xdom::fparserfilter.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parserfilter));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fparserfilter)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnodefilter));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fparserfilter)->SetClassName(JS_STR("DOMLSParserFilter"));

    v8::Handle<v8::ObjectTemplate> tparserfilter = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fparserfilter)->InstanceTemplate();
    tparserfilter->SetInternalFieldCount(1);
    tparserfilter->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMLSParserFilter"));

    v8::Handle<v8::Template> pparserfilter = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fparserfilter)->PrototypeTemplate();
    /**
     *	DOMLSParserFilter prototype methods
     */
    tparserfilter->Set(JS_STR("~DOMLSParserFilter"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parserfilter_destructor));
    pparserfilter->Set(JS_STR("startElement"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parserfilterstartelement));
    pparserfilter->Set(JS_STR("getWhatToShow"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_parserfiltergetwhattoshow));


  // *****						*****
  // *****	END   [[ DOMLSParserFilter ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMLSSerializer ]]		*****
  // *****						*****

    xdom::fserializer.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_serializer));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fserializer)->SetClassName(JS_STR("DOMLSSerializer"));

    v8::Handle<v8::ObjectTemplate> tserializer = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fserializer)->InstanceTemplate();
    tserializer->SetInternalFieldCount(2);
    tserializer->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMLSSerializer"));
    tserializer->Set(JS_STR("~DOMLSSerializer"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_serializer_destructor));

    v8::Handle<v8::Template> pserializer = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fserializer)->PrototypeTemplate();
    pserializer->Set(JS_STR("getDomConfig"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_serializergetdomconfig));
    pserializer->Set(JS_STR("setNewLine"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_serializersetnewline));
    pserializer->Set(JS_STR("setFilter"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_serializersetfilter));
    pserializer->Set(JS_STR("getNewLine"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_serializergetnewline));
    pserializer->Set(JS_STR("getFilter"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_serializergetfilter));
    pserializer->Set(JS_STR("write"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_serializerwrite));
    pserializer->Set(JS_STR("writeToURI"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_serializerwritetouri));
    pserializer->Set(JS_STR("writeToString"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_serializerwritetostring));

  // *****						*****
  // *****	END   [[ DOMLSSerializer ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMLSSerializerFilter ]]	*****
  // *****						*****

    // v8::Handle<v8::FunctionTemplate> fserializerfilter = v8::FunctionTemplate::New(JS_ISOLATE, xdom::_serializer);
    xdom::fserializerfilter.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_serializerfilter));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fserializerfilter)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnodefilter));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fserializerfilter)->SetClassName(JS_STR("DOMLSSerializerFilter"));

    v8::Handle<v8::ObjectTemplate> tserializerfilter = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fserializerfilter)->InstanceTemplate();
    tserializerfilter->SetInternalFieldCount(1);
    tserializerfilter->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMLSSerializerFilter"));

    v8::Handle<v8::Template> pserializerfilter = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fserializerfilter)->PrototypeTemplate();
    /**
     *	DOMLSSerializerFilter prototype methods
     */
    tserializerfilter->Set(JS_STR("~DOMLSSerializerFilter"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_serializerfilter_destructor));
    pserializerfilter->Set(JS_STR("getWhatToShow"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_serializerfiltergetwhattoshow));

  // *****						*****
  // *****	END   [[ DOMLSSerializerFilter ]]	*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMLSInput ]]			*****
  // *****						*****

    xdom::fdomlsinput.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsinput));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomlsinput)->SetClassName(JS_STR("DOMLSInput"));

    v8::Handle<v8::Template> pdomlsinput =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomlsinput)->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> domlsinputt =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomlsinput)->InstanceTemplate();
    domlsinputt->SetInternalFieldCount(2);
    domlsinputt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMLSInput"));

    /**
     * DOMLSInput prototype methods
     */
    domlsinputt->Set(JS_STR("~DOMLSInput"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsinput_destructor));
    pdomlsinput->Set(JS_STR("getStringData"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsinputgetstringdata));
    pdomlsinput->Set(JS_STR("getByteStream"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsinputgetbytestream));
    pdomlsinput->Set(JS_STR("getEncoding"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsinputgetencoding));
    pdomlsinput->Set(JS_STR("getPublicId"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsinputgetpublicid));
    pdomlsinput->Set(JS_STR("getSystemId"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsinputgetsystemid));
    pdomlsinput->Set(JS_STR("getBaseURI"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsinputgetbaseuri));
    pdomlsinput->Set(JS_STR("setStringData"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsinputsetstringdata));
    pdomlsinput->Set(JS_STR("setByteStream"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsinputsetbytestream));
    pdomlsinput->Set(JS_STR("setEncoding"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsinputsetencoding));
    pdomlsinput->Set(JS_STR("setPublicId"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsinputsetpublicid));
    pdomlsinput->Set(JS_STR("setSystemId"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsinputsetsystemid));
    pdomlsinput->Set(JS_STR("setBaseURI"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsinputsetbaseuri));
    pdomlsinput->Set(JS_STR("setIssueFatalErrorIfNotFound"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsinputsetissuefatalerrorifnotfound));
    pdomlsinput->Set(JS_STR("getIssueFatalErrorIfNotFound"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsinputgetissuefatalerrorifnotfound));

  // *****						*****
  // *****	END   [[ DOMLSInput ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMLSOutput ]]			*****
  // *****						*****

    xdom::foutput.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsoutput));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::foutput)->SetClassName(JS_STR("DOMLSOutput"));

    v8::Handle<v8::ObjectTemplate> toutput = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::foutput)->InstanceTemplate();
    toutput->SetInternalFieldCount(2);
    toutput->Set(JS_STR("~DOMLSOutput"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsoutput_destructor));
    toutput->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMLSOutput"));

    v8::Handle<v8::Template> poutput = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::foutput)->PrototypeTemplate();
    poutput->Set(JS_STR("getByteStream"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsoutputgetbytestream));
    poutput->Set(JS_STR("getEncoding"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsoutputgetencoding));
    poutput->Set(JS_STR("getSystemId"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsoutputgetsystemid));
    poutput->Set(JS_STR("setByteStream"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsoutputsetbytestream));
    poutput->Set(JS_STR("setEncoding"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsoutputsetencoding));
    poutput->Set(JS_STR("setSystemId"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domlsoutputsetsystemid));

  // *****						*****
  // *****	END   [[ DOMLSOutput ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ XMLFormatTarget ]]		*****
  // *****						*****

/*
    xdom::fformattarget.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_outputtarget));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fformattarget)->Inherit(xdom::fxmemory);
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fformattarget)->SetClassName(JS_STR("XMLFormatTarget"));

    v8::Handle<v8::ObjectTemplate> tformattarget = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fformattarget)->InstanceTemplate();
    tformattarget->SetInternalFieldCount(1);
    tformattarget->Set(JS_STR("~XMLFormatTarget"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_formattarget_destructor));
    tformattarget->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("XMLFormatTarget"));

    v8::Handle<v8::Template> pformattarget = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fformattarget)->PrototypeTemplate();
    pformattarget->Set(JS_STR("writeChars"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_formattargetwritechars));
    pformattarget->Set(JS_STR("flush"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_formattargetflush));

*/

  // *****						*****
  // *****	END   [[ XMLFormatTarget ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ v8::LocalFileFormatTarget ]]	*****
  // *****						*****

/*
    xdom::ffiletarget.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_filetarget));
    xdom::ffiletarget->Inherit(xdom::fformattarget);
    xdom::ffiletarget->SetClassName(JS_STR("v8::LocalFileFormatTarget"));

    v8::Handle<v8::ObjectTemplate> tfiletarget = xdom::ffiletarget->InstanceTemplate();
    tfiletarget->SetInternalFieldCount(1);
    tfiletarget->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("v8::LocalFileFormatTarget"));
    tfiletarget->Set(JS_STR("~v8::LocalFileFormatTarget"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_filetarget_destructor));

    v8::Handle<v8::Template> pfiletarget = xdom::ffiletarget->PrototypeTemplate();

*/

  // *****						*****
  // *****	END   [[ v8::LocalFileFormatTarget ]]	*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ MemBufFormatTarget ]]		*****
  // *****						*****

/*
    xdom::fmembuftarget.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_membuftarget));
    xdom::fmembuftarget->Inherit(xdom::fformattarget);
    xdom::fmembuftarget->SetClassName(JS_STR("MemBufFormatTarget"));

    v8::Handle<v8::ObjectTemplate> tmembuftarget = xdom::fmembuftarget->InstanceTemplate();
    tmembuftarget->SetInternalFieldCount(1);
    tmembuftarget->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("MemBufFormatTarget"));
    tmembuftarget->Set(JS_STR("~MemBufFormatTarget"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_membuftarget_destructor));

    v8::Handle<v8::Template> pmembuftarget = xdom::fmembuftarget->PrototypeTemplate();
    pmembuftarget->Set(JS_STR("getRawBuffer"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_membuftargetgetrawbuffer));
    pmembuftarget->Set(JS_STR("getLen"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_membuftargetgetlen));
*/

  // *****						*****
  // *****	END   [[ MemBufFormatTarget ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ StdOutFormatTarget ]]		*****
  // *****						*****

/*
    xdom::fstdouttarget.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_stdouttarget));
    xdom::fstdouttarget->Inherit(xdom::fformattarget);
    xdom::fstdouttarget->SetClassName(JS_STR("StdOutFormatTarget"));

    v8::Handle<v8::ObjectTemplate> tstdouttarget = xdom::fstdouttarget->InstanceTemplate();
    tstdouttarget->SetInternalFieldCount(1);
    t->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("StdOutFormatTarget"));
    tstdouttarget->Set(JS_STR("~StdOutFormatTarget"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_stdouttarget_destructor));

    v8::Handle<v8::Template> pstdouttarget = xdom::fstdouttarget->PrototypeTemplate();
*/

  // *****						*****
  // *****	END   [[ StdOutFormatTarget ]]		*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ DOMStringList ]]		*****
  // *****						*****

    xdom::fstringlist.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_stringlist));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fstringlist)->SetClassName(JS_STR("DOMStringList"));

    v8::Handle<v8::ObjectTemplate> stringlistt = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fstringlist)->InstanceTemplate();
    stringlistt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMStringList"));
    stringlistt->SetInternalFieldCount(1);

    stringlistt->SetAccessor(JS_STR("length"), xdom::get_property);

    v8::Handle<v8::String> fstringlistdata( JS_STR("stringlist") );
    stringlistt->SetIndexedPropertyHandler(xdom::indexed_property_get, xdom::indexed_property_set, xdom::indexed_property_query, xdom::indexed_property_delete, xdom::indexed_property_enumerate, fstringlistdata);
    //stringlistt->SetNamedPropertyv8::Handler(xdom::named_property_get, NULL, xdom::named_property_query, NULL, xdom::named_property_enumerate, fstringlistdata);

    v8::Handle<v8::Template> tstringlist = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fstringlist)->PrototypeTemplate();
    //	DOMStringList prototype methods
    stringlistt->Set(JS_STR("~DOMStringList"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_stringlist_destructor));
    tstringlist->Set(JS_STR("item"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_stringlistitem));
    tstringlist->Set(JS_STR("getLength"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_stringlistgetlength));
    tstringlist->Set(JS_STR("contains"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_stringlistcontains));

  // *****						*****
  // *****	END   [[ DOMStringList ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMNamedNodeMap ]]		*****
  // *****						*****

    xdom::fnamednodemap.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_namednodemap));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnamednodemap)->SetClassName(JS_STR("DOMNamedNodeMap"));
    v8::Handle<v8::ObjectTemplate> namednodemapt = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnamednodemap)->InstanceTemplate();
    namednodemapt->SetInternalFieldCount(1);
    namednodemapt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMNamedNodeMap"));

    namednodemapt->SetAccessor(JS_STR("length"), xdom::get_property);
    namednodemapt->SetAccessor(JS_STR("Length"), xdom::get_property);

    v8::Handle<v8::String> fnamednodemapdata( JS_STR("namednodemap") );
    namednodemapt->SetIndexedPropertyHandler(xdom::indexed_property_get, xdom::indexed_property_set, xdom::indexed_property_query, xdom::indexed_property_delete, xdom::indexed_property_enumerate, fnamednodemapdata);
    //namednodemapt->SetNamedPropertyv8::Handler(xdom::named_property_get, xdom::named_property_set, xdom::named_property_query, xdom::named_property_delete, xdom::named_property_enumerate, fnamednodemapdata);
    //namednodemapt->SetIndexedPropertyHandler(xdom::indexed_property_get, NULL, xdom::indexed_property_query, NULL, xdom::indexed_property_enumerate, fnamednodemapdata);
    //namednodemapt->SetNamedPropertyv8::Handler(xdom::named_property_get, NULL, xdom::named_property_query, NULL, xdom::named_property_enumerate, fnamednodemapdata);

    v8::Handle<v8::ObjectTemplate> tnamednodemap = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnamednodemap)->PrototypeTemplate();
    //	DOMNamedNodeMap prototype methods
    namednodemapt->Set(JS_STR("~DOMNamedNodeMap"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_namednodemap_destructor));
    tnamednodemap->Set(JS_STR("item"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodemapitem));
    tnamednodemap->Set(JS_STR("getLength"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodemapgetlength));
    tnamednodemap->Set(JS_STR("getNamedItem"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodemapgetnameditem));
    tnamednodemap->Set(JS_STR("getNamedItemNS"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodemapgetnameditemns));
    tnamednodemap->Set(JS_STR("setNamedItem"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodemapsetnameditem));
    tnamednodemap->Set(JS_STR("setNamedItemNS"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodemapsetnameditemns));
    tnamednodemap->Set(JS_STR("removeNamedItem"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodemapremovenameditem));
    tnamednodemap->Set(JS_STR("removeNamedItemNS"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodemapremovenameditemns));

  // *****						*****
  // *****	END   [[ DOMNamedNodeMap ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMNodeList ]]			*****
  // *****						*****

    xdom::fnodelist.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodelist));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnodelist)->SetClassName(JS_STR("DOMNodeList"));

    v8::Handle<v8::String> fnodelistdata( JS_STR("nodelist") );

    v8::Handle<v8::ObjectTemplate> nodelistt =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnodelist)->InstanceTemplate();
    nodelistt->SetInternalFieldCount(1);
    nodelistt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMNodeList"));
    nodelistt->SetAccessor(JS_STR("length"), xdom::get_property);
    nodelistt->SetIndexedPropertyHandler(xdom::indexed_property_get, xdom::indexed_property_set, xdom::indexed_property_query, xdom::indexed_property_delete, xdom::indexed_property_enumerate, fnodelistdata);

    v8::Handle<v8::Template> pnodelist =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnodelist)->PrototypeTemplate();
    //	DOMNodeList prototype methods
    nodelistt->Set(JS_STR("~DOMNodeList"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodelist_destructor));
    pnodelist->Set(JS_STR("item"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodelistitem));
    pnodelist->Set(JS_STR("getLength"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodelistgetlength));
    pnodelist->Set(JS_STR("toArray"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodelisttoarray));

  // *****						*****
  // *****	END   [[ DOMNodeList ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMUserDataHandler ]]		*****
  // *****						*****

    xdom::fuserdatahandler.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domuserdatahandler));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fuserdatahandler)->SetClassName(JS_STR("DOMUserDataHandler"));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fuserdatahandler)->Set(JS_STR("NODE_CLONED"), JS_INT(xercesc_3_1::DOMUserDataHandler::NODE_CLONED));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fuserdatahandler)->Set(JS_STR("NODE_IMPORTED"), JS_INT(xercesc_3_1::DOMUserDataHandler::NODE_IMPORTED));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fuserdatahandler)->Set(JS_STR("NODE_DELETED"), JS_INT(xercesc_3_1::DOMUserDataHandler::NODE_DELETED));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fuserdatahandler)->Set(JS_STR("NODE_RENAMED"), JS_INT(xercesc_3_1::DOMUserDataHandler::NODE_RENAMED));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fuserdatahandler)->Set(JS_STR("NODE_ADOPTED"), JS_INT(xercesc_3_1::DOMUserDataHandler::NODE_ADOPTED));

    v8::Handle<v8::ObjectTemplate> userdatahandlert = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fuserdatahandler)->InstanceTemplate();
    userdatahandlert->SetInternalFieldCount(2);
    userdatahandlert->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMUserDataHandler"));

    v8::Handle<v8::Template> puserdatahandler = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fuserdatahandler)->PrototypeTemplate();

    //	DOMUserDataHandler prototype methods
    userdatahandlert->Set(JS_STR("~DOMUserDataHandler"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domuserdatahandler_destructor));
    puserdatahandler->Set(JS_STR("handle"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domuserdatahandlerhandle));

  // *****						*****
  // *****	END   [[ DOMUserDataHandler ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMConfiguration ]]		*****
  // *****						*****

    xdom::fdomconfiguration.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domconfiguration));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomconfiguration)->SetClassName(JS_STR("DOMConfiguration"));

    v8::Handle<v8::ObjectTemplate> domconfigurationt =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomconfiguration)->InstanceTemplate();
    domconfigurationt->SetInternalFieldCount(1);
    domconfigurationt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMConfiguration"));
    domconfigurationt->SetAccessor(JS_STR("parameterNames"), xdom::get_property, NULL, JS_STR("DOMConfiguration"));

    /**
     * Static property, useful for stats gathering
     */
    domconfigurationt->Set(JS_STR("childCount"), JS_INT(1));

    v8::Handle<v8::ObjectTemplate> tdomconfiguration =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomconfiguration)->PrototypeTemplate();

    /**
     * DOM prototype methods (new Document().*)
     */
    domconfigurationt->Set(JS_STR("~DOMConfiguration"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domconfiguration_destructor));
    tdomconfiguration->Set(JS_STR("getParameter"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domconfiggetparameter));
    tdomconfiguration->Set(JS_STR("setParameter"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domconfigsetparameter));
    tdomconfiguration->Set(JS_STR("canSetParameter"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domconfigcansetparameter));
    tdomconfiguration->Set(JS_STR("getParameterNames"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domconfiggetparameternames));

  // *****						*****
  // *****	END   [[ DOMConfiguration ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMNode ]]			*****
  // *****						*****

    xdom::fnode.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domnode));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->SetClassName(JS_STR("DOMNode"));

    v8::Handle<v8::ObjectTemplate> nodet(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->InstanceTemplate() );
    nodet->SetInternalFieldCount(1);
    nodet->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMNode"));

    v8::Handle<v8::Template> pnode(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->PrototypeTemplate() );

    /*	*
	*	Emulate enumerated types by setting static property values
	*	for this class on its FunctionTemplate:
	*	(see "http://xerces.apache.org/xerces-c/apiDocs-3/classDOMTypeInfo.html" for enumerated values)
     *	*/
      // "NodeType":
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->Set(JS_STR("ELEMENT_NODE"), JS_INT(xercesc_3_1::DOMNode::ELEMENT_NODE));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->Set(JS_STR("ATTRIBUTE_NODE"), JS_INT(xercesc_3_1::DOMNode::ATTRIBUTE_NODE));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->Set(JS_STR("TEXT_NODE"), JS_INT(xercesc_3_1::DOMNode::TEXT_NODE));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->Set(JS_STR("CDATA_SECTION_NODE"), JS_INT(xercesc_3_1::DOMNode::CDATA_SECTION_NODE));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->Set(JS_STR("ENTITY_REFERENCE_NODE"), JS_INT(xercesc_3_1::DOMNode::ENTITY_REFERENCE_NODE));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->Set(JS_STR("ENTITY_NODE"), JS_INT(xercesc_3_1::DOMNode::ENTITY_NODE));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->Set(JS_STR("PROCESSING_INSTRUCTION_NODE"), JS_INT(xercesc_3_1::DOMNode::PROCESSING_INSTRUCTION_NODE));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->Set(JS_STR("COMMENT_NODE"), JS_INT(xercesc_3_1::DOMNode::COMMENT_NODE));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->Set(JS_STR("DOCUMENT_NODE"), JS_INT(xercesc_3_1::DOMNode::DOCUMENT_NODE));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->Set(JS_STR("DOCUMENT_TYPE_NODE"), JS_INT(xercesc_3_1::DOMNode::DOCUMENT_TYPE_NODE));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->Set(JS_STR("DOCUMENT_FRAGMENT_NODE"), JS_INT(xercesc_3_1::DOMNode::DOCUMENT_FRAGMENT_NODE));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->Set(JS_STR("NOTATION_NODE"), JS_INT(xercesc_3_1::DOMNode::NOTATION_NODE));
      // "DocumentPosition":
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->Set(JS_STR("DOCUMENT_POSITION_DISCONNECTED"), JS_INT(xercesc_3_1::DOMNode::DOCUMENT_POSITION_DISCONNECTED));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->Set(JS_STR("DOCUMENT_POSITION_PRECEDING"), JS_INT(xercesc_3_1::DOMNode::DOCUMENT_POSITION_PRECEDING));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->Set(JS_STR("DOCUMENT_POSITION_FOLLOWING"), JS_INT(xercesc_3_1::DOMNode::DOCUMENT_POSITION_FOLLOWING));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->Set(JS_STR("DOCUMENT_POSITION_CONTAINS"), JS_INT(xercesc_3_1::DOMNode::DOCUMENT_POSITION_CONTAINS));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->Set(JS_STR("DOCUMENT_POSITION_CONTAINED_BY"), JS_INT(xercesc_3_1::DOMNode::DOCUMENT_POSITION_CONTAINED_BY));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->Set(JS_STR("DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC"), JS_INT(xercesc_3_1::DOMNode::DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC));

    /**
     * prototype property accessors
     */
    nodet->SetAccessor(JS_STR("element"),xdom::get_property);
    nodet->SetAccessor(JS_STR("Element"),xdom::get_property);
    nodet->SetAccessor(JS_STR("nodeType"),xdom::get_node_type);
    nodet->SetAccessor(JS_STR("nodeName"),xdom::get_node_name);
    nodet->SetAccessor(JS_STR("nodeValue"),xdom::get_property,xdom::set_property);
    nodet->SetAccessor(JS_STR("attributes"),xdom::get_property);
    nodet->SetAccessor(JS_STR("childNodes"),xdom::get_property);
    nodet->SetAccessor(JS_STR("firstChild"),xdom::get_property);
    nodet->SetAccessor(JS_STR("lastChild"),xdom::get_property);
    nodet->SetAccessor(JS_STR("nextSibling"),xdom::get_property);
    nodet->SetAccessor(JS_STR("previousSibling"),xdom::get_property);
    nodet->SetAccessor(JS_STR("parentNode"),xdom::get_property);
    nodet->SetAccessor(JS_STR("ownerDocument"),xdom::get_property);
    nodet->SetAccessor(JS_STR("ownerImplementation"),xdom::get_property);
    nodet->SetAccessor(JS_STR("implementation"),xdom::get_property);
    nodet->SetAccessor(JS_STR("prefix"),xdom::get_property);
    nodet->SetAccessor(JS_STR("localName"),xdom::get_property);
    nodet->SetAccessor(JS_STR("innerHTML"),xdom::get_property,xdom::set_property);
    nodet->SetAccessor(JS_STR("innerHtml"),xdom::get_property,xdom::set_property);
    nodet->SetAccessor(JS_STR("innerXML"),xdom::get_property,xdom::set_property);
    nodet->SetAccessor(JS_STR("innerXml"),xdom::get_property,xdom::set_property);
    nodet->SetAccessor(JS_STR("outerHTML"),xdom::get_property,xdom::set_property);
    nodet->SetAccessor(JS_STR("outerHtml"),xdom::get_property,xdom::set_property);
    nodet->SetAccessor(JS_STR("outerXML"),xdom::get_property,xdom::set_property);
    nodet->SetAccessor(JS_STR("outerXml"),xdom::get_property,xdom::set_property);
    nodet->SetAccessor(JS_STR("innerText"),xdom::get_property,xdom::set_property);
    nodet->SetAccessor(JS_STR("textContent"),xdom::get_property,xdom::set_property);
    nodet->SetAccessor(JS_STR("TextContent"),xdom::get_property,xdom::set_property);

    /**
     * prototype methods
     */
    nodet->Set(JS_STR("~DOMNode"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_domnode_destructor));
    pnode->Set(JS_STR("serialize"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodeserialize));
    pnode->Set(JS_STR("getOuterHTML"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodeserialize));
    pnode->Set(JS_STR("getOuterHtml"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodeserialize));
    pnode->Set(JS_STR("getOuterXML"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodeserialize));
    pnode->Set(JS_STR("getOuterXml"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodeserialize));
    pnode->Set(JS_STR("getInnerHTML"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodeserializeinner));
    pnode->Set(JS_STR("getInnerHtml"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodeserializeinner));
    pnode->Set(JS_STR("getInnerXML"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodeserializeinner));
    pnode->Set(JS_STR("getInnerXml"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodeserializeinner));
    // pnode->Set(JS_STR("toString"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodeserialize));
    pnode->Set(JS_STR("getAsElement"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodegetaselement));
    pnode->Set(JS_STR("getNodeName"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodegetnodename));
    pnode->Set(JS_STR("getNodev8::Value"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodegetnodevalue));
    pnode->Set(JS_STR("getNodeType"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodegetnodetype));
    pnode->Set(JS_STR("getParentNode"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodegetparentnode));
    pnode->Set(JS_STR("getChildNodes"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodegetchildnodes));
    pnode->Set(JS_STR("getFirstChild"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodegetfirstchild));
    pnode->Set(JS_STR("getLastChild"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodegetlastchild));
    pnode->Set(JS_STR("getPreviousSibling"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodegetprevioussibling));
    pnode->Set(JS_STR("getNextSibling"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodegetnextsibling));
    pnode->Set(JS_STR("getAttributes"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodegetattributes));
    pnode->Set(JS_STR("getOwnerDocument"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodegetownerdocument));
    pnode->Set(JS_STR("getImplementation"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodegetownerimplementation));
    pnode->Set(JS_STR("cloneNode"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodeclonenode));
    pnode->Set(JS_STR("insertBefore"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodeinsertbefore));
    pnode->Set(JS_STR("replaceChild"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodereplacechild));
    pnode->Set(JS_STR("removeChild"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_noderemovechild));
    pnode->Set(JS_STR("appendChild"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodeappendchild));
    pnode->Set(JS_STR("hasChildNodes"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodehaschildnodes));
    pnode->Set(JS_STR("setNodev8::Value"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodesetnodevalue));
    pnode->Set(JS_STR("normalize"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodenormalize));
    pnode->Set(JS_STR("isSupported"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodeissupported));
    pnode->Set(JS_STR("getNamespaceURI"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodegetnamespaceuri));
    pnode->Set(JS_STR("getPrefix"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodegetprefix));
    pnode->Set(JS_STR("getv8::LocalName"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodegetlocalname));
    pnode->Set(JS_STR("setPrefix"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodesetprefix));
    pnode->Set(JS_STR("hasAttributes"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodehasattributes));
    pnode->Set(JS_STR("isSameNode"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodeissamenode));
    pnode->Set(JS_STR("isEqualNode"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodeisequalnode));
    pnode->Set(JS_STR("setUserData"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodesetuserdata));
    pnode->Set(JS_STR("getUserData"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodegetuserdata));
    pnode->Set(JS_STR("getBaseURI"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodegetbaseuri));
    pnode->Set(JS_STR("compareDocumentPosition"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodecomparedocumentposition));
    pnode->Set(JS_STR("getTextContent"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodegettextcontent));
    pnode->Set(JS_STR("setTextContent"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodesettextcontent));
    pnode->Set(JS_STR("lookupPrefix"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodelookupprefix));
    pnode->Set(JS_STR("isDefaultNamespace"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodeisdefaultnamespace));
    pnode->Set(JS_STR("lookupNamespaceURI"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodelookupnamespaceuri));
    pnode->Set(JS_STR("getFeature"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodegetfeature));

  // *****						*****
  // *****	END   [[ DOMNode ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMDocumentType ]]		*****
  // *****						*****

    xdom::fdocumenttype.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documenttype));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdocumenttype)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdocumenttype)->SetClassName(JS_STR("DOMDocumentType"));

    v8::Handle<v8::Template> pdocumenttype = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdocumenttype)->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> documenttypet = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdocumenttype)->InstanceTemplate();
    documenttypet->SetInternalFieldCount(1);
    documenttypet->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMDocumentType"));

    documenttypet->SetAccessor(JS_STR("name"), xdom::get_property);
    documenttypet->SetAccessor(JS_STR("entities"), xdom::get_property);
    documenttypet->SetAccessor(JS_STR("notations"), xdom::get_property);
    documenttypet->SetAccessor(JS_STR("publicId"), xdom::get_property);
    documenttypet->SetAccessor(JS_STR("systemId"), xdom::get_property);
    documenttypet->SetAccessor(JS_STR("internalSubset"), xdom::get_property);

    /**
     * prototype methods
     */
    documenttypet->Set(JS_STR("~DOMDocumentType"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documenttype_destructor));
    pdocumenttype->Set(JS_STR("getName"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_dtgetname));
    pdocumenttype->Set(JS_STR("getEntities"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_dtgetentities));
    pdocumenttype->Set(JS_STR("getNotations"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_dtgetnotations));
    pdocumenttype->Set(JS_STR("getPublicId"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_dtgetpublicid));
    pdocumenttype->Set(JS_STR("getSystemId"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_dtgetsystemid));
    pdocumenttype->Set(JS_STR("getInternalSubset"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_dtgetinternalsubset));

  // *****						*****
  // *****	END   [[ DOMDocumentType ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMDocument ]]			*****
  // *****						*****

    xdom::fdocument.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_document));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdocument)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdocument)->SetClassName(JS_STR("DOMDocument"));

    v8::Handle<v8::ObjectTemplate> documentt = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdocument)->InstanceTemplate();
    documentt->SetInternalFieldCount(1);
    documentt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMDocument"));

    documentt->SetAccessor(JS_STR("documentElement"), xdom::get_property);
    documentt->SetAccessor(JS_STR("doctype"), xdom::get_property, xdom::set_property);
    documentt->SetAccessor(JS_STR("docType"), xdom::get_property, xdom::set_property);
    documentt->SetAccessor(JS_STR("implementation"), xdom::get_property);
    documentt->SetAccessor(JS_STR("ownerImplementation"), xdom::get_property);
    documentt->SetAccessor(JS_STR("inputEncoding"), xdom::get_property, xdom::set_property);
    documentt->SetAccessor(JS_STR("xmlEncoding"), xdom::get_property, xdom::set_property);
    documentt->SetAccessor(JS_STR("xmlStandalone"), xdom::get_property, xdom::set_property);
    documentt->SetAccessor(JS_STR("xmlVersion"), xdom::get_property, xdom::set_property);
    documentt->SetAccessor(JS_STR("documentURI"), xdom::get_property, xdom::set_property);
    documentt->SetAccessor(JS_STR("domConfig"), xdom::get_property);
    documentt->SetAccessor(JS_STR("strictErrorChecking"), xdom::get_property, xdom::set_property);

    v8::Handle<v8::Template> pdocument = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdocument)->PrototypeTemplate();

    /**
     * Document prototype methods
     */
    documentt->Set(JS_STR("~DOMDocument"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_document_destructor));
    // pdocument->Set(JS_STR("toString"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentserialize));
    pdocument->Set(JS_STR("serialize"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentserialize));
    pdocument->Set(JS_STR("createLSSerializer"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentcreatelsserializer));
    pdocument->Set(JS_STR("createLSOutput"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentcreatelsoutput));
    pdocument->Set(JS_STR("createNode"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentcreatenode));
    pdocument->Set(JS_STR("createElement"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentcreateelement));
    pdocument->Set(JS_STR("createDocumentFragment"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentcreatedocumentfragment));
    pdocument->Set(JS_STR("createTextNode"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentcreatetextnode));
    pdocument->Set(JS_STR("createComment"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentcreatecomment));
    pdocument->Set(JS_STR("createCDATASection"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentcreatecdatasection));
    pdocument->Set(JS_STR("createProcessingInstruction"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentcreateprocessinginstruction));
    pdocument->Set(JS_STR("createAttribute"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentcreateattribute));
    pdocument->Set(JS_STR("createEntityReference"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentcreateentityreference));
    pdocument->Set(JS_STR("getDocType"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentgetdoctype));
    pdocument->Set(JS_STR("getImplementation"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentgetimplementation));
    pdocument->Set(JS_STR("getDocumentElement"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentgetdocumentelement));
    pdocument->Set(JS_STR("getElementsByTagName"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentgetelementsbytagname));
    pdocument->Set(JS_STR("importNode"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentimportnode));
    pdocument->Set(JS_STR("createElementNS"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentcreateelementns));
    pdocument->Set(JS_STR("createAttributeNS"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentcreateattributens));
    pdocument->Set(JS_STR("getElementsByTagNameNS"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentgetelementsbytagnamens));
    pdocument->Set(JS_STR("getElementById"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentgetelementbyid));
    pdocument->Set(JS_STR("getInputEncoding"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentgetinputencoding));
    pdocument->Set(JS_STR("getXmlEncoding"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentgetxmlencoding));
    pdocument->Set(JS_STR("getXmlStandalone"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentgetxmlstandalone));
    pdocument->Set(JS_STR("setXmlStandalone"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentsetxmlstandalone));
    pdocument->Set(JS_STR("getXmlVersion"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentgetxmlversion));
    pdocument->Set(JS_STR("setXmlVersion"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentsetxmlversion));
    pdocument->Set(JS_STR("getDocumentURI"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentgetdocumenturi));
    pdocument->Set(JS_STR("setDocumentURI"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentsetdocumenturi));
    pdocument->Set(JS_STR("getStrictErrorChecking"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentgetstricterrorchecking));
    pdocument->Set(JS_STR("setStrictErrorChecking"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentsetstricterrorchecking));
    pdocument->Set(JS_STR("renameNode"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentrenamenode));
    pdocument->Set(JS_STR("adoptNode"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentadoptnode));
    pdocument->Set(JS_STR("normalizeDocument"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentnormalizedocument));
    pdocument->Set(JS_STR("getDOMConfig"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_documentgetdomconfig));

  // *****						*****
  // *****	END   [[ DOMDocument ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMAttr ]]			*****
  // *****						*****

    xdom::fattribute.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_attribute));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fattribute)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fattribute)->SetClassName(JS_STR("DOMAttr"));

    v8::Handle<v8::ObjectTemplate> attributet = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fattribute)->InstanceTemplate();
    attributet->SetInternalFieldCount(1); /* id, ... */
    attributet->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMAttr"));

    attributet->SetAccessor(JS_STR("value"), xdom::get_property, xdom::set_property);
    attributet->SetAccessor(JS_STR("name"), xdom::get_property);
    attributet->SetAccessor(JS_STR("specified"), xdom::get_property);
    attributet->SetAccessor(JS_STR("ownerElement"), xdom::get_property);
    attributet->SetAccessor(JS_STR("schemaTypeInfo"), xdom::get_property);

    v8::Handle<v8::Template> pattribute = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fattribute)->PrototypeTemplate();

    /**
     * Attribute prototype methods
     */
    attributet->Set(JS_STR("~DOMAttr"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_attribute_destructor));
    pattribute->Set(JS_STR("getName"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_attributegetname));
    pattribute->Set(JS_STR("getSpecified"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_attributegetspecified));
    pattribute->Set(JS_STR("getv8::Value"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_attributegetvalue));
    pattribute->Set(JS_STR("setv8::Value"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_attributesetvalue));
    pattribute->Set(JS_STR("valueOf"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_attributegetvalue));
    pattribute->Set(JS_STR("v8::ValueOf"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_attributegetvalue));
    pattribute->Set(JS_STR("toString"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_attributegetvalue));
    pattribute->Set(JS_STR("ToString"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_attributegetvalue));
    pattribute->Set(JS_STR("getOwnerElement"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_attributegetownerelement));
    pattribute->Set(JS_STR("isId"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_attributeisid));
    pattribute->Set(JS_STR("getSchemaTypeInfo"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_attributegetschematypeinfo));

  // *****						*****
  // *****	END   [[ DOMAttr ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ PreElement ]]			*****
  // *****						*****

    xdom::fpreelement.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_preelement));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fpreelement)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fpreelement)->SetClassName(JS_STR("PreElement"));

    v8::Handle<v8::ObjectTemplate> preelementt = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fpreelement)->InstanceTemplate();
    preelementt->SetInternalFieldCount(1);

    /**
     * PreElement property accessors
     */
    preelementt->SetAccessor(JS_STR("tagName"),xdom::get_tag_name);
    preelementt->SetAccessor(JS_STR("TagName"),xdom::get_tag_name);
    preelementt->SetAccessor(JS_STR("node"),xdom::get_as_node);
    preelementt->SetAccessor(JS_STR("Node"),xdom::get_as_node);
    preelementt->SetAccessor(JS_STR("schemaTypeInfo"),xdom::get_property);
    preelementt->SetAccessor(JS_STR("SchemaTypeInfo"),xdom::get_property);

    v8::Handle<v8::Template> ppreelement = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fpreelement)->PrototypeTemplate();

    /**
     * PreElement prototype methods
     */
    preelementt->Set(JS_STR("~PreElement"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_preelement_destructor));
    //ppreelement->Set(JS_STR("toString"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_nodeserialize));
    ppreelement->Set(JS_STR("getAsNode"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_elementgetasnode));
    ppreelement->Set(JS_STR("setAttribute"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_elementsetattribute));
    ppreelement->Set(JS_STR("setAttributeNS"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_elementsetattributens));
    ppreelement->Set(JS_STR("setAttributeNode"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_elementsetattributenode));
    ppreelement->Set(JS_STR("setAttributeNodeNS"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_elementsetattributenodens));
    ppreelement->Set(JS_STR("getTagName"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_elementgettagname));
    ppreelement->Set(JS_STR("getAttribute"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_elementgetattribute));
    ppreelement->Set(JS_STR("getAttributeNode"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_elementgetattributenode));
    ppreelement->Set(JS_STR("getElementsByTagName"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_elementgetelementsbytagname));
    ppreelement->Set(JS_STR("removeAttribute"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_elementremoveattribute));
    ppreelement->Set(JS_STR("removeAttributeNode"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_elementremoveattributenode));
    ppreelement->Set(JS_STR("getAttributeNS"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_elementgetattributens));
    ppreelement->Set(JS_STR("removeAttributeNS"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_elementremoveattributens));
    ppreelement->Set(JS_STR("getAttributeNodeNS"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_elementgetattributenodens));
    ppreelement->Set(JS_STR("getElementsByTagNameNS"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_elementgetelementsbytagnamens));
    ppreelement->Set(JS_STR("hasAttribute"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_elementhasattribute));
    ppreelement->Set(JS_STR("hasAttributeNS"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_elementhasattributens));
    ppreelement->Set(JS_STR("setIdAttribute"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_elementsetidattribute));
    ppreelement->Set(JS_STR("setIdAttributeNS"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_elementsetidattributens));
    ppreelement->Set(JS_STR("setIdAttributeNode"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_elementsetidattributenode));
    ppreelement->Set(JS_STR("getSchemaTypeInfo"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_elementgetschematypeinfo));

  // *****						*****
  // *****	END   [[ PreElement ]]			*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ DOMElement ]]			*****
  // *****						*****

    xdom::felement.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_element));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::felement)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fpreelement));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::felement)->SetClassName(JS_STR("DOMElement"));

    v8::Handle<v8::ObjectTemplate> elementt = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::felement)->InstanceTemplate();
    elementt->SetInternalFieldCount(1);
    elementt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMElement"));

    /**
     * Element property accessors
     */
    v8::Local<v8::String> felementdata( JS_STR("element") );
    elementt->SetAccessor(JS_STR("tagName"),xdom::get_tag_name);
    elementt->SetAccessor(JS_STR("TagName"),xdom::get_tag_name);
    elementt->SetAccessor(JS_STR("node"),xdom::get_as_node);
    elementt->SetAccessor(JS_STR("Node"),xdom::get_as_node);
    //elementt->SetNamedPropertyv8::Handler(xdom::named_property_get, xdom::named_property_set, xdom::named_property_query, xdom::named_property_delete, xdom::named_property_enumerate, felementdata);

    v8::Handle<v8::Template> pelement = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::felement)->PrototypeTemplate();

    /**
     * Element prototype methods
     */
    elementt->Set(JS_STR("~DOMElement"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_element_destructor));

  // *****						*****
  // *****	END   [[ DOMElement ]]			*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ CDATA ]]			*****
  // *****						*****

    xdom::fcdata.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_cdata));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fcdata)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fcdata)->SetClassName(JS_STR("DOMCharacterData"));

    v8::Handle<v8::Template> pcdata = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fcdata)->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> cdatat = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fcdata)->InstanceTemplate();
    cdatat->SetInternalFieldCount(1); /* id, ... */
    cdatat->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMCharacterData"));
    cdatat->SetAccessor(JS_STR("data"), xdom::get_property, xdom::set_property);
    cdatat->SetAccessor(JS_STR("length"), xdom::get_property);

    /**
     * CharacterData prototype methods
     */
    cdatat->Set(JS_STR("~DOMCharacterData"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_cdata_destructor));
    pcdata->Set(JS_STR("getData"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_cdatagetdata));
    pcdata->Set(JS_STR("getLength"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_cdatagetlength));
    pcdata->Set(JS_STR("substringData"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_cdatasubstringdata));
    pcdata->Set(JS_STR("appendData"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_cdataappenddata));
    pcdata->Set(JS_STR("insertData"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_cdatainsertdata));
    pcdata->Set(JS_STR("deleteData"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_cdatadeletedata));
    pcdata->Set(JS_STR("replaceData"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_cdatareplacedata));
    pcdata->Set(JS_STR("setData"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_cdatasetdata));

  // *****						*****
  // *****	END   [[ CDATA ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ Text ]]			*****
  // *****						*****

    xdom::ftext.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_text));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::ftext)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fcdata));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::ftext)->SetClassName(JS_STR("DOMText"));

    v8::Handle<v8::Template> ptextnode = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::ftext)->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> textnodet = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::ftext)->InstanceTemplate();
    textnodet->SetInternalFieldCount(1); /* id, ... */
    textnodet->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMText"));

    /**
     * Text prototype methods
     */
    textnodet->Set(JS_STR("~DOMText"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_text_destructor));
    ptextnode->Set(JS_STR("splitText"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_textsplittext));
    ptextnode->Set(JS_STR("getIsElementContentWhitespace"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_textgetiselementcontentwhitespace));
    ptextnode->Set(JS_STR("getWholeText"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_textgetwholetext));
    ptextnode->Set(JS_STR("replaceWholeText"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_textreplacewholetext));
    ptextnode->Set(JS_STR("isIgnorableWhitespace"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_textisignorablewhitespace));

  // *****						*****
  // *****	END   [[ Text ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ CDATASection ]]		*****
  // *****						*****

    xdom::fcdatasection.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_cdatasection));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fcdatasection)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::ftext));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fcdatasection)->SetClassName(JS_STR("DOMCDATASection"));

    v8::Handle<v8::ObjectTemplate> cdatasectiont = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fcdatasection)->InstanceTemplate();
    cdatasectiont->SetInternalFieldCount(1);
    cdatasectiont->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMCDATASection"));

    /**
     * CDATASection prototype methods
     */
    cdatasectiont->Set(JS_STR("~DOMCDATASection"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_cdatasection_destructor));

  // *****						*****
  // *****	END   [[ CDATASection ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ Comment ]]			*****
  // *****						*****

    xdom::fcomment.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_comment));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fcomment)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fcdata));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fcomment)->SetClassName(JS_STR("DOMComment"));

    v8::Handle<v8::ObjectTemplate> commentt = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fcomment)->InstanceTemplate();
    commentt->SetInternalFieldCount(1);
    commentt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMComment"));

    /**
     * Comment prototype methods
     */
    commentt->Set(JS_STR("~DOMComment"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_comment_destructor));

  // *****						*****
  // *****	END   [[ Comment ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ Entity ]]			*****
  // *****						*****

    xdom::fentity.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_entity));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fentity)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fentity)->SetClassName(JS_STR("DOMEntity"));

    v8::Handle<v8::Template> pentity = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fentity)->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> entityt = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fentity)->InstanceTemplate();
    entityt->SetInternalFieldCount(1); /* id, ... */
    entityt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMEntity"));
    entityt->SetAccessor(JS_STR("publicId"), xdom::get_property);
    entityt->SetAccessor(JS_STR("systemId"), xdom::get_property);
    entityt->SetAccessor(JS_STR("notationName"), xdom::get_property);
    entityt->SetAccessor(JS_STR("inputEncoding"), xdom::get_property);
    entityt->SetAccessor(JS_STR("xmlEncoding"), xdom::get_property);
    entityt->SetAccessor(JS_STR("xmlVersion"), xdom::get_property);

    /**
     * Entity prototype methods
     */
    entityt->Set(JS_STR("~DOMEntity"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_entity_destructor));
    pentity->Set(JS_STR("getPublicId"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_entitygetpublicid));
    pentity->Set(JS_STR("getSystemId"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_entitygetsystemid));
    pentity->Set(JS_STR("getNotationName"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_entitygetnotationname));
    pentity->Set(JS_STR("getInputEncoding"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_entitygetinputencoding));
    pentity->Set(JS_STR("getXmlEncoding"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_entitygetxmlencoding));
    pentity->Set(JS_STR("getXmlVersion"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_entitygetxmlversion));

  // *****						*****
  // *****	END   [[ Entity ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ EntityReference ]]		*****
  // *****						*****

    xdom::fentityreference.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_entityreference));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fentityreference)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fentityreference)->SetClassName(JS_STR("DOMEntityReference"));

    v8::Handle<v8::ObjectTemplate> entityreferencet = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fentityreference)->InstanceTemplate();
    entityreferencet->SetInternalFieldCount(1); /* id, ... */
    entityreferencet->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMEntityReference"));

    /**
     * EntityReference prototype methods
     */
    entityreferencet->Set(JS_STR("~DOMEntityReference"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_entityreference_destructor));

  // *****						*****
  // *****	END   [[ EntityReference ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMProcessingInstruction ]]	*****
  // *****						*****

    xdom::fprocessinginstruction.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_processinginstruction));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fprocessinginstruction)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fprocessinginstruction)->SetClassName(JS_STR("DOMProcessingInstruction"));

    v8::Handle<v8::ObjectTemplate> processinginstructiont = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fprocessinginstruction)->InstanceTemplate();
    processinginstructiont->SetInternalFieldCount(1); /* id, ... */
    processinginstructiont->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMProcessingInstruction"));
    processinginstructiont->SetAccessor(JS_STR("target"),xdom::get_property);
    processinginstructiont->SetAccessor(JS_STR("data"),xdom::get_property,xdom::set_property);

    v8::Handle<v8::Template> pprocessinginstruction = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fprocessinginstruction)->PrototypeTemplate();

    /**
     * ProcessingInstruction prototype methods
     */
    processinginstructiont->Set(JS_STR("~DOMProcessingInstruction"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_processinginstruction_destructor));
    pprocessinginstruction->Set(JS_STR("getData"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_processinginstructiongetdata));
    pprocessinginstruction->Set(JS_STR("setData"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_processinginstructionsetdata));
    pprocessinginstruction->Set(JS_STR("getTarget"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_processinginstructiongettarget));

  // *****						*****
  // *****	END   [[ DOMProcessingInstruction ]]	*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMNotation ]]			*****
  // *****						*****

    xdom::fnotation.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_notation));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnotation)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnotation)->SetClassName(JS_STR("DOMNotation"));

    v8::Handle<v8::ObjectTemplate> notationt = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnotation)->InstanceTemplate();
    notationt->SetInternalFieldCount(1); /* id, ... */
    notationt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMNotation"));
    notationt->SetAccessor(JS_STR("publicId"),xdom::get_property);
    notationt->SetAccessor(JS_STR("systemId"),xdom::get_property);

    v8::Handle<v8::Template> pnotation = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnotation)->PrototypeTemplate();

    /**
     *	DOMNotation prototype methods
     */
    notationt->Set(JS_STR("~DOMNotation"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_notation_destructor));
    pnotation->Set(JS_STR("getPublicId"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_notationgetpublicid));
    pnotation->Set(JS_STR("getSystemId"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_notationgetsystemid));

  // *****						*****
  // *****	END   [[ DOMNotation ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ Buffer ]]			*****
  // *****						*****

    xdom::fbuffer.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_buffer));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fbuffer)->SetClassName(JS_STR("Buffer"));

    v8::Handle<v8::Template> pbuffer = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fbuffer)->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> buffert = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fbuffer)->InstanceTemplate();
    buffert->SetInternalFieldCount(2);
    buffert->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("Buffer"));

    /**
     * Buffer prototype methods
     */
    buffert->Set(JS_STR("~Buffer"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_buffer_destructor));

  // *****						*****
  // *****	END   [[ Buffer ]]			*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ MemoryManager ]]			*****
  // *****						*****

    xdom::fmemorymanager.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_memorymanager));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fmemorymanager)->SetClassName(JS_STR("MemoryManager"));

    v8::Handle<v8::Template> pmemorymanager = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fmemorymanager)->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> memorymanagert = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fmemorymanager)->InstanceTemplate();
    memorymanagert->SetInternalFieldCount(1);
    memorymanagert->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("MemoryManager"));

    /**
     * MemoryManager prototype methods
     */
    memorymanagert->Set(JS_STR("~MemoryManager"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_memorymanager_destructor));
    pmemorymanager->Set(JS_STR("getExceptionMemoryManager"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_memorymanagergetexceptionmemorymanager));
    pmemorymanager->Set(JS_STR("allocate"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_memorymanagerallocate));
    pmemorymanager->Set(JS_STR("deallocate"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_memorymanagerdeallocate));

  // *****						*****
  // *****	END   [[ MemoryManager ]]			*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ DOMMemoryManager ]]		*****
  // *****						*****

    xdom::fdommemorymanager.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_dommemorymanager));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdommemorymanager)->SetClassName(JS_STR("DOMMemoryManager"));

    v8::Handle<v8::Template> pdommemorymanager =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdommemorymanager)->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> dommemorymanagert =v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdommemorymanager)->InstanceTemplate();
    dommemorymanagert->SetInternalFieldCount(1);
    dommemorymanagert->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMMemoryManager"));

    /**
     *	DOMMemoryManager prototype methods
     */
    dommemorymanagert->Set(JS_STR("~DOMMemoryManager"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_dommemorymanager_destructor));
    pdommemorymanager->Set(JS_STR("getMemoryAllocationBlockSize"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_dommemorymanagergetmemoryallocationblocksize));
    pdommemorymanager->Set(JS_STR("setMemoryAllocationBlockSize"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_dommemorymanagersetmemoryallocationblocksize));
    pdommemorymanager->Set(JS_STR("allocate"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_dommemorymanagerallocate));
//    pdommemorymanager->Set(JS_STR("release"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_dommemorymanagerrelease));
    pdommemorymanager->Set(JS_STR("cloneString"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_dommemorymanagerclonestring));

  // *****						*****
  // *****	END   [[ DOMMemoryManager ]]		*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ XMemory ]]			*****
  // *****						*****

    xdom::fxmemory.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xmemory));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fxmemory)->SetClassName(JS_STR("XMemory"));

    v8::Handle<v8::Template> pxmemory = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fxmemory)->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> xmemoryt = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fxmemory)->InstanceTemplate();
    xmemoryt->SetInternalFieldCount(1);
    xmemoryt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("XMemory"));

    /**
     * XMemory prototype methods
     */
    xmemoryt->Set(JS_STR("~XMemory"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xmemory_destructor));
    pxmemory->Set(JS_STR("New"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xmemorynew));
    pxmemory->Set(JS_STR("Delete"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xmemorydelete));

  // *****						*****
  // *****	END   [[ XMemory ]]			*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ BinInputStream ]]		*****
  // *****						*****

    xdom::fbininput.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_bininput));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fbininput)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fxmemory));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fbininput)->SetClassName(JS_STR("BinInputStream"));

    v8::Handle<v8::Template> pbininputstream = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fbininput)->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> bininputstreamt = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fbininput)->InstanceTemplate();
    bininputstreamt->SetInternalFieldCount(1);
    bininputstreamt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("BinInputStream"));

    /**
     * BinInputStream prototype methods
     */
    bininputstreamt->Set(JS_STR("~BinInputStream"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_bininput_destructor));

  // *****						*****
  // *****	END   [[ BinInputStream ]]		*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ BinFileInputStream ]]		*****
  // *****						*****

    xdom::fbinfileinput.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_binfileinput));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fbinfileinput)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fbininput));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fbinfileinput)->SetClassName(JS_STR("BinFileInputStream"));

    v8::Handle<v8::Template> pbinfileinput = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fbinfileinput)->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> binfileinputt = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fbinfileinput)->InstanceTemplate();
    binfileinputt->SetInternalFieldCount(1);
    binfileinputt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("BinFileInputStream"));

    /**
     * BinFileInputStream prototype methods
     */
    binfileinputt->Set(JS_STR("~BinFileInputStream"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_binfileinput_destructor));

  // *****						*****
  // *****	END   [[ BinFileInputStream ]]			*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ BinMemInputStream ]]		*****
  // *****						*****

    xdom::fbinmeminput.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_binmeminputstream));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fbinmeminput)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fbininput));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fbinmeminput)->SetClassName(JS_STR("BinMemInputStream"));

    v8::Handle<v8::Template> pbinmeminputstream = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fbinmeminput)->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> binmeminputstreamt = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fbinmeminput)->InstanceTemplate();
    binmeminputstreamt->SetInternalFieldCount(1);
    binmeminputstreamt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("BinMemInputStream"));

    /**
     * BinMemInputStream prototype methods
     */
    binmeminputstreamt->Set(JS_STR("~BinMemInputStream"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_binmeminputstream_destructor));

  // *****						*****
  // *****	END   [[ BinMemInputStream ]]			*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ InputSource ]]			*****
  // *****						*****

    xdom::finputsource.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_inputsource));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::finputsource)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fxmemory));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::finputsource)->SetClassName(JS_STR("InputSource"));

    v8::Handle<v8::Template> pinputsource = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::finputsource)->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> inputsourcet = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::finputsource)->InstanceTemplate();
    inputsourcet->SetInternalFieldCount(1);
    inputsourcet->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("InputSource"));

    /**
     * InputSource prototype methods
     */
    inputsourcet->Set(JS_STR("~InputSource"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_inputsource_destructor));
    pinputsource->Set(JS_STR("makeStream"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_inputsourcemakestream));
    pinputsource->Set(JS_STR("getEncoding"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_inputsourcegetencoding));
    pinputsource->Set(JS_STR("getPublicId"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_inputsourcegetpublicid));
    pinputsource->Set(JS_STR("getSystemId"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_inputsourcegetsystemid));
    pinputsource->Set(JS_STR("getIssueFatalErrorIfNotFound"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_inputsourcegetissuefatalerrorifnotfound));
    pinputsource->Set(JS_STR("getMemoryManager"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_inputsourcegetmemorymanager));
    pinputsource->Set(JS_STR("setEncoding"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_inputsourcesetencoding));
    pinputsource->Set(JS_STR("setPublicId"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_inputsourcesetpublicid));
    pinputsource->Set(JS_STR("setSystemId"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_inputsourcesetsystemid));
    pinputsource->Set(JS_STR("setIssueFatalErrorIfNotFound"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_inputsourcesetissuefatalerrorifnotfound));

  // *****						*****
  // *****	END   [[ InputSource ]]			*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ LocalFileInputSource ]]	*****
  // *****						*****

    xdom::ffileinput.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_fileinput));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::ffileinput)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::finputsource));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::ffileinput)->SetClassName(JS_STR("LocalFileInputSource"));

    v8::Handle<v8::Template> pfileinput = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::ffileinput)->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> fileinputt = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::ffileinput)->InstanceTemplate();
    fileinputt->SetInternalFieldCount(1);
    fileinputt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("LocalFileInputSource"));

    /**
     * FileInputSource prototype methods
     */
    fileinputt->Set(JS_STR("~LocalFileInputSource "), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_fileinput_destructor));

  // *****						*****
  // *****	END   [[ LocalFileInputSource ]]	*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ MemBufInputSource ]]		*****
  // *****						*****

    xdom::fmembufinput.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_membufinput));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fmembufinput)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::finputsource));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fmembufinput)->SetClassName(JS_STR("MemBufInputSource"));

    v8::Handle<v8::Template> pmembufinput = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fmembufinput)->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> membufinputt = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fmembufinput)->InstanceTemplate();
    membufinputt->SetInternalFieldCount(2);
    membufinputt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("MemBufInputSource"));

    /**
     * MemBufInputSource prototype methods
     */
    membufinputt->Set(JS_STR("~MemBufInputSource"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_membufinput_destructor));
    pmembufinput->Set(JS_STR("setCopyBufToStream"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_membufinputsetcopybuftostream));
    pmembufinput->Set(JS_STR("resetMemBufInputSource"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_membufinputresetmembufinputsource));

  // *****						*****
  // *****	END   [[ MemBufInputSource ]]		*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ StdInInputSource ]]		*****
  // *****						*****

    xdom::fstdin.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_stdin));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fstdin)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::finputsource));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fstdin)->SetClassName(JS_STR("StdInInputSource"));

    v8::Handle<v8::Template> pstdin = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fstdin)->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> stdint = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fstdin)->InstanceTemplate();
    stdint->SetInternalFieldCount(1);
    stdint->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("StdInInputSource"));

    /**
     * StdInInputSource prototype methods
     */
    stdint->Set(JS_STR("~StdInInputSource "), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_stdin_destructor));

  // *****						*****
  // *****	END   [[ StdInInputSource ]]		*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ URLInputSource ]]		*****
  // *****						*****

    xdom::furlinput.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_urlinput));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::furlinput)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::finputsource));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::furlinput)->SetClassName(JS_STR("URLInputSource"));

    v8::Handle<v8::Template> purlinput = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::furlinput)->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> urlinputt = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::furlinput)->InstanceTemplate();
    urlinputt->SetInternalFieldCount(1);
    urlinputt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("URLInputSource"));

    /**
     * URLInputSource prototype methods
     */
    urlinputt->Set(JS_STR("~URLInputSource "), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_urlinput_destructor));

  // *****						*****
  // *****	END   [[ URLInputSource ]]		*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ XMLURL ]]		*****
  // *****						*****

    xdom::fxmlurl.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xmlurl));
   v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fxmlurl)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::finputsource));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fxmlurl)->SetClassName(JS_STR("XMLURL"));

    v8::Handle<v8::Template> pxmlurl = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fxmlurl)->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> xmlurlt = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fxmlurl)->InstanceTemplate();
    xmlurlt->SetInternalFieldCount(1);
    xmlurlt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("XMLURL"));

    /**
     * XMLURL prototype methods
     */
    xmlurlt->Set(JS_STR("~XMLURL"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xmlurl_destructor));
    pxmlurl->Set(JS_STR("getFragment"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xmlurlgetfragment));
    pxmlurl->Set(JS_STR("getHost"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xmlurlgethost));
    pxmlurl->Set(JS_STR("getPassword"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xmlurlgetpassword));
    pxmlurl->Set(JS_STR("getPath"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xmlurlgetpath));
    pxmlurl->Set(JS_STR("getPortNum"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xmlurlgetportnum));
    pxmlurl->Set(JS_STR("getProtocolName"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xmlurlgetprotocolname));
    pxmlurl->Set(JS_STR("getQuery"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xmlurlgetquery));
    pxmlurl->Set(JS_STR("getURIText"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xmlurlgeturltext));
    pxmlurl->Set(JS_STR("getUser"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xmlurlgetuser));
    pxmlurl->Set(JS_STR("hasInvalidChar"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xmlurlhasinvalidchar));
    pxmlurl->Set(JS_STR("makeNewStream"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xmlurlmakenewstream));
    pxmlurl->Set(JS_STR("makeRelativeTo"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xmlurlmakerelativeto));
    pxmlurl->Set(JS_STR("lookupByName"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xmlurllookupbyname));
    pxmlurl->Set(JS_STR("parse"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xmlurlparse));
    pxmlurl->Set(JS_STR("toString"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xmlurlgeturltext));

  // *****						*****
  // *****	END   [[ XMLURL ]]		*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ XPathNamespace ]]		*****
  // *****						*****

    xdom::fxpathnamespace.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xpathnamespace));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fxpathnamespace)->Inherit(v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fxpathnamespace)->SetClassName(JS_STR("DOMXPathNamespace"));

    v8::Handle<v8::Template> pxpathnamespace = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fxpathnamespace)->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> xpathnamespacet = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fxpathnamespace)->InstanceTemplate();
    xpathnamespacet->SetInternalFieldCount(1);
    xpathnamespacet->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMXPathNamespace"));
    xpathnamespacet->SetAccessor(JS_STR("ownerElement"), xdom::get_property);

    /**
     * XPathNamespace prototype methods
     */
    xpathnamespacet->Set(JS_STR("~DOMXPathNamespace"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xpathnamespace_destructor));
    pxpathnamespace->Set(JS_STR("getOwnerElement"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_xpathgetownerelement));

  // *****						*****
  // *****	END   [[ XPathNamespace ]]		*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ DOMTypeInfo ]]			*****
  // *****						*****

    xdom::ftypeinfo.Reset(JS_ISOLATE, v8::FunctionTemplate::New(JS_ISOLATE, xdom::_typeinfo));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::ftypeinfo)->SetClassName(JS_STR("DOMTypeInfo"));

    v8::Handle<v8::ObjectTemplate> typeinfot = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::ftypeinfo)->InstanceTemplate();
    typeinfot->SetInternalFieldCount(1);
    typeinfot->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMTypeInfo"));

    v8::Handle<v8::Template> ttypeinfo = v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::ftypeinfo)->PrototypeTemplate();

    /*	*
	*	Emulate enumerated types by setting static property values
	*	for this class on its FunctionTemplate:
	*	(see "http://xerces.apache.org/xerces-c/apiDocs-3/classDOMTypeInfo.html" for enumerated values)
     *	*/
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::ftypeinfo)->Set(JS_STR("DERIVATION_EXTENSION"), JS_INT(xercesc_3_1::DOMTypeInfo::DERIVATION_EXTENSION));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::ftypeinfo)->Set(JS_STR("DERIVATION_LIST"), JS_INT(xercesc_3_1::DOMTypeInfo::DERIVATION_LIST));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::ftypeinfo)->Set(JS_STR("DERIVATION_RESTRICTION"), JS_INT(xercesc_3_1::DOMTypeInfo::DERIVATION_RESTRICTION));
    v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::ftypeinfo)->Set(JS_STR("DERIVATION_UNION"), JS_INT(xercesc_3_1::DOMTypeInfo::DERIVATION_UNION));

    /**
     * DOMTypeInfo prototype methods
     */
    typeinfot->Set(JS_STR("~DOMTypeInfo"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_typeinfo_destructor));
    ttypeinfo->Set(JS_STR("getTypeName"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_typeinfogettypename));
    ttypeinfo->Set(JS_STR("getTypeNamespace"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_typeinfogettypenamespace));
    ttypeinfo->Set(JS_STR("isDerivedFrom"), v8::FunctionTemplate::New(JS_ISOLATE, xdom::_typeinfoisderivedfrom));

  // *****						*****
  // *****	END   [[ DOMTypeInfo ]]			*****
  // ********************************************************


  // ********************************************************
  // ********************************************************

  //	*
  //	*	Exported symbols:
  //	*

  exports->Set(JS_STR("DOMException"),v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomexcpt)->GetFunction());
  exports->Set(JS_STR("DOMImplementation"),v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdom)->GetFunction());
  exports->Set(JS_STR("DOMImplementationLS"),v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomls)->GetFunction());
  exports->Set(JS_STR("DOMImplementationSource"),v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomsource)->GetFunction());
  exports->Set(JS_STR("DOMImplementationRegistry"),v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fdomreg)->GetFunction());
  exports->Set(JS_STR("DOMLSParser"), v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fparser)->GetFunction());
  exports->Set(JS_STR("DOMLSSerializer"), v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fserializer)->GetFunction());
  exports->Set(JS_STR("DOMTypeInfo"), v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::ftypeinfo)->GetFunction());
  exports->Set(JS_STR("DOMNode"),v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fnode)->GetFunction());
  exports->Set(JS_STR("XMLURL"), v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fxmlurl)->GetFunction());
  exports->Set(JS_STR("MemBufInputSource"), v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, xdom::fmembufinput)->GetFunction());
}

/*
 *	Server-side DOM module for v8cgi
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
  using namespace xercesc_3_0;
  using namespace v8;
  //XERCES_CPP_NAMESPACE_USE;

  #include "js_xdom.hpp"

  //	**********************************************		//
  //	**********************************************		//

  //	DOMException
  //
  JS_METHOD(_domexcpt) {
    TryCatch tc;
    if (args.Length()<1)
      return JS_ERROR("[_domexcpt()] ERROR: Missing input parameter");
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
      return JS_ERROR("[_domexcpt()] ERROR: \"domerr\" is a null pointer");
    }
    else {
      SAVE_PTR(0, domerr);
      return args.This();
    }
  }

  JS_METHOD(_domexcpt_destructor) {
    /* TryCatch tc; */
    //DOMERR;
    //XTRY( domerr->~DOMException(); );
    return args.This();
  }


  //	DOMLSException
  //
  JS_METHOD(_domlsexcpt) {
    TryCatch tc;
    if (args.Length()<1)
      return JS_ERROR("[_domlsexcpt()] ERROR: Missing input parameter");
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
      return JS_ERROR("[_domlsexcpt()] ERROR: \"domlserr\" is a null pointer");
    }
    else {
      SAVE_PTR(0, domlserr);
      return args.This();
    }
  }

  JS_METHOD(_domlsexcpt_destructor) {
    /* TryCatch tc; */
    //DOMLSERR;
    //XTRY( domlserr->~DOMLSException(); );
    return args.This();
  }


  //	DOMImplementationList
  //
  JS_METHOD(_domlist) {
    TryCatch tc;
    if (args.Length()<1)
      return JS_ERROR("[_domlist()] ERROR: Missing input parameter");
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
      return JS_ERROR("[_domlist()] ERROR: \"domlist\" is a null pointer");
    }
    else {
      SAVE_PTR(0, domlist);
      return args.This();
    }
  }

  JS_METHOD(_domlistitem) {
    if (args.Length()!=1) {
      return JS_ERROR("[_domlistitem()] ERROR: Incorrect number of input parameters");
    }
    DOMLIST;
    DOMImplementation * dom = NULL;
    XMLSize_t index = (XMLSize_t)args[0]->ToInteger()->IntegerValue();
    XTRY( dom = domlist->item(index); );
    if (dom==NULL) {
      return JS_ERROR("[_domlistitem()] ERROR: \"dom\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      Local<Value> fargv[] = { External::New((void *)dom) };
      Local<Function> func( xdom::fdom->GetFunction() );
      Handle<Object> ret( func->NewInstance(fargc, fargv) );
      return ret;
    }
  }

  JS_METHOD(_domlistgetlength) {
    if (args.Length()>0) {
      return JS_ERROR("[_domlistgetlength()] ERROR: Incorrect number of input parameters");
    }
    DOMLIST;
    XMLSize_t length = 0;
    XTRY( length = domlist->getLength(); );
    return JS_INT(length);
  }

  JS_METHOD(_domlist_destructor) {
    /* TryCatch tc; */
    //DOMERR;
    //XTRY( domlist->~DOMImplementationList(); );
    return args.This();
  }


  //	DOMLocator
  //
  JS_METHOD(_domlocator) {
    TryCatch tc;
    if (args.Length()<1)
      return JS_ERROR("[_domlocator()] ERROR: Missing input parameter");
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
      return JS_ERROR("[_domlocator()] ERROR: \"domlocator\" is a null pointer");
    }
    else {
      SAVE_PTR(0, domlocator);
      return args.This();
    }
  }

  JS_METHOD(_domlocatorgetrelatednode) {
    if (args.Length()>0) {
      return JS_ERROR("[_domlocatorgetrelatednode()] ERROR: Incorrect number of input parameters");
    }
    DOMLOCATOR;
    DOMNode * node = NULL;
    XTRY( node = domlocator->getRelatedNode(); );
    if (node==NULL) {
      return JS_ERROR("[_domlocatorgetrelatednode()] ERROR: \"node\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      Local<Value> fargv[] = { External::New((void *)node) };
      Local<Function> func( xdom::fnode->GetFunction() );
      Handle<Object> ret( func->NewInstance(fargc, fargv) );
      return ret;
    }
  }

  JS_METHOD(_domlocatorgetlinenumber) {
    if (args.Length()>0) {
      return JS_ERROR("[_domlocatorgetlength()] ERROR: Incorrect number of input parameters");
    }
    DOMLOCATOR;
    XMLFileLoc loc = 0;
    XTRY( loc = domlocator->getLineNumber(); );
    return JS_INT(loc);
  }

  JS_METHOD(_domlocatorgetcolumnnumber) {
    if (args.Length()>0) {
      return JS_ERROR("[_domlocatorgetlength()] ERROR: Incorrect number of input parameters");
    }
    DOMLOCATOR;
    XMLFileLoc loc = 0;
    XTRY( loc = domlocator->getColumnNumber(); );
    return JS_INT(loc);
  }

  JS_METHOD(_domlocatorgetbyteoffset) {
    if (args.Length()>0) {
      return JS_ERROR("[_domlocatorgetlength()] ERROR: Incorrect number of input parameters");
    }
    DOMLOCATOR;
    XMLFilePos loc = 0;
    XTRY( loc = domlocator->getByteOffset(); );
    return JS_INT(loc);
  }

  JS_METHOD(_domlocatorgetutf16offset) {
    if (args.Length()>0) {
      return JS_ERROR("[_domlocatorgetlength()] ERROR: Incorrect number of input parameters");
    }
    DOMLOCATOR;
    XMLFilePos loc = 0;
    XTRY( loc = domlocator->getUtf16Offset(); );
    return JS_INT(loc);
  }

  JS_METHOD(_domlocatorgeturi) {
    if (args.Length()>0) {
      return JS_ERROR("[_domlocatorgeturi()] ERROR: Incorrect number of input parameters");
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
    return JS_STR(ret);
  }

  JS_METHOD(_domlocator_destructor) {
    /* TryCatch tc; */
    //DOMERR;
    //XTRY( domlocator->~DOMLocator(); );
    return args.This();
  }


  //	DOMImplementationSource
  //
  JS_METHOD(_domsource) {
    TryCatch tc;
    if (args.Length()!=0 && args.Length()!=1)
      return JS_ERROR("[_domsource()] ERROR: Incorrect number of input parameters");
    ASSERT_CONSTRUCTOR;
    if (xdom::initialized!=true) {
      xercesc_3_0::XMLPlatformUtils::Initialize();
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
      return JS_ERROR("[_domsource()] ERROR: \"domsource\" is a null pointer");
    }
    else {
      SAVE_PTR(0, domsource);
      return args.This();
    }
  }

  JS_METHOD(_domsourcegetdomimplementation) {
    if (args.Length()!=1) {
      return JS_ERROR("[_domsourcegetdomimplementation()] ERROR: Incorrect number of input parameters");
    }
    if (xdom::initialized!=true) {
      xercesc_3_0::XMLPlatformUtils::Initialize();
      xdom::initialized=true;
    }
    DOMSOURCE;
    DOMImplementation * dom = NULL;
    XTRY( dom = domsource->getDOMImplementation(ARGSTR(0)); );
    if (dom==NULL) {
      return JS_ERROR("[_domsourcegetdomimplementation()] ERROR: \"dom\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      Local<Value> fargv[] = { External::New((void *)dom) };
      Local<Function> func( xdom::fdom->GetFunction() );
      Handle<Object> ret( func->NewInstance(fargc, fargv) );
      return ret;
    }
  }

  JS_METHOD(_domsourcegetdomimplementationlist) {
    if (args.Length()!=1) {
      return JS_ERROR("[_domsourcegetdomimplementationlist()] ERROR: Incorrect number of input parameters");
    }
    if (xdom::initialized!=true) {
      xercesc_3_0::XMLPlatformUtils::Initialize();
      xdom::initialized=true;
    }
    DOMSOURCE;
    DOMImplementationList * domlist = NULL;
    XTRY( domlist = domsource->getDOMImplementationList(ARGSTR(0)); );
    if (domlist==NULL) {
      return JS_ERROR("[_domsourcegetdomimplementationlist()] ERROR: \"domlist\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      Local<Value> fargv[] = { External::New((void *)domlist) };
      Local<Function> func( xdom::fdomlist->GetFunction() );
      Handle<Object> ret( func->NewInstance(fargc, fargv) );
      return ret;
    }
  }

  JS_METHOD(_domsource_destructor) {
    /* TryCatch tc; */
    //DOMERR;
    //XTRY( domsource->~DOMImplementationSource(); );
    return args.This();
  }


  //	DOMImplementationRegistry
  //
  JS_METHOD(_domreg) {
    TryCatch tc;
    if (args.Length()!=1 && args.Length()!=0)
      return JS_ERROR("[_domreg()] ERROR: Incorrect number of input parameters");
    ASSERT_CONSTRUCTOR;
    if (xdom::initialized!=true) {
      xercesc_3_0::XMLPlatformUtils::Initialize();
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
      return JS_ERROR("[_domreg()] ERROR: \"domreg\" is a null pointer");
    }
    else {
      SAVE_PTR(0, domreg);
      return args.This();
    }
  }

  JS_METHOD(_domreggetdomimplementation) {
    TryCatch tc;
    if (args.Length()!=1) {
      return JS_ERROR("[_domreggetdomimplementation()] ERROR: Incorrect number of input parameters");
    }
    //DOMREG;
    if (xdom::initialized!=true) {
      xercesc_3_0::XMLPlatformUtils::Initialize();
      xdom::initialized=true;
    }
    DOMImplementation * dom = NULL;
    SS intxt( *String::Utf8Value(args[0]->ToString()) );
    const XMLCh * arg0 = X(intxt.str().c_str());
    XTRY( dom = DOMImplementationRegistry::getDOMImplementation(arg0); );
    if (dom==NULL) {
      return JS_ERROR("[_domreggetdomimplementation()] ERROR: \"dom\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      Local<Value> fargv[] = { External::New((void *)dom) };
      Local<Function> func( xdom::fdom->GetFunction() );
      Handle<Object> ret( func->NewInstance(fargc, fargv) );
      return ret;
    }
  }

  JS_METHOD(_domreggetdomimplementationlist) {
    TryCatch tc;
    if (args.Length()!=1) {
      return JS_ERROR("[_domreggetdomimplementationlist()] ERROR: Incorrect number of input parameters");
    }
    //DOMREG;
    if (xdom::initialized!=true) {
      xercesc_3_0::XMLPlatformUtils::Initialize();
      xdom::initialized=true;
    }
    DOMImplementationList * domlist = NULL;
    SS intxt( *String::Utf8Value(args[0]->ToString()) );
    const XMLCh * arg0 = X(intxt.str().c_str());
    XTRY( domlist = DOMImplementationRegistry::getDOMImplementationList(arg0); );
    if (domlist==NULL) {
      return JS_ERROR("[_domreggetdomimplementationlist()] ERROR: \"domlist\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      Local<Value> fargv[] = { External::New((void *)domlist) };
      Local<Function> func( xdom::fdomlist->GetFunction() );
      Handle<Object> ret( func->NewInstance(fargc, fargv) );
      return ret;
    }
  }

  JS_METHOD(_domregaddsource) {
    if (args.Length()!=1) {
      return JS_ERROR("[_domregaddsource()] ERROR: Incorrect number of input parameters");
    }
    if (xdom::initialized!=true) {
      xercesc_3_0::XMLPlatformUtils::Initialize();
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
      return JS_ERROR("[_domregaddsource()] ERROR: \"src\" is a null pointer");
    }
    else {
      XTRY( domreg->addSource(src); );
      return args.This();
    }
  }

  JS_METHOD(_domreg_destructor) {
    /* TryCatch tc; */
    //DOMERR;
    //XTRY( domreg->~DOMImplementationRegistry(); );
    return args.This();
  }


  //	XMemory
  //
  JS_METHOD(_xmemory) {
    TryCatch tc;
    if (args.Length()<1)
      return JS_ERROR("[_xmemory()] ERROR: Missing input parameter");
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
      return JS_ERROR("[_xmemory()] ERROR: \"xmemory\" is a null pointer");
    }
    else {
      SAVE_PTR(0, xmemory);
      return args.This();
    }
  }

  JS_METHOD(_xmemorynew) {
    TryCatch tc;
    if (args.Length()!=1 && args.Length()!=2) {
      return JS_ERROR("[_xmemorynew()] ERROR: Incorrect number of input parameters");
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
	return JS_ERROR("[_xmemorynew()] ERROR: \"mm\" is a null pointer");
      }
      else {
	XTRY( buf = mm->allocate(size); );
      }
    }
    if (buf==NULL) {
      return JS_ERROR("[_xmemorynew()] ERROR: \"buf\" is a null pointer");
    }
    else {
      Local<Value> fargv[] = { External::New((void *)buf), Integer::New(size) };
      XMLSize_t fargc = 2;
      Handle<Object> ret( fbuffer->GetFunction()->NewInstance(fargc,fargv) );
      return ret;
    }
  }

  JS_METHOD(_xmemorydelete) {
    TryCatch tc;
    if (args.Length()!=1 && args.Length()!=2) {
      return JS_ERROR("[_xmemorydelete()] ERROR: Incorrect number of input parameters");
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
	return JS_ERROR("[_xmemorydelete()] ERROR: \"mm\" is a null pointer");
      }
      else {
	XTRY( xmem->XMemory::operator delete(p, mm); );
      }
    }
    return args.This();
  }

  JS_METHOD(_xmemory_destructor) {
    /* TryCatch tc; */
    //XMEM;
    //XTRY( xmem->~XMemory(); );
    return args.This();
  }



  //	DOMLSInput
  //
  JS_METHOD(_domlsinput) {
    TryCatch tc;
    if (args.Length()<1)
      return JS_ERROR("[_domlsinput()] ERROR: Missing input parameter");
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
      return JS_ERROR("[_domlsinput()] ERROR: \"domlsinput\" is a null pointer");
    }
    else {
      SAVE_PTR(0,domlsinput);
      return args.This();
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
    return JS_STR(ret);
  }

  JS_METHOD(_domlsinputgetbytestream) {
    DOMLSINPUT;
    InputSource * src = NULL;
    XLSTRY( src = domlsinput->getByteStream(); );
    if (src==NULL) {
      return JS_ERROR("[_domlsinputgetbytestream()] ERROR: \"src\" is a null pointer");
    }
    else {
      Local<Value> fargv[] = { External::New((void *)src) };
      XMLSize_t fargc = 1;
      Handle<Value> ret( xdom::finputsource->GetFunction()->NewInstance(fargc, fargv) );
      return ret;
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
    return JS_STR(ret);
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
    return JS_STR(ret);
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
    return JS_STR(ret);
  }

  JS_METHOD(_domlsinputgetbaseuri) {
    if (args.Length()>0) {
      return JS_ERROR("[_domlsinputgetbaseuri()] ERROR: incorrect number of input parameters");
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
    return JS_STR(ret);
  }

  JS_METHOD(_domlsinputsetstringdata) {
    if (args.Length()!=1) {
      return JS_ERROR("[_domlsinputsetstringdata()] ERROR: incorrect number of input parameters");
    }
    DOMLSINPUT;
    XLSTRY( domlsinput->setStringData(ARGSTR(0)); );
    return args.This();
  }

  JS_METHOD(_domlsinputsetbytestream) {
    if (args.Length()!=1) {
      return JS_ERROR("[_domlsinputsetbytestream()] ERROR: incorrect number of input parameters");
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
      return JS_ERROR("[_domlsinputsetbytestream()] ERROR: \"src\" is a null pointer");
    }
    else {
      XLSTRY( domlsinput->setByteStream(src); );
      return args.This();
    }
  }

  JS_METHOD(_domlsinputsetencoding) {
    if (args.Length()!=1) {
      return JS_ERROR("[_domlsinputsetstringdata()] ERROR: incorrect number of input parameters");
    }
    DOMLSINPUT;
    XLSTRY( domlsinput->setEncoding(ARGSTR(0)); );
    return args.This();
  }

  JS_METHOD(_domlsinputsetpublicid) {
    if (args.Length()!=1) {
      return JS_ERROR("[_domlsinputsetpublicid()] ERROR: incorrect number of input parameters");
    }
    DOMLSINPUT;
    XLSTRY( domlsinput->setPublicId(ARGSTR(0)); );
    return args.This();
  }

  JS_METHOD(_domlsinputsetsystemid) {
    if (args.Length()!=1) {
      return JS_ERROR("[_domlsinputsetsystemid()] ERROR: incorrect number of input parameters");
    }
    DOMLSINPUT;
    XLSTRY( domlsinput->setSystemId(ARGSTR(0)); );
    return args.This();
  }

  JS_METHOD(_domlsinputsetbaseuri) {
    if (args.Length()!=1) {
      return JS_ERROR("[_domlsinputsetbaseuri()] ERROR: incorrect number of input parameters");
    }
    DOMLSINPUT;
    XLSTRY( domlsinput->setBaseURI(ARGSTR(0)); );
    return args.This();
  }

  JS_METHOD(_domlsinputsetissuefatalerrorifnotfound) {
    if (args.Length()!=1) {
      return JS_ERROR("[_domlsinputsetissuefatalerrorifnotfound()] ERROR: incorrect number of input parameters");
    }
    DOMLSINPUT;
    XLSTRY( domlsinput->setIssueFatalErrorIfNotFound(args[0]->ToBoolean()->BooleanValue()); );
    return args.This();
  }

  JS_METHOD(_domlsinputgetissuefatalerrorifnotfound) {
    if (args.Length()>0) {
      return JS_ERROR("[_domlsinputgetissuefatalerrorifnotfound()] ERROR: incorrect number of input parameters");
    }
    DOMLSINPUT;
    bool ret = false;
    XLSTRY( ret = domlsinput->getIssueFatalErrorIfNotFound(); );
    return JS_BOOL(ret);
  }

  JS_METHOD(_domlsinput_destructor) {
    /* TryCatch tc; */
    //DOMLSINPUT;
    //XLSTRY( domlsinput->~DOMLSInput(); );
    return args.This();
  }


  //	DOMLSOutput
  //
  JS_METHOD(_domlsoutput) {
    TryCatch tc;
    if (args.Length()<1)
      return JS_ERROR("[_domlsoutput()] ERROR: Missing output parameter");
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
      return JS_ERROR("[_domlsoutput()] ERROR: \"domlsoutput\" is a null pointer");
    }
    else {
      SAVE_PTR(0, domlsoutput);
      return args.This();
    }
  }

  JS_METHOD(_domlsoutputgetbytestream) {
    DOMLSOUTPUT;
    XMLFormatTarget * dst = NULL;
    XLSTRY( dst = domlsoutput->getByteStream(); );
    if (dst==NULL) {
      return JS_ERROR("[_domlsoutputgetbytestream()] ERROR: \"dst\" is a null pointer");
    }
    else {
      Local<Value> fargv[] = { External::New((void *)dst) };
      XMLSize_t fargc = 1;
      Handle<Value> ret( xdom::fformattarget->GetFunction()->NewInstance(fargc, fargv) );
      return ret;
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
    return JS_STR(ret);
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
    return JS_STR(ret);
  }

  JS_METHOD(_domlsoutputsetencoding) {
    if (args.Length()!=1) {
      return JS_ERROR("[_domlsoutputsetstringdata()] ERROR: incorrect number of output parameters");
    }
    DOMLSOUTPUT;
    XLSTRY( domlsoutput->setEncoding(ARGSTR(0)); );
    return args.This();
  }

  JS_METHOD(_domlsoutputsetsystemid) {
    if (args.Length()!=1) {
      return JS_ERROR("[_domlsoutputsetsystemid()] ERROR: incorrect number of output parameters");
    }
    DOMLSOUTPUT;
    XLSTRY( domlsoutput->setSystemId(ARGSTR(0)); );
    return args.This();
  }

  JS_METHOD(_domlsoutputsetbytestream) {
    if (args.Length()!=1) {
      return JS_ERROR("[_domlsoutputsetbytestream()] ERROR: incorrect number of output parameters");
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
      return JS_ERROR("[_domlsoutputsetbytestream()] ERROR: \"target\" is a null pointer");
    }
    else {
      XLSTRY( domlsoutput->setByteStream(target); );
      return args.This();
    }
  }

  JS_METHOD(_domlsoutput_destructor) {
    /* TryCatch tc; */
    //DOMLSOUTPUT;
    //XLSTRY( domlsoutput->~DOMLSOutput(); );
    return args.This();
  }


  //	BinInputStream
  //
  JS_METHOD(_bininput) {
    /* TryCatch tc; */
    if (args.Length()<1)
      return JS_ERROR("[_bininput()] ERROR: Missing input parameter");
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
      return JS_ERROR("[_bininput()] ERROR: \"bininputstream\" is a null pointer");
    }
    else {
      SAVE_PTR(0, bininputstream);
      return args.This();
    }
  }

  JS_METHOD(_bininputcurpos) {
    //BININPUT;
    return args.This();
  }

  JS_METHOD(_bininputreadbytes) {
    //BININPUT;
    return args.This();
  }

  JS_METHOD(_bininputgetcontenttype) {
    //BININPUT;
    return args.This();
  }

  JS_METHOD(_bininput_destructor) {
    /* TryCatch tc; */
    //FILEINPUT;
    //XTRY( xpath->~BinInputStream (); );
    return args.This();
  }

  //	BinFileInputStream
  //
  JS_METHOD(_binfileinput) {
    /* TryCatch tc; */
    if (args.Length()<1)
      return JS_ERROR("[_binfileinput()] ERROR: Missing input parameter");
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
      return JS_ERROR("[_binfileinput()] ERROR: \"binfileinput\" is a null pointer");
    }
    else {
      SAVE_PTR(0, binfileinput);
      return args.This();
    }
  }

  JS_METHOD(_binfileinputgetisopen) {
    //BINFILEINPUT;
    return args.This();
  }

  JS_METHOD(_binfileinputgetsize) {
    //BINFILEINPUT;
    return args.This();
  }

  JS_METHOD(_binfileinputreset) {
    //BINFILEINPUT;
    return args.This();
  }

  JS_METHOD(_binfileinput_destructor) {
    /* TryCatch tc; */
    //FILEINPUT;
    //XTRY( xpath->~BinFileInputStream (); );
    return args.This();
  }


  //	BinMemInputStream
  //
  JS_METHOD(_binmeminputstream) {
    /* TryCatch tc; */
    if (args.Length()<1)
      return JS_ERROR("[_binmeminputstream()] ERROR: Missing input parameter");
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
      return JS_ERROR("[_binmeminputstream()] ERROR: \"binmeminputstream\" is a null pointer");
    }
    else {
      SAVE_PTR(0, binmeminputstream);
      return args.This();
    }
  }

  JS_METHOD(_binmeminputstreamgetsize) {
    //BINMEMINPUT;
    return args.This();
  }

  JS_METHOD(_binmeminputstreamreset) {
    //BINMEMINPUT;
    return args.This();
  }

  JS_METHOD(_binmeminputstream_destructor) {
    /* TryCatch tc; */
    //FILEINPUT;
    //XTRY( xpath->~BinMemInputStream (); );
    return args.This();
  }


  //	Buffer
  //
  JS_METHOD(_buffer) {
    /* TryCatch tc; */
    if (args.Length()<1)
      return JS_ERROR("[_buffer()] ERROR: Missing input parameter");
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
      return JS_ERROR("[_buffer()] ERROR: \"buf\" is a null pointer");
    }
    else {
      SAVE_PTR(0, buf);
      SAVE_PTR(1, size);
      return args.This();
    }
  }

  JS_METHOD(_buffer_destructor) {
    /* TryCatch tc; */
    //FILEINPUT;
    //XTRY( xpath->~BinMemInputStream (); );
    return args.This();
  }


  //	DOMMemoryManager
  //
  JS_METHOD(_dommemorymanager) {
    TryCatch tc;
    if (args.Length()<1)
      return JS_ERROR("[_dommemorymanager()] ERROR: Missing input parameter");
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
      return JS_ERROR("[_dommemorymanager()] ERROR: \"dommm\" is a null pointer");
    }
    else {
      SAVE_PTR(0, dommm);
      return args.This();
    }
  }

  JS_METHOD(_dommemorymanagerallocate) {
    TryCatch tc;
    if (args.Length()!=1 && args.Length()!=2) {
      return JS_ERROR("[_dommemorymanagerallocate()] ERROR: Incorrect number of input parameters");
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
    Local<Value> fargv[] = { External::New((void *)buf), Integer::New(size) };
    XMLSize_t fargc = 2;
    Handle<Object> ret( fbuffer->GetFunction()->NewInstance(fargc,fargv) );
    return ret;
  }

  JS_METHOD(_dommemorymanagergetmemoryallocationblocksize) {
    TryCatch tc;
    if (args.Length()>0) {
      return JS_ERROR("[_dommemorymanagergetmemoryallocationblocksize()] ERROR: Incorrect number of input parameters");
    }
    DOMMEMMGR;
    XMLSize_t size = 0;
    XTRY( size = dommm->getMemoryAllocationBlockSize(); );
    return JS_INT(size);
  }

  JS_METHOD(_dommemorymanagersetmemoryallocationblocksize) {
    TryCatch tc;
    if (args.Length()!=1) {
      return JS_ERROR("[_dommemorymanagersetmemoryallocationblocksize()] ERROR: Incorrect number of input parameters");
    }
    DOMMEMMGR;
    XMLSize_t size = (XMLSize_t)args[0]->ToInteger()->IntegerValue();
    XTRY( dommm->setMemoryAllocationBlockSize(size); );
    return args.This();
  }

  JS_METHOD(_dommemorymanagerclonestring) {
    TryCatch tc;
    if (args.Length()!=1) {
      return JS_ERROR("[_dommemorymanagerclonestring()] ERROR: Incorrect number of input parameters");
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
    return JS_STR(ret);
  }

  JS_METHOD(_dommemorymanager_destructor) {
    /* TryCatch tc; */
    DOMMEMMGR;
    XTRY( dommm->~DOMMemoryManager(); );
    return args.This();
  }


  //	MemoryManager
  //
  JS_METHOD(_memorymanager) {
    TryCatch tc;
    if (args.Length()<1)
      return JS_ERROR("[_memorymanager()] ERROR: Missing input parameter");
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
      return JS_ERROR("[_memorymanager()] ERROR: \"mm\" is a null pointer");
    }
    else {
      SAVE_PTR(0, mm);
      return args.This();
    }
  }

  JS_METHOD(_memorymanagergetexceptionmemorymanager) {
    TryCatch tc;
    MM;
    MemoryManager * exmm = NULL;
    XTRY( exmm = mm->getExceptionMemoryManager(); );
    if (exmm==NULL) {
      return JS_ERROR("[_memorymanagergetexceptionmemorymanager()] ERROR: \"exmm\" is a null pointer");
    }
    else {
      Local<Value> fargv[] = { External::New((void *)exmm) };
      XMLSize_t fargc = 1;
      Handle<Object> ret( fmemorymanager->GetFunction()->NewInstance(fargc,fargv) );
      return ret;
    }
  }

  JS_METHOD(_memorymanagerallocate) {
    TryCatch tc;
    if (args.Length()!=1) {
      return JS_ERROR("[_memorymanagerallocate()] ERROR: Incorrect number of input parameters");
    }
    MM;
    XMLSize_t size = (XMLSize_t)args[0]->ToInteger()->IntegerValue();
    void * buf = NULL;
    XTRY( buf = mm->allocate(size); );
    Local<Value> fargv[] = { External::New((void *)buf), Integer::New(size) };
    XMLSize_t fargc = 2;
    Handle<Object> ret( fbuffer->GetFunction()->NewInstance(fargc,fargv) );
    return ret;
  }

  JS_METHOD(_memorymanagerdeallocate) {
    TryCatch tc;
    if (args.Length()!=1) {
      return JS_ERROR("[_memorymanagerallocate()] ERROR: Incorrect number of input parameters");
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
    return args.This();
  }

  JS_METHOD(_memorymanager_destructor) {
    TryCatch tc;
    //FILEINPUT;
    //XTRY( xpath->~BinMemInputStream (); );
    return args.This();
  }


  /**
   *	InputSource
   **/
  JS_METHOD(_inputsource) {
    TryCatch tc;
    if (args.Length()<1)
      return JS_ERROR("[_inputsource()] ERROR: Missing input parameter");
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
      return JS_ERROR("[_inputsource()] ERROR: \"inputsource\" is a null pointer");
    }
    else {
      SAVE_PTR(0, inputsource);
      return args.This();
    }
  }

  JS_METHOD(_inputsourcemakestream) {
    TryCatch tc;
    if (args.Length()>0) {
      return JS_ERROR("[_inputsourcemakestream()] ERROR: Too many input parameters");
    }
    INPUTSOURCE;
    Handle<Object> ret;
    BinInputStream * bin = NULL;
    XTRY( bin = inputsource->makeStream(); );
    if (bin==NULL) {
      return JS_ERROR("[_inputsourcemakestream()] ERROR: \"bin\" is a null pointer");
    }
    else {
      Local<Value> fargv[] = { External::New((void *)bin) };
      XMLSize_t fargc = 1;
      ret = xdom::fbininput->GetFunction()->NewInstance(fargc, fargv);
    }
    return ret;
  }

  JS_METHOD(_inputsourcegetencoding) {
    TryCatch tc;
    if (args.Length()>0) {
      return JS_ERROR("[_inputsourcegetencoding()] ERROR: Too many input parameters");
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
    return JS_STR(ret);
  }

  JS_METHOD(_inputsourcegetpublicid) {
    if (args.Length()>0) {
      return JS_ERROR("[_inputsourcegetpublicid()] ERROR: Too many input parameters");
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
    return JS_STR(ret);
  }

  JS_METHOD(_inputsourcegetsystemid) {
    if (args.Length()>0) {
      return JS_ERROR("[_inputsourcegetsystemid()] ERROR: Too many input parameters");
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
    return JS_STR(ret);
  }

  JS_METHOD(_inputsourcegetissuefatalerrorifnotfound) {
    if (args.Length()>0) {
      return JS_ERROR("[_inputsourcegetissuefatalerrorifnotfound()] ERROR: Too many input parameters");
    }
    INPUTSOURCE;
    bool ret = false;
    XTRY( ret = inputsource->getIssueFatalErrorIfNotFound(); );
    return JS_BOOL(ret);
  }

  JS_METHOD(_inputsourcegetmemorymanager) {
    if (args.Length()>0) {
      return JS_ERROR("[_inputsourcegetmemorymanager()] ERROR: Too many input parameters");
    }
    INPUTSOURCE;
    Handle<Object> ret;
    MemoryManager * mm = NULL;
    XTRY( mm = inputsource->getMemoryManager(); );
    if (mm==NULL) {
      return JS_ERROR("[_inputsourcegetmemorymanager()] ERROR: \"mm\" is a null pointer");
    }
    else {
      Local<Value> fargv[] = { External::New((void *)mm) };
      XMLSize_t fargc = 1;
      ret = xdom::fmemorymanager->GetFunction()->NewInstance(fargc, fargv);
    }
    return ret;
  }

  JS_METHOD(_inputsourcesetencoding) {
    if (args.Length()!=1) {
      return JS_ERROR("[_inputsourcesetencoding()] ERROR: Incorrect number of input parameters");
    }
    INPUTSOURCE;
    XTRY( inputsource->setEncoding(ARGSTR(0)); );
    return args.This();
  }

  JS_METHOD(_inputsourcesetpublicid) {
    if (args.Length()!=1) {
      return JS_ERROR("[_inputsourcesetpublicid()] ERROR: Incorrect number of input parameters");
    }
    INPUTSOURCE;
    XTRY( inputsource->setPublicId(ARGSTR(0)); );
    return args.This();
  }

  JS_METHOD(_inputsourcesetsystemid) {
    if (args.Length()!=1) {
      return JS_ERROR("[_inputsourcesetsystemid()] ERROR: Incorrect number of input parameters");
    }
    INPUTSOURCE;
    XTRY( inputsource->setSystemId(ARGSTR(0)); );
    return args.This();
  }

  JS_METHOD(_inputsourcesetissuefatalerrorifnotfound) {
    if (args.Length()!=1) {
      return JS_ERROR("[_inputsourcesetissuefatalerrorifnotfound()] ERROR: Incorrect number of input parameters");
    }
    INPUTSOURCE;
    XTRY( inputsource->setIssueFatalErrorIfNotFound(args[0]->ToBoolean()->BooleanValue()); );
    return args.This();
  }

  JS_METHOD(_inputsource_destructor) {
    /* TryCatch tc; */
    //INPUTSOURCE;
    //XTRY( xpath->~InputSource (); );
    return args.This();
  }


  //	LocalFileInputSource
  //
  JS_METHOD(_fileinput) {
    /* TryCatch tc; */
    if (args.Length()<1) {
      return JS_ERROR("[_fileinput()] ERROR: Missing input parameter");
    }
    ASSERT_CONSTRUCTOR;
    if (xdom::initialized!=true) {
      xercesc_3_0::XMLPlatformUtils::Initialize();
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
      return JS_ERROR("[_fileinput()] ERROR: \"fileinput\" is a null pointer");
    }
    else {
      SAVE_PTR(0, fileinput);
      return args.This();
    }
  }

  JS_METHOD(_fileinput_destructor) {
    /* TryCatch tc; */
    //FILEINPUT;
    //XTRY( xpath->~LocalFileInputSource (); );
    return args.This();
  }


  //	MemBufInputSource
  //
  JS_METHOD(_membufinput) {
    /* TryCatch tc; */
    if (args.Length()<1) {
      return JS_ERROR("[_membuf()] ERROR: Missing input parameter");
    }
    bool * adopt = new bool;
    *adopt = false;
    ASSERT_CONSTRUCTOR;
    if (xdom::initialized!=true) {
      xercesc_3_0::XMLPlatformUtils::Initialize();
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
      SS tmp( *String::Utf8Value(args[0]->ToString()) );
      char * src = strdup(tmp.str().c_str());
      size_t isize = strlen(src);
      XMLSize_t * len = reinterpret_cast<XMLSize_t *>(&isize);
      membuf = new MemBufInputSource(reinterpret_cast<const XMLByte *>(src),*len,"test",false);
      *adopt = true;
    }
    if (membuf==NULL) {
      return JS_ERROR("[_membuf()] ERROR: \"membuf\" is a null pointer");
    }
    else {
      SAVE_PTR(0, membuf);
      SAVE_PTR(1, adopt);
      return args.This();
    }
  }

  JS_METHOD(_membufinputsetcopybuftostream) {
    if (args.Length()!=1) {
      return JS_ERROR("[_membufinputsetcopybuftostream()] ERROR: Incorrect number of input parameters");
    }
    MEMBUFINPUT;
    const bool newState = args[0]->ToBoolean()->BooleanValue();
    XTRY( membuf->setCopyBufToStream(newState); );
    return args.This();
  }

  JS_METHOD(_membufinputresetmembufinputsource) {
    if (args.Length()!=1 && args.Length()!=2) {
      return JS_ERROR("[_membufinputresetmembufinputsource()] ERROR: Incorrect number of input parameters");
    }
    MEMBUFINPUT;
    const XMLByte *const srcDocBytes = reinterpret_cast<const XMLByte *const>(*String::Utf8Value(args[0]->ToString()));
    const XMLSize_t byteCount = strlen((const char *)srcDocBytes);
    XTRY( membuf->resetMemBufInputSource(srcDocBytes,byteCount); );
    return args.This();
  }

  JS_METHOD(_membufinput_destructor) {
    /* TryCatch tc; */
    MEMBUFINPUT;
    bool * adopt = LOAD_PTR(1,bool *);
    if (*adopt==true) {
      delete membuf;
    }
    return args.This();
  }


  //	StdInInputSource
  //
  JS_METHOD(_stdin) {
    /* TryCatch tc; */
    if (args.Length()<1) {
      return JS_ERROR("[_stdin()] ERROR: Missing input parameter");
    }
    ASSERT_CONSTRUCTOR;
    if (xdom::initialized!=true) {
      xercesc_3_0::XMLPlatformUtils::Initialize();
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
      return JS_ERROR("[_stdin()] ERROR: \"my_stdin\" is a null pointer");
    }
    else {
      SAVE_PTR(0, my_stdin);
      return args.This();
    }
  }

  JS_METHOD(_stdin_destructor) {
    /* TryCatch tc; */
    STDIN;
    XTRY( my_stdin->~StdInInputSource(); );
    return args.This();
  }


  //	XMLURL
  //
  JS_METHOD(_xmlurl) {
    /* TryCatch tc; */
    if (args.Length()<1) {
      return JS_ERROR("[_xmlurl()] ERROR: Missing input parameter");
    }
    ASSERT_CONSTRUCTOR;
    if (xdom::initialized!=true) {
      xercesc_3_0::XMLPlatformUtils::Initialize();
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
      return JS_ERROR("[_xmlurl()] ERROR: \"xmlurl\" is a null pointer");
    }
    else {
      SAVE_PTR(0, xmlurl);
      return args.This();
    }
  }

  JS_METHOD(_xmlurlgetfragment) {
    LXMLURL;
    XS txt = NULL;
    XTRY( txt = (XMLCh *)xmlurl->getFragment(); );
    if (txt==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(txt);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_xmlurlgethost) {
    LXMLURL;
    XS txt = NULL;
    XTRY( txt = (XMLCh *)xmlurl->getHost(); );
    if (txt==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(txt);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_xmlurlgetpassword) {
    LXMLURL;
    XS txt = NULL;
    XTRY( txt = (XMLCh *)xmlurl->getPassword(); );
    if (txt==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(txt);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_xmlurlgetpath) {
    LXMLURL;
    XS txt = NULL;
    XTRY( txt = (XMLCh *)xmlurl->getPath(); );
    if (txt==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(txt);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_xmlurlgetportnum) {
    LXMLURL;
    unsigned int ret = 0;
    XTRY( ret = xmlurl->getPortNum(); );
    return JS_INT(ret);
  }

  JS_METHOD(_xmlurlgetprotocol) {
    LXMLURL;
    unsigned int ret = 0;
    XTRY( ret = (unsigned int)xmlurl->getPortNum(); );
    return JS_INT(ret);
  }

  JS_METHOD(_xmlurlgetprotocolname) {
    LXMLURL;
    XS txt = NULL;
    XTRY( txt = (XMLCh *)xmlurl->getProtocolName(); );
    if (txt==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(txt);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_xmlurlgetquery) {
    LXMLURL;
    XS txt = NULL;
    XTRY( txt = (XMLCh *)xmlurl->getQuery(); );
    if (txt==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(txt);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_xmlurlgeturltext) {
    LXMLURL;
    XS txt = NULL;
    XTRY( txt = (XMLCh *)xmlurl->getURLText(); );
    if (txt==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(txt);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_xmlurlgetuser) {
    LXMLURL;
    XS txt = NULL;
    XTRY( txt = (XMLCh *)xmlurl->getUser(); );
    if (txt==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(txt);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_xmlurlgetmemorymanager) {
    //LXMLURL;
    return args.This();
  }

  JS_METHOD(_xmlurlseturl) {
    LXMLURL;
    XTRY( xmlurl->setURL(ARGSTR(0)); );
    return args.This();
  }

  JS_METHOD(_xmlurlisrelative) {
    LXMLURL;
    bool ret = false;
    XTRY( ret = xmlurl->isRelative(); );
    return JS_BOOL(ret);
  }

  JS_METHOD(_xmlurlhasinvalidchar) {
    LXMLURL;
    bool ret = false;
    XTRY( ret = xmlurl->hasInvalidChar(); );
    return JS_BOOL(ret);
  }

  JS_METHOD(_xmlurlmakenewstream) {
    LXMLURL;
    BinInputStream * bin = NULL;
    XTRY( bin = xmlurl->makeNewStream(); );
    if (bin==NULL) {
      return JS_STR("[_xmlurlmakenewstream()] ERROR: \"bin\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      Handle<Value> fargv[] = { External::New((void *)bin) };
      Handle<Object> ret( xdom::fbininput->GetFunction()->NewInstance(fargc, fargv) );
      return ret;
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
      return JS_STR("[_xmlurlmakerelativeto()] ERROR: \"base\" is a null pointer");
    }
    else {
      XTRY( xmlurl->makeRelativeTo((const XMLURL)*base); );
      return args.This();
    }
  }

  JS_METHOD(_xmlurllookupbyname) {
    //LXMLURL;
    return args.This();
  }

  JS_METHOD(_xmlurlparse) {
    LXMLURL;
    bool ret = false;
    XMLURL * url = RECAST(args[1],XMLURL *);
    XMLURL tmp = *url;
    XTRY( ret = xmlurl->parse((const XMLCh *)ARGSTR(0),(XMLURL &)*url); );
    return JS_BOOL(ret);
  }

  JS_METHOD(_xmlurl_destructor) {
    /* TryCatch tc; */
    //LXMLURL;
    //FILEINPUT;
    //XTRY( xpath->~XMLURL (); );
    return args.This();
  }


  //	URLInputSource
  //
  JS_METHOD(_urlinput) {
    /* TryCatch tc; */
    if (args.Length()<1) {
      return JS_ERROR("[_url()] ERROR: Missing input parameter");
    }
    ASSERT_CONSTRUCTOR;
    if (xdom::initialized!=true) {
      xercesc_3_0::XMLPlatformUtils::Initialize();
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
      return JS_ERROR("[_url()] ERROR: \"url\" is a null pointer");
    }
    else {
      SAVE_PTR(0, url);
      return args.This();
    }
  }

  JS_METHOD(_urlinputurlsrc) {
    return args.This();
  }

  JS_METHOD(_urlinput_destructor) {
    /* TryCatch tc; */
    //FILEINPUT;
    //XTRY( xpath->~URLInputSource (); );
    return args.This();
  }


  /**
   *	DOMXPathNamespace
   **/
  JS_METHOD(_xpathnamespace) {
    /* TryCatch tc; */
    if (args.Length()<1)
      return JS_ERROR("[_xpathnamespace()] ERROR: Missing input parameter");
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
      return JS_ERROR("[_xpathnamespace()] ERROR: \"xpath\" is a null pointer");
    }
    else {
      SAVE_PTR(0, xpath);
      return args.This();
    }
  }

  JS_METHOD(_xpathgetownerelement) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_xpathgetownerelement()] ERROR: Too many input parameters");
    XPATH;
    DOMElement * el = NULL;
    XTRY( el = xpath->getOwnerElement(); );
    if (el==NULL) {
      return JS_ERROR("[_xpathgetownerelement()] ERROR: \"el\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)el) };
      Handle<Object> ret( xdom::felement->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_xpathnamespace_destructor) {
    /* TryCatch tc; */
    //XPATH;
    //XTRY( xpath->~DOMXPathNamespace(); );
    return args.This();
  }


  //	**********************************************		//
  //	**********************************************		//

  /**
   *	DOMCDATASection
   **/
  JS_METHOD(_cdatasection) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_cdatasection()] ERROR: Incorrect number of input parameters");
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
      return JS_ERROR("[_cdatasection()] ERROR: \"cdatasect\" is a null pointer");
    }
    else {
      SAVE_PTR(0, cdatasect);
      return args.This();
    }
  }

  JS_METHOD(_cdatasection_destructor) {
    /* TryCatch tc; */
    //CDATASECT;
    //XTRY( cdatasect->~DOMCDATASection(); );
    return args.This();
  }


  /**
   *	DOMStringList
   **/

  JS_METHOD(_stringlist) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_stringlist()] ERROR: Incorrect number of input parameters");
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
      return JS_ERROR("[_stringlist()] ERROR: \"dslist\" is a null pointer");
    }
    else {
      SAVE_PTR(0, dslist);
      return args.This();
    }
  }

  JS_METHOD(_stringlistitem) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_stringlistitem()] ERROR: Incorrect number of input parameters");
    STRINGLIST;
    XMLSize_t index = (XMLSize_t)(args[0]->ToInteger()->IntegerValue());
    XS val = NULL;
    XTRY( val = (XMLCh *)dslist->item(index); );
    if (val==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(val);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_stringlistgetlength) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_stringlistgetlength()] ERROR: Too many input parameters");
    STRINGLIST;
    XMLSize_t length = 0;
    XTRY( length = dslist->getLength(); );
    return JS_INT(length);
  }

  JS_METHOD(_stringlistcontains) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_stringlistcontains()] ERROR: Incorrect number of input parameters");
    STRINGLIST;
    SS val(*String::Utf8Value(args[0]->ToString()));
    bool ret = false;
    XTRY( ret = dslist->contains(X_STR(val)); );
    return JS_BOOL(ret);
  }

  JS_METHOD(_stringlist_destructor) {
    /* TryCatch tc; */
    //STRINGLIST;
    XTRY(
	//dslist->release();
	//dslist->~DOMStringList(); 
    );
    return args.This();
  }

  /**
   *	DOMNamedNodeMap
   **/

  JS_METHOD(_namednodemap) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_namednodemap()] ERROR: Incorrect number of input parameters");
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
      return JS_ERROR("[_namednodemap()] ERROR: \"nodemap\" is a null pointer");
    }
    else {
      SAVE_PTR(0, nodemap);
      return args.This();
    }
  }

  JS_METHOD(_nodemapitem) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_nodemapitem()] ERROR: Incorrect number of input parameters");
    NODEMAP;
    XMLSize_t index = (XMLSize_t)(args[0]->ToInteger()->IntegerValue());
    DOMNode * item = NULL;
    XTRY( item = nodemap->item(index); );
    if (item==NULL) {
      return JS_ERROR("[_nodemapitem()] ERROR: \"item\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)item) };
      Handle<Object> ret( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_nodemapgetlength) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_nodemapgetlength()] ERROR: Too many input parameters");
    NODEMAP;
    XMLSize_t length = 0;
    XTRY( length = nodemap->getLength(); );
    return JS_INT(length);
  }

  JS_METHOD(_nodemapgetnameditem) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_nodemapgetnameditem()] ERROR: Incorrect number of input parameters");
    NODEMAP;
    DOMNode * item = NULL;
    XTRY( item = nodemap->getNamedItem(ARGSTR(0)); );
    if (item==NULL) {
      return JS_ERROR("[_nodemapgetnameditem()] ERROR: \"item\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)item) };
      Handle<Object> ret( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_nodemapgetnameditemns) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_nodemapgetnameditemns()] ERROR: Incorrect number of input parameters");
    NODEMAP;
    DOMNode * item = NULL;
    XTRY( item = nodemap->getNamedItemNS(ARGSTR(0),ARGSTR(1)); );
    if (item==NULL) {
      return JS_ERROR("[_nodemapgetnameditemns()] ERROR: \"item\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)item) };
      Handle<Object> ret( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_nodemapsetnameditem) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_nodemapsetnameditem()] ERROR: Incorrect number of input parameters");
    NODEMAP;
    DOMNode * arg = NULL;
    if (args[0]->IsExternal()) {
      arg = RECAST(args[0],DOMNode *);
    }
    else if (args[0]->IsObject()) {
      Local<Object> tobj( args[0]->ToObject() );
      arg = RECAST(tobj->GetInternalField(0),DOMNode *);
    }
    if (arg==NULL)
      return JS_ERROR("[_nodemapsetnameditem()] ERROR: \"arg\" is a null pointer");
    else {
      DOMNode * newNode = NULL;
      XTRY( newNode = nodemap->setNamedItem(arg); );
      if (newNode==NULL) {
	return JS_ERROR("[_nodemapsetnameditem()] ERROR: \"newNode\" is a null pointer");
      }
      else {
	Handle<Value> fargs[] = { External::New((void *)newNode) };
	Handle<Object> ret( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
	return ret;
      }
    }
  }

  JS_METHOD(_nodemapsetnameditemns) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_nodemapsetnameditemns()] ERROR: Incorrect number of input parameters");
    NODEMAP;
    DOMNode * arg = NULL;
    if (args[0]->IsExternal()) {
      arg = RECAST(args[0],DOMNode *);
    }
    else if (args[0]->IsObject()) {
      Local<Object> tobj( args[0]->ToObject() );
      arg = RECAST(tobj->GetInternalField(0),DOMNode *);
    }
    if (arg==NULL) {
      return JS_ERROR("[_nodemapsetnameditem()] ERROR: \"arg\" is a null pointer");
    }
    else {
      DOMNode * newNode = NULL;
      XTRY( newNode = nodemap->setNamedItemNS(arg); );
      if (newNode==NULL) {
	return JS_ERROR("[_nodemapsetnameditem()] ERROR: \"newNode\" is a null pointer");
      }
      else {
	Handle<Value> fargs[] = { External::New((void *)newNode) };
	Handle<Object> ret( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
	return ret;
      }
    }
  }

  JS_METHOD(_nodemapremovenameditem) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_nodemapremovenameditem()] ERROR: Incorrect number of input parameters");
    NODEMAP;
    DOMNode * item = NULL;
    XTRY( item = nodemap->removeNamedItem(ARGSTR(0)); );
    if (item==NULL) {
      return JS_ERROR("[_nodemapremovenameditem()] ERROR: \"item\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)item) };
      Handle<Object> ret( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_nodemapremovenameditemns) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_nodemapremovenameditemns()] ERROR: Incorrect number of input parameters");
    NODEMAP;
    DOMNode * item = NULL;
    XTRY( item = nodemap->removeNamedItemNS(ARGSTR(0),ARGSTR(1)); );
    if (item==NULL) {
      return JS_ERROR("[_nodemapremovenameditemns()] ERROR: \"item\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)item) };
      Handle<Object> ret( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_namednodemap_destructor) {
    /* TryCatch tc; */
    NODEMAP;
    XTRY( nodemap->~DOMNamedNodeMap(); );
    return args.This();
  }

  /**
   *	DOMNodeList
   **/

  JS_METHOD(_nodelist) {
    /* TryCatch tc; */
    if (args.Length()<1)
      return JS_ERROR("[_nodelist()] ERROR: Missing input parameter");
    ASSERT_CONSTRUCTOR;
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMNodeList");
    DOMNodeList * nodelist = RECAST(args[0],DOMNodeList *);
    SAVE_PTR(0, nodelist);
    return args.This();
  }

  JS_METHOD(_nodelistitem) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_nodelistitem()] ERROR: Incorrect number of input parameters");
    NODELIST;
    XMLSize_t index = (XMLSize_t)(args[0]->ToInteger()->IntegerValue());
    DOMNode * item = NULL;
    XTRY( item = nodelist->item(index); );
    if (item==NULL) {
      return JS_ERROR("[_nodelistitem()] ERROR: \"item\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)item) };
      Handle<Object> ret( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_nodelistgetlength) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_nodelistgetlength()] ERROR: Too many input parameters");
    NODELIST;
    XMLSize_t length = 0;
    XTRY( length = nodelist->getLength(); );
    return JS_INT(length);
  }

  JS_METHOD(_nodelisttoarray) {
    //TryCatch tc;
    if (args.Length()>0)
      return JS_ERROR("[_nodelisttoarray()] ERROR: Too many input parameters");
    NODELIST;
    Handle<Array> ret;
    XMLSize_t len = 0;
    XTRY( len = nodelist->getLength(); );
    if (len > 0) {
      ret = v8::Array::New(len);
      for (unsigned int i = (int)len; i < len; i++) {
	DOMNode * val = NULL;
	XTRY( val = nodelist->item(i); );
	if (val==NULL) {
	  return JS_ERROR("[_nodelisttoarray()] ERROR: \"val\" is a null pointer");
	}
	else {
	  Local<Value> fargs[] = { v8::External::New((void *)val) };
	  Handle<Object> tmp( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
	  ret->Set(JS_INT(i), tmp);
	}
      }
    }
    return ret;
  }

  JS_METHOD(_nodelist_destructor) {
    /* TryCatch tc; */
    NODELIST;
    XTRY( nodelist->~DOMNodeList(); );
    return args.This();
  }

  /**
   *	DOMUserDataHandler
   **/
  JS_METHOD(_domuserdatahandler) {
    /* TryCatch tc; */
    if (args.Length()<1) {
      return JS_ERROR("[_domuserdatahandler()] ERROR: Missing input parameter");
    }
    ASSERT_CONSTRUCTOR;
    if (xdom::initialized!=true) {
      xercesc_3_0::XMLPlatformUtils::Initialize();
      xdom::initialized=true;
    }
    SAVE_PTR(0, NULL);
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMUserDataHandler");
    DOMUserDataHandler * dhandler = NULL;
    if (args.Length()>1) {
      
      return v8::Undefined();
    }
    else {
      if (args[0]->IsExternal()) {
	dhandler = RECAST(args[0],DOMUserDataHandler *);
      }
      else if (args[0]->IsObject()) {
	dhandler = RECAST(args[0]->ToObject()->GetInternalField(0),DOMUserDataHandler *);
      }
      if (dhandler==NULL) {
	return JS_ERROR("[_domuserdatahandler()] ERROR: \"dhandler\" is a null pointer");
      }
      else {
	SAVE_PTR(0, dhandler);
	return args.This();
      }
    }
  }

  JS_METHOD(_domuserdatahandlerhandle) {
    /* TryCatch tc; */
    if (args.Length()!=5) {
      return JS_ERROR("[_domuserdatahandlerhandle()] ERROR: Incorrect number of input parameters");
    }
    if (xdom::initialized!=true) {
      xercesc_3_0::XMLPlatformUtils::Initialize();
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
      Local<Object> tobj( args[3]->ToObject() );
      src = RECAST(tobj->GetInternalField(0),DOMNode *);
    }
    if (args[4]->IsExternal()) {
      dst = RECAST(args[4],DOMNode *);
    }
    else if (args[4]->IsObject()) {
      Local<Object> tobj( args[4]->ToObject() );
      dst = RECAST(tobj->GetInternalField(0),DOMNode *);
    }
    if (src==NULL) {
      return JS_ERROR("[_handle()] ERROR: \"src\" is a null pointer");
    }
    else if (dst==NULL) {
      return JS_ERROR("[_handle()] ERROR: \"dst\" is a null pointer");
    }
    else {
      XTRY( dhandler->handle(operation,ARGSTR(1),data,src,dst); );
      return args.This();
    }
  }

  JS_METHOD(_domuserdatahandler_destructor) {
    /* TryCatch tc; */
    USERDATAHANDLER;
    XTRY( dhandler->~DOMUserDataHandler(); );
    return args.This();
  }


  /**
   *	DOMImplementationLS constructor:
   *
   **/
  JS_METHOD(_implls) {
    /* TryCatch tc; */
    if (args.Length()!=1) {
      return JS_ERROR("[_implls()] ERROR: Incorrect number of input parameters");
    }
    ASSERT_CONSTRUCTOR;
    if (xdom::initialized!=true) {
      xercesc_3_0::XMLPlatformUtils::Initialize();
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
	  return JS_ERROR("[_implls()] ERROR: \"dom\" is a null pointer");
	}
	else {
	  domls = (DOMImplementationLS *)dom;
	}
      }
    }
    if (domls==NULL) {
      return JS_ERROR("[_implls()] ERROR: \"domls\" is a null pointer");
    }
    else {
      SAVE_PTR(0,domls);
      return args.This();
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
      return JS_ERROR("[_createlsparser()] ERROR: \"parser\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      Local<Value> fargv[] = { External::New((void *)parser) };
      Handle<Object> ret( xdom::fparser->GetFunction()->NewInstance(fargc,fargv) );
      return ret;
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
      return JS_ERROR("[_createlsserializer()] ERROR: \"serializer\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      Local<Value> fargv[] = { External::New((void *)serializer) };
      Handle<Object> ret( xdom::fserializer->GetFunction()->NewInstance(fargc,fargv) );
      return ret;
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
      return JS_ERROR("[_createlsinput()] ERROR: \"lsinput\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      Local<Value> fargv[] = { External::New((void *)lsinput) };
      Handle<Object> ret( xdom::finput->GetFunction()->NewInstance(fargc,fargv) );
      return ret;
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
      return JS_ERROR("[_createlsoutput()] ERROR: \"lsoutput\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      Local<Value> fargv[] = { External::New((void *)lsoutput) };
      Handle<Object> ret( xdom::foutput->GetFunction()->NewInstance(fargc,fargv) );
      return ret;
    }
  }


  /**
   *	~DOMImplementationLS method
   *	- Destructor for DOMImplementationLS objects
   */ 
  JS_METHOD(_implls_destructor) {
    /* TryCatch tc; */
    SAVE_PTR(0,NULL);
    return args.This();
  }


  /**
   *	DOMImplementation constructor:
   * 	- Adds "~DOMImplementation()" destructor method to global Garbage Collector
   **/
  JS_METHOD(_impl) {
    /* TryCatch tc; */
    ASSERT_CONSTRUCTOR;
    // initialize the XML library
    if (xdom::initialized!=true) {
      xercesc_3_0::XMLPlatformUtils::Initialize();
      xdom::initialized=true;
    }
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMImplementation");
    SAVE_PTR(0,NULL);
    DOMImplementation * dom = NULL;
    const XMLCh dfltSchemaType[] = {chLatin_L, chLatin_S, chNull};
    XMLCh * schemaType = (XMLCh *)dfltSchemaType;
    if (args.Length()==0) {
      dom = xercesc_3_0::DOMImplementationRegistry::getDOMImplementation(schemaType);
    }
    else {
      SS attr("");
      if (args[0]->IsExternal()) {
        dom = RECAST(args[0],xercesc_3_0::DOMImplementation *);
      }
      else if (args[0]->IsString()) {
	XTRY( dom = xercesc_3_0::DOMImplementationRegistry::getDOMImplementation((XMLCh *) *String::Utf8Value(args[0]->ToString())); );
      }
      else if (args[0]->IsObject()) {
	if (args[0]->ToObject()->Has(JS_STR("_domtype_"))) {
	  std::string domtype( *USTR(args[0]->ToObject()->Get(JS_STR("_domtype_"))->ToString()) );
	  if (domtype=="DOMImplementation") {
	    dom = RECAST(args[0]->ToObject()->GetInternalField(0),xercesc_3_0::DOMImplementation *);
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
	      schemaType = (XMLCh *) *String::Utf8Value( args[0]->ToObject()->Get(JS_STR("schema"))->ToString() );
	    }
	    XTRY( dom = xercesc_3_0::DOMImplementationRegistry::getDOMImplementation((const XMLCh *)schemaType); );
	  }
	}
      }
    }
    if (dom==NULL) {
      return JS_ERROR("[_impl()] ERROR: \"dom\" is a null pointer");
    }
    else {
      SAVE_PTR(0,dom);
      return args.This();
    }
  }

  JS_METHOD(_domcreateimplementationls) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_domcreateimplementationls()] ERROR: Too many input parameters");
    DOM;
    Local<Value> fargs[] = { External::New((void *)dom) };
    Handle<Object> ret( xdom::fdomls->GetFunction()->NewInstance(1, fargs) );
    return ret;
  }

  JS_METHOD(_domgetimplementation) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_domgetimplementation()] ERROR: Too many input parameters");
    DOM;
    Handle<Value> fargs[] = { External::New((void *)dom) };
    return Handle<Function>::Cast(args.This()->Get(JS_STR("DOMImplementation")))->NewInstance(1, fargs);
  }

  JS_METHOD(_domloaddomexceptionmsg) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_domloaddomexceptionmsg()] ERROR: Incorrect number of input parameters");
    DOM;
    short msgToLoad = (short)args[0]->ToInteger()->Int32Value();
    XS const toFill = ARGSTR(1);
    const XMLSize_t maxChars = sizeof(toFill);
    XTRY( dom->loadDOMExceptionMsg(msgToLoad, toFill, maxChars); );
    return args.This();
  }

  JS_METHOD(_domhasfeature) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_domhasfeature()] ERROR: Incorrect number of input parameters");
    DOM;
    bool ret = false;
    XTRY( ret = dom->hasFeature(ARGSTR(0),ARGSTR(1)); );
    return JS_BOOL(ret);
  }

  JS_METHOD(_domcreateparser) {
    /* TryCatch tc; */
    if (args.Length()>1)
      return JS_ERROR("[_domcreateparser()] ERROR: Incorrect number of input parameters");
    DOM;
    XS schemaType = NULL;
    if (args.Length()>0) {
      if (args[0]->IsString()) {
	schemaType = ARGSTR(0);
      }
    }
    DOMLSParser * parser = NULL;
    XLSTRY(
	parser = ((DOMImplementationLS *)dom)->createLSParser(xercesc_3_0::DOMImplementationLS::MODE_SYNCHRONOUS, schemaType);
//	parser = ((DOMImplementationLS *)dom)->createLSParser(xercesc_3_0::DOMImplementationLS::MODE_ASYNCHRONOUS, schemaType);
	//DOMConfiguration* dc = parser->getDomConfig();
	//dc->setParameter(XMLUni::fgXercesSchema, true);
	//dc->setParameter(XMLUni::fgXercesCacheGrammarFromParse, true);
	//dc->setParameter(XMLUni::fgXercesUseCachedGrammarInParse, true);
	//dc->setParameter(XMLUni::fgDOMValidate, true);
    );
    if (parser==NULL) {
      return JS_ERROR("[_impl()] ERROR: \"parser\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)parser), External::New((void *)dom) };
      Handle<Object> ret( xdom::fparser->GetFunction()->NewInstance(2, fargs) );
      return ret;
    }
  }

  JS_METHOD(_domcreatedocumenttype) {
    /* TryCatch tc; */
    if (args.Length()!=3 && args.Length()!=1)
      return JS_ERROR("[_domcreatedocumenttype()] ERROR: Incorrect number of input parameters");
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
	publicId = ARGSTR(1); // << *String::Utf8Value(args[1]->ToString());
    }
    if (!(args[2]->IsUndefined())) if (args[2]->IsString()) {
      if (!(args[2]->IsNull()))
	systemId = ARGSTR(2); // << *String::Utf8Value(args[2]->ToString());
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
      return JS_ERROR("[_domcreatedocumenttype()] ERROR: \"docType\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((DOMDocumentType *)docType) };
      Handle<Object> ret( xdom::fdocumenttype->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_domcreatedocument) {
    /* TryCatch tc; */
    if (args.Length()!=3 && args.Length()!=0)
      return JS_ERROR("[_domcreatedocumenttype()] ERROR: Incorrect number of input parameters");
    DOM;
    DOMDocumentType * docType = NULL;
    DOMDocument * doc = NULL;
    if (args.Length()==0) {
      XTRY( doc = dom->createDocument(); );
    }
    else {
      SS namespaceURI(*String::Utf8Value(args[0]->ToString()));
      SS qualifiedName(*String::Utf8Value(args[1]->ToString()));
      if (args[2]->IsExternal()) {
	docType = RECAST(args[2],DOMDocumentType *);
      }
      else if (args[2]->IsObject()) {
	Handle<Object> tobj = args[2]->ToObject();
	docType = RECAST(tobj->GetInternalField(0),DOMDocumentType *);
      }
      if (docType==NULL) {
	return JS_ERROR("[_domcreatedocument()] ERROR: \"docType\" is a null pointer");
      }
      else {
	XTRY( doc = dom->createDocument(X_STR(namespaceURI),X_STR(qualifiedName),docType); );
      }
    }
    if (doc==NULL) {
      return JS_ERROR("[_domcreatedocument()] ERROR: \"doc\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)doc) };
      Handle<Object> ret( xdom::fdocument->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  /**
   *	~DOM method
   *	- Destructor for DOMImplementation objects
   */ 
  JS_METHOD(_impl_destructor) {
    /* TryCatch tc; */
    DOM;
    if (dom!=NULL) {
      // SAVE_PTR(0,NULL);
      //X TRY( dom->~DOMImplementation(); );
    }
    //XMLPlatformUtils::Terminate();
    //xdom::initialized=false;
    return args.This();
  }


  /**
   *	DOMLSSerializer constructor:
   * 	- Adds "~DOMLSSerializer()" method to global GC
   */
  JS_METHOD(_serializer) {
    ///* TryCatch tc; */
    if (args.Length()<1) {
      return JS_ERROR("[_serializer()] ERROR: Missing input parameter");
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
      return JS_ERROR("[_serializer()] ERROR: \"serializer\" is a null pointer");
    }
    else {
      SAVE_PTR(0,serializer);
      SAVE_PTR(1,dom);
      return args.This();
    }
  }

  JS_METHOD(_serializergetdomconfig) {
    /* TryCatch tc; */
    if (args.Length()>0) {
      return JS_ERROR("[_serializergetdomconfig()] ERROR: Too many input parameters");
    }
    SERIALIZER;
    DOMConfiguration * domconfig = NULL;
    XLSTRY( domconfig = serializer->getDomConfig(); );
    if (domconfig==NULL) {
      return JS_ERROR("[_serializergetdomconfig()] ERROR: \"domconfig\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)domconfig) };
      Handle<Object> ret( xdom::fdomconfiguration->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_serializergetfilter) {
    /* TryCatch tc; */
    if (args.Length()>0) {
      return JS_ERROR("[_serializergetfilter()] ERROR: Too many input parameters");
    }
    SERIALIZER;
    DOMLSSerializerFilter * filter = NULL;
    XLSTRY( filter = (DOMLSSerializerFilter *)serializer->getFilter(); );
    if (filter==NULL) {
      return JS_ERROR("[_serializergetfilter()] ERROR: \"filter\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)filter) };
      Handle<Object> ret( xdom::fserializerfilter->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_serializergetnewline) {
    /* TryCatch tc; */
    if (args.Length()>0) {
      return JS_ERROR("[_serializergetfilter()] ERROR: Too many input parameters");
    }
    SERIALIZER;
    DOMLSSerializerFilter * filter = NULL;
    XLSTRY( filter = (DOMLSSerializerFilter *)serializer->getFilter(); );
    if (filter==NULL) {
      return JS_ERROR("[_serializergetfilter()] ERROR: \"filter\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)filter) };
      Handle<Object> ret( xdom::fserializerfilter->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_serializersetfilter) {
    /* TryCatch tc; */
    if (args.Length()!=1) {
      return JS_ERROR("[_serializersetfilter()] ERROR: Incorrect number of input parameters");
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
      return JS_ERROR("[_serializersetfilter()] ERROR: \"filter\" is a null pointer");
    }
    XLSTRY( serializer->setFilter(filter); );
    return args.This();
  }

  JS_METHOD(_serializersetnewline) {
    /* TryCatch tc; */
    if (args.Length()!=1) {
      return JS_ERROR("[_serializersetnewline()] ERROR: Incorrect number of input parameters");
    }
    SERIALIZER;
    XLSTRY( serializer->setNewLine(ARGSTR(0)); );
    return args.This();
  }

  JS_METHOD(_serializerwrite) {
    /* TryCatch tc; */
    if (args.Length()!=2) {
      return JS_ERROR("[_serializerwrite()] ERROR: Incorrect number of input parameters");
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
      return JS_ERROR("[_serializerwrite()] ERROR: \"node\" is a null pointer");
    }
    if (args[1]->IsExternal()) {
      dst = RECAST(args[1],DOMLSOutput *);
    }
    else if (args[0]->IsObject()) {
      dst = RECAST(args[1]->ToObject()->GetInternalField(1),DOMLSOutput *);
    }
    if (dst==NULL) {
      return JS_ERROR("[_serializerwrite()] ERROR: \"dst\" is a null pointer");
    }
    XLSTRY( serializer->write(node,dst); );
    return args.This();
  }

  JS_METHOD(_serializerwritetouri) {
    if (args.Length()!=2) {
      return JS_ERROR("[_serializerwritetouri()] ERROR: Incorrect number of input parameters");
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
      return JS_ERROR("[_serializerwritetouri()] ERROR: \"node\" is a null pointer");
    }
    XLSTRY( serializer->writeToURI(node,uri); );
    return args.This();
  }

  JS_METHOD(_serializerwritetostring) {
    if (args.Length()!=1) {
      return JS_ERROR("[_serializerwritetostring()] ERROR: Incorrect number of input parameters");
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
      return JS_ERROR("[_serializerwritetostring()] ERROR: \"node\" is a null pointer");
    }
    XLSTRY( ret = X(serializer->writeToString(node)); );
    if (ret==NULL) {
      return JS_ERROR("[_serializerwritetostring()] ERROR: \"ret\" is a null pointer");
    }
    else {
      return JS_STR(ret);
    }
  }


  JS_METHOD(_serializer_destructor) {
    /* TryCatch tc; */
    //SERIALIZER_DOM;
    //dom = NULL;
    // SAVE_PTR(0,NULL);
    // SAVE_PTR(1,NULL);
    XLSTRY(
	// serializer->release();
	// serializer->~DOMLSSerializer();
    );
    return args.This();
  }


  /**
   *	DOMLSSerializerFilter constructor:
   * 	- Adds "~DOMLSSerializerFilter()" method to global GC
   */
  JS_METHOD(_serializerfilter) {
    // /* TryCatch tc; */
    if (args.Length()<1) {
      return JS_ERROR("[_serializerfilter()] ERROR: Missing input parameter");
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
      return JS_ERROR("[_serializerfilter()] ERROR: \"filter\" is a null pointer");
    else {
      SAVE_PTR(0,filter);
      return args.This();
    }
  }

  JS_METHOD(_serializerfiltergetwhattoshow) {
    SERIALIZERFILTER;
    xercesc_3_0::DOMNodeFilter::ShowType ret = 0;
    XTRY( ret = filter->getWhatToShow(); );
    return JS_INT(ret);
  }

  /**
   *	~DOMLSSerializerFilter method
   *	- Destructor for DOMLSSerializerFilter objects
   */ 
  JS_METHOD(_serializerfilter_destructor) {
    /* TryCatch tc; */
    SERIALIZERFILTER;
    // SAVE_PTR(0,NULL);
    XLSTRY( filter->~DOMLSSerializerFilter(); );
    return args.This();
  }


  /**
   *	DOMNodeFilter constructor:
   * 	- Adds "~DOMNodeFilter()" method to global GC
   */
  JS_METHOD(_nodefilter) {
    // /* TryCatch tc; */
    if (args.Length()<1) {
      return JS_ERROR("[_domnodefilter()] ERROR: Missing input parameter");
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
      return JS_ERROR("[_domnodefilter()] ERROR: \"filter\" is a null pointer");
    else {
      SAVE_PTR(0,filter);
      return args.This();
    }
  }

  JS_METHOD(_nodefilteracceptnode) {
    NODEFILTER;
    xercesc_3_0::DOMNodeFilter::ShowType ret = 0;
    DOMNode * node = NULL;
    if (args[0]->IsExternal()) {
      node = RECAST(args[0],DOMNode *);
    }
    else if (args[0]->IsObject()) {
      node = RECAST(args[0]->ToObject()->GetInternalField(0),DOMNode *);	
    }
    XTRY( ret = filter->acceptNode(node); );
    return JS_INT(ret);
  }

  /**
   *	~DOMNodeFilter method
   *	- Destructor for DOMNodeFilter objects
   */ 
  JS_METHOD(_nodefilter_destructor) {
    /* TryCatch tc; */
    NODEFILTER;
    // SAVE_PTR(0,NULL);
    XLSTRY( filter->~DOMNodeFilter(); );
    return args.This();
  }


  /**
   *	DOMLSParser constructor:
   * 	- Adds "~DOMLSParser()" method to global GC
   */
  JS_METHOD(_parser) {
    ///* TryCatch tc; */
    if (args.Length()<1) {
      return JS_ERROR("[_parser()] ERROR: Missing input parameter");
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
      return JS_ERROR("[_parser()] ERROR: \"parser\" is a null pointer");
    }
    else {
      SAVE_PTR(0,parser);
      SAVE_PTR(1,dom);
      return args.This();
    }
  }

  JS_METHOD(_parsergetdomconfig) {
    /* TryCatch tc; */
    if (args.Length()>0) {
      return JS_ERROR("[_parsergetdomconfig()] ERROR: Too many input parameters");
    }
    PARSER;
    DOMConfiguration * domconfig = NULL;
    XLSTRY( domconfig = parser->getDomConfig(); );
    if (domconfig==NULL) {
      return JS_ERROR("[_parsergetdomconfig()] ERROR: \"domconfig\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)domconfig) };
      Handle<Object> ret( xdom::fdomconfiguration->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_parsergetfilter) {
    /* TryCatch tc; */
    if (args.Length()>0) {
      return JS_ERROR("[_parsergetfilter()] ERROR: Too many input parameters");
    }
    PARSER;
    DOMLSParserFilter * filter = NULL;
    XLSTRY( filter = (DOMLSParserFilter *)parser->getFilter(); );
    if (filter==NULL) {
      return JS_ERROR("[_parsergetfilter()] ERROR: \"filter\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)filter) };
      Handle<Object> ret( xdom::fparserfilter->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_parsergetasync) {
    /* TryCatch tc; */
    if (args.Length()>0) {
      return JS_ERROR("[_parsergetasync()] ERROR: Too many input parameters");
    }
    PARSER;
    bool async = false;
    XLSTRY( async = parser->getAsync(); );
    Handle<Boolean> ret( JS_BOOL(async) );
    return ret;
  }

  JS_METHOD(_parsergetbusy) {
    /* TryCatch tc; */
    if (args.Length()>0) {
      return JS_ERROR("[_parsergetbusy()] ERROR: Too many input parameters");
    }
    PARSER;
    bool busy = false;
    XLSTRY( busy = parser->getBusy(); );
    Handle<Boolean> ret( JS_BOOL(busy) );
    return ret;
  }

  JS_METHOD(_parsersetfilter) {
    /* TryCatch tc; */
    if (args.Length()!=1) {
      return JS_ERROR("[_parsersetfilter()] ERROR: Incorrect number of input parameters");
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
      return JS_ERROR("[_parsersetfilter()] ERROR: \"filter\" is a null pointer");
    }
    XLSTRY( parser->setFilter(filter); );
    return args.This();
  }

  JS_METHOD(_parserparse) {
    TryCatch tc;
    if (args.Length()!=1) {
      return JS_ERROR("[_parserparse()] ERROR: Incorrect number of input parameters");
    }
    PARSER_DOM;
    DOMLSInput * inv = NULL;
    if (args[0]->IsExternal()) {
      inv = RECAST(args[0],DOMLSInput *);
    }
    else if (args[0]->IsObject()) {
      Local<Object> tobj( args[0]->ToObject() );
      std::string domtype( *String::Utf8Value(tobj->Get(JS_STR("_domtype_"))->ToString()) );
      if (domtype=="DOMLSInput") {
	inv = RECAST(args[0]->ToObject()->GetInternalField(0),DOMLSInput *);
      }
    }
    else if (args[0]->IsString()) {
      SS tmp( *String::Utf8Value(args[0]->ToString()) );
      char * src = strdup(tmp.str().c_str());
      size_t isize = strlen(src);
      XMLSize_t * len = reinterpret_cast<XMLSize_t *>(&isize);
      MemBufInputSource * mem = new MemBufInputSource(reinterpret_cast<const XMLByte*>(src),*len,"test",false);
      if (dom==NULL) {
        return JS_ERROR("[_parserparse()] ERROR (1): \"dom\" is a null pointer");
      }
      inv = ((DOMImplementationLS *)dom)->createLSInput();
      mem->setCopyBufToStream(false);
      inv->setByteStream(mem);
      inv->setEncoding(XMLUni::fgUTF8EncodingString);
    }
    if (inv==NULL) {
      return JS_ERROR("[_parserparse()] ERROR (2): \"inv\" is a null pointer");
    }
    DOMDocument * doc = NULL;
    XLSTRY( doc = parser->parse(inv); );
    if (doc==NULL) {
      return JS_ERROR("[_parserparse()] ERROR (3): \"doc\" is a null pointer");
    }
    else {
        Handle<Value> fargs[] = { External::New((void *)doc) };
        Handle<Object> ret( xdom::fdocument->GetFunction()->NewInstance(1, fargs) );
        return ret;
    }
  }

  JS_METHOD(_parserparseuri) {
    /* TryCatch tc; */
    if (args.Length()!=1) {
      return JS_ERROR("[_parserparseuri()] ERROR: Incorrect number of input parameters");
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
      SS tmp( *String::Utf8Value(args[0]->ToString()) );
      src = (char *)tmp.str().c_str();
      XLSTRY( uri = new XMLURL((const XMLCh *)ARGSTR(0)); );
    }
    if (uri==NULL) {
      return JS_ERROR("[_parserparseuri()] ERROR: \"uri\" is a null pointer");
    }
    DOMDocument * doc = NULL;
   // XLSTRY( doc = parser->parseURI((const char *)src); );
    XLSTRY( doc = parser->parseURI(uri->getURLText()); );
    if (doc==NULL) {
      return JS_ERROR("[_parserparseuri()] ERROR: \"doc\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)doc) };
      Handle<Object> ret( xdom::fdocument->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_parserparsewithcontext) {
    TryCatch tc;
    if (args.Length()!=3) {
      return JS_ERROR("[_parserparsewithcontext()] ERROR: Incorrect number of input parameters");
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
      SS tmp( *String::Utf8Value(args[0]->ToString()) );
      const char * src = tmp.str().c_str();
      XMLSize_t len = (XMLSize_t)(tmp.str().length() + 1);
      MemBufInputSource mem((const XMLByte *const)src,len,"parsersrc",false);
      mem.setEncoding(X("UTF-8"));
      inv = (DOMLSInput *)(&mem);
    }
    if (inv==NULL) {
      return JS_ERROR("[_parserparsewithcontext()] ERROR: \"inv\" is a null pointer");
    }
    DOMNode * context = NULL;
    if (args[1]->IsExternal()) {
      context = RECAST(args[1],DOMNode *);
    }
    else if (args[1]->IsObject()) {
      context = RECAST(args[1]->ToObject()->GetInternalField(0),DOMNode *);
    }
    if (context==NULL) {
      return JS_ERROR("[_parserparsewithcontext()] ERROR: \"context\" is a null pointer");
    }
    else {
      int action = args[2]->ToInteger()->IntegerValue();
      XLSTRY( parser->parseWithContext((const DOMLSInput *)inv,context,(xercesc_3_0::DOMLSParser::ActionType)action); );
      return args.This();
    }
  }

  JS_METHOD(_parserabort) {
    TryCatch tc;
    PARSER;
    XLSTRY( parser->abort(); );
    return args.This();
  }

  JS_METHOD(_parserresetdocumentpool) {
    TryCatch tc;
    PARSER;
    XLSTRY( parser->resetDocumentPool(); );
    return args.This();
  }

  JS_METHOD(_parserloadgrammar) {
    TryCatch tc;
    return args.This();
  }

  JS_METHOD(_parsergetgrammar) {
    TryCatch tc;
    return args.This();
  }

  JS_METHOD(_parsergetrootgrammar) {
    TryCatch tc;
    return args.This();
  }

  JS_METHOD(_parsergeturitext) {
    TryCatch tc;
    return args.This();
  }

  JS_METHOD(_parserresetcachedgrammarpool) {
    TryCatch tc;
    return args.This();
  }

  JS_METHOD(_parsergetsrcoffset) {
    TryCatch tc;
    if (args.Length()>0) {
      return JS_ERROR("[_parsergetsrcoffset()] ERROR: Too many input parameters");
    }
    PARSER;
    unsigned int pos = 0;
    XLSTRY( pos = parser->getSrcOffset(); );
    return JS_INT(pos);
  }

  JS_METHOD(_parsergetimplementation) {
    TryCatch tc;
    if (args.Length()>0) {
      return JS_ERROR("[_parsergetimplementation()] ERROR: Too many input parameters");
    }
    DOM;
    if (dom==NULL) {
      return JS_ERROR("[_parsergetimplementation()] ERROR: \"dom\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)dom) };
      Handle<Object> obj( xdom::fdom->GetFunction()->NewInstance(1, fargs) );
      Handle<Value> ret( obj );
      return ret;
    }
  }

  /**
   *	~DOMLSParser method
   *	- Destructor for DOMLSParser objects
   */ 
  JS_METHOD(_parser_destructor) {
    /* TryCatch tc; */
    //PARSER_DOM;
    //dom = NULL;
    // SAVE_PTR(0,NULL);
    // SAVE_PTR(1,NULL);
    XLSTRY(
	// parser->release();
	// parser->~DOMLSParser();
    );
    return args.This();
  }


  /**
   *	DOMLSParserFilter constructor:
   * 	- Adds "~DOMLSParserFilter()" method to global GC
   */
  JS_METHOD(_parserfilter) {
    // /* TryCatch tc; */
    if (args.Length()<1) {
      return JS_ERROR("[_parserfilter()] ERROR: Missing input parameter");
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
      return JS_ERROR("[_parserfilter()] ERROR: \"filter\" is a null pointer");
    else {
      SAVE_PTR(0,filter);
      return args.This();
    }
  }

  JS_METHOD(_parserfilterstartelement) {
    PARSERFILTER;
    xercesc_3_0::DOMLSParserFilter::FilterAction ret;
    DOMElement * el = NULL;
    if (args[0]->IsExternal()) {
      el = RECAST(args[0],DOMElement *);
    }
    else if (args[0]->IsObject()) {
      el = RECAST(args[0]->ToObject()->GetInternalField(0),DOMElement *);
    }
    XTRY( ret = filter->startElement(el); );
    return JS_INT(ret);
  }

  JS_METHOD(_parserfiltergetwhattoshow) {
    PARSERFILTER;
    xercesc_3_0::DOMNodeFilter::ShowType ret = 0;
    XTRY( ret = filter->getWhatToShow(); );
    return JS_INT(ret);
  }

  /**
   *	~DOMLSParserFilter method
   *	- Destructor for DOMLSParserFilter objects
   */ 
  JS_METHOD(_parserfilter_destructor) {
    /* TryCatch tc; */
    PARSERFILTER;
    // SAVE_PTR(0,NULL);
    XLSTRY( filter->~DOMLSParserFilter(); );
    return args.This();
  }


  /**
   *	DOMConfiguration constructor:
   * 	- Adds "DOMConfiguration()" method to global GC
   */
  JS_METHOD(_domconfiguration) {
    ///* TryCatch tc; */
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
	Local<Object> tobj( args[0]->ToObject() );
	domconfig = RECAST(tobj->GetInternalField(0),DOMConfiguration *);
      }
    }
    if (domconfig==NULL) {
      return JS_ERROR("[_domconfiguration()] ERROR: \"domconfig\" is a null pointer");
    }
    else {
      SAVE_PTR(0,domconfig);
      return args.This();
    }
  }

  JS_METHOD(_domconfiggetparameter) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_domconfiggetparameter()] ERROR: Incorrect number of input parameters");
    DOMCONFIG;
    SS name(*String::Utf8Value(args[0]->ToString()));
    bool * paramval = NULL;
    XTRY( paramval = (bool *)domconfig->getParameter(X_STR(name)); );
    if (paramval==NULL) {
      return JS_ERROR("[_domconfiggetparameter()] ERROR: \"paramval\" is a null pointer");
    }
    else {
      return JS_BOOL(*paramval);
    }
  }

  JS_METHOD(_domconfigsetparameter) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_domconfigsetparameter()] ERROR: Incorrect number of input parameters");
    DOMCONFIG;
    SS name (*String::Utf8Value(args[0]->ToString()));
    bool val = args[1]->ToBoolean()->BooleanValue();
    XTRY( domconfig->setParameter(X_STR(name), val); );
    return args.This();
  }

  JS_METHOD(_domconfigcansetparameter) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_domconfigcansetparameter()] ERROR: Incorrect number of input parameters");
    DOMCONFIG;
    SS name(*String::Utf8Value(args[0]->ToString()));
    bool val = args[1]->ToBoolean()->BooleanValue();
    bool ret = false;
    XTRY( ret = domconfig->canSetParameter(X_STR(name),val); );
    return JS_BOOL(ret);
  }

  JS_METHOD(_domconfiggetparameternames) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_domconfiggetparameternames()] ERROR: Too many input parameters");
    DOMCONFIG;
    DOMStringList * dslist = NULL;
    XTRY( dslist = (DOMStringList *)domconfig->getParameterNames(); );
    if (dslist==NULL) {
      return JS_ERROR("[_domconfiggetparameternames()] ERROR: \"dslist\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)dslist) };
      Handle<Object> ret( xdom::fstringlist->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  /**
   *	~DOMConfiguration method
   *	- Destructor for DOM objects
   */ 
  JS_METHOD(_domconfiguration_destructor) {
    /* TryCatch tc; */
    //DOMCONFIG;
    // SAVE_PTR(0,NULL);
    // X TRY( domconfig->~DOMConfiguration(); );
    return args.This();
  }
  
  /**
   *	DOMNode constructor:
   * 	- Adds "~DOMNode()" method to global GC
   */
  JS_METHOD(_domnode) {
    /* TryCatch tc; */
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
      return JS_ERROR("[_node()] ERROR: \"node\" is a null pointer");
    }
    if (args.Length() > 1) {
      if (args[1]->IsBoolean()) {
	if (args[1]->ToBoolean()->BooleanValue()!=true) {
	  SAVE_PTR(0,node);
	  return args.This();
	}
      }
    }
    xercesc_3_0::DOMNode::NodeType nodeType = node->getNodeType();
    Handle<Value> fargs[] = { External::New((void *)node) };
    if (nodeType==xercesc_3_0::DOMNode::ELEMENT_NODE) {
      Handle<Object> ret( xdom::felement->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
    else if (nodeType==xercesc_3_0::DOMNode::DOCUMENT_TYPE_NODE) {
      Handle<Object> ret( xdom::fdocumenttype->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
    else if (nodeType==xercesc_3_0::DOMNode::DOCUMENT_NODE) {
      Handle<Object> ret( xdom::fdocument->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
    else if (nodeType==xercesc_3_0::DOMNode::DOCUMENT_FRAGMENT_NODE) {
      Handle<Object> ret( xdom::fdocumentfragment->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
    else if (nodeType==xercesc_3_0::DOMNode::ATTRIBUTE_NODE) {
      Handle<Object> ret( xdom::fattribute->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
    else if (nodeType==xercesc_3_0::DOMNode::TEXT_NODE) {
      Handle<Object> ret( xdom::ftext->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
    else if (nodeType==xercesc_3_0::DOMNode::COMMENT_NODE) {
      Handle<Object> ret( xdom::fcomment->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
    else if (nodeType==xercesc_3_0::DOMNode::CDATA_SECTION_NODE) {
      Handle<Object> ret( xdom::fcdatasection->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
    else {
      SAVE_PTR(0,node);
      return args.This();
    }
  }

  JS_METHOD(_nodegetaselement) {
	/* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_nodegetaselement()] ERROR: Too many input parameters");
    DOMNode * node = NULL;
    node = RECAST(args.This()->GetInternalField(0),DOMNode *);
    if (node==NULL) {
      return JS_ERROR("[_nodegetaselement()] ERROR: \"node\" is a null pointer");
    }
    else {
      const int fargc = 2;
      Local<Value> upConvert( *Boolean::New(true) );
      v8::Local<v8::Value> fargv[] = { v8::External::New((void *)node), upConvert };
      v8::Handle<v8::Function> f = xdom::fnode->GetFunction();
      v8::Handle<v8::Object> ret ( f->NewInstance(fargc, fargv) );
      return ret;
    }
  }

  JS_METHOD(_nodeserialize) {
    /* TryCatch tc; */
    NODE;
    DOMDocument * doc = NULL;
    DOMImplementation * dom = NULL;
    DOMLSOutput * pOutput = NULL;
    DOMLSSerializer * pSerializer = NULL;
    bool cleanSer = true;
    bool cleanOut = true;
    if (args.Length()>2) {
      return JS_ERROR("[_nodeserialize()] ERROR: Too many input parameters");
    }
    SS encoding("UTF-8");
    if (args.Length()>0) {
      if (args[0]->IsString()) {
	encoding.flush() << *String::Utf8Value(args[0]->ToString());
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
      Handle<String> ret(JS_STR(cstr));
      if (cleanSer==true) {
	pSerializer->release();
      }
      if (cleanOut==true) {
	pOutput->release();
      }
      delete cstr;
      return ret;
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
      return JS_ERROR("[_nodeserializeinner()] ERROR: Too many input parameters");
    }
    SS encoding("UTF-8");
    if (args.Length()>0) {
      if (args[0]->IsString()) {
	encoding.flush() << *String::Utf8Value(args[0]->ToString());
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
      Handle<String> ret(JS_STR(cstr));
      if (cleanSer==true) {
	pSerializer->release();
      }
      if (cleanOut==true) {
	pOutput->release();
      }
      delete cstr;
      return ret;
    );
  }

  JS_METHOD(_nodegetnodename) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_nodegetnodename()] ERROR: Too many input parameters");
    NODE;
    XS name = NULL;
    XTRY( name = (XMLCh *)node->getNodeName(); );
    if (name==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(name);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_nodegetnodevalue) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_nodegetnodevalue()] ERROR: Too many input parameters");
    NODE;
    XS val = NULL;
    XTRY( val = (XMLCh *)node->getNodeValue(); );
    if (val==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(val);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_nodegetnodetype) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_nodegetnodetype()] ERROR: Too many input parameters");
    NODE;
    int ret = -1;
    XTRY( ret = (int)node->getNodeType(); );
    if (ret<0) {
      return JS_ERROR("[_nodegetnodetype()] ERROR: \"ret\" has an invalid value");
    }
    else {
      return JS_INT(ret);
    }
  }

  JS_METHOD(_nodegetparentnode) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_nodegetparentnode()] ERROR: Too many input parameters");
    NODE;
    DOMNode * parent = NULL;
    XTRY( parent = node->getParentNode(); );
    Handle<Value> fargs[] = { External::New((void *)parent) };
    Handle<Object> ret( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
    return ret;
  }

  JS_METHOD(_nodegetchildnodes) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_nodegetchildnodes()] ERROR: Too many input parameters");
    NODE;
    DOMNodeList * nodelist = NULL;
    XTRY( nodelist = node->getChildNodes(); );
    if (nodelist==NULL) {
      return JS_ERROR("[_nodegetchildnodes()] ERROR: \"nodelist\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)nodelist) };
      Handle<Object> ret( xdom::fnodelist->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_nodegetfirstchild) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_nodegetfirstchild()] ERROR: Too many input parameters");
    NODE;
    DOMNode * child = NULL;
    XTRY( child = node->getFirstChild(); );
    if (child==NULL) {
      return JS_ERROR("[_nodegetfirstchild()] ERROR: \"child\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)child) };
      Handle<Object> ret( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_nodegetlastchild) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_nodegetlastchild()] ERROR: Too many input parameters");
    NODE;
    DOMNode * child = NULL;
    XTRY( child = node->getLastChild(); );
    if (child==NULL) {
      return JS_ERROR("[_nodegetlastchild()] ERROR: \"child\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)child) };
      Handle<Object> ret( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_nodegetprevioussibling) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_nodegetprevioussibling()] ERROR: Too many input parameters");
    NODE;
    DOMNode * sib = NULL;
    XTRY( sib = node->getPreviousSibling(); );
    if (sib==NULL) {
      return JS_ERROR("[_nodegetprevioussibling()] ERROR: \"sib\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)sib) };
      Handle<Object> ret( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_nodegetnextsibling) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_nodegetnextsibling()] ERROR: Too many input parameters");
    NODE;
    DOMNode * sib = NULL;
    XTRY( sib = node->getNextSibling(); );
    if (sib==NULL) {
      return JS_ERROR("[_nodegetnextsibling()] ERROR: \"sib\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)sib) };
      Handle<Object> ret( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_nodegetattributes) {
    TryCatch tc;
    if (args.Length()>0)
      return JS_ERROR("[_nodegetattributes()] ERROR: Too many input parameters");
    NODE;
    DOMNamedNodeMap * nodemap = NULL;
    XTRY( nodemap = node->getAttributes(); );
    if (nodemap==NULL) {
      return JS_ERROR("[_nodegetattributes()] ERROR: \"nodemap\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)nodemap) };
      Handle<Object> ret( xdom::fnamednodemap->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_nodegetownerdocument) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_nodegetownerdocument()] ERROR: Too many input parameters");
    NODE;
    DOMDocument * doc = NULL;
    XTRY( doc = node->getOwnerDocument(); );
    if (doc==NULL) {
      return JS_ERROR("[_nodegetownerdocument()] ERROR: \"doc\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)doc) };
      Handle<Object> ret ( xdom::fdocument->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_nodegetownerimplementation) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_nodegetownerimplementation()] ERROR: Too many input parameters");
    NODE;
    DOMDocument * doc = NULL;
    XTRY( doc = node->getOwnerDocument(); );
    if (doc==NULL) {
      return JS_ERROR("[_nodegetownerimplementation()] ERROR: \"doc\" is a null pointer");
    }
    else {
      DOMImplementation * impl = NULL;
      XTRY( impl = doc->getImplementation(); );
      if (impl==NULL) {
	return JS_ERROR("[_nodegetownerimplementation()] ERROR: \"impl\" is a null pointer");
      }
      else {
	Handle<Value> fargs[] = { External::New((void *)impl) };
	Handle<Object> ret ( xdom::fdom->GetFunction()->NewInstance(1, fargs) );
	return ret;
      }
    }
  }

  JS_METHOD(_nodeclonenode) {
    /* TryCatch tc; */
    if (args.Length()>1)
      return JS_ERROR("[_nodeclonenode()] ERROR: Too many input parameters");
    NODE;
    Local<Boolean> inDepth ( args[0]->ToBoolean() );
    DOMNode * clone = NULL;
    XTRY( clone = node->cloneNode(*inDepth); );
    if (clone==NULL) {
      return JS_ERROR("[_nodeclonenode()] ERROR: \"clone\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)clone) };
      Handle<Object> ret ( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_nodeinsertbefore) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_nodeinsertbefore()] ERROR: Incorrect number of input parameters");
    NODE;
    DOMNode * newChild = RECAST(args[0],DOMNode *);
    DOMNode * refChild = RECAST(args[1],DOMNode *);
    DOMNode * retChild = NULL;
    XTRY( retChild = node->insertBefore(newChild,refChild); );
    if (retChild==NULL) {
      return JS_ERROR("[_nodeinsertbefore()] ERROR: \"retChild\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)retChild) };
      Handle<Object> ret ( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_nodereplacechild) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_nodereplacechild()] ERROR: Incorrect number of input parameters");
    Handle<Object> ret;
    {
      NODE;
      DOMNode * newChild = RECAST(args[0],DOMNode *);
      DOMNode * oldChild = RECAST(args[1],DOMNode *);
      DOMNode * retChild = NULL;
      XTRY( retChild = node->replaceChild(newChild,oldChild); );
      if (retChild==NULL) {
	return JS_ERROR("[_nodereplacechild()] ERROR: \"retChild\" is a null pointer");
      }
      else {
	Local<Value> fargs[] = { External::New((void *)retChild) };
	ret = xdom::fnode->GetFunction()->NewInstance(1, fargs);
      }
    }
    return ret;
  }

  JS_METHOD(_noderemovechild) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_noderemovechild()] ERROR: Incorrect number of input parameters");
    NODE;
    DOMNode * oldChild = RECAST(args[0],DOMNode *);
    DOMNode * retChild = NULL;
    XTRY( retChild = node->removeChild(oldChild); );
    if (retChild==NULL) {
      return JS_ERROR("[_noderemovechild()] ERROR: \"retChild\" is a null pointer");
    }
    else {
      Local<Value> fargs[] = { External::New((void *)retChild) };
      Handle<Object> ret( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_nodeappendchild) {
    /* TryCatch tc; */
    if (args.Length()<1)
      return JS_ERROR("[_nodeappendchild()] ERROR: Missing input parameter");
    else if (args.Length()>1)
      return JS_ERROR("[_nodeappendchild()] ERROR: Too many input parameters");
    NODE;
    DOMNode * newChild = NULL;
    if (args[0]->IsExternal()) {
      newChild = RECAST(args[0],DOMNode *);
    }
    else if (args[0]->IsObject()) {
      newChild = RECAST(args[0]->ToObject()->GetInternalField(0),DOMNode *);
    }
    if (newChild==NULL) {
      return JS_ERROR("[_nodeappendchild()] ERROR: \"newChild\" is a null pointer");
    }
    else {
      DOMNode * res = NULL;
      XTRY( res = node->appendChild(newChild); );
      if (res==NULL) {
	return JS_ERROR("[_nodeappendchild()] ERROR: \"res\" is a null pointer");
      }
      else {
	Handle<Value> fargs[] = { External::New((void *)res) };
	Handle<Object> ret ( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
	return ret;
      }
    }
  }

  JS_METHOD(_nodehaschildnodes) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_nodehaschildnodes()] ERROR: Too many input parameters");
    NODE;
    bool ret = false;
    XTRY( ret = node->hasChildNodes(); );
    return JS_BOOL(ret);
  }

  JS_METHOD(_nodesetnodevalue) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_nodesetnodevalue()] ERROR: Incorrect number of input parameters");
    NODE;
    SS val( *String::Utf8Value(args[0]->ToString()) );
    XTRY( node->setNodeValue(X_STR(val)); );
    return args.This();
  }

  JS_METHOD(_nodenormalize) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_nodenormalize()] ERROR: Too many input parameters");
    NODE;
    XTRY( node->normalize(); );
    return args.This();
  }

  JS_METHOD(_nodeissupported) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_nodeissupported()] ERROR: Incorrect number of input parameters");
    NODE;
    bool ret = false;
    SS feature ("");
    SS version ("");
    feature << *String::Utf8Value(args[0]);
    version << *String::Utf8Value(args[1]);
    XTRY( ret = node->isSupported(X_STR(feature),X_STR(version)); );
    return JS_BOOL(ret);
  }

  JS_METHOD(_nodegetnamespaceuri) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_nodegetnamespaceuri()] ERROR: Too many input parameters");
    NODE;
    Handle<String> ret;
    XTRY( ret = JS_STR((char *) node->getNamespaceURI()); );
    return ret;
  }

  JS_METHOD(_nodegetprefix) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_nodegetprefix()] ERROR: Too many input parameters");
    NODE;
    Handle<String> ret;
    XTRY( ret = JS_STR((char *)node->getPrefix()); );
    return ret;
  }

  JS_METHOD(_nodegetlocalname) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_nodegetlocalname()] ERROR: Too many input parameters");
    NODE;
    Handle<String> ret;
    XTRY( ret = JS_STR((char *)node->getLocalName()); );
    return ret;
  }

  JS_METHOD(_nodesetprefix) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_nodesetprefix()] ERROR: Incorrect number of input parameters");
    else {
      NODE;
      SS prefix( *String::Utf8Value(args[0]->ToString()) );
      XTRY( node->setPrefix(X_STR(prefix)); );
      return args.This();
    }
  }

  JS_METHOD(_nodehasattributes) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_nodehasattributes()] ERROR: Too many input parameters");
    NODE;
    bool ret = false;
    XTRY( ret = node->hasAttributes(); );
    return JS_BOOL(ret);
  }

  JS_METHOD(_nodeissamenode) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_nodeissamenode()] ERROR: Incorrect number of input parameters");
    NODE;
    DOMNode * other = NULL;
    if (args[0]->IsExternal()) {
      other = RECAST(args[0],DOMNode *);
    }
    else if(args[0]->IsObject())
      other = RECAST(args[0]->ToObject()->GetInternalField(0),DOMNode *);
    if (other==NULL)
      return JS_ERROR("[_nodeissamenode()] ERROR: \"other\" is a null pointer");
    else {
      bool ret = false;
      XTRY( ret = node->isSameNode(other); );
      return JS_BOOL(ret);
    }
  }

  JS_METHOD(_nodeisequalnode) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_nodeisequalnode()] ERROR: Incorrect number of input parameters");
    NODE;
    DOMNode * other = NULL;
    if (args[0]->IsExternal()) {
      other = RECAST(args[0],DOMNode *);
    }
    else if(args[0]->IsObject())
      other = RECAST(args[0]->ToObject()->GetInternalField(0),DOMNode *);
    if (other==NULL)
      return JS_ERROR("[_nodeisequalnode()] ERROR: \"other\" is a null pointer");
    else {
      bool ret = false;
      XTRY( ret = node->isEqualNode(other); );
      return JS_BOOL(ret);
    }
  }

  JS_METHOD(_nodesetuserdata) {
    /* TryCatch tc; */
    if (args.Length()>3 || args.Length()<2)
      return JS_ERROR("[_nodesetuserdata()] ERROR: Incorrect number of input parameters");
    NODE;
    SS key("");
    key << *String::Utf8Value( args[0] );
    void * data = NULL;
    if (args[1]->IsExternal()) {
      data = RECAST(args[1],void *);
    }
    DOMUserDataHandler * handler = NULL;
    if (args[2]->IsExternal()) {
      handler = RECAST(args[2],DOMUserDataHandler *);
    }
    else if (args[2]->IsObject()) {
      Local<Object> tobj ( args[2]->ToObject() );
      if (tobj->InternalFieldCount()>0) {
	handler = RECAST(tobj->GetInternalField(0),DOMUserDataHandler *);
      }
    }
    XTRY( node->setUserData(X_STR(key),data,handler); );
    return args.This();
  }

  JS_METHOD(_nodegetuserdata) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_nodegetuserdata()] ERROR: Incorrect number of input parameters");
    NODE;
    SS key("");
    key << *String::Utf8Value( args[0] );
    void * obj_ptr = NULL;
    XTRY( obj_ptr = node->getUserData(X_STR(key)); );
    return args.This();
  }

  JS_METHOD(_nodegetbaseuri) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_nodegetbaseuri()] ERROR: Too many input parameters");
    NODE;
    XS uri = NULL;
    XTRY( uri = (XMLCh *)node->getBaseURI(); );
    if (uri==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(uri);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_nodecomparedocumentposition) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_nodegetbaseuri()] ERROR: Incorrect number of input parameters");
    NODE;
    DOMNode * other = NULL;
    if (args[0]->IsExternal()) {
      other = RECAST(args[0],DOMNode *);
    }
    else if (args[0]->IsObject()) {
      Local<Object> tobj ( args[0]->ToObject() );
      if (tobj->InternalFieldCount()>0) {
	other = RECAST(tobj->GetInternalField(0),DOMNode *);
      }
    }
    if (other==NULL)
      return JS_ERROR("[_nodecomparedocumentposition()] ERROR: \"other\" is a null pointer");
    else {
      short ret = 0;
      XTRY( ret = node->compareDocumentPosition(other); );
      return JS_INT(ret);
    }
  }

  JS_METHOD(_nodegettextcontent) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_nodegettextcontent()] ERROR: Too many input parameters");
    NODE;
    XS textcontent = NULL;
    XTRY( textcontent = (XMLCh *)node->getTextContent(); );
    if (textcontent==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(textcontent);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_nodesettextcontent) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_nodesettextcontent()] ERROR: Incorrect number of input parameters");
    NODE;
    SS content("");
    content << *String::Utf8Value(args[0]->ToString());
    XTRY( node->setTextContent(X_STR(content)); );
    return args.This();
  }

  JS_METHOD(_nodelookupprefix) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_nodelookupprefix()] ERROR: Incorrect number of input parameters");
    NODE;
    SS prefix("");
    prefix << *String::Utf8Value(args[0]->ToString());
    XS res = NULL;
    XTRY( res = (XMLCh *)node->lookupPrefix(X_STR(prefix)); );
    if (res==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(res);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_nodeisdefaultnamespace) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_nodeisdefaultnamespace()] ERROR: Incorrect number of input parameters");
    NODE;
    SS ns(*String::Utf8Value(args[0]->ToString()));
    bool ret = false;
    XTRY( node->isDefaultNamespace(X_STR(ns)); );
    return JS_BOOL(ret);
  }

  JS_METHOD(_nodelookupnamespaceuri) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_nodelookupnamespaceuri()] ERROR: Incorrect number of input parameters");
    NODE;
    SS ns(*String::Utf8Value(args[0]->ToString()));
    XS res = NULL;
    XTRY( res = (XMLCh *)node->lookupNamespaceURI(X_STR(ns)); );
    if (res==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(res);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_nodegetfeature) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_nodegetfeature()] ERROR: Incorrect number of input parameters");
    NODE;
    SS feature ("");
    SS version ("");
    feature << *String::Utf8Value(args[0]);
    version << *String::Utf8Value(args[1]);
    void * res = NULL;
    XTRY( res = (void *)node->getFeature(X_STR(feature),X_STR(version)); );
    Handle<Value> ret ( External::New((void *)res) );
    return ret;
  }
  
    /**
     *	~Node method
     *	- Destructor for Node objects
     */
    JS_METHOD(_domnode_destructor) {
      /* TryCatch tc; */
      //NODE;
      //if (node!=NULL) {
	//SAVE_PTR(0,NULL);
        //XTRY( node->release(); );
	//XTRY( node->~DOMNode(); );
	//return args.This();
      //}
      return args.This();
    }
  
  /**
   *	Text constructor:
   * 	- Adds "Text()" method to global GC
   */
  JS_METHOD(_text) {
    /* TryCatch tc; */
    if (args.Length()!=1 && args.Length()!=1)
      return JS_ERROR("[_text()] ERROR: Incorrect number of input parameters");
    ASSERT_CONSTRUCTOR;
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMText");
    DOMText * text = NULL;
    if (args[0]->IsExternal()) {
      text = RECAST(args[0],DOMText *);
    }
    else if (args[0]->IsObject()) {
      Handle<Object> tobj( args[0]->ToObject() );
      text = RECAST(tobj->GetInternalField(0),DOMText *);
    }
    if (text==NULL)
      return JS_ERROR("[_text()] ERROR: \"text\" is a null pointer");
    else {
      SAVE_PTR(0,text);
      return args.This();
    }
  }

  JS_METHOD(_textsplittext) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_textsplittext] ERROR: Incorrect number of input parameters");
    TEXT;
    XMLSize_t offset = (XMLSize_t)(args[0]->ToInteger()->Uint32Value());
    DOMText * splitText = NULL;
    XTRY( splitText = text->splitText(offset); );
    Handle<Value> fargs[] = { External::New((void *)splitText) };
    Handle<Object> ret ( xdom::ftext->GetFunction()->NewInstance(1, fargs) );
    return ret;
  }

  JS_METHOD(_textgetiselementcontentwhitespace) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_textgetiselementcontentwhitespace] ERROR: Too many input parameters");
    TEXT;
    bool ret = false;
    XTRY( ret = text->getIsElementContentWhitespace(); );
    return JS_BOOL(ret);
  }

  JS_METHOD(_textgetwholetext) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_textgetwholetext] ERROR: Too many input parameters");
    TEXT;
    XS wholeText = NULL;
    XTRY( wholeText = (XMLCh *)text->getWholeText(); );
    if (wholeText==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(wholeText);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_textreplacewholetext) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_textreplacewholetext] ERROR: Incorrect number of input parameters");
    TEXT;
    SS content( *String::Utf8Value(args[0]->ToString()) );
    DOMText * newText = NULL;
    XTRY( newText = text->replaceWholeText(X_STR(content)); );
    if (newText==NULL)
      return JS_ERROR("[_textreplacewholetext] ERROR: \"newText\" is a null pointer");
    else
      SAVE_PTR(0,newText);
    XTRY( text->~DOMText(); );
    return args.This();
  }

  JS_METHOD(_textisignorablewhitespace) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_textisignorablewhitespace] ERROR: Too many input parameters");
    TEXT;
    bool ret = false;
    XTRY( ret = text->isIgnorableWhitespace(); );
    return JS_BOOL(ret);
  }

  /**
   *	~Text method
   *	- Destructor for Text objects
   */ 
  JS_METHOD(_text_destructor) {
    /* TryCatch tc; */
    //TEXT;
    //XTRY( text->~DOMText(); );
    // SAVE_PTR(0,NULL);
    return args.This();
  }


  /**
   *	DocumentType constructor:
   * 	- Adds "DocumentType()" method to global GC
   */
  JS_METHOD(_documenttype) {
    /* TryCatch tc; */
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
      return JS_ERROR("[_documenttype()] ERROR: \"docType\" is a null pointer");
    }
    else {
      SAVE_PTR(0,docType);
      return args.This();
    }
  }

  JS_METHOD(_dtgetname) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_dtgetname()] ERROR: Too many input parameters");
    DOCTYPE;
    XS name = NULL;
    XTRY( name = (XMLCh *)docType->getName(); );
    if (name==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(name);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_dtgetentities) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_dtgetentities()] ERROR: Too many input parameters");
    DOCTYPE;
    DOMNamedNodeMap * nodemap = NULL;
    XTRY( nodemap = docType->getEntities(); );
    Handle<Value> fargs[] = { External::New((DOMNamedNodeMap *)(nodemap)) };
    Handle<Object> ret( xdom::fnamednodemap->GetFunction()->NewInstance(1, fargs) );
    return ret;
  }

  JS_METHOD(_dtgetnotations) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_dtgetnotations()] ERROR: Too many input parameters");
    DOCTYPE;
    DOMNamedNodeMap * nodemap = NULL;
    XTRY( nodemap = docType->getNotations(); );
    Handle<Value> fargs[] = { External::New((DOMNamedNodeMap *)(nodemap)) };
    Handle<Object> ret( xdom::fnamednodemap->GetFunction()->NewInstance(1, fargs) );
    return ret;
  }

  JS_METHOD(_dtgetpublicid) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_dtgetpublicid()] ERROR: Too many input parameters");
    DOCTYPE;
    XS publicId = NULL;
    XTRY( publicId = (XMLCh *)docType->getPublicId(); );
    if (publicId==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(publicId);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_dtgetsystemid) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_dtgetsystemid()] ERROR: Too many input parameters");
    DOCTYPE;
    XS systemId = NULL;
    XTRY( systemId = (XMLCh *)docType->getSystemId(); );
    if (systemId==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(systemId);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_dtgetinternalsubset) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_dtgetinternalsubset()] ERROR: Too many input parameters");
    DOCTYPE;
    XS subset = NULL;
    XTRY( subset = (XMLCh *)docType->getInternalSubset(); );
    if (subset==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(subset);
      return JS_STR(ret);
    }
  }

  /**
   *	~DocumentType method
   *	- Destructor for DocumentType objects
   */ 
  JS_METHOD(_documenttype_destructor) {
    /* TryCatch tc; */
    //DOCTYPE;
    // SAVE_PTR(0,NULL);
    //XTRY( docType->release(); );
    //XTRY( docType->~DOMDocumentType(); );
    return args.This();
  }


  /**
   *	DocumentFragment constructor:
   * 	- Adds "DocumentFragment()" method to global GC
   */
  JS_METHOD(_documentfragment) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_documentfragment()] ERROR: Incorrect number of input parameters");
    ASSERT_CONSTRUCTOR;
    GC * gc = GC_PTR;
    gc->add(args.This(), "~DOMDocumentFragment");
    DOMDocumentFragment * frag = NULL;
    if (args[0]->IsExternal()) {
      frag = RECAST(args[0],DOMDocumentFragment *);
    }
    else if (args[0]->IsObject()) {
      Handle<Object> tobj( args[0]->ToObject() );
      frag = RECAST(tobj->GetInternalField(0),DOMDocumentFragment *);
    }
    if (frag==NULL)
      return JS_ERROR("[_documentfragment()] ERROR: \"frag\" is a null pointer");
    else {
      SAVE_PTR(0,frag);
      return args.This();
    }
  }

  /**
   *	~DocumentType method
   *	- Destructor for DocumentType objects
   */ 
  JS_METHOD(_documentfragment_destructor) {
    /* TryCatch tc; */
    //DOCFRAG;
    //XTRY( frag->~DOMDocumentFragment(); );
    // SAVE_PTR(0,NULL)
    return args.This();
  }

  /**
   *	Document constructor:
   * 	- Adds "Document()" method to global GC
   */
  JS_METHOD(_document) {
    /* TryCatch tc; */
    ASSERT_CONSTRUCTOR;
    if (args.Length()!=1) {
      return JS_ERROR("[_document()] ERROR: Incorrect number of input parameters");
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
      return JS_ERROR("[_document()] ERROR: \"doc\" is a null pointer");
    }
    else {
      SAVE_PTR(0,doc);
      return args.This();
    }
  }

  JS_METHOD(_documentcreatelsoutput) {
    DOC;
    SS encoding("UTF-8");
    if (args.Length()>0) {
      if (args[0]->IsString()) {
	encoding.flush() << *String::Utf8Value(args[0]->ToString());
      }
      else if (args[0]->IsObject()) {
	if (args[0]->ToObject()->Has(JS_STR("encoding"))) {
	  encoding.flush() << *String::Utf8Value( args[0]->ToObject()->Get(JS_STR("encoding"))->ToString() );
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
      return JS_ERROR("[_documentcreatelsoutput()] ERROR: \"target\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      Local<Value> fargv[] = { External::New((void *)target) };
      Handle<Object> ret( xdom::foutput->GetFunction()->NewInstance(fargc, fargv) );
      return ret;
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
      return JS_ERROR("[_documentcreatelsserializer()] ERROR: \"ser\" is a null pointer");
    }
    else {
      XMLSize_t fargc = 1;
      Local<Value> fargv[] = { External::New((void *)ser) };
      Handle<Object> ret( xdom::fserializer->GetFunction()->NewInstance(fargc, fargv) );
      return ret;
    }
  }

  JS_METHOD(_documentcreatenode) {
    /* TryCatch tc; */
    // DOC;
    return args.This();
  }

  JS_METHOD(_documentcreateelement) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_documentcreateelement()] ERROR: Incorrect number of input parameters");
    DOC;
    DOMElement * el = NULL;
    XTRY( el = doc->createElement(ARGSTR(0)); );
    if (el==NULL) {
      return JS_ERROR("[_documentcreateelement()] ERROR: \"el\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)(el)) };
      Handle<Object> ret( xdom::felement->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_documentcreatedocumentfragment) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_documentcreatedocumentfragment()] ERROR: Too many input parameters");
    DOC;
    DOMDocumentFragment * frag = NULL;
    XTRY( frag = doc->createDocumentFragment(); );
    Handle<Value> fargs[] = { External::New((void *)(frag)) };
    Handle<Object> ret( xdom::fdocumentfragment->GetFunction()->NewInstance(1, fargs) );
    return ret;
  }

  JS_METHOD(_documentcreatetextnode) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_documentcreatetextnode()] ERROR: Incorrect number of input parameters");
    DOC;
    DOMText * text = NULL;
    XTRY( text = doc->createTextNode(ARGSTR(0)); );
    Handle<Value> fargs[] = { External::New((void *)(text)) };
    Handle<Object> ret( xdom::ftext->GetFunction()->NewInstance(1, fargs) );
    return ret;
  }

  JS_METHOD(_documentcreatecomment) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_documentcreatecomment()] ERROR: Incorrect number of input parameters");
    DOC;
    DOMComment * comment = NULL;
    XTRY( comment = doc->createComment(ARGSTR(0)); );
    Handle<Value> fargs[] = { External::New((void *)(comment)) };
    Handle<Object> ret( xdom::fcomment->GetFunction()->NewInstance(1, fargs) );
    return ret;
  }

  JS_METHOD(_documentcreatecdatasection) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_documentcreatecdatasection()] ERROR: Incorrect number of input parameters");
    DOC;
    DOMCDATASection * cdata = NULL;
    XTRY( cdata = doc->createCDATASection(ARGSTR(0)); );
    Handle<Value> fargs[] = { External::New((void *)(cdata)) };
    Handle<Object> ret( xdom::fcdatasection->GetFunction()->NewInstance(1, fargs) );
    return ret;
  }

  JS_METHOD(_documentcreateprocessinginstruction) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_documentcreateprocessinginstruction()] ERROR: Incorrect number of input parameters");
    DOC;
    DOMProcessingInstruction * procinst = NULL;
    XTRY( procinst = doc->createProcessingInstruction(ARGSTR(0),ARGSTR(1)); );
    if (procinst==NULL) {
      return JS_ERROR("[_documentcreateprocessinginstruction()] ERROR: \"procinst\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((DOMProcessingInstruction *)procinst) };
      Handle<Object> ret( xdom::fprocessinginstruction->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_documentcreateattribute) {
    /* TryCatch tc; */
    if (args.Length()!=1 && args.Length()!=2)
      return JS_ERROR("[_documentcreateattribute()] ERROR: Incorrect number of input parameters");
    DOC;
    SS name(*String::Utf8Value(args[0]->ToString()));
    DOMAttr * attr = NULL;
    XTRY( attr = doc->createAttribute(ARGSTR(0)); );
    if (attr==NULL) {
      return JS_ERROR("[_documentcreateattribute()] ERROR: \"attr\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((DOMAttr *)attr) };
      Handle<Object> ret( xdom::fattribute->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_documentcreateentityreference) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_documentcreateentityreference()] ERROR: Incorrect number of input parameters");
    DOC;
    SS name(*String::Utf8Value(args[0]->ToString()));
    DOMEntityReference * entityref = NULL;
    XTRY( entityref = doc->createEntityReference(X_STR(name)); );
    if (entityref==NULL) {
      return JS_ERROR("[_documentcreateentityref()] ERROR: \"entityref\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)(entityref)) };
      Handle<Object> ret( xdom::fentityreference->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_documentcreateelementns) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_documentcreateelementns()] ERROR: Incorrect number of input parameters");
    DOC;
    DOMElement * el = NULL;
    XTRY( el = doc->createElementNS(ARGSTR(0),ARGSTR(1)); );
    if (el==NULL) {
      return JS_ERROR("[_documentcreateelementns()] ERROR: \"el\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)el) };
      Handle<Object> ret( xdom::felement->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_documentcreateattributens) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_documentcreateattributens()] ERROR: Incorrect number of input parameters");
    DOC;
    DOMAttr * attr = NULL;
    XTRY( attr = doc->createAttributeNS(ARGSTR(0),ARGSTR(1)); );
    if (attr==NULL) {
      return JS_ERROR("[_documentcreateattributens()] ERROR: \"attr\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)(attr)) };
      Handle<Object> ret( xdom::fattribute->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_documentgetdoctype) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_documentgetdoctype()] ERROR: Too many input parameters");
    DOC;
    DOMDocumentType * docType = NULL;
    XTRY( docType = doc->getDoctype(); );
    if (docType==NULL) {
      return JS_ERROR("[_documentgetdoctype()] ERROR: \"docType\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)(docType)) };
      Handle<Object> ret( xdom::fdocumenttype->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_documentgetimplementation) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_documentgetimplementation()] ERROR: Too many input parameters");
    DOC;
    DOMImplementation * dom = NULL;
    XTRY( dom = doc->getImplementation(); );
    if (dom==NULL) {
      return JS_ERROR("[_documentgetimplementation()] ERROR: \"dom\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)(dom)) };
      Handle<Function> impl( Handle<Function>::Cast(JS_GLOBAL->Get(JS_STR("DOMImplementation"))) );
      Handle<Object> ret( impl->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_documentgetdocumentelement) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_documentgetdocumentelement()] ERROR: Too many input parameters");
    DOC;
    DOMElement * el = NULL;
    XTRY( el = doc->getDocumentElement(); );
    if (el==NULL) {
      return JS_ERROR("[_documentgetodocumentelement()] ERROR: \"el\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)el) };
      Handle<Object> ret( xdom::felement->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_documentgetelementsbytagname) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_documentgetelementsbytagname()] ERROR: Too many input parameters");
    DOC;
    DOMNodeList * nodelist = NULL;
    XTRY( nodelist = doc->getElementsByTagName(ARGSTR(0)); );
    if (nodelist==NULL) {
      return JS_ERROR("[_documentgetelementsbytagname()] ERROR: \"nodelist\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)nodelist) };
      Handle<Object> ret( xdom::fnodelist->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_documentimportnode) {
    /* TryCatch tc; */
    if (args.Length()!=2 && args.Length()!=1)
      return JS_ERROR("[_documentgetdoctype()] ERROR: Incorrect number of input parameters");
    DOC;
    bool deep = false;
    if (args.Length()>1)
      deep = args[1]->ToBoolean()->BooleanValue();
    DOMNode * importedNode = NULL;
    if (args[0]->IsExternal()) {
      importedNode = RECAST(args[0],DOMNode *);
    }
    else if (args[0]->IsObject()) {
      Local<Object> tobj( args[0]->ToObject() );
      importedNode = RECAST(tobj->GetInternalField(0),DOMNode *);
    }
    DOMNode * node = NULL;
    XTRY( node = doc->importNode(importedNode, deep); );
    if (node==NULL)
      return JS_ERROR("[_documentimportnode()] ERROR: \"node\" is a null pointer");
    Handle<Value> fargs[] = { External::New((void *)node) };
    Handle<Object> ret( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
    return ret;
  }

  JS_METHOD(_documentgetelementsbytagnamens) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_documentgetelementsbytagnamens()] ERROR: Incorrect number of input parameters");
    DOC;
    SS namespaceURI(*String::Utf8Value(args[0]->ToString()));
    SS localName(*String::Utf8Value(args[1]->ToString()));
    DOMNodeList * nodelist = NULL;
    XTRY( nodelist = doc->getElementsByTagNameNS(X_STR(namespaceURI),X_STR(localName)); );
    Handle<Value> fargs[] = { External::New((void *)nodelist) };
    Handle<Object> ret( xdom::fnodelist->GetFunction()->NewInstance(1, fargs) );
    return ret;
  }

  JS_METHOD(_documentgetelementbyid) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_documentgetelementbyid()] ERROR: Incorrect number of input parameters");
    DOC;
    SS elementId(*String::Utf8Value(args[0]->ToString()));
    DOMElement * el = NULL;
    XTRY( el = doc->getElementById(X_STR(elementId)); );
    if (el==NULL)
      return JS_ERROR("[_documentgetelementbyid()] ERROR: \"el\" is a null pointer");
    Handle<Value> fargs[] = { External::New((void *)(el)) };
    Handle<Object> ret( xdom::felement->GetFunction()->NewInstance(1, fargs) );
    return ret;
  }

  JS_METHOD(_documentgetinputencoding) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_documentgetinputencoding()] ERROR: Too many input parameters");
    DOC;
    XS encoding = NULL;
    XTRY( encoding = (XMLCh *)doc->getInputEncoding(); );
    if (encoding==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(encoding);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_documentgetxmlencoding) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_documentgetxmlencoding()] ERROR: Too many input parameters");
    DOC;
    XS encoding = NULL;
    XTRY( encoding = (XMLCh *)doc->getXmlEncoding(); );
    if (encoding==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(encoding);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_documentgetxmlstandalone) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_documentgetxmlstandalone()] ERROR: Too many input parameters");
    DOC;
    bool ret = false;
    XTRY( ret = doc->getXmlStandalone(); );
    return JS_BOOL(ret);
  }

  JS_METHOD(_documentsetxmlstandalone) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_documentsetxmlstandalone()] ERROR: Incorrect number of input parameters");
    DOC;
    bool standalone = args[0]->ToBoolean()->BooleanValue();
    XTRY( doc->setXmlStandalone(standalone); );
    return args.This();
  }

  JS_METHOD(_documentgetxmlversion) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_documentgetxmlversion()] ERROR: Too many input parameters");
    DOC;
    XS version = NULL;
    XTRY( version = (XMLCh *)doc->getXmlVersion(); );
    if (version==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(version);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_documentsetxmlversion) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_documentsetxmlstandalone()] ERROR: Incorrect number of input parameters");
    DOC;
    SS version(*String::Utf8Value(args[0]->ToString()));
    XTRY( doc->setXmlVersion(X_STR(version)); );
    return args.This();
  }

  JS_METHOD(_documentgetdocumenturi) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_documentgetdocumenturi()] ERROR: Too many input parameters");
    DOC;
    XS uri = NULL;
    XTRY( uri = (XMLCh *)doc->getDocumentURI(); );
    if (uri==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(uri);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_documentsetdocumenturi) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_documentsetxmlstandalone()] ERROR: Incorrect number of input parameters");
    DOC;
    SS uri(*String::Utf8Value(args[0]->ToString()));
    XTRY( doc->setDocumentURI(X_STR(uri)); );
    return args.This();
  }

  JS_METHOD(_documentgetstricterrorchecking) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_documentgetxmlstandalone()] ERROR: Too many input parameters");
    DOC;
    bool ret = false;
    XTRY( ret = doc->getStrictErrorChecking(); );
    return JS_BOOL(ret);
  }

  JS_METHOD(_documentsetstricterrorchecking) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_documentsetxmlstandalone()] ERROR: Incorrect number of input parameters");
    DOC;
    bool strict = args[0]->ToBoolean()->BooleanValue();
    XTRY( doc->setStrictErrorChecking(strict); );
    return args.This();
  }

  JS_METHOD(_documentrenamenode) {
    /* TryCatch tc; */
    if (args.Length()!=3)
      return JS_ERROR("[_documentrenamenode()] ERROR: Incorrect number of input parameters");
    DOC;
    SS namespaceURI(*String::Utf8Value(args[1]->ToString()));
    SS qualifiedName(*String::Utf8Value(args[2]->ToString()));
    DOMNode * newNode = NULL;
    DOMNode * n = NULL;
    if (args[0]->IsExternal()) {
      n = RECAST(args[0],DOMNode *);
    }
    else if (args[0]->IsObject()) {
      Local<Object> tobj( args[0]->ToObject() );
      n = RECAST(tobj->GetInternalField(0),DOMNode *);
    }
    XTRY( newNode = doc->renameNode(n, X_STR(namespaceURI), X_STR(qualifiedName)); );
    if (newNode==NULL)
      return JS_ERROR("[_documentrenamenode()] ERROR: \"newNode\" is a null pointer");
    else {
      Handle<Value> fargs[] = { External::New((void *)newNode) };
      Handle<Object> ret( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_documentadoptnode) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_documentadoptnode()] ERROR: Incorrect number of input parameters");
    DOC;
    DOMNode * source = NULL;
    if (args[0]->IsExternal()) {
      source = RECAST(args[0],DOMNode *);
    }
    else if (args[0]->IsObject()) {
      Local<Object> tobj( args[0]->ToObject() );
      source = RECAST(tobj->GetInternalField(0),DOMNode *);
    }
    DOMNode * node = NULL;
    XTRY( node = doc->adoptNode(source); );
    if (node==NULL)
      return JS_ERROR("[_documentadoptnode()] ERROR: \"node\" is a null pointer");
    Handle<Value> fargs[] = { External::New((void *)node) };
    Handle<Object> ret( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
    return ret;
  }

  JS_METHOD(_documentnormalizedocument) {
    /* TryCatch tc; */
    DOC;
    XTRY( doc->normalizeDocument(); );
    return args.This();
  }

  JS_METHOD(_documentgetdomconfig) {
    /* TryCatch tc; */
    if (args.Length()>0) {
      return JS_ERROR("[_documentgetdomconfig()] ERROR: Too many input parameters");
    }
    DOC;
    DOMConfiguration * domconfig = NULL;
    XTRY( domconfig = doc->getDOMConfig(); );
    if (domconfig==NULL) {
      return JS_ERROR("[_documentgetdomconfig()] ERROR: \"domconfig\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)domconfig) };
      Handle<Object> ret( xdom::fdomconfiguration->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_documentcreateentity) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_documentcreateentity()] ERROR: Incorrect number of input parameters");
    DOC;
    SS name(*String::Utf8Value(args[0]->ToString()));
    DOMEntity * entity = NULL;
    XTRY( entity = doc->createEntity(X_STR(name)); );
    if (entity==NULL)
      return JS_ERROR("[_documentcreateentity()] ERROR: \"entity\" is a null pointer");
    Handle<Value> fargs[] = { External::New((void *)(entity)) };
    Handle<Object> ret( xdom::fentity->GetFunction()->NewInstance(1, fargs) );
    return ret;
  }

  JS_METHOD(_documentcreatenotation) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_documentcreatenotation()] ERROR: Incorrect number of input parameters");
    DOC;
    SS name(*String::Utf8Value(args[0]->ToString()));
    DOMNotation * notation = NULL;
    XTRY( notation = doc->createNotation(X_STR(name)); );
    Handle<Value> fargs[] = { External::New((void *)(notation)) };
    Handle<Object> ret( xdom::fnotation->GetFunction()->NewInstance(1, fargs) );
    return ret;
  }

  JS_METHOD(_documentcreatedocumenttype) {
    /* TryCatch tc; */
    if (args.Length()!=3 && args.Length()!=1)
      return JS_ERROR("[_documentcreatedocumenttype()] ERROR: Incorrect number of input parameters");
    DOC;
    DOMDocumentType * docType = NULL;
    SS qName(*String::Utf8Value(args[0]->ToString()));
    if (args.Length()==1) {
      XTRY( docType = doc->createDocumentType(X_STR(qName)); );
    }
    else {
      SS publicId(*String::Utf8Value(args[1]->ToString()));
      SS systemId(*String::Utf8Value(args[2]->ToString()));
      XTRY( docType = doc->createDocumentType(X_STR(qName),X_STR(publicId),X_STR(systemId)); );
    }
    if (docType==NULL)
      return JS_ERROR("[_documentcreatedocumenttype()] ERROR: \"docType\" is a null pointer");
    Handle<Value> fargs[] = { External::New((void *)docType) };
    Handle<Object> ret( xdom::fdocumenttype->GetFunction()->NewInstance(1, fargs) );
    return ret;
  }

  JS_METHOD(_documentserialize) {
    DOC;
    DOMImplementation * dom = NULL;
    DOMLSOutput * pOutput = NULL;
    DOMLSSerializer * pSerializer = NULL;
    bool cleanSer = true;
    bool cleanOut = true;
    if (args.Length()>2) {
      return JS_ERROR("[_documentserialize()] ERROR: Too many input parameters");
    }
    SS encoding("UTF-8");
    if (args.Length()>0) {
      if (args[0]->IsString()) {
	encoding.flush() << *String::Utf8Value(args[0]->ToString());
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
      Handle<String> ret(JS_STR(cstr));
      if (cleanSer==true) {
	pSerializer->release();
      }
      if (cleanOut==true) {
	pOutput->release();
      }
      delete cstr;
      return ret;
    );
  }

  /**
   *	~DOMDocument method
   *	- Destructor for Document objects
   */ 
  JS_METHOD(_document_destructor) {
    DOC;
    if (doc!=NULL) {
      TryCatch inner;
      //XTRY( doc->~DOMDocument(); );
      if (inner.HasCaught()) {
      }
      // SAVE_PTR(0,NULL);
    }
    return args.This();
  }


  /**
   *	PreElement constructor:
   * 	- Adds "~PreElement()" method to global GC
   */
  JS_METHOD(_preelement) {
    /* TryCatch tc; */
    if (args.Length()!=1 && args.Length()!=2)
      return JS_ERROR("[_preelement()] ERROR: Incorrect number of input parameters");
    ASSERT_CONSTRUCTOR;
    //GC * gc = GC_PTR;
    //gc->add(args.This(), "~PreElement");
    DOMElement * element = NULL;
    if (args[0]->IsExternal()) {
      element = RECAST(args[0],DOMElement *);
    }
    else if (args[0]->IsObject()) {
      Handle<Object> tobj( args[0]->ToObject() );
      element = RECAST(tobj->GetInternalField(0),DOMElement *);
    }
    if (element==NULL) {
      return JS_ERROR("[_preelement()] ERROR: \"element\" is a null pointer");
    }
    else {
      SAVE_PTR(0,element);
      return args.This();
    }
  }

  JS_METHOD(_preelement_destructor) {
    /* TryCatch tc; */
    //ELEMENT;
    //XTRY(
	// element->release();
	// element->~DOMElement();
    //);
    //SAVE_PTR(0,NULL)
    return args.This();
  }

  /**
   *	Element constructor:
   * 	- Adds "Element()" method to global GC
   */
  JS_METHOD(_element) {
    /* TryCatch tc; */
    if (args.Length()!=1 && args.Length()!=2)
      return JS_ERROR("[_element()] ERROR: Incorrect number of input parameters");
    ASSERT_CONSTRUCTOR;
    //GC * gc = GC_PTR;
    //gc->add(args.This(), "~DOMElement");
    DOMElement * element = NULL;
    if (args[0]->IsExternal()) {
      element = RECAST(args[0],DOMElement *);
    }
    else if (args[0]->IsObject()) {
      Handle<Object> tobj( args[0]->ToObject() );
      element = RECAST(tobj->GetInternalField(0),DOMElement *);
    }
    if (element==NULL) {
      return JS_ERROR("[_element()] ERROR: \"element\" is a null pointer");
    }
    else {
      SAVE_PTR(0,element);
      return args.This();
    }
  }

  JS_METHOD(_elementgetasnode) {
	/* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_elementgetasnode()] ERROR: Too many input parameters");
    DOMNode * node = NULL;
    node = RECAST(args.This()->GetInternalField(0),DOMNode *);
    if (node==NULL) {
      return JS_ERROR("[elementgetasnode()] ERROR: \"node\" is a null pointer");
    }
    else {
      const int fargc = 2;
      Local<Value> upConvert( *Boolean::New(false) );
      v8::Local<v8::Value> fargv[] = { v8::External::New((void *)node), upConvert };
      v8::Handle<v8::Function> f = xdom::fnode->GetFunction();
      v8::Handle<v8::Object> ret ( f->NewInstance(fargc, fargv) );
      return ret;
    }
  }

  JS_METHOD(_elementgettagname) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_elementgettagname()] ERROR: Too many input parameters");
    EL;
    XS name = NULL;
    XTRY( name = (XMLCh *)el->getTagName(); );
    if (name==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(name);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_elementgetattribute) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_elementgetattribute()] ERROR: Incorrect number of input parameters");
    EL;
    XS val = NULL;
    XTRY( val = (XMLCh *)el->getAttribute(ARGSTR(0)); );
    if (val==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(val);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_elementgetattributenode) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_elementgetattributenode()] ERROR: Incorrect number of input parameters");
    EL;
    DOMAttr * attr = NULL;
    XTRY( attr = el->getAttributeNode(ARGSTR(0)); );
    if (attr==NULL) {
      return JS_ERROR("[_elementgetattributenode()] ERROR: \"attr\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)attr) };
      Handle<Object> ret( xdom::fattribute->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_elementgetelementsbytagname) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_elementgetelementsbytagname()] ERROR: Incorrect number of input parameters");
    EL;
    SS name( *String::Utf8Value(args[0]->ToString()) );
    DOMNodeList * nodelist = NULL;
    XTRY( nodelist = el->getElementsByTagName(X_STR(name)); );
    if (nodelist==NULL) {
      return JS_ERROR("[_elementgetelementsbytagname()] ERROR: \"nodelist\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)nodelist) };
      Handle<Object> ret( xdom::fnodelist->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_elementsetattribute) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_elementsetattribute()] ERROR: Incorrect number of input parameters");
    EL;
    XTRY( el->setAttribute(ARGSTR(0),ARGSTR(1)); );
    return args.This();
  }

  JS_METHOD(_elementsetattributenode) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_elementsetattributenode()] ERROR: Incorrect number of input parameters");
    EL;
    DOMAttr * newAttr = NULL;
    if (args[0]->IsExternal()) {
      newAttr = RECAST(args[0],DOMAttr *);
    }
    else if (args[0]->IsObject()) {
      newAttr = RECAST(args[0]->ToObject()->GetInternalField(0),DOMAttr *);
    }
    if (newAttr==NULL) {
      return JS_ERROR("[_elementsetattributenode()] ERROR: \"newAttr\" is a null pointer");
    }
    DOMAttr * ret = NULL;
    XTRY( ret = el->setAttributeNode(newAttr); );
    if (ret==NULL) {
      return v8::Null();
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)ret) };
      Handle<Object> ret( xdom::fattribute->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_elementremoveattributenode) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_elementremoveattributenode()] ERROR: Incorrect number of input parameters");
    EL;
    DOMAttr * oldAttr = NULL;
    if (args[0]->IsExternal()) {
      oldAttr = RECAST(args[0],DOMAttr *);
    }
    else if (args[0]->IsObject()) {
      oldAttr = RECAST(args[0]->ToObject()->GetInternalField(0),DOMAttr *);
    }
    if (oldAttr==NULL) {
      return JS_ERROR("[_elementremoveattributenode()] ERROR: \"oldAttr\" is a null pointer");
    }
    DOMAttr * ret = NULL;
    XTRY( ret = el->removeAttributeNode(oldAttr); );
    if (ret==NULL) {
      return JS_ERROR("[_elementremoveattributenode()] ERROR: \"ret\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)ret) };
      Handle<Object> ret( xdom::fattribute->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_elementremoveattribute) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_elementremoveattribute()] ERROR: Incorrect number of input parameters");
    EL;
    XTRY( el->removeAttribute(ARGSTR(0)); );
    return JS_BOOL(true);
  }

  JS_METHOD(_elementgetattributens) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_elementgetattributens()] ERROR: Incorrect number of input parameters");
    EL;
    XS val = NULL;
    XTRY( val = (XMLCh *)el->getAttributeNS(ARGSTR(0),ARGSTR(1)); );
    if (val==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(val);
      return JS_STR(ret);
    }    
  }

  JS_METHOD(_elementsetattributens) {
    /* TryCatch tc; */
    if (args.Length()!=3)
      return JS_ERROR("[_elementsetattributens()] ERROR: Incorrect number of input parameters");
    EL;
    XTRY( el->setAttributeNS(ARGSTR(0),ARGSTR(1),ARGSTR(2)); );
    return args.This();
  }

  JS_METHOD(_elementremoveattributens) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_elementremoveattributens()] ERROR: Incorrect number of input parameters");
    EL;
    XTRY( el->removeAttributeNS(ARGSTR(0),ARGSTR(1)); );
    return JS_BOOL(true);
  }

  JS_METHOD(_elementgetattributenodens) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_elementgetattributenodens()] ERROR: Incorrect number of input parameters");
    EL;
    DOMAttr * attr = NULL;
    XTRY( attr = el->getAttributeNodeNS(ARGSTR(0),ARGSTR(1)); );
    if (attr==NULL) {
      return JS_ERROR("[_elementgetattributenodens()] ERROR: \"attr\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)attr) };
      Handle<Object> ret( xdom::fattribute->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_elementsetattributenodens) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_elementsetattributenodens()] ERROR: Incorrect number of input parameters");
    EL;
    DOMAttr * newAttr = NULL;
    if (args[0]->IsExternal()) {
      newAttr = RECAST(args[0],DOMAttr *);
    }
    else if (args[0]->IsObject()) {
      newAttr = RECAST(args[0]->ToObject()->GetInternalField(0),DOMAttr *);
    }
    if (newAttr==NULL) {
      return JS_ERROR("[_elementsetattributenodens()] ERROR: \"newAttr\" is a null pointer");
    }
    DOMAttr * ret = NULL;
    XTRY( ret = el->setAttributeNodeNS(newAttr); );
    if (ret==NULL) {
      return v8::Null();
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)ret) };
      Handle<Object> ret( xdom::fattribute->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_elementgetelementsbytagnamens) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_elementgetelementsbytagnamens()] ERROR: Incorrect number of input parameters");
    EL;
    DOMNodeList * nodelist = NULL;
    XTRY( nodelist = el->getElementsByTagNameNS(ARGSTR(0),ARGSTR(1)); );
    if (nodelist==NULL) {
      return JS_ERROR("[_elementgetelementsbytagnamens()] ERROR: \"nodelist\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)nodelist) };
      Handle<Object> ret( xdom::fnodelist->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_elementhasattribute) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_elementhasattribute()] ERROR: Incorrect number of input parameters");
    EL;
    bool ret = false;
    XTRY( el->hasAttribute(ARGSTR(0)); );
    return JS_BOOL(ret);
  }

  JS_METHOD(_elementhasattributens) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_elementhasattributens()] ERROR: Incorrect number of input parameters");
    EL;
    bool ret = false;
    XTRY( ret = el->hasAttributeNS(ARGSTR(0),ARGSTR(1)); );
    return JS_BOOL(ret);    
  }

  JS_METHOD(_elementsetidattribute) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_elementsetidattribute()] ERROR: Incorrect number of input parameters");
    EL;
    bool isId = args[1]->ToBoolean()->BooleanValue();
    XTRY( el->setIdAttribute(ARGSTR(0),isId); );
    return args.This();
  }

  JS_METHOD(_elementsetidattributens) {
    /* TryCatch tc; */
    if (args.Length()!=3)
      return JS_ERROR("[_elementsetidattributens()] ERROR: Incorrect number of input parameters");
    EL;
    bool isId = args[2]->ToBoolean()->BooleanValue();
    XTRY( el->setIdAttributeNS(ARGSTR(0),ARGSTR(1),isId); );
    return args.This();
  }

  JS_METHOD(_elementsetidattributenode) {
    /* TryCatch tc; */
    if (args.Length()!=2)
      return JS_ERROR("[_elementsetidattributenode()] ERROR: Incorrect number of input parameters");
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
    return args.This();
  }

  JS_METHOD(_elementgetschematypeinfo) {
    /* TryCatch tc; */
     if (args.Length()>0)
      return JS_ERROR("[_elementgetschematypeinfo()] ERROR: Too many input parameters");
    EL;
    DOMTypeInfo * typeinfo = NULL;
    XTRY( typeinfo = (DOMTypeInfo *)el->getSchemaTypeInfo(); );
    if (typeinfo==NULL) {
      return JS_ERROR("[_elementgetschematypeinfo()] ERROR: \"typeinfo\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)typeinfo) };
      Handle<Object> ret( xdom::ftypeinfo->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  /**
   *	~Element method
   *	- Destructor for Element objects
   */ 
  JS_METHOD(_element_destructor) {
    /* TryCatch tc; */
    //ELEMENT;
    XTRY(
	// element->release();
	//element->~DOMElement(); 
    );
    //SAVE_PTR(0,NULL)
    return args.This();
  }

  /**
   *	Attribute constructor:
   * 	- Adds "Attribute()" method to global GC
   */
  JS_METHOD(_attribute) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_attribute()] ERROR: Incorrect number of input parameters");
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
      return JS_ERROR("[_attribute()] ERROR: \"attr\" is a null pointer");
    }
    else {
      SAVE_PTR(0,attr);
      return args.This();
    }
  }

  JS_METHOD(_attributegetname) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_attributegetname()] ERROR: Too many input parameters");
    ATTRIBUTE;
    XS name = NULL;
    XTRY( name = (XMLCh *)attribute->getName(); );
    if (name==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(name);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_attributegetspecified) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_attributegetspecified()] ERROR: Too many input parameters");
    ATTRIBUTE;
    bool ret = false;
    XTRY( ret = (bool)attribute->getSpecified(); );
    return JS_BOOL(ret);
  }

  JS_METHOD(_attributegetvalue) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_attributegetvalue()] ERROR: Too many input parameters");
    ATTRIBUTE;
    XS val = NULL;
    XTRY( val = (XMLCh *)attribute->getValue(); );
    if (val==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(val);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_attributesetvalue) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_attributesetvalue()] ERROR: Incorrect number of input parameters");
    ATTRIBUTE;
    XTRY( attribute->setValue(ARGSTR(0)); );
    return args.This();
  }

  JS_METHOD(_attributegetownerelement) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_attributegetownerelement()] ERROR: Too many input parameters");
    ATTRIBUTE;
    DOMElement * el = NULL;
    XTRY( el = attribute->getOwnerElement(); );
    if (el==NULL) {
      return JS_ERROR("[_attributegetownerelement()] ERROR: \"el\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)el) };
      Handle<Object> ret( xdom::felement->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  JS_METHOD(_attributeisid) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_attributeisid()] ERROR: Too many input parameters");
    ATTRIBUTE;
    bool ret = false;
    XTRY( ret = attribute->isId(); );
    return JS_BOOL(ret);
  }

  JS_METHOD(_attributegetschematypeinfo) {
    /* TryCatch tc; */
    if (args.Length()>0)
      return JS_ERROR("[_attributegetschematypeinfo()] ERROR: Too many input parameters");
    ATTRIBUTE;
    DOMTypeInfo * typeinfo = NULL;
    XTRY( typeinfo = (DOMTypeInfo *)attribute->getSchemaTypeInfo(); );
    if (typeinfo==NULL) {
      return JS_ERROR("[_attributegetschematypeinfo()] ERROR: \"typeinfo\" is a null pointer");
    }
    else {
      Handle<Value> fargs[] = { External::New((void *)typeinfo) };
      Handle<Object> ret( xdom::ftypeinfo->GetFunction()->NewInstance(1, fargs) );
      return ret;
    }
  }

  /**
   *	~Attribute method
   *	- Destructor for Attribute objects
   */
  JS_METHOD(_attribute_destructor) {
    /* TryCatch tc; */
    //ATTRIBUTE;
    //XTRY( attribute->release(); );
    //XTRY( attribute->~DOMAttr(); );
    // SAVE_PTR(0,NULL);
    return args.This();
  }

  /**
   *	CDATA constructor:
   * 	- Adds "CDATA()" method to global GC
   */
  JS_METHOD(_cdata) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_cdata()] ERROR: Incorrect number of input parameters");
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
      return JS_ERROR("[_cdata()] ERROR: \"cdata\" is a null pointer");
    }
    else {
      SAVE_PTR(0,cdata);
      return args.This();
    }
  }

  JS_METHOD(_cdatagetdata) {
    /* TryCatch tc; */
    CDATA;
    const XS data = NULL;
    XTRY( data = (XMLCh *)cdata->getData(); );
    if (data==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(data);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_cdatagetlength) {
    /* TryCatch tc; */
    CDATA;
    XMLSize_t ret = 0;
    XTRY( ret = cdata->getLength(); );
    return JS_INT(ret);
  }

  JS_METHOD(_cdatasubstringdata) {
    /* TryCatch tc; */
    CDATA;
    XMLSize_t offset = (XMLSize_t)args[0]->ToInteger()->IntegerValue();
    XMLSize_t count = (XMLSize_t)args[1]->ToInteger()->IntegerValue();
    XS data = NULL;
    XTRY( data = (XMLCh *)cdata->substringData(offset, count); );
    if (data==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(data);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_cdataappenddata) {
    /* TryCatch tc; */
    CDATA;
    SS data( *String::Utf8Value(args[0]->ToString()) );
    XTRY( cdata->appendData(X_STR(data)); );
    return args.This();
  }

  JS_METHOD(_cdatainsertdata) {
    /* TryCatch tc; */
    CDATA;
    XMLSize_t offset = (XMLSize_t)args[0]->ToInteger()->IntegerValue();
    SS data( *String::Utf8Value(args[1]->ToString()) );
    XTRY( cdata->insertData(offset,X_STR(data)); );
    return args.This();
  }

  JS_METHOD(_cdatadeletedata) {
    /* TryCatch tc; */
    CDATA;
    XMLSize_t offset = (XMLSize_t)args[0]->ToInteger()->IntegerValue();
    XMLSize_t count = (XMLSize_t)args[1]->ToInteger()->IntegerValue();
    XTRY( cdata->deleteData(offset, count); );
    return args.This();
  }

  JS_METHOD(_cdatareplacedata) {
    /* TryCatch tc; */
    CDATA;
    XMLSize_t offset = (XMLSize_t)args[0]->ToInteger()->IntegerValue();
    XMLSize_t count = (XMLSize_t)args[1]->ToInteger()->IntegerValue();
    SS data( *String::Utf8Value(args[2]->ToString()) );
    XTRY( cdata->replaceData(offset, count, X_STR(data)); );
    return args.This();
  }

  JS_METHOD(_cdatasetdata) {
    /* TryCatch tc; */
    CDATA;
    SS data( *String::Utf8Value(args[0]->ToString()) );
    XTRY( cdata->setData(X_STR(data)); );
    return args.This();
  }

  /**
   *	~CDATA method
   *	- Destructor for CDATA objects
   */ 
  JS_METHOD(_cdata_destructor) {
    /* TryCatch tc; */
    //CDATA;
    //XTRY( cdata->~DOMCharacterData(); );
    // SAVE_PTR(0,NULL);
    return args.This();
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
      return JS_ERROR("[_comment()] ERROR: \"comment\" is a null pointer");
    }
    else {
      SAVE_PTR(0,comment);
      return args.This();
    }
  }

  /**
   *	~Comment method
   *	- Destructor for Comment objects
   */ 
  JS_METHOD(_comment_destructor) {
    /* TryCatch tc; */
    //COMMENT;
    //XTRY( comment->~DOMComment(); );
    // SAVE_PTR(0,NULL);
    return args.This();
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
      return JS_ERROR("[_entity()] ERROR: \"entity\" is a null pointer");
    }
    else {
      SAVE_PTR(0,entity);
      return args.This();
    }
  }

  JS_METHOD(_entitygetpublicid) {
    /* TryCatch tc; */
    if (args.Length()>0) {
      return JS_ERROR("[_entitygetpublicid()] ERROR: Too many input parameters");
    }
    ENTITY;
    XS publicid = NULL;
    XTRY( publicid = (XMLCh *)entity->getPublicId(); );
    if (publicid==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(publicid);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_entitygetsystemid) {
    /* TryCatch tc; */
    if (args.Length()>0) {
      return JS_ERROR("[_entitygetsystemid()] ERROR: Too many input parameters");
    }
    ENTITY;
    XS systemid = NULL;
    XTRY( systemid = (XMLCh *)entity->getSystemId(); );
    if (systemid==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(systemid);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_entitygetnotationname) {
    /* TryCatch tc; */
    if (args.Length()>0) {
      return JS_ERROR("[_entitygetnotationname()] ERROR: Too many input parameters");
    }
    ENTITY;
    XS name = NULL;
    XTRY( name = (XMLCh *)entity->getNotationName(); );
    if (name==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(name);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_entitygetinputencoding) {
    /* TryCatch tc; */
    if (args.Length()>0) {
      return JS_ERROR("[_entitygetinputencoding()] ERROR: Too many input parameters");
    }
    ENTITY;
    XS encoding = NULL;
    XTRY( encoding = (XMLCh *)entity->getInputEncoding(); );
    if (encoding==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(encoding);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_entitygetxmlencoding) {
    /* TryCatch tc; */
    if (args.Length()>0) {
      return JS_ERROR("[_entitygetxmlencoding()] ERROR: Too many input parameters");
    }
    ENTITY;
    XS encoding = NULL;
    XTRY( encoding = (XMLCh *)entity->getXmlEncoding(); );
    if (encoding==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(encoding);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_entitygetxmlversion) {
    /* TryCatch tc; */
    if (args.Length()>0) {
      return JS_ERROR("[_entitygetxmlversion()] ERROR: Too many input parameters");
    }
    ENTITY;
    XS version = NULL;
    XTRY( version = (XMLCh *)entity->getXmlVersion(); );
    if (version==NULL) {
      return JS_STR("");
    }
    else {
      char * ret = X(version);
      return JS_STR(ret);
    }
  }

  /**
   *	~Entity method
   *	- Destructor for Entity objects
   */ 
  JS_METHOD(_entity_destructor) {
    /* TryCatch tc; */
    //ENTITY;
    //XTRY( entity->~DOMEntity(); );
    // SAVE_PTR(0,NULL);
    return args.This();
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
      return JS_ERROR("[_entityreference()] ERROR: \"entityreference\" is a null pointer");
    else {
      SAVE_PTR(0,entityreference);
      return args.This();
    }
  }

  /**
   *	~EntityReference method
   *	- Destructor for EntityReference objects
   */ 
  JS_METHOD(_entityreference_destructor) {
    /* TryCatch tc; */
    ENTITYREFERENCE;
    XTRY( entityreference->~DOMEntityReference(); );
    // SAVE_PTR(0,NULL);
    return args.This();
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
      return JS_ERROR("[_notation()] ERROR: \"notation\" is a null pointer");
    else {
      SAVE_PTR(0,notation);
      return args.This();
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
    return JS_STR(ret);
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
    return JS_STR(ret);
  }

  /**
   *	~Notation method
   *	- Destructor for Notation objects
   */ 
  JS_METHOD(_notation_destructor) {
    /* TryCatch tc; */
    //NOTATION;
    //XTRY( notation->~DOMNotation(); );
    // SAVE_PTR(0,NULL);
    return args.This();
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
      return JS_ERROR("[_procinst()] ERROR: \"procinst\" is a null pointer");
    else {
      SAVE_PTR(0,procinst);
      return args.This();
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
    return JS_STR(ret);
  }

  JS_METHOD(_processinginstructionsetdata) {
    if (args.Length()!=1) {
      return JS_ERROR("[_processinginstructionsetdata()] ERROR: Incorrect number of input parameters");
    }
    PROCINST;
    XTRY( procinst->setData(ARGSTR(0)); );
    return args.This();
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
    return JS_STR(ret);
  }

  /**
   *	~ProcessingInstruction method
   *	- Destructor for ProcessingInstruction objects
   */ 
  JS_METHOD(_processinginstruction_destructor) {
    /* TryCatch tc; */
    //PROCINST;
    // SAVE_PTR(0,NULL);
    //XTRY( procinst->~DOMProcessingInstruction(); );
    return args.This();
  }


  /**
   *	DOMTypeInfo
   **/
  JS_METHOD(_typeinfo) {
    /* TryCatch tc; */
    if (args.Length()!=1)
      return JS_ERROR("[_typeinfo()] ERROR: Incorrect number of input parameters");
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
      return JS_ERROR("[_typeinfo()] ERROR: \"typeinfo\" is a null pointer");
    }
    else {
      SAVE_PTR(0, typeinfo);
      return args.This();
    }
  }

  JS_METHOD(_typeinfogettypename) {
    /* TryCatch tc; */
    if (args.Length()>0) {
      return JS_ERROR("[_typeinfogettypename()] ERROR: Too many input parameters");
    }
    TYPEINFO;
    XS name = NULL;
    XTRY( name = (XMLCh *)typeinfo->getTypeName(); );
    if (name==NULL) {
      return JS_ERROR("[_typeinfogettypename()] ERROR: \"name\" is a null pointer");
    }
    else {
      char * ret = X(name);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_typeinfogettypenamespace) {
    /* TryCatch tc; */
    if (args.Length()>0) {
      return JS_ERROR("[_typeinfogettypename()] ERROR: Too many input parameters");
    }
    TYPEINFO;
    XS lnamespace = NULL;
    XTRY( lnamespace = (XMLCh *)typeinfo->getTypeNamespace(); );
    if (lnamespace==NULL) {
      return JS_ERROR("[_typeinfogettypenamespace()] ERROR: \"namespace\" is a null pointer");
    }
    else {
      char * ret = X(lnamespace);
      return JS_STR(ret);
    }
  }

  JS_METHOD(_typeinfoisderivedfrom) {
    /* TryCatch tc; */
    if (args.Length()!=3) {
      return JS_ERROR("[_typeinfogettypename()] ERROR: Incorrect number of input parameters");
    }
    TYPEINFO;
    int derivationMethod = (int)args[2]->ToInteger()->IntegerValue();
    bool ret = false;
    XTRY( ret = typeinfo->isDerivedFrom(ARGSTR(0),ARGSTR(1),(xercesc_3_0::DOMTypeInfo::DerivationMethods)derivationMethod); );
    return JS_BOOL(ret);
  }

  JS_METHOD(_typeinfo_destructor) {
    /* TryCatch tc; */
    TYPEINFO;
    //XTRY( typeinfo->release(); );
    XTRY( typeinfo->~DOMTypeInfo(); );
    return args.This();
  }


  // * * *
  // * * *	Property accessors
  // * * *

  Handle<Value> echo_data(Local<String> name, const AccessorInfo& args) {
    Handle<Value> ret( JS_STR(*USTR(args.Data())) );
    return ret;
  }

  Handle<Value> get_node_type(Local<String> name, const AccessorInfo& args) {
    /* TryCatch tc; */
    NODE;
    int nodeType = 0;
    XTRY( nodeType = (int)node->getNodeType(); );
    if (nodeType==0) {
      return JS_ERROR("[get_node_type()] ERROR: nodeType is invalid");
    }
    else {
      Handle<Integer> ret( JS_INT(nodeType) );
      return ret;
    }
  }

  Handle<Value> get_node_name(Local<String> name, const AccessorInfo& args) {
    /* TryCatch tc; */
    NODE;
    XS nodeName = NULL;
    XTRY( nodeName = (XMLCh *)node->getNodeName(); );
    if (nodeName==NULL) {
      return JS_ERROR("[get_node_name()] ERROR: \"nodeName\" is a null pointer");
    }
    else {
      Handle<String> ret( JS_STR(X(nodeName)) );
      return ret;
    }
  }

  Handle<Value> get_node_value(Local<String> name, const AccessorInfo& args) {
    /* TryCatch tc; */
    NODE;
    XS nodeValue = NULL;
    XTRY( nodeValue = (XMLCh *)node->getNodeValue(); );
    if (nodeValue==NULL) {
      return JS_ERROR("[get_node_value()] ERROR: \"nodeValue\" is a null pointer");
    }
    else {
      char * tmp = NULL;
      Handle<Value> ret( v8::Undefined() );
      if (nodeValue!=NULL) {
        tmp = X(nodeValue);
        if (strlen(tmp)<1) {
          ret = v8::Null();
        }
        else {
          ret = JS_STR(tmp);
        }
      }
      return ret;
    }
  }

  Handle<Value> get_tag_name(Local<String> name, const AccessorInfo& args) {
    /* TryCatch tc; */
    EL;
    XS tagName = NULL;
    XTRY( tagName = (XMLCh *)el->getTagName(); );
    if (tagName==NULL) {
      return JS_ERROR("[get_tag_name()] ERROR: \"tagName\" is a null pointer");
    }
    else {
      char * tmp = NULL;
      Handle<Value> ret( v8::Undefined() );
      if (tagName!=NULL) {
        tmp = X(tagName);
        if (strlen(tmp)<1) {
          ret = v8::Null();
        }
        else {
          ret = JS_STR(tmp);
        }
      }
      return ret;
    }
  }

  Handle<Value> get_property (Local<String> iName, const AccessorInfo& args) {
	/* TryCatch tc; */
    std::string name(*String::Utf8Value(iName));
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
    else if (name=="localName" || name=="LocalName")
      funcname << "getLocalName";
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
    else if (name=="value" || name=="Value")
      funcname << "getValue";
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
    else if (name=="nodevalue" || name=="NodeValue")
      funcname << "getNodeValue";
    else if (name=="prefix" || name=="Prefix")
      funcname << "getPrefix";
    v8::Local<v8::Value> f = args.Holder()->Get(JS_STR(CSTR(funcname)));
    v8::Handle<v8::Function> func = v8::Local<v8::Function>::Cast(f);
    v8::Handle<v8::Value> ret ( func->Call(args.Holder(), fargc, fargv) );
    return ret;
  }

  void set_property (Local<String> iName, Local<Value> iValue, const AccessorInfo& args) {
	/* TryCatch tc; */
    std::string name(*String::Utf8Value(iName));
    SS funcname("");
    const int fargc = 1;
    v8::Handle<v8::Value> fargv[] = { iValue };
    if (name=="filter" || name=="Filter")
      funcname << "setFilter";
    else if (name=="value" || name=="Value")
      funcname << "setValue";
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
    else if (name=="nodevalue" || name=="NodeValue")
      funcname << "setNodeValue";
    else if (name=="prefix" || name=="Prefix")
      funcname << "setPrefix";
    v8::Local<v8::Value> f = args.This()->Get(JS_STR(CSTR(funcname)));
    v8::Handle<v8::Function> func = v8::Local<v8::Function>::Cast(f);
    func->Call(args.This(), fargc, fargv);
    return (void)false;
  }


  Handle<Value> get_as_node (Local<String> iName, const AccessorInfo& args) {
	/* TryCatch tc; */
    std::string name(*String::Utf8Value(iName));
    DOMNode * node = NULL;
    node = RECAST(args.Holder()->GetInternalField(0),DOMNode *);
    if (node==NULL) {
      return JS_ERROR("[get_as_node()] ERROR: \"node\" is a null pointer");
    }
    else {
      const int fargc = 2;
      Local<Value> upConvert( *Boolean::New(false) );
      v8::Local<v8::Value> fargv[] = { v8::External::New((void *)node), upConvert };
      v8::Handle<v8::Function> f = xdom::fnode->GetFunction();
      v8::Handle<v8::Object> ret ( f->NewInstance(fargc, fargv) );
      return ret;
    }
  }

  Handle<Value> get_as_element (Local<String> iName, const AccessorInfo& args) {
	/* TryCatch tc; */
    std::string name(*String::Utf8Value(iName));
    DOMNode * node = NULL;
    node = RECAST(args.Holder()->GetInternalField(0),DOMNode *);
    if (node==NULL) {
      return JS_ERROR("[get_as_element()] ERROR: \"node\" is a null pointer");
    }
    else {
      const int fargc = 2;
      Local<Value> upConvert( *Boolean::New(true) );
      v8::Local<v8::Value> fargv[] = { v8::External::New((void *)node), upConvert };
      v8::Handle<v8::Function> f = xdom::fnode->GetFunction();
      v8::Handle<v8::Object> ret ( f->NewInstance(fargc, fargv) );
      return ret;
    }
  }

  //	Indexed property handlers:
  //		(these enable "square bracket"-style dereferencing of items in array-like collections
  //		 such as DOMNodeList, DOMStringList, or DOMNamedNodeMap objects, using an integer as index)

  v8::Handle<v8::Value> indexed_property_get( uint32_t index, const AccessorInfo& args ) {
    SS objstream( *String::Utf8Value(args.Data()->ToString()) );
    std::string objtype( objstream.str() );
    Handle<Object> This( args.Holder() );
    Handle<Value> ret;
    XMLSize_t idx = (XMLSize_t)index;
    if (objtype=="domlist") {
      DOMImplementationList * domlist = reinterpret_cast<DOMImplementationList *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      DOMImplementation * val = NULL;
      XTRY( val = (DOMImplementation *)domlist->item(idx); );
      if (val==NULL) {
	// JS_ERROR("[indexed_property_get()] ERROR: (domlist) \"val\" is a null pointer");
	ret = v8::Undefined();
      }
      else {
	Local<Value> fargs[] = { v8::External::New((void *)val) };
	ret = xdom::fdom->GetFunction()->NewInstance(1, fargs);
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
	ret = v8::Undefined();
      }
      else {
	Local<Value> fargs[] = { v8::External::New((void *)val) };
	ret = xdom::fnode->GetFunction()->NewInstance(1, fargs);
      }
    }
    else if (objtype=="nodelist") {
      DOMNodeList * nodelist = reinterpret_cast<DOMNodeList *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      DOMNode * val = NULL;
      XTRY( val = nodelist->item(idx); );
      if (val==NULL) {
	//JS_ERROR("[indexed_property_get()] ERROR: (nodelist) \"val\" is a null pointer");
	ret = v8::Undefined();
      }
      else {
	Local<Value> fargs[] = { v8::External::New((void *)val) };
	ret = xdom::fnode->GetFunction()->NewInstance(1, fargs);
      }
    }
    else {
      return JS_ERROR("[indexed_property_get()] ERROR: unrecognized object type");
    }
    return ret;
  }

  v8::Handle<v8::Value> indexed_property_set( uint32_t index, Local<Value> iValue, const AccessorInfo& args ) {
    SS objstream( *String::Utf8Value(args.Data()->ToString()) );
    std::string objtype( objstream.str() );
    Handle<Object> This( args.Holder() );
    Handle<Boolean> ret( JS_BOOL(false) );
    if (objtype=="stringlist") {
      return JS_ERROR("[indexed_property_set()] ERROR");
    }
    else if (objtype=="domlist") {
      return JS_ERROR("[indexed_property_set()] ERROR");
    }
    else if (objtype=="namednodemap") {
    }
    else if (objtype=="nodelist") {
      return JS_ERROR("[indexed_property_set()] ERROR");
    }
    else {
      return JS_ERROR("[indexed_property_set()] ERROR: unrecognized object type");
    }
    return JS_BOOL(true);
  }

  v8::Handle<v8::Boolean> indexed_property_query( uint32_t index, const AccessorInfo& args ) {
    SS objstream( *String::Utf8Value(args.Data()->ToString()) );
    std::string objtype( objstream.str() );
    Handle<Object> This( args.Holder() );
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
      catch( xercesc_3_0::DOMException& e ) {
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
      catch( xercesc_3_0::DOMException& e ) {
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
    return JS_BOOL(ret);
  }

  v8::Handle<v8::Boolean> indexed_property_delete( uint32_t index, const AccessorInfo& args ) {
    SS objstream( *String::Utf8Value(args.Data()->ToString()) );
    std::string objtype( objstream.str() );
    Handle<Object> This( args.Holder() );
    Handle<Boolean> ret( JS_BOOL(false) );
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
      catch( xercesc_3_0::DOMException& e ) {
	char * msg = X(e.getMessage());
	JS_ERROR(msg);
      }
    }
    else {
      JS_ERROR("[indexed_property_delete()] ERROR: unrecognized object type");
    }
    return JS_BOOL(true);
  }

  v8::Handle<v8::Array> indexed_property_enumerate( const AccessorInfo& args ) {
    SS objstream( *String::Utf8Value(args.Data()->ToString()) );
    std::string objtype( objstream.str() );
    Handle<Object> This( args.Holder() );
    Handle<Array> ret;
    if (objtype=="domlist") {
     ZTRY(
      DOMImplementationList * domlist = reinterpret_cast<DOMImplementationList *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      XMLSize_t len = domlist->getLength();
      ret = v8::Array::New(len);
      for (unsigned int i = (int)len; i < len; i++) {
	DOMImplementation * val = domlist->item(i);
	Local<Value> fargs[] = { v8::External::New((void *)val) };
	Handle<Object> tmp( xdom::fdom->GetFunction()->NewInstance(1, fargs) );
	ret->Set(JS_INT(i), tmp);
      }
     );
    }
    else if (objtype=="stringlist") {
     ZTRY(
      DOMStringList * stringlist = reinterpret_cast<DOMStringList *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      XMLSize_t len = stringlist->getLength();
      ret = v8::Array::New(len);
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
      ret = v8::Array::New(len);
      for (unsigned int i = (int)len; i < len; i++) {
	DOMNode * val = NULL;
	try { val = nodemap->item(i); } catch( DOMException& e ) { char * msg = X(e.getMessage()); JS_ERROR(msg); }
	if (val!=NULL) {
	  Local<Value> fargs[] = { v8::External::New((void *)val) };
	  Handle<Object> tmp( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
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
      ret = v8::Array::New(len);
      for (unsigned int i = (int)len; i < len; i++) {
	DOMNode * val = nodelist->item(i);
	Local<Value> fargs[] = { v8::External::New((void *)val) };
	Handle<Object> tmp( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
	ret->Set(JS_INT(i), tmp);
      }
     );
    }
    else {
      JS_ERROR("[indexed_property_enumerate()] ERROR: unrecognized object type");
    }
    return ret;
  }


  //	Named property handlers:
  //		(these enable "hash"-style dereferencing of items in hash-like collections such
  //		 as DOMNamedNodeMap objects, using a string as the index instead of an integer)

  v8::Handle<v8::Value> named_property_get( Local<String> index, const AccessorInfo& args ) {
    SS objstream( *String::Utf8Value(args.Data()->ToString()) );
    std::string objtype( objstream.str() );
    Handle<Object> This( args.Holder() );
    SS tmp( *String::Utf8Value(index) );
    const char * name = tmp.str().c_str();
    XS idx = X(name);
    Handle<Value> ret;
    if (objtype=="namednodemap") {
      ZTRY(
	DOMNamedNodeMap * nodemap = reinterpret_cast<DOMNamedNodeMap *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
	DOMNode * val = NULL;
	val = nodemap->getNamedItem(idx);
	if (val==NULL) {
	  ret = v8::Undefined();
	}
	else {
	  Local<Value> fargs[] = { v8::External::New((void *)val) };
	  ret = xdom::fnode->GetFunction()->NewInstance(1, fargs);
	}
      );
    }
    else if (objtype=="element") {
      ZTRY(
	DOMElement * el = reinterpret_cast<DOMElement *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
	DOMElement * pel = el;
	Local<Value> fargs[] = { v8::External::New((void *)pel) };
	Handle<Object> pobj ( xdom::fpreelement->GetFunction()->NewInstance(1, fargs) );
	Handle<Value> pval ( pobj->Get(index) );
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
      return JS_ERROR("[named_property_get()] ERROR: unrecognized object type");
    }
    return ret;
  }

  v8::Handle<v8::Value> named_property_set( Local<String> index, Local<Value> iValue, const AccessorInfo& args ) {
    SS objstream( *String::Utf8Value(args.Data()->ToString()) );
    std::string objtype( objstream.str() );
    Handle<Object> This( args.Holder() );
    Handle<Value> ret;
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
	return JS_ERROR("[named_property_set()] ERROR: \"node\" is a null pointer");
      }
      else {
	DOMNode * retval = NULL;
	XTRY( retval = nodemap->setNamedItem(node); );
	if (retval==NULL) {
	  //return JS_ERROR("[named_property_set()] ERROR: \"retval\" is a null pointer");
	  return v8::Null();
	}
	else {
	  Local<Value> fargs[] = { v8::External::New((void *)retval) };
	  ret = xdom::fnode->GetFunction()->NewInstance(1, fargs);
	  return ret;
	}
      }
     );
    }
    else if (objtype=="element") {
     ZTRY(
      DOMElement * el = reinterpret_cast<DOMElement *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      DOMElement * pel = el;
      Local<Value> fargs[] = { v8::External::New((void *)pel) };
      Handle<Object> pobj ( xdom::fpreelement->GetFunction()->NewInstance(1, fargs) );
      bool pval = pobj->Has(index);
      if ( pval==true ) {
        pobj->Set(index, iValue);
      }
      else {
        XMLSize_t fargc = 2;
        Local<Value> fargv[] = { index, iValue };
        Handle<Function> f( Local<Function>::Cast(pobj->Get(JS_STR("setAttribute"))) );
        f->Call(pobj, fargc, fargv );
      }
     );
    }
    else {
      return JS_ERROR("[named_property_set()] ERROR: unrecognized object type");
    }
    return v8::Undefined();
  }

  v8::Handle<v8::Boolean> named_property_query( Local<String> index, const AccessorInfo& args ) {
    SS objstream( *String::Utf8Value(args.Data()->ToString()) );
    std::string objtype( objstream.str() );
    Handle<Object> This( args.Holder() );
    SS tmp( *String::Utf8Value(index) );
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
      Local<Value> fargs[] = { v8::External::New((void *)pel) };
      Handle<Object> pobj ( xdom::fpreelement->GetFunction()->NewInstance(1, fargs) );
      bool pval = pobj->Has(index);
      if ( pval==true ) {
        return JS_BOOL(true);
      }
      else {
        bool hasAttr = false;
        hasAttr = el->hasAttribute(idx);
        Handle<Boolean> tbool( JS_BOOL(hasAttr) );
        return tbool;
      }
     );
    }
    else {
      JS_ERROR("[named_property_query()] ERROR: unrecognized object type");
    }
    Handle<Boolean> ret( JS_BOOL(exists) );
    return ret;
  }

  v8::Handle<v8::Boolean> named_property_delete( Local<String> index, const AccessorInfo& args ) {
    SS objstream( *String::Utf8Value(args.Data()->ToString()) );
    std::string objtype( objstream.str() );
    Handle<Object> This( args.Holder() );
    SS tmp( *String::Utf8Value(index) );
    XS idx( X(tmp.str().c_str()) );
    if (objtype=="namednodemap") {
      DOMNamedNodeMap * nodemap = reinterpret_cast<DOMNamedNodeMap *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      try { nodemap->removeNamedItem(idx); } catch( xercesc_3_0::DOMException& e ) { char * msg = X(e.getMessage()); JS_ERROR(msg); }
    }
    else if (objtype=="element") {
      DOMElement * el = reinterpret_cast<DOMElement *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      try { el->removeAttribute(idx); } catch( xercesc_3_0::DOMException& e ) { char * msg = X(e.getMessage()); JS_ERROR(msg); }
    }
    else {
      JS_ERROR("[named_property_delete()] ERROR: unrecognized object type");
    }
    return JS_BOOL(true);
  }

  v8::Handle<v8::Array> named_property_enumerate( const AccessorInfo& args ) {
    SS objstream( *String::Utf8Value(args.Data()->ToString()) );
    std::string objtype( objstream.str() );
    Handle<Object> This( args.Holder() );
    Handle<Array> ret;
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
      ret = v8::Array::New(len);
      for (unsigned int i = (int)len; i < len; i++) {
	DOMNode * val = nodelist->item(i);
	Local<Value> fargs[] = { v8::External::New((void *)val) };
	Handle<Object> tmp( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
	ret->Set(JS_INT(i), tmp);
      }
     );
    }
    else if (objtype=="element") {
      DOMElement * el = reinterpret_cast<DOMElement *>(v8::Handle<v8::External>::Cast(This->GetInternalField(0))->Value());
      DOMElement * pel = el;
      Local<Value> fargs[] = { v8::External::New((void *)pel) };
      Handle<Object> pobj ( xdom::fpreelement->GetFunction()->NewInstance(1, fargs) );
      Local<Array> arr( pobj->GetPropertyNames() );
	XMLSize_t xlen = arr->Length();
      DOMNamedNodeMap * nodemap = NULL;
      try { nodemap = pel->getAttributes(); } catch( DOMException& e ) { char * msg = X(e.getMessage()); JS_ERROR(msg); }
      if (nodemap==NULL) {
	ret = arr;
      }
      else {
	XMLSize_t tlen = (XMLSize_t)nodemap->getLength();
	XMLSize_t len = tlen + xlen;
	ret = v8::Array::New(len);
	XMLSize_t i = 0;
	for (i = 0; i < xlen; i++) {
	  Handle<Value> val( arr->Get(JS_INT(i)) );
	  ret->Set(JS_INT(i), val);
	}
	for (i = 0; i < tlen; i++) {
	  DOMNode * val = nodemap->item(i);
	  Local<Value> fargs[] = { v8::External::New((void *)val) };
	  Handle<Object> tmp( xdom::fnode->GetFunction()->NewInstance(1, fargs) );
	  ret->Set(JS_INT((i + xlen)), tmp);
	}
      }
    }
    else {
      JS_ERROR("[named_property_enumerate()] ERROR: unrecognized object type");
    }
    return ret;
  }


} /* end namespace "xdom" */


SHARED_INIT() {


  // ********************************************************
  // *****	BEGIN [[ DOMException ]]		*****
  // *****						*****

    xdom::fdomexcpt = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_domexcpt));
    xdom::fdomexcpt->SetClassName(JS_STR("DOMException"));
    xdom::fdomexcpt->Set(JS_STR("INDEX_SIZE_ERR"),JS_INT((unsigned int)xercesc_3_0::DOMException::INDEX_SIZE_ERR));
    xdom::fdomexcpt->Set(JS_STR("DOMSTRING_SIZE_ERR"),JS_INT((unsigned int)xercesc_3_0::DOMException::DOMSTRING_SIZE_ERR));
    xdom::fdomexcpt->Set(JS_STR("HIERARCHY_REQUEST_ERR"),JS_INT((unsigned int)xercesc_3_0::DOMException::HIERARCHY_REQUEST_ERR));
    xdom::fdomexcpt->Set(JS_STR("WRONG_DOCUMENT_ERR"),JS_INT((unsigned int)xercesc_3_0::DOMException::WRONG_DOCUMENT_ERR));
    xdom::fdomexcpt->Set(JS_STR("INVALID_CHARACTER_ERR"),JS_INT((unsigned int)xercesc_3_0::DOMException::INVALID_CHARACTER_ERR));
    xdom::fdomexcpt->Set(JS_STR("NO_DATA_ALLOWED_ERR"),JS_INT((unsigned int)xercesc_3_0::DOMException::NO_DATA_ALLOWED_ERR));
    xdom::fdomexcpt->Set(JS_STR("NO_MODIFICATION_ALLOWED_ERR"),JS_INT((unsigned int)xercesc_3_0::DOMException::NO_MODIFICATION_ALLOWED_ERR));
    xdom::fdomexcpt->Set(JS_STR("NOT_FOUND_ERR"),JS_INT((unsigned int)xercesc_3_0::DOMException::NOT_FOUND_ERR));
    xdom::fdomexcpt->Set(JS_STR("NOT_SUPPORTED_ERR"),JS_INT((unsigned int)xercesc_3_0::DOMException::NOT_SUPPORTED_ERR));
    xdom::fdomexcpt->Set(JS_STR("INUSE_ATTRIBUTE_ERR"),JS_INT((unsigned int)xercesc_3_0::DOMException::INUSE_ATTRIBUTE_ERR));
    xdom::fdomexcpt->Set(JS_STR("INVALID_STATE_ERR"),JS_INT((unsigned int)xercesc_3_0::DOMException::INVALID_STATE_ERR));
    xdom::fdomexcpt->Set(JS_STR("SYNTAX_ERR"),JS_INT((unsigned int)xercesc_3_0::DOMException::SYNTAX_ERR));
    xdom::fdomexcpt->Set(JS_STR("INVALID_MODIFICATION_ERR"),JS_INT((unsigned int)xercesc_3_0::DOMException::INVALID_MODIFICATION_ERR));
    xdom::fdomexcpt->Set(JS_STR("NAMESPACE_ERR"),JS_INT((unsigned int)xercesc_3_0::DOMException::NAMESPACE_ERR));
    xdom::fdomexcpt->Set(JS_STR("INVALID_ACCESS_ERR"),JS_INT((unsigned int)xercesc_3_0::DOMException::INVALID_ACCESS_ERR));
    xdom::fdomexcpt->Set(JS_STR("VALIDATION_ERR"),JS_INT((unsigned int)xercesc_3_0::DOMException::VALIDATION_ERR));
    xdom::fdomexcpt->Set(JS_STR("TYPE_MISMATCH_ERR"),JS_INT((unsigned int)xercesc_3_0::DOMException::TYPE_MISMATCH_ERR));

    v8::Handle<v8::ObjectTemplate> domexcptt = xdom::fdomexcpt->InstanceTemplate();
    domexcptt->SetInternalFieldCount(1);
    domexcptt->Set(JS_STR("~DOMException"), v8::FunctionTemplate::New(xdom::_domexcpt_destructor));
    /**
     * DOMException property accessors
     */
    domexcptt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMException"));

    v8::Handle<v8::Template> pdomexcpt = xdom::fdomexcpt->PrototypeTemplate();

  // *****						*****
  // *****	END   [[ DOMException ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMLSException ]]		*****
  // *****						*****

    xdom::fdomlsexcpt = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_domlsexcpt));
    xdom::fdomlsexcpt->Inherit(xdom::fdomexcpt);
    xdom::fdomlsexcpt->SetClassName(JS_STR("DOMLSException"));
    xdom::fdomlsexcpt->Set(JS_STR("PARSE_ERR"),JS_INT((unsigned int)xercesc_3_0::DOMLSException::PARSE_ERR));
    xdom::fdomlsexcpt->Set(JS_STR("SERIALIZE_ERR"),JS_INT((unsigned int)xercesc_3_0::DOMLSException::SERIALIZE_ERR));

    v8::Handle<v8::ObjectTemplate> domlsexcptt = xdom::fdomlsexcpt->InstanceTemplate();
    domlsexcptt->SetInternalFieldCount(1);
    domlsexcptt->Set(JS_STR("~DOMLSException"), v8::FunctionTemplate::New(xdom::_domlsexcpt_destructor));
    /**
     * DOMLSException property accessors
     */
    domlsexcptt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMLSException"));

    v8::Handle<v8::Template> pdomlsexcpt = xdom::fdomlsexcpt->PrototypeTemplate();

  // *****						*****
  // *****	END   [[ DOMLSException ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMImplementationList ]]	*****
  // *****						*****

    xdom::fdomlist = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_domlist));
    xdom::fdomlist->SetClassName(JS_STR("DOMImplementationList"));

    v8::Handle<v8::ObjectTemplate> domlistt = xdom::fdomlist->InstanceTemplate();
    domlistt->SetInternalFieldCount(1);
    domlistt->Set(JS_STR("~DOMImplementationList"), v8::FunctionTemplate::New(xdom::_domlist_destructor));
    domlistt->SetAccessor(JS_STR("length"), xdom::get_property);

    v8::Handle<v8::String> fdomlistdata( JS_STR("domlist") );
    domlistt->SetIndexedPropertyHandler(xdom::indexed_property_get, xdom::indexed_property_set, xdom::indexed_property_query, xdom::indexed_property_delete, xdom::indexed_property_enumerate, fdomlistdata);
    /**
     * DOMImplementationList property accessors
     */
    domlistt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMImplementationList"));

    v8::Handle<v8::Template> pdomlist = xdom::fdomlist->PrototypeTemplate();
    pdomlist->Set(JS_STR("item"), v8::FunctionTemplate::New(xdom::_domlistitem));
    pdomlist->Set(JS_STR("getLength"), v8::FunctionTemplate::New(xdom::_domlistgetlength));

  // *****						*****
  // *****	END   [[ DOMImplementationList ]]	*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMImplementationSource ]]	*****
  // *****						*****

    xdom::fdomsource = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_domsource));
    xdom::fdomsource->SetClassName(JS_STR("DOMImplementationSource"));

    v8::Handle<v8::ObjectTemplate> domsourcet = xdom::fdomsource->InstanceTemplate();
    domsourcet->SetInternalFieldCount(1);
    domsourcet->Set(JS_STR("~DOMImplementationSource"), v8::FunctionTemplate::New(xdom::_domsource_destructor));
    /**
     * DOMImplementationSource property accessors
     */
    domsourcet->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMImplementationSource"));

    v8::Handle<v8::Template> pdomsource = xdom::fdomsource->PrototypeTemplate();
    pdomsource->Set(JS_STR("getDOMImplementation"), v8::FunctionTemplate::New(xdom::_domsourcegetdomimplementation));
    pdomsource->Set(JS_STR("getDOMImplementationList"), v8::FunctionTemplate::New(xdom::_domsourcegetdomimplementationlist));

  // *****						*****
  // *****	END   [[ DOMImplementationSource ]]	*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMLocator ]]			*****
  // *****						*****

    xdom::fdomlocator = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_domlocator));
    xdom::fdomlocator->SetClassName(JS_STR("DOMLocator"));

    v8::Handle<v8::ObjectTemplate> domlocatort = xdom::fdomlocator->InstanceTemplate();
    domlocatort->SetInternalFieldCount(1);
    domlocatort->Set(JS_STR("~DOMLocator"), v8::FunctionTemplate::New(xdom::_domlocator_destructor));

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

    v8::Handle<v8::Template> pdomlocator = xdom::fdomlocator->PrototypeTemplate();
    pdomlocator->Set(JS_STR("getLineNumber"), v8::FunctionTemplate::New(xdom::_domlocatorgetlinenumber));
    pdomlocator->Set(JS_STR("getColumnNumber"), v8::FunctionTemplate::New(xdom::_domlocatorgetcolumnnumber));
    pdomlocator->Set(JS_STR("getByteOffset"), v8::FunctionTemplate::New(xdom::_domlocatorgetbyteoffset));
    pdomlocator->Set(JS_STR("getUtf16Offset"), v8::FunctionTemplate::New(xdom::_domlocatorgetutf16offset));
    pdomlocator->Set(JS_STR("getRelatedNode"), v8::FunctionTemplate::New(xdom::_domlocatorgetrelatednode));
    pdomlocator->Set(JS_STR("getURI"), v8::FunctionTemplate::New(xdom::_domlocatorgeturi));
    

  // *****						*****
  // *****	END   [[ DOMLocator ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMImplementationRegistry ]]	*****
  // *****						*****

    xdom::fdomreg = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_domreg));
    xdom::fdomreg->SetClassName(JS_STR("DOMImplementationRegistry"));
    xdom::fdomreg->Set(JS_STR("getDOMImplementation"), v8::FunctionTemplate::New(xdom::_domreggetdomimplementation));
    xdom::fdomreg->Set(JS_STR("getDOMImplementationList"), v8::FunctionTemplate::New(xdom::_domreggetdomimplementationlist));
    xdom::fdomreg->Set(JS_STR("addSource"), v8::FunctionTemplate::New(xdom::_domregaddsource));

    v8::Handle<v8::ObjectTemplate> domregt = xdom::fdomreg->InstanceTemplate();
    domregt->SetInternalFieldCount(1);
    domregt->Set(JS_STR("~DOMImplementationRegistry"), v8::FunctionTemplate::New(xdom::_domreg_destructor));
    /**
     * DOMImplementationRegistry property accessors
     */
    domregt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMImplementationRegistry"));

    v8::Handle<v8::Template> pdomreg = xdom::fdomreg->PrototypeTemplate();

  // *****						*****
  // *****	END   [[ DOMImplementationRegistry ]]	*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMImplementation ]]		*****
  // *****						*****

    //v8::Handle<v8::FunctionTemplate> fdom = v8::FunctionTemplate::New(xdom::_impl) ;
    xdom::fdom = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_impl));
    xdom::fdom->SetClassName(JS_STR("DOMImplementation"));

    v8::Handle<v8::ObjectTemplate> domt = xdom::fdom->InstanceTemplate();
    domt->SetInternalFieldCount(1);
    /**
     * DOMImplementation property accessors
     */
    domt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMImplementation"));
    domt->Set(JS_STR("~DOMImplementation"), v8::FunctionTemplate::New(xdom::_impl_destructor));

    v8::Handle<v8::Template> pt = xdom::fdom->PrototypeTemplate();
    /**
     *	DOMImplementation prototype methods
     */
    pt->Set(JS_STR("getImplementation"), v8::FunctionTemplate::New(xdom::_domgetimplementation));
    pt->Set(JS_STR("loadDOMExceptionMsg"), v8::FunctionTemplate::New(xdom::_domloaddomexceptionmsg));
    pt->Set(JS_STR("hasFeature"), v8::FunctionTemplate::New(xdom::_domhasfeature));
    pt->Set(JS_STR("createDocumentType"), v8::FunctionTemplate::New(xdom::_domcreatedocumenttype));
    pt->Set(JS_STR("createDocType"), v8::FunctionTemplate::New(xdom::_domcreatedocumenttype));
    pt->Set(JS_STR("createDocument"), v8::FunctionTemplate::New(xdom::_domcreatedocument));
    pt->Set(JS_STR("createParser"), v8::FunctionTemplate::New(xdom::_domcreateparser));
    pt->Set(JS_STR("createImplementationLS"), v8::FunctionTemplate::New(xdom::_domcreateimplementationls));


  // *****						*****
  // *****	END   [[ DOMImplementation ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMImplementationLS ]]		*****
  // *****						*****

    //v8::Handle<v8::FunctionTemplate> fdom = v8::FunctionTemplate::New(xdom::_impl) ;
    xdom::fdomls = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_implls));
    xdom::fdomls->Inherit(xdom::fdom);
    xdom::fdomls->SetClassName(JS_STR("DOMImplementationLS"));
    xdom::fdomls->Set(JS_STR("MODE_ASYNCHRONOUS"),JS_INT((unsigned int)xercesc_3_0::DOMImplementationLS::MODE_ASYNCHRONOUS));
    xdom::fdomls->Set(JS_STR("MODE_SYNCHRONOUS"),JS_INT((unsigned int)xercesc_3_0::DOMImplementationLS::MODE_SYNCHRONOUS));

    v8::Handle<v8::ObjectTemplate> domlst = xdom::fdomls->InstanceTemplate();
    domlst->SetInternalFieldCount(1);
    domlst->Set(JS_STR("~DOMImplementationLS"), v8::FunctionTemplate::New(xdom::_implls_destructor));
    /**
     * DOMImplementationLS property accessors
     */
    domlst->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMImplementationLS"));

    v8::Handle<v8::Template> plst = xdom::fdomls->PrototypeTemplate();
    /**
     * DOMImplementationLS prototype methods
     */
    plst->Set(JS_STR("createLSParser"), v8::FunctionTemplate::New(xdom::_impllscreatelsparser));
    plst->Set(JS_STR("createLSSerializer"), v8::FunctionTemplate::New(xdom::_impllscreatelsserializer));
    plst->Set(JS_STR("createLSOutput"), v8::FunctionTemplate::New(xdom::_impllscreatelsoutput));
    plst->Set(JS_STR("createLSInput"), v8::FunctionTemplate::New(xdom::_impllscreatelsinput));

  // *****						*****
  // *****	END   [[ DOMImplementationLS ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMLSParser ]]			*****
  // *****						*****

    // v8::Handle<v8::FunctionTemplate> fparser = v8::FunctionTemplate::New(xdom::_parser);
    xdom::fparser = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_parser));
    xdom::fparser->SetClassName(JS_STR("DOMLSParser"));

    v8::Handle<v8::ObjectTemplate> tparser = xdom::fparser->InstanceTemplate();
    tparser->SetInternalFieldCount(2);
    tparser->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMLSParser"));

    v8::Handle<v8::Template> parsert = xdom::fparser->PrototypeTemplate();

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
    tparser->Set(JS_STR("~DOMLSParser"), v8::FunctionTemplate::New(xdom::_parser_destructor));
    parsert->Set(JS_STR("getDomConfig"), v8::FunctionTemplate::New(xdom::_parsergetdomconfig));
    parsert->Set(JS_STR("getFilter"), v8::FunctionTemplate::New(xdom::_parsergetfilter));
    parsert->Set(JS_STR("getAsync"), v8::FunctionTemplate::New(xdom::_parsergetasync));
    parsert->Set(JS_STR("getBusy"), v8::FunctionTemplate::New(xdom::_parsergetbusy));
    parsert->Set(JS_STR("setFilter"), v8::FunctionTemplate::New(xdom::_parsersetfilter));
    parsert->Set(JS_STR("parse"), v8::FunctionTemplate::New(xdom::_parserparse));
    parsert->Set(JS_STR("parseURI"), v8::FunctionTemplate::New(xdom::_parserparseuri));
    parsert->Set(JS_STR("parseWithContext"), v8::FunctionTemplate::New(xdom::_parserparsewithcontext));
    parsert->Set(JS_STR("abort"), v8::FunctionTemplate::New(xdom::_parserabort));
    parsert->Set(JS_STR("resetDocumentPool"), v8::FunctionTemplate::New(xdom::_parserresetdocumentpool));
    parsert->Set(JS_STR("loadGrammar"), v8::FunctionTemplate::New(xdom::_parserloadgrammar));
    parsert->Set(JS_STR("getGrammar"), v8::FunctionTemplate::New(xdom::_parsergetgrammar));
    parsert->Set(JS_STR("getRootGrammar"), v8::FunctionTemplate::New(xdom::_parsergetrootgrammar));
    parsert->Set(JS_STR("getURIText"), v8::FunctionTemplate::New(xdom::_parsergeturitext));
    parsert->Set(JS_STR("resetCachedGrammarPool"), v8::FunctionTemplate::New(xdom::_parserresetcachedgrammarpool));
    parsert->Set(JS_STR("getSrcOffset"), v8::FunctionTemplate::New(xdom::_parsergetsrcoffset));
    parsert->Set(JS_STR("getImplementation"), v8::FunctionTemplate::New(xdom::_parsergetimplementation));

  // *****						*****
  // *****	END   [[ DOMLSParser ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMNodeFilter ]]		*****
  // *****						*****

    xdom::fnodefilter = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_nodefilter));
    xdom::fnodefilter->SetClassName(JS_STR("DOMNodeFilter"));

    v8::Handle<v8::ObjectTemplate> tnodefilter = xdom::fnodefilter->InstanceTemplate();
    tnodefilter->SetInternalFieldCount(1);
    tnodefilter->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMNodeFilter"));

    v8::Handle<v8::Template> pnodefilter = xdom::fnodefilter->PrototypeTemplate();
    /**
     *	DOMNodeFilter prototype methods
     */
    tnodefilter->Set(JS_STR("~DOMNodeFilter"), v8::FunctionTemplate::New(xdom::_nodefilter_destructor));
    pnodefilter->Set(JS_STR("acceptNode"), v8::FunctionTemplate::New(xdom::_nodefilteracceptnode));

  // *****						*****
  // *****	END   [[ DOMNodeFilter ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMLSParserFilter ]]		*****
  // *****						*****

    xdom::fparserfilter = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_parserfilter));
    xdom::fparserfilter->Inherit(xdom::fnodefilter);
    xdom::fparserfilter->SetClassName(JS_STR("DOMLSParserFilter"));

    v8::Handle<v8::ObjectTemplate> tparserfilter = xdom::fparserfilter->InstanceTemplate();
    tparserfilter->SetInternalFieldCount(1);
    tparserfilter->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMLSParserFilter"));

    v8::Handle<v8::Template> pparserfilter = xdom::fparserfilter->PrototypeTemplate();
    /**
     *	DOMLSParserFilter prototype methods
     */
    tparserfilter->Set(JS_STR("~DOMLSParserFilter"), v8::FunctionTemplate::New(xdom::_parserfilter_destructor));
    pparserfilter->Set(JS_STR("startElement"), v8::FunctionTemplate::New(xdom::_parserfilterstartelement));
    pparserfilter->Set(JS_STR("getWhatToShow"), v8::FunctionTemplate::New(xdom::_parserfiltergetwhattoshow));


  // *****						*****
  // *****	END   [[ DOMLSParserFilter ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMLSSerializer ]]		*****
  // *****						*****

    xdom::fserializer = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_serializer));
    xdom::fserializer->SetClassName(JS_STR("DOMLSSerializer"));

    v8::Handle<v8::ObjectTemplate> tserializer = xdom::fserializer->InstanceTemplate();
    tserializer->SetInternalFieldCount(2);
    tserializer->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMLSSerializer"));
    tserializer->Set(JS_STR("~DOMLSSerializer"), v8::FunctionTemplate::New(xdom::_serializer_destructor));

    v8::Handle<v8::Template> pserializer = xdom::fserializer->PrototypeTemplate();
    pserializer->Set(JS_STR("getDomConfig"), v8::FunctionTemplate::New(xdom::_serializergetdomconfig));
    pserializer->Set(JS_STR("setNewLine"), v8::FunctionTemplate::New(xdom::_serializersetnewline));
    pserializer->Set(JS_STR("setFilter"), v8::FunctionTemplate::New(xdom::_serializersetfilter));
    pserializer->Set(JS_STR("getNewLine"), v8::FunctionTemplate::New(xdom::_serializergetnewline));
    pserializer->Set(JS_STR("getFilter"), v8::FunctionTemplate::New(xdom::_serializergetfilter));
    pserializer->Set(JS_STR("write"), v8::FunctionTemplate::New(xdom::_serializerwrite));
    pserializer->Set(JS_STR("writeToURI"), v8::FunctionTemplate::New(xdom::_serializerwritetouri));
    pserializer->Set(JS_STR("writeToString"), v8::FunctionTemplate::New(xdom::_serializerwritetostring));

  // *****						*****
  // *****	END   [[ DOMLSSerializer ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMLSSerializerFilter ]]	*****
  // *****						*****

    // v8::Handle<v8::FunctionTemplate> fserializerfilter = v8::FunctionTemplate::New(xdom::_serializer);
    xdom::fserializerfilter = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_serializerfilter));
    xdom::fserializerfilter->Inherit(xdom::fnodefilter);
    xdom::fserializerfilter->SetClassName(JS_STR("DOMLSSerializerFilter"));

    v8::Handle<v8::ObjectTemplate> tserializerfilter = xdom::fserializerfilter->InstanceTemplate();
    tserializerfilter->SetInternalFieldCount(1);
    tserializerfilter->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMLSSerializerFilter"));

    v8::Handle<v8::Template> pserializerfilter = xdom::fserializerfilter->PrototypeTemplate();
    /**
     *	DOMLSSerializerFilter prototype methods
     */
    tserializerfilter->Set(JS_STR("~DOMLSSerializerFilter"), v8::FunctionTemplate::New(xdom::_serializerfilter_destructor));
    pserializerfilter->Set(JS_STR("getWhatToShow"), v8::FunctionTemplate::New(xdom::_serializerfiltergetwhattoshow));

  // *****						*****
  // *****	END   [[ DOMLSSerializerFilter ]]	*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMLSInput ]]			*****
  // *****						*****

    xdom::fdomlsinput = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_domlsinput));
    xdom::fdomlsinput->SetClassName(JS_STR("DOMLSInput"));

    v8::Handle<v8::Template> pdomlsinput = xdom::fdomlsinput->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> domlsinputt = xdom::fdomlsinput->InstanceTemplate();
    domlsinputt->SetInternalFieldCount(2);
    domlsinputt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMLSInput"));

    /**
     * DOMLSInput prototype methods
     */
    domlsinputt->Set(JS_STR("~DOMLSInput"), v8::FunctionTemplate::New(xdom::_domlsinput_destructor));
    pdomlsinput->Set(JS_STR("getStringData"), v8::FunctionTemplate::New(xdom::_domlsinputgetstringdata));
    pdomlsinput->Set(JS_STR("getByteStream"), v8::FunctionTemplate::New(xdom::_domlsinputgetbytestream));
    pdomlsinput->Set(JS_STR("getEncoding"), v8::FunctionTemplate::New(xdom::_domlsinputgetencoding));
    pdomlsinput->Set(JS_STR("getPublicId"), v8::FunctionTemplate::New(xdom::_domlsinputgetpublicid));
    pdomlsinput->Set(JS_STR("getSystemId"), v8::FunctionTemplate::New(xdom::_domlsinputgetsystemid));
    pdomlsinput->Set(JS_STR("getBaseURI"), v8::FunctionTemplate::New(xdom::_domlsinputgetbaseuri));
    pdomlsinput->Set(JS_STR("setStringData"), v8::FunctionTemplate::New(xdom::_domlsinputsetstringdata));
    pdomlsinput->Set(JS_STR("setByteStream"), v8::FunctionTemplate::New(xdom::_domlsinputsetbytestream));
    pdomlsinput->Set(JS_STR("setEncoding"), v8::FunctionTemplate::New(xdom::_domlsinputsetencoding));
    pdomlsinput->Set(JS_STR("setPublicId"), v8::FunctionTemplate::New(xdom::_domlsinputsetpublicid));
    pdomlsinput->Set(JS_STR("setSystemId"), v8::FunctionTemplate::New(xdom::_domlsinputsetsystemid));
    pdomlsinput->Set(JS_STR("setBaseURI"), v8::FunctionTemplate::New(xdom::_domlsinputsetbaseuri));
    pdomlsinput->Set(JS_STR("setIssueFatalErrorIfNotFound"), v8::FunctionTemplate::New(xdom::_domlsinputsetissuefatalerrorifnotfound));
    pdomlsinput->Set(JS_STR("getIssueFatalErrorIfNotFound"), v8::FunctionTemplate::New(xdom::_domlsinputgetissuefatalerrorifnotfound));

  // *****						*****
  // *****	END   [[ DOMLSInput ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMLSOutput ]]			*****
  // *****						*****

    xdom::foutput = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_domlsoutput));
    xdom::foutput->SetClassName(JS_STR("DOMLSOutput"));

    v8::Handle<v8::ObjectTemplate> toutput = xdom::foutput->InstanceTemplate();
    toutput->SetInternalFieldCount(2);
    toutput->Set(JS_STR("~DOMLSOutput"), v8::FunctionTemplate::New(xdom::_domlsoutput_destructor));
    toutput->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMLSOutput"));

    v8::Handle<v8::Template> poutput = xdom::foutput->PrototypeTemplate();
    poutput->Set(JS_STR("getByteStream"), v8::FunctionTemplate::New(xdom::_domlsoutputgetbytestream));
    poutput->Set(JS_STR("getEncoding"), v8::FunctionTemplate::New(xdom::_domlsoutputgetencoding));
    poutput->Set(JS_STR("getSystemId"), v8::FunctionTemplate::New(xdom::_domlsoutputgetsystemid));
    poutput->Set(JS_STR("setByteStream"), v8::FunctionTemplate::New(xdom::_domlsoutputsetbytestream));
    poutput->Set(JS_STR("setEncoding"), v8::FunctionTemplate::New(xdom::_domlsoutputsetencoding));
    poutput->Set(JS_STR("setSystemId"), v8::FunctionTemplate::New(xdom::_domlsoutputsetsystemid));

  // *****						*****
  // *****	END   [[ DOMLSOutput ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ XMLFormatTarget ]]		*****
  // *****						*****

/*
    xdom::fformattarget = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_outputtarget));
    xdom::fformattarget->Inherit(xdom::fxmemory);
    xdom::fformattarget->SetClassName(JS_STR("XMLFormatTarget"));

    v8::Handle<v8::ObjectTemplate> tformattarget = xdom::fformattarget->InstanceTemplate();
    tformattarget->SetInternalFieldCount(1);
    tformattarget->Set(JS_STR("~XMLFormatTarget"), v8::FunctionTemplate::New(xdom::_formattarget_destructor));
    tformattarget->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("XMLFormatTarget"));

    v8::Handle<v8::Template> pformattarget = xdom::fformattarget->PrototypeTemplate();
    pformattarget->Set(JS_STR("writeChars"), v8::FunctionTemplate::New(xdom::_formattargetwritechars));
    pformattarget->Set(JS_STR("flush"), v8::FunctionTemplate::New(xdom::_formattargetflush));

*/

  // *****						*****
  // *****	END   [[ XMLFormatTarget ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ LocalFileFormatTarget ]]	*****
  // *****						*****

/*
    xdom::ffiletarget = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_filetarget));
    xdom::ffiletarget->Inherit(xdom::fformattarget);
    xdom::ffiletarget->SetClassName(JS_STR("LocalFileFormatTarget"));

    v8::Handle<v8::ObjectTemplate> tfiletarget = xdom::ffiletarget->InstanceTemplate();
    tfiletarget->SetInternalFieldCount(1);
    tfiletarget->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("LocalFileFormatTarget"));
    tfiletarget->Set(JS_STR("~LocalFileFormatTarget"), v8::FunctionTemplate::New(xdom::_filetarget_destructor));

    v8::Handle<v8::Template> pfiletarget = xdom::ffiletarget->PrototypeTemplate();

*/

  // *****						*****
  // *****	END   [[ LocalFileFormatTarget ]]	*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ MemBufFormatTarget ]]		*****
  // *****						*****

/*
    xdom::fmembuftarget = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_membuftarget));
    xdom::fmembuftarget->Inherit(xdom::fformattarget);
    xdom::fmembuftarget->SetClassName(JS_STR("MemBufFormatTarget"));

    v8::Handle<v8::ObjectTemplate> tmembuftarget = xdom::fmembuftarget->InstanceTemplate();
    tmembuftarget->SetInternalFieldCount(1);
    tmembuftarget->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("MemBufFormatTarget"));
    tmembuftarget->Set(JS_STR("~MemBufFormatTarget"), v8::FunctionTemplate::New(xdom::_membuftarget_destructor));

    v8::Handle<v8::Template> pmembuftarget = xdom::fmembuftarget->PrototypeTemplate();
    pmembuftarget->Set(JS_STR("getRawBuffer"), v8::FunctionTemplate::New(xdom::_membuftargetgetrawbuffer));
    pmembuftarget->Set(JS_STR("getLen"), v8::FunctionTemplate::New(xdom::_membuftargetgetlen));
*/

  // *****						*****
  // *****	END   [[ MemBufFormatTarget ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ StdOutFormatTarget ]]		*****
  // *****						*****

/*
    xdom::fstdouttarget = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_stdouttarget));
    xdom::fstdouttarget->Inherit(xdom::fformattarget);
    xdom::fstdouttarget->SetClassName(JS_STR("StdOutFormatTarget"));

    v8::Handle<v8::ObjectTemplate> tstdouttarget = xdom::fstdouttarget->InstanceTemplate();
    tstdouttarget->SetInternalFieldCount(1);
    t->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("StdOutFormatTarget"));
    tstdouttarget->Set(JS_STR("~StdOutFormatTarget"), v8::FunctionTemplate::New(xdom::_stdouttarget_destructor));

    v8::Handle<v8::Template> pstdouttarget = xdom::fstdouttarget->PrototypeTemplate();
*/

  // *****						*****
  // *****	END   [[ StdOutFormatTarget ]]		*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ DOMStringList ]]		*****
  // *****						*****

    xdom::fstringlist = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_stringlist));
    xdom::fstringlist->SetClassName(JS_STR("DOMStringList"));

    v8::Handle<v8::ObjectTemplate> stringlistt = xdom::fstringlist->InstanceTemplate();
    stringlistt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMStringList"));
    stringlistt->SetInternalFieldCount(1);

    stringlistt->SetAccessor(JS_STR("length"), xdom::get_property);

    v8::Handle<v8::String> fstringlistdata( JS_STR("stringlist") );
    stringlistt->SetIndexedPropertyHandler(xdom::indexed_property_get, xdom::indexed_property_set, xdom::indexed_property_query, xdom::indexed_property_delete, xdom::indexed_property_enumerate, fstringlistdata);
    //stringlistt->SetNamedPropertyHandler(xdom::named_property_get, NULL, xdom::named_property_query, NULL, xdom::named_property_enumerate, fstringlistdata);

    v8::Handle<v8::Template> tstringlist = xdom::fstringlist->PrototypeTemplate();
    //	DOMStringList prototype methods
    stringlistt->Set(JS_STR("~DOMStringList"), v8::FunctionTemplate::New(xdom::_stringlist_destructor));
    tstringlist->Set(JS_STR("item"), v8::FunctionTemplate::New(xdom::_stringlistitem));
    tstringlist->Set(JS_STR("getLength"), v8::FunctionTemplate::New(xdom::_stringlistgetlength));
    tstringlist->Set(JS_STR("contains"), v8::FunctionTemplate::New(xdom::_stringlistcontains));

  // *****						*****
  // *****	END   [[ DOMStringList ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMNamedNodeMap ]]		*****
  // *****						*****

    xdom::fnamednodemap = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_namednodemap));
    xdom::fnamednodemap->SetClassName(JS_STR("DOMNamedNodeMap"));
    v8::Handle<v8::ObjectTemplate> namednodemapt = xdom::fnamednodemap->InstanceTemplate();
    namednodemapt->SetInternalFieldCount(1);
    namednodemapt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMNamedNodeMap"));

    namednodemapt->SetAccessor(JS_STR("length"), xdom::get_property);
    namednodemapt->SetAccessor(JS_STR("Length"), xdom::get_property);

    v8::Handle<v8::String> fnamednodemapdata( JS_STR("namednodemap") );
    namednodemapt->SetIndexedPropertyHandler(xdom::indexed_property_get, xdom::indexed_property_set, xdom::indexed_property_query, xdom::indexed_property_delete, xdom::indexed_property_enumerate, fnamednodemapdata);
    //namednodemapt->SetNamedPropertyHandler(xdom::named_property_get, xdom::named_property_set, xdom::named_property_query, xdom::named_property_delete, xdom::named_property_enumerate, fnamednodemapdata);
    //namednodemapt->SetIndexedPropertyHandler(xdom::indexed_property_get, NULL, xdom::indexed_property_query, NULL, xdom::indexed_property_enumerate, fnamednodemapdata);
    //namednodemapt->SetNamedPropertyHandler(xdom::named_property_get, NULL, xdom::named_property_query, NULL, xdom::named_property_enumerate, fnamednodemapdata);

    v8::Handle<v8::ObjectTemplate> tnamednodemap = xdom::fnamednodemap->PrototypeTemplate();
    //	DOMNamedNodeMap prototype methods
    namednodemapt->Set(JS_STR("~DOMNamedNodeMap"), v8::FunctionTemplate::New(xdom::_namednodemap_destructor));
    tnamednodemap->Set(JS_STR("item"), v8::FunctionTemplate::New(xdom::_nodemapitem));
    tnamednodemap->Set(JS_STR("getLength"), v8::FunctionTemplate::New(xdom::_nodemapgetlength));
    tnamednodemap->Set(JS_STR("getNamedItem"), v8::FunctionTemplate::New(xdom::_nodemapgetnameditem));
    tnamednodemap->Set(JS_STR("getNamedItemNS"), v8::FunctionTemplate::New(xdom::_nodemapgetnameditemns));
    tnamednodemap->Set(JS_STR("setNamedItem"), v8::FunctionTemplate::New(xdom::_nodemapsetnameditem));
    tnamednodemap->Set(JS_STR("setNamedItemNS"), v8::FunctionTemplate::New(xdom::_nodemapsetnameditemns));
    tnamednodemap->Set(JS_STR("removeNamedItem"), v8::FunctionTemplate::New(xdom::_nodemapremovenameditem));
    tnamednodemap->Set(JS_STR("removeNamedItemNS"), v8::FunctionTemplate::New(xdom::_nodemapremovenameditemns));

  // *****						*****
  // *****	END   [[ DOMNamedNodeMap ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMNodeList ]]			*****
  // *****						*****

    xdom::fnodelist = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_nodelist));
    xdom::fnodelist->SetClassName(JS_STR("DOMNodeList"));

    v8::Handle<v8::String> fnodelistdata( JS_STR("nodelist") );

    v8::Handle<v8::ObjectTemplate> nodelistt = xdom::fnodelist->InstanceTemplate();
    nodelistt->SetInternalFieldCount(1);
    nodelistt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMNodeList"));
    nodelistt->SetAccessor(JS_STR("length"), xdom::get_property);
    nodelistt->SetIndexedPropertyHandler(xdom::indexed_property_get, xdom::indexed_property_set, xdom::indexed_property_query, xdom::indexed_property_delete, xdom::indexed_property_enumerate, fnodelistdata);

    v8::Handle<v8::Template> pnodelist = xdom::fnodelist->PrototypeTemplate();
    //	DOMNodeList prototype methods
    nodelistt->Set(JS_STR("~DOMNodeList"), v8::FunctionTemplate::New(xdom::_nodelist_destructor));
    pnodelist->Set(JS_STR("item"), v8::FunctionTemplate::New(xdom::_nodelistitem));
    pnodelist->Set(JS_STR("getLength"), v8::FunctionTemplate::New(xdom::_nodelistgetlength));
    pnodelist->Set(JS_STR("toArray"), v8::FunctionTemplate::New(xdom::_nodelisttoarray));

  // *****						*****
  // *****	END   [[ DOMNodeList ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMUserDataHandler ]]		*****
  // *****						*****

    xdom::fuserdatahandler = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_domuserdatahandler));
    xdom::fuserdatahandler->SetClassName(JS_STR("DOMUserDataHandler"));
    xdom::fuserdatahandler->Set(JS_STR("NODE_CLONED"), JS_INT(xercesc_3_0::DOMUserDataHandler::NODE_CLONED));
    xdom::fuserdatahandler->Set(JS_STR("NODE_IMPORTED"), JS_INT(xercesc_3_0::DOMUserDataHandler::NODE_IMPORTED));
    xdom::fuserdatahandler->Set(JS_STR("NODE_DELETED"), JS_INT(xercesc_3_0::DOMUserDataHandler::NODE_DELETED));
    xdom::fuserdatahandler->Set(JS_STR("NODE_RENAMED"), JS_INT(xercesc_3_0::DOMUserDataHandler::NODE_RENAMED));
    xdom::fuserdatahandler->Set(JS_STR("NODE_ADOPTED"), JS_INT(xercesc_3_0::DOMUserDataHandler::NODE_ADOPTED));

    v8::Handle<v8::ObjectTemplate> userdatahandlert = xdom::fuserdatahandler->InstanceTemplate();
    userdatahandlert->SetInternalFieldCount(2);
    userdatahandlert->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMUserDataHandler"));

    v8::Handle<v8::Template> puserdatahandler = xdom::fuserdatahandler->PrototypeTemplate();

    //	DOMUserDataHandler prototype methods
    userdatahandlert->Set(JS_STR("~DOMUserDataHandler"), v8::FunctionTemplate::New(xdom::_domuserdatahandler_destructor));
    puserdatahandler->Set(JS_STR("handle"), v8::FunctionTemplate::New(xdom::_domuserdatahandlerhandle));

  // *****						*****
  // *****	END   [[ DOMUserDataHandler ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMConfiguration ]]		*****
  // *****						*****

    xdom::fdomconfiguration = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_domconfiguration));
    xdom::fdomconfiguration->SetClassName(JS_STR("DOMConfiguration"));

    v8::Handle<v8::ObjectTemplate> domconfigurationt = xdom::fdomconfiguration->InstanceTemplate();
    domconfigurationt->SetInternalFieldCount(1);
    domconfigurationt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMConfiguration"));
    domconfigurationt->SetAccessor(JS_STR("parameterNames"), xdom::get_property, NULL, JS_STR("DOMConfiguration"));

    /**
     * Static property, useful for stats gathering
     */
    domconfigurationt->Set(JS_STR("childCount"), JS_INT(1));

    v8::Handle<v8::ObjectTemplate> tdomconfiguration = xdom::fdomconfiguration->PrototypeTemplate();

    /**
     * DOM prototype methods (new Document().*)
     */
    domconfigurationt->Set(JS_STR("~DOMConfiguration"), v8::FunctionTemplate::New(xdom::_domconfiguration_destructor));
    tdomconfiguration->Set(JS_STR("getParameter"), v8::FunctionTemplate::New(xdom::_domconfiggetparameter));
    tdomconfiguration->Set(JS_STR("setParameter"), v8::FunctionTemplate::New(xdom::_domconfigsetparameter));
    tdomconfiguration->Set(JS_STR("canSetParameter"), v8::FunctionTemplate::New(xdom::_domconfigcansetparameter));
    tdomconfiguration->Set(JS_STR("getParameterNames"), v8::FunctionTemplate::New(xdom::_domconfiggetparameternames));

  // *****						*****
  // *****	END   [[ DOMConfiguration ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMNode ]]			*****
  // *****						*****

    xdom::fnode = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_domnode));
    xdom::fnode->SetClassName(JS_STR("DOMNode"));

    v8::Handle<v8::ObjectTemplate> nodet( xdom::fnode->InstanceTemplate() );
    nodet->SetInternalFieldCount(1);
    nodet->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMNode"));

    v8::Handle<v8::Template> pnode( xdom::fnode->PrototypeTemplate() );

    /*	*
	*	Emulate enumerated types by setting static property values
	*	for this class on its FunctionTemplate:
	*	(see "http://xerces.apache.org/xerces-c/apiDocs-3/classDOMTypeInfo.html" for enumerated values)
     *	*/
      // "NodeType":
    xdom::fnode->Set(JS_STR("ELEMENT_NODE"), JS_INT(xercesc_3_0::DOMNode::ELEMENT_NODE));
    xdom::fnode->Set(JS_STR("ATTRIBUTE_NODE"), JS_INT(xercesc_3_0::DOMNode::ATTRIBUTE_NODE));
    xdom::fnode->Set(JS_STR("TEXT_NODE"), JS_INT(xercesc_3_0::DOMNode::TEXT_NODE));
    xdom::fnode->Set(JS_STR("CDATA_SECTION_NODE"), JS_INT(xercesc_3_0::DOMNode::CDATA_SECTION_NODE));
    xdom::fnode->Set(JS_STR("ENTITY_REFERENCE_NODE"), JS_INT(xercesc_3_0::DOMNode::ENTITY_REFERENCE_NODE));
    xdom::fnode->Set(JS_STR("ENTITY_NODE"), JS_INT(xercesc_3_0::DOMNode::ENTITY_NODE));
    xdom::fnode->Set(JS_STR("PROCESSING_INSTRUCTION_NODE"), JS_INT(xercesc_3_0::DOMNode::PROCESSING_INSTRUCTION_NODE));
    xdom::fnode->Set(JS_STR("COMMENT_NODE"), JS_INT(xercesc_3_0::DOMNode::COMMENT_NODE));
    xdom::fnode->Set(JS_STR("DOCUMENT_NODE"), JS_INT(xercesc_3_0::DOMNode::DOCUMENT_NODE));
    xdom::fnode->Set(JS_STR("DOCUMENT_TYPE_NODE"), JS_INT(xercesc_3_0::DOMNode::DOCUMENT_TYPE_NODE));
    xdom::fnode->Set(JS_STR("DOCUMENT_FRAGMENT_NODE"), JS_INT(xercesc_3_0::DOMNode::DOCUMENT_FRAGMENT_NODE));
    xdom::fnode->Set(JS_STR("NOTATION_NODE"), JS_INT(xercesc_3_0::DOMNode::NOTATION_NODE));
      // "DocumentPosition":
    xdom::fnode->Set(JS_STR("DOCUMENT_POSITION_DISCONNECTED"), JS_INT(xercesc_3_0::DOMNode::DOCUMENT_POSITION_DISCONNECTED));
    xdom::fnode->Set(JS_STR("DOCUMENT_POSITION_PRECEDING"), JS_INT(xercesc_3_0::DOMNode::DOCUMENT_POSITION_PRECEDING));
    xdom::fnode->Set(JS_STR("DOCUMENT_POSITION_FOLLOWING"), JS_INT(xercesc_3_0::DOMNode::DOCUMENT_POSITION_FOLLOWING));
    xdom::fnode->Set(JS_STR("DOCUMENT_POSITION_CONTAINS"), JS_INT(xercesc_3_0::DOMNode::DOCUMENT_POSITION_CONTAINS));
    xdom::fnode->Set(JS_STR("DOCUMENT_POSITION_CONTAINED_BY"), JS_INT(xercesc_3_0::DOMNode::DOCUMENT_POSITION_CONTAINED_BY));
    xdom::fnode->Set(JS_STR("DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC"), JS_INT(xercesc_3_0::DOMNode::DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC));

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
    nodet->Set(JS_STR("~DOMNode"), v8::FunctionTemplate::New(xdom::_domnode_destructor));
    pnode->Set(JS_STR("serialize"), v8::FunctionTemplate::New(xdom::_nodeserialize));
    pnode->Set(JS_STR("getOuterHTML"), v8::FunctionTemplate::New(xdom::_nodeserialize));
    pnode->Set(JS_STR("getOuterHtml"), v8::FunctionTemplate::New(xdom::_nodeserialize));
    pnode->Set(JS_STR("getOuterXML"), v8::FunctionTemplate::New(xdom::_nodeserialize));
    pnode->Set(JS_STR("getOuterXml"), v8::FunctionTemplate::New(xdom::_nodeserialize));
    pnode->Set(JS_STR("getInnerHTML"), v8::FunctionTemplate::New(xdom::_nodeserializeinner));
    pnode->Set(JS_STR("getInnerHtml"), v8::FunctionTemplate::New(xdom::_nodeserializeinner));
    pnode->Set(JS_STR("getInnerXML"), v8::FunctionTemplate::New(xdom::_nodeserializeinner));
    pnode->Set(JS_STR("getInnerXml"), v8::FunctionTemplate::New(xdom::_nodeserializeinner));
    // pnode->Set(JS_STR("toString"), v8::FunctionTemplate::New(xdom::_nodeserialize));
    pnode->Set(JS_STR("getAsElement"), v8::FunctionTemplate::New(xdom::_nodegetaselement));
    pnode->Set(JS_STR("getNodeName"), v8::FunctionTemplate::New(xdom::_nodegetnodename));
    pnode->Set(JS_STR("getNodeValue"), v8::FunctionTemplate::New(xdom::_nodegetnodevalue));
    pnode->Set(JS_STR("getNodeType"), v8::FunctionTemplate::New(xdom::_nodegetnodetype));
    pnode->Set(JS_STR("getParentNode"), v8::FunctionTemplate::New(xdom::_nodegetparentnode));
    pnode->Set(JS_STR("getChildNodes"), v8::FunctionTemplate::New(xdom::_nodegetchildnodes));
    pnode->Set(JS_STR("getFirstChild"), v8::FunctionTemplate::New(xdom::_nodegetfirstchild));
    pnode->Set(JS_STR("getLastChild"), v8::FunctionTemplate::New(xdom::_nodegetlastchild));
    pnode->Set(JS_STR("getPreviousSibling"), v8::FunctionTemplate::New(xdom::_nodegetprevioussibling));
    pnode->Set(JS_STR("getNextSibling"), v8::FunctionTemplate::New(xdom::_nodegetnextsibling));
    pnode->Set(JS_STR("getAttributes"), v8::FunctionTemplate::New(xdom::_nodegetattributes));
    pnode->Set(JS_STR("getOwnerDocument"), v8::FunctionTemplate::New(xdom::_nodegetownerdocument));
    pnode->Set(JS_STR("getImplementation"), v8::FunctionTemplate::New(xdom::_nodegetownerimplementation));
    pnode->Set(JS_STR("cloneNode"), v8::FunctionTemplate::New(xdom::_nodeclonenode));
    pnode->Set(JS_STR("insertBefore"), v8::FunctionTemplate::New(xdom::_nodeinsertbefore));
    pnode->Set(JS_STR("replaceChild"), v8::FunctionTemplate::New(xdom::_nodereplacechild));
    pnode->Set(JS_STR("removeChild"), v8::FunctionTemplate::New(xdom::_noderemovechild));
    pnode->Set(JS_STR("appendChild"), v8::FunctionTemplate::New(xdom::_nodeappendchild));
    pnode->Set(JS_STR("hasChildNodes"), v8::FunctionTemplate::New(xdom::_nodehaschildnodes));
    pnode->Set(JS_STR("setNodeValue"), v8::FunctionTemplate::New(xdom::_nodesetnodevalue));
    pnode->Set(JS_STR("normalize"), v8::FunctionTemplate::New(xdom::_nodenormalize));
    pnode->Set(JS_STR("isSupported"), v8::FunctionTemplate::New(xdom::_nodeissupported));
    pnode->Set(JS_STR("getNamespaceURI"), v8::FunctionTemplate::New(xdom::_nodegetnamespaceuri));
    pnode->Set(JS_STR("getPrefix"), v8::FunctionTemplate::New(xdom::_nodegetprefix));
    pnode->Set(JS_STR("getLocalName"), v8::FunctionTemplate::New(xdom::_nodegetlocalname));
    pnode->Set(JS_STR("setPrefix"), v8::FunctionTemplate::New(xdom::_nodesetprefix));
    pnode->Set(JS_STR("hasAttributes"), v8::FunctionTemplate::New(xdom::_nodehasattributes));
    pnode->Set(JS_STR("isSameNode"), v8::FunctionTemplate::New(xdom::_nodeissamenode));
    pnode->Set(JS_STR("isEqualNode"), v8::FunctionTemplate::New(xdom::_nodeisequalnode));
    pnode->Set(JS_STR("setUserData"), v8::FunctionTemplate::New(xdom::_nodesetuserdata));
    pnode->Set(JS_STR("getUserData"), v8::FunctionTemplate::New(xdom::_nodegetuserdata));
    pnode->Set(JS_STR("getBaseURI"), v8::FunctionTemplate::New(xdom::_nodegetbaseuri));
    pnode->Set(JS_STR("compareDocumentPosition"), v8::FunctionTemplate::New(xdom::_nodecomparedocumentposition));
    pnode->Set(JS_STR("getTextContent"), v8::FunctionTemplate::New(xdom::_nodegettextcontent));
    pnode->Set(JS_STR("setTextContent"), v8::FunctionTemplate::New(xdom::_nodesettextcontent));
    pnode->Set(JS_STR("lookupPrefix"), v8::FunctionTemplate::New(xdom::_nodelookupprefix));
    pnode->Set(JS_STR("isDefaultNamespace"), v8::FunctionTemplate::New(xdom::_nodeisdefaultnamespace));
    pnode->Set(JS_STR("lookupNamespaceURI"), v8::FunctionTemplate::New(xdom::_nodelookupnamespaceuri));
    pnode->Set(JS_STR("getFeature"), v8::FunctionTemplate::New(xdom::_nodegetfeature));

  // *****						*****
  // *****	END   [[ DOMNode ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMDocumentType ]]		*****
  // *****						*****

    xdom::fdocumenttype = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_documenttype));
    xdom::fdocumenttype->Inherit(xdom::fnode);
    xdom::fdocumenttype->SetClassName(JS_STR("DOMDocumentType"));

    v8::Handle<v8::Template> pdocumenttype = xdom::fdocumenttype->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> documenttypet = xdom::fdocumenttype->InstanceTemplate();
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
    documenttypet->Set(JS_STR("~DOMDocumentType"), v8::FunctionTemplate::New(xdom::_documenttype_destructor));
    pdocumenttype->Set(JS_STR("getName"), v8::FunctionTemplate::New(xdom::_dtgetname));
    pdocumenttype->Set(JS_STR("getEntities"), v8::FunctionTemplate::New(xdom::_dtgetentities));
    pdocumenttype->Set(JS_STR("getNotations"), v8::FunctionTemplate::New(xdom::_dtgetnotations));
    pdocumenttype->Set(JS_STR("getPublicId"), v8::FunctionTemplate::New(xdom::_dtgetpublicid));
    pdocumenttype->Set(JS_STR("getSystemId"), v8::FunctionTemplate::New(xdom::_dtgetsystemid));
    pdocumenttype->Set(JS_STR("getInternalSubset"), v8::FunctionTemplate::New(xdom::_dtgetinternalsubset));

  // *****						*****
  // *****	END   [[ DOMDocumentType ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMDocument ]]			*****
  // *****						*****

    xdom::fdocument = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_document));
    xdom::fdocument->Inherit(xdom::fnode);
    xdom::fdocument->SetClassName(JS_STR("DOMDocument"));

    v8::Handle<v8::ObjectTemplate> documentt = xdom::fdocument->InstanceTemplate();
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

    v8::Handle<v8::Template> pdocument = xdom::fdocument->PrototypeTemplate();

    /**
     * Document prototype methods
     */
    documentt->Set(JS_STR("~DOMDocument"), v8::FunctionTemplate::New(xdom::_document_destructor));
    // pdocument->Set(JS_STR("toString"), v8::FunctionTemplate::New(xdom::_documentserialize));
    pdocument->Set(JS_STR("serialize"), v8::FunctionTemplate::New(xdom::_documentserialize));
    pdocument->Set(JS_STR("createLSSerializer"), v8::FunctionTemplate::New(xdom::_documentcreatelsserializer));
    pdocument->Set(JS_STR("createLSOutput"), v8::FunctionTemplate::New(xdom::_documentcreatelsoutput));
    pdocument->Set(JS_STR("createNode"), v8::FunctionTemplate::New(xdom::_documentcreatenode));
    pdocument->Set(JS_STR("createElement"), v8::FunctionTemplate::New(xdom::_documentcreateelement));
    pdocument->Set(JS_STR("createDocumentFragment"), v8::FunctionTemplate::New(xdom::_documentcreatedocumentfragment));
    pdocument->Set(JS_STR("createTextNode"), v8::FunctionTemplate::New(xdom::_documentcreatetextnode));
    pdocument->Set(JS_STR("createComment"), v8::FunctionTemplate::New(xdom::_documentcreatecomment));
    pdocument->Set(JS_STR("createCDATASection"), v8::FunctionTemplate::New(xdom::_documentcreatecdatasection));
    pdocument->Set(JS_STR("createProcessingInstruction"), v8::FunctionTemplate::New(xdom::_documentcreateprocessinginstruction));
    pdocument->Set(JS_STR("createAttribute"), v8::FunctionTemplate::New(xdom::_documentcreateattribute));
    pdocument->Set(JS_STR("createEntityReference"), v8::FunctionTemplate::New(xdom::_documentcreateentityreference));
    pdocument->Set(JS_STR("getDocType"), v8::FunctionTemplate::New(xdom::_documentgetdoctype));
    pdocument->Set(JS_STR("getImplementation"), v8::FunctionTemplate::New(xdom::_documentgetimplementation));
    pdocument->Set(JS_STR("getDocumentElement"), v8::FunctionTemplate::New(xdom::_documentgetdocumentelement));
    pdocument->Set(JS_STR("getElementsByTagName"), v8::FunctionTemplate::New(xdom::_documentgetelementsbytagname));
    pdocument->Set(JS_STR("importNode"), v8::FunctionTemplate::New(xdom::_documentimportnode));
    pdocument->Set(JS_STR("createElementNS"), v8::FunctionTemplate::New(xdom::_documentcreateelementns));
    pdocument->Set(JS_STR("createAttributeNS"), v8::FunctionTemplate::New(xdom::_documentcreateattributens));
    pdocument->Set(JS_STR("getElementsByTagNameNS"), v8::FunctionTemplate::New(xdom::_documentgetelementsbytagnamens));
    pdocument->Set(JS_STR("getElementById"), v8::FunctionTemplate::New(xdom::_documentgetelementbyid));
    pdocument->Set(JS_STR("getInputEncoding"), v8::FunctionTemplate::New(xdom::_documentgetinputencoding));
    pdocument->Set(JS_STR("getXmlEncoding"), v8::FunctionTemplate::New(xdom::_documentgetxmlencoding));
    pdocument->Set(JS_STR("getXmlStandalone"), v8::FunctionTemplate::New(xdom::_documentgetxmlstandalone));
    pdocument->Set(JS_STR("setXmlStandalone"), v8::FunctionTemplate::New(xdom::_documentsetxmlstandalone));
    pdocument->Set(JS_STR("getXmlVersion"), v8::FunctionTemplate::New(xdom::_documentgetxmlversion));
    pdocument->Set(JS_STR("setXmlVersion"), v8::FunctionTemplate::New(xdom::_documentsetxmlversion));
    pdocument->Set(JS_STR("getDocumentURI"), v8::FunctionTemplate::New(xdom::_documentgetdocumenturi));
    pdocument->Set(JS_STR("setDocumentURI"), v8::FunctionTemplate::New(xdom::_documentsetdocumenturi));
    pdocument->Set(JS_STR("getStrictErrorChecking"), v8::FunctionTemplate::New(xdom::_documentgetstricterrorchecking));
    pdocument->Set(JS_STR("setStrictErrorChecking"), v8::FunctionTemplate::New(xdom::_documentsetstricterrorchecking));
    pdocument->Set(JS_STR("renameNode"), v8::FunctionTemplate::New(xdom::_documentrenamenode));
    pdocument->Set(JS_STR("adoptNode"), v8::FunctionTemplate::New(xdom::_documentadoptnode));
    pdocument->Set(JS_STR("normalizeDocument"), v8::FunctionTemplate::New(xdom::_documentnormalizedocument));
    pdocument->Set(JS_STR("getDOMConfig"), v8::FunctionTemplate::New(xdom::_documentgetdomconfig));

  // *****						*****
  // *****	END   [[ DOMDocument ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMAttr ]]			*****
  // *****						*****

    xdom::fattribute = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_attribute));
    xdom::fattribute->Inherit(xdom::fnode);
    xdom::fattribute->SetClassName(JS_STR("DOMAttr"));

    v8::Handle<v8::ObjectTemplate> attributet = xdom::fattribute->InstanceTemplate();
    attributet->SetInternalFieldCount(1); /* id, ... */
    attributet->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMAttr"));

    attributet->SetAccessor(JS_STR("value"), xdom::get_property, xdom::set_property);
    attributet->SetAccessor(JS_STR("name"), xdom::get_property);
    attributet->SetAccessor(JS_STR("specified"), xdom::get_property);
    attributet->SetAccessor(JS_STR("ownerElement"), xdom::get_property);
    attributet->SetAccessor(JS_STR("schemaTypeInfo"), xdom::get_property);

    v8::Handle<v8::Template> pattribute = xdom::fattribute->PrototypeTemplate();

    /**
     * Attribute prototype methods
     */
    attributet->Set(JS_STR("~DOMAttr"), v8::FunctionTemplate::New(xdom::_attribute_destructor));
    pattribute->Set(JS_STR("getName"), v8::FunctionTemplate::New(xdom::_attributegetname));
    pattribute->Set(JS_STR("getSpecified"), v8::FunctionTemplate::New(xdom::_attributegetspecified));
    pattribute->Set(JS_STR("getValue"), v8::FunctionTemplate::New(xdom::_attributegetvalue));
    pattribute->Set(JS_STR("setValue"), v8::FunctionTemplate::New(xdom::_attributesetvalue));
    pattribute->Set(JS_STR("valueOf"), v8::FunctionTemplate::New(xdom::_attributegetvalue));
    pattribute->Set(JS_STR("ValueOf"), v8::FunctionTemplate::New(xdom::_attributegetvalue));
    pattribute->Set(JS_STR("toString"), v8::FunctionTemplate::New(xdom::_attributegetvalue));
    pattribute->Set(JS_STR("ToString"), v8::FunctionTemplate::New(xdom::_attributegetvalue));
    pattribute->Set(JS_STR("getOwnerElement"), v8::FunctionTemplate::New(xdom::_attributegetownerelement));
    pattribute->Set(JS_STR("isId"), v8::FunctionTemplate::New(xdom::_attributeisid));
    pattribute->Set(JS_STR("getSchemaTypeInfo"), v8::FunctionTemplate::New(xdom::_attributegetschematypeinfo));

  // *****						*****
  // *****	END   [[ DOMAttr ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ PreElement ]]			*****
  // *****						*****

    xdom::fpreelement = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_preelement));
    xdom::fpreelement->Inherit(xdom::fnode);
    xdom::fpreelement->SetClassName(JS_STR("PreElement"));

    v8::Handle<v8::ObjectTemplate> preelementt = xdom::fpreelement->InstanceTemplate();
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

    v8::Handle<v8::Template> ppreelement = xdom::fpreelement->PrototypeTemplate();

    /**
     * PreElement prototype methods
     */
    preelementt->Set(JS_STR("~PreElement"), v8::FunctionTemplate::New(xdom::_preelement_destructor));
    //ppreelement->Set(JS_STR("toString"), v8::FunctionTemplate::New(xdom::_nodeserialize));
    ppreelement->Set(JS_STR("getAsNode"), v8::FunctionTemplate::New(xdom::_elementgetasnode));
    ppreelement->Set(JS_STR("setAttribute"), v8::FunctionTemplate::New(xdom::_elementsetattribute));
    ppreelement->Set(JS_STR("setAttributeNS"), v8::FunctionTemplate::New(xdom::_elementsetattributens));
    ppreelement->Set(JS_STR("setAttributeNode"), v8::FunctionTemplate::New(xdom::_elementsetattributenode));
    ppreelement->Set(JS_STR("setAttributeNodeNS"), v8::FunctionTemplate::New(xdom::_elementsetattributenodens));
    ppreelement->Set(JS_STR("getTagName"), v8::FunctionTemplate::New(xdom::_elementgettagname));
    ppreelement->Set(JS_STR("getAttribute"), v8::FunctionTemplate::New(xdom::_elementgetattribute));
    ppreelement->Set(JS_STR("getAttributeNode"), v8::FunctionTemplate::New(xdom::_elementgetattributenode));
    ppreelement->Set(JS_STR("getElementsByTagName"), v8::FunctionTemplate::New(xdom::_elementgetelementsbytagname));
    ppreelement->Set(JS_STR("removeAttribute"), v8::FunctionTemplate::New(xdom::_elementremoveattribute));
    ppreelement->Set(JS_STR("removeAttributeNode"), v8::FunctionTemplate::New(xdom::_elementremoveattributenode));
    ppreelement->Set(JS_STR("getAttributeNS"), v8::FunctionTemplate::New(xdom::_elementgetattributens));
    ppreelement->Set(JS_STR("removeAttributeNS"), v8::FunctionTemplate::New(xdom::_elementremoveattributens));
    ppreelement->Set(JS_STR("getAttributeNodeNS"), v8::FunctionTemplate::New(xdom::_elementgetattributenodens));
    ppreelement->Set(JS_STR("getElementsByTagNameNS"), v8::FunctionTemplate::New(xdom::_elementgetelementsbytagnamens));
    ppreelement->Set(JS_STR("hasAttribute"), v8::FunctionTemplate::New(xdom::_elementhasattribute));
    ppreelement->Set(JS_STR("hasAttributeNS"), v8::FunctionTemplate::New(xdom::_elementhasattributens));
    ppreelement->Set(JS_STR("setIdAttribute"), v8::FunctionTemplate::New(xdom::_elementsetidattribute));
    ppreelement->Set(JS_STR("setIdAttributeNS"), v8::FunctionTemplate::New(xdom::_elementsetidattributens));
    ppreelement->Set(JS_STR("setIdAttributeNode"), v8::FunctionTemplate::New(xdom::_elementsetidattributenode));
    ppreelement->Set(JS_STR("getSchemaTypeInfo"), v8::FunctionTemplate::New(xdom::_elementgetschematypeinfo));

  // *****						*****
  // *****	END   [[ PreElement ]]			*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ DOMElement ]]			*****
  // *****						*****

    xdom::felement = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_element));
    xdom::felement->Inherit(xdom::fpreelement);
    xdom::felement->SetClassName(JS_STR("DOMElement"));

    v8::Handle<v8::ObjectTemplate> elementt = xdom::felement->InstanceTemplate();
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
    //elementt->SetNamedPropertyHandler(xdom::named_property_get, xdom::named_property_set, xdom::named_property_query, xdom::named_property_delete, xdom::named_property_enumerate, felementdata);

    v8::Handle<v8::Template> pelement = xdom::felement->PrototypeTemplate();

    /**
     * Element prototype methods
     */
    elementt->Set(JS_STR("~DOMElement"), v8::FunctionTemplate::New(xdom::_element_destructor));

  // *****						*****
  // *****	END   [[ DOMElement ]]			*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ CDATA ]]			*****
  // *****						*****

    xdom::fcdata = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_cdata));
    xdom::fcdata->Inherit(xdom::fnode);
    xdom::fcdata->SetClassName(JS_STR("DOMCharacterData"));

    v8::Handle<v8::Template> pcdata = xdom::fcdata->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> cdatat = xdom::fcdata->InstanceTemplate();
    cdatat->SetInternalFieldCount(1); /* id, ... */
    cdatat->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMCharacterData"));
    cdatat->SetAccessor(JS_STR("data"), xdom::get_property, xdom::set_property);
    cdatat->SetAccessor(JS_STR("length"), xdom::get_property);

    /**
     * CharacterData prototype methods
     */
    cdatat->Set(JS_STR("~DOMCharacterData"), v8::FunctionTemplate::New(xdom::_cdata_destructor));
    pcdata->Set(JS_STR("getData"), v8::FunctionTemplate::New(xdom::_cdatagetdata));
    pcdata->Set(JS_STR("getLength"), v8::FunctionTemplate::New(xdom::_cdatagetlength));
    pcdata->Set(JS_STR("substringData"), v8::FunctionTemplate::New(xdom::_cdatasubstringdata));
    pcdata->Set(JS_STR("appendData"), v8::FunctionTemplate::New(xdom::_cdataappenddata));
    pcdata->Set(JS_STR("insertData"), v8::FunctionTemplate::New(xdom::_cdatainsertdata));
    pcdata->Set(JS_STR("deleteData"), v8::FunctionTemplate::New(xdom::_cdatadeletedata));
    pcdata->Set(JS_STR("replaceData"), v8::FunctionTemplate::New(xdom::_cdatareplacedata));
    pcdata->Set(JS_STR("setData"), v8::FunctionTemplate::New(xdom::_cdatasetdata));

  // *****						*****
  // *****	END   [[ CDATA ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ Text ]]			*****
  // *****						*****

    xdom::ftext = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_text));
    xdom::ftext->Inherit(xdom::fcdata);
    xdom::ftext->SetClassName(JS_STR("DOMText"));

    v8::Handle<v8::Template> ptextnode = xdom::ftext->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> textnodet = xdom::ftext->InstanceTemplate();
    textnodet->SetInternalFieldCount(1); /* id, ... */
    textnodet->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMText"));

    /**
     * Text prototype methods
     */
    textnodet->Set(JS_STR("~DOMText"), v8::FunctionTemplate::New(xdom::_text_destructor));
    ptextnode->Set(JS_STR("splitText"), v8::FunctionTemplate::New(xdom::_textsplittext));
    ptextnode->Set(JS_STR("getIsElementContentWhitespace"), v8::FunctionTemplate::New(xdom::_textgetiselementcontentwhitespace));
    ptextnode->Set(JS_STR("getWholeText"), v8::FunctionTemplate::New(xdom::_textgetwholetext));
    ptextnode->Set(JS_STR("replaceWholeText"), v8::FunctionTemplate::New(xdom::_textreplacewholetext));
    ptextnode->Set(JS_STR("isIgnorableWhitespace"), v8::FunctionTemplate::New(xdom::_textisignorablewhitespace));

  // *****						*****
  // *****	END   [[ Text ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ CDATASection ]]		*****
  // *****						*****

    xdom::fcdatasection = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_cdatasection));
    xdom::fcdatasection->Inherit(xdom::ftext);
    xdom::fcdatasection->SetClassName(JS_STR("DOMCDATASection"));

    v8::Handle<v8::ObjectTemplate> cdatasectiont = xdom::fcdatasection->InstanceTemplate();
    cdatasectiont->SetInternalFieldCount(1);
    cdatasectiont->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMCDATASection"));

    /**
     * CDATASection prototype methods
     */
    cdatasectiont->Set(JS_STR("~DOMCDATASection"), v8::FunctionTemplate::New(xdom::_cdatasection_destructor));

  // *****						*****
  // *****	END   [[ CDATASection ]]		*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ Comment ]]			*****
  // *****						*****

    xdom::fcomment = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_comment));
    xdom::fcomment->Inherit(xdom::fcdata);
    xdom::fcomment->SetClassName(JS_STR("DOMComment"));

    v8::Handle<v8::ObjectTemplate> commentt = xdom::fcomment->InstanceTemplate();
    commentt->SetInternalFieldCount(1);
    commentt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMComment"));

    /**
     * Comment prototype methods
     */
    commentt->Set(JS_STR("~DOMComment"), v8::FunctionTemplate::New(xdom::_comment_destructor));

  // *****						*****
  // *****	END   [[ Comment ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ Entity ]]			*****
  // *****						*****

    xdom::fentity = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_entity));
    xdom::fentity->Inherit(xdom::fnode);
    xdom::fentity->SetClassName(JS_STR("DOMEntity"));

    v8::Handle<v8::Template> pentity = xdom::fentity->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> entityt = xdom::fentity->InstanceTemplate();
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
    entityt->Set(JS_STR("~DOMEntity"), v8::FunctionTemplate::New(xdom::_entity_destructor));
    pentity->Set(JS_STR("getPublicId"), v8::FunctionTemplate::New(xdom::_entitygetpublicid));
    pentity->Set(JS_STR("getSystemId"), v8::FunctionTemplate::New(xdom::_entitygetsystemid));
    pentity->Set(JS_STR("getNotationName"), v8::FunctionTemplate::New(xdom::_entitygetnotationname));
    pentity->Set(JS_STR("getInputEncoding"), v8::FunctionTemplate::New(xdom::_entitygetinputencoding));
    pentity->Set(JS_STR("getXmlEncoding"), v8::FunctionTemplate::New(xdom::_entitygetxmlencoding));
    pentity->Set(JS_STR("getXmlVersion"), v8::FunctionTemplate::New(xdom::_entitygetxmlversion));

  // *****						*****
  // *****	END   [[ Entity ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ EntityReference ]]		*****
  // *****						*****

    xdom::fentityreference = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_entityreference));
    xdom::fentityreference->Inherit(xdom::fnode);
    xdom::fentityreference->SetClassName(JS_STR("DOMEntityReference"));

    v8::Handle<v8::ObjectTemplate> entityreferencet = xdom::fentityreference->InstanceTemplate();
    entityreferencet->SetInternalFieldCount(1); /* id, ... */
    entityreferencet->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMEntityReference"));

    /**
     * EntityReference prototype methods
     */
    entityreferencet->Set(JS_STR("~DOMEntityReference"), v8::FunctionTemplate::New(xdom::_entityreference_destructor));

  // *****						*****
  // *****	END   [[ EntityReference ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMProcessingInstruction ]]	*****
  // *****						*****

    xdom::fprocessinginstruction = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_processinginstruction));
    xdom::fprocessinginstruction->Inherit(xdom::fnode);
    xdom::fprocessinginstruction->SetClassName(JS_STR("DOMProcessingInstruction"));

    v8::Handle<v8::ObjectTemplate> processinginstructiont = xdom::fprocessinginstruction->InstanceTemplate();
    processinginstructiont->SetInternalFieldCount(1); /* id, ... */
    processinginstructiont->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMProcessingInstruction"));
    processinginstructiont->SetAccessor(JS_STR("target"),xdom::get_property);
    processinginstructiont->SetAccessor(JS_STR("data"),xdom::get_property,xdom::set_property);

    v8::Handle<v8::Template> pprocessinginstruction = xdom::fprocessinginstruction->PrototypeTemplate();

    /**
     * ProcessingInstruction prototype methods
     */
    processinginstructiont->Set(JS_STR("~DOMProcessingInstruction"), v8::FunctionTemplate::New(xdom::_processinginstruction_destructor));
    pprocessinginstruction->Set(JS_STR("getData"), v8::FunctionTemplate::New(xdom::_processinginstructiongetdata));
    pprocessinginstruction->Set(JS_STR("setData"), v8::FunctionTemplate::New(xdom::_processinginstructionsetdata));
    pprocessinginstruction->Set(JS_STR("getTarget"), v8::FunctionTemplate::New(xdom::_processinginstructiongettarget));

  // *****						*****
  // *****	END   [[ DOMProcessingInstruction ]]	*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ DOMNotation ]]			*****
  // *****						*****

    xdom::fnotation = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_notation));
    xdom::fnotation->Inherit(xdom::fnode);
    xdom::fnotation->SetClassName(JS_STR("DOMNotation"));

    v8::Handle<v8::ObjectTemplate> notationt = xdom::fnotation->InstanceTemplate();
    notationt->SetInternalFieldCount(1); /* id, ... */
    notationt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMNotation"));
    notationt->SetAccessor(JS_STR("publicId"),xdom::get_property);
    notationt->SetAccessor(JS_STR("systemId"),xdom::get_property);

    v8::Handle<v8::Template> pnotation = xdom::fnotation->PrototypeTemplate();

    /**
     *	DOMNotation prototype methods
     */
    notationt->Set(JS_STR("~DOMNotation"), v8::FunctionTemplate::New(xdom::_notation_destructor));
    pnotation->Set(JS_STR("getPublicId"), v8::FunctionTemplate::New(xdom::_notationgetpublicid));
    pnotation->Set(JS_STR("getSystemId"), v8::FunctionTemplate::New(xdom::_notationgetsystemid));

  // *****						*****
  // *****	END   [[ DOMNotation ]]			*****
  // ********************************************************


  // ********************************************************
  // *****	BEGIN [[ Buffer ]]			*****
  // *****						*****

    xdom::fbuffer = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_buffer));
    xdom::fbuffer->SetClassName(JS_STR("Buffer"));

    v8::Handle<v8::Template> pbuffer = xdom::fbuffer->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> buffert = xdom::fbuffer->InstanceTemplate();
    buffert->SetInternalFieldCount(2);
    buffert->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("Buffer"));

    /**
     * Buffer prototype methods
     */
    buffert->Set(JS_STR("~Buffer"), v8::FunctionTemplate::New(xdom::_buffer_destructor));

  // *****						*****
  // *****	END   [[ Buffer ]]			*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ MemoryManager ]]			*****
  // *****						*****

    xdom::fmemorymanager = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_memorymanager));
    xdom::fmemorymanager->SetClassName(JS_STR("MemoryManager"));

    v8::Handle<v8::Template> pmemorymanager = xdom::fmemorymanager->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> memorymanagert = xdom::fmemorymanager->InstanceTemplate();
    memorymanagert->SetInternalFieldCount(1);
    memorymanagert->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("MemoryManager"));

    /**
     * MemoryManager prototype methods
     */
    memorymanagert->Set(JS_STR("~MemoryManager"), v8::FunctionTemplate::New(xdom::_memorymanager_destructor));
    pmemorymanager->Set(JS_STR("getExceptionMemoryManager"), v8::FunctionTemplate::New(xdom::_memorymanagergetexceptionmemorymanager));
    pmemorymanager->Set(JS_STR("allocate"), v8::FunctionTemplate::New(xdom::_memorymanagerallocate));
    pmemorymanager->Set(JS_STR("deallocate"), v8::FunctionTemplate::New(xdom::_memorymanagerdeallocate));

  // *****						*****
  // *****	END   [[ MemoryManager ]]			*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ DOMMemoryManager ]]		*****
  // *****						*****

    xdom::fdommemorymanager = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_dommemorymanager));
    xdom::fdommemorymanager->SetClassName(JS_STR("DOMMemoryManager"));

    v8::Handle<v8::Template> pdommemorymanager = xdom::fdommemorymanager->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> dommemorymanagert = xdom::fdommemorymanager->InstanceTemplate();
    dommemorymanagert->SetInternalFieldCount(1);
    dommemorymanagert->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMMemoryManager"));

    /**
     *	DOMMemoryManager prototype methods
     */
    dommemorymanagert->Set(JS_STR("~DOMMemoryManager"), v8::FunctionTemplate::New(xdom::_dommemorymanager_destructor));
    pdommemorymanager->Set(JS_STR("getMemoryAllocationBlockSize"), v8::FunctionTemplate::New(xdom::_dommemorymanagergetmemoryallocationblocksize));
    pdommemorymanager->Set(JS_STR("setMemoryAllocationBlockSize"), v8::FunctionTemplate::New(xdom::_dommemorymanagersetmemoryallocationblocksize));
    pdommemorymanager->Set(JS_STR("allocate"), v8::FunctionTemplate::New(xdom::_dommemorymanagerallocate));
//    pdommemorymanager->Set(JS_STR("release"), v8::FunctionTemplate::New(xdom::_dommemorymanagerrelease));
    pdommemorymanager->Set(JS_STR("cloneString"), v8::FunctionTemplate::New(xdom::_dommemorymanagerclonestring));

  // *****						*****
  // *****	END   [[ DOMMemoryManager ]]		*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ XMemory ]]			*****
  // *****						*****

    xdom::fxmemory = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_xmemory));
    xdom::fxmemory->SetClassName(JS_STR("XMemory"));

    v8::Handle<v8::Template> pxmemory = xdom::fxmemory->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> xmemoryt = xdom::fxmemory->InstanceTemplate();
    xmemoryt->SetInternalFieldCount(1);
    xmemoryt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("XMemory"));

    /**
     * XMemory prototype methods
     */
    xmemoryt->Set(JS_STR("~XMemory"), v8::FunctionTemplate::New(xdom::_xmemory_destructor));
    pxmemory->Set(JS_STR("New"), v8::FunctionTemplate::New(xdom::_xmemorynew));
    pxmemory->Set(JS_STR("Delete"), v8::FunctionTemplate::New(xdom::_xmemorydelete));

  // *****						*****
  // *****	END   [[ XMemory ]]			*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ BinInputStream ]]		*****
  // *****						*****

    xdom::fbininput = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_bininput));
    xdom::fbininput->Inherit(xdom::fxmemory);
    xdom::fbininput->SetClassName(JS_STR("BinInputStream"));

    v8::Handle<v8::Template> pbininputstream = xdom::fbininput->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> bininputstreamt = xdom::fbininput->InstanceTemplate();
    bininputstreamt->SetInternalFieldCount(1);
    bininputstreamt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("BinInputStream"));

    /**
     * BinInputStream prototype methods
     */
    bininputstreamt->Set(JS_STR("~BinInputStream"), v8::FunctionTemplate::New(xdom::_bininput_destructor));

  // *****						*****
  // *****	END   [[ BinInputStream ]]		*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ BinFileInputStream ]]		*****
  // *****						*****

    xdom::fbinfileinput = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_binfileinput));
    xdom::fbinfileinput->Inherit(xdom::fbininput);
    xdom::fbinfileinput->SetClassName(JS_STR("BinFileInputStream"));

    v8::Handle<v8::Template> pbinfileinput = xdom::fbinfileinput->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> binfileinputt = xdom::fbinfileinput->InstanceTemplate();
    binfileinputt->SetInternalFieldCount(1);
    binfileinputt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("BinFileInputStream"));

    /**
     * BinFileInputStream prototype methods
     */
    binfileinputt->Set(JS_STR("~BinFileInputStream"), v8::FunctionTemplate::New(xdom::_binfileinput_destructor));

  // *****						*****
  // *****	END   [[ BinFileInputStream ]]			*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ BinMemInputStream ]]		*****
  // *****						*****

    xdom::fbinmeminput = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_binmeminputstream));
    xdom::fbinmeminput->Inherit(xdom::fbininput);
    xdom::fbinmeminput->SetClassName(JS_STR("BinMemInputStream"));

    v8::Handle<v8::Template> pbinmeminputstream = xdom::fbinmeminput->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> binmeminputstreamt = xdom::fbinmeminput->InstanceTemplate();
    binmeminputstreamt->SetInternalFieldCount(1);
    binmeminputstreamt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("BinMemInputStream"));

    /**
     * BinMemInputStream prototype methods
     */
    binmeminputstreamt->Set(JS_STR("~BinMemInputStream"), v8::FunctionTemplate::New(xdom::_binmeminputstream_destructor));

  // *****						*****
  // *****	END   [[ BinMemInputStream ]]			*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ InputSource ]]			*****
  // *****						*****

    xdom::finputsource = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_inputsource));
    xdom::finputsource->Inherit(xdom::fxmemory);
    xdom::finputsource->SetClassName(JS_STR("InputSource"));

    v8::Handle<v8::Template> pinputsource = xdom::finputsource->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> inputsourcet = xdom::finputsource->InstanceTemplate();
    inputsourcet->SetInternalFieldCount(1);
    inputsourcet->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("InputSource"));

    /**
     * InputSource prototype methods
     */
    inputsourcet->Set(JS_STR("~InputSource"), v8::FunctionTemplate::New(xdom::_inputsource_destructor));
    pinputsource->Set(JS_STR("makeStream"), v8::FunctionTemplate::New(xdom::_inputsourcemakestream));
    pinputsource->Set(JS_STR("getEncoding"), v8::FunctionTemplate::New(xdom::_inputsourcegetencoding));
    pinputsource->Set(JS_STR("getPublicId"), v8::FunctionTemplate::New(xdom::_inputsourcegetpublicid));
    pinputsource->Set(JS_STR("getSystemId"), v8::FunctionTemplate::New(xdom::_inputsourcegetsystemid));
    pinputsource->Set(JS_STR("getIssueFatalErrorIfNotFound"), v8::FunctionTemplate::New(xdom::_inputsourcegetissuefatalerrorifnotfound));
    pinputsource->Set(JS_STR("getMemoryManager"), v8::FunctionTemplate::New(xdom::_inputsourcegetmemorymanager));
    pinputsource->Set(JS_STR("setEncoding"), v8::FunctionTemplate::New(xdom::_inputsourcesetencoding));
    pinputsource->Set(JS_STR("setPublicId"), v8::FunctionTemplate::New(xdom::_inputsourcesetpublicid));
    pinputsource->Set(JS_STR("setSystemId"), v8::FunctionTemplate::New(xdom::_inputsourcesetsystemid));
    pinputsource->Set(JS_STR("setIssueFatalErrorIfNotFound"), v8::FunctionTemplate::New(xdom::_inputsourcesetissuefatalerrorifnotfound));

  // *****						*****
  // *****	END   [[ InputSource ]]			*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ LocalFileInputSource ]]	*****
  // *****						*****

    xdom::ffileinput = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_fileinput));
    xdom::ffileinput->Inherit(xdom::finputsource);
    xdom::ffileinput->SetClassName(JS_STR("LocalFileInputSource"));

    v8::Handle<v8::Template> pfileinput = xdom::ffileinput->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> fileinputt = xdom::ffileinput->InstanceTemplate();
    fileinputt->SetInternalFieldCount(1);
    fileinputt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("LocalFileInputSource"));

    /**
     * FileInputSource prototype methods
     */
    fileinputt->Set(JS_STR("~LocalFileInputSource "), v8::FunctionTemplate::New(xdom::_fileinput_destructor));

  // *****						*****
  // *****	END   [[ LocalFileInputSource ]]	*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ MemBufInputSource ]]		*****
  // *****						*****

    xdom::fmembufinput = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_membufinput));
    xdom::fmembufinput->Inherit(xdom::finputsource);
    xdom::fmembufinput->SetClassName(JS_STR("MemBufInputSource"));

    v8::Handle<v8::Template> pmembufinput = xdom::fmembufinput->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> membufinputt = xdom::fmembufinput->InstanceTemplate();
    membufinputt->SetInternalFieldCount(2);
    membufinputt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("MemBufInputSource"));

    /**
     * MemBufInputSource prototype methods
     */
    membufinputt->Set(JS_STR("~MemBufInputSource"), v8::FunctionTemplate::New(xdom::_membufinput_destructor));
    pmembufinput->Set(JS_STR("setCopyBufToStream"), v8::FunctionTemplate::New(xdom::_membufinputsetcopybuftostream));
    pmembufinput->Set(JS_STR("resetMemBufInputSource"), v8::FunctionTemplate::New(xdom::_membufinputresetmembufinputsource));

  // *****						*****
  // *****	END   [[ MemBufInputSource ]]		*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ StdInInputSource ]]		*****
  // *****						*****

    xdom::fstdin = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_stdin));
    xdom::fstdin->Inherit(xdom::finputsource);
    xdom::fstdin->SetClassName(JS_STR("StdInInputSource"));

    v8::Handle<v8::Template> pstdin = xdom::fstdin->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> stdint = xdom::fstdin->InstanceTemplate();
    stdint->SetInternalFieldCount(1);
    stdint->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("StdInInputSource"));

    /**
     * StdInInputSource prototype methods
     */
    stdint->Set(JS_STR("~StdInInputSource "), v8::FunctionTemplate::New(xdom::_stdin_destructor));

  // *****						*****
  // *****	END   [[ StdInInputSource ]]		*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ URLInputSource ]]		*****
  // *****						*****

    xdom::furlinput = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_urlinput));
    xdom::furlinput->Inherit(xdom::finputsource);
    xdom::furlinput->SetClassName(JS_STR("URLInputSource"));

    v8::Handle<v8::Template> purlinput = xdom::furlinput->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> urlinputt = xdom::furlinput->InstanceTemplate();
    urlinputt->SetInternalFieldCount(1);
    urlinputt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("URLInputSource"));

    /**
     * URLInputSource prototype methods
     */
    urlinputt->Set(JS_STR("~URLInputSource "), v8::FunctionTemplate::New(xdom::_urlinput_destructor));

  // *****						*****
  // *****	END   [[ URLInputSource ]]		*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ XMLURL ]]		*****
  // *****						*****

    xdom::fxmlurl = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_xmlurl));
    xdom::fxmlurl->Inherit(xdom::finputsource);
    xdom::fxmlurl->SetClassName(JS_STR("XMLURL"));

    v8::Handle<v8::Template> pxmlurl = xdom::fxmlurl->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> xmlurlt = xdom::fxmlurl->InstanceTemplate();
    xmlurlt->SetInternalFieldCount(1);
    xmlurlt->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("XMLURL"));

    /**
     * XMLURL prototype methods
     */
    xmlurlt->Set(JS_STR("~XMLURL"), v8::FunctionTemplate::New(xdom::_xmlurl_destructor));
    pxmlurl->Set(JS_STR("getFragment"), v8::FunctionTemplate::New(xdom::_xmlurlgetfragment));
    pxmlurl->Set(JS_STR("getHost"), v8::FunctionTemplate::New(xdom::_xmlurlgethost));
    pxmlurl->Set(JS_STR("getPassword"), v8::FunctionTemplate::New(xdom::_xmlurlgetpassword));
    pxmlurl->Set(JS_STR("getPath"), v8::FunctionTemplate::New(xdom::_xmlurlgetpath));
    pxmlurl->Set(JS_STR("getPortNum"), v8::FunctionTemplate::New(xdom::_xmlurlgetportnum));
    pxmlurl->Set(JS_STR("getProtocolName"), v8::FunctionTemplate::New(xdom::_xmlurlgetprotocolname));
    pxmlurl->Set(JS_STR("getQuery"), v8::FunctionTemplate::New(xdom::_xmlurlgetquery));
    pxmlurl->Set(JS_STR("getURIText"), v8::FunctionTemplate::New(xdom::_xmlurlgeturltext));
    pxmlurl->Set(JS_STR("getUser"), v8::FunctionTemplate::New(xdom::_xmlurlgetuser));
    pxmlurl->Set(JS_STR("hasInvalidChar"), v8::FunctionTemplate::New(xdom::_xmlurlhasinvalidchar));
    pxmlurl->Set(JS_STR("makeNewStream"), v8::FunctionTemplate::New(xdom::_xmlurlmakenewstream));
    pxmlurl->Set(JS_STR("makeRelativeTo"), v8::FunctionTemplate::New(xdom::_xmlurlmakerelativeto));
    pxmlurl->Set(JS_STR("lookupByName"), v8::FunctionTemplate::New(xdom::_xmlurllookupbyname));
    pxmlurl->Set(JS_STR("parse"), v8::FunctionTemplate::New(xdom::_xmlurlparse));
    pxmlurl->Set(JS_STR("toString"), v8::FunctionTemplate::New(xdom::_xmlurlgeturltext));

  // *****						*****
  // *****	END   [[ XMLURL ]]		*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ XPathNamespace ]]		*****
  // *****						*****

    xdom::fxpathnamespace = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_xpathnamespace));
    xdom::fxpathnamespace->Inherit(xdom::fnode);
    xdom::fxpathnamespace->SetClassName(JS_STR("DOMXPathNamespace"));

    v8::Handle<v8::Template> pxpathnamespace = xdom::fxpathnamespace->PrototypeTemplate();

    v8::Handle<v8::ObjectTemplate> xpathnamespacet = xdom::fxpathnamespace->InstanceTemplate();
    xpathnamespacet->SetInternalFieldCount(1);
    xpathnamespacet->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMXPathNamespace"));
    xpathnamespacet->SetAccessor(JS_STR("ownerElement"), xdom::get_property);

    /**
     * XPathNamespace prototype methods
     */
    xpathnamespacet->Set(JS_STR("~DOMXPathNamespace"), v8::FunctionTemplate::New(xdom::_xpathnamespace_destructor));
    pxpathnamespace->Set(JS_STR("getOwnerElement"), v8::FunctionTemplate::New(xdom::_xpathgetownerelement));

  // *****						*****
  // *****	END   [[ XPathNamespace ]]		*****
  // ********************************************************



  // ********************************************************
  // *****	BEGIN [[ DOMTypeInfo ]]			*****
  // *****						*****

    xdom::ftypeinfo = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(xdom::_typeinfo));
    xdom::ftypeinfo->SetClassName(JS_STR("DOMTypeInfo"));

    v8::Handle<v8::ObjectTemplate> typeinfot = xdom::ftypeinfo->InstanceTemplate();
    typeinfot->SetInternalFieldCount(1);
    typeinfot->SetAccessor(JS_STR("_domtype_"), xdom::echo_data, NULL, JS_STR("DOMTypeInfo"));

    v8::Handle<v8::Template> ttypeinfo = xdom::ftypeinfo->PrototypeTemplate();

    /*	*
	*	Emulate enumerated types by setting static property values
	*	for this class on its FunctionTemplate:
	*	(see "http://xerces.apache.org/xerces-c/apiDocs-3/classDOMTypeInfo.html" for enumerated values)
     *	*/
    xdom::ftypeinfo->Set(JS_STR("DERIVATION_EXTENSION"), JS_INT(xercesc_3_0::DOMTypeInfo::DERIVATION_EXTENSION));
    xdom::ftypeinfo->Set(JS_STR("DERIVATION_LIST"), JS_INT(xercesc_3_0::DOMTypeInfo::DERIVATION_LIST));
    xdom::ftypeinfo->Set(JS_STR("DERIVATION_RESTRICTION"), JS_INT(xercesc_3_0::DOMTypeInfo::DERIVATION_RESTRICTION));
    xdom::ftypeinfo->Set(JS_STR("DERIVATION_UNION"), JS_INT(xercesc_3_0::DOMTypeInfo::DERIVATION_UNION));

    /**
     * DOMTypeInfo prototype methods
     */
    typeinfot->Set(JS_STR("~DOMTypeInfo"), v8::FunctionTemplate::New(xdom::_typeinfo_destructor));
    ttypeinfo->Set(JS_STR("getTypeName"), v8::FunctionTemplate::New(xdom::_typeinfogettypename));
    ttypeinfo->Set(JS_STR("getTypeNamespace"), v8::FunctionTemplate::New(xdom::_typeinfogettypenamespace));
    ttypeinfo->Set(JS_STR("isDerivedFrom"), v8::FunctionTemplate::New(xdom::_typeinfoisderivedfrom));

  // *****						*****
  // *****	END   [[ DOMTypeInfo ]]			*****
  // ********************************************************


  // ********************************************************
  // ********************************************************

  //	*
  //	*	Exported symbols:
  //	*

  exports->Set(JS_STR("DOMException"), xdom::fdomexcpt->GetFunction());
  exports->Set(JS_STR("DOMImplementation"), xdom::fdom->GetFunction());
  exports->Set(JS_STR("DOMImplementationLS"), xdom::fdomls->GetFunction());
  exports->Set(JS_STR("DOMImplementationSource"), xdom::fdomsource->GetFunction());
  exports->Set(JS_STR("DOMImplementationRegistry"), xdom::fdomreg->GetFunction());
  exports->Set(JS_STR("DOMLSParser"), xdom::fparser->GetFunction());
  exports->Set(JS_STR("DOMLSSerializer"), xdom::fserializer->GetFunction());
  exports->Set(JS_STR("DOMTypeInfo"), xdom::ftypeinfo->GetFunction());
  exports->Set(JS_STR("DOMNode"), xdom::fnode->GetFunction());
  exports->Set(JS_STR("XMLURL"), xdom::fxmlurl->GetFunction());
  exports->Set(JS_STR("MemBufInputSource"), xdom::fmembufinput->GetFunction());
}

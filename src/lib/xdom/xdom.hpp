#ifndef _JS_DOM_H
#define _JS_DOM_H

#define RECAST(item, type) reinterpret_cast<type>(v8::Handle<v8::External>::Cast(item)->Value());

#define JS_RETURN_ERROR(reason) { JS_ERROR(reason); return; }

#define LOAD_DOMEXCEPTION(domerr)	DOMException * domerr = LOAD_PTR(0,DOMException *)
#define DOM_EXCEPTION			LOAD_DOMEXCEPTION(domerr)
#define DOMEXCPT			LOAD_DOMEXCEPTION(domerr)
#define DOMERR				LOAD_DOMEXCEPTION(domerr)

#define LOAD_DOMLSEXCEPTION(domerr)	DOMLSException * domerr = LOAD_PTR(0,DOMLSException *)
#define DOM_LSEXCEPTION			LOAD_DOMLSEXCEPTION(domerr)
#define DOMLSEXCPT			LOAD_DOMLSEXCEPTION(domerr)
#define DOMLSERR			LOAD_DOMLSEXCEPTION(domerr)

#define LOAD_DOMLIST(domlist)		DOMImplementationList * domlist = LOAD_PTR(0,DOMImplementationList *)
#define DOM_LIST			LOAD_DOMLIST(domlist)
#define DOMLIST				LOAD_DOMLIST(domlist)

#define LOAD_DOMLOCATOR(domlocator)	DOMLocator * domlocator = LOAD_PTR(0,DOMLocator *)
#define DOM_LOCATOR			LOAD_DOMLOCATOR(domlocator)
#define DOMLOCATOR			LOAD_DOMLOCATOR(domlocator)

#define LOAD_DOMSOURCE(domsource)	DOMImplementationSource * domsource = LOAD_PTR(0,DOMImplementationSource *)
#define DOM_SOURCE			LOAD_DOMSOURCE(domsource)
#define DOMSOURCE			LOAD_DOMSOURCE(domsource)

#define LOAD_DOMREG(domreg)		DOMImplementationRegistry * domreg = LOAD_PTR(0,DOMImplementationRegistry *)
#define DOM_REG				LOAD_DOMREG(domreg)
#define DOMREG				LOAD_DOMREG(domreg)

#define DOM_LOAD_DOM(dom)		DOMImplementation * dom = LOAD_PTR(0,DOMImplementation *)
#define DOM_DOM				DOM_LOAD_DOM(dom)
#define DOM				DOM_LOAD_DOM(dom)

#define DOM_LOAD_DOMLS(domls)		DOMImplementationLS * domls = LOAD_PTR(0,DOMImplementationLS *)
#define DOM_DOMLS			DOM_LOAD_DOMLS(domls)
#define DOMLS				DOM_LOAD_DOMLS(domls)

#define PARSER_LOAD_DOM(parser,dom)	DOMLSParser * parser = LOAD_PTR(0,DOMLSParser *); DOMImplementation * dom = LOAD_PTR(1, DOMImplementation *)
#define PARSER_LOAD(parser)		DOMLSParser * parser = LOAD_PTR(0,DOMLSParser *)
#define PARSER_DOM			PARSER_LOAD_DOM(parser,dom)
#define PARSER				PARSER_LOAD(parser)

#define NODEFILTER_LOAD_DOM(filter)	DOMNodeFilter * filter = LOAD_PTR(0,DOMNodeFilter *)
#define NODEFILTER_DOM			NODEFILTER_LOAD_DOM(filter)
#define NODEFILTER			NODEFILTER_LOAD_DOM(filter)

#define PARSERFILTER_LOAD_DOM(filter)	DOMLSParserFilter * filter = LOAD_PTR(0,DOMLSParserFilter *)
#define PARSERFILTER_DOM		PARSERFILTER_LOAD_DOM(filter)
#define PARSERFILTER			PARSERFILTER_LOAD_DOM(filter)

#define DOM_LOAD_DOCFRAG(frag)		DOMDocumentFragment * frag = LOAD_PTR(0,DOMDocumentFragment *)
#define DOM_DOCUMENTFRAGMENT		DOM_LOAD_DOCFRAG(frag)
#define DOCUMENTFRAGMENT		DOM_LOAD_DOCFRAG(frag)
#define DOCFRAG				DOM_LOAD_DOCFRAG(frag)

#define DOM_LOAD_NODE(node)		DOMNode * node = LOAD_PTR(0,DOMNode *)
#define DOM_NODE			DOM_LOAD_NODE(node)
#define NODE				DOM_LOAD_NODE(node)

#define DOM_LOAD_TEXT(text)		DOMText * text = LOAD_PTR(0,DOMText *)
#define DOM_TEXT			DOM_LOAD_TEXT(text)
#define TEXT				DOM_LOAD_TEXT(text)

#define DOM_LOAD_PROCESSINGINSTRUCTION(processinginstruction)		DOMProcessingInstruction * processinginstruction = LOAD_PTR(0,DOMProcessingInstruction *)
#define DOM_PROCESSINGINSTRUCTION	DOM_LOAD_PROCESSINGINSTRUCTION(processinginstruction)
#define PROCESSINGINSTRUCTION		DOM_LOAD_PROCESSINGINSTRUCTION(processinginstruction)
#define PROCINST			DOM_LOAD_PROCESSINGINSTRUCTION(procinst)

#define DOM_LOAD_DOC(doc)		DOMDocument * doc = LOAD_PTR(0,DOMDocument *)
#define DOM_DOCUMENT			DOM_LOAD_DOC(document)
#define DOCUMENT			DOM_LOAD_DOC(document)
#define DOC				DOM_LOAD_DOC(doc)

#define DOM_LOAD_ELEMENT(element)	DOMElement * element = LOAD_PTR(0,DOMElement *)
#define DOM_ELEMENT			DOM_LOAD_ELEMENT(element)
#define ELEMENT				DOM_LOAD_ELEMENT(element)
#define EL				DOM_LOAD_ELEMENT(el)

#define DOM_LOAD_ATTRIBUTE(attribute)	DOMAttr * attribute = LOAD_PTR(0,DOMAttr *)
#define DOM_ATTRIBUTE			DOM_LOAD_ATTRIBUTE(attribute)
#define ATTRIBUTE			DOM_LOAD_ATTRIBUTE(attribute)

#define DOM_LOAD_ENTITYREFERENCE(er)	DOMEntityReference * er = LOAD_PTR(0,DOMEntityReference *)
#define DOM_ENTITYREFERENCE		DOM_LOAD_ENTITYREFERENCE(entityreference)
#define ENTITYREFERENCE			DOM_LOAD_ENTITYREFERENCE(entityreference)
#define ENTITYREF			DOM_LOAD_ENTITYREFERENCE(entityref)

#define DOM_LOAD_CHARDATA(cdatasect)	DOMCDATASection * cdatasect = LOAD_PTR(0,DOMCDATASection *)
#define DOM_CDATASECT			DOM_LOAD_CHARDATA(cdatasect)
#define CDATASECT			DOM_LOAD_CHARDATA(cdatasect)

#define DOM_LOAD_CDATA(cdata)		DOMCharacterData * cdata = LOAD_PTR(0,DOMCharacterData *)
#define DOM_CDATA			DOM_LOAD_CHARDATA(cdata)
#define CDATA				DOM_LOAD_CHARDATA(cdata)

#define DOM_LOAD_COMMENT(comment)	DOMComment * comment = LOAD_PTR(0,DOMComment *)
#define DOM_COMMENT			DOM_LOAD_COMMENT(comment)
#define COMMENT				DOM_LOAD_COMMENT(comment)

#define DOM_LOAD_DOCUMENTTYPE(dtype)	DOMDocumentType * dtype = LOAD_PTR(0,DOMDocumentType *)
#define DOM_DOCUMENTTYPE		DOM_LOAD_DOCUMENTTYPE(documenttype)
#define DOCUMENTTYPE			DOM_LOAD_DOCUMENTTYPE(documenttype)
#define DOCTYPE				DOM_LOAD_DOCUMENTTYPE(docType)

#define DOM_LOAD_ENTITY(entity)		DOMEntity * entity = LOAD_PTR(0,DOMEntity *)
#define DOM_ENTITY			DOM_LOAD_ENTITY(entity)
#define ENTITY				DOM_LOAD_ENTITY(entity)

#define DOM_LOAD_NOTATION(notation)	DOMNotation * notation = LOAD_PTR(0,DOMNotation *)
#define DOM_NOTATION			DOM_LOAD_NOTATION(notation)
#define NOTATION			DOM_LOAD_NOTATION(notation)

#define DOM_LOAD_CONFIG(domconfig)	DOMConfiguration * domconfig = LOAD_PTR(0,DOMConfiguration *)
#define DOM_CONFIG			DOM_LOAD_CONFIG(domconfig)
#define DOMCONFIG			DOM_LOAD_CONFIG(domconfig)

#define DOM_LOAD_XPATH(xpath)		DOMXPathNamespace * xpath = LOAD_PTR(0,DOMXPathNamespace *)
#define DOM_XPATH			DOM_LOAD_XPATH(xpath)
#define XPATH				DOM_LOAD_XPATH(xpath)

#define LOAD_MM(mm)			MemoryManager * mm = LOAD_PTR(0,MemoryManager *)
#define MEMMGR				LOAD_MM(mm)
#define MM				LOAD_MM(mm)

#define DOM_LOAD_MM(dommm)		DOMMemoryManager * dommm = LOAD_PTR(0,DOMMemoryManager *)
#define DOM_MEMMGR			DOM_LOAD_MM(dommm)
#define DOMMEMMGR			DOM_LOAD_MM(dommm)

#define DOM_LOAD_XMEM(xmem)		XMemory * xmem = LOAD_PTR(0,XMemory *)
#define DOM_XMEM			DOM_LOAD_XMEM(xmem)
#define XMEM				DOM_LOAD_XMEM(xmem)

#define DOM_LOAD_STDIN(stdin)		StdInInputSource * stdin = LOAD_PTR(0,StdInInputSource *)
#define DOM_STDIN			DOM_LOAD_STDIN(my_stdin)
#define STDIN				DOM_LOAD_STDIN(my_stdin)

#define DOM_LOAD_XMLURL(xmlurl)		XMLURL * xmlurl = LOAD_PTR(0,XMLURL *)
#define DOM_XMLURL			DOM_LOAD_XMLURL(xmlurl)
#define LXMLURL				DOM_LOAD_XMLURL(xmlurl)

#define DOM_LOAD_INPUTSOURCE(inputsource) InputSource * inputsource = LOAD_PTR(0,InputSource *)
#define DOM_INPUTSOURCE			DOM_LOAD_INPUTSOURCE(inputsource)
#define INPUTSOURCE			DOM_LOAD_INPUTSOURCE(inputsource)

#define LOAD_FILEINPUT(fileinput)	LocalFileInputSource * fileinput = LOAD_PTR(0,LocalFileInputSource *)
#define FILEINPUT			LOAD_FILEINPUT(fileinput)

#define DOM_LOAD_BININPUT(bininput)	BinInputStream * bininput = LOAD_PTR(0,BinInputStream *)
#define DOM_BININPUT			DOM_LOAD_BININPUT(bininput)
#define BININPUT			DOM_LOAD_BININPUT(bininput)

#define DOM_LOAD_BINFILEINPUT(binfileinput)	BinFileInputStream * binfileinput = LOAD_PTR(0,BinFileInputStream *)
#define DOM_BINFILEINPUT		DOM_LOAD_BINFILEINPUT(binfileinput)
#define BINFILEINPUT			DOM_LOAD_BINFILEINPUT(binfileinput)

#define DOM_LOAD_BINMEMINPUT(binmeminput)	BinMemInputStream * binmeminput = LOAD_PTR(0,BinMemInputStream *)
#define DOM_BINMEMINPUT			DOM_LOAD_BINMEMINPUT(binmeminput)
#define BINMEMINPUT			DOM_LOAD_BINMEMINPUT(binmeminput)

#define DOM_LOAD_MEMBUFINPUT(membuf)	MemBufInputSource * membuf = LOAD_PTR(0,MemBufInputSource *)
#define DOM_MEMBUFINPUT			DOM_LOAD_MEMBUFINPUT(membuf)
#define MEMBUFINPUT			DOM_LOAD_MEMBUFINPUT(membuf)

#define DOM_LOAD_UDHANDLER(dhandler)	DOMUserDataHandler * dhandler = LOAD_PTR(0,DOMUserDataHandler *)
#define DOM_USERDATAHANDLER		DOM_LOAD_UDHANDLER(dhandler)
#define USERDATAHANDLER			DOM_LOAD_UDHANDLER(dhandler)
 
#define DOM_LOAD_STRINGLIST(dslist)	DOMStringList * dslist = LOAD_PTR(0,DOMStringList *)
#define DOM_STRINGLIST			DOM_LOAD_STRINGLIST(dslist)
#define STRINGLIST			DOM_LOAD_STRINGLIST(dslist)

#define DOM_LOAD_NODELIST(nodelist)	DOMNodeList * nodelist = LOAD_PTR(0,DOMNodeList *)
#define DOM_NODELIST			DOM_LOAD_NODELIST(nodelist)
#define NODELIST			DOM_LOAD_NODELIST(nodelist)

#define DOM_LOAD_NAMEDNODEMAP(nodemap)	DOMNamedNodeMap * nodemap = LOAD_PTR(0,DOMNamedNodeMap *)
#define DOM_NAMEDNODEMAP		DOM_LOAD_NAMEDNODEMAP(nodemap)
#define NODEMAP				DOM_LOAD_NAMEDNODEMAP(nodemap)

#define DOM_LOAD_TYPEINFO(typeinfo)	DOMTypeInfo * typeinfo = LOAD_PTR(0,DOMTypeInfo *)
#define DOM_TYPEINFO			DOM_LOAD_TYPEINFO(typeinfo)
#define TYPEINFO			DOM_LOAD_TYPEINFO(typeinfo)

#define DOM_LOAD_DOMLSINPUT(domlsinput)	DOMLSInput * domlsinput = LOAD_PTR(0,DOMLSInput *)
#define DOM_DOMLSINPUT			DOM_LOAD_DOMLSINPUT(domlsinput)
#define DOMLSINPUT			DOM_LOAD_DOMLSINPUT(domlsinput)

#define DOM_LOAD_DOMLSOUTPUT(domlsoutput)	DOMLSOutput * domlsoutput = LOAD_PTR(0,DOMLSOutput *)
#define DOM_DOMLSOUTPUT			DOM_LOAD_DOMLSOUTPUT(domlsoutput)
#define DOMLSOUTPUT			DOM_LOAD_DOMLSOUTPUT(domlsoutput)

#define SERIALIZER_LOAD_DOM(serializer,dom)	DOMLSSerializer * serializer = LOAD_PTR(0,DOMLSSerializer *); DOMImplementation * dom = LOAD_PTR(1, DOMImplementation *)
#define SERIALIZER_LOAD(serializer)	DOMLSSerializer * serializer = LOAD_PTR(0,DOMLSSerializer *)
#define SERIALIZER_DOM			SERIALIZER_LOAD_DOM(serializer,dom)
#define SERIALIZER			SERIALIZER_LOAD(serializer)

#define SERIALIZERFILTER_LOAD_DOM(filter)	DOMLSSerializerFilter * filter = LOAD_PTR(0,DOMLSSerializerFilter *)
#define SERIALIZERFILTER_DOM		SERIALIZERFILTER_LOAD_DOM(filter)
#define SERIALIZERFILTER		SERIALIZERFILTER_LOAD_DOM(filter)

#define USTR(...)			v8::String::Utf8Value(__VA_ARGS__)
#define SS				std::stringstream
#define XS				XMLCh *
#define XML_STR(...)			XMLString::transcode(__VA_ARGS__)
#define X(...)				XMLString::transcode(__VA_ARGS__)
#define X_STR(item)			XMLString::transcode(item.str().c_str())
#define ARGSTR(item)			X(*v8::String::Utf8Value(args[item]))
#define OLD2_ARGSTR(item)		*String::Value(args[item])
#define OLD_ARGSTR(item)		*String::Value(args[item]->ToString())
#define DOMOPTYPE			xercesc_3_1::DOMUserDataHandler::DOMOperationType
#define CSTR(sstream)			sstream.str().c_str()

#define XTRY(...)			try{ __VA_ARGS__ }    catch( xercesc_3_1::DOMException& e ) { char * msg = X(e.getMessage()); JS_RETURN_ERROR(msg); }
#define ZTRY(...)			try{ __VA_ARGS__ }    catch( xercesc_3_1::DOMException& e ) { char * msg = X(e.getMessage()); JS_ERROR(msg); }
#define XLSTRY(...)			try{ __VA_ARGS__ }    catch( xercesc_3_1::DOMLSException& e ) { char * msg = X(e.getMessage()); JS_RETURN_ERROR(msg); }
#define ZLSTRY(...)			try{ __VA_ARGS__ }    catch( xercesc_3_1::DOMLSException& e ) { char * msg = X(e.getMessage()); JS_ERROR(msg); }

/*
 *	Function templates for each of the
 *	DOM node types:
 */

v8::Persistent<v8::FunctionTemplate> fdomexcpt;
v8::Persistent<v8::FunctionTemplate> fdomlsexcpt;
v8::Persistent<v8::FunctionTemplate> fdomlist;
v8::Persistent<v8::FunctionTemplate> fdomlocator;
v8::Persistent<v8::FunctionTemplate> fdomsource;
v8::Persistent<v8::FunctionTemplate> fdomreg;
v8::Persistent<v8::FunctionTemplate> fdom;
v8::Persistent<v8::FunctionTemplate> fdomls;
v8::Persistent<v8::FunctionTemplate> fdomconfiguration;
v8::Persistent<v8::FunctionTemplate> fnodefilter;
v8::Persistent<v8::FunctionTemplate> fparser;
v8::Persistent<v8::FunctionTemplate> fparserfilter;
v8::Persistent<v8::FunctionTemplate> fserializer;
v8::Persistent<v8::FunctionTemplate> fserializerfilter;
v8::Persistent<v8::FunctionTemplate> finput;
v8::Persistent<v8::FunctionTemplate> foutput;
v8::Persistent<v8::FunctionTemplate> fdomlsinput;

v8::Persistent<v8::FunctionTemplate> fdocumentfragment;
v8::Persistent<v8::FunctionTemplate> fnode;
v8::Persistent<v8::FunctionTemplate> fprocessinginstruction;
v8::Persistent<v8::FunctionTemplate> fdocument;
v8::Persistent<v8::FunctionTemplate> fpreelement;
v8::Persistent<v8::FunctionTemplate> felement;
v8::Persistent<v8::FunctionTemplate> fattribute;
v8::Persistent<v8::FunctionTemplate> fentityreference;
v8::Persistent<v8::FunctionTemplate> fcdata;
v8::Persistent<v8::FunctionTemplate> fcomment;
v8::Persistent<v8::FunctionTemplate> ftext;
v8::Persistent<v8::FunctionTemplate> fcdatasection;
v8::Persistent<v8::FunctionTemplate> fdocumenttype;
v8::Persistent<v8::FunctionTemplate> fentity;
v8::Persistent<v8::FunctionTemplate> fnotation;
v8::Persistent<v8::FunctionTemplate> fxpathnamespace;

/*
 *	Function templates for miscellaneous DOM class types:
 */
v8::Persistent<v8::FunctionTemplate> fxmlurl;
v8::Persistent<v8::FunctionTemplate> fstringlist;
v8::Persistent<v8::FunctionTemplate> fnamednodemap;
v8::Persistent<v8::FunctionTemplate> fnodelist;
v8::Persistent<v8::FunctionTemplate> fuserdata;
v8::Persistent<v8::FunctionTemplate> fuserdatahandler;
v8::Persistent<v8::FunctionTemplate> ftypeinfo;

v8::Persistent<v8::FunctionTemplate> fbuffer;
v8::Persistent<v8::FunctionTemplate> fxmemory;
v8::Persistent<v8::FunctionTemplate> fdommemorymanager;
v8::Persistent<v8::FunctionTemplate> fmemorymanager;

v8::Persistent<v8::FunctionTemplate> finputsource;
v8::Persistent<v8::FunctionTemplate> fbininput;
v8::Persistent<v8::FunctionTemplate> fbinfileinput;
v8::Persistent<v8::FunctionTemplate> fbinmeminput;
v8::Persistent<v8::FunctionTemplate> ffileinput;
v8::Persistent<v8::FunctionTemplate> fstdin;
v8::Persistent<v8::FunctionTemplate> furlinput;
v8::Persistent<v8::FunctionTemplate> fmembufinput;
v8::Persistent<v8::FunctionTemplate> ffileloc;
v8::Persistent<v8::FunctionTemplate> ffilepos;

v8::Persistent<v8::FunctionTemplate> fformattarget;
v8::Persistent<v8::FunctionTemplate> ffiletarget;
v8::Persistent<v8::FunctionTemplate> fmembuftarget;
v8::Persistent<v8::FunctionTemplate> fstdouttarget;

#endif

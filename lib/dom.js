var Node = function(ownerDocument, name) {
	this.childNodes = [];
	this.attributes = [];

	this.parentNode = null;
	this.previousSibling = null;
	this.nextSibling = null;
	this.ownerDocument = ownerDocument;

	this.nodeName = name;
	this.nodeValue = null;
	this.nodeType = 0;

	this.namespaceURI = ""
	this.baseURI = "";
}

Node.ELEMENT_NODE = 1;
Node.ATTRIBUTE_NODE = 2;
Node.TEXT_NODE = 3;
Node.CDATA_SECTION_NODE = 4;
Node.ENTITY_REFERENCE_NODE = 5;
Node.ENTITY_NODE = 6;
Node.PROCESSING_INSTRUCTION_NODE = 7;
Node.COMMENT_NODE = 8;
Node.DOCUMENT_NODE = 9;
Node.DOCUMENT_TYPE_NODE = 10;
Node.DOCUMENT_FRAGMENT_NODE = 11;
Node.NOTATION_NODE = 12;

Node.prototype.__defineGetter__("firstChild", function() { return this.childNodes.length ? this.childNodes[0] : null; });
Node.prototype.__defineGetter__("lastChild", function() { return this.childNodes.length ? this.childNodes[this.childNodes.length-1] : null; });
Node.prototype.__defineGetter__("textContent", function() { return this._textContent(); });
Node.prototype.__defineGetter__("localName", function() { return null; });
Node.prototype.__defineGetter__("prefix", function() { return null; });

Node.prototype.appendChild = function(node) {
	node._removeReferences();

	this.childNodes.push(node);
	node.parentNode = this;

	node._addReferences();

	return node;
}

Node.prototype.cloneNode = function(deep) {
	return null;
}

Node.prototype.hasAttributes = function() {
	return this.attributes.length > 0;
}

Node.prototype.hasChildNodes = function() {
	return this.childNodes.length > 0;
}

Node.prototype.insertBefore = function(newNode, referenceNode) {
	if (!referenceNode) { return this.appendChild(newNode); }

	var index = this.childNodes.indexOf(referenceNode);
	if (index == -1) { throw new Error("Cannot insert before non-existent child"); }
	newNode._removeReferences();
	this.childNodes.splice(index, 0, newNode);
	newNode._addReferences();
	referenceNode._addReferences();

	if (index > 0) {
		var prev = this.childNodes[index-1];
		prev._addReferences();
	}
	return newNode;
}

Node.prototype.replaceChild = function(newChild, oldChild) {
	var index = this.childNodes.indexOf(oldChild);
	if (index == -1) { throw new Error("Cannot replace non-existent child"); }

	oldChild._removeReferences();
	newChild._removeReferences();
	this.childNodes.splice(index, 0, newChild);
	newChild._addReferences();
	
	return newChild;
}

Node.prototype.removeChild = function(child) {
	if (child.parentNode != this) { throw new Error("Cannot remove child from non-parent"); }
	child._removeReferences();
	return child;
}

Node.prototype.normalize = function() {
	var index = 0;
	var lastText = null;

	while (index < this.childNodes.length) {
		var child = this.childNodes[index];

		if (child.nodeType == Node.TEXT_NODE) {
			/* text node */
			var remove = false; 
			if (child.nodeValue == "") { remove = true; }

			if (lastText) {
				/* merge with previous */
				lastText.appendData(child.nodeValue);
				remove = true;
			}

			if (remove) { 
				this.removeChild(child); 
			} else {
				lastText = child;
				index++;
			}
		} else {
			/* non-text node: reset last text, continue */
			lastText = null;
			index++;
		}

	}
}

Node.prototype._removeReferences = function() {
	if (this.previousSibling) {
		this.previousSibling.nextSibling = null;
		this.previousSibling = null;
	}

	if (this.nextSibling) {
		this.nextSibling.previousSibling = null;
		this.nextSibling = null;
	}

	if (this.parentNode) {
		var index = this.parentNode.childNodes.indexOf(this);
		if (index == -1) { throw new Error("Cannot find node in its parent"); }
		this.parentNode.childNodes.splice(index, 1);
		this.parentNode = null;
	}
}

Node.prototype._addReferences = function() {
	if (!this.parentNode) { return; }
	var index = this.parentNode.childNodes.indexOf(this);
	if (index == -1) { throw new Error("Cannot find node in its parent"); }

	if (index > 0) {
		var prev = this.parentNode.childNodes[index-1];
		prev.nextSibling = this;
		this.previousSibling = prev;
	}

	if (index < this.parentNode.childNodes.length-1) {
		var next = this.parentNode.childNodes[index+1];
		next.previousSibling = this;
		this.nextSibling = next;
	}
}

Node.prototype._textContent = function() {
	return this.nodeValue;
}

Node.prototype._pad = function(depth) {
	var str = "";
	for (var i=0;i<depth;i++) { str += "\t"; }
	return str;
}

/* ------------------------------------------------------------- */

var Attr = function(ownerDocument, name) {
	Node.call(this, ownerDocument, name);
	this.nodeType = Node.ATTRIBUTE_NODE;
	this.ownerElement = null;
}

var tmp = function(){}; tmp.prototype = Node.prototype; Attr.prototype = new tmp();

Attr.prototype.__defineGetter__("localName", function() { return this._localName(); });
Attr.prototype.__defineGetter__("prefix", function() { return this._prefix(); });
Attr.prototype.__defineGetter__("value", function() { return this.nodeValue; });
Attr.prototype.__defineGetter__("nodeValue", function() { return this._getNodeValue(); });
Attr.prototype.__defineSetter__("nodeValue", function(value) { return this._setNodeValue(value); });

Attr.prototype.cloneNode = function(deep) {
	var attr = new Attr(this.ownerDocument, this.nodeName);
	if (this.childNodes.length) { attr.nodeValue = this.nodeValue; }
	return attr;
}

Attr.prototype.toString = function() { return "Attribute "+this.nodeName; }

Attr.prototype._localName = function() {
	var index = this.nodeName.indexOf(":");
	if (index == -1) {
		return this.nodeName;
	} else {
		return this.nodeName.substring(index+1);
	}
}

Attr.prototype._prefix = function() {
	var index = this.nodeName.indexOf(":");
	if (index == -1) {
		return null;
	} else {
		return this.nodeName.substring(0, index);
	}
}

Attr.prototype._getNodeValue = function() {
	if (this.childNodes.length) {
		return this.childNodes[0].nodeValue;
	} else { return ""; }
}

Attr.prototype._setNodeValue = function(value) {
	if (value === null) { return; }
	if (!this.childNodes.length) {
		this.appendChild(this.ownerDocument.createTextNode(value));
	}
	this.childNodes[0].nodeValue = value;
}

/* ------------------------------------------------------------- */

var Element = function(ownerDocument, name) {
	Node.call(this, ownerDocument, name);
	this.nodeType = Node.ELEMENT_NODE;
}

var tmp = function(){}; tmp.prototype = Node.prototype; Element.prototype = new tmp();

Element.prototype.__defineGetter__("localName", function() { return Attr.prototype._localName.call(this); });
Element.prototype.__defineGetter__("prefix", function() { return Attr.prototype._prefix.call(this); });

Element.prototype.setAttribute = function(name, value) {
	var node = this.getAttributeNode(name);
	if (node) {
		node.nodeValue = value;
	} else {
		var attr = new Attr(this.ownerDocument, name);
		attr.nodeValue = value;
		attr.ownerElement = this;
		this.attributes.push(attr);
	}
}

Element.prototype.setAttributeNode = function(attr) {
	var name = attr.nodeName;
	var node = this.getAttributeNode(name);
	attr.ownerElement = this;
	if (node) {
		var index = this.attributes.indexOf(node);
		node.ownerElement = null;
		this.attributes.splice(index, 1, attr);
		return node;
	} else {
		this.attributes.push(attr);
		return null;
	}
}

Element.prototype.getAttribute = function(name) {
	var node = this.getAttributeNode(name);
	if (!node) { return node; }
	return node.nodeValue;
}

Element.prototype.getAttributeNode = function(name) {
	for (var i=0;i<this.attributes.length;i++) {
		var att = this.attributes[i];
		if (att.nodeName == name) { return att; }
	}
	return null;
}

Element.prototype.hasAttribute = function(name) {
	return !!this.getAttributeNode(name);
}

Element.prototype.removeAttribute = function(name) {
	var node = this.getAttributeNode(name);
	if (!node) { return; }
	return this.removeAttributeNode(node);
}

Element.prototype.removeAttributeNode = function(node) {
	node.ownerElement = null;
	var index = this.attributes.indexOf(node);
	this.attributes.splice(index, 1);
}

Element.prototype.getElementsByTagName = function(name) {
	var result = [];
	for (var i=0;i<this.childNodes.length;i++) {
		var child = this.childNodes[i];
		if (child.nodeType != Node.ELEMENT_NODE) { continue; }
		if (child.nodeName == name) { result.push(child); }
		
		var sub = child.getElementsByTagName(name);
		for (var j=0;j<sub.length;j++) { result.push(sub[j]); }
	}
	return result;
}

Element.prototype.cloneNode = function(deep) {
	var elm = new Element(this.ownerDocument, this.nodeName);
	if (deep) {
		for (var i=0;i<this.attributes.length;i++) {
			var att = this.attributes[i].cloneNode(deep);
			elm.setAttributeNode(att);
		}
		for (var i=0;i<this.childNodes.length;i++) {
			var node = this.childNodes[i].cloneNode(deep);
			elm.appendChild(node);
		}
	}
	return elm;
}

Element.prototype.toString = function() { return "Element "+this.nodeName; }

Element.prototype._textContent = function() {
	var str = "";
	for (var i=0;i<this.childNodes.length;i++) {
		str += this.childNodes[i].textContent;
	}
	return str;
}

/* ------------------------------------------------------------- */

var CharacterData = function(ownerDocument, name, value) {
	Node.call(this, ownerDocument, name);
	this.nodeValue = value;
}

var tmp = function(){}; tmp.prototype = Node.prototype; CharacterData.prototype = new tmp();

CharacterData.prototype.__defineGetter__("data", function() { return this.nodeValue; });
CharacterData.prototype.__defineGetter__("length", function() { return this.nodeValue.length; });

CharacterData.prototype.substringData = function(offset, count) {
	return this.nodeValue.substring(offset, count);
}

CharacterData.prototype.appendData = function(data) {
	this.nodeValue += data;
}

CharacterData.prototype.insertData = function(offset, data) {
	var arr = this.nodeValue.split("");
	var args = [offset, 0];
	for (var i=0;i<data.length;i++) { args.push(data[i]); }
	arr.splice.apply(arr, args); 
	this.nodeValue = arr.join("");
}

CharacterData.prototype.deleteData = function(offset, count) {
	var arr = this.nodeValue.split("");
	arr.splice(offset, count);
	this.nodeValue = arr.join("");
}

CharacterData.prototype.replaceData = function(offset, count, data) {
	this.deleteData(offset, count);
	this.insertData(offset, data);
}

CharacterData.prototype.toString = function() { return this.nodeValue; }

/* ------------------------------------------------------------- */

var Text = function(ownerDocument, value) {
	CharacterData.call(this, ownerDocument, "#text", value);
	this.nodeType = Node.TEXT_NODE;
}

var tmp = function(){}; tmp.prototype = CharacterData.prototype; Text.prototype = new tmp();

Text.prototype.cloneNode = function(deep) {
	return new Text(this.ownerDocument, this.nodeValue);
}

/* ------------------------------------------------------------- */

var CDATASection = function(ownerDocument, value) {
	CharacterData.call(this, ownerDocument, "#cdata-section", value);
	this.nodeType = Node.CDATA_SECTION_NODE;
}

var tmp = function(){}; tmp.prototype = CharacterData.prototype; CDATASection.prototype = new tmp();

CDATASection.prototype.cloneNode = function(deep) {
	return new CDATASection(this.ownerDocument, this.nodeValue);
}

/* ------------------------------------------------------------- */

var Comment = function(ownerDocument, value) {
	CharacterData.call(this, ownerDocument, "#comment", value);
	this.nodeType = Node.COMMENT_NODE;
}

var tmp = function(){}; tmp.prototype = CharacterData.prototype; Comment.prototype = new tmp();

Comment.prototype.cloneNode = function(deep) {
	return new Comment(this.ownerDocument, this.nodeValue);
}

/* ------------------------------------------------------------- */

var ProcessingInstruction = function(ownerDocument, name, value) {
	Node.call(this, ownerDocument, name);
	this.nodeType = Node.PROCESSING_INSTRUCTION_NODE;
	this.nodeValue = value;
}

var tmp = function(){}; tmp.prototype = Node.prototype; ProcessingInstruction.prototype = new tmp();

ProcessingInstruction.prototype.__defineGetter__("target", function() { return this.nodeName; });
ProcessingInstruction.prototype.__defineGetter__("data", function() { return this.nodeValue; });


ProcessingInstruction.prototype.cloneNode = function(deep) {
	return new ProcessingInstruction(this.ownerDocument, this.nodeName, this.nodeValue);
}

/* ------------------------------------------------------------- */

var DocumentType = function(ownerDocument, name) {
	Node.call(this, ownerDocument, name);
	this.nodeType = Node.DOCUMENT_TYPE_NODE;
	this.publicId = null;
	this.systemId = null;
}

var tmp = function(){}; tmp.prototype = Node.prototype; DocumentType.prototype = new tmp();

DocumentType.prototype.__defineGetter__("name", function() { return this.nodeName; });


DocumentType.prototype.cloneNode = function(deep) {
	return new DocumentType(this.ownerDocument, this.nodeName, this.nodeValue);
}

/* ------------------------------------------------------------- */

var Document = function() {
	Node.call(this, null, "#document");
	this.nodeType = Node.DOCUMENT_NODE;
	this.xmlEncoding = "utf-8";
	this.xmlVersion = "1.0";
	this.doctype = null;
}

var tmp = function(){}; tmp.prototype = Node.prototype; Document.prototype = new tmp();

Document.prototype.__defineGetter__("documentElement", function() { return this._documentElement(); });

Document.prototype.createElement = function(name) {
	return new Element(this, name);
}

Document.prototype.createElementNS = function(ns, name) {
	var elm = new Element(this, name);
	elm.namespaceURI = ns;
	return elm;
}

Document.prototype.createTextNode = function(value) {
	return new Text(this, value);
}

Document.prototype.createCDATASection = function(value) {
	return new CDATASection(this, value);
}

Document.prototype.createProcessingInstruction = function(name, value) {
	return new ProcessingInstruction(this, name, value);
}

Document.prototype.createComment = function(value) {
	return new Comment(this, value);
}

Document.prototype.createAttribute = function(name) {
	return new Attr(this, name);
}

Document.prototype.createAttributeNS = function(ns, name) {
	var attr = new Attr(this, name);
	attr.namespaceURI = ns;
	return attr;
}

Document.prototype.createDocumentType = function(name, publicId, systemId) {
	var dt = new DocumentType(this, name);
	dt.publicId = publicId;
	dt.systemId = systemId;
	return dt;
}

Document.prototype.getElementsByTagName = Element.prototype.getElementsByTagName;

Document.prototype.cloneNode = function(deep) {
	var elm = new Document();
	elm.xmlEncoding = this.xmlEncoding;
	elm.xmlVersion = this.xmlVersion;
	elm.doctype = this.doctype;
	
	if (deep) {
		for (var i=0;i<this.childNodes.length;i++) {
			var node = this.childNodes[i].cloneNode(deep);
			elm.appendChild(node);
		}
	}
	return elm;
}

Document.prototype.toString = function() { return "Document"; }

Document.prototype._documentElement = function() {
	for (var i=0;i<this.childNodes.length;i++) {
		var node = this.childNodes[i];
		if (node.nodeType == Node.ELEMENT_NODE) { return node; }
	}
	return null;
}

/* ------------------------------------------------------------- */

var XMLSerializer = function() {
	this._map = {};
	this._map[Node.DOCUMENT_NODE] = this._serializeDocument;
	this._map[Node.ELEMENT_NODE] = this._serializeElement;
	this._map[Node.ATTRIBUTE_NODE] = this._serializeAttribute;
	this._map[Node.TEXT_NODE] = this._serializeText;
	this._map[Node.CDATA_SECTION_NODE] = this._serializeCDATASection;
	this._map[Node.PROCESSING_INSTRUCTION_NODE] = this._serializeProcessingInstruction;
	this._map[Node.COMMENT_NODE] = this._serializeComment;
	this._map[Node.DOCUMENT_TYPE_NODE] = this._serializeDocumentType;
}

XMLSerializer.prototype.serializeToString = function(document) {
	this._doc = document;
	return this._serializeNode(document, 0) + "\n";
}

XMLSerializer.prototype._serializeNode = function(node, depth) {
	if (node.nodeType in this._map) {
		return this._map[node.nodeType].call(this, node, depth);
	} else {
		throw new Error("Cannot serialize nodeType '" + node.nodeType + "'");
	}
}

XMLSerializer.prototype._serializeDocument = function(document) {
	var str = "";
	str += '<?xml version="'+document.xmlVersion+'" encoding="'+document.xmlEncoding+'"?>\n';
	if (document.doctype) { str += this._serializeDocumentType(document.doctype); }
	str += this._serializeChildNodes(document);
	return str;
}

XMLSerializer.prototype._serializeDocumentType = function(dt) {
	var str = "<!DOCTYPE " + dt.nodeName;
	var arr = [];
	
	if (dt.publicId) { arr.push('PUBLIC "'+dt.publicId+'"'); }
	if (dt.systemId) { arr.push('"'+dt.systemId+'"'); }
	if (arr.length) { str += " "+arr.join(" "); }
	
	str += ">\n";
	return str;
}

XMLSerializer.prototype._serializeChildNodes = function(node, depth) {
	var str = "";
	for (var i=0;i<node.childNodes.length;i++) {
		str += this._serializeNode(node.childNodes[i], depth);
	}
	return str;
}

XMLSerializer.prototype._serializeElement = function(element, depth) {
	var str = "";
	str += "<" + element.nodeName;
	var arr = [];
	for (var i=0;i<element.attributes.length;i++) {
		arr.push(this._serializeNode(element.attributes[i], depth));
	}
	
	if (element.namespaceURI && !element.prefix) {
		/* walk upwards, try to find non-prefixed element with equal namespace */
		var wasDeclared = false;
		var current = element.parentNode;
		
		while (current != this._doc) {
			if (current.namespaceURI == element.namespaceURI && !current.prefix) { 
				wasDeclared = true; 
				break;
			}
			current = current.parentNode;
		}
		
		if (!wasDeclared) { arr.push('xmlns="'+element.namespaceURI+'"'); }
	}
	
	if (arr.length) { str += " "+arr.join(" "); }

	if (element.childNodes.length) {
		str += ">";
		str += this._serializeChildNodes(element, depth+1);
		str += "</"+element.nodeName+">";
	} else {
		str += "/>";
	}

	return str;
}

XMLSerializer.prototype._serializeAttribute = function(attribute, depth) {
	return this._escapeEntities(attribute.nodeName) + '="' + this._escapeEntities(attribute.nodeValue) + '"';
}

XMLSerializer.prototype._serializeText = function(text, depth) {
	return this._escapeEntities(text.nodeValue);
}

XMLSerializer.prototype._serializeCDATASection = function(cdata, depth) {
	return "<![CDATA[" + cdata.nodeValue + "]]>";
}

XMLSerializer.prototype._serializeComment = function(comment, depth) {
	var str =  "<!--" + comment.nodeValue + "-->";
	if (comment.parentNode == this._doc) { str += "\n"; }
	return str;
}

XMLSerializer.prototype._serializeProcessingInstruction = function(pi, depth) {
	var str = "<?" + pi.nodeName + " " + pi.nodeValue + "?>";
	if (pi.parentNode == this._doc) { str += "\n"; }
	return str;
}

XMLSerializer.prototype._escapeEntities = function(str) {
	return str
			.replace(/&/g, "&amp;")
			.replace(/'/g, "&apos;") // '
			.replace(/"/g, "&quot;") // "
			.replace(/</g, "&lt;")
			.replace(/>/g, "&gt;");
}

/* ------------------------------------------------------------- */

var DOMParser = function() {
	this._path = [];
	this._source = null;
	this._index = 0;
	this._doc = null;
	
	this._line = 0;
	this._char = 0;
	this._lastChar = null;
}

DOMParser._ERR_GENERIC = 	0;
DOMParser._ERR_EOF = 		1;
DOMParser._ERR_ENTITY = 	2;
DOMParser._ERR_ELEMENT = 	3;
DOMParser._ERR_ATTRIBUTE =	4;
DOMParser._ERR_PI = 		5;
DOMParser._ERR_CLOSE = 		6;
DOMParser._ERR_XML = 		7;
DOMParser._ERR_PREFIX =		8;
DOMParser._ERR_DOCTYPE =	9;

DOMParser.prototype.parseFromString = function(str) {
	this._doc = new Document();
	
	this._source = str;
	this._path = [this._doc];
	this._index = -1;
	this._line = 1;
	this._char = 0;
	this._lastChar = null;
	this._parseChildNodes();
	if (this._path.length != 1) { this._error(DOMParser._ERR_EOF); }
	
	return this._doc;
}

/**
 * We are in child nodes area
 */
DOMParser.prototype._parseChildNodes = function() {
	var buffer = "";
	var ch;
	
	while (1) {
		ch = this._getChar();
		if (ch === null) { break; }
		
		if (ch == "<") {
			if (buffer.length) {
				var txt = this._createTextNode(buffer);
				var elm = this._current();
				if (elm != this._doc) { elm.appendChild(txt); }
				buffer = "";
			}
			this._parseNode();
		} else {
			buffer += ch;
		}
	}
	
	if (buffer.length) {
		var txt = this._createTextNode(buffer);
		var elm = this._current();
		if (elm != this._doc) { elm.appendChild(txt); }
	}
}

/**
 * We just started a non-text node
 */
DOMParser.prototype._parseNode = function() {
	var ch = this._getChar();
	if (ch === null) {
		this._error(DOMParser._ERR_EOF);
	} else if (ch == "!") { /* CDATA or comment or DOCTYPE */
		var str = this._getChars(2);
		if (str == "--") { /* comment */
			this._parseComment();
		} else if (str.toUpperCase() == "[C") { /* cdata */
			str = this._getChars(5);
			if (str.toUpperCase() == "DATA[") {
				this._parseCDATASection();
			} else { this._error(DOMParser._ERR_GENERIC); }
		} else if (str.toUpperCase() == "DO") { /* doctype */
			str = this._getChars(5);
			if (str.toUpperCase() == "CTYPE") {
				this._parseDocumentType();
			} else { this._error(DOMParser._ERR_GENERIC); }
		} else { this._error(DOMParser._ERR_GENERIC); }
	} else if (ch == "?") { /* processing intruction */
		this._parseProcessingInstruction();
	} else if (ch == "/") { /* element end */
		this._parseElementEnd();
	} else { this._parseElement(ch); }
}

/**
 * We just started a DOCTYPE declaration
 */
DOMParser.prototype._parseDocumentType = function() {
	var publicId = null;

	var ch = this._getChar();
	if (!ch.match(/\s/)) { this._error(DOMParser._ERR_GENERIC); }
	
	var ch = this._parseWhitespace();
	var name = this._parseNodeName(ch);
	if (!name) { this._error(DOMParser._ERR_DOCTYPE); }
	
	var doctype = this._doc.createDocumentType(name, null, null);
	this._doc.doctype = doctype;
	if (this._lastChar == ">") { return; }
	
	var ch = this._parseWhitespace();
	if (ch == ">") { return; }

	if (ch == "'" || ch == '"') {
		doctype.systemId = this._parseQuoted(ch);
	} else {
		var tmp = this._parseNodeName(ch);
		if (tmp.toLowerCase() != "public") { this._error(DOMParser._ERR_DOCTYPE); }
		if (!this._lastChar.match(/\s/)) { this._error(DOMParser._ERR_DOCTYPE); }
		
		var ch = this._parseWhitespace();
		if (ch == ">") { this._error(DOMParser._ERR_DOCTYPE); }
		doctype.publicId = this._parseQuoted(ch);
		
		var ch = this._parseWhitespace();
		if (ch == ">") { this._error(DOMParser._ERR_DOCTYPE); }		
		doctype.systemId = this._parseQuoted(ch);
		
	}
	var ch = this._parseWhitespace();
	if (ch == ">") { return; }
	
	if (ch == "[") {
		this._parseUntil("]>");
	} else { this._error(DOMParser._ERR_DOCTYPE); }
}

/**
 * We just started a comment
 */
DOMParser.prototype._parseComment = function() {
	var data = this._parseUntil("-->");
	var c = this._doc.createComment(data);
	this._current().appendChild(c);
}

/**
 * We just started a CDATA
 */
DOMParser.prototype._parseCDATASection = function() {
	var data = this._parseUntil("]]>");
	var c = this._doc.createCDATASection(data);
	this._current().appendChild(c);
}

/**
 * We just started a PI
 */
DOMParser.prototype._parseProcessingInstruction = function() {
	var name = this._parseNodeName();
	if (!name) { this._error(DOMParser._ERR_PI); }
	
	var data = this._parseUntil("?>");
	var c = this._doc.createProcessingInstruction(name, data);
	
	var elm = this._current();
	if (name.toLowerCase() == "xml") {
		if (elm != this._doc) { this._error(DOMParser._ERR_XML); }
		this._xmlProlog(data);
	} else {
		elm.appendChild(c);
	}
}

DOMParser.prototype._xmlProlog = function(str) {
	var reVersion = /version\s*=\s*(['"])(.+?)\1/;
	var reEncoding = /encoding\s*=\s*(['"])(.+?)\1/;
	
	var r = str.match(reVersion);
	if (r) { this._doc.xmlVersion = r[2]; }
	var r = str.match(reEncoding);
	if (r) { this._doc.xmlEncoding = r[2]; }
}

/**
 * We just encountered element end tag
 */
DOMParser.prototype._parseElementEnd = function() {
	var ch = this._parseWhitespace();
	var name = this._parseNodeName(ch);
	if (!name) { this._error(DOMParser._ERR_GENERIC);}
	
	var elm = this._current();
	if (elm == this._doc || elm.nodeName != name) { this._error(DOMParser._ERR_CLOSE); }
	
	/* close the tag */
	this._path.pop();
	
	/* finish him */
	if (this._lastChar != ">") { this._parseUntil(">"); }
	
}

/**
 * We just encountered element start tag, ch == first character
 */
DOMParser.prototype._parseElement = function(ch) {
	var name = this._parseNodeName(ch);
	if (!name) { this._error(DOMParser._ERR_ELEMENT); }
	
	var elm = this._doc.createElement(name);
	this._current().appendChild(elm);
	this._path.push(elm);
	
	var end = false;
	if (this._lastChar == ">") { end = true; }
	if (this._lastChar == "/") { 
		this._parseAutoclose(); 
		end = true;
	}
	
	/* parse attributes */
	while (!end) {
		var ch = this._parseWhitespace();
		if (ch == ">") { 
			end = true; 
			continue;
		}
		if (ch == "/") { 
			this._parseAutoclose(); 
			end = true;
			continue;
		}
		this._parseAttribute(ch);
	}
	
	this._resolveNamespace(elm);
	for (var i=0;i<elm.attributes.length;i++) {
		var a = elm.attributes[i];
		if (a.prefix && a.prefix != "xmlns") { a.namespaceURI = this._resolvePrefix(a.prefix); }
	}
}

/**
 * Parse attribute starting with a given char
 */
DOMParser.prototype._parseAttribute = function(ch) {
	var name = this._parseNodeName(ch);
	if (!name) { this._error(DOMParser._ERR_ATTRIBUTE); }
	
	if (this._lastChar != "=") { 
		if (!this._lastChar.match(/\s/)) { this._error(DOMParser._ERR_GENERIC); }
		var ch = this._parseWhitespace();
		if (ch != "=") { this._error(DOMParser._ERR_GENERIC); }
	}
	var separator = this._parseWhitespace();
	
	var value = this._parseQuoted(separator);
	value = this._unescapeEntities(value);
	
	var a = this._doc.createAttribute(name);
	if (a.prefix == "xmlns" || a.nodeName == "xmlns") { a.namespaceURI = "http://www.w3.org/2000/xmlns/"; }
	a.nodeValue = value;
	
	this._current().setAttributeNode(a);
}

DOMParser.prototype._resolveNamespace = function(elm) {
	if (elm.prefix) { /* search for prefix definition */
		elm.namespaceURI = this._resolvePrefix(elm.prefix);
		return;
	}

	for (var i=0;i<elm.attributes.length;i++) { /* search for xmlns attribute */
		var a = elm.attributes[i];
		if (a.nodeName == "xmlns") { 
			elm.namespaceURI = a.nodeValue; 
			return;
		}
	}

	for (var i=this._path.length-1;i>0;i--) { /* search upwards */
		var parent = this._path[i];
		if (parent.getAttribute("xmlns")) { 
			elm.namespaceURI = parent.namespaceURI;
			return;
		}
	}
}

DOMParser.prototype._resolvePrefix = function(prefix) {
	var a = "xmlns:"+prefix;
	for (var i=this._path.length-1;i>0;i--) { /* search upwards */
		var elm = this._path[i];
		var att = elm.getAttribute(a);
		if (att) { return att; }
	}
	this._error(DOMParser._ERR_PREFIX);
}

/**
 * Parse element name
 */
DOMParser.prototype._parseNodeName = function(initial) {
	var re = /^[a-z0-9_:-]+$/i;
	var str = initial || "";
	while (1) {
		if (str.length && !str.match(re)) {
			if (str.length > 1) {
				return str.substring(0, str.length-1);
			} else { return str; }
		}
		var ch = this._getChar();
		if (ch === null) { this._error(DOMParser._ERR_EOF); }
		str += ch;
	}
}

/**
 * Parse element autoclose part
 */
DOMParser.prototype._parseAutoclose = function() {
	var ch = this._getChar();
	if (ch == ">") {
		this._path.pop();
	} else {
		this._error(DOMParser._ERR_GENERIC);
	}
}

/**
 * Create text node from a PCDATA
 */
DOMParser.prototype._createTextNode = function(str) {
	var s = this._unescapeEntities(str);
	return this._doc.createTextNode(s);
}

/**
 * 
 */
DOMParser.prototype._parseQuoted = function(separator) {
	if (separator != "'" && separator != '"') { this._error(DOMParser._ERR_GENERIC); }
	return this._parseUntil(separator);
}

/**
 * Read string until a terminator is found
 */
DOMParser.prototype._parseUntil = function(end) {
	var str = "";
	var e = end.charAt(end.length-1);
	while (1) {
		var ch = this._getChar();
		if (ch === null) { this._error(DOMParser._ERR_EOF); }
		str += ch;
		if (ch == e) {
			if (str.substring(str.length-end.length) == end) { break; }
		}
	}
	return str.substring(0, str.length-end.length);
}

/**
 * Parse whitespace, return first non-white char
 */
DOMParser.prototype._parseWhitespace = function() {
	var ch;
	while (1) {
		ch = this._getChar();
		if (ch === null) { this._error(DOMParser._ERR_EOF); }
		if (!ch.match(/\s/)) { return ch; }
	}
}

/**
 * Convert entities
 */
DOMParser.prototype._unescapeEntities = function(str) {
	var tr = {
		"lt": "<",
		"gt": ">",
		"quot": '"',
		"apos": "'",
		"amp": "&"
	}

	var self = this;
	return str.replace(/&(#(x)?)?([0-9a-z]+)(.)/i, function (str, hash, x, entity, end) {
		if (end != ";") { self._error(DOMParser._ERR_ENTITY, str); } /* error */
		
		if (hash) { /* numeric */
			return String.fromCharCode(parseInt(entity, (x ? 16 : 10)));
		} else { /* text */
			if (entity in tr) { return tr[entity]; }
			self._error(DOMParser._ERR_ENTITY, str);
		}
	});
}

/**
 * Get one char from the input stream
 */
DOMParser.prototype._getChar = function() {
	if (this._index+1 == this._source.length) { return null; }
	this._index++;
	this._char = this._index+1;
	var ch = this._source.charAt(this._index);
	
	if (this._lastChar == "\n") {
		this._char = 1;
		this._line++;
	}
	
	this._lastChar = ch;
	return ch;
}

/**
 * Get N chars from the input stream
 */
DOMParser.prototype._getChars = function(amount) {
	var str = "";
	for (var i=0;i<amount;i++) { 
		var ch = this._getChar();
		if (ch !== null) { str += ch; }
	}
	return str;
}

DOMParser.prototype._error = function(type, data) {
	var where = " (line "+this._line+", char "+this._char+")";
	var reason = "";
	
	switch (type) {
		case DOMParser._ERR_GENERIC:
			reason = "Parsing error";
		break;
		
		case DOMParser._ERR_EOF:
			reason = "Unexpected end of document";
		break;

		case DOMParser._ERR_ENTITY:
			reason = "Unknown entity '"+data+"'";
		break;

		case DOMParser._ERR_ELEMENT:
			reason = "Undefined element name";
		break;

		case DOMParser._ERR_ATTRIBUTE:
			reason = "Undefined attribute name";
		break;
		
		case DOMParser._ERR_PI:
			reason = "Undefined processing instruction";
		break;

		case DOMParser._ERR_CLOSE:
			reason = "Invalid closing element name";
		break;

		case DOMParser._ERR_XML:
			reason = "XML prolog error";
		break;

		case DOMParser._ERR_PREFIX:
			reason = "Prefix not bound to namespace";
		break;

		case DOMParser._ERR_DOCTYPE:
			reason = "Doctype declaration error";
		break;

		default:
			reason = "Unknown error";
		break;
	}
	
	throw new Error(reason + where);
}

DOMParser.prototype._current = function() {
	return this._path[this._path.length-1];
}

/* ------------------------------------------------------------- */

exports.Document = Document;
exports.XMLSerializer = XMLSerializer;
exports.DOMParser = DOMParser;
exports.Node = Node;

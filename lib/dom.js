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

Node.prototype.__defineGetter__("firstChild", function() { return this.childNodes[0]; });
Node.prototype.__defineGetter__("lastChild", function() { return this.childNodes[this.childNodes.length-1]; });
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
	var index = this.childNodes.indexOf(referenceNode);
	if (index == -1) { throw new Error("Cannot insert before non-existent child"); }
	if (!referenceNode) { return this.appendChild(newNode); }
	
	newNode._removeReferences();
	this.childNodes.splice(index, 0, newNode);
	newNode._addReferences();
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

Node.prototype._serialize = function(depth) {
	var str = "";
	
	if (this.ownerDocument.pretty) {
		for (var i=0;i<depth;i++) { str += "\t"; }
	}
	
	str += "<" + this.nodeName;
	var arr = [];
	for (var i=0;i<this.attributes.length;i++) {
		arr.push(this.attributes[i]._serialize(depth));
	}
	if (arr.length) { str += " "+arr.join(" "); }
	
	if (this.childNodes.length) {
		str += ">";
		str += this._serializeChildNodes(depth+1);
		str += "</"+this.nodeName+">";
	} else {
		str += "/>";
	}
	
	if (this.ownerDocument.pretty) {
		str += "\n";
	}
	
	return str;
}

Node.prototype._serializeChildNodes = function(depth) {
	var str = "";
	for (var i=0;i<this.childNodes.length;i++) {
		str += this.childNodes[i]._serialize(depth);
	}
	return str;
}

Node.prototype._escapeEntities = function(str) {
	return str
			.replace(/&/g, "&amp;")
			.replace(/'/g, "&apos;") // '
			.replace(/"/g, "&quot;") // "
			.replace(/</g, "&lt;")
			.replace(/>/g, "&gt;");
}

/* ------------------------------------------------------------- */

var Attr = function(ownerDocument, name) {
	Node.call(this, ownerDocument, name);
	this.nodeType = Node.ATTRIBUTE_NODE;
	this.ownerElement = null;
}

Attr.prototype.__defineGetter__("localName", function() { return this._localName(); });
Attr.prototype.__defineGetter__("prefix", function() { return this._prefix(); });
Attr.prototype.__defineGetter__("value", function() { return this.nodeValue; });
Attr.prototype.__defineGetter__("nodeValue", function() { return this._getNodeValue(); });
Attr.prototype.__defineSetter__("nodeValue", function(value) { return this._setNodeValue(value); });

var tmp = function(){}; tmp.prototype = Node.prototype; Attr.prototype = new tmp();

Attr.prototype.cloneNode = function(deep) {
	var attr = new Attr(this.ownerDocument, this.nodeName);
	if (this.childNodes.length) { attr.nodeValue = this.nodeValue; }
	return attr;
}

Attr.prototype._serialize = function(depth) {
	return this._escapeEntities(this.nodeName) + '="' + this._escapeEntities(this.nodeValue) + '"';
}

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
		return this.nodeName;
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
		if (att.nodeName == name) { return arr; }
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

/* ------------------------------------------------------------- */

var Text = function(ownerDocument, value) {
	CharacterData.call(this, ownerDocument, "#text", value);
	this.nodeType = Node.TEXT_NODE;
}

var tmp = function(){}; tmp.prototype = CharacterData.prototype; Text.prototype = new tmp();

Text.prototype.cloneNode = function(deep) {
	return new Text(this.ownerDocument, this.nodeValue);
}

Text.prototype._serialize = function(depth) {
	return this._escapeEntities(this.nodeValue);
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

CDATASection.prototype._serialize = function(depth) {
	return "<![CDATA[" + this.nodeValue + "]]>";
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

Comment.prototype._serialize = function(depth) {
	return "<!--" + this.nodeValue + "-->";
}

/* ------------------------------------------------------------- */

var Document = function() {
	Node.call(this, null, "#document");
	this.nodeType = Node.DOCUMENT_NODE;
	this.xmlEncoding = "utf-8";
	this.xmlVersion = "1.0";
	
	this.pretty = true;
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

Document.prototype.createComment = function(name, value) {
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

Document.prototype.getElementsByTagName = Element.prototype.getElementsByTagName;

Document.prototype._documentElement = function() {
	for (var i=0;i<this.childNodes.length;i++) {
		var node = this.childNodes[i];
		if (node.nodeType == Node.ELEMENT_NODE) { return node; }
	}
	return null;
}

Document.prototype._serialize = function() {
	var str = "";
	str += '<xml version="'+this.xmlVersion+'" encoding="'+this.xmlEncoding+'">';
	
	if (this.pretty) { str += "\n"; }
	
	str += this._serializeChildNodes(0);
	return str;
}

/* ------------------------------------------------------------- */

var ProcessingInstruction = function(ownerDocument, name, value) {
	Node.call(this, ownerDocument, name);
	this.nodeType = Node.PROCESSING_INSTRUCTION_NODE;
}

ProcessingInstruction.prototype.__defineGetter__("target", function() { return this.nodeName; });
ProcessingInstruction.prototype.__defineGetter__("data", function() { return this.nodeValue; });

var tmp = function(){}; tmp.prototype = Node.prototype; ProcessingInstruction.prototype = new tmp();

ProcessingInstruction.prototype.cloneNode = function(deep) {
	return new ProcessingInstruction(this.ownerDocument, this.nodeName, this.nodeValue);
}

ProcessingInstruction.prototype._serialize = function(depth) {
	return str = "<?" + this.nodeName + " " + this.nodeValue + " ?>\n";
}

/* ------------------------------------------------------------- */

var XMLSerializer = function() {
}

XMLSerializer.prototype.serializeToString = function(document) {
	return document._serialize();
}

/* ------------------------------------------------------------- */

exports.Document = Document;
exports.XMLSerializer = XMLSerializer;

/**
 * This file tests the JS DOM module.
 */

var assert = require("assert");
var DOM = require("dom");

var XMLSTR = '<!DOCTYPE a PUBLIC "b" "c">\n';
XMLSTR += '<?xml version="1.0" encoding="utf-8"?>\n';
XMLSTR += '<?xml-stylesheet href="test.xsl"?>\n';
XMLSTR += '<a x="y">';
XMLSTR += '<b z="&amp;"><![CDATA[world]]></b><!--hello--></a>\n';

function setup() {
	var d = new DOM.Document();
	return d;
}

function setupFull() {
	var d = setup();
	
	var xsl = d.createProcessingInstruction('xml-stylesheet', 'href="test.xsl"');
	d.appendChild(xsl);
	
	var dt = d.createDocumentType("a", "b", "c");
	d.doctype = dt;
	
	var node1 = d.createElement("a");
	var node2 = d.createElement("b");
	d.appendChild(node1);
	d.documentElement.appendChild(node2);
	
	node1.setAttribute("x", "y");
	node2.setAttribute("z", "&");
	
	var c = d.createComment("hello");
	node1.appendChild(c);
	
	var cd = d.createCDATASection("world");
	node2.appendChild(cd);
	
	return d;
}

exports.testAppend = function() {
	var d = setup();
	
	var elm = d.createElement("test");
	assert.assertEquals("New node without parent", null, elm.parentNode);
	
	d.appendChild(elm);
	assert.assertEquals("Appended node with parent", d, elm.parentNode);
	
	var elm2 = d.createElement("test2");
	elm2.appendChild(elm);
	assert.assertEquals("Node removed from document", 0, d.childNodes.length);
	assert.assertEquals("Node removed from document", null, d.firstChild);
	assert.assertEquals("Node appended to other node", elm2, elm.parentNode);
}

exports.testInsert = function() {
	var d = setup();
	
	var elm1 = d.createElement("test");
	var elm2 = d.createElement("test");
	var elm3 = d.createElement("test");
	
	d.appendChild(elm1);
	d.appendChild(elm3);
	d.insertBefore(elm2, elm3);
	
	assert.assertEquals("Node inserted before node", elm2, d.childNodes[1]);
	assert.assertEquals("Sibling relation #1", elm2, elm3.previousSibling);
	assert.assertEquals("Sibling relation #2", elm2, elm1.nextSibling);
	
	var d = setup();
	var elm1 = d.createElement("test");
	var elm2 = d.createElement("test");
	var elm3 = d.createElement("test");
	d.appendChild(elm1);
	d.appendChild(elm2);
	d.insertBefore(elm3, null);
	
	assert.assertEquals("Null insert = append", elm3, d.childNodes[2]);
	assert.assertEquals("Sibling relation #1", elm2, elm3.previousSibling);
	assert.assertEquals("Sibling relation #2", elm3, elm2.nextSibling);
	
}

exports.testSerialize = function() {
	var d = setupFull();
	var ser = new DOM.XMLSerializer();

	var str = ser.serializeToString(d);
	assert.assertEquals("Kitchen sink serialization", XMLSTR, str);
}

exports.testClone = function() {
	var d = setupFull();
	var ser = new DOM.XMLSerializer();
	
	var clone = d.cloneNode(true);
	str = ser.serializeToString(clone);
	assert.assertEquals("Document deep clone", XMLSTR, str);
}

exports.testParse = function() {
	var d = setupFull();
	var ser = new DOM.XMLSerializer();
	var par = new DOM.DOMParser();
	
	var doc = par.parseFromString(XMLSTR);
	var str = ser.serializeToString(doc);
	
	assert.assertEquals("XML parsing", XMLSTR, str);
}

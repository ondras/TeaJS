/**
 * This file tests the JS DOM module.
 */

var assert = require("assert");
var DOM = require("dom");

var XMLSTR = '<!DOCTYPE a PUBLIC "b" "c">\n';
XMLSTR += '<?xml version="1.0" encoding="utf-8"?>\n';
XMLSTR += '<?xml-stylesheet href="test.xsl"?>\n';
XMLSTR += '<a x="y">';
XMLSTR += '<b z="&amp;hi"><![CDATA[world]]></b><!--hello--></a>\n';

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
	node2.setAttribute("z", "&hi");
	
	var c = d.createComment("hello");
	node1.appendChild(c);
	
	var cd = d.createCDATASection("world");
	node2.appendChild(cd);
	
	return d;
}

exports.testAppend = function() {
	var d = setup();
	
	var elm = d.createElement("test");
	assert.equal(elm.parentNode, null, "New node without parent");
	
	d.appendChild(elm);
	assert.equal(elm.parentNode, d, "Appended node with parent");
	
	var elm2 = d.createElement("test2");
	elm2.appendChild(elm);
	assert.equal(d.childNodes.length, 0, "Node removed from document");
	assert.equal(d.firstChild, null, "Node removed from document");
	assert.equal(elm.parentNode, elm2, "Node appended to other node");
}

exports.testInsert = function() {
	var d = setup();
	
	var elm1 = d.createElement("test");
	var elm2 = d.createElement("test");
	var elm3 = d.createElement("test");
	
	d.appendChild(elm1);
	d.appendChild(elm3);
	d.insertBefore(elm2, elm3);
	
	assert.equal(d.childNodes[1], elm2, "Node inserted before node");
	assert.equal(elm3.previousSibling, elm2, "Sibling relation #1");
	assert.equal(elm1.nextSibling, elm2, "Sibling relation #2");
	
	var d = setup();
	var elm1 = d.createElement("test");
	var elm2 = d.createElement("test");
	var elm3 = d.createElement("test");
	d.appendChild(elm1);
	d.appendChild(elm2);
	d.insertBefore(elm3, null);
	
	assert.equal(d.childNodes[2], elm3, "Null insert = append");
	assert.equal(elm3.previousSibling, elm2, "Sibling relation #1");
	assert.equal(elm2.nextSibling, elm3, "Sibling relation #2");
	
}

exports.testSerialize = function() {
	var d = setupFull();
	var ser = new DOM.XMLSerializer();

	var str = ser.serializeToString(d);
	assert.equal(str, XMLSTR, "Kitchen sink serialization");
}

exports.testClone = function() {
	var d = setupFull();
	var ser = new DOM.XMLSerializer();
	
	var clone = d.cloneNode(true);
	str = ser.serializeToString(clone);
	assert.equal(str, XMLSTR, "Document deep clone");
}

exports.testParse = function() {
	var d = setupFull();
	var ser = new DOM.XMLSerializer();
	var par = new DOM.DOMParser();
	
	var doc = par.parseFromString(XMLSTR);
	var str = ser.serializeToString(doc);
	
	assert.equal(str, XMLSTR, "XML parsing");
}

exports.testBadEntities = function() {
	var str1 = "<root a='&test;'/>";
	var str2 = "<root a='&amp'/>";
	var par = new DOM.DOMParser();
	
	assert.throws(function() {
		par.parseFromString(str1);
	}, null, "Non-existent entity");
	
	assert.throws(function() {
		par.parseFromString(str2);
	}, null, "Unfinished entity");
}

/**
 * This file tests the JS DOM module.
 */

var assert = require("assert");
var DOM = require("dom");

function setup() {
	var d = new DOM.Document();
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

exports.testSerializeClone = function() {
	var d = setup();
	d.pretty = false;
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
	
	var ser = new DOM.XMLSerializer();
	var str = ser.serializeToString(d);
	
	var ref = '<xml version="1.0" encoding="utf-8">';
	ref += '<a x="y">';
	ref += '<b z="&amp;"><![CDATA[world]]></b><!--hello--></a>';
	
	assert.assertEquals("Kitchen sink serialization", ref, str);
	var clone = d.cloneNode(true);
	str = ser.serializeToString(clone);
	assert.assertEquals("Document deep clone", ref, str);
}


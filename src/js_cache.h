/*
 * There are multiple caching levels in v8cgi.
 * - getHandle checks file's MTIME and provides source code / DSO handle
 * - getScript checks file's MTIME and provides compiled source code
 * - getExports returns module's "exports" object. No checks are performed, exports are valid through whole request.
 */

#ifndef _JS_CACHE_H
#define _JS_CACHE_H

#include <string>
#include <map>
#include "v8.h"

class Cache {
public:
	void * getHandle(std::string filename);
	v8::Handle<v8::Script> getScript(std::string filename, bool wrap);
	v8::Handle<v8::Object> getExports(std::string filename);
	void clearExports();
	void addExports(std::string filename, v8::Handle<v8::Object> obj);
	void removeExports(std::string filename);

private:
	typedef std::map<std::string,time_t> TimeValue;
	typedef std::map<std::string,void*> HandleValue;
	typedef std::map<std::string,v8::Persistent<v8::Script> > ScriptValue;
	typedef std::map<std::string, v8::Persistent<v8::Object> > ExportsValue;

	/* mtimes */
	TimeValue modified;
	/* DSO handles */
	HandleValue handles;
	/* compiled scripts */
	ScriptValue scripts;
	/* exports */
	ExportsValue exports;
	
	std::string getSource(std::string filename, bool wrap);
	void mark(std::string filename);
	bool isCached(std::string filename);
	void erase(std::string filename);
};

#endif

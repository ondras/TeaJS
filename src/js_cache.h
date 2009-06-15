#ifndef _JS_CACHE_H
#define _JS_CACHE_H

#include <string>
#include <map>
#include "v8.h"

class Cache {
public:
	std::string getSource(std::string filename, bool wrap);
	void * getHandle(std::string filename);
	v8::Persistent<v8::Script> getScript(std::string filename, bool wrap);

private:
	typedef std::map<std::string,time_t> TimeValue;
	typedef std::map<std::string,std::string> SourceValue;
	typedef std::map<std::string,void*> HandleValue;
	typedef std::map<std::string,v8::Persistent<v8::Script> > ScriptValue;
	TimeValue modified;
	SourceValue sources;
	HandleValue handles;
	ScriptValue scripts;
	void mark(std::string filename);
	bool isCached(std::string filename);
	void erase(std::string filename);
};

#endif

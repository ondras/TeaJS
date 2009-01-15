#ifndef _JS_CACHE_H
#define _JS_CACHE_H

#include <string>
#include <map>

class Cache {
public:
	std::string getJS(std::string filename);
	void* getHandle(std::string filename);

private:
	typedef std::map<std::string,time_t> TimeValue;
	typedef std::map<std::string,std::string> JSValue;
	typedef std::map<std::string,void*> HandleValue;
	TimeValue modified;
	JSValue sources;
	HandleValue handles;
	bool isCached(std::string filename);
	void erase(std::string filename);
};

#endif

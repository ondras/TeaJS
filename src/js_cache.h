#ifndef _JS_CACHE_H
#define _JS_CACHE_H

#include <string>
#include <map>

class Cache {
private:
	std::map<std::string,time_t> modified;
	std::map<std::string,std::string> sources;
	std::map<std::string,void*> handles;
	bool isCached(std::string filename);
	void erase(std::string filename);
public:
	std::string getJS(std::string filename);
	void* getHandle(std::string filename);
};

#endif

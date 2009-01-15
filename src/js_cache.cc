#include <string>
#include <map>
#include <sys/types.h>
#include <sys/stat.h>

#ifndef windows
#   include <dlfcn.h>
#else
#   include <windows.h>
#   define dlopen(x,y) (void*)LoadLibrary(x)
#   define dlsym(x,y) (void*)GetProcAddress((HMODULE)x,y)
#   define dlclose(x) FreeLibrary((HMODULE)x)
#endif

#include "js_cache.h"

bool Cache::isCached(std::string filename) {
	struct stat st;
	int result = stat(filename.c_str(), &st);
	if (result != 0) { return false; }	

	std::map<std::string,time_t>::iterator it = modified.find(filename);
	if (it == modified.end()) { /* not seen yet */
		modified[filename] = st.st_mtime;
		return false; 
	}
	
	if (it->second != st.st_mtime) { /* was modified */
		erase(filename);
		modified[filename] = st.st_mtime;
		return false;
	}
	return true;
}

void Cache::erase(std::string filename) {
	std::map<std::string,std::string>::iterator it1 = sources.find(filename);
	if (it1 != sources.end()) { sources.erase(it1); }

	std::map<std::string,void*>::iterator it2 = handles.find(filename);
	if (it2 != handles.end()) { 
		dlclose(it2->second);
		handles.erase(it2); 
	}
}

std::string Cache::getJS(std::string filename) {
	if (isCached(filename)) {
		std::map<std::string,std::string>::iterator it = sources.find(filename);
		return it->second;
	} else {
		FILE * file = fopen(filename.c_str(), "rb");
		if (file == NULL) { return std::string(""); }
		fseek(file, 0, SEEK_END);
		size_t size = ftell(file);
		rewind(file);
		char* chars = new char[size + 1];
		chars[size] = '\0';
		for (unsigned int i = 0; i < size;) {
			size_t read = fread(&chars[i], 1, size - i, file);
			i += read;
		}
		fclose(file);
		std::string source = chars;
		delete[] chars;
													  
		/* remove shebang line */
		if (source.find('#',0) == 0 && source.find('!',1) == 1 ) {
			unsigned int pfix = source.find('\n',0);
			source.erase(0,pfix);
		};
		
		sources[filename] = source;
		return source;
	}
};

void * Cache::getHandle(std::string filename) {
	if (isCached(filename)) {
		std::map<std::string,void*>::iterator it = handles.find(filename);
		return it->second;
	} else {
		void * handle = dlopen(filename.c_str(), RTLD_LAZY);
		if (!handle) { return NULL; }
		handles[filename] = handle;
		return handle;
	}
};

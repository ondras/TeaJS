#include <js_path.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

// chdir()
#ifndef HAVE_CHDIR
#	include <direct.h>
#	define chdir(name) _chdir(name)
#endif

// getcwd()
#ifndef HAVE_GETCWD
#	include <direct.h>
#	define getcwd(name, bytes) _getcwd(name, bytes)
#endif

std::string path_normalize(std::string path, std::string base) {
	std::string result;
	if (path_isabsolute(path)) {
		result = path;
	} else {
		if (base.length()) {
			result = base;
			result += '/';
		}
		result += path;
	}
	
	size_t pos = 0;
	int state = 1; /* 0 bad, 1 just after dirname, 2 dot  */
	while (pos != result.length()) {
		char ch = result.at(pos);
		switch (ch) {
			case '/':
			case '\\':
				if (state == 0) { state = 1; }
				if (state == 2) { 
					pos -= 2;
					result.erase(pos, 2);
				}
			break;
			
			case '.': 
				if (state == 1) { 
					state = 2; 
				} else {
					state = 0;
				}
			break;
			default: state = 0; break;
		}
		pos++;
	}
	
	return result;
}

std::string path_filename(std::string path) {
	size_t pos = path_lastslash(path);
	if (pos != std::string::npos) { path.erase(0, pos+1); }
	return path;
}

std::string path_dirname(std::string path) {
	size_t pos = path_lastslash(path);
	if (pos != std::string::npos) { path.erase(pos, path.length()-pos); }
	return path;
}

size_t path_lastslash(std::string path) {
	size_t pos = path.find_last_of('/');
	if (pos == std::string::npos) { pos = path.find_last_of('\\'); }
	return pos;
}

bool path_isabsolute(std::string path) {
#ifdef windows
	size_t pos = path.find(':');
	return (pos != std::string::npos);
#else
	if (path.length() == 0) { return false; }
	char ch = path.at(0);
	return (ch == '/');
#endif
}
 
bool path_file_exists(std::string path) {
	struct stat st;
	if (stat(path.c_str(), &st) != 0) { return false; } /* does not exist */
	if (st.st_mode & S_IFDIR) { return false; } /* is directory */
	return true;
}

bool path_dir_exists(std::string path) {
	struct stat st;
	if (stat(path.c_str(), &st) != 0) { return false; } /* does not exist */
	if (st.st_mode & S_IFDIR) { return true; } /* is directory */
	return false;
}

std::string path_getcwd() {
	return getcwd(NULL, 0);
}

void path_chdir(std::string dir) {
	chdir(dir.c_str());
}

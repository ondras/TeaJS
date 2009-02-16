#include <js_path.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

std::string path_normalize(std::string path, std::string base) {
	std::string result;
	if (path_isabsolute(path)) {
		result = path;
	} else {
		result = base;
		result += '/';
		result += path;
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
 
bool path_exists(std::string path) {
	struct stat st;
	if (stat(path.c_str(), &st) != 0) { return false; } /* does not exist */
	if (st.st_mode & S_IFDIR) { return false; } /* is directory */
	return true;
}

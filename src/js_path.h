#ifndef _JS_PATH_H
#define _JS_PATH_H

#include <string>

size_t path_lastslash(std::string path);
std::string path_normalize(std::string path, std::string base);
std::string path_filename(std::string path);
std::string path_dirname(std::string path);
bool path_isabsolute(std::string path);
bool path_file_exists(std::string path);
bool path_dir_exists(std::string path);
std::string path_getcwd();
void path_chdir(std::string dir);

#endif 

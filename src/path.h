/**
 * Utility functions for path manipulation.
 * Not (yet) exposed to public API, used mainly for module loading.
 */

#ifndef _JS_PATH_H
#define _JS_PATH_H

#include <string>

/* get index of last (back)slash in a path */
size_t path_lastslash(std::string path);
/* normalize - remove ., .., symlinks */
std::string path_normalize(std::string path);
/* filename component */
std::string path_filename(std::string path);
/* dirname component */
std::string path_dirname(std::string path);
/* is this path absolute? */
bool path_isabsolute(std::string path);
/* is this path an existing file? */
bool path_file_exists(std::string path);
/* is this path an existing directory? */
bool path_dir_exists(std::string path);
/* get current working directory */
std::string path_getcwd();
/* change current working directory */
void path_chdir(std::string dir);

#endif

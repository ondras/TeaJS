#include <v8.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <string>
#include <stdlib.h>
#include "js_macros.h"
#include "js_common.h"

// access()
#ifdef HAVE_UNISTD_H
#	include <unistd.h>
#else
#	include <io.h>
#	define F_OK 0
#	define access(path,mode) _access(path,mode)
#endif

// directory listing
#ifdef HAVE_DIRENT_H
#	include <dirent.h>
#else
#	include <io.h>
#endif

// mkdir()
#ifndef HAVE_MKDIR
#	include <direct.h>
#	define mkdir(name, mode) _mkdir(name)
#endif

// rmdir()
#ifndef HAVE_RMDIR
#	define rmdir(name) _rmdir(name)
#endif

#define TYPE_FILE 0
#define TYPE_DIR 1

v8::Handle<v8::Value> list_items(char * name, int type) {
	v8::HandleScope handle_scope;
	v8::Handle<v8::Array> result = v8::Array::New();
	int cnt = 0;

#ifdef HAVE_DIRENT_H
	DIR * dp;
	struct dirent * ep;
	int cond = (type == TYPE_FILE ? DT_REG : DT_DIR);
	
	dp = opendir(name);
	if (dp == NULL) { return JS_EXCEPTION("Directory cannot be opened"); }
	while ((ep = readdir(dp))) { 
		if (ep->d_type == cond) {
			std::string name = ep->d_name;
			if (type == TYPE_FILE) {
				result->Set(JS_INT(cnt++), JS_STR(ep->d_name));
			} else if (name != "." && name != "..") {
				result->Set(JS_INT(cnt++), JS_STR(ep->d_name));
			}
		}
	}
	closedir(dp);
#else
	_finddata_t * info = (_finddata_t *) malloc(sizeof(_finddata_t));
	unsigned int value = (type == TYPE_FILE ? 0 : _A_SUBDIR);

	std::string path = name;
	path += "/*";

	intptr_t ptr = _findfirst(path.c_str(), info);
	
	if (ptr != -1L) {
		do {
			if ((info->attrib & _A_SUBDIR) == value) {
				std::string name = info->name;
				if (type == TYPE_FILE) {
					result->Set(JS_INT(cnt++), JS_STR(info->name));
				} else if (name != "." && name != "..") {
					result->Set(JS_INT(cnt++), JS_STR(info->name));
				}
			}
		} while (_findnext(ptr, info) == 0);
		_findclose(ptr);
	}
	free(info);
#endif
	
	return handle_scope.Close(result);
}

JS_METHOD(_directory) {
	if (args.Length() < 1 || args.This()->InternalFieldCount() == 0) {
		return JS_EXCEPTION("Invalid call format. Use 'new Directory(name)'");
	}
	
	SAVE_VALUE(0, args[0]);
	return args.This();
}

JS_METHOD(_create) {
	v8::String::Utf8Value name(LOAD_VALUE(0));
	int mode;
	if (args.Length() == 0) { 
		mode = 0777; 
	} else {
		mode = args[0]->Int32Value();
	}

	int result = mkdir(*name, mode);
	if (result != 0) {
		return JS_EXCEPTION("Cannot create directory");
	}
	
	return args.This();
}

JS_METHOD(_listfiles) {
	v8::String::Utf8Value name(LOAD_VALUE(0));
	return list_items(*name, TYPE_FILE);
}

JS_METHOD(_listdirectories) {
	v8::String::Utf8Value name(LOAD_VALUE(0));
	return list_items(*name, TYPE_DIR);
}

JS_METHOD(_file) {
	if (args.Length() < 1 || args.This()->InternalFieldCount() == 0) {
		return JS_EXCEPTION("Invalid call format. Use 'new File(name)'");
	}
	
	SAVE_VALUE(0, args[0]);
	SAVE_VALUE(1, JS_BOOL(false));
	return args.This();
}

JS_METHOD(_open) {
	if (args.Length() < 1) {
		return JS_EXCEPTION("Bad argument count. Use 'file.open(mode)'");
	}
	v8::String::Utf8Value mode(args[0]);
	v8::String::Utf8Value name(LOAD_VALUE(0));
	v8::Handle<v8::Value> file = LOAD_VALUE(1);
	if (!file->IsFalse()) {
		return JS_EXCEPTION("File already opened");
	}
	
	FILE * f;
	f = fopen(*name, *mode);
	
	if (!f) {
		return JS_EXCEPTION("Cannot open file");
	}
	
	SAVE_PTR(1, f);
	return args.This();
}
		
JS_METHOD(_close) {
	v8::Handle<v8::Value> file = LOAD_VALUE(1);
	
	if (file->IsFalse()) {
		return JS_EXCEPTION("Cannot close non-opened file");
	}
	
	FILE * f = LOAD_PTR(1, FILE *);
	
	fclose(f);
	SAVE_VALUE(1, JS_BOOL(false));
	return args.This();
}

JS_METHOD(_read) {
	v8::Handle<v8::Value> file = LOAD_VALUE(1);
	
	if (file->IsFalse()) {
		return JS_EXCEPTION("File must be opened before reading");
	}
	FILE * f = LOAD_PTR(1, FILE *);
	
	size_t count = 0;
	if (args.Length() && args[0]->IsNumber()) {
		count = args[0]->IntegerValue();
	}
	
	std::string data;
	size_t size = 0;
	if (count == 0) { /* all */
		size_t tmp;
		char * buf = new char[1024];
		do {
			tmp = fread(buf, sizeof(char), sizeof(buf), f);
			size += tmp;
			data.insert(data.length(), buf, tmp);
		} while (tmp == sizeof(buf));
		delete[] buf;
	} else {
		char * tmp = new char[count];
		size = fread(tmp, sizeof(char), count, f);
		data.insert(0, tmp, size);
		delete[] tmp;
	}
	
	if (args.Length() > 1 && args[1]->IsTrue()) {
		return JS_CHARARRAY((char *) data.data(), size);
	} else {
		return JS_STR(data.data(), size);
	}
}

JS_METHOD(_rewind) {
	v8::Handle<v8::Value> file = LOAD_VALUE(1);
	if (file->IsFalse()) {
		return JS_EXCEPTION("File must be opened before rewinding");
	}
	
	FILE * f = LOAD_PTR(1, FILE *);
	rewind(f);

	return args.This();
}

JS_METHOD(_write) {
	v8::Handle<v8::Value> file = LOAD_VALUE(1);
	
	if (file->IsFalse()) {
		return JS_EXCEPTION("File must be opened before writing");
	}
	

	FILE * f = LOAD_PTR(1, FILE *);
	
	
	if (args[0]->IsArray()) {
		v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(args[0]);
		uint32_t len = arr->Length();
		
		int max = 4096;
		int current = 0;
		char * buf = new char[max];
		for (unsigned int i=0;i<len;i++) {
			buf[current++] = (char) arr->Get(JS_INT(i))->IntegerValue();
			if (current == max) {
				fwrite(buf, sizeof(char), current, f);
				current = 0;
			}
		}
		if (current) { fwrite(buf, sizeof(char), current, f); }
		delete[] buf;
	} else {
		v8::String::Utf8Value data(args[0]);
		fwrite(*data, sizeof(char), args[0]->ToString()->Utf8Length(), f);
	}
		
	return args.This();
}

JS_METHOD(_removefile) {
	v8::String::Utf8Value name(LOAD_VALUE(0));
	
	if (remove(*name) != 0) {
		return JS_EXCEPTION("Cannot remove file");
	}
	
	return args.This();
}

JS_METHOD(_removedirectory) {
	v8::String::Utf8Value name(LOAD_VALUE(0));
	
	if (rmdir(*name) != 0) {
		return JS_EXCEPTION("Cannot remove directory");
	}
	
	return args.This();
}

JS_METHOD(_stat) {
	v8::String::Utf8Value name(LOAD_VALUE(0));
	struct stat st;
	if (stat(*name, &st) == 0) {
		v8::Handle<v8::Object> obj = v8::Object::New();
		obj->Set(JS_STR("size"), JS_INT(st.st_size));
		obj->Set(JS_STR("mtime"), JS_INT(st.st_mtime));
		obj->Set(JS_STR("atime"), JS_INT(st.st_atime));
		obj->Set(JS_STR("ctime"), JS_INT(st.st_ctime));
		obj->Set(JS_STR("mode"), JS_INT(st.st_mode));
		obj->Set(JS_STR("uid"), JS_INT(st.st_uid));
		obj->Set(JS_STR("gid"), JS_INT(st.st_gid));
		return obj;
	} else {
		return JS_BOOL(false);
	}
}

v8::Handle<v8::Value> _copy(char * name1, char * name2) {
	size_t size = 0;
	void * data = my_read(name1, &size);
	if (data == NULL) { return JS_EXCEPTION("Cannot open source file"); }
	
	int result = my_write(name2, data, size);
	my_free((char *)data, size);
	
	if (result == -1) { return JS_EXCEPTION("Cannot open target file"); }
	return JS_BOOL(true);
}

JS_METHOD(_movefile) {
	if (args.Length() < 1) {
		return JS_EXCEPTION("Bad argument count. Use 'file.rename(newname)'");
	}
	
	v8::String::Utf8Value name(LOAD_VALUE(0));
	v8::String::Utf8Value newname(args[0]);

	int renres = rename(*name, *newname);

	if (renres != 0) {
		v8::Handle<v8::Value> result = _copy(*name, *newname);
		if (result->IsTrue()) {
			remove(*name);
		} else {
			return result;
		}
	}
	
	SAVE_VALUE(0, args[0]);
	return args.This();	
}

JS_METHOD(_copyfile) {
	if (args.Length() < 1) {
		return JS_EXCEPTION("Bad argument count. Use 'file.copy(newname)'");
	}
	
	v8::String::Utf8Value name(LOAD_VALUE(0));
	v8::String::Utf8Value newname(args[0]);

	v8::Handle<v8::Value> result = _copy(*name, *newname);	
	if (result->IsTrue()) {
		v8::Handle<v8::Value> fargs[] = { args[0] };
		
		v8::Handle<v8::Value> f = JS_GLOBAL->Get(JS_STR("File"));
		v8::Handle<v8::Function> newf = v8::Handle<v8::Function>::Cast(f);
		return newf->NewInstance(1, fargs);
	} else {
		return result;
	}
}

JS_METHOD(_tostring) {
	return LOAD_VALUE(0);
}

JS_METHOD(_exists) {
	v8::String::Utf8Value name(LOAD_VALUE(0));
	int result = access(*name, F_OK);
	return JS_BOOL(result == 0);
}

void setup_io(v8::Handle<v8::Object> target) {
	v8::HandleScope handle_scope;
	
	v8::Handle<v8::FunctionTemplate> ft = v8::FunctionTemplate::New(_file);
	ft->SetClassName(JS_STR("File"));
	v8::Handle<v8::ObjectTemplate> ot = ft->InstanceTemplate();
	ot->SetInternalFieldCount(2); /* filename, handle */

	v8::Handle<v8::ObjectTemplate> pt = ft->PrototypeTemplate();
	pt->Set("open", v8::FunctionTemplate::New(_open));
	pt->Set("read", v8::FunctionTemplate::New(_read));
	pt->Set("rewind", v8::FunctionTemplate::New(_rewind));
	pt->Set("close", v8::FunctionTemplate::New(_close));
	pt->Set("write", v8::FunctionTemplate::New(_write));
	pt->Set("remove", v8::FunctionTemplate::New(_removefile));
	pt->Set("toString", v8::FunctionTemplate::New(_tostring));
	pt->Set("exists", v8::FunctionTemplate::New(_exists));
	pt->Set("move", v8::FunctionTemplate::New(_movefile));
	pt->Set("copy", v8::FunctionTemplate::New(_copyfile));
	pt->Set("stat", v8::FunctionTemplate::New(_stat));

	target->Set(JS_STR("File"), ft->GetFunction());			
	
	v8::Handle<v8::FunctionTemplate> dt = v8::FunctionTemplate::New(_directory);
	dt->SetClassName(JS_STR("Directory"));
	ot = dt->InstanceTemplate();
	ot->SetInternalFieldCount(1); /* dirname */

	pt = dt->PrototypeTemplate();
	pt->Set("create", v8::FunctionTemplate::New(_create));
	pt->Set("listFiles", v8::FunctionTemplate::New(_listfiles));
	pt->Set("listDirectories", v8::FunctionTemplate::New(_listdirectories));
	pt->Set("toString", v8::FunctionTemplate::New(_tostring));
	pt->Set("exists", v8::FunctionTemplate::New(_exists));
	pt->Set("remove", v8::FunctionTemplate::New(_removedirectory));
	pt->Set("stat", v8::FunctionTemplate::New(_stat));

	target->Set(JS_STR("Directory"), dt->GetFunction());
}

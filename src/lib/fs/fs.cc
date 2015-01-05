/**
 * IO library defines File and Directory classes.
 * Some compatibility macros are defined for Win32 environment.
 */

#include <v8.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <string>
#include <stdlib.h>
#include "macros.h"
#include "common.h"
#include "path.h"

#include <unistd.h>
#include <dirent.h>

#ifdef windows
#	define MKDIR(a, b) mkdir(a)
#else
#	define MKDIR mkdir
#endif

#define TYPE_FILE 0
#define TYPE_DIR 1

namespace {

v8::Persistent<v8::Function> file;

/**
 * Generic directory lister
 * @param {char *} name Directory name
 * @param {int} type Type constant - do we list files or directories?
 * @param {args} the function callback args
 */
void list_items(char * name, int type, const v8::FunctionCallbackInfo<v8::Value>& args) {
	v8::HandleScope handle_scope(JS_ISOLATE);
	v8::Handle<v8::Array> result = v8::Array::New(JS_ISOLATE);
	int cnt = 0;

	DIR * dp;
	struct dirent * ep;
	struct stat st;
	std::string path;
	unsigned int cond = (type == TYPE_FILE ? 0 : S_IFDIR);
	
	dp = opendir(name);
	if (dp == NULL) { JS_ERROR("Directory cannot be opened"); return; }
	while ((ep = readdir(dp))) { 
		path = name;
		path += "/";
		path += ep->d_name;
		if (stat(path.c_str(), &st) != 0) { continue; } /* cannot access */
		
		if ((st.st_mode & S_IFDIR) == cond) {
			std::string name = ep->d_name;
			if (type == TYPE_FILE) {
				result->Set(JS_INT(cnt++), JS_STR(ep->d_name));
			} else if (name != "." && name != "..") {
				result->Set(JS_INT(cnt++), JS_STR(ep->d_name));
			}
		}
	}
	closedir(dp);
	args.GetReturnValue().Set(result);
}

JS_METHOD(_directory) {
	ASSERT_CONSTRUCTOR;
	SAVE_VALUE(0, args[0]);
	args.GetReturnValue().Set(args.This());
}

JS_METHOD(_create) {
	v8::String::Utf8Value name(LOAD_VALUE(0));
	int mode;
	if (args.Length() == 0) { 
		mode = 0777; 
	} else {
		mode = args[0]->Int32Value();
	}

	int result = MKDIR(*name, mode);
	if (result != 0) {
		JS_ERROR("Cannot create directory");
		return;
	}

	args.GetReturnValue().Set(args.This());
}

JS_METHOD(_listfiles) {
	v8::String::Utf8Value name(LOAD_VALUE(0));
	list_items(*name, TYPE_FILE, args);
}

JS_METHOD(_listdirectories) {
	v8::String::Utf8Value name(LOAD_VALUE(0));
	list_items(*name, TYPE_DIR, args);
}

JS_METHOD(_isdirectory) {
	v8::String::Utf8Value name(LOAD_VALUE(0));
	args.GetReturnValue().Set(JS_BOOL(path_dir_exists(*name)));
}

JS_METHOD(_file) {
	ASSERT_CONSTRUCTOR;
	
	SAVE_VALUE(0, args[0]);
	SAVE_VALUE(1, JS_BOOL(false));
	args.GetReturnValue().Set(args.This());
}

JS_METHOD(_open) {
	if (args.Length() < 1) {
		JS_TYPE_ERROR("Bad argument count. Use 'file.open(mode)'");
		return;
	}
	v8::String::Utf8Value mode(args[0]);
	v8::String::Utf8Value name(LOAD_VALUE(0));
	v8::Handle<v8::Value> file = LOAD_VALUE(1);
	if (!file->IsFalse()) {
		JS_ERROR("File already opened");
		return;
	}
	
	FILE * f;
	f = fopen(*name, *mode);
	
	if (!f) {
		JS_ERROR("Cannot open file");
		return;
	}
	
	SAVE_PTR(1, f);
	args.GetReturnValue().Set(args.This());
}
		
JS_METHOD(_close) {
	v8::Handle<v8::Value> file = LOAD_VALUE(1);
	
	if (file->IsFalse()) {
		JS_ERROR("Cannot close non-opened file");
		return;
	}
	
	FILE * f = LOAD_PTR(1, FILE *);
	
	fclose(f);
	SAVE_VALUE(1, JS_BOOL(false));
	args.GetReturnValue().Set(args.This());
}

JS_METHOD(_flush) {
	v8::Handle<v8::Value> file = LOAD_VALUE(1);

	if (file->IsFalse()) {
		JS_ERROR("Cannot flush non-opened file");
		return;
	}

	FILE * f = LOAD_PTR(1, FILE *);

	fflush(f);
	args.GetReturnValue().Set(args.This());
}

JS_METHOD(_read) {
	v8::Handle<v8::Value> file = LOAD_VALUE(1);
	
	if (file->IsFalse()) {
		JS_ERROR("File must be opened before reading");
		return;
	}
	FILE * f = LOAD_PTR(1, FILE *);
	
	size_t count = 0;
	if (args.Length() && args[0]->IsNumber()) {
		count = args[0]->IntegerValue();
	}
	
	READ(f, count, args);
}

JS_METHOD(_readline) {
	v8::Handle<v8::Value> file = LOAD_VALUE(1);
	
	if (file->IsFalse()) {
		JS_ERROR("File must be opened before reading");
		return;
	}
	FILE * f = LOAD_PTR(1, FILE *);
	
	int size = args[1]->IntegerValue();
	if (size < 1) { size = 0xFFFF; }
	
	READ_LINE(f, size, args);
}

JS_METHOD(_rewind) {
	v8::Handle<v8::Value> file = LOAD_VALUE(1);
	if (file->IsFalse()) {
		JS_ERROR("File must be opened before rewinding");
		return;
	}
	
	FILE * f = LOAD_PTR(1, FILE *);
	rewind(f);

	args.GetReturnValue().Set(args.This());
}

JS_METHOD(_iseof) {
	v8::Handle<v8::Value> file = LOAD_VALUE(1);
	if (file->IsFalse()) {
		JS_ERROR("File must be opened before an EOF check");
		return;
	}
	FILE * f = LOAD_PTR(1, FILE *);

	args.GetReturnValue().Set(JS_BOOL(feof(f) != 0));
}

JS_METHOD(_write) {
	v8::Handle<v8::Value> file = LOAD_VALUE(1);
	
	if (file->IsFalse()) {
		JS_ERROR("File must be opened before writing");
		return;
	}
	
	FILE * f = LOAD_PTR(1, FILE *);
	
	WRITE(f, args[0]);
	args.GetReturnValue().Set(args.This());
}

JS_METHOD(_writeline) {
	v8::Handle<v8::Value> file = LOAD_VALUE(1);
	
	if (file->IsFalse()) {
		JS_ERROR("File must be opened before writing");
		return;
	}
	
	FILE * f = LOAD_PTR(1, FILE *);
	
	WRITE_LINE(f, args[0]);
	args.GetReturnValue().Set(args.This());
}

JS_METHOD(_removefile) {
	v8::String::Utf8Value name(LOAD_VALUE(0));
	
	if (remove(*name) != 0) {
		JS_ERROR("Cannot remove file");
		return;
	}

	args.GetReturnValue().Set(args.This());
}

JS_METHOD(_removedirectory) {
	v8::String::Utf8Value name(LOAD_VALUE(0));
	
	if (rmdir(*name) != 0) {
		JS_ERROR("Cannot remove directory");
		return;
	}

	args.GetReturnValue().Set(args.This());
}

JS_METHOD(_stat) {
	v8::String::Utf8Value name(LOAD_VALUE(0));
	struct stat st;
	if (stat(*name, &st) == 0) {
		v8::Handle<v8::Object> obj = v8::Object::New(JS_ISOLATE);
		obj->Set(JS_STR("size"), JS_INT(st.st_size));
		obj->Set(JS_STR("mtime"), JS_INT(st.st_mtime));
		obj->Set(JS_STR("atime"), JS_INT(st.st_atime));
		obj->Set(JS_STR("ctime"), JS_INT(st.st_ctime));
		obj->Set(JS_STR("mode"), JS_INT(st.st_mode));
		obj->Set(JS_STR("uid"), JS_INT(st.st_uid));
		obj->Set(JS_STR("gid"), JS_INT(st.st_gid));
		args.GetReturnValue().Set(obj);
	} else {
		args.GetReturnValue().Set(JS_BOOL(false));
	}
}

bool _copy(char * name1, char * name2) {
	size_t size = 0;
	void * data = mmap_read(name1, &size);
	if (data == NULL) { JS_ERROR("Cannot open source file"); return false; }
	
	int result = mmap_write(name2, data, size);
	mmap_free((char *)data, size);
	
	if (result == -1) { JS_ERROR("Cannot open target file"); return false; }
	return true;
}

JS_METHOD(_movefile) {
	if (args.Length() < 1) {
		JS_TYPE_ERROR("Bad argument count. Use 'file.rename(newname)'");
		return;
	}
	
	v8::String::Utf8Value name(LOAD_VALUE(0));
	v8::String::Utf8Value newname(args[0]);

	int renres = rename(*name, *newname);

	if (renres != 0) {
		if (!_copy(*name, *newname)) {
			return;
		}
		remove(*name);
	}
	
	SAVE_VALUE(0, args[0]);
	args.GetReturnValue().Set(args.This());
}

JS_METHOD(_copyfile) {
	if (args.Length() < 1) {
		JS_TYPE_ERROR("Bad argument count. Use 'file.copy(newname)'");
		return;
	}
	
	v8::String::Utf8Value name(LOAD_VALUE(0));
	v8::String::Utf8Value newname(args[0]);

	if (!_copy(*name, *newname)) {
		return;
	}
	v8::Handle<v8::Value> fargs[] = { args[0] };
	v8::Local<v8::Function> _file = v8::Local<v8::Function>::New(JS_ISOLATE, file);
	args.GetReturnValue().Set(_file->NewInstance(1, fargs));
}

JS_METHOD(_tostring) {
	args.GetReturnValue().Set(LOAD_VALUE(0));
}

JS_METHOD(_exists) {
	v8::String::Utf8Value name(LOAD_VALUE(0));
	int result = access(*name, F_OK);
	args.GetReturnValue().Set(JS_BOOL(result == 0));
}

JS_METHOD(_isfile) {
	v8::String::Utf8Value name(LOAD_VALUE(0));
	args.GetReturnValue().Set(JS_BOOL(path_file_exists(*name)));
}


}

SHARED_INIT() {
	v8::HandleScope handle_scope(JS_ISOLATE);
	
	v8::Handle<v8::FunctionTemplate> ft = v8::FunctionTemplate::New(JS_ISOLATE, _file);
	ft->SetClassName(JS_STR("File"));
	v8::Handle<v8::ObjectTemplate> ot = ft->InstanceTemplate();
	/* filename, handle */
	ot->SetInternalFieldCount(2); 

	v8::Handle<v8::ObjectTemplate> pt = ft->PrototypeTemplate();
	/**
	 * File prototype methods (new File().*)
	 */
	pt->Set(JS_STR("open"), v8::FunctionTemplate::New(JS_ISOLATE, _open));
	pt->Set(JS_STR("read"), v8::FunctionTemplate::New(JS_ISOLATE, _read));
	pt->Set(JS_STR("readLine"), v8::FunctionTemplate::New(JS_ISOLATE, _readline));
	pt->Set(JS_STR("rewind"), v8::FunctionTemplate::New(JS_ISOLATE, _rewind));
	pt->Set(JS_STR("close"), v8::FunctionTemplate::New(JS_ISOLATE, _close));
	pt->Set(JS_STR("flush"), v8::FunctionTemplate::New(JS_ISOLATE, _flush));
	pt->Set(JS_STR("write"), v8::FunctionTemplate::New(JS_ISOLATE, _write));
	pt->Set(JS_STR("writeLine"), v8::FunctionTemplate::New(JS_ISOLATE, _writeline));
	pt->Set(JS_STR("remove"), v8::FunctionTemplate::New(JS_ISOLATE, _removefile));
	pt->Set(JS_STR("toString"), v8::FunctionTemplate::New(JS_ISOLATE, _tostring));
	pt->Set(JS_STR("exists"), v8::FunctionTemplate::New(JS_ISOLATE, _exists));
	pt->Set(JS_STR("move"), v8::FunctionTemplate::New(JS_ISOLATE, _movefile));
	pt->Set(JS_STR("copy"), v8::FunctionTemplate::New(JS_ISOLATE, _copyfile));
	pt->Set(JS_STR("stat"), v8::FunctionTemplate::New(JS_ISOLATE, _stat));
	pt->Set(JS_STR("isFile"), v8::FunctionTemplate::New(JS_ISOLATE, _isfile));
	pt->Set(JS_STR("isEOF"), v8::FunctionTemplate::New(JS_ISOLATE, _iseof));


	exports->Set(JS_STR("File"), ft->GetFunction());			
	file.Reset(JS_ISOLATE, ft->GetFunction());
	
	v8::Handle<v8::FunctionTemplate> dt = v8::FunctionTemplate::New(JS_ISOLATE, _directory);
	dt->SetClassName(JS_STR("Directory"));
	ot = dt->InstanceTemplate();
	/* dirname */
	ot->SetInternalFieldCount(1); 

	pt = dt->PrototypeTemplate();

	/**
	 * Directory prototype methods (new File().*)
	 */
	pt->Set(JS_STR("create"), v8::FunctionTemplate::New(JS_ISOLATE, _create));
	pt->Set(JS_STR("listFiles"), v8::FunctionTemplate::New(JS_ISOLATE, _listfiles));
	pt->Set(JS_STR("listDirectories"), v8::FunctionTemplate::New(JS_ISOLATE, _listdirectories));
	pt->Set(JS_STR("toString"), v8::FunctionTemplate::New(JS_ISOLATE, _tostring));
	pt->Set(JS_STR("exists"), v8::FunctionTemplate::New(JS_ISOLATE, _exists));
	pt->Set(JS_STR("remove"), v8::FunctionTemplate::New(JS_ISOLATE, _removedirectory));
	pt->Set(JS_STR("stat"), v8::FunctionTemplate::New(JS_ISOLATE, _stat));
	pt->Set(JS_STR("isDirectory"), v8::FunctionTemplate::New(JS_ISOLATE, _isdirectory));

	exports->Set(JS_STR("Directory"), dt->GetFunction());
}

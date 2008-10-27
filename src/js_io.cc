#include <v8.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <sstream>

#include <string.h>
#include <stdlib.h>
#include "js_common.h"

// access()
#ifdef HAVE_UNISTD_H
#  include <unistd.h>
#else
#  include <io.h>
#  define F_OK 0
#  define access(path,mode) _access(path,mode)
#endif

// directory listing
#ifdef HAVE_DIRENT_H
#  include <dirent.h>
#else
#  include <io.h>
#endif

// mkdir()
#ifndef HAVE_MKDIR
#  include <direct.h>
#  define mkdir(name, mode) _mkdir(name)
#endif

// mkdir()
#ifndef HAVE_RMDIR
#  define rmdir(name) _rmdir(name)
#endif

#define TYPE_FILE 0
#define TYPE_DIR 1

v8::Handle<v8::FunctionTemplate> ft;

v8::Handle<v8::Value> list_items(char * name, int type) {
    v8::Handle<v8::Array> result = v8::Array::New();
    int cnt = 0;

#ifdef HAVE_DIRENT_H
    DIR * dp;
    struct dirent * ep;
    int cond = (type == TYPE_FILE ? DT_REG : DT_DIR);
    
    dp = opendir(name);
    if (dp == NULL) { return v8::ThrowException(v8::String::New("Directory cannot be opened")); }
    while ((ep = readdir(dp))) { 
	if (ep->d_type == cond) {
	    if (type == TYPE_FILE) {
		result->Set(v8::Integer::New(cnt++), v8::String::New(ep->d_name));
	    } else if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0) {
		result->Set(v8::Integer::New(cnt++), v8::String::New(ep->d_name));
	    }
	}
    }
    closedir(dp);
#else
    _finddata_t * info = (_finddata_t *) malloc(sizeof(_finddata_t));
    unsigned int value = (type == TYPE_FILE ? 0 : _A_SUBDIR);

    std::string path;
    std::stringstream ss;
    ss << name << "/*";
    ss >> path;

    intptr_t ptr = _findfirst(path.c_str(), info);
    
    if (ptr != -1L) {
	do {
	    if ((info->attrib & _A_SUBDIR) == value) {
		if (type == TYPE_FILE) {
		    result->Set(v8::Integer::New(cnt++), v8::String::New(info->name));
		} else if (strcmp(info->name, ".") != 0 && strcmp(info->name, "..") != 0) {
		    result->Set(v8::Integer::New(cnt++), v8::String::New(info->name));
		}
	    }
	} while (_findnext(ptr, info) == 0);
	_findclose(ptr);
    }
#endif
    
    return result;
}

v8::Handle<v8::Value> _directory(const v8::Arguments& args) {
    v8::HandleScope handle_scope;
    if (args.Length() < 1 || args.This()->InternalFieldCount() == 0) {
	return v8::ThrowException(v8::String::New("Invalid call format. Use 'new Directory(name)'"));
    }
    
    args.This()->SetInternalField(0, args[0]);
    return args.This();
}

v8::Handle<v8::Value> _create(const v8::Arguments& args) {
    v8::HandleScope handle_scope;

    v8::String::Utf8Value name(args.This()->GetInternalField(0));
    int mode;
    if (args.Length() == 0) { 
	mode = 0777; 
    } else {
	mode = args[0]->Int32Value();
    }

    int result = mkdir(*name, mode);
    if (result != 0) {
	return v8::ThrowException(v8::String::New("Cannot create directory'"));
    }
    
    return args.This();
}



v8::Handle<v8::Value> _listfiles(const v8::Arguments& args) {
    v8::HandleScope handle_scope;
    v8::String::Utf8Value name(args.This()->GetInternalField(0));
    return list_items(*name, TYPE_FILE);
}

v8::Handle<v8::Value> _listdirectories(const v8::Arguments& args) {
    v8::HandleScope handle_scope;
    v8::String::Utf8Value name(args.This()->GetInternalField(0));
    return list_items(*name, TYPE_DIR);
}

v8::Handle<v8::Value> _file(const v8::Arguments& args) {
    v8::HandleScope handle_scope;
    if (args.Length() < 1 || args.This()->InternalFieldCount() == 0) {
	return v8::ThrowException(v8::String::New("Invalid call format. Use 'new File(name)'"));
    }
    
    args.This()->SetInternalField(0, args[0]);
    args.This()->SetInternalField(1, v8::Boolean::New(false));
    return args.This();
}

v8::Handle<v8::Value> _open(const v8::Arguments& args) {
    v8::HandleScope handle_scope;
    if (args.Length() < 1) {
	return v8::ThrowException(v8::String::New("Bad argument count. Use 'file.open(mode)'"));
    }
    v8::String::Utf8Value mode(args[0]);
    v8::String::Utf8Value name(args.This()->GetInternalField(0));
    v8::Handle<v8::Value> file = args.This()->GetInternalField(1);
    if (!file->IsFalse()) {
	return v8::ThrowException(v8::String::New("File already opened"));
    }
    
    FILE * f;
    f = fopen(*name, *mode);
    
    if (!f) {
	return v8::ThrowException(v8::String::New("Cannot open file"));
    }
    
    struct stat st;
    if (stat(*name, &st) == 0) {
	args.This()->SetInternalField(2, v8::Integer::New(st.st_size));
    }
    args.This()->SetInternalField(1, v8::External::New((void *)f));
    args.This()->SetInternalField(3, v8::Integer::New(0));
    
    return args.This();
}
		
v8::Handle<v8::Value> _close(const v8::Arguments& args) {
    v8::HandleScope handle_scope;
    v8::Handle<v8::Value> file = args.This()->GetInternalField(1);
    
    if (file->IsFalse()) {
	return v8::ThrowException(v8::String::New("Cannot close non-opened file"));
    }
    
    FILE * f = reinterpret_cast<FILE *>(v8::Handle<v8::External>::Cast(file)->Value());
    fclose(f);
    args.This()->SetInternalField(1, v8::Boolean::New(false));
    return args.This();
}

v8::Handle<v8::Value> _read(const v8::Arguments& args) {
    v8::HandleScope handle_scope;
    v8::Handle<v8::Value> file = args.This()->GetInternalField(1);
    
    if (file->IsFalse()) {
	return v8::ThrowException(v8::String::New("File must be opened before reading"));
    }
    
    int64_t size = args.This()->GetInternalField(2)->IntegerValue();
    int64_t pos = args.This()->GetInternalField(3)->IntegerValue();
    
    FILE * f = reinterpret_cast<FILE *>(v8::Handle<v8::External>::Cast(file)->Value());
    
    size_t avail = size-pos;
    if (!avail) { return v8::Boolean::New(false); }
    
    if (args.Length() && args[0]->IsNumber()) {
        int64_t len = args[0]->IntegerValue();
	if (len < avail) { avail = len; }
    }
    char * buf = (char *) malloc(avail * sizeof(char));
    fread(buf, sizeof(char), avail, f);
    pos += avail;
    
    args.This()->SetInternalField(3, v8::Integer::New(pos));
    
   if (args.Length() > 1 && args[1]->IsTrue()) {
       return char2array(buf, avail);
   } else {
       return char2string(buf, avail);
    }
}

v8::Handle<v8::Value> _rewind(const v8::Arguments& args) {
    v8::HandleScope handle_scope;
    v8::Handle<v8::Value> file = args.This()->GetInternalField(1);
    if (file->IsFalse()) {
	return v8::ThrowException(v8::String::New("File must be opened before rewinding"));
    }
    
    FILE * f = reinterpret_cast<FILE *>(v8::Handle<v8::External>::Cast(file)->Value());
    rewind(f);

    args.This()->SetInternalField(3, v8::Integer::New(0));
    return args.This();
}

v8::Handle<v8::Value> _write(const v8::Arguments& args) {
    v8::HandleScope handle_scope;
    v8::Handle<v8::Value> file = args.This()->GetInternalField(1);
    
    if (file->IsFalse()) {
	return v8::ThrowException(v8::String::New("File must be opened before writing"));
    }
    

    FILE * f = reinterpret_cast<FILE *>(v8::Handle<v8::External>::Cast(file)->Value());
    
    
    if (args[0]->IsArray()) {
	v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(args[0]);
	uint32_t len = arr->Length();
	
	int max = 4096;
	int current = 0;
	char * buf = (char *) malloc(max * sizeof(char));
	for (unsigned int i=0;i<len;i++) {
	    buf[current++] = (char) arr->Get(v8::Integer::New(i))->IntegerValue();
	    if (current == max) {
    		fwrite(buf, sizeof(char), current, f);
		current = 0;
	    }
	}
	if (current) { fwrite(buf, sizeof(char), current, f); }

    } else {
	v8::String::Utf8Value data(args[0]);
	fwrite(*data, sizeof(char), args[0]->ToString()->Utf8Length(), f);
    }
	    
    return args.This();
}

v8::Handle<v8::Value> _removefile(const v8::Arguments& args) {
    v8::HandleScope handle_scope;
    v8::String::Utf8Value name(args.This()->GetInternalField(0));
    
    if (remove(*name) != 0) {
	return v8::ThrowException(v8::String::New("Cannot remove file"));
    }
    
    return args.This();
}

v8::Handle<v8::Value> _removedirectory(const v8::Arguments& args) {
    v8::HandleScope handle_scope;
    v8::String::Utf8Value name(args.This()->GetInternalField(0));
    
    if (rmdir(*name) != 0) {
	return v8::ThrowException(v8::String::New("Cannot remove directory"));
    }
    
    return args.This();
}

v8::Handle<v8::Value> _stat(const v8::Arguments& args) {
    v8::HandleScope handle_scope;
    
    v8::String::Utf8Value name(args.This()->GetInternalField(0));
    struct stat st;
    if (stat(*name, &st) == 0) {
	v8::Handle<v8::Object> obj = v8::Object::New();
	obj->Set(v8::String::New("size"), v8::Integer::New(st.st_size));
	obj->Set(v8::String::New("mtime"), v8::Integer::New(st.st_mtime));
	obj->Set(v8::String::New("atime"), v8::Integer::New(st.st_atime));
	obj->Set(v8::String::New("ctime"), v8::Integer::New(st.st_ctime));
	obj->Set(v8::String::New("mode"), v8::Integer::New(st.st_mode));
	obj->Set(v8::String::New("uid"), v8::Integer::New(st.st_uid));
	obj->Set(v8::String::New("gid"), v8::Integer::New(st.st_gid));
	return obj;
    } else {
	return v8::Boolean::New(false);
    }
}

v8::Handle<v8::Value> _copy(char * name1, char * name2) {
    int len = 1024;
    char * buf = (char *) malloc(len * sizeof(char));
    
    FILE * f1 = fopen(name1, "rb");
    FILE * f2 = fopen(name2, "wb");
    
    if (f1 == NULL) { return v8::ThrowException(v8::String::New("Cannot open source file")); }
    if (f2 == NULL) { return v8::ThrowException(v8::String::New("Cannot open target file")); }
    
    size_t size = 0;
    
    while ((size = fread(buf, sizeof(char), len, f1))) {
	fwrite(buf, sizeof(char), size, f2);
    }
    
    fclose(f1);
    fclose(f2);
    return v8::Boolean::New(true);
}
v8::Handle<v8::Value> _movefile(const v8::Arguments& args) {
    v8::HandleScope handle_scope;
    
    if (args.Length() < 1) {
	return v8::ThrowException(v8::String::New("Bad argument count. Use 'file.rename(newname)'"));
    }
    
    v8::String::Utf8Value name(args.This()->GetInternalField(0));
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
    
    args.This()->SetInternalField(0, args[0]);
    return args.This();    
}

v8::Handle<v8::Value> _copyfile(const v8::Arguments & args) {
    v8::HandleScope handle_scope;
    if (args.Length() < 1) {
	return v8::ThrowException(v8::String::New("Bad argument count. Use 'file.copy(newname)'"));
    }
    
    v8::String::Utf8Value name(args.This()->GetInternalField(0));
    v8::String::Utf8Value newname(args[0]);

    v8::Handle<v8::Value> result = _copy(*name, *newname);    
    if (result->IsTrue()) {
	v8::Handle<v8::Value> fargs[] = { args[0] };
    	return ft->GetFunction()->NewInstance(1, fargs);
    } else {
	return result;
    }
}



v8::Handle<v8::Value> _tostring(const v8::Arguments& args) {
    v8::HandleScope handle_scope;
    return args.This()->GetInternalField(0);
}

v8::Handle<v8::Value> _exists(const v8::Arguments& args) {
    v8::HandleScope handle_scope;
    v8::String::Utf8Value name(args.This()->GetInternalField(0));
    int result = access(*name, F_OK);
    return v8::Boolean::New(result == 0);
}

void setup_io(v8::Handle<v8::Object> target) {

  ft = v8::FunctionTemplate::New(_file);
  ft->SetClassName(v8::String::New("File"));
  v8::Handle<v8::ObjectTemplate> ot = ft->InstanceTemplate();
  ot->SetInternalFieldCount(4); /* filename, handle, size, position */

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

  target->Set(v8::String::New("File"), ft->GetFunction());	      
  
  ft = v8::FunctionTemplate::New(_directory);
  ft->SetClassName(v8::String::New("Directory"));
  ot = ft->InstanceTemplate();
  ot->SetInternalFieldCount(1); /* dirname */

  pt = ft->PrototypeTemplate();
  pt->Set("create", v8::FunctionTemplate::New(_create));
  pt->Set("listFiles", v8::FunctionTemplate::New(_listfiles));
  pt->Set("listDirectories", v8::FunctionTemplate::New(_listdirectories));
  pt->Set("toString", v8::FunctionTemplate::New(_tostring));
  pt->Set("exists", v8::FunctionTemplate::New(_exists));
  pt->Set("remove", v8::FunctionTemplate::New(_removedirectory));
  pt->Set("stat", v8::FunctionTemplate::New(_stat));

  target->Set(v8::String::New("Directory"), ft->GetFunction());	      
  
}

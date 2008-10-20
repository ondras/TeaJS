#include <v8.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <common.h>
#include <dirent.h>
#include <string.h>

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

    DIR * dp;
    struct dirent * ep;
    
    v8::Handle<v8::Array> result = v8::Array::New();
  
    dp = opendir(*name);
    if (dp == NULL) { return v8::ThrowException(v8::String::New("Directory cannot be opened")); }
    int cnt = 0;
    while ((ep = readdir(dp))) { 
	if (ep->d_type == DT_REG) {
	    result->Set(v8::Integer::New(cnt++), v8::String::New(ep->d_name));
	}
    }
    closedir(dp);
    return result;
}

v8::Handle<v8::Value> _listdirectories(const v8::Arguments& args) {
    v8::HandleScope handle_scope;
    v8::String::Utf8Value name(args.This()->GetInternalField(0));

    DIR * dp;
    struct dirent * ep;
    
    v8::Handle<v8::Array> result = v8::Array::New();
  
    dp = opendir(*name);
    if (dp == NULL) { return v8::ThrowException(v8::String::New("Directory cannot be opened")); }
    int cnt = 0;
    while ((ep = readdir(dp))) { 
	if (ep->d_type == DT_DIR) {
	    if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0) {
		result->Set(v8::Integer::New(cnt++), v8::String::New(ep->d_name));
	    }
	}
    }
    closedir(dp);
    return result;
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
    
    long size = args.This()->GetInternalField(2)->IntegerValue();
    long pos = args.This()->GetInternalField(3)->IntegerValue();
    
    FILE * f = reinterpret_cast<FILE *>(v8::Handle<v8::External>::Cast(file)->Value());
    
    long avail = size-pos;
    if (!avail) { return v8::Boolean::New(false); }
    
    if (args.Length() && args[0]->IsNumber()) {
        int len = args[0]->IntegerValue();
	if (len < avail) { avail = len; }
    }
    char buf[avail];
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
    
    if (args.Length() < 1) {
	return v8::ThrowException(v8::String::New("Bad argument count. Use 'file.write(data)'"));
    }

    FILE * f = reinterpret_cast<FILE *>(v8::Handle<v8::External>::Cast(file)->Value());
    
    
    if (args[0]->IsArray()) {
	v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(args[0]);
	int len = arr->Length();
	
	int max = 4096;
	int current = 0;
	char buf[max];
	for (int i=0;i<len;i++) {
    	    v8::Handle<v8::Integer> a = v8::Integer::New(arr->Get(v8::Integer::New(i))->IntegerValue());
	    buf[current++] = (char) a->Int32Value();
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

v8::Handle<v8::Value> _remove(const v8::Arguments& args) {
    v8::HandleScope handle_scope;
    v8::String::Utf8Value name(args.This()->GetInternalField(0));
    v8::Handle<v8::Value> file = args.This()->GetInternalField(1);
    
    if (!file->IsFalse()) {
	return v8::ThrowException(v8::String::New("File must be closed before deleting"));
    }
    
    if (!remove(*name)) {
	return v8::ThrowException(v8::String::New("Cannot remove file"));
    }
    
    return args.This();
}

v8::Handle<v8::Value> _getsize(const v8::Arguments& args) {
    v8::HandleScope handle_scope;
    
    v8::String::Utf8Value name(args.This()->GetInternalField(0));
    struct stat st;
    if (stat(*name, &st) == 0) {
	return v8::Integer::New(st.st_size);
    } else {
	return v8::Boolean::New(false);
    } 
}

v8::Handle<v8::Value> _tostring(const v8::Arguments& args) {
    v8::HandleScope handle_scope;
    return args.This()->GetInternalField(0);

}

void SetupIo(v8::Handle<v8::Object> target) {
  v8::HandleScope handle_scope;

  v8::Handle<v8::FunctionTemplate> ft = v8::FunctionTemplate::New(_file);
  ft->SetClassName(v8::String::New("File"));
  v8::Handle<v8::ObjectTemplate> ot = ft->InstanceTemplate();
  ot->SetInternalFieldCount(4); /* filename, handle, size, position */

  v8::Handle<v8::ObjectTemplate> pt = ft->PrototypeTemplate();
  pt->Set("open", v8::FunctionTemplate::New(_open));
  pt->Set("read", v8::FunctionTemplate::New(_read));
  pt->Set("rewind", v8::FunctionTemplate::New(_rewind));
  pt->Set("close", v8::FunctionTemplate::New(_close));
  pt->Set("write", v8::FunctionTemplate::New(_write));
  pt->Set("remove", v8::FunctionTemplate::New(_remove));
  pt->Set("getSize", v8::FunctionTemplate::New(_getsize));
  pt->Set("toString", v8::FunctionTemplate::New(_tostring));

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

  target->Set(v8::String::New("Directory"), ft->GetFunction());	      
  
}

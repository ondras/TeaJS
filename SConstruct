import sys
import os

def build_with_binary(env, target = "", source = []):
	e = env.Clone()
	support = ["src/app", "src/path", "src/cache", "src/lib/binary/bytestorage"]
	if e["os"] == "windows":
		e.Append(LIBS = ["iconv"])
		support += ["src/system", "src/gc"]
	# if
	e.SharedLibrary(
		target = target, 
		source = source + support,
		SHLIBPREFIX=""
	)
# def 

def build_sources(env, sources):
	return [ env.SharedObject(s) for s in sources ]
# def

def build_profiler(env):
	e = env.Clone()
	e.SharedLibrary(
		target = "lib/profiler",
		source = ["src/lib/profiler/profiler.cc"],
		SHLIBPREFIX="")
# def

def build_fibers(env):
	e = env.Clone()
	e.SharedLibrary(
		target = "lib/fibers",
		source = ["src/lib/fibers/fibers.cc"],
		SHLIBPREFIX=""
	)
# def

def build_memcached(env):
	e = env.Clone()
	if env["os"] == "darwin":
		e.Append(
			LIBPATH = ["/opt/local/lib"],
			CPPPATH = ["/opt/local/include"]
		)
	if env["os"] == "posix":
	  e.Append(
	    LIBPATH = ["/usr/local/libmemcached/lib"],
	    CPPPATH = ["/usr/local/libmemcached/include"]
	  )
	# if
	e.Append(
		LIBS = ["libmemcached"]
	)
	e.SharedLibrary(
		target = "lib/memcached",
		source = ["src/lib/memcached/memcached.cc"],
		SHLIBPREFIX=""
	)
# def

def build_mysql(env):
	e = env.Clone()
	if env["os"] == "windows":
		e.Append(
			LIBS = ["wsock32", "user32", "advapi32", "mysql"],
		)
	# if
	if env["os"] == "darwin":
		e.Append(
			LIBPATH = ["/opt/local/lib/", "/opt/local/lib/mysql5/mysql"],
			LIBS = ["mysqlclient"]
		)
	# if
	if env["os"] == "posix":
		e.Append(
			LIBS = ["mysqlclient"]
		)
	# if
	e.Append(
		CPPPATH = env["mysql_path"],
	)
	e.SharedLibrary(
		target = "lib/mysql",
		source = ["src/gc", "src/lib/mysql/mysql.cc"],
		SHLIBPREFIX=""
	)
# def

def build_pgsql(env):
	e = env.Clone()
	e.Append(
		CPPPATH = env["pgsql_path"],
		LIBS = "pq"
	)
	if env["os"] == "windows":
		e.Append(
			LIBS = ["pthreadGCE2"],
		)
	# if
	e.SharedLibrary(
		target = "lib/pgsql",
		source = ["src/gc", "src/lib/pgsql/pgsql.cc"],
		SHLIBPREFIX=""
	)
# def

def build_sqlite(env):
	e = env.Clone()
	e.Append(
		LIBS = ["sqlite3"]
	)
	e.SharedLibrary(
		target = "lib/sqlite", 
		source = ["src/gc", "src/lib/sqlite/sqlite.cc"],
		SHLIBPREFIX=""
	)
# def

def build_zlib(env):
	e = env.Clone()
	e.Append(
		LIBS = ["z"]
	)
	e.SharedLibrary(
		target = "lib/zlib", 
		source = ["src/lib/zlib/zlib.cc", "src/app", "src/path", "src/cache", "src/lib/binary/bytestorage"],
		SHLIBPREFIX=""
	)
# def

def build_gd(env):
	e = env.Clone()
	libname = ("gd", "bgd")[env["os"] == "windows"]
	e.Append(
		LIBS = [libname]
	)
	build_with_binary(
		e,
		target = "lib/gd", 
		source = ["src/common", "src/lib/gd/gd.cc"],
	)
# def

def build_socket(env):
	build_with_binary(
		env, 
		target = "lib/socket", 
		source = ["src/lib/socket/socket.cc"]
	)
# def

def build_fs(env):
	build_with_binary(
		env, 
		target = "lib/fs", 
		source = ["src/lib/fs/fs.cc", "src/common"],
	)
# def

def build_process(env):
	env.SharedLibrary(
		target = "lib/process", 
		source = ["src/lib/process/process.cc"],
		SHLIBPREFIX=""
	)
# def

def build_binary(env):
	e = env.Clone()
	if env["os"] == "windows" or env["os"] == "darwin":
		e.Append(
			LIBS = ["iconv"]
		)
	# if
	e.SharedLibrary(
		target = "lib/binary", 
		source = ["src/lib/binary/binary.cc", "src/lib/binary/bytestorage"],
		SHLIBPREFIX=""
	)
# def

def build_xdom(env):
	e = env.Clone()
	e.Append(
		CPPPATH = env["xercesc_path"],
		LIBS = "xerces-c"
	)
	e.SharedLibrary(
		target = "lib/xdom",
		source = ["src/gc.cc", "src/lib/xdom/xdom.cc"],
		SHLIBPREFIX=""
	)
# def	

def build_gl(env):
	e = env.Clone()
	e.Append(
		LIBS = ["glut", "GLU", "GL", "GLEW"]
	)
	e.SharedLibrary(
		target = "lib/GL",
		source = ["src/gc.cc", "src/lib/GL/GL.cc", "src/lib/GL/glbindings/glbind.cpp", "src/lib/GL/glesbindings/glesbind.cpp", "src/lib/GL/glubindings/glubind.cpp", "src/lib/GL/glutbindings/glutbind.cpp"],
		SHLIBPREFIX=""
	)
# def

def build_module(env, sources):
	e = env.Clone()
	e.Append(
		CPPPATH = [env["apache_path"], env["apr_path"]]
	)
	if e["os"] == "darwin":
		e.Append(
			LINKFLAGS = "-bundle -bundle_loader /usr/sbin/httpd",
			LIBS = ["apr-1", "aprutil-1"]
		)
		e["SHLINKFLAGS"] = e["LINKFLAGS"]
	if e["os"] == "windows":
		e.Append(
			LIBS = ["apr-1", "httpd", "aprutil-1", "iconv"]
		)
	# if
	
	e.SharedLibrary(
		target = "mod_v8cgi", 
		source = [sources, "src/mod_v8cgi.cc"],
		SHLIBPREFIX=""
	)
# def

def build_cgi(env, sources):
	if env["fcgi"] == 1:
		env.Append(
			LIBS = ["fcgi"],
			CPPPATH = ["src/fcgi/include"],
			CPPDEFINES = ["FASTCGI"]
		)
	# if
	if env["os"] == "windows":
		env.Append(
			LIBS = ["iconv"]
		)
	# if
	env.Program(
		source = [sources, "src/v8cgi.cc"],
		target = "v8cgi"
	)
# def

# base source files
sources = ["common.cc", "system.cc", "cache.cc", "gc.cc", "app.cc", "path.cc", "lib/binary/bytestorage.cc"]
sources = [ "src/%s" % s for s in sources ]

version = open("VERSION", "r").read()
config_path = ""
mysql_include = ""
pgsql_include = ""
os_string = ""
apache_include = ""
apr_include = ""

# platform-based default values
if sys.platform.find("win") != -1 and sys.platform.find("darwin") == -1:
	mysql_include = "c:/"
	pgsql_include = "c:/"
	apache_include = "c:/"
	apr_include = "c:/"
	config_path = "c:/v8cgi.conf"
	os_string = "windows"
	xercesc_include = "c:/"
	gl_include = "c:/"
elif sys.platform.find("darwin") != -1:
	mysql_include = "/opt/local/include/mysql5/mysql"
	pgsql_include = "/opt/local/include/postgresql83"
	apache_include = "/opt/local/apache2/include"
	apr_include = "/opt/local/include/apr-1"
	config_path = "/etc/v8cgi.conf"
	os_string = "darwin"
	xercesc_include = "/opt/local/include/xercesc3"
	gl_include = "/opt/local/include/GL"
else:
	mysql_include = "/usr/include/mysql"
	pgsql_include = "`/usr/bin/pg_config --includedir`"
	apache_include = "/usr/include/apache2"
	apr_include = "/usr/include/apr-1.0"
	config_path = "/etc/v8cgi.conf"
	os_string = "posix"
	xercesc_include = "/usr/include/xercesc"
	gl_include = "/usr/include/GL"
# endif 

# command line options
vars = Variables()

# module switches
vars.Add(BoolVariable("mysql", "MySQL library", 1))
vars.Add(BoolVariable("profiler", "V8 Profiler library", 1))
vars.Add(BoolVariable("fibers", "Fiber support", 1))
vars.Add(BoolVariable("memcached", "Memcached library", 1))
vars.Add(BoolVariable("pgsql", "PostgreSQL library", 0))
vars.Add(BoolVariable("gd", "GD library", 1))
vars.Add(BoolVariable("sqlite", "SQLite library", 1))
vars.Add(BoolVariable("socket", "Socket library", 1))
vars.Add(BoolVariable("process", "Process library", 1))
vars.Add(BoolVariable("fs", "Filesystem I/O library", 1))
vars.Add(BoolVariable("xdom", "DOM Level 3 library (xerces based, for XML/XHTML)", 0))
vars.Add(BoolVariable("gl", "OpenGL library", 0))
vars.Add(BoolVariable("zlib", "zlib library", 1))
vars.Add(BoolVariable("module", "Build Apache module", 1))
vars.Add(BoolVariable("cgi", "Build CGI binary", 1))
vars.Add(BoolVariable("fcgi", "FastCGI support (for CGI binary)", 0))
vars.Add(BoolVariable("debug", "Debugging support", 0))
vars.Add(BoolVariable("verbose", "Verbose debugging messages", 0))
vars.Add(BoolVariable("reuse_context", "Reuse context for multiple requests", 0))

# optional library paths
vars.Add(("mysql_path", "MySQL header path", mysql_include))
vars.Add(("pgsql_path", "PostgreSQL header path", pgsql_include))
vars.Add(("apache_path", "Apache header path", apache_include))
vars.Add(("apr_path", "APR header path", apr_include))
vars.Add(("xercesc_path", "Xerces-C++ header path", xercesc_include))
vars.Add(("gl_path", "OpenGL header path", gl_include))

# misc compile options
vars.Add(PathVariable("v8_path", "Directory with V8", "../v8"))
vars.Add(EnumVariable("os", "Operating system", os_string, allowed_values = ["windows", "posix", "darwin"]))
vars.Add(("config_file", "Config file", config_path))

# additional
vars.Add(("cpppath", "Additional include paths (semicolon separated)", ""))
vars.Add(("libpath", "Additional library paths (semicolon separated)", ""))

env = Environment(variables=vars)

Help(vars.GenerateHelpText(env))
conf = Configure(env)

# before compilation checks
if conf.CheckCHeader("sys/mman.h", include_quotes = "<>"):
	env.Append(CPPDEFINES = ["HAVE_MMAN_H"])

if conf.CheckFunc("sleep"):
	env.Append(CPPDEFINES = ["HAVE_SLEEP"])

if env["debug"] == 1:
  v8_lib = "v8_g"
else:
  v8_lib = "v8"
  
# default built-in values
env.Append(
	LIBS = [v8_lib],
	CCFLAGS = ["-Wall", "-O3"],
	CPPPATH = ["src", env["v8_path"] + "/include"],
	LIBPATH = env["v8_path"],
	CPPDEFINES = [
		"CONFIG_PATH=" + env["config_file"],
		"VERSION=" + version,
		env["os"]
	],
	LINKFLAGS = []
)
	
# additional paths
env.Append(
	CPPPATH = env["cpppath"].split(";"),
	LIBPATH = env["libpath"].split(";")
)

if env["os"] == "posix":
	env.Append(
		LIBS = ["pthread", "rt"]
	)
# if

# look for V8 - sanity check
if (env["os"] != "windows") and not (conf.CheckLib(v8_lib)):
	print("Cannot find V8 library!")
	sys.exit(1)
# if

# configured build environment
env = conf.Finish()

# add posix-specific values
if env["os"] == "posix":
	env.Append(
		LIBS = ["dl"],
		CPPDEFINES = ["DSO_EXT=so"]
	)
# if

# add macos-specific values
if env["os"] == "darwin":
	env.Append(
		CPPDEFINES = ["DSO_EXT=dylib"]
	)
# if

# add windows-specific values
if env["os"] == "windows":
	env.Append(
		LIBS = ["ws2_32"],
		CPPDEFINES = ["USING_V8_SHARED", "WIN32", "_WIN32_WINNT=0x0501", "HAVE_RINT", "DSO_EXT=dll"],
	)
# if

if env["debug"] == 1:
	env.Append(
		CCFLAGS = ["-O0", "-g", "-g3", "-gdwarf-2", "-pg"],
		LINKFLAGS = ["-pg"]
	)
# if

if env["verbose"] == 1:
	env.Append(
		CPPDEFINES = ["VERBOSE"]
	)
# if

if env["reuse_context"] == 1:
	env.Append(
		CPPDEFINES = ["REUSE_CONTEXT"]
	)
# if

# start compiling
sources = build_sources(env, sources)
build_binary(env)

if env["fibers"] == 1: build_fibers(env)
if env["mysql"] == 1: build_mysql(env)
if env["memcached"] == 1: build_memcached(env)
if env["profiler"] == 1: build_profiler(env)
if env["pgsql"] == 1: build_pgsql(env)
if env["sqlite"] == 1: build_sqlite(env)
if env["gd"] == 1: build_gd(env)
if env["socket"] == 1: build_socket(env)
if env["process"] == 1: build_process(env)
if env["fs"] == 1: build_fs(env)
if env["zlib"] == 1: build_zlib(env)
if env["xdom"] == 1: build_xdom(env)
if env["gl"] == 1: build_gl(env)
if env["module"] == 1: build_module(env, sources)
if env["cgi"] == 1: build_cgi(env, sources)

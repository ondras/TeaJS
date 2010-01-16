import sys
import os

version = open("VERSION", "r").read()

# base source files
sources = [
	"common.cc",
	"system.cc",
	"io.cc",
	"cache.cc",
	"gc.cc",
	"app.cc",
	"path.cc"
]
sources = [ "src/%s" % s for s in sources ]

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
vars.Add(BoolVariable("mysql", "MySQL library", 1))
vars.Add(BoolVariable("pgsql", "PostgreSQL library", 0))
vars.Add(BoolVariable("gd", "GD library", 1))
vars.Add(BoolVariable("sqlite", "SQLite library", 1))
vars.Add(BoolVariable("socket", "Socket library", 1))
vars.Add(BoolVariable("process", "Process library", 1))
vars.Add(BoolVariable("xdom", "DOM Level 3 library (xerces based, for XML/XHTML)", 0))
vars.Add(BoolVariable("gl", "OpenGL library", 0))
vars.Add(BoolVariable("module", "Build Apache module", 1))
vars.Add(BoolVariable("cgi", "Build CGI binary", 1))
vars.Add(BoolVariable("fcgi", "FastCGI support (for CGI binary)", 0))
vars.Add(BoolVariable("debug", "Debugging support", 0))
vars.Add(BoolVariable("verbose", "Verbose debugging messages", 0))
vars.Add(BoolVariable("reuse_context", "Reuse context for multiple requests", 0))

vars.Add(("mysql_path", "MySQL header path", mysql_include))
vars.Add(("pgsql_path", "PostgreSQL header path", pgsql_include))
vars.Add(("apache_path", "Apache header path", apache_include))
vars.Add(("apr_path", "APR header path", apr_include))
vars.Add(("xercesc_path", "Xerces-C++ header path", xercesc_include))
vars.Add(("gl_path", "OpenGL header path", gl_include))

vars.Add(PathVariable("v8_path", "Directory with V8", "../v8"))
vars.Add(EnumVariable("os", "Operating system", os_string, allowed_values = ["windows", "posix", "darwin"]))
vars.Add(("config_file", "Config file", config_path))

vars.Add(("cpppath", "Additional include paths (semicolon separated)", ""))
vars.Add(("libpath", "Additional library paths (semicolon separated)", ""))

env = Environment(variables=vars)

Help(vars.GenerateHelpText(env))
conf = Configure(env)

if conf.CheckCHeader("sys/mman.h", include_quotes = "<>"):
	env.Append(CPPDEFINES = ["HAVE_MMAN_H"])

if conf.CheckFunc("sleep"):
	env.Append(CPPDEFINES = ["HAVE_SLEEP"])

# default values
env.Append(
	LIBS = ["v8"],
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

if ((env["os"] != "windows") and not (conf.CheckLib("v8"))):
	print("Cannot find V8 library!")
	sys.exit(1)
# if

env = conf.Finish()

if env["os"] == "posix":
	env.Append(
		LIBS = ["dl"],
		CPPDEFINES = ["DSO_EXT=so"]
	)
# if

if env["os"] == "darwin":
	env.Append(
		CPPDEFINES = ["DSO_EXT=dylib"]
	)
# if

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

if env["mysql"] == 1:
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
		source = ["src/gc.cc", "src/lib/mysql/mysql.cc"],
		SHLIBPREFIX=""
	)
# if

if env["pgsql"] == 1:
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
		source = ["src/gc.cc", "src/lib/pgsql/pgsql.cc"],
		SHLIBPREFIX=""
	)
# if

if env["sqlite"] == 1:
	e = env.Clone()
	e.Append(
		LIBS = ["sqlite3"]
	)
	e.SharedLibrary(
		target = "lib/sqlite", 
		source = ["src/gc.cc", "src/lib/sqlite/sqlite.cc"],
		SHLIBPREFIX=""
	)
# if

if env["gd"] == 1:
	e = env.Clone()
	libname = ("gd", "bgd")[env["os"] == "windows"]
	e.Append(
		LIBS = [libname]
	)
	e.SharedLibrary(
		target = "lib/gd", 
		source = ["src/common.cc", "src/lib/gd/gd.cc"],
		SHLIBPREFIX=""
	)
# if

if env["socket"] == 1:
	e = env.Clone()
	e.SharedLibrary(
		target = "lib/socket", 
		source = ["src/lib/socket/socket.cc"],
		SHLIBPREFIX=""
	)
# if

if env["process"] == 1:
	e = env.Clone()
	e.SharedLibrary(
		target = "lib/process", 
		source = ["src/lib/process/process.cc"],
		SHLIBPREFIX=""
	)
# if

e.SharedLibrary(
	target = "lib/binary", 
	source = ["src/lib/binary/binary.cc", "src/lib/binary/bytestring.cc"],
	SHLIBPREFIX=""
)

if env["xdom"] == 1:
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
# if

if env["gl"] == 1:
	e = env.Clone()
	e.Append(
		LIBS = ["glut", "GLU", "GL", "GLEW"]
	)
	e.SharedLibrary(
		target = "lib/GL",
		source = ["src/gc.cc", "src/lib/GL/GL.cc", "src/lib/GL/glbindings/glbind.cpp", "src/lib/GL/glesbindings/glesbind.cpp", "src/lib/GL/glubindings/glubind.cpp", "src/lib/GL/glutbindings/glutbind.cpp"],
		SHLIBPREFIX=""
	)
# if

if env["module"] == 1:
	e = env.Clone()
	e.Append(
		CPPPATH = [env["apache_path"], env["apr_path"]]
	)
	if env["os"] == "darwin":
		e.Append(
			LINKFLAGS = "-bundle_loader /opt/local/apache2/bin/httpd",
			LIBS = ["apr-1", "aprutil-1"]
		)
	if env["os"] == "windows":
		e.Append(
			LIBS = ["apr-1", "httpd", "aprutil-1"]
		)
	# if
	
	s = []
	s[:] = sources[:]
	s.append("src/mod_v8cgi.cc")
	e.SharedLibrary(
		target = "mod_v8cgi", 
		source = s,
		SHLIBPREFIX=""
	)
# if

if env["cgi"] == 1:
	if env["fcgi"] == 1:
		env.Append(
			LIBS = ["fcgi"],
			CPPPATH = ["src/fcgi/include"],
			CPPDEFINES = ["FASTCGI"]
		)
	# if
	sources.append("src/v8cgi.cc")
	env.Program(
		source = sources, 
		target = "v8cgi"
	)
# if

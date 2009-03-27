import sys
import os

# base source files
sources = [
	"js_system.cc",
	"js_io.cc",
	"js_socket.cc",
	"js_cache.cc",
	"js_gc.cc",
	"js_app.cc",
	"js_path.cc"
]
sources = [ "src/%s" % s for s in sources ]

config_path = ""
mysql_include = ""
os_string = ""
apache_include = ""
apr_include = ""

# platform-based default values
if sys.platform.find("win") != -1 and sys.platform.find("darwin") == -1:
	mysql_include = "c:/"
	apache_include = "c:/"
	apr_include = "c:/"
	config_path = "c:/v8cgi.conf"
	os_string = "windows"
else:
	mysql_include = "/usr/include/mysql"
	apache_include = "/usr/include/apache2"
	apr_include = "/usr/include/apr-1.0"
	config_path = "/etc/v8cgi.conf"
	os_string = "posix"
# endif 

# command line options
opts = Options()
opts.Add(BoolOption("mysql", "MySQL library", 1))
opts.Add(BoolOption("gd", "GD library", 1))
opts.Add(BoolOption("module", "Build Apache module", 1))
opts.Add(BoolOption("cgi", "Build CGI binray", 1))
opts.Add(BoolOption("fcgi", "FastCGI support (for CGI binary)", 0))

opts.Add(("mysqlpath", "MySQL header path", mysql_include))
opts.Add(("apachepath", "Apache header path", apache_include))
opts.Add(("aprpath", "APR header path", apr_include))

opts.Add(PathOption("v8path", "Directory with V8", "../v8"))
opts.Add(EnumOption("os", "Operating system", os_string, allowed_values = ["windows", "posix"]))
opts.Add(("conffile", "Config file", config_path))

env = Environment(options=opts)

# default values
env.Append(
    LIBS = ["v8"], 
    CPPPATH = ["src"], 
    CCFLAGS = ["-Wall", "-O3", "-m32"], 
    CPPDEFINES = [],
    LIBPATH = "",
    LINKFLAGS = ["-m32"]
)

if env["os"] == "posix":
	env.Append(
		LIBS = ["pthread"]
	)
# if

Help(opts.GenerateHelpText(env))
conf = Configure(env)

# adjust variables based on user selection
if conf.CheckCHeader("unistd.h", include_quotes = "<>"):
    env.Append(CPPDEFINES = "HAVE_UNISTD_H")

if conf.CheckCHeader("dirent.h", include_quotes = "<>"):
    env.Append(CPPDEFINES = "HAVE_DIRENT_H")

if conf.CheckCHeader("sys/mman.h", include_quotes = "<>"):
    env.Append(CPPDEFINES = "HAVE_MMAN_H")

if not conf.CheckFunc("close"):
    env.Append(CPPDEFINES = "HAVE_WINSOCK")

if conf.CheckFunc("mkdir"):
    env.Append(CPPDEFINES = "HAVE_MKDIR")

if conf.CheckFunc("rmdir"):
    env.Append(CPPDEFINES = "HAVE_RMDIR")

if conf.CheckFunc("chdir"):
    env.Append(CPPDEFINES = "HAVE_CHDIR")

if conf.CheckFunc("getcwd"):
    env.Append(CPPDEFINES = "HAVE_GETCWD")

if conf.CheckFunc("sleep"):
    env.Append(CPPDEFINES = "HAVE_SLEEP")
	
if ((env["os"] != "windows") and not (conf.CheckLib("v8"))):
	print "Cannot find V8 library!"
# if

env = conf.Finish()

env.Append(
    CPPDEFINES = ["CONFIG_PATH=" + env["conffile"], env["os"]],
    CPPPATH = env["v8path"] + "/include",
    LIBPATH = env["v8path"]
)

if env["os"] == "posix":
    env.Append(LIBS = ["dl"])
# if

if env["os"] == "windows":
	env.Append(
		LIBS = ["ws2_32"],
		CPPDEFINES = ["USING_V8_SHARED", "WIN32"],
		LIBPATH = os.environ["LIBPATH"].split(";"),
		CPPPATH = os.environ["INCLUDE"].split(";")
	)
# if

if env["fcgi"] == 1:
	env.Append(
		LIBS = ["fcgi"],
		CPPPATH = ["src/fcgi/include"],
		CPPDEFINES = ["FASTCGI"]
	)
# if

if env["mysql"] == 1:
	e = env.Clone()
	if env["os"] == "windows":
		e.Append(
			LIBS = ["wsock32", "user32", "advapi32"],
			LINKFLAGS = ["/nodefaultlib:\"libcmtd\""]
		)
	# if
	e.Append(
		CPPPATH = env["mysqlpath"],
		LIBS = "mysqlclient"
	)
	e.SharedLibrary(
		target = "lib/libmysql", 
		source = ["src/js_gc.cc", "src/lib/mysql/js_mysql.cc"],
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
		target = "lib/libgd", 
		source = "src/lib/gd/js_gd.cc",
		SHLIBPREFIX=""
	)
# if


if env["module"] == 1:
	e = env.Clone()
	e.Append(
		CPPPATH = [env["apachepath"], env["aprpath"]]
	)
	if env["os"] == "windows":
		e.Append(
			LIBS = ["libapr-1", "libhttpd"]
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
	sources.append("src/v8cgi.cc")
	env.Program(
		source = sources, 
		target = "v8cgi"
	)
# if

import sys

# default values
libs = ["v8"]
libpath = []
cpppath = ["src"]
ccflags = ["-Wall", "-O3"]
cppdefines = []
target = "v8cgi"

config_path = ""
mysql_include = ""
os = ""

# platform-based default values
if sys.platform.find("win") != -1:
    mysql_include = "c:/"
    config_path = "c:/windows/v8cgi.conf"
    os = "windows"
else:
    mysql_include = "/usr/include/mysql"
    config_path = "/etc/v8cgi.conf"
    os = "posix"
# endif 

# base source files
sources = [
    "v8cgi.cc", 
    "js_common.cc", 
    "js_system.cc", 
    "js_io.cc"
]

# command line options
opts = Options()
opts.Add(BoolOption("mysql", "MySQL support", 0))
opts.Add(PathOption("mysqlpath", "MySQL header path", mysql_include))
opts.Add(PathOption("v8path", "Directory with V8", "../v8"))
opts.Add(("conffile", "Config file", config_path))
opts.Add(EnumOption("os", "Operating system", os, allowed_values = ["windows", "posix"]))

env = Environment(options=opts)
Help(opts.GenerateHelpText(env))
conf = Configure(env)

# adjust variables based on user selection
if conf.CheckCHeader("unistd.h", include_quotes = "<>"):
    cppdefines.append("HAVE_UNISTD_H")

if conf.CheckCHeader("dirent.h", include_quotes = "<>"):
    cppdefines.append("HAVE_DIRENT_H")

if conf.CheckFunc("mkdir"):
    cppdefines.append("HAVE_MKDIR")

env = conf.Finish()

cppdefines.append("CONFIG_PATH=" + env["conffile"])
cppdefines.append(env["os"])
libpath.append(env["v8path"])
cpppath.append(env["v8path"] + "/include")

if env["os"] == "posix":
    libs.append("pthread")
# if

if env["os"] == "windows":
    cppdefines.append("USING_V8_SHARED")
    libpath.append(os.environ.pop("LIB"))
    libpath.append(os.environ.pop("LIBPATH"))
# if

if env["mysql"] == 1:
    sources.append("js_mysql.cc")    
    libs.append("mysqlclient")
    cpppath.append(env["mysqlpath"])
    cppdefines.append("HAVE_MYSQL")
# if

sources = [ "src/%s" % s for s in sources ]

Program(
    source = sources, 
    target = target, 
    LIBS=libs, 
    CPPPATH=cpppath, 
    CCFLAGS=ccflags, 
    CPPDEFINES=cppdefines,
    LIBPATH=libpath
)

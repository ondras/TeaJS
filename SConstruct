import sys

libs = ["v8", "pthread"]
cpppath = ["src", "../v8/include"]
ccflags = ["-Wall", "-O3"]
cppdefines = []
target = "v8cgi"

config_path = ""
mysql_include = ""
os = ""

if sys.platform.find("win") != -1:
    mysql_include = "c:/"
    config_path = "c:/windows/v8cgi.conf"
    os = "windows"
else:
    mysql_include = "/usr/include/mysql"
    config_path = "/etc/v8cgi.conf"
    os = "posix"
# endif 

opts = Options()
opts.Add(BoolOption("mysql", "MySQL support", 0))
opts.Add(PathOption("mysqlpath", "MySQL header path", mysql_include))
opts.Add(("conffile", "Config file", config_path))
opts.Add(EnumOption("os", "Operating system", os, allowed_values = ["windows", "posix"]))

env = Environment(options=opts)
Help(opts.GenerateHelpText(env))
conf = Configure(env)

if conf.CheckCHeader("unistd.h", include_quotes = "<>"):
    cppdefines.append("HAVE_UNISTD_H")

if conf.CheckCHeader("dirent.h", include_quotes = "<>"):
    cppdefines.append("HAVE_DIRENT_H")

if conf.CheckFunc("mkdir"):
    cppdefines.append("HAVE_MKDIR")


env = conf.Finish()

sources = [
    "v8cgi.cc", 
    "js_common.cc", 
    "js_system.cc", 
    "js_io.cc"
]

cppdefines.append("CONFIG_PATH=" + env["conffile"])
cppdefines.append(env["os"])

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
    CPPDEFINES=cppdefines
)

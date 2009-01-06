import sys
import os

config_path = ""
mysql_include = ""
os_string = ""

# platform-based default values
if sys.platform.find("win") != -1:
    mysql_include = "c:/"
    config_path = "c:/v8cgi.conf"
    os_string = "windows"
else:
    mysql_include = "/usr/include/mysql"
    config_path = "/etc/v8cgi.conf"
    os_string = "posix"
# endif 


# command line options
opts = Options()
opts.Add(BoolOption("mysql", "MySQL support", 0))
opts.Add(BoolOption("gd", "GD support", 0))
opts.Add(PathOption("mysqlpath", "MySQL header path", mysql_include))
opts.Add(PathOption("v8path", "Directory with V8", "../v8"))
opts.Add(("conffile", "Config file", config_path))
opts.Add(EnumOption("os", "Operating system", os_string, allowed_values = ["windows", "posix"]))

env = Environment(options=opts)

# default values
env.Append(
    LIBS = ["v8", "dl"], 
    CPPPATH = ["src"], 
    CCFLAGS = ["-Wall", "-O3"], 
    CPPDEFINES = [],
    LIBPATH = "",
    LINKFLAGS = []
)

Help(opts.GenerateHelpText(env))
conf = Configure(env)

# adjust variables based on user selection
if conf.CheckCHeader("unistd.h", include_quotes = "<>"):
    env.Append(CPPDEFINES = "HAVE_UNISTD_H")

if conf.CheckCHeader("dirent.h", include_quotes = "<>"):
    env.Append(CPPDEFINES = "HAVE_DIRENT_H")

if conf.CheckFunc("mkdir"):
    env.Append(CPPDEFINES = "HAVE_MKDIR")

if conf.CheckFunc("rmdir"):
    env.Append(CPPDEFINES = "HAVE_RMDIR")

if conf.CheckFunc("chdir"):
    env.Append(CPPDEFINES = "HAVE_CHDIR")

if conf.CheckFunc("getcwd"):
    env.Append(CPPDEFINES = "HAVE_GETCWD")

env = conf.Finish()

env.Append(
    CPPDEFINES = ["CONFIG_PATH=" + env["conffile"], env["os"]],
    CPPPATH = env["v8path"] + "/include",
    LIBPATH = env["v8path"]
)

if env["os"] == "posix":
    env.Append(LIBS = "pthread")
# if

if env["os"] == "windows":
    env.Append(
	    CPPDEFINES = "USING_V8_SHARED",
        LIBPATH = [os.environ.pop("LIB"), os.environ.pop("LIBPATH")],
        CPPPATH = os.environ.pop("INCLUDE")
    )
# if

if env["mysql"] == 1:
    e = env.Clone()
    if env["os"] == "windows":
        e.Append(
            LIBS = ["wsock32", "user32", "advapi32"],
            LINKFLAGS = "/nodefaultlib:\"libcmtd\""
        )
    # if
    e.Append(
        CPPPATH = env["mysqlpath"],
        LIBS = "mysqlclient"
    )
    e.SharedLibrary(
		target = "lib/mysql", 
		source = "src/lib/mysql/js_mysql.cc",
	)
# if

#if env["gd"] == 1:
#    sources.append("js_gd.cc")    
#    libs.append("gd")
#    cppdefines.append("HAVE_GD")
# if

# base source files
sources = [
    "v8cgi.cc", 
    "js_common.cc", 
    "js_system.cc", 
    "js_io.cc"
]
sources = [ "src/%s" % s for s in sources ]

env.Program(
    source = sources, 
    target = "v8cgi"
)

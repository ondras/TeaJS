import sys

libs = ["v8", "pthread"]
cpppath = ["src", "../v8/include"]
ccflags = ["-Wall", "-O3"]
cppdefines = {}
target = "v8cgi"

config_path = ""
mysql_include = ""


if sys.platform.find("win") != -1:
    mysql_include = ""
    config_path = "c:/windows/v8cgi.conf"
else:
    mysql_include = "/usr/include/mysql"
    config_path = "/etc/v8cgi.conf"
# endif 

opts = Options()
opts.Add(BoolOption("mysql", "MySQL support", 0))
opts.Add(PathOption("mysqlpath", "MySQL header path", mysql_include))
opts.Add(("conffile", "Config file", config_path))

env = Environment(options=opts)
Help(opts.GenerateHelpText(env))

sources = [
    "v8cgi.cc", 
    "common.cc", 
    "system.cc", 
    "io.cc"
]

cppdefines["CONFIG_PATH"] = env["conffile"]

if env["mysql"] == 1:
    sources.append("jsmysql.cc")    
    libs.append("mysqlclient")
    cpppath.append(env["mysqlpath"])
    cppdefines["HAVE_MYSQL"] = 1
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

libs = ["v8", "pthread"]
cpppath = ["src", "../v8/include"]
ccflags = ["-Wall", "-O3"]
cppdefines = {}
target = "v8cgi"

opts = Options()
opts.Add(BoolOption("mysql", "MySQL support", 0))
opts.Add(PathOption("mysqlpath", "MySQL header path", "/usr/include/mysql"))

env = Environment(options=opts)
Help(opts.GenerateHelpText(env))

sources = [
    "v8cgi.cc", 
    "common.cc", 
    "system.cc", 
    "io.cc"
]

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

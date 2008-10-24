libs = ["v8", "pthread"]
cpppath = ["src", "../v8/include"]
ccflags = ["-Wall"]
cppdefines = {}
target = "v8cgi"

opts = Options()
opts.Add(BoolOption("mysql", "MySQL support", 0))

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
    cpppath.append("/usr/include/mysql")
    cppdefines["HAVE_MYSQL"] = 1
# if

for index in range(len(sources)):
    sources[index] = "src/"+sources[index]
# for

Program(
    source = sources, 
    target = target, 
    LIBS=libs, 
    CPPPATH=cpppath, 
    CCFLAGS=ccflags, 
    CPPDEFINES=cppdefines
)

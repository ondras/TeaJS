CC = g++
CFLAGS = -Wall

# path to V8 headers
INCLUDES += -I ../v8/include
#path to MySQL headers
INCLUDES += -I /usr/include/mysql

INCLUDES += -I src

LIBS += -lv8
LIBS += -lpthread
LIBS += -lmysqlclient

SOURCE = src/v8cgi.cc src/common.cc src/io.cc src/system.cc src/jsmysql.cc
OBJECT = $(SOURCE:.cc=.o)

all: v8cgi

v8cgi: $(OBJECT)
	$(CC) $(CFLAGS) -o $@ $(LIBS) $(OBJECT)

.cc.o:
	$(CC) -o $@ -c $(CFLAGS) $(INCLUDES) $(@:.o=.cc)

clean:
	rm -rf src/*.o v8cgi

install:
	echo "Nothing yet!"

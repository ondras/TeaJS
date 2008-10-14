#!/bin/bash

INCLUDES=""
INCLUDES+=" -I ../v8/include"
INCLUDES+=" -I src"
INCLUDES+=" -I /usr/include/mysql"

LIBS=""
LIBS+=" -lv8";
LIBS+=" -lpthread";
LIBS+=" -lmysqlclient";

g++ -Wall -o v8cgi $INCLUDES $LIBS src/*.cc

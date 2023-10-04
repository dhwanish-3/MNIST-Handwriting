CC = g++
SRC = ./src
INCLUDE_DIR = ./include
CFLAGS = -std=c++11 -DEUCLID
LIB_DATA = libdata.so

all: main

main: src/knn.cc
	$(CC) $(CFLAGS) src/knn.cc -o main -L../lib/ -I./include -I../include -ldata

clean:
	rm main

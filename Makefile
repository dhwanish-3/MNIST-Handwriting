MNIST_ML_ROOT := $(PWD)
CC := g++
INCLUDE_DIR := ./include
SRC := ./src
CFLAGS := -shared -std=c++11 -g
LIB_DATA := libdata.so

all: $(LIB_DATA)

$(LIB_DATA): libdir objectdir obj/data_handler.o obj/data.o
	$(CC) $(CFLAGS) -o lib/$(LIB_DATA) obj/*.o
	rm -r obj

libdir:
	mkdir lib

objectdir:
	mkdir obj

obj/data_handler.o: $(SRC)/data_handler.cc
	$(CC) -fPIC $(CFLAGS) -o ./obj/data_handler.o -I$(INCLUDE_DIR) -c ./src/data_handler.cc

obj/data.o: $(SRC)/data.cc
	$(CC) -fPIC $(CFLAGS) -o ./obj/data.o -I$(INCLUDE_DIR) -c ./src/data.cc

clean:
	rm -r "C:\Users\dhwan\Documents\Programming\C++ Programming\Machine Learning\MNIST Handwriting\lib"
	rm -r "C:\Users\dhwan\Documents\Programming\C++ Programming\Machine Learning\MNIST Handwriting\obj"

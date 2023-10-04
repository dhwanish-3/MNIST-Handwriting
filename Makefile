MNIST_ML_ROOT := $(PWD)
CC := g++
INCLUDE_DIR := $(MNIST_ML_ROOT)/include
LIB_DIR := $(MNIST_ML_ROOT)/lib
SRC := $(MNIST_ML_ROOT)/src
CFLAGS := -std=c++11 -g
LIB_DATA := libdata.so

all: $(LIB_DATA)

$(LIB_DATA): libdir objectdir obj/data_handler.o obj/data.o
	$(CC) $(CFLAGS) -shared -o $(LIB_DIR)/$(LIB_DATA) obj/*.o
	rm -r obj

libdir:
	mkdir -p $(MNIST_ML_ROOT)/lib

objectdir:
	mkdir -p $(MNIST_ML_ROOT)/obj

obj/data_handler.o: $(SRC)/data_handler.cc
	$(CC) -fPIC $(CFLAGS) -o obj/data_handler.o -I$(INCLUDE_DIR) -c $(SRC)/data_handler.cc

obj/data.o: $(SRC)/data.cc
	$(CC) -fPIC $(CFLAGS) -o obj/data.o -I$(INCLUDE_DIR) -c $(SRC)/data.cc

clean:
	rm -r $(MNIST_ML_ROOT)/lib
	rm -r $(MNIST_ML_ROOT)/obj

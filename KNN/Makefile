CC=g++
KNN_ROOT := $(PWD)
MNIST_ML_ROOT := $(KNN_ROOT)/../../MNIST_Handwriting
SRC := $(KNN_ROOT)/src
CFLAGS := -std=c++11 -DEUCLID
INCLUDE_DIR := $(KNN_ROOT)/include/

all: main

main : $(SRC)/knn.cc
	$(CC) $(CFLAGS) $(SRC)/knn.cc -o main -L$(MNIST_ML_ROOT)/lib/ -I$(INCLUDE_DIR) -I$(MNIST_ML_ROOT)/include -ldata

clean:
	rm main
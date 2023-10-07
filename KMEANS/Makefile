CC=g++
KMEANS_ROOT := $(PWD)
MNIST_ML_ROOT := $(KMEANS_ROOT)/../../MNIST_Handwriting
SRC := $(KMEANS_ROOT)/src
CFLAGS := -std=c++11
INCLUDE_DIR := $(KMEANS_ROOT)/include/

all: main

main : $(SRC)/kmeans.cc
	$(CC) $(CFLAGS) $(SRC)/kmeans.cc -o main -L$(MNIST_ML_ROOT)/lib/ -I$(INCLUDE_DIR) -I$(MNIST_ML_ROOT)/include -ldata

clean:
	rm main
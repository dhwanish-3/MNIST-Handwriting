#! /bin/bash

if [[ -z $MNIST_ML_ROOT ]]; then
    echo "Please define MNIST_ML_ROOT in your environment"
    exit 1
fi

dir=$(echo "$@" | tr a-z A-Z) # convert to upper case
model_name_lower=$(echo "$@" | tr A-Z a-z) # convert to lower case

mkdir -p $MNIST_ML_ROOT/$dir/include $MNIST_ML_ROOT/$dir/src
touch $MNIST_ML_ROOT/$dir/Makefile
touch $MNIST_ML_ROOT/$dir/include/"$model_name_lower.hpp"
touch $MNIST_ML_ROOT/$dir/src/"$model_name_lower.cc"
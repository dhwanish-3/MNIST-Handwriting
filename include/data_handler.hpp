#ifndef __DATA_HANDLER_H
#define __DATA_HANDLER_H

#include <vector>
#include <map>
#include <stdint.h>
#include <string>
#include "data.hpp"
using namespace std;

class DataHandler{
    vector<Data*> *data_array; // all data before splitting
    vector<Data*> *training_data;
    vector<Data*> *test_data;
    vector<Data*> *validation_data;

    int num_classes;
    int feature_vector_size;
    map<uint8_t,int> class_map;

    const double TRAIN_SET_PERCENT=0.75;
    const double TEST_SET_PERCENT=0.20;
    const double VALIDATION_PERCENT=0.05;

    public:
    DataHandler();
    ~DataHandler();

    void read_feature_vector(string path);
    void read_feature_label(string path);
    void split_data();
    void count_classes();

    uint32_t convert_to_little_endian(const unsigned char* bytes);

    int get_num_classes();
    vector<Data*> * get_training_data();
    vector<Data*> * get_test_data();
    vector<Data*> * get_validation_data();
};

#endif
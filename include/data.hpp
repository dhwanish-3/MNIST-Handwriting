#ifndef __DATA_H
#define __DATA_H

#include <vector>
#include <stdint.h>
using namespace std;

class Data{
    vector<uint8_t>* feature_vector; // No class at end
    vector<double>* double_feature_vector;
    vector<int>* class_vector;
    uint8_t label;
    int enum_label; // A=1 , B=2
    double distance;

    public:
    Data();
    ~Data();
    void set_feature_vector(vector<uint8_t>*);
    void set_feature_vector(vector<double>*);
    void append_to_feature_vector(uint8_t);
    void append_to_feature_vector(double);
    void set_class_vector(int count);
    void set_label(uint8_t);
    void set_enumeric_label(int);
    void set_distance(double);
    double get_distance();

    int get_feature_vector_size();
    uint8_t get_label();
    int get_enumeric_label();

    vector<uint8_t>* get_feature_vector();
    vector<double>* get_double_feature_vector();
    vector<int>* get_class_vector();
};

#endif
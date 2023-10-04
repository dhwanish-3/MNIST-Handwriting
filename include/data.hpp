#ifndef __DATA_H
#define __DATA_H

#include <vector>
#include <stdint.h>
using namespace std;

class Data{
    vector<uint8_t>* feature_vector; // No class at end
    uint8_t label;
    int enum_label; // A=1 , B=2
    double distance;

    public:
    Data();
    ~Data();
    void set_feature_vector(vector<uint8_t>*);
    void append_to_feature_vector(uint8_t);
    void set_label(uint8_t);
    void set_enumeric_label(int);
    void set_distance(double);

    int get_feature_vector_size();
    uint8_t get_label();
    int get_enumeric_label();

    vector<uint8_t>* get_feature_vector();
};

#endif
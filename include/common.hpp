#ifndef __COMMON_HPP
#define __COMMON_HPP

#include <vector>
#include "data.hpp"
using namespace std;
class commonData {
    protected:
        vector<Data*>* training_data;
        vector<Data*>* test_data;
        vector<Data*>* validation_data;

    public:
    void set_training_data(vector<Data*>* training_data);
    void set_test_data(vector<Data*>* test_data);
    void set_validation_data(vector<Data*>* validation_data);
};

#endif
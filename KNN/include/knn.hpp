#ifndef __KNN_H
#define __KNN_H

#include "../../include/common.hpp"
using namespace std;

class kNN : public commonData {
    int k;
    vector<Data*>* neighbours;

    public:
    kNN(int);
    kNN();
    ~kNN();

    void find_k_nearest_neighbours(Data* query_point);
    void set_k(int val);

    int predict();
    double calculate_distance(Data* query_point, Data* input);
    double validate_performance();
    double test_performance();
};

#endif
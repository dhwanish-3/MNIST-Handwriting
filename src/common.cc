#include "../include/common.hpp"
#include <vector>
using namespace std;

void commonData::set_training_data(vector<Data*>* vect) {
    training_data = vect;
}
void commonData::set_test_data(vector<Data*>* vect) {
    test_data = vect;
}
void commonData::set_validation_data(vector<Data*>* vect) {
    validation_data = vect;
}
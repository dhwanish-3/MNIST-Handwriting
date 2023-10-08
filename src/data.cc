#include "../include/data.hpp"
#include <bits/stdc++.h>
using namespace std;

Data::Data(){
    feature_vector=new vector<uint8_t>;
}
Data::~Data(){

}

void Data::set_feature_vector(vector<uint8_t> * v){
    feature_vector=v;
}
void Data::set_feature_vector(vector<double> * v){
    double_feature_vector=v;
}
void Data::append_to_feature_vector(uint8_t val){
    feature_vector->push_back(val);
}
void Data::append_to_feature_vector(double val){
    double_feature_vector->push_back(val);
}
void Data::set_label(uint8_t val){
    label=val;
}
void Data::set_enumeric_label(int val){
    enum_label=val;
}
void Data::set_class_vector(int count){
    class_vector = new vector<int>();
    for (int i = 0; i < count; i++) {
        if (i == label) {
            class_vector->push_back(1);
        } else {
            class_vector->push_back(0);
        }
    }
}

void Data::set_distance(double val){
    distance = val;
}

double Data::get_distance(){
    return distance;
}

int Data::get_feature_vector_size(){
    return feature_vector->size();
}
uint8_t Data::get_label(){
    return label;
}
int Data::get_enumeric_label(){
    return enum_label;
}

vector<uint8_t>* Data::get_feature_vector(){
    return feature_vector;
}
vector<double>* Data::get_double_feature_vector(){
    return double_feature_vector;
}
vector<int>* Data::get_class_vector(){
    return class_vector;
}
#include <bits/stdc++.h>
#include "../include/data_handler.hpp"
using namespace std;

DataHandler::DataHandler(){
    data_array=new vector<Data*>;
    test_data=new vector<Data*>;
    training_data=new vector<Data*>;
    validation_data=new vector<Data*>;
}

DataHandler::~DataHandler(){

}

void DataHandler:: read_feature_vector(string path){
    uint32_t header[4]; // [magic , num images , row_size , column_size]
    unsigned char bytes[4];
    FILE* file=fopen(path.c_str(),"rb"); // "r" can be changed to "rb" if did not work
    if(file){
        for(int i=0;i<4;i++){
            if(fread(bytes,sizeof(bytes),1,file)){
                header[i]=convert_to_little_endian(bytes);
            }
        }
        cout<<"Done getting input file header"<<endl;
        int image_size=header[2]*header[3];
        for(int i=0;i<header[1];i++){
            Data* data=new Data();
            uint8_t element[1];
            for(int j=0;j<image_size;j++){
                if(fread(element,sizeof(element),1,file)){
                    data->append_to_feature_vector(element[0]);
                }else{
                    cout<<"Error reading from file"<<endl;
                    exit(1);
                }
            }
            data_array->push_back(data);
        }
        cout<<"Successfully stored feature vector "<<data_array->size()<<endl;
    }else{
        cout<<"Could not find file"<<endl;
    }
}

void DataHandler::read_feature_label(string path){
    uint32_t header[2]; // [magic , num images]
    unsigned char bytes[4];
    FILE* file=fopen(path.c_str(),"r"); // "r" can be changed to "rb" if did not work
    if(file){
        for(int i=0;i<2;i++){
            if(fread(bytes,sizeof(bytes),1,file)){
                header[i]=convert_to_little_endian(bytes);
            }
        }
        cout<<"Done getting label file headder"<<endl;
        for(int i=0;i<header[1];i++){
            uint8_t element[1];
            if(fread(element,sizeof(element),1,file)){
                data_array->at(i)->set_label(element[0]);
            }else{
                cout<<"Error reading from file"<<endl;
                exit(1);
            }
        }
        cout<<"Successfully stored label "<<data_array->size()<<endl;
    }else{
        cout<<"Could not find file"<<endl;
        exit(1);
    }
}
void DataHandler::split_data(){
    unordered_set<int> used_indices;
    int train_size=data_array->size()*TRAIN_SET_PERCENT;
    int test_size=data_array->size()*TEST_SET_PERCENT;
    int valid_size=data_array->size()*VALIDATION_PERCENT;

    // Training data
    int count=0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0,100000);
    while(count<train_size){
        // int random_index=rand()%data_array->size(); // rand() gives random number till 32768 only which is less than tran_size
        int random_index=distribution(gen)%data_array->size();
        if(used_indices.find(random_index)==used_indices.end()){
            training_data->push_back(data_array->at(random_index));
            used_indices.insert(random_index);
            count++;
        }
    }
    // Test data
    count=0;
    while(count<test_size){
        int random_index=distribution(gen)%data_array->size();
        if(used_indices.find(random_index)==used_indices.end()){
            test_data->push_back(data_array->at(random_index));
            used_indices.insert(random_index);
            count++;
        }
    }
    // Test data
    count=0;
    while(count<valid_size){
        int random_index=distribution(gen)%data_array->size();
        if(used_indices.find(random_index)==used_indices.end()){
            validation_data->push_back(data_array->at(random_index));
            used_indices.insert(random_index);
            count++;
        }
    }

    cout<<"Training data size : "<<training_data->size()<<endl;
    cout<<"Testing data size : "<<test_data->size()<<endl;
    cout<<"Validation data size : "<<validation_data->size()<<endl;
}
void DataHandler::count_classes(){
    int count=0;
    for(unsigned i=0;i<data_array->size();i++){
        if(class_map.find(data_array->at(i)->get_label())==class_map.end()){
            class_map[data_array->at(i)->get_label()]=count;
            data_array->at(i)->set_enumeric_label(count);
            count++;
        }
    }
    num_classes=count;
    cout<<"Successfully extracted "<<num_classes<<" unique classes"<<endl;
}

uint32_t DataHandler::convert_to_little_endian(const unsigned char* bytes){
    return (uint32_t)((bytes[0]<<24) | (bytes[1]<<16) | (bytes[2]<<8) | (bytes[3]));
}

vector<Data*> * DataHandler::get_training_data(){
    return training_data;
}
vector<Data*> * DataHandler::get_test_data(){
    return test_data;
}
vector<Data*> * DataHandler::get_validation_data(){
    return validation_data;
}


int main(){
    DataHandler* data_handler=new DataHandler();
    data_handler->read_feature_vector("data/train-images.idx3-ubyte");
    data_handler->read_feature_label("data/train-labels.idx1-ubyte");
    data_handler->split_data();
    data_handler->count_classes();
    return 0;
}
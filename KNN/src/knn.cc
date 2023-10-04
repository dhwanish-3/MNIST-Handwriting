#include "../include/knn.hpp"
#include <iostream>
#include <queue>
#include <cmath>
#include <limits>
#include <map>
#include <stdint.h>
#include "../../include/data_handler.hpp"

using namespace std;

kNN::kNN(int val) {
    k = val;
}
kNN::kNN() {
    // Nothing to do
}
kNN::~kNN() {
    // Nothing to do
}

struct compare {
    bool operator()(Data* d1, Data* d2) {
        return d1->get_distance() > d2->get_distance();
    }
};

void kNN::find_k_nearest_neighbours(Data* query_point) {
    neighbours = new vector<Data*>();
    double min = numeric_limits<double>::max();
    double prev_min = min;
    int index = 0;

    // inefficient implementation
    // for (int i = 0; i < k; i++) {
    //     if (i == 0) {
    //         for (int j = 0; j < training_data->size(); j++) {
    //             double distance = calculate_distance(query_point, training_data->at(j));
    //             training_data->at(j)->set_distance(distance);
    //             if (distance < min) {
    //                 min = distance;
    //                 index = j;
    //             }
    //         }
    //         neighbours->push_back(training_data->at(index));
    //         prev_min = min;
    //         min = numeric_limits<double>::max();
    //     } else {
    //         for (int j = 0; j < training_data->size(); i++) {
    //             double distance = calculate_distance(query_point, training_data->at(j));
    //             training_data->at(j)->set_distance(distance);
    //             if (distance < min && distance > prev_min) {
    //                 min = distance;
    //                 index = j;
    //             }
    //         }
    //         neighbours->push_back(training_data->at(index));
    //         prev_min = min;
    //         min = numeric_limits<double>::max();
    //     }
    // }

    // doing the same thing done above using priority queue
    priority_queue<Data*, vector<Data*>, compare> pq;
    for (int i = 0; i < training_data->size(); i++) {
        double distance = calculate_distance(query_point, training_data->at(i));
        training_data->at(i)->set_distance(distance);
        pq.push(training_data->at(i));
    }
    for (int i = 0; i < k; i++) {
        neighbours->push_back(pq.top());
        pq.pop();
    }
}
void kNN::set_training_data(vector<Data*>* vect) {
    training_data = vect;
}
void kNN::set_test_data(vector<Data*>* vect) {
    test_data = vect;
}
void kNN::set_validation_data(vector<Data*>* vect) {
    validation_data = vect;
}
void kNN::set_k(int val) {
    k = val;
}

int kNN::predict() {
    map<uint8_t, int> class_freq;
    for (int i = 0; i < neighbours->size(); i++) {
        if (class_freq.find(neighbours->at(i)->get_label()) == class_freq.end()) {
            class_freq[neighbours->at(i)->get_label()] = 1;
        } else {
            class_freq[neighbours->at(i)->get_label()]++;
        }
    }
    int best = 0;
    int max = 0;
    for (auto kv : class_freq) {
        if (kv.second > max) {
            max = kv.second;
            best = kv.first;
        }
    }
    delete neighbours;
    return best;
}

double kNN::calculate_distance(Data* query_point, Data* input) {
    double distance = 0;
    if (query_point->get_feature_vector_size() != input->get_feature_vector_size()) {
        cout << "Error: Feature vector sizes do not match" << endl;
        exit(1);
    }
    #ifdef EUCLID
        for (unsigned i = 0; i < query_point->get_feature_vector_size(); i++) {
            distance += pow(query_point->get_feature_vector()->at(i) - input->get_feature_vector()->at(i), 2);
        }
        distance = sqrt(distance);
    #elif defined MANHATTAN
        for (unsigned i = 0; i < query_point->get_feature_vector_size(); i++) {
            distance += abs(query_point->get_feature_vector()->at(i) - input->get_feature_vector()->at(i));
        }
    #elif defined CHEBYSHEV
        for (unsigned i = 0; i < query_point->get_feature_vector_size(); i++) {
            double temp = abs(query_point->get_feature_vector()->at(i) - input->get_feature_vector()->at(i));
            if (temp > distance) {
                distance = temp;
            }
        }
    #else
        cout << "Error: No distance metric defined" << endl;
        exit(1);
    #endif
    return distance;
}

double kNN::validate_performance() {
    double curr_performance = 0;
    int count = 0;
    int data_index = 0;
    for (Data* query_point : *validation_data) {
        find_k_nearest_neighbours(query_point);
        int prediction = predict();
        cout << prediction << " -> ";
        printf("%d\n", query_point->get_label());
        if (prediction == query_point->get_label()) {
            count++;
        }
        data_index++; 
        cout << "Current performance " << ((double)((count * 100) / data_index)) << endl;
    }
    curr_performance = ((double)((count * 100) / validation_data->size()));
    cout << "Validation performance for k = " << k << " : " << curr_performance << endl;
    return curr_performance;
}

double kNN::test_performance() {
    double curr_performance = 0;
    int count = 0;
    for (Data* data : *test_data) {
        find_k_nearest_neighbours(data);
        int prediction = predict();
        if (prediction == data->get_label()) {
            count++;
        }
    }
    curr_performance = ((double)((count * 100) / test_data->size()));
    cout << "Test performance: " << curr_performance << endl;
    return curr_performance;
}

int main () {
    DataHandler* dh = new DataHandler();
    cout << "Reading data..." << endl;
    dh->read_feature_vector("../data/train-images.idx3-ubyte");
    dh->read_feature_label("../data/train-labels.idx1-ubyte");
    dh->split_data();
    dh->count_classes();
    kNN* knn = new kNN();
    knn->set_training_data(dh->get_training_data());
    knn->set_test_data(dh->get_test_data());
    knn->set_validation_data(dh->get_validation_data());
    double performance = 0;
    double best_performance = 0;
    int best_k = 10;
    knn->set_k(best_k);
    performance = knn->validate_performance();
    cout << "performance : " << performance << endl;
    // for (int i = 1; i <= 10; i++) {
    //     knn->set_k(i);
    //     performance = knn->validate_performance();
    //     if (performance > best_performance) {
    //         best_performance = performance;
    //         best_k = i;
    //     }
    // }
    // cout << "Best k: " << best_k << endl;
    // knn->set_k(best_k);
    // knn->test_performance();
    return 0;
}
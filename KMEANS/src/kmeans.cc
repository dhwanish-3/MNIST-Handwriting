#include "../include/kmeans.hpp"
#include <iostream>
using namespace std;

kMeans::kMeans(int k) {
    numClusters = k;
    usedIndexes = new unordered_set<int>();
    clusters = new vector<cluster_t*>();
}

void kMeans::initClusters() {
    for (int i = 0; i < numClusters; i++) {
        int index = rand() % training_data->size();
        while (usedIndexes->find(index) != usedIndexes->end()) {
            index = rand() % training_data->size();
        }
        clusters->push_back(new cluster_t(training_data->at(index)));
        usedIndexes->insert(index);
    }
}

void kMeans::initClustersForEachClass() {
    unordered_set<int> classes_used;
    for (int i = 0; i < training_data->size(); i++) {
        int label = training_data->at(i)->get_label();
        if (classes_used.find(label) == classes_used.end()) {
            clusters->push_back(new cluster_t(training_data->at(i)));
            classes_used.insert(label);
            usedIndexes->insert(i);
        }
    }
}

void kMeans::train() {
    while (usedIndexes->size() < training_data->size()) {
        int index = rand() % training_data->size();
        while (usedIndexes->find(index) != usedIndexes->end()) {
            index = rand() % training_data->size();
        }
        double minDist = numeric_limits<double>::max();
        int bestCluster = -1;
        for (int j = 0; j < clusters->size(); j++) {
            double dist = euclideanDistance(clusters->at(j)->centroid, training_data->at(index));
            if (dist < minDist) {
                minDist = dist;
                bestCluster = j;
            }
        }
        clusters->at(bestCluster)->add_to_cluster(training_data->at(index));
        usedIndexes->insert(index);
    }
}

double kMeans::euclideanDistance(vector<double>* centroid, Data* point) {
    double dist = 0;
    for (int i = 0; i < centroid->size(); i++) {
        dist += pow(centroid->at(i) - point->get_feature_vector()->at(i), 2);
    }
    return sqrt(dist);
}

double kMeans::validate() {
    double numCorrect = 0;
    for (auto query_point : *validation_data) {
        double minDist = numeric_limits<double>::max();
        int bestCluster = -1;
        for (int j = 0; j < clusters->size(); j++) {
            double dist = euclideanDistance(clusters->at(j)->centroid, query_point);
            if (dist < minDist) {
                minDist = dist;
                bestCluster = j;
            }
        }
        if (clusters->at(bestCluster)->mostFrequentClass == query_point->get_label()) {
            numCorrect++;
        }
    }
    return 100 * (numCorrect / (double)validation_data->size());
}

double kMeans::test() {
    double numCorrect = 0;
    for (auto query_point : *test_data) {
        double minDist = numeric_limits<double>::max();
        int bestCluster = -1;
        for (int j = 0; j < clusters->size(); j++) {
            double dist = euclideanDistance(clusters->at(j)->centroid, query_point);
            if (dist < minDist) {
                minDist = dist;
                bestCluster = j;
            }
        }
        if (clusters->at(bestCluster)->mostFrequentClass == query_point->get_label()) {
            numCorrect++;
        }
    }
    return 100 * (numCorrect / (double)test_data->size());
}

vector<cluster_t*>* kMeans::get_clusters() {
    return this->clusters;
}

int main() {
    DataHandler* dh = new DataHandler();
    cout << "Reading data..." << endl;
    dh->read_feature_vector("../data/train-images.idx3-ubyte");
    dh->read_feature_label("../data/train-labels.idx1-ubyte");
    dh->split_data();
    dh->count_classes();
    int best_k = 0;
    double best_performance = 0;
    for (int k = dh->get_num_classes(); k < dh->get_training_data()->size() * 0.1; k++) {
        kMeans* km = new kMeans(k);
        km->set_training_data(dh->get_training_data());
        km->set_test_data(dh->get_test_data());
        km->set_validation_data(dh->get_validation_data());
        km->initClusters();
        km->train();
        cout << "completed training for k = " << k << endl;
        double performance = km->validate();
        if (performance > best_performance) {
            best_performance = performance;
            best_k = k;
        }
        cout << "performance at k = "<< k << " : " << performance << "%" << endl;
    }
    cout << "Best k : " << best_k << endl;
    kMeans* km = new kMeans(best_k);
    km->set_training_data(dh->get_training_data());
    km->set_test_data(dh->get_test_data());
    km->set_validation_data(dh->get_validation_data());
    km->initClusters();
    km->train();
    cout << "Overall Test performance : " << km->test() << endl;
}
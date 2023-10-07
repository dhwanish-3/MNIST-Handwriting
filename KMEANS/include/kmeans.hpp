#ifndef __KMEANS_HPP
#define __KMEANS_HPP

#include "../../include/common.hpp"
#include "../../include/data_handler.hpp"
#include <unordered_set>
#include <limits>
#include <cstdlib>
#include <cmath>
#include <map>
using namespace std;

typedef struct cluster {
    vector<Data*>* clusterPoints;
    vector<double>* centroid;
    map<int, int> classCount;
    int mostFrequentClass;
    cluster(Data* initialPoint) {
        centroid = new vector<double>;
        clusterPoints = new vector<Data*>;
        for (auto val : *(initialPoint->get_feature_vector())) {
            centroid->push_back(val);
        }
        clusterPoints->push_back(initialPoint);
        classCount[initialPoint->get_label()] = 1;
        mostFrequentClass = initialPoint->get_label();
    }

    void add_to_cluster(Data* point) {
        int prevSize = clusterPoints->size();
        clusterPoints->push_back(point);
        for (int i = 0; i < centroid->size() - 1; i++) {
            double val = centroid->at(i);
            val *= prevSize;
            val += point->get_feature_vector()->at(i);
            val /= (double)clusterPoints->size();
            centroid->at(i) = val;
        }
        if (classCount.find(point->get_label()) == classCount.end()) {
            classCount[point->get_label()] = 1;
        } else {
            classCount[point->get_label()]++;
        }
        set_most_frequent_class();
    }

    void set_most_frequent_class() {
        int bestClass = -1;
        int bestCount = 0;
        for (auto kv : classCount) {
            if (kv.second > bestCount) {
                bestCount = kv.second;
                bestClass = kv.first;
            }
        }
        mostFrequentClass = bestClass;
    }
} cluster_t;

class kMeans : public commonData {
    int numClusters;
    vector<cluster_t*>* clusters;
    unordered_set<int>* usedIndexes;
    public:
    kMeans(int k);
    void initClusters();
    void initClustersForEachClass();
    void train();
    double euclideanDistance(vector<double>*, Data*);
    double validate();
    double test();
    vector<cluster_t*>* get_clusters();
};

#endif
#include <iostream>
#include <random>
#include <vector>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 100000);

    for(int i=0;i<100000;i++){
        int random_index = distribution(gen);
        std::cout << "Random Index: " << random_index << std::endl;
    }
    return 0;
}

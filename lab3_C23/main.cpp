#include <iostream>
#include "marker.h"
int main() {
    int* array;
    int arrSize, numOfThreads;
    std::cout << "Input array size: ";
    std:: cin >> arrSize;
    std::cout << "Input number of threads: ";
    std:: cin >> numOfThreads;
    array = new int[arrSize];
    std::fill(array, array + arrSize, 0);
    
    return 0;
}

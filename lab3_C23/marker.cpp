#include "marker.h"
#include <cstdlib>
#include <iostream>
#include <windows.h>

void Marker::marker(int orderNumber){
    srand(orderNumber);
    int* changedElementsIndexes;
    changedElementsIndexes = new int[arrSize];
    int randomNum;
    int numOfMarks = 0;
    bool signal = true;

    while(signal) {
        randomNum = rand();
        randomNum %= arrSize;
        if (array[randomNum] == 0) {
            Sleep(5);
            array[randomNum] = orderNumber;
            Sleep(5);
            numOfMarks++;
        } else {
            {
                std::unique_lock<std::mutex> locker(lockPrint);
                std::cout << "Order number of the thread: " << orderNumber;
                std::cout << "Num of marked elements: " << numOfMarks;
                std::cout << "Index of element can not to change: " << randomNum;
            }

            {
                std::unique_lock<std::mutex> locker(lockQueue);
                markersWithErrorsQueue.push(orderNumber);
                markerStop.notify_one();
            }

            {
                std::unique_lock<std::mutex> locker(lockQueue);
                mainMade.wait(locker);
                if (markerToDestroy == orderNumber) {
                    signal = false;
                    for (int i = 0; i < numOfMarks; ++i) {
                        array[changedElementsIndexes[i]] = 0;
                    }
                }
            }
        }
    }
}





void Marker::markerMain() {
    int numOfThreads;
    std::cout << "Input array size: ";
    std:: cin >> arrSize;
    std::cout << "Input number of threads: ";
    std:: cin >> numOfThreads;
    array = new int[arrSize];
    std::fill(array, array + arrSize, 0);

}

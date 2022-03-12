#include "marker.h"
#include <cstdlib>
#include <iostream>
#include <windows.h>

void Marker::marker(int orderNumber){
    srand(orderNumber);
    int* changedElementsIndexes;
    changedElementsIndexes = new int[arrSize];
    std::fill(changedElementsIndexes, changedElementsIndexes + arrSize, -1);
    int k;
    int randomNum;
    int numOfMarks = 0;
    bool signal = true;

    while(signal)
    {
        randomNum = rand();
        randomNum %= arrSize;
        if(array[randomNum]==0){
            Sleep(5);
            array[randomNum] = orderNumber;
            Sleep(5);
            numOfMarks++;
        }
        else{
            {
                std::unique_lock<std::mutex> locker(lockPrint);
                std::cout<<"Order number of the thread: "<< orderNumber;
                std::cout<<"Num of marked elements: "<< numOfMarks;
                std::cout<<"Index of element can not to change: "<< randomNum;
            }

            {
                std::unique_lock <std::mutex> locker(lockQueue);
                markersWithErrorsQueue.push(orderNumber);
                markerStop.notify_one();

            }
            {
                std::unique_lock<std::mutex> locker(lockQueue);
                mainMade.wait(locker);
                if(markerToDestroy == orderNumber) {
                    signal = false;
                    k = 0;
                    while(changedElementsIndexes[k] != -1) {
                        array[changedElementsIndexes[k]] = 0;
                        ++k;
                    }
                }
            }
        }
    }



}

#include "marker.h"
#include <cstdlib>
#include <iostream>
#include <windows.h>

void marker(int* array, int arrSize, int orderNumber){
    srand(orderNumber);
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
            std::cout<<"Order number of the thread: "<< orderNumber;
            std::cout<<"Num of marked elements: "<< numOfMarks;
            std::cout<<"Index of element can not to change: "<< randomNum;
            signal = false;
        }
    }



}

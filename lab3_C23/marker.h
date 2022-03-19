//
// Created by lizam on 12.03.2022.
//

#ifndef LAB3_C23_MARKER_H
#define LAB3_C23_MARKER_H

#include <mutex>
#include <condition_variable>
#include <queue>

class Marker{
    int* array;
    int arrSize;
    int markerToDestroy = -1;
    std::mutex lockPrint;
    std::mutex lockQueue;
    std::condition_variable markerStop;
    std::condition_variable mainMade;
    std::queue<int> markersWithErrorsQueue;


public:
    void marker(int orderNumber);
    void markerMain();


};
#endif //LAB3_C23_MARKER_H

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <windows.h>
#include <vector>
std::mutex mtx,mtx1,mtx2,mtx3;
std::condition_variable cv,cv1,cv2;
int* array;
int arrSize;
int markerToDestroy = -1;
int numOfFinishedThreads;
bool continueDestroy = false, destructionFinished = false,continueWork =false;
void marker(int orderNumber){
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
            std::unique_lock<std::mutex> ul(mtx,std::defer_lock);
            Sleep(5);

            ul.lock();
            array[randomNum] = orderNumber;
            ul.unlock();
            Sleep(5);
            changedElementsIndexes[numOfMarks] = randomNum;
            numOfMarks++;

        } else {
            {
                std::lock_guard<std::mutex> locker(mtx);

                std::cout << "Order number of the thread: " << orderNumber<< std::endl;
                std::cout << "Num of marked elements: " << numOfMarks << std::endl;
                std::cout << "Index of element can not to change: " << randomNum<< std::endl;

            }

            {

                numOfFinishedThreads++;
                cv.notify_one();
            }
            {

                std::cout << "Waiting... \n";
                std::unique_lock<std::mutex> locker(mtx);
                cv.wait(locker, [&]() {
                    return continueDestroy;
                });
            }
            if(orderNumber==markerToDestroy){
                {

                    std::lock_guard<std::mutex> locker(mtx);
                    for (int i = 0; i < numOfMarks; ++i) {
                        array[changedElementsIndexes[i]] = 0;

                    }
                    std::cout << "dest... \n";
                    destructionFinished = true;
                    cv.notify_one();
                }

                signal = false;
            }
            else{
                {

                    std::cout << "Waiting... \n";
                    std::unique_lock<std::mutex> locker(mtx);
                    cv1.wait(locker, [&]() {
                        return continueWork;
                    });
                }
                std::cout << "stop wait... \n";
                signal = true;


            }

        }
    }
}
void printArray(){
    for (int i = 0; i < arrSize; ++i) {
        std::cout<<array[i];
    }
    std::cout << std::endl;
}
int main() {


    int numOfThreads;
    std::cout << "Input array size: ";
    std:: cin >> arrSize;
    std::cout << "Input number of threads: ";
    std:: cin >> numOfThreads;
    array = new int[arrSize];
    std::fill(array, array + arrSize, 0);

    std::vector<std::thread> threads;
    for (int i = 0; i < numOfThreads; ++i) {
        threads.push_back(std::thread(marker,i+1 ));
    }

    while(numOfThreads) {

        {
            std::unique_lock<std::mutex> locker(mtx);
            cv.wait(locker, [&]() {
                return numOfThreads == numOfFinishedThreads;
            });
        }
        continueWork = false;
        numOfFinishedThreads = 0;
        numOfThreads--;
        std::cout << "Array: ";
        printArray();
        std::cout << "Input number of thread to destroy: ";
        std::cin >> markerToDestroy;
        continueDestroy = true;
        cv.notify_all();


        std::cout << "Array: ";
        {
            std::unique_lock<std::mutex> locker1(mtx);
            cv.wait(locker1, [&]() {
                return destructionFinished;
            });
            printArray();
            continueWork = true;
        }
        cv1.notify_all();
        continueDestroy = false;
        destructionFinished = false;
        numOfThreads--;
    }
    for (int i = 0; i < threads.size(); ++i) {
        threads[i].join();
    }
    return 0;
}

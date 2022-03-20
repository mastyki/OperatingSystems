#include <iostream>
#include <mutex>
#include <condition_variable>
#include <windows.h>
#include <vector>
std::mutex mtxPrint;
std::mutex mtxArray;
std::mutex mtxWorker;
std::condition_variable cvWorker;
std::condition_variable cvMain;
int* array;
int arrSize;
int markerToDestroy = -1;
int numOfFinishedThreads;
bool continueDestroy = false, continueWork= false,isFinished = false;
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
            std::unique_lock<std::mutex> ulArray(mtxArray);
            Sleep(5);
            array[randomNum] = orderNumber;
            Sleep(5);
            numOfMarks++;
            ulArray.unlock();
        } else {
            {
                std::lock_guard<std::mutex> locker(mtxPrint);

                std::cout << "Order number of the thread: " << orderNumber<< std::endl;
                std::cout << "Num of marked elements: " << numOfMarks << std::endl;
                std::cout << "Index of element can not to change: " << randomNum<< std::endl;

            }

            {
                std::unique_lock<std::mutex> locker(mtxWorker);
                numOfFinishedThreads++;
                cvWorker.notify_one();
            }
            {
                std::unique_lock<std::mutex> locker(mtxWorker);
                std::cout << "Waiting... \n";
                cvMain.wait(locker,[&](){
                    return continueDestroy;
                });
            }
            if(orderNumber==markerToDestroy){
                for (int i = 0; i < numOfMarks; ++i) {
                    array[changedElementsIndexes[i]] = 0;
                }
                isFinished = true;
                cvWorker.notify_one();
                signal = false;
            }
            else{{
                    std::unique_lock<std::mutex> locker(mtxWorker);
                    std::cout << "Waiting... \n";
                    cvMain.wait(locker,[&](){
                        return continueWork;
                    });
                }
                signal = true;
                continue;

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
   while(numOfThreads){
       std::unique_lock<std::mutex> locker(mtxWorker);
       cvWorker.wait(locker,[&](){
           return numOfThreads == numOfFinishedThreads;
       });
       numOfFinishedThreads =0;
       numOfThreads--;
       std::cout<<"Array: ";
       printArray();
       std::cout << "Input number of thread to destroy: ";
       std:: cin >> markerToDestroy;
       continueDestroy = true;
       cvMain.notify_all();

       cvWorker.wait(locker,[&](){
           return true;
       });

       std::cout<<"Array: ";
       printArray();
       continueWork = true;
       cvMain.notify_all();

   }
    for (int i = 0; i < numOfThreads; ++i) {
        threads[i].join();
    }
    return 0;
}

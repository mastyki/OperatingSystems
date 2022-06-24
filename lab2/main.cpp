#include <iostream>
#include <windows.h>
struct Array
{
    int *arr;
    int arrSize;
    int minInd = 0;
    int maxInd = 0;
    int average;

    Array (int size){
        arrSize = size;
        arr = new int[arrSize];
        int elem;
        for(int i = 0; i < arrSize; ++i ){
            printf("Input array element: ");
            scanf("%d",&elem);
            arr[i] = elem;
        }
        printf("Initial array: ");
        print();
    }
    void print(){
        for(int i = 0; i < arrSize; ++i ){
            printf("%d ",arr[i]);
        }
        printf("\n");
    }
    ~Array (){
        delete[] arr;
    }
};

VOID Sleep(
        DWORD dwMilliseconds // миллисекунды
);
DWORD WINAPI minMax(LPVOID v)
{
    Array *array = (Array*)v;

    for (int i = 0; i < array->arrSize; i++){
        if(array->arr[i] < array->arr[array->minInd]){
            Sleep(7);
            array->minInd = i;
        }
        else if(array->arr[i]> array->arr[array->maxInd]){
            Sleep(7);
            array->maxInd = i;
        }
    }
    printf("Minimum element: %d \nMaximum element: %d\n",array->arr[array->minInd],array->arr[array->maxInd]);
    return 0;
}
DWORD WINAPI average(LPVOID v)
{
    Array *array = (Array*)v;

    int sum = 0;
    for (int i = 0; i< array->arrSize; ++i){
        sum += array->arr[i];
        Sleep(12);
    }
    array->average =  sum/array->arrSize;
    printf("Average value: %d\n", array->average);
    return 0;
}

int main() {
    int arrSize;

    printf("Input array size:");
    scanf("%d",&arrSize);
    Array *array = new Array(arrSize);

    HANDLE Thread1;
    DWORD IDThread1;

    Thread1 = CreateThread(NULL, 0, minMax,array, 0, &IDThread1);
    WaitForSingleObject(Thread1, INFINITE);

    HANDLE Thread2;
    DWORD IDThread2;
    CloseHandle(Thread1);
    Thread2 = CreateThread(NULL, 0, average, array, 0, &IDThread2);
    WaitForSingleObject(Thread2, INFINITE);

    CloseHandle(Thread2);

    array->arr[array->minInd] = array->average;
    array->arr[array->maxInd] = array->average;

    printf("Modified array: ");
    array->print();
    system("pause");
    return 0;
}


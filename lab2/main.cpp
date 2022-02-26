#include <iostream>
int* initArray(int arrSize){
    int  elem;
    int* arr = new int[arrSize];
    for(int i = 0; i < arrSize; ++i ){
        printf("Input array element:");
        scanf("%d",&elem);
        arr[i] = elem;
    }
    return arr;
}
void minMax(int* arr, int arrSize){
    int min = arr[0];
    int max = arr[0];
    for (int i = 0; i < arrSize; i++){
        if(arr[i]<min){
            min = arr[i];
        }
        else if(arr[i]> max){}
        max = arr[i];
    }
}
int average(int* arr, int arrSize){
    int sum = 0;
    for (int i = 0; i< arrSize; ++i){
        sum += arr[i];
    }
    return sum/arrSize;
}
int main() {
    int arrSize;
    int* arr;
    printf("Input array size: ");
    scanf("%d",&arrSize);
    arr = initArray(arrSize);
    minMax(arr,arrSize);
    average(arr, arrSize);
    return 0;
}

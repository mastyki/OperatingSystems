#include <iostream>
#include <windows.h>
struct employee
{
    int num;
    char name[10];
    double hours;
};
void recordEmployee(FILE* file){
    employee newEmployee = {};
    printf("Input new employee data\n");
    printf("Number:");
    scanf("%d", &newEmployee.num);
    printf("Name:");
    scanf("%s",newEmployee.name);
    printf("Hours:");
    scanf("%lf",&newEmployee.hours);

    fwrite(&newEmployee,sizeof(employee),1,file);
}

int main(int argc, char* args[]) {


    int numOfRecords = 0;
    char* fName;
    if(argc != 3) {
        std::cout << "Incorrect number of arguments!"<< std::endl <<":(";
        return -1;
    }
    fName = args[1];
    numOfRecords = atoi(args[2]);

    FILE* outFile;
    outFile = fopen(fName, "wb");
    if(outFile){
        for(int i = 0; i < numOfRecords; i++){
            recordEmployee(outFile);
        }
        fclose(outFile);
    }
    return 0;
}
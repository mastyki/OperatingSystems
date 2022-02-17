#include <iostream>
#include <windows.h>
struct employee
{
    int num;
    char name[10];
    double hours;
};
void recordEmployee(FILE* file){
    employee newEmployee;
    printf("Input next record for the employee");
    printf("\nNumber: ");
    scanf("%d",&newEmployee.num);
    printf("\nName: ");
    scanf("%s",&newEmployee.name);
    printf("\nHours: ");
    scanf("%f",&newEmployee.hours);
    printf("\n");
    fwrite(&newEmployee,sizeof(employee), 1, file);
}

int main(int argc, char* args[]) {


    int numOfRecords = 0;
    char* fName;
    if(argc != 3) {
        std::cout << "Incorrect number of arguments!"<< std::endl <<":(";
        return -1;
    }
    std::cout << argc << std::endl;
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
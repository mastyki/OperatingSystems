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
    try{
        int numOfRecords = 0;
        char* fName;
        if(argc != 3) {
            throw "Incorrect number of arguments!\n";
        }
        fName = args[1];
        numOfRecords = atoi(args[2]);

        FILE* outFile;
        outFile = fopen(fName, "wb");
        if(!outFile){
            throw "No such file\n";
        }
        for(int i = 0; i < numOfRecords; i++){
            recordEmployee(outFile);
        }
        fclose(outFile);
    }
    catch(const char* exception){
        std::cerr << "Error: " << exception << std:: endl;
    }

    return 0;
}
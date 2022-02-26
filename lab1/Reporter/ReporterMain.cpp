#include <iostream>
#include <clocale>
#include <windows.h>
struct employee
{
    int num;
    char name[10];
    double hours;
};
void addEployeeToOutputFile(FILE* outputFile, employee employeeRecord, int salary){
    fprintf(outputFile, "\n%-20d|%-15s|%-10.2lf|%-15.2lf",
            employeeRecord.num,employeeRecord.name,employeeRecord.hours,employeeRecord.hours*(double)salary);
}
void addHeaderToOutputFile(FILE* outputFile, char* finName){
    fprintf(outputFile,"Report on file \"%s\"\n",finName);
    fprintf(outputFile, "%-20s|%-15s|%-10s|%-15s","Employee number","Name","Hours","Salary");
}

int main(int argc, char* args[]) {
    try{
        int salary = 0;
        char* finName;
        char* foutName;

        if(argc != 4) {
            throw "Incorrect number of arguments!\n";
        }
        finName = args[1];
        foutName = args[2];
        salary = atoi(args[3]);

        FILE* outFile, *inFile;
        outFile = fopen(foutName, "w");
        inFile = fopen(finName,"rb");
        if(!outFile || !inFile){
           throw "No such file\n";
        }
        addHeaderToOutputFile(outFile,finName);
        employee newEmployee;
        while (!feof(inFile)){
            fread(&newEmployee, sizeof(employee), 1, inFile);
            if (!feof(inFile)) {
                addEployeeToOutputFile(outFile,newEmployee,salary);
            }
        }

        fclose(outFile);
        fclose(inFile);
    }
    catch(const char* exception){
        std::cerr << "Error: " << exception << std:: endl;
    }

    return 0;
}
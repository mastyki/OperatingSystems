#include <iostream>
#include <string>
#include <windows.h>
DWORD WaitForSingleObject(
        HANDLE hHandle, // дескриптор объекта
        DWORD dwMilliseconds // интервал ожидания в миллисекундах
);
BOOL CreateProcess
        (
                LPCTSTR lpApplicationName,                 // имя исполняемого модуля
                LPTSTR lpCommandLine,                      // Командная строка
                LPSECURITY_ATTRIBUTES lpProcessAttributes, // Указатель на структуру SECURITY_ATTRIBUTES
                LPSECURITY_ATTRIBUTES lpThreadAttributes,  // Указатель на структуру SECURITY_ATTRIBUTES
                BOOL bInheritHandles,                      // Флаг наследования текущего процесса
                DWORD dwCreationFlags,                     // Флаги способов создания процесса
                LPVOID lpEnvironment,                      // Указатель на блок среды
                LPCTSTR lpCurrentDirectory,                // Текущий диск или каталог
                LPSTARTUPINFO lpStartupInfo,               // Указатель нас структуру STARTUPINFO
                LPPROCESS_INFORMATION lpProcessInformation // Указатель нас структуру PROCESS_INFORMATION
        );
int main(int argc, char* args[]) {

    try {
        if(argc != 3) {
           throw "Incorrect number of arguments!";
        }
        STARTUPINFO si;
        PROCESS_INFORMATION piApp;

        ZeroMemory(&si,sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);

        int size = strlen("code ") + strlen(args[1]) + strlen(args[2]) + 2;
        char* commandLineArgument = new char[size];
        commandLineArgument[0] = 0;
        strcat(commandLineArgument,"code ");
        strcat(commandLineArgument,args[1]);
        strcat(commandLineArgument," ");
        strcat(commandLineArgument,args[2]);

        CreateProcessA("Creator.exe",commandLineArgument,NULL,NULL,
                       FALSE,NULL,NULL,NULL,&si,&piApp);
        WaitForSingleObject(piApp.hThread,INFINITE);

        CloseHandle(piApp.hThread);
        CloseHandle(piApp.hProcess);

        char reportName[256];
        char salary[32];
        printf("Input name of report file and salary\n");
        printf("Report file name:");
        scanf("%s",reportName);
        printf("Salary:");
        scanf("%s",salary);
        size = strlen("code ") + strlen(reportName) + strlen(salary) + 2;
        commandLineArgument = new char[size];
        commandLineArgument[0] = 0;
        strcat(commandLineArgument,"code");
        strcat(commandLineArgument,reportName);
        strcat(commandLineArgument," ");
        strcat(commandLineArgument,salary);
        ZeroMemory(&si,sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);
        CreateProcessA("ReporterMain.exe",commandLineArgument,NULL,NULL,
                       FALSE,NULL,NULL,NULL,&si,&piApp);
        WaitForSingleObject(piApp.hThread,INFINITE);

        CloseHandle(piApp.hThread);
        CloseHandle(piApp.hProcess);
    }
    catch(const char* exception){
        std::cerr << "Error: " << exception << std:: endl;
    }

    return 0;
}

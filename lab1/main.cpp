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

    if(argc != 3) {
        printf("Incorrect number of arguments!");
    } else {

        STARTUPINFO si;
        PROCESS_INFORMATION piApp;

        ZeroMemory(&si,sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);

        std::string numberCount = args[2];
        std::string binaryFileName = args[1];
        binaryFileName = binaryFileName;
        std::string commandLineArguments = "code" + binaryFileName +" "+ numberCount;
        char* argument = const_cast<char *>(commandLineArguments.c_str());

        CreateProcessA("Creator.exe",argument,NULL,NULL,
                       FALSE,NULL,NULL,NULL,&si,&piApp);
        WaitForSingleObject(piApp.hThread,INFINITE);
        CloseHandle(piApp.hThread);
        CloseHandle(piApp.hProcess);
    }

    return 0;
}

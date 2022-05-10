#include<iostream>
#include<fstream>
#include<string>
#include<Windows.h>
#include<vector>

using namespace std;

HANDLE start_process(wstring command_line) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    CloseHandle(pi.hThread);
    return pi.hProcess;
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

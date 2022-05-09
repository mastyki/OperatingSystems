#include <iostream>
#include <Windows.h>
#include "header.h"

using namespace std;

DWORD WINAPI marker(LPVOID lpParam)
{
    params* p = (params*)lpParam;
    int num = 0;
    srand(p->i);
    HANDLE hEvents[2] = { p->hStartEvent,p->hEndEvent };
    while (WaitForMultipleObjects(2, hEvents, FALSE, INFINITE) != WAIT_OBJECT_0 + 1)
    {
        while (true) {
            int r = rand();
            int mod = r % p->n;
            EnterCriticalSection(&cs);
            if (ArrayOfThreads[mod] == 0) {
                Sleep(5);
                ArrayOfThreads[mod] = p->i;
                LeaveCriticalSection(&cs);
                num++;
                Sleep(5);
            }
            else {
                cout << "Thread:" << p->i - 1 << " " << num << " " << mod << endl;
                LeaveCriticalSection(&cs);
                SetEvent(p->hCantEvent);
                break;
            }
        }
    }
    for (int i = 0; i < p->n; i++)
        if (ArrayOfThreads[i] == p->i)
            ArrayOfThreads[i] = 0;
    return 0;
}


int main()
{

}
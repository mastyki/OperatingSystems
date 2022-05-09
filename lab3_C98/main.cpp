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
    int arraySize;
    cout << "Input size of array: " << endl;
    cin >> arraySize;
    ArrayOfThreads = new int[arraySize];
    for (int i = 0; i < arraySize; ++i) {
        ArrayOfThreads = 0;
    }
    InitializeCriticalSection(&cs);
    cout << "Input number of threads: " << endl;
    int numOfThreads;
    cin >> numOfThreads;

    HANDLE* hThreads = new HANDLE[numOfThreads];
    params* p = new params[numOfThreads];
    for (int i = 0; i < numOfThreads; i++)
    {
        p[i].n = arraySize;
        p[i].i = i + 1;
        p[i].hStartEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
        if (p[i].hStartEvent == NULL)
        {
            cerr << "Failed to create start event!\n";
            return 1;
        };
        p[i].hEndEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
        if (p[i].hEndEvent == NULL)
        {
            cerr << "Failed to create end event!\n";
            return 1;
        }
        p[i].hCantEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
        if (p[i].hCantEvent == NULL)
        {
            cerr << "Failed to create cant event!\n";
            return 1;
        }
        hThreads[i] = CreateThread(NULL, 0, marker, &p[i], 0, NULL);
        if (hThreads[i] == NULL)
        {
            cerr << "Failed to create a thread!\n";
            return 2;
        }
    }
    for (int i = 0; i < numOfThreads; i++) {
        SetEvent(p[i].hStartEvent);
    }
    bool* a = new bool[numOfThreads];
    memset(a, false, sizeof(bool) * numOfThreads);
    while (true) {
        for (int i = 0; i < numOfThreads; i++) {
            if (a[i] == false)
                WaitForSingleObject(p[i].hCantEvent, INFINITE);
        }
        cout << "Array after marks:" << endl;
        for (int i = 0; i < arraySize; i++) {
            cout << ArrayOfThreads[i] << " ";
        }
        cout << endl << "Input number of thread you want to cancel: ";
        int threadToCancel;
        cin >> threadToCancel;
        a[threadToCancel] = 1;
        SetEvent(p[threadToCancel].hEndEvent);
        WaitForSingleObject(hThreads[threadToCancel], INFINITE);
        cout << "Array after cancelling: " << endl;
        for (int i = 0; i < arraySize; i++) {
            cout << ArrayOfThreads[i] << " ";
        }
        cout << endl;
        bool allThreadEnd = 1;
        for (int i = 0; i < numOfThreads; i++) {
            if (a[i] == 0) {
                SetEvent(p[i].hStartEvent);
                allThreadEnd = 0;
            }
        }
        if (allThreadEnd == 1) {
            cout << "All the threads are canceled";
            break;
        }
    }

    for (int i = 0; i < numOfThreads; i++)
    {
        CloseHandle(hThreads[i]);
        CloseHandle(p[i].hStartEvent);
        CloseHandle(p[i].hEndEvent);
        CloseHandle(p[i].hCantEvent);
    }
    delete[] ArrayOfThreads;
    delete[] p;
    delete[] hThreads;
    delete[] a;
    DeleteCriticalSection(&cs);
    return 0;
}
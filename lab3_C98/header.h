#include <iostream>
#include <Windows.h>
struct params
{
    int i;
    int n;
    HANDLE hEndEvent;
    HANDLE hStartEvent;
    HANDLE hCantEvent;
};

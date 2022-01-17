﻿#include <iostream>
#include <Windows.h>

DWORD pid = NULL;
DWORD WINAPI OS04_04_T1() {
    DWORD tid = GetCurrentThreadId();
    for (int i = 0; i < 50; i++)
    {
        Sleep(1000);
        std::cout << "PID = " << pid << ", Child Thread 1: tid- " << tid << " : " << i << '\n';
    }
    return 0;
}
DWORD WINAPI OS04_04_T2() {
    DWORD tid = GetCurrentThreadId();
    for (int i = 0; i < 125; i++)
    {
        Sleep(1000);
        std::cout << "PID = " << pid << ", Child Thread 2: tid- " << tid << " : " << i << '\n';
    }
    return 0;
}


int main()
{
    pid = GetCurrentThreadId();
    DWORD OS04_04_T1Id = NULL;
    DWORD OS04_04_T2Id = NULL;
    HANDLE hChild = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OS04_04_T1, NULL, 0, &OS04_04_T1Id);
    HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OS04_04_T2, NULL, 0, &OS04_04_T2Id);
    for (int i = 0; i < 100; i++)
    {
        Sleep(1000);
        std::cout << "PID = " << pid << ", Parent Thread: tid- " << pid << " : " << i << '\n';
        if (i == 30)
        {
            std::cout << "Sleep Parent\n";
            Sleep(10000);
            std::cout << "Wakeup Parent\n";
        }
    }
    WaitForSingleObject(hChild, INFINITE);
    CloseHandle(hChild);
    WaitForSingleObject(hChild2, INFINITE);
    CloseHandle(hChild2);
    system("pause");
    return 0;
}


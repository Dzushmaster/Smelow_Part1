#include <iostream>
#include <Windows.h>

DWORD pid = NULL;
DWORD WINAPI OS04_05_T1() {
    DWORD tid = GetCurrentThreadId();
    for (int i = 0; i < 50; i++)
    {
        Sleep(1000);
        std::cout << "PID = " << pid << ", Child Thread 1: tid- " << tid << " : " << i << '\n';
    }
    return 0;
}
DWORD WINAPI OS04_05_T2() {
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
    DWORD OS04_05_T1Id = NULL;
    DWORD OS04_05_T2Id = NULL;
    HANDLE hChild = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OS04_05_T1, NULL, 0, &OS04_05_T1Id);
    HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OS04_05_T2, NULL, 0, &OS04_05_T2Id);
    for (int i = 0; i < 100; i++)
    {
        Sleep(1000);
        std::cout << "PID = " << pid << ", Parent Thread: tid- " << pid << " : " << i << '\n';
        if (i == 40)
        {
            std::cout << "I has created you and i will kill you, Child1\n";
            TerminateThread(hChild, -1);
        }
    }
    WaitForSingleObject(hChild2, INFINITE);
    CloseHandle(hChild2);
    system("pause");
    return 0;
}


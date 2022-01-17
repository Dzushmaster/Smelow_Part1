// OS_05.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <Windows.h>
#include <iostream>
#include <bitset>
#include <intrin.h>
#include <string>
void printPriorProcess(HANDLE hp);
void printPriorThread(HANDLE ht);
int getQuantityProcessors(ULONG_PTR procMask);
int main()
{
    HANDLE hp = GetCurrentProcess();
    HANDLE ht = GetCurrentThread();
    ULONG_PTR procMask;
    ULONG_PTR sysMask;
    SYSTEM_INFO sys_info;
    DWORD icpu = -1;
    char buf[10];
    std::cout << "=========================== OS_05 ===========================\n";
    std::cout << "---- Current PID = " << GetCurrentProcessId() << "\n";
    printPriorProcess(hp);
    std::cout << "---- Current TID = " << GetCurrentThreadId() << "\n";
    printPriorThread(ht);
    
    bool success = GetProcessAffinityMask(hp, &procMask, &sysMask);
    if (success)
    {
        _itoa_s(procMask, buf, 2);
        std::cout << "process mask: " << buf;
        _itoa_s(sysMask, buf, 2);
        std::cout << "\nsystem mask: " << buf;
        icpu = SetThreadIdealProcessor(ht, MAXIMUM_PROCESSORS);
        std::cout << "\nThread Ideal Processor: " << icpu;
        GetSystemInfo(&sys_info);
        std::cout << "\nMax count processors: " << sys_info.dwNumberOfProcessors;
        std::cout << "\nquantity of processors " << getQuantityProcessors(procMask) << '\n';
        
    }

    system("pause");
}

void printPriorProcess(HANDLE h) {
    DWORD prty = GetPriorityClass(h);
    switch (prty) {
    case IDLE_PRIORITY_CLASS: std::cout << " ----+  IDLE_PRIORITY_CLASS\n"; break;
    case BELOW_NORMAL_PRIORITY_CLASS: std::cout << " ----+  BELOW_NORMAL_PRIORITY_CLASS\n"; break;
    case NORMAL_PRIORITY_CLASS: std::cout << " ----+  NORMAL_PRIORITY_CLASS\n"; break;
    case ABOVE_NORMAL_PRIORITY_CLASS: std::cout << " ----+  ABOVE_NORMAL_PRIORITY_CLASS\n"; break;
    case HIGH_PRIORITY_CLASS: std::cout << " ----+  HIGH_PRIORITY_CLASS\n"; break;
    case REALTIME_PRIORITY_CLASS: std::cout << " ----+  REALTIME_PRIORITY_CLASS\n"; break;
    default: std::cout << " ----+  ?\n";
    }
    return;
}
void printPriorThread(HANDLE ht) {
    DWORD prty = GetThreadPriority(ht);
    switch (prty) {
    case THREAD_PRIORITY_LOWEST: std::cout << " ----+  THREAD_PRIORITY_LOWEST\n"; break;
    case THREAD_PRIORITY_BELOW_NORMAL: std::cout << " ----+  THREAD_PRIORITY_BELOW_NORMAL\n"; break;
    case THREAD_PRIORITY_NORMAL: std::cout << " ----+  THREAD_PRIORITY_NORMAL\n"; break;
    case THREAD_PRIORITY_ABOVE_NORMAL: std::cout << " ----+  THREAD_PRIORITY_ABOVE_NORMALE\n"; break;
    case THREAD_PRIORITY_HIGHEST: std::cout << " ----+  THREAD_PRIORITY_HIGHEST\n"; break;
    case THREAD_PRIORITY_IDLE: std::cout << " ----+  THREAD_PRIORITY_TIME_IDLE\n"; break;
    case THREAD_PRIORITY_TIME_CRITICAL: std::cout << " ----+  THREAD_PRIORITY_TIME_CRITICAL\n"; break;
    default: std::cout << " ----+  ?\n";
    }
    return;
}

int getQuantityProcessors(ULONG_PTR procMask) {
    int counter = 0;
    while (procMask != 0) {
        if (procMask & 0x1)
            counter++;
        procMask = procMask >> 1;
    }
    return counter;
}
//колич процесс достп проце
//процессор назн потоку
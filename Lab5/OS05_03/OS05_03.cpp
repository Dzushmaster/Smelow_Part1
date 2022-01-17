#include <iostream>
#include <cstdlib>
#include "Windows.h"
#include <bitset>

DWORD pid = GetCurrentProcessId();
char const* getPriorityThreadToString(int);

DWORD WINAPI TA() {
	HANDLE thread = GetCurrentThread();
	DWORD tid = GetCurrentThreadId();

	for (int i = 0; i < 1000; i++)
	{
		std::cout << "\nIterations: " << i;
		if (i % 10 == 0) {
			Sleep(200);
			std::cout << "Thread Ideal Processor " << SetThreadIdealProcessor(thread, MAXIMUM_PROCESSORS) << '\n';
			std::cout << "\ttid: " << tid << '\t' << getPriorityThreadToString(GetThreadPriority(thread)) << '\n';
		}
	}
	return 0;
}

int main(int argc, char* argv[]) {
	DWORD mask;
	DWORD priority_process;
	int priority_thread1;
	int priority_thread2;
	char* end;
	try {
		if (argc > 4) {
			mask = strtol(argv[1], &end, 10);
			priority_process = strtol(argv[2], &end, 10);
			priority_thread1 = strtol(argv[3], &end, 10);
			priority_thread2 = strtol(argv[4], &end, 10);
		}
		else {
			throw "Dont exist enough parameters";
		}
	}
	catch (const char* err) {
		std::cout << err << '\n';
		return -1;
	}
	HANDLE handler = GetCurrentProcess();
	SetPriorityClass(handler, priority_process);
	bool success = SetProcessAffinityMask(handler, mask);
	if (success) {
		ULONG_PTR processAffinityMask;
		ULONG_PTR systemAffinityMask;
		success = GetProcessAffinityMask(handler, &processAffinityMask, &systemAffinityMask);
		if (success)
			std::cout << "process mask" << std::bitset<8>(processAffinityMask) << '\n';
	}
	HANDLE hChild_1 = CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(&TA), nullptr, 0, nullptr);

	HANDLE hChild_2 = CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(&TA), nullptr, 0, nullptr);

	SetThreadPriority(hChild_1, priority_thread1);
	SetThreadPriority(hChild_2, priority_thread2);

	ResumeThread(hChild_1);
	ResumeThread(hChild_2);

	WaitForSingleObject(hChild_1, INFINITE);
	WaitForSingleObject(hChild_2, INFINITE);
	CloseHandle(hChild_1);
	CloseHandle(hChild_2);
	system("pause");
	return 0;
}
char const* getPriorityThreadToString(int priority)
{
	switch (priority) {
	case THREAD_PRIORITY_IDLE:          return "THREAD_PRIORITY_IDLE";
	case THREAD_PRIORITY_LOWEST:        return "THREAD_PRIORITY_LOWEST";
	case THREAD_PRIORITY_BELOW_NORMAL:  return "THREAD_PRIORITY_BELOW_NORMAL";
	case THREAD_PRIORITY_NORMAL:        return "THREAD_PRIORITY_NORMAL";
	case THREAD_PRIORITY_ABOVE_NORMAL:  return "THREAD_PRIORITY_ABOVE_NORMAL";
	case THREAD_PRIORITY_HIGHEST:       return "THREAD_PRIORITY_HIGHEST";
	case THREAD_PRIORITY_TIME_CRITICAL: return "THREAD_PRIORITY_TIME_CRITICAL";
	default:                            return "Try set priority again";
	}

}
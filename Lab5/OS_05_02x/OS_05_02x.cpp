#include <iostream>
#include "Windows.h"

std::string getProcessPriority(HANDLE hp);
void getThreadPriority(HANDLE ht);
void getAffinityMask(HANDLE hp, HANDLE ht);

int main()
{
	HANDLE hp = GetCurrentProcess();
	HANDLE ht = GetCurrentThread();
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();

	for (int i = 0; i < 1000; i++) {
		std::cout << "Iteration: " << i << '\n';
		if (i % 10 == 0)
		{
			//std::cout << "Iteration: " << i << '\n';
				std::cout<< "PID: " << pid << '\n' << "TID: " << tid << '\n'
				<< getProcessPriority(hp);
				getThreadPriority(ht);
				getAffinityMask(hp, ht);
				Sleep(200);
		}

	}
	system("pause");
}
std::string getProcessPriority(HANDLE hp)
{
	std::string prStr = "Process priority class: ";
	DWORD pr = GetPriorityClass(hp);
	switch (pr) {
	case IDLE_PRIORITY_CLASS: prStr += " IDLE_PRIORITY_CLASS\n"; break;
	case BELOW_NORMAL_PRIORITY_CLASS: prStr += "  BELOW_NORMAL_PRIORITY_CLASS\n"; break;
	case NORMAL_PRIORITY_CLASS: prStr += " NORMAL_PRIORITY_CLASS\n"; break;
	case ABOVE_NORMAL_PRIORITY_CLASS: prStr += " ABOVE_NORMAL_PRIORITY_CLASS\n"; break;
	case HIGH_PRIORITY_CLASS: prStr += " HIGH_PRIORITY_CLASS\n"; break;
	case REALTIME_PRIORITY_CLASS: prStr += " REALTIME_PRIORITY_CLASS\n"; break;
	default: prStr += "  ?\n";
	}
	return prStr;
}
void getThreadPriority(HANDLE ht)
{
	DWORD prty = GetThreadPriority(ht);
	std::cout << "Thread priority: ";
	switch (prty) {
	case THREAD_PRIORITY_LOWEST: std::cout << " THREAD_PRIORITY_LOWEST\n"; break;
	case THREAD_PRIORITY_BELOW_NORMAL: std::cout << " THREAD_PRIORITY_BELOW_NORMAL\n"; break;
	case THREAD_PRIORITY_NORMAL: std::cout << " THREAD_PRIORITY_NORMAL\n"; break;
	case THREAD_PRIORITY_ABOVE_NORMAL: std::cout << " THREAD_PRIORITY_ABOVE_NORMALE\n"; break;
	case THREAD_PRIORITY_HIGHEST: std::cout << " THREAD_PRIORITY_HIGHEST\n"; break;
	case THREAD_PRIORITY_IDLE: std::cout << " THREAD_PRIORITY_TIME_IDLE\n"; break;
	case THREAD_PRIORITY_TIME_CRITICAL: std::cout << " THREAD_PRIORITY_TIME_CRITICAL\n"; break;
	default: std::cout << " ?\n";
	}
}
void getAffinityMask(HANDLE hp, HANDLE ht)
{
	std::cout << "Thread Ideal Processor " << SetThreadIdealProcessor(ht, MAXIMUM_PROCESSORS) << '\n';
}
#include <Windows.h>
#include <iostream>
#include <ctime>
#include <TlHelp32.h>
#include <stdio.h>

DWORD ChildThread();
DWORD GetParentPid();
int simple(int n);
bool stop = false;

int main() {
	clock_t start = clock();
	std::cout << "Parent Pid: " << GetParentPid() << '\n';
	HANDLE htimer = OpenWaitableTimer(TIMER_ALL_ACCESS, FALSE, L"OS08_04");
	DWORD ChildId2 = NULL;
	HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread, NULL, 0, &ChildId2);
	WaitForSingleObject(htimer, INFINITE);
	stop = true;
	CloseHandle(hChild2);
	std::cout << "time: " << clock() - start << '\n';
	system("pause");
	return 0;
}
DWORD GetParentPid() {
	HANDLE hSnapshot;
	PROCESSENTRY32 pe32;
	DWORD ppid = 0, pid = GetCurrentProcessId();
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	__try {
		if (hSnapshot == INVALID_HANDLE_VALUE) __leave;
		ZeroMemory(&pe32, sizeof(pe32));
		pe32.dwSize = sizeof(pe32);
		if (!Process32First(hSnapshot, &pe32)) __leave;
		do {
			if (pe32.th32ProcessID == pid) {
				ppid = pe32.th32ParentProcessID;
				break;
			}
		} while (Process32Next(hSnapshot, &pe32));
	}
	__finally {
		if (hSnapshot != INVALID_HANDLE_VALUE) CloseHandle(hSnapshot);
	}
	return ppid;
}
DWORD ChildThread() {
	DWORD tid = GetCurrentThreadId();
	for (long long i = 2; ; i++) {
		if (stop) break;
		if (simple(i)) std::cout << i <<'\n';
	}
	return 0;
}
int simple(int n) {
	for (int i = 2; i <= n / 2; i++)
		if ((n % i) == 0)
			return 0;
	return 1;
}
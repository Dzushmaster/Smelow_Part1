#include <iostream>
#include <Windows.h>
//Поочередно с 30 до 60
DWORD pid = NULL;
DWORD WINAPI ChildThread1();
DWORD WINAPI ChildThread2();
CRITICAL_SECTION cs;

int main() {
	pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	DWORD ChildId1 = NULL;
	DWORD ChildId2 = NULL;
	HANDLE hChild1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread1, NULL, 0, &ChildId1);
	HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread2, NULL, 0, &ChildId2);
	
	InitializeCriticalSection(&cs);
	for (int i = 0; i < 90; i++) {
		if (i == 30) {
			EnterCriticalSection(&cs);
			std::cout << "--------------------------------------------------------\n";
		}
		if(i == 60)
			LeaveCriticalSection(&cs);
		std::cout << "Main PID = " << pid << ", Parent Thread: " << "tid - " << tid << ": " << i << '\n';
		Sleep(100);
	}

	WaitForSingleObject(hChild1, INFINITE);
	WaitForSingleObject(hChild2, INFINITE);
	DeleteCriticalSection(&cs);
	CloseHandle(hChild1);
	CloseHandle(hChild2);
}

DWORD WINAPI ChildThread1() {
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 90; i++) {
		if (i == 30) {
			EnterCriticalSection(&cs);
			std::cout << "--------------------------------------------------------\n";
		}

		if (i == 60)
			LeaveCriticalSection(&cs);
		std::cout << "First PID = " << pid << ", Child Thread: tid- " << tid << ": " << i << '\n';
		Sleep(100);
	}
	LeaveCriticalSection(&cs);
	return 0;
}

DWORD WINAPI ChildThread2() {
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 90; i++) {
		if (i == 30) {
			EnterCriticalSection(&cs);
			std::cout << "--------------------------------------------------------\n";
		}
		if (i == 60)
			LeaveCriticalSection(&cs);
		std::cout << "Second PID = " << pid << ", Child Thread: tid- " << tid << ": " << i << '\n';
		Sleep(100);
	}
	LeaveCriticalSection(&cs);
	return 0;
}
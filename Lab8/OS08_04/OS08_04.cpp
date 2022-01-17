#include <Windows.h>
#include <iostream>
#include <ctime>
#define SECOND 10000000
int main() {
	clock_t start = clock();
	DWORD pid = GetCurrentProcessId();
	std::cout << "Main PID: " << pid << '\n';
	long long it = -60 * SECOND;
	HANDLE htimer = CreateWaitableTimer(NULL, FALSE, L"OS08_04");
	if (!SetWaitableTimer(htimer, (LARGE_INTEGER*)&it, 60000, NULL, NULL, FALSE))
		throw "Error SrtWaitableTimer";
	LPCWSTR an = L"D:/University/ОС/Lab8/OS08_01/Debug/OS08_04x.exe";
	PROCESS_INFORMATION pi1, pi2;
	pi1.dwThreadId = 1; pi2.dwThreadId = 2;
	{
		STARTUPINFO si; ZeroMemory(&si, sizeof(STARTUPINFO)); si.cb = sizeof(STARTUPINFO);
		CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1) ?
			std::cout << "Process OS08_04x_A created\n" : std::cout << "Process OS08_04x_A not created\n";
	}
	{
		STARTUPINFO si; ZeroMemory(&si, sizeof(STARTUPINFO)); si.cb = sizeof(STARTUPINFO);
		CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2) ?
			std::cout << "Process OS08_04x_B created\n" : std::cout << "Process OS08_04x_B not created\n";
	}
	WaitForSingleObject(pi1.hProcess, INFINITE); WaitForSingleObject(pi2.hProcess, INFINITE);
	CancelWaitableTimer(htimer);
	std::cout << "time: " << clock() - start << '\n';
	system("pause");
	return 0;
}
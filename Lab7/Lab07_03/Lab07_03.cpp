#include <iostream>
#include <Windows.h>
int main() {
	LPCWSTR an = L"D:/University/ОС/Lab7/Lab07_02/Debug/Lab07_03A.exe";
	LPCWSTR an2 = L"D:/University/ОС/Lab7/Lab07_02/Debug/Lab07_03B.exe";
	DWORD pid = GetCurrentProcessId();
	STARTUPINFO si1;
	STARTUPINFO si2;
	PROCESS_INFORMATION pi1;
	PROCESS_INFORMATION pi2;
	ZeroMemory(&si1, sizeof(STARTUPINFO)); si1.cb = sizeof(STARTUPINFO);
	ZeroMemory(&si2, sizeof(STARTUPINFO)); si2.cb = sizeof(STARTUPINFO);
	HANDLE hm = CreateMutex(NULL, FALSE, L"Mutex");
	
	if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &pi1))
		std::cout << "--Process OS07_03A created--\n";
	else
		std::cout << "--Process OS07_03A not created--\n";

	if (CreateProcess(an2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2))
		std::cout << "--Process OS07_03B created--\n";
	else
		std::cout << "--Process OS07_03B not created--\n";
	int start = clock();
	for (int i = 0; i < 90; i++) {
		if (i == 30)
			WaitForSingleObject(hm, INFINITE);
		if (i == 60)
			ReleaseMutex(hm);
		std::cout << i << " OS07_03 MAIN pid = " << pid << ", time: " << clock() - start << '\n';
		Sleep(100);
	}
	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);
	CloseHandle(hm);
	CloseHandle(pi1.hProcess); CloseHandle(pi2.hProcess);
	system("pause");
	return 0;
}
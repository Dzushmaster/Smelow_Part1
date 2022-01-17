#include <iostream>
#include <Windows.h>
#include <ctime>
int main() {
	int start = clock();
	DWORD pid = GetCurrentProcessId();
	HANDLE hs = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"Semaphore");
	hs == NULL ? std::cout << "OS07_04A: Open Error Semaphore\n" : std::cout << "OS07_04A: Open Semaphore\n";
	LONG prevcount = 0;
	for (int i = 0; i < 90; i++) {
		if (i == 30)
			WaitForSingleObject(hs, INFINITE);
		if (i == 60)
			ReleaseSemaphore(hs, 1, &prevcount);
		std::cout << i << " OS07_04A CHILD_1 pid = " << pid << ", time: " << clock() - start << '\n';
		Sleep(100);
	}
	CloseHandle(hs);
	system("pause");
	return 0;
}
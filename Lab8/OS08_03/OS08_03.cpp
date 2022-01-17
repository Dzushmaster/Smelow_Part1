#include <Windows.h>
#include <iostream>
#include <ctime>
int count = 0;
#define SECOND 1000000
PTIMERAPCROUTINE CALLBACK callback(LPVOID lpArgToCompletionRoutine, DWORD dwTimerLowValue, DWORD dwTimerHighValue)
{
	count = ++count;
	return NULL;
}
int main() {
	HANDLE htimer = CreateWaitableTimer(NULL, FALSE, NULL);
	long long it = SECOND * -0;
	LPVOID lpArgToCompletionRoutine = NULL;
	DWORD dwTimerLowValue = NULL, dwTimerHighValue = NULL;
	clock_t start = clock();
	for (int i = 0;; i++) {
		if (!SetWaitableTimer(htimer, (LARGE_INTEGER*)&it, 3000, callback(lpArgToCompletionRoutine, dwTimerLowValue, dwTimerHighValue), NULL, FALSE)) {
			throw "Error SetWaitableTimer";
		}
		if ((clock() - start) == 3000 || (clock() - start) == 6000 || (clock() - start) == 9000 || (clock() - start) == 12000) {
			std::cout << "- " << count << ", s - " << clock() - start << '\n';
		}
		if ((clock() - start) / CLOCKS_PER_SEC == 15) {
			std::cout << "- " << count << ", s - " << clock() - start << '\n';
			break;
		}
		WaitForSingleObject(htimer, INFINITE);
	}
	CloseHandle(htimer);
	system("pause");
	return 0;
}
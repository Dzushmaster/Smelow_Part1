#include <iostream>
#include "Windows.h"
int main() {
	for (int i = 0; i < 1000000; i++)
	{
		std::cout << i << ' ' << GetCurrentProcessId() << ' ' << GetCurrentThreadId() << '\n';
		Sleep(1000);
	}
	return 0;
}
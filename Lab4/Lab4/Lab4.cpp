#include <iostream>
#include <Windows.h>

int main() 
{
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	for (unsigned long long i = 0; i < MAXULONGLONG; i++)
	{
		Sleep(1000);
		std::cout << "PID = " << pid << ", TID = " << tid << " : " << i << '\n';
	}
	
}
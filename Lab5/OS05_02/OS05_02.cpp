#include <iostream>
#include <cstdlib>
#include "Windows.h"

int main(int argc, char* argv[])
{
	try {
		if (argc == 4) {
			char buf[10];
			int p1 = atoi(argv[1]);
			int p2 = atoi(argv[2]);
			int p3 = atoi(argv[3]);
			if (!SetProcessAffinityMask(GetCurrentProcess(), p1)) {
				throw "Error: SetProcessAfinityMask";
			}
			_itoa_s(p1, buf, 2);
			std::cout << "processAffinityMask: " << buf << '\n'
				<< "processPriorityClass1: " << p2 << '\n'
				<< "processPriorityClass2: " << p3 << '\n';
			LPCWSTR an1 = L"D:/University/ОС/Lab5/OS_05/Debug/OS_05_02x.exe";
			LPCWSTR an2 = L"D:/University/ОС/Lab5/OS_05/Debug/OS_05_02x.exe";
			STARTUPINFO si1, si2;
			PROCESS_INFORMATION pi1, pi2;
			ZeroMemory(&si1, sizeof(STARTUPINFO));
			si1.cb = sizeof(STARTUPINFO);
			
			ZeroMemory(&si2, sizeof(STARTUPINFO));
			si2.cb = sizeof(STARTUPINFO);
			if (CreateProcess(an1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | p2, NULL, NULL, &si1, &pi1))
				std::cout << "-- Process OS05_021 created\n";
			else
				std::cout << "-- Proccess OS05_021 not created\n";

			if (CreateProcess(an2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | p3, NULL, NULL, &si2, &pi2))
				std::cout << "-- Process OS05_022 created\n";
			else
				std::cout << "-- Proccess OS05_022 not created\n";

			WaitForSingleObject(pi1.hProcess, INFINITE);
			WaitForSingleObject(pi2.hProcess, INFINITE);
			CloseHandle(pi1.hProcess);
			CloseHandle(pi2.hProcess);
		}
	}
	catch (std::string err) {
		std::cout << err << '\n';
	}
}
#include <iostream>
#include <Windows.h>

int main() {
	DWORD pid = GetCurrentProcessId();
	for (int i = 0; i < 50; i++) {
		std::cout << i << " OS03_02_01 pid: " << pid << '\n';
		Sleep(1000);
	}
}
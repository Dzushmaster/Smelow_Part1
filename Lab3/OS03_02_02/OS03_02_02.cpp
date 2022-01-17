#include <iostream>
#include <Windows.h>

int main() {
	DWORD pid = GetCurrentProcessId();
	for (int i = 0; i < 125; i++) {
		std::cout << i << " OS03_02_02 pid: " << pid << '\n';
		Sleep(1000);
	}
}
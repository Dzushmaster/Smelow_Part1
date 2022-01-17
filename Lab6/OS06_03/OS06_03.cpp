#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <locale>

// K = ca
// а = e0
// м = ec
// Страница CA = 202, смещение E0E = 3598, Адрес = CAE0E, 00BD0000 + CAE0E = C9AE0E

#define KB (1024)
#define MB (KB * KB)
#define PG (4 * KB)

void saymem() {
	MEMORYSTATUS ms;
	GlobalMemoryStatus(&ms);
	std::cout << " -- Физическая память: " << ms.dwTotalPhys / MB << '\n';
	std::cout << " -- Доступно физ памяти: " << ms.dwAvailPhys / MB << '\n';
	std::cout << " -- Объем виртуальной памяти: " << ms.dwTotalVirtual / MB << '\n';
	std::cout << " -- Доступно виртуальной памяти: " << ms.dwAvailVirtual / MB << '\n';
}

int main() {
	setlocale(LOCALE_ALL, "rus");
	int pages = 256;
	int countItems = pages * PG / sizeof(int);
	saymem();
	LPVOID xmemaddr = VirtualAlloc(NULL, pages * PG, MEM_COMMIT, PAGE_READWRITE);
	std::cout << std::hex << xmemaddr << '\n';
	int* arr = (int*)xmemaddr;
	for (int i = 0; i < countItems; i++)
		arr[i] = i;
	std::cout << '\n';
	saymem();
	VirtualFree(xmemaddr, NULL, MEM_RELEASE) ? std::cout << "VirtualFree free\n " : std::cout << "Virtual false\n";
	saymem();
	system("pause");
}
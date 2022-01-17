#include <iostream>
#include <Windows.h>
/*
14. Разработайте консольное приложение OS06_04, которое включает функцию sh, принимающую 1 параметр: дескриптор (HANDLE) heap.
15. Функция sh выводит на консоль, общий размер heap, размеры распределенной  и нераспределенных  областей памяти heap.
16. Приложение OS06_04 размещает в стандартной heap процесса int-массив размерности 300000.
17. Выведите с помощью функции sh информацию до размещения массива и после.
18. Объясните результат.
*/
void sh(HANDLE pheap);
int main() {
	HANDLE pheap = GetProcessHeap();
	std::cout << "--Before--\n\n";
	sh(pheap);
	{
		int size = 300000;
		int* m = new int[size];
		std::cout << "-- m = " << std::hex << m << ", size = " << std::dec << size << '\n';
	}
	std::cout << "\n\n--After--\n\n";
	sh(pheap);
}
void sh(HANDLE pheap) {
	PROCESS_HEAP_ENTRY phe;
	phe.lpData = NULL;
	while (HeapWalk(pheap, &phe)) {
		std::cout << "-- address = " << std::hex << phe.lpData <<
			", size = " << std::dec << phe.cbData <<
			((phe.wFlags & PROCESS_HEAP_REGION) ? " R": "") <<
			((phe.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE) ? " U": "")<<
			((phe.wFlags & PROCESS_HEAP_ENTRY_BUSY) ? "B" : "") << '\n';
	}
	std::cout << "----\n";
}
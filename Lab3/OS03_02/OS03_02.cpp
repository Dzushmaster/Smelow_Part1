// OS03_01.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
int main()
{
	LPCWSTR an = L"D:\\University\\ОС\\Lab3\\OS03_01\\Debug\\OS03_02_01.exe";
	LPCWSTR bn = L"D:\\University\\ОС\\Lab3\\OS03_01\\Debug\\OS03_02_02.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	if (
		CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)//Имя_Модуля, командная строка, Дескр безоп, Дескр безоп, Дескр парам наслед, Флажок создания,
		//Нов_Блок_Конф, Имя_Тек_Каталога, Инф_Предуст, Инф_О_Проц
		)
		std::cout << "-- Process OS03_02_01 created\n";
	else
		std::cout << "-- Process OS03_02_01 not created\n";
	if (
		CreateProcess(bn, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)
		)
		std::cout << "-- Process OS03_02_02 created\n";
	else
		std::cout << "-- Process OS03_02_02 not created\n";

	DWORD pid = GetCurrentProcessId();
	for (int i = 0; i < 100; i++) {
		Sleep(1000);
		std::cout << i << " PID process:  " << pid << '\n';
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <algorithm>
#include <map>
#define OS09_01TXT L"D:/University/ОС/Lab9/OS09_01.txt"
#define FILE_PATH L"D:/University/ОС/Lab9/file.txt"
BOOL delRowFileTxt(LPWSTR FileName, DWORD row);
BOOL printFileTxt(LPWSTR FileName);
HANDLE openFile(LPWSTR FileName); 
std::map<int, std::string> getRows(LPWSTR filePath);
BOOL writeInFile(HANDLE file, std::map<int, std::string> row);
std::map<int, std::string> rows;
int main() {//получить элемент map и в файл
	setlocale(LC_CTYPE, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	rows = getRows((LPWSTR)OS09_01TXT);
	if (delRowFileTxt((LPWSTR)OS09_01TXT, 1) == FALSE)
		std::cout << "\n\nValue 1 didn't find\n\n";
	std::cout << "\nAfter delete 1\n";
	printFileTxt((LPWSTR)FILE_PATH);
	if (delRowFileTxt((LPWSTR)OS09_01TXT, 3) == FALSE)
		std::cout << "\n\nValue 3 didn't find\n\n";
	std::cout << "\nAfter delete 3\n";
	printFileTxt((LPWSTR)FILE_PATH);
	if (delRowFileTxt((LPWSTR)OS09_01TXT, 8) == FALSE)
		std::cout << "\n\nValue 8 didn't find\n\n";
	std::cout << "\nAfter delete 8\n";
	printFileTxt((LPWSTR)FILE_PATH);
	if (delRowFileTxt((LPWSTR)OS09_01TXT, 10) == FALSE)
		std::cout << "\n\nValue 10 didn't find\n\n";
	std::cout << "\nAfter delete 10\n";
	printFileTxt((LPWSTR)FILE_PATH);
	if (delRowFileTxt((LPWSTR)OS09_01TXT, 15) == FALSE)
		std::cout << "\n\nValue 15 didn't find\n\n";
	std::cout << "\nAfter delete 15\n";
	printFileTxt((LPWSTR)FILE_PATH);
 }
std::map<int, std::string> getRows(LPWSTR filePath) {
	std::map<int, std::string> rows;
	char buf[1024];
	HANDLE file = openFile(filePath);
	DWORD countBytes = NULL;
	ReadFile(file, &buf, 250, &countBytes, NULL);
	int i = 0, j = 1, k = 0;
	char bf[200] = "";
	while(buf[i] != '\0') {
		bf[k++] = buf[i++];
		if (buf[i] == '\n' && buf[i-1] == '\r') {
			bf[i] = '\0';
			i++;
			k = 0;
			std::string st;
			st.append(bf);
			rows.insert({ j++, st });
			ZeroMemory(&bf, sizeof(bf));;
		}
	} 
	CloseHandle(file);
	return rows;
}
BOOL delRowFileTxt(LPWSTR FileName, DWORD row) {
	HANDLE file;
	if ((file = openFile(FileName)) == NULL)
		return FALSE;
	try {
		if (rows.erase(row) == 0)
			return FALSE;
		writeInFile(file, rows);
		CloseHandle(file);
		return TRUE;
	}
	catch (const char* str) {
		CloseHandle(file);
		std::cout << "Error: " << str;
		return FALSE;
	}
}
BOOL writeInFile(HANDLE file, std::map<int, std::string> row) {
	DWORD n = NULL;
	std::ofstream out;
	out.open(FILE_PATH);
	if (!out.is_open())
		return FALSE;
	for (auto r = row.begin(); r != row.end(); r++) {
		out << r->second;
	}
	out.close();
	//HANDLE fil = openFile((LPWSTR)FILE_PATH);
	//for (auto r = row.begin(); r!=row.end(); r++) {
	//	const char* wcs = r->second.c_str();
	//	if (!WriteFile(fil, &wcs, wcslen(wcs) * sizeof(char), &n, NULL)) {
	//		CloseHandle(fil);
	//		return FALSE;
	//	}	
	//	//std::cout << r->second << '\n';
	//}
	//CloseHandle(fil);
	return TRUE;
}
BOOL printFileTxt(LPWSTR FileName)
{
	HANDLE file;
	if ((file = openFile(FileName)) == NULL)
		return FALSE;
	char buf[1024];
	DWORD countBytes = NULL;    
	ZeroMemory(buf, sizeof(buf));
	BOOL b = ReadFile(file, &buf, 1024, &countBytes, NULL);
	if (!b) throw "write file failed";
	std::cout << "-- Read file " << countBytes << " byte succesfull\n";
	std::string str = buf;
	std::replace(str.begin(), str.end(), '\r', '\n');
	std::cout << str;
	CloseHandle(file);
	//std::string line;
	//std::ifstream in(FILE_PATH);
	//if (!in.is_open())
	//	return FALSE;
	//
	//getline(in, line);
	//std::replace(line.begin(), line.end(), '\r', '\n');
	//std::cout << line;
	//in.close();
	return TRUE;
}

HANDLE openFile(LPWSTR FileName) {
	try {
		HANDLE hf = CreateFile(FileName,
			GENERIC_WRITE | GENERIC_READ,
			NULL, NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (hf == INVALID_HANDLE_VALUE) throw "create file failed";
		return hf;
	}
	catch (const char* em) {
		std::cout << "-- Error: " << em << '\n';
		return NULL;
	}
}
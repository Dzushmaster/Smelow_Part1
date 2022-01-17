#include <iostream>
#include <Windows.h>
BY_HANDLE_FILE_INFORMATION fileinfo;
std::string getFileName(wchar_t* filePath); 
LARGE_INTEGER getSizeFile(HANDLE file);
std::string writeTypeFile(HANDLE file);
BOOL printFileInfo(LPWSTR FileName);
BOOL printFileTxt(LPWSTR FileName);
HANDLE openFile(LPWSTR FileName);
#define FILE_PATH L"D:/University/ОС/Lab9/file.txt"
#define OS09_01TXT L"D:/University/ОС/Lab9/OS09_01.txt"
int main() {
	setlocale(LC_CTYPE, "Rus");
	ZeroMemory(&fileinfo, sizeof(BY_HANDLE_FILE_INFORMATION));
	printFileInfo((LPWSTR)FILE_PATH);
	printFileTxt((LPWSTR)OS09_01TXT);
	system("pause");
}
BOOL printFileTxt(LPWSTR FileName)
{
	try {
		HANDLE file;
		if ((file = openFile(FileName)) == NULL)
			return FALSE;
		char buf[1024];
		DWORD countBytes = NULL;
		ZeroMemory(buf, sizeof(buf));
		BOOL b = ReadFile(file, &buf, 200, &countBytes, NULL);
		if (!b) throw "write file failed";
		std::cout << "-- Read file " << countBytes << " byte succesfull:\n" << buf << '\n';
		CloseHandle(file);
		return TRUE;
	}
	catch (const char* em) {
		std::cout << "-- Error: " << em << '\n';
		return FALSE;
	}
}
BOOL printFileInfo(LPWSTR FileName) {
	HANDLE file;
	SYSTEMTIME sysTime;
	ZeroMemory(&sysTime, sizeof(SYSTEMTIME));
	if((file = openFile((LPWSTR)(FILE_PATH))) == NULL)
		return FALSE;
	GetFileInformationByHandle(file, &fileinfo);
	if (&fileinfo == NULL) {
		CloseHandle(file);
		return FALSE;
	}
	std::cout << "FileName: " << getFileName((wchar_t*)FILE_PATH) << '\n';
	std::cout << "Type: " << writeTypeFile(file) << '\n';
	std::cout << "Size(GetFileSizeEx): " << getSizeFile(file).LowPart << "B" << '\n';
	std::cout << "Size: " << fileinfo.nFileSizeLow << "B" << '\n';
	FileTimeToSystemTime(&fileinfo.ftCreationTime, &sysTime);
	std::cout << "CreationTime: " << sysTime.wDay << '.' << sysTime.wMonth  << '.' << sysTime.wYear  <<
		' ' << sysTime.wHour + 3 << ':' << sysTime.wMinute << '\n';
	FileTimeToSystemTime(&fileinfo.ftLastWriteTime, &sysTime);
	std::cout << "UpdateTime: " << sysTime.wDay << '.' << sysTime.wMonth << '.' << sysTime.wYear <<
		' ' << sysTime.wHour + 3 << ':' << sysTime.wMinute << '\n';
	CloseHandle(file);
	return TRUE;
}
LARGE_INTEGER getSizeFile(HANDLE file) {
	LARGE_INTEGER lpFileSize;
	ZeroMemory(&lpFileSize, sizeof(LARGE_INTEGER));
	GetFileSizeEx(file, &lpFileSize);
	return lpFileSize;
}
std::string getFileName(wchar_t* filePath) {
	std::wstring ws(filePath);
	std::string filename(ws.begin(), ws.end());
	const size_t last_slash_idx = filename.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		filename.erase(0, last_slash_idx + 1);
	}
	return filename;
}
std::string writeTypeFile(HANDLE file) {
	switch (GetFileType(file)) {
	case FILE_TYPE_UNKNOWN:
		return "FILE_TYPE_UNKNOWN";
	case FILE_TYPE_DISK:
		return "FILE_TYPE_DISK";
	case FILE_TYPE_CHAR:
		return "FILE_TYPE_CHAR";
	case FILE_TYPE_PIPE:
		return "FILE_TYPE_PIPE";
	case FILE_TYPE_REMOTE:
		return "FILE_TYPE_REMOTE";
	default:
		return "ERROR: WRITE FILE TYPE";
	}
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
		std::cout << "Create file or open successfull\n";
		return hf;
	}
	catch (const char* em) {
		std::cout << "-- Error: " << em << '\n';
		return NULL;
	}
}
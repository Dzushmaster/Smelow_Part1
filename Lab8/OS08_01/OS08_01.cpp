#include <Windows.h>
#include <iostream>
#include <ctime>

int main() {
	time_t t1;
	t1 = time(&t1);
	tm ttm;
	localtime_s(&ttm, &t1);
	std::cout << "--localtime--\n";
	std::cout << ttm.tm_mday << '.' 
		<< ttm.tm_mon + 1 << '.'
		<< ttm.tm_year + 1900<< ' ' 
		<< ttm.tm_hour << ':'
		<< ttm.tm_min << ':'
		<< ttm.tm_sec;
}
#include <Windows.h>
#include <iostream>
#include <ctime>

int main() {
	clock_t start = clock();

	int k = 0;
	bool s5 = true, s10 = true;
	while (true) {
		k++;
		if ((clock() - start) / CLOCKS_PER_SEC == 5 && s5) {
			std::cout << "After 5s k = " << k << '\n';
			s5 = false;
		}
		if ((clock() - start) / CLOCKS_PER_SEC == 10 && s10) {
			std::cout << "After 10s k = " << k << '\n';
			s10 = false;
		}
		if ((clock() - start) / CLOCKS_PER_SEC == 15) {
			std::cout << "After 15s k = " << k << '\n';
			break;
		}
	}
}
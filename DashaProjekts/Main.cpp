#include "Header.h"

int main() {
	HWND hwnd = GetConsoleWindow();
	HANDLE h = GetStdHandle(-11);
	Setings(h, hwnd);
	Word word{ 6 };
	MenuGreenText(h, 0, 0);
	MenuEvent(h, word);
	system("pause > NULL");
}
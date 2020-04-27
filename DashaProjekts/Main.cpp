#include "Header.h"

int main() {
	HWND hwnd = GetConsoleWindow();
	HANDLE h = GetStdHandle(-11);
	Setings(h, hwnd);
	Word word{ 7 };
	MenuGreenText(h, 0, 0);
	MenuEvent(h, word, false);
	system("cls");
	Loading(h, int(Colors::GREEN));
	CreateWord(word);
	system("cls");
	setlocale(LC_ALL, "C");
	Frame(h, word, 10, 35);
	setlocale(LC_ALL, "RUS");
	GameplayPrint(h, word, 4, 8);
	GamePlay(h, word);
	system("pause > NULL");
}
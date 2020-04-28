#include "Header.h"

int main() {
	HWND hwnd = GetConsoleWindow();
	HANDLE h = GetStdHandle(-11);
	Setings(h, hwnd);
	Word word{ 17 };
	MenuGreenText(h, 0, 0);
	MenuEvent(h, word, false);
	system("cls");
	Loading(h, int(Colors::GREEN));
	CreateWord(word);
	system("cls");
	Frame(h, word, 10, 35);
	GameplayPrint(h, word, 4, 8);
	GamePlay(h, word, 13, int(Colors::RED), int(Colors::GREEN));
	system("pause > NULL");
}
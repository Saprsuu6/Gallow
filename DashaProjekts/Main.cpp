#include "Header.h"

int main() {
	HWND hwnd = GetConsoleWindow();
	HANDLE h = GetStdHandle(-11);
	Setings(h, hwnd);
	Word word{ 17 };
	MenuGreenText(h, 0, 0, int(Colors::GREEN));
	MenuEvent(h, word, false, int(Colors::RED), int(Colors::GREEN));
	system("cls");
	//Loading(h, int(Colors::GREEN));
	CreateWord(word);
	CountLetters(word);
	system("cls");
	Frame(h, word, 10, 35);
	GameplayPrint(h, word, 8);
	GamePlay(h, word, 13, int(Colors::RED), int(Colors::GREEN), int(Colors::PINK));
	system("pause > NULL");
}
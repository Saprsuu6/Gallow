// подключение собственного заголовочного файла
#include "Header.h"

// фунция мэйн с выполнение собственных(моих) функций
// все действия функций описаны в OtherFoo.cpp
int main() {
	HWND hwnd = GetConsoleWindow();
	HANDLE h = GetStdHandle(-11);
	Setings(h, hwnd);
	Word word{ 12 }; // списковая инициализация(только превой переменной)
	CreatePapka();
	FillWordsTxt();
	FillHintsTxt();
	MenuGreenText(h, 0, 0, int(Colors::GREEN)); // явное преобразование в int т.к. Colors содержит целосленные КОНСТАНТЫ
	//MenuEvent(h, word, false, int(Colors::RED), int(Colors::GREEN));
	system("cls"); // очистка экрана
	Loading(h, int(Colors::GREEN));
	CreateWord(word);
	CountLetters(word);
	system("cls");
	Frame(h, word, 10, 35);
	GameplayPrint(h, word, 8);
	GamePlay(h, word, 13, int(Colors::RED), int(Colors::GREEN), int(Colors::PINK));
	system("pause > NULL"); // завершение после нажатия на любую клавишу
}
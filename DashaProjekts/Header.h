#include<iostream>
#include<Windows.h>
#include<ctime>
#include<conio.h>
using namespace std;

enum class Colors { GREEN = 10, RED = 4, PINK = 13 };

struct Word {
    int length;
    char* str = new char[length];
};

void Setings(const HANDLE& h, const HWND& hwnd);
void MenuGreenText(const HANDLE& h, int x, int y, int color);
void MenuEvent(HANDLE& h, Word& word, bool exit, int color, int color2);
void MenuDarkGreenText(const HANDLE& h, string str, int x, int y, int color);
int GameSetings();
int main();
void Exit();
void Loading(const HANDLE& h, int color);
void CreateWord(Word& word);
void Frame(const HANDLE& h, const Word& word, int hight, int width);
void GameplayPrint(const HANDLE& h, const Word& word, int width);
void CountLetters(Word& word);
void GamePlay(const HANDLE& h, const Word& word, int enter, int color, int color2, int color3);
int RandomLatter(const Word& word, int*& ar);
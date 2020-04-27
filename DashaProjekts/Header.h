#include<iostream>
#include<Windows.h>
#include<ctime>
#include<conio.h>
using namespace std;

enum class Colors { GREEN = 10, RED = 4 };

struct Word {
    int length;
    char* str = new char[length];
};

void Setings(HANDLE& h, HWND& hwnd);
void MenuGreenText(HANDLE& h, int x, int y);
void MenuEvent(HANDLE& h, Word& word, bool exit);
void MenuDarkGreenText(HANDLE& h, string str, int x, int y, int color);
int GameSetings();
int main();
void Exit();
void Complexity(HANDLE& h, Word& word);
void Loading(HANDLE& h, int color);
void CreateWord(Word& word);
void Frame(HANDLE& h, Word& word, int hight, int width);
void GameplayPrint(HANDLE& h, Word& word, int hight, int width);
void CountLetters(Word& word);
void GamePlay(HANDLE& h, Word& word);
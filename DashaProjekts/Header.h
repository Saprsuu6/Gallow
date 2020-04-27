#include<iostream>
#include<Windows.h>
#include<ctime>
#include<conio.h>
using namespace std;

struct Word {
    int length;
    char* str = new char[length];
};

void Setings(HANDLE& h, HWND& hwnd);
void MenuGreenText(HANDLE& h, int x, int y);
void MenuEvent(HANDLE& h, Word& word);
void MenuDarkGreenText(HANDLE& h, string str, int x, int y, int color);
int GameSetings();
int main();
void Exit();
void Complexity(HANDLE& h, Word& word);
void Loading(HANDLE& h, int color);
#include<iostream>
#include<Windows.h>
#include<ctime>
using namespace std;

void Setings(HANDLE& h, HWND& hwnd);
void MenuGreenText(HANDLE& h, int x, int y);
void MenuEvent(HANDLE& h, Word& word);
void MenuDarkGreenText(HANDLE& h, string str, int x, int y, int color);
int GameSettings();
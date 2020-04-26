#include "Header.h"

enum Colours { GREEN = 10, DARK_GREEN = 2 };

void Setings(HANDLE& h, HWND& hwnd) {
    system("mode con cols=70 lines=25");
    SetConsoleTextAttribute(h, 10);
    system("title Gallows");
    setlocale(LC_ALL, "RUS");
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 100;
    SetConsoleCursorInfo(h, &info);
    srand(time(0));
}

struct Word {
    int length;
    char* str = new char[length];
};

void MenuGreenText(HANDLE& h, int x, int y) {
    COORD text{ x,y };
    SetConsoleCursorPosition(h, text);
    SetConsoleTextAttribute(h, DARK_GREEN);
    SetConsoleTextAttribute(h, GREEN);
    cout << "Начать игру." << endl;
    cout << "Настройки." << endl;
    cout << "Выход." << endl;
}

void MenuDarkGreenText(HANDLE& h, string str, int x, int y, int color) {
    COORD text{ x,y };
    SetConsoleCursorPosition(h, text);
    SetConsoleTextAttribute(h, color);
    cout << str;
}

void MenuEvent(HANDLE& h, Word& word) {
    COORD mouse;
    HANDLE h_m = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(h_m, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    const int events = 256;
    INPUT_RECORD all_events[events];
    DWORD read_event;
    while (true) {
        ReadConsoleInput(h_m, all_events, events, &read_event);
        for (int i = 0; i < read_event; i++) {
            mouse.X = all_events[i].Event.MouseEvent.dwMousePosition.X;
            mouse.Y = all_events[i].Event.MouseEvent.dwMousePosition.Y;
            MenuGreenText(h, 0, 0);
            if (mouse.X >= 0 && mouse.X <= 11 && mouse.Y == 0)
                MenuDarkGreenText(h, "Начать игру.", 0, 0, DARK_GREEN);
            else if (mouse.X >= 0 && mouse.X <= 9 && mouse.Y == 1)
                MenuDarkGreenText(h, "Настройки.", 0, 1, DARK_GREEN);
            else if (mouse.X >= 0 && mouse.X <= 5 && mouse.Y == 2)
                MenuDarkGreenText(h, "Выход.", 0, 2, DARK_GREEN);
            if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED &&
                mouse.X >= 0 && mouse.X <= 5 && mouse.Y == 2)
                system("taskkill /im Gallow.exe");
            else if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED &&
                mouse.X >= 0 && mouse.X <= 9 && mouse.Y == 1) {
                cout << "1 - Сложно, 2 - Нормально, 3 - Легко\nВыберите сложность:";
                if (GameSettings() == 1)
                    word.length = 5;
                else if (GameSettings() == 2)
                    word.length = 10;
                else if (GameSettings() == 3)
                    word.length = 15;
            }
                
        }
    }
}

int GameSettings() {
    int complexity;
    cin >> complexity;
    return complexity;
}

//void CreateWord(Word& word) {
//    cin.getline(word.str, word.length - 1);
//}
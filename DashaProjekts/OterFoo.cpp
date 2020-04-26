#include "Header.h"

enum Colours { GREEN = 10, RED = 4 };

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

void MenuGreenText(HANDLE& h, int x, int y) {
    COORD text{ x,y };
    SetConsoleCursorPosition(h, text);
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

void Complexity(HANDLE& h, Word& word) {
    SetConsoleTextAttribute(h, GREEN);
    cout << "1 - Легко, 2 - Нормально, 3 - Сложно\nВыберите сложность и нажмите ENTER: ";
    int setings = GameSetings();
    cout << setings;
    if (setings == 1)
        word.length = 6;
    else if (setings == 2)
        word.length = 8;
    else if (setings == 3)
        word.length = 10;
    else {
        system("cls");
        cout << "Попробуйте ещё раз!" << endl;
        Complexity(h, word);
    }
    main();
}

void Exit() {
    int message = MessageBoxA(0, "", "Вы точно хотите выйти?", MB_YESNO);
    if (message == IDYES)
        system("taskkill /im Gallow.exe");
    else
        main();
}

int GameSetings() {
    int complexity;
    cin >> complexity;
    return complexity;
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
                MenuDarkGreenText(h, "Начать игру.", 0, 0, RED);
            else if (mouse.X >= 0 && mouse.X <= 9 && mouse.Y == 1)
                MenuDarkGreenText(h, "Настройки.", 0, 1, RED);
            else if (mouse.X >= 0 && mouse.X <= 5 && mouse.Y == 2)
                MenuDarkGreenText(h, "Выход.", 0, 2, RED);
            if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED &&
                mouse.X >= 0 && mouse.X <= 5 && mouse.Y == 2)
                Exit();
            else if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED &&
                mouse.X >= 0 && mouse.X <= 9 && mouse.Y == 1) {
                system("cls");
                Complexity(h, word);
            }
            else if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED &&
                mouse.X >= 0 && mouse.X <= 11 && mouse.Y == 0) {
                system("cls");
                Complexity(h, word);
            }
        }
    }
}
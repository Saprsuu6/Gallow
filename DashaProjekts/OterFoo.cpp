#include "Header.h"

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
    SetConsoleTextAttribute(h, int(Colors::GREEN));
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
    SetConsoleTextAttribute(h, int(Colors::GREEN));
    cout << "1 - Легко, 2 - Нормально, 3 - Сложно\nВыберите сложность и нажмите ENTER: ";
    int setings = GameSetings();
    cout << setings;
    if (setings == 1)
        word.length = 7;
    else if (setings == 2)
        word.length = 9;
    else if (setings == 3)
        word.length = 11;
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

void Loading(HANDLE& h, int color) {
    COORD c{ 7,0 };
    SetConsoleTextAttribute(h, color);
    for (int i = 0; i < 3; i++) {
        cout << "Loading";
        for (int i = 0; i < 3; i++) {
            Sleep(100);
            SetConsoleCursorPosition(h, c);
            cout << ".";
            Sleep(200);
            c.X++;
            if (c.X == 10) {
                system("cls");
                c.X = 7;
            }
        }
    }
}

void MenuEvent(HANDLE& h, Word& word, bool exit) {
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
                MenuDarkGreenText(h, "Начать игру.", 0, 0, int(Colors::RED));
            else if (mouse.X >= 0 && mouse.X <= 9 && mouse.Y == 1)
                MenuDarkGreenText(h, "Настройки.", 0, 1, int(Colors::RED));
            else if (mouse.X >= 0 && mouse.X <= 5 && mouse.Y == 2)
                MenuDarkGreenText(h, "Выход.", 0, 2, int(Colors::RED));
            if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED &&
                mouse.X >= 0 && mouse.X <= 5 && mouse.Y == 2)
                Exit();
            else if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED &&
                mouse.X >= 0 && mouse.X <= 9 && mouse.Y == 1) {
                system("cls");
                Complexity(h, word);
            }
            else if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED &&
                mouse.X >= 0 && mouse.X <= 11 && mouse.Y == 0)
                exit = true;
        }
        if (exit == true)
            break;
    }
}

void CreateWord(Word& word) {
    cout << "Введите слово или словосочетание из " << word.length - 1 << " букв: ";
    cin.getline(word.str, word.length);
    _strcmpi(word.str, "\0");
    CountLetters(word);
}

void CountLetters(Word& word) {
    int letters = 0;
    for (int i = 0; i < word.length; i++) {
        if (word.str[i] > 0 && word.str[i] < 256)
            letters++;
    }
    word.length = letters;
}

void Frame(HANDLE& h, Word& word, int hight, int width) {
    for (int i = 0; i < hight; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 && j == 0)
                cout << char(201);
            else if (i == hight - 1 && j == 0)
                cout << char(200);
            else if (i == 0 && j == width - 1)
                cout << char(187);
            else if (i == hight - 1 && j == width - 1)
                cout << char(188);
            else if (i == 0 && j == 17)
                cout << char(203);
            else if (i == hight - 1 && j == 17)
                cout << char(202);
            else if (i == 0 || i == hight - 1)
                cout << char(205);
            else if (j == 0 || j == width - 1 || j == 17)
                cout << char(186);
            else if (i == 2 && j > 0 && j < word.length + 1) 
                cout << "-";
            else
                cout << " ";
        }
        cout << endl;
    }
}

void GameplayPrint(HANDLE& h, Word& word, int hight, int width) {
    COORD c{ 1,3 };
    SetConsoleCursorPosition(h, c);
    cout << "Введите букву: ";
    c.Y+=2;
    for (int i = 0; i < hight; i++) {
        SetConsoleCursorPosition(h, c);
        for (int j = 0; j < width; j++) {
            SetConsoleTextAttribute(h, rand() % 14 + 1);
            cout << ":)";
        }
        c.Y++;
    }
}

void GamePlay(HANDLE& h, Word& word) {
    COORD input{ 16,3 };
    char latter;
    for (int i = 0; i < word.length; i++) {
        SetConsoleCursorPosition(h, input);
        
    }
}
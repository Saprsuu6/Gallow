#include "Header.h"

void Setings(const HANDLE& h, const HWND& hwnd) {
    system("mode con cols=70 lines=25");
    SetConsoleTextAttribute(h, 10);
    system("title Gallows");
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 100;
    SetConsoleCursorInfo(h, &info);
    srand(time(0));
}

void MenuGreenText(const HANDLE& h, int x, int y) {
    COORD text{ x,y };
    SetConsoleCursorPosition(h, text);
    SetConsoleTextAttribute(h, int(Colors::GREEN));
    cout << "Start game." << endl;
    cout << "Setings." << endl;
    cout << "Exit." << endl;
}

void MenuDarkGreenText(const HANDLE& h, string str, int x, int y, int color) {
    COORD text{ x,y };
    SetConsoleCursorPosition(h, text);
    SetConsoleTextAttribute(h, color);
    cout << str;
}

void Complexity(const HANDLE& h, Word& word) {
    SetConsoleTextAttribute(h, int(Colors::GREEN));
    cout << "1 - Easy, 2 - Normal, 3 - Hard\nChoose complexity and press ENTER: ";
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
        cout << "Try again!" << endl;
        Complexity(h, word);
    }
    main();
}

void Exit() {
    int message = MessageBoxA(0, "", "Do you realy to exit?", MB_YESNO);
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

void Loading(const HANDLE& h, int color) {
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
                MenuDarkGreenText(h, "Start game.", 0, 0, int(Colors::RED));
            else if (mouse.X >= 0 && mouse.X <= 9 && mouse.Y == 1)
                MenuDarkGreenText(h, "Setings.", 0, 1, int(Colors::RED));
            else if (mouse.X >= 0 && mouse.X <= 5 && mouse.Y == 2)
                MenuDarkGreenText(h, "Exit.", 0, 2, int(Colors::RED));
            if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED &&
                mouse.X >= 0 && mouse.X <= 5 && mouse.Y == 2)
                Exit();
            /*else if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && // not fix
                mouse.X >= 0 && mouse.X <= 9 && mouse.Y == 1) {                                        // not fix
                system("cls");                                                                         // not fix
                Complexity(h, word);                                                                   // not fix
            }*/                                                                                        // not fix
            else if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED &&
                mouse.X >= 0 && mouse.X <= 11 && mouse.Y == 0)
                exit = true;
        }
        if (exit == true)
            break;
    }
}

void CreateWord(Word& word) {
    cout << "Enter word or sentence from " << word.length - 1 << " latters(ENGLISH): ";
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

void Frame(const HANDLE& h, const Word& word, int hight, int width) {
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

void GameplayPrint(const HANDLE& h, const Word& word, int hight, int width) {
    COORD c{ 1,3 };
    SetConsoleCursorPosition(h, c);
    cout << "Enter latter:" << char(26) << " " << char(27);
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

void GamePlay(const HANDLE& h, const Word& word, int enter, int color, int color2) {
    COORD input;
    char latter;
    for (int i = 0; i < word.length; i++) {
        while (true) {
            input.Y = 3;
            input.X = 15;
            SetConsoleTextAttribute(h, color);
            SetConsoleCursorPosition(h, input);
            int code = _getch();
            if (code == 224)
                code = _getch();
            if(code != 9)
                cout << char(code);
            input.Y++;
            input.X -= 14;
            SetConsoleTextAttribute(h, color2);
            SetConsoleCursorPosition(h, input);
            cout << "Press ENTER";
        }
    }
}
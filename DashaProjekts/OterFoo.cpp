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

void MenuGreenText(const HANDLE& h, int x, int y, int color) {
    COORD text{ x,y };
    SetConsoleCursorPosition(h, text);
    SetConsoleTextAttribute(h, color);
    cout << "Start game." << endl;
    cout << "Exit." << endl;
}

void MenuDarkGreenText(const HANDLE& h, string str, int x, int y, int color) {
    COORD text{ x,y };
    SetConsoleCursorPosition(h, text);
    SetConsoleTextAttribute(h, color);
    cout << str;
}

void Exit() {
    int message = MessageBoxA(0, "Do you realy to exit?", "", MB_YESNO);
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

void MenuEvent(HANDLE& h, Word& word, bool exit, int color, int color2) {
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
            MenuGreenText(h, 0, 0, color2);
            if (mouse.X >= 0 && mouse.X <= 11 && mouse.Y == 0)
                MenuDarkGreenText(h, "Start game.", 0, 0, color);
            else if (mouse.X >= 0 && mouse.X <= 5 && mouse.Y == 1)
                MenuDarkGreenText(h, "Exit.", 0, 1, color);
            if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED &&
                mouse.X >= 0 && mouse.X <= 5 && mouse.Y == 1)
                Exit();                                                                                    
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

void GameplayPrint(const HANDLE& h, const Word& word, int width) {
    COORD c{ 1,3 };
    SetConsoleCursorPosition(h, c);
    cout << "Enter latter:" << char(26) << " " << char(27);
    c.Y+=5;
    for (int i = 0; i < width; i++) {
        SetConsoleCursorPosition(h, c);
        SetConsoleTextAttribute(h, rand() % 14 + 1);
        cout << ":)";
        c.X += 2;
    }
}

void GamePlay(const HANDLE& h, const Word& word, int enter, int color, int color2, int color3) {
    COORD input;
    int code;
    char latter_code = 0;
    int latters_left = word.length;
    int* ar = new int[word.length];
    int ind_of_latter = RandomLatter(word, ar);
    while (true) {
        int exit_from_cycle = 0;
        input.X = 1;
        input.Y = 6;
        SetConsoleCursorPosition(h, input);
        SetConsoleTextAttribute(h, color3);
        cout << "Latters left: " << latters_left;
        input.Y++;
        SetConsoleCursorPosition(h, input);
        cout << "Now " << ind_of_latter + 1 << " latter!";
        while (true) {
            input.Y = 3;
            input.X = 15;
            SetConsoleCursorPosition(h, input);
            SetConsoleTextAttribute(h, color);
            code = Input();
            if (code != 13)
                latter_code = code;
            else
                exit_from_cycle = code;
            if (latter_code != 9) // TAB and ENTER
                cout << char(latter_code);
            if (exit_from_cycle == 13) //ENTER
                break;
            input.Y++;
            input.X -= 14;
            SetConsoleCursorPosition(h, input);
            SetConsoleTextAttribute(h, color2);
            cout << "Press ENTER";
        }
        Check(h, input, word, latter_code, ind_of_latter, ar, latters_left);
        CheckForFinish(latters_left);
    }
}


// почему-то не хочет нормально работать
int RandomLatter(const Word& word, int*& ar) {  
    int value = rand() % word.length;           
    for (int i = 0; i < word.length; i++) {     
        if (ar[i] == value) {                   
            while (value == ar[i])              
                value = rand() % word.length;   
            i = 0;                              
        }                                       
    }                                           
    ar[value] = value;                          
    return value;                               
}                                               

int Input() {
    int code = _getch();
    if (code == 224)
        code = _getch();
    return code;
}

void Check(const HANDLE& h, COORD& input, const Word& word, int latter_code, int& ind_of_latter, int*& ar,
    int& latters_left) {
    if (latter_code == char(word.str[ind_of_latter])) {
        input.X = ind_of_latter + 1;
        input.Y = 1;
        SetConsoleCursorPosition(h, input);
        cout << char(latter_code);
        Effect(h, input, int(Colors::LIGHT_RED), int(Colors::GREEN), "RIGHT:)");
        ind_of_latter = RandomLatter(word, ar);
        latters_left--;
    }
    else 
        Effect(h, input, int(Colors::LIGHT_RED), int(Colors::GREEN), "WRONG:(");
}

void Effect(const HANDLE& h, COORD& input, int color, int color2, string str) {
    input.X = 1;
    input.Y = 5;
    for (int i = 0; i < 6; i++) {
        if (i % 2 == 0)
            SetConsoleTextAttribute(h, color);
        else
            SetConsoleTextAttribute(h, color2);
        SetConsoleCursorPosition(h, input);
        cout << str;
        Sleep(200);
    }
    Sleep(100);
    SetConsoleCursorPosition(h, input);
    cout << "       ";
}

void CheckForFinish(int latters_left) {
    if (latters_left == 0) {
        MusikWin();
        int message = MessageBoxA(0, "You have guessed all latters. Do you wnat to play again?", "You win!!!", MB_YESNO);
        if (message == IDYES)
            main();
        else
            system("taskkill /im Gallow.exe");
    }
}

void MusikWin() {
    Beep(494, 500);
    for (int i = 0; i < 2; i++)
        Beep(523, 100);
    Beep(523, 100);
    Beep(880, 500);
}
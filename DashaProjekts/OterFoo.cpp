// символ &(ссылка) при преданых значений в функцию называется передача параметра по ссылке(и измененение его на прямую, а не через копию)
// два символа *(указатель на массив)&(ссылка) при преданых значений в функцию называется передача указателя на массив по ссылке
// указатель на массив указывает на первый его элемент
// тип char автоматически преобразовывает число в литерал исходя из таблици ASCI

// подключение собственного заголовочного файла
#include "Header.h"

void Setings(const HANDLE& h, const HWND& hwnd) {
    system("mode con cols=70 lines=25"); // настройка размеров окна консоли
    SetConsoleTextAttribute(h, 10); // настройка главного цвета
    system("title Gallow"); // название окна консоли
    // делаем курсор невидемым
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 100;
    SetConsoleCursorInfo(h, &info);
    // для постоянного рандома
    srand(time(0));
}

// функция вывода текста меню с использованием координат
void MenuGreenText(const HANDLE& h, int x, int y, int color) {
    COORD text{ x,y };
    SetConsoleCursorPosition(h, text);
    SetConsoleTextAttribute(h, color);
    cout << "Start game." << endl;
    cout << "Exit." << endl;
}

// функция вывода текста меню с использованием координат(когда поднесли курсор)
void MenuRedText(const HANDLE& h, string str, int x, int y, int color) {
    COORD text{ x,y };
    SetConsoleCursorPosition(h, text);
    SetConsoleTextAttribute(h, color);
    cout << str;
}

// функция выхода с использова окна виндовс
void Exit() {
    int message = MessageBoxA(0, "Do you realy to exit?", "", MB_YESNO);
    if (message == IDYES)
        system("taskkill /im Gallow.exe");
    else
        main();
}

// функция воображаемой нагрузки на процессор с и спользованием цикла и перестановки координат
void Loading(const HANDLE& h, int color) {
    COORD c{ 7,0 }; // юудем рисовать точки на этих координатах 
    SetConsoleTextAttribute(h, color);
    for (int i = 0; i < 3; i++) {
        cout << "Loading";
        for (int i = 0; i < 3; i++) {
            Sleep(100);
            SetConsoleCursorPosition(h, c);
            cout << "."; // нарисовали точку
            Sleep(200); // подождать 200 сек.
            c.X++; // увеличили ао х
            if (c.X == 10) { // если х = 10, стираем и делаем заного
                system("cls"); // очистка экрана
                c.X = 7;
            }
        }
    }
}

// функция событи мышки
void MenuEvent(HANDLE& h, Word& word, bool exit, int color, int color2) {
    COORD mouse; // координаты мышки
    HANDLE h_m = GetStdHandle(STD_INPUT_HANDLE); // дескриптор ввода мышки в дискриптор консоли
    SetConsoleMode(h_m, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS); // установка режима использования мышки
    const int events = 256; // количество событий за момент
    INPUT_RECORD all_events[events]; // массив событий за момент произошедших в консоли 
    DWORD read_event; // пере менная в которую записывется количество произошедших событий
    while (true) { // бесконечный цикл
        ReadConsoleInput(h_m, all_events, events, &read_event); // получение всех событий произош. в консоли 
        for (int i = 0; i < read_event; i++) { // цикл каждого события
            mouse.X = all_events[i].Event.MouseEvent.dwMousePosition.X; // получение координат мышки
            mouse.Y = all_events[i].Event.MouseEvent.dwMousePosition.Y; // получение координат мышки
            MenuGreenText(h, 0, 0, color2); // Функция показа текста
            if (mouse.X >= 0 && mouse.X <= 11 && mouse.Y == 0)
                MenuRedText(h, "Start game.", 0, 0, color); // функция показа крассным цветом при наведении
            else if (mouse.X >= 0 && mouse.X <= 5 && mouse.Y == 1)
                MenuRedText(h, "Exit.", 0, 1, color); // функция показа крассным цветом при наведении
            if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && 
                mouse.X >= 0 && mouse.X <= 5 && mouse.Y == 1) // если была нажата ПРАВАЯ(1ST) кнопка мыши
                Exit(); // функция выхода                                                                                   
            else if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED &&
                mouse.X >= 0 && mouse.X <= 11 && mouse.Y == 0) // если была нажата ПРАВАЯ(1ST) кнопка мыши
                exit = true; // переменная которая означает выход из бесконечного цикла и начало игры
        }
        if (exit == true)
            break; // выход из бесконечного цикла и начало игры
    }
}

void CreatePapka() {
    _mkdir("Source");
}

void FillWordsTxt() {
    FILE* file;
    Words words;
    fopen_s(&file, "Source\\Words.txt", "w");
    for (int i = 0; i < words.length; i++)
        fputs(words.str[i], file);
}

void FillHintsTxt() {
    FILE* file;
    Hints hints;
    fopen_s(&file, "Source\\Hints.txt", "w");
    for (int i = 0; i < hints.length; i++)
        fputs(hints.str[i], file);
}

// word. доступ переменноый структуры через объект типа структуры
void CreateWord(Word& word) { // ввод символов из 12 доступных
    /*Words words;
    FILE* file;
    int str = 0;
    char* temp = new char[100];
    int random = rand() % words.length;
    fopen_s(&file, "Source\\Words.txt", "r");
    while (!feof(file)) {
        if (str == random) 
            fgets(temp, 99, file);
        str++;
    }
    fclose(file);
    word.str = temp;
    cout << word.str;
    Sleep(INFINITE);*/
    cout << "Enter word or sentence from " << word.length - 1 << " latters(ENGLISH): ";
    cin.getline(word.str, word.length); // ввыод в маасив символов с максимальной размерностью автоматическое выставление \0 для обозначения конца строки
    CountLetters(word); // функция подсчёта символов слова кроме \0
}

// функция подсчёта символов слова кроме \0
void CountLetters(Word& word) {
    int letters = 0;
    for (int i = 0; i < word.length; i++) {
        if (word.str[i] > 0 && word.str[i] < 256) // если символ находится в диапазоне значений ASCI
            letters++;
    }
    word.length = letters; // запись в переменную структуры количество символов
}

// создание рамки для игры
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
            else if (i == 2 && j > 0 && j < word.length + 1) // печать символа "-" для  обозначения количества символов
                cout << "-";
            else
                cout << " ";
        }
        cout << endl;
    }
}

// функция печати 
void GameplayPrint(const HANDLE& h, const Word& word, int width) {
    COORD c{ 1,3 };
    SetConsoleCursorPosition(h, c);
    cout << "Enter latter:" << char(26) << " " << char(27); // между стрелочек будет писаться буква
    c.Y+=5; // увеличение координаты у на 5
    for (int i = 0; i < width; i++) {
        SetConsoleCursorPosition(h, c);
        SetConsoleTextAttribute(h, rand() % 14 + 1);
        cout << ":)"; // для красоты)
        c.X += 2;
    }
}

// функция самого геймплея
void GamePlay(const HANDLE& h, const Word& word, int enter, int color, int color2, int color3) {
    COORD input; // координаты для работы с текстом
    int fail = 0; // колчество неправильных вводов
    int code; // переменная с кодом нажатой клавиши
    char latter_code = 0; // код символа
    int latters_left = word.length; // сколько букв осталось
    int* ar = new int[word.length]; // чтобы программа не повторяла ввод одного и того же слова, если оно было введено ПРАВИЛЬНО
    int ind_of_latter = RandomLatter(word, ar); // создание индекса по которому находиться буква
    while (true) {
        int exit_from_cycle = 0; // переменная для выхода из цикла
        input.X = 1;
        input.Y = 6;
        SetConsoleCursorPosition(h, input);
        SetConsoleTextAttribute(h, color3); // выбор цвета
        cout << "Latters left: " << latters_left; // запись по координатам (1,6)
        input.Y++; //увеличение координаты у на 1 
        SetConsoleCursorPosition(h, input);
        cout << "Now " << ind_of_latter + 1 << " latter  "; // запись количества оставшихся букв  
        while (true) {
            input.Y = 3;
            input.X = 15;
            SetConsoleCursorPosition(h, input);
            SetConsoleTextAttribute(h, color);
            code = Input(); // взятие кода по нажатой клавиши клавиши и её запись в переменную
            if (code != 13) // если код не равен клавише ENTER то в пременную записывается код буквы
                latter_code = code;
            else // в другом случае в переменную входа из цикла присваивается код 13
                exit_from_cycle = code;
            if (latter_code != 9) // показ всех сиволов кроме символа по коду клавиши TAB
                cout << char(latter_code); // показ по координатам (15,3)
            if (exit_from_cycle == 13) // выход из цикла если пременная выход равна 13
                break; 
            input.Y++;
            input.X -= 14;
            SetConsoleCursorPosition(h, input);
            SetConsoleTextAttribute(h, color2);
            cout << "Press ENTER"; // показ по координатам (1,4)
        }
        Check(h, input, word, latter_code, ind_of_latter, ar, latters_left, fail); // функциия проверки символов
        CheckForFinish(word, latters_left, fail); // проверка на конец игры
    }
}

// функция для взятия рандомной буквы
int RandomLatter(const Word& word, int*& ar) {  
    int value = rand() % word.length; // запись в переменную рандомного числа в диапазоне от 0 до количества симолов - 1 включительно 
    for (int i = 0; i < word.length; i++) {     
        if (ar[i] == value) { // если по такомуто индексу найдено токоеже число                   
            while (value == ar[i]) // запуск массива пока не изменится число              
                value = rand() % word.length;   
            i = 0; // обнуление счётчика чтобы не повторялось значение в любом индексе массива                             
        }                                       
    }                                           
    ar[value] = value; // запись значения в массив по ткомуто индексу                     
    return value; // возврат значения и запись в пременную ind_of_latter                             
}                                               

// функция ввода символа из клавиатуры
int Input() {
    int code = _getch(); // функция _getch() возврашает код по нажатой клавише 
    if (code == 224) // эта функцтя не зависимо от нажатия возвращает код 224
        code = _getch(); // поэтому мы повторно запрашиваем 
    return code; // возврат значения и запись в пременную code
}

// функция проверки символов
void Check(const HANDLE& h, COORD& input, const Word& word, int latter_code, int& ind_of_latter, int*& ar,
    int& latters_left, int& fail) {
    if (latter_code == int(word.str[ind_of_latter]) 
        || latter_code + 32 == int(word.str[ind_of_latter])
        || latter_code - 32 == int(word.str[ind_of_latter])) { // если коды символов похожи
        input.X = ind_of_latter + 1;
        input.Y = 1;
        SetConsoleCursorPosition(h, input);
        cout << word.str[ind_of_latter]; // запись этого символа прямо на его месте
        Effect(h, input, int(Colors::LIGHT_RED), int(Colors::GREEN), "RIGHT:)"); // функция создания эффекта
        ind_of_latter = RandomLatter(word, ar); // запуск выбора рандомного числа по которому находится символ в строке
        latters_left--; // уменьшение оставшихся букв
    }
    else {
        Effect(h, input, int(Colors::LIGHT_RED), int(Colors::GREEN), "WRONG:("); // функция создания эффекта
        // рисование виселици исходя из количества введённых символов начиная с координаты (18,1), жёлтым цветом
        // переменная fail увеличивается по выполнению одного условия с отрисовками
        COORD picture{ 18,1 };
        SetConsoleTextAttribute(h, int(Colors::DARK_YELLOW));
        if (word.length == 11) {
            if (fail == 0) {
                fail++;
                GallowPicture(h, picture, 8, 16);
            }
            else if (fail == 1) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 2);
            }
            else if (fail == 2) {
                fail++;
                HeadtPicture(h, picture, 26, 3);
            }
            else if (fail == 3) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 4);
            }
            else if (fail == 4) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 4);
            }
            else if (fail == 5) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 4);
            }
            else if (fail == 6) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 5);
            }
            else if (fail == 7) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 5);
            }
            else if (fail == 8) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 25, 6);
            }
            else if (fail == 9) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 27, 6);
            }
            else if (fail == 10) {
                fail++;
                Right_LeftFootPicture(h, picture, 24, 6);
                Right_LeftFootPicture(h, picture, 28, 6);
            }
        }
        else if (word.length == 10) {
            if (fail == 0) {
                fail++;
                GallowPicture(h, picture, 8, 16);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 2);
            }
            else if (fail == 1) {
                fail++;
                HeadtPicture(h, picture, 26, 3);
            }
            else if (fail == 2) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 4);
            }
            else if (fail == 3) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 4);
            }
            else if (fail == 4) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 4);
            }
            else if (fail == 5) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 5);
            }
            else if (fail == 6) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 5);
            }
            else if (fail == 7) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 25, 6);
            }
            else if (fail == 8) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 27, 6);
            }
            else if (fail == 9) {
                fail++;
                Right_LeftFootPicture(h, picture, 24, 6);
                Right_LeftFootPicture(h, picture, 28, 6);
            }
        }
        else if (word.length == 9) {
            if (fail == 0) {
                fail++;
                GallowPicture(h, picture, 8, 16);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 2);
                HeadtPicture(h, picture, 26, 3);
            }
            else if (fail == 1) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 4);
            }
            else if (fail == 2) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 4);
            }
            else if (fail == 3) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 4);
            }
            else if (fail == 4) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 5);
            }
            else if (fail == 5) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 5);
            }
            else if (fail == 6) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 25, 6);
            }
            else if (fail == 7) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 27, 6);
            }
            else if (fail == 8) {
                fail++;
                Right_LeftFootPicture(h, picture, 24, 6);
                Right_LeftFootPicture(h, picture, 28, 6);
            }
        }
        else if (word.length == 8) {
            if (fail == 0) {
                fail++;
                GallowPicture(h, picture, 8, 16);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 2);
            }
            else if (fail == 1) {
                fail++;
                HeadtPicture(h, picture, 26, 3);
            }
            else if (fail == 2) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 4);
            }
            else if (fail == 3) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 4);
            }
            else if (fail == 4) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 4);
            }
            else if (fail == 5) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 5);
            }
            else if (fail == 6) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 5);
            }
            else if (fail == 7) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 25, 6);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 27, 6);
                Right_LeftFootPicture(h, picture, 24, 6);
                Right_LeftFootPicture(h, picture, 28, 6);
            }
        }
        else if (word.length == 7) {
            if (fail == 0) {
                fail++;
                GallowPicture(h, picture, 8, 16);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 2);
                HeadtPicture(h, picture, 26, 3);
            }
            else if (fail == 1) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 4);
            }
            else if (fail == 2) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 4);
            }
            else if (fail == 3) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 4);
            }
            else if (fail == 4) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 5);
            }
            else if (fail == 5) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 5);
            }
            else if (fail == 6) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 25, 6);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 27, 6);
                Right_LeftFootPicture(h, picture, 24, 6);
                Right_LeftFootPicture(h, picture, 28, 6);
            }
        }
        else if (word.length == 6) {
            if (fail == 0) {
                fail++;
                GallowPicture(h, picture, 8, 16);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 2);
                HeadtPicture(h, picture, 26, 3);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 4);
            }
            else if (fail == 1) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 4);
            }
            else if (fail == 2) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 4);
            }
            else if (fail == 3) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 5);
            }
            else if (fail == 4) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 5);
            }
            else if (fail == 5) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 25, 6);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 27, 6);
                Right_LeftFootPicture(h, picture, 24, 6);
                Right_LeftFootPicture(h, picture, 28, 6);
            }
        }
        else if (word.length == 5) {
            if (fail == 0) {
                fail++;
                GallowPicture(h, picture, 8, 16);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 2);
                HeadtPicture(h, picture, 26, 3);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 4);
            }
            else if (fail == 1) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 4);
                LeftArm_LegPicture(h, picture, 27, 4);
            }
            else if (fail == 2) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 5);
            }
            else if (fail == 3) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 5);
            }
            else if (fail == 4) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 25, 6);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 27, 6);
                Right_LeftFootPicture(h, picture, 24, 6);
                Right_LeftFootPicture(h, picture, 28, 6);
            }
        }
        else if (word.length == 4) {
            if (fail == 0) {
                fail++;
                GallowPicture(h, picture, 8, 16);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 2);
                HeadtPicture(h, picture, 26, 3);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 4);
            }
            else if (fail == 1) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 4);
                LeftArm_LegPicture(h, picture, 27, 4);
            }
            else if (fail == 2) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 5);
                LeftArm_LegPicture(h, picture, 27, 5);
            }
            else if (fail == 3) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 25, 6);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 27, 6);
                Right_LeftFootPicture(h, picture, 24, 6);
                Right_LeftFootPicture(h, picture, 28, 6);
            }
        }
        else if (word.length == 3) {
            if (fail == 0) {
                fail++;
                GallowPicture(h, picture, 8, 16);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 2);
                HeadtPicture(h, picture, 26, 3);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 4);
            }
            else if (fail == 1) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 4);
                LeftArm_LegPicture(h, picture, 27, 4);
                RightArm_LegPicture(h, picture, 25, 5);
                LeftArm_LegPicture(h, picture, 27, 5);
            }
            else if (fail == 2) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 25, 6);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 27, 6);
                Right_LeftFootPicture(h, picture, 24, 6);
                Right_LeftFootPicture(h, picture, 28, 6);
            }
        }
        else if (word.length == 2) {
            if (fail == 0) {
                fail++;
                GallowPicture(h, picture, 8, 16);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 2);
                HeadtPicture(h, picture, 26, 3);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 4);
                RightArm_LegPicture(h, picture, 25, 4);
                LeftArm_LegPicture(h, picture, 27, 4);
                RightArm_LegPicture(h, picture, 25, 5);
                LeftArm_LegPicture(h, picture, 27, 5);
            }
            else if (fail == 1) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 25, 6);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 27, 6);
                Right_LeftFootPicture(h, picture, 24, 6);
                Right_LeftFootPicture(h, picture, 28, 6);
            }
        }
        else if (word.length == 1) {
            if (fail == 0) {
                fail++;
                GallowPicture(h, picture, 8, 16);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 2);
                HeadtPicture(h, picture, 26, 3);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 4);
                RightArm_LegPicture(h, picture, 25, 4);
                LeftArm_LegPicture(h, picture, 27, 4);
                RightArm_LegPicture(h, picture, 25, 5);
                LeftArm_LegPicture(h, picture, 27, 5);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 25, 6);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 27, 6);
                Right_LeftFootPicture(h, picture, 24, 6);
                Right_LeftFootPicture(h, picture, 28, 6);
            }
        }
    }
}

// функция создание эффекта
void Effect(const HANDLE& h, COORD& input, int color, int color2, string str) {
    input.X = 1;
    input.Y = 5;
    for (int i = 0; i < 6; i++) { // функция будет писать опредлённый текст разными цветами в координатах (1,5)
        if (i % 2 == 0) // если итерация чётная цвет один
            SetConsoleTextAttribute(h, color);
        else
            SetConsoleTextAttribute(h, color2); // иначе другой
        SetConsoleCursorPosition(h, input);
        cout << str; // пишим текст
        Sleep(200); // ждём 200 сек
    }
    Sleep(100);
    SetConsoleCursorPosition(h, input);
    cout << "       "; // в конце по тем же координатам пишим эти пробелы
}

// функция проверки на конец игры
void CheckForFinish(const Word& word, int latters_left, int& fail) {
    if (fail == word.length) { // если игрок полностью показал картинку(количество фейлов равно количеству всех введённых символов
        MusikGameOver(); // играет пищалка
        ForLoose(); // сообщение о проигрыше
    }
    if (latters_left == 0) { // если не осталось ни одно не угаданой буквы
        MusikWin(); // играет пищалка
        GuessedAllLatters(); // сообщение о выйгрыше
    }
}

// сообщение о проигрыше
void ForLoose() {
    int message = MessageBoxA(0, "You haven't guessed all latters. Do you wnat to play again?", "You loos", MB_YESNO);
    if (message == IDYES)
        main(); // если ответ "да" то назад в main
    else
        Exit(); // если нет то на выход
}

void GuessedAllLatters() {
    int message = MessageBoxA(0, "You have guessed all latters. Do you wnat to play again?", "You win!!!", MB_YESNO);
    if (message == IDYES)
        main(); // если ответ "да" то назад в main
    else
        Exit(); // если нет то на выход
}

// функция для пищалки
void MusikGameOver() { // превое число обозначает https://studfile.net/preview/600434/page:10/ второе чило обозначает частоту звучания чем выше тем звонце, чем ниже тем басистее
    Beep(587, 500); 
    Beep(523, 500);
    Beep(494, 500);
    for (int i = 0; i < 5; i++)
        Beep(466, 100);
}

void MusikWin() {
    Beep(494, 500);
    for (int i = 0; i < 2; i++)
        Beep(523, 100);
    Beep(523, 100);
    Beep(880, 500);
}

// печать самой виселици
void GallowPicture(const HANDLE& h, COORD& picture, int hight, int width) {
    for (int i = 0; i < hight; i++) {
        SetConsoleCursorPosition(h, picture);
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == 1 || i == hight - 1 || i == 0 && j < 9) // значения равны таким показателям рисуем виселицу
                cout << char(219);
        }
        picture.Y++; // увеличисваем координату у
    }
}

// печать каната, корпуса человека, правой ноги, левой ноги
// печать не циклом т.к. это единичны элемент, его достаточно поставить по определённым координатам
void Kanat_Body_RightLeg_LeftLegPicture(const HANDLE& h, COORD& picture, int x, int y) {
    picture.X = x;
    picture.Y = y;
    SetConsoleCursorPosition(h, picture);
    cout << "|";
}

// печать головы
// печать не циклом т.к. это единичны элемент, его достаточно поставить по определённым координатам
void HeadtPicture(const HANDLE& h, COORD& picture, int x, int y) {
    picture.X = x;
    picture.Y = y;
    SetConsoleCursorPosition(h, picture);
    cout << char(2);
}

// печать левой руки и првой руки
// печать не циклом т.к. это единичны элемент, его достаточно поставить по определённым координатам
void LeftArm_LegPicture(const HANDLE& h, COORD& picture, int x, int y) {
    picture.X = x;
    picture.Y = y;
    SetConsoleCursorPosition(h, picture);
    cout << "\\";
}

// печать левого бедра и првого бедра
// печать не циклом т.к. это единичны элемент, его достаточно поставить по определённым координатам
void RightArm_LegPicture(const HANDLE& h, COORD& picture, int x, int y) {
    picture.X = x;
    picture.Y = y;
    SetConsoleCursorPosition(h, picture);
    cout << "/";
}

// песать ступней
// печать не циклом т.к. это единичны элемент, его достаточно поставить по определённым координатам
void Right_LeftFootPicture(const HANDLE& h, COORD& picture, int x, int y) {
    picture.X = x;
    picture.Y = y;
    SetConsoleCursorPosition(h, picture);
    cout << "_";
}
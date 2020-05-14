// подключение нужных для работы библиотек
#include<iostream> // для организации ввода вывода
#include<Windows.h> // для структур HANDLE(взяти дискиптора(номера)окна консоли), HWND(взяти дискиптора(номера)окна консоли для мыши), COORD(Возможность упрвления координатами)
#include<ctime> // для рандомных чисел, отсчёт времени от 1983 года (дата появления с++)
#include<conio.h> // для функции _getch() (ввод с клавиатуры)
#include<direct.h>
using namespace std;

// создание перечесления
enum class Colors { GREEN = 10, RED = 4, PINK = 13, LIGHT_RED = 12, DARK_YELLOW = 6 };

// создание структуры слово состоящего из длинны и массива символов
struct Word {
    int length;
    char* str = new char[length];
};

// создание прототипов функций для тошо чтобы можно было обращаться к функции из любого места кода 
void Setings(const HANDLE& h, const HWND& hwnd);
void MenuGreenText(const HANDLE& h, int x, int y, int color);
void MenuEvent(HANDLE& h, Word& word, bool exit, int color, int color2);
void MenuRedText(const HANDLE& h, string str, int x, int y, int color);
int main();
void Exit();
void Loading(const HANDLE& h, int color);
void CreateWord(Word& word);
void Frame(const HANDLE& h, const Word& word, int hight, int width);
void GameplayPrint(const HANDLE& h, const Word& word, int width);
void CountLetters(Word& word);
void GamePlay(const HANDLE& h, const Word& word, int enter, int color, int color2, int color3);
int RandomLatter(const Word& word, int*& ar);
int Input();
void Check(const HANDLE& h, COORD& input, const Word& word, int latter_code, int& ind_of_latter, int*& ar,
    int& latters_left, int& fail);
void Effect(const HANDLE& h, COORD& input, int color, int color2, string str);
void CheckForFinish(const Word& word, int latters_left, int& fail);
void MusikWin();
void GallowPicture(const HANDLE& h, COORD& picture, int hight, int width);
void Kanat_Body_RightLeg_LeftLegPicture(const HANDLE& h, COORD& picture, int x, int y);
void HeadtPicture(const HANDLE& h, COORD& picture, int x, int y);
void LeftArm_LegPicture(const HANDLE& h, COORD& picture, int x, int y);
void RightArm_LegPicture(const HANDLE& h, COORD& picture, int x, int y);
void Right_LeftFootPicture(const HANDLE& h, COORD& picture, int x, int y);
void MusikGameOver();
void GuessedAllLatters();
void ForLoose();
void CreatePapka();
void FillWordsTxt();
void FillHintsTxt();
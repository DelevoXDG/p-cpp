#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;
using std::string;

// Prosze napisac program, ktory bedzie pobieral od uzytkownika n nazwisk i umieszczal je w tablicy o rozmiarze n, gdzie n to ustalona stala. 
// Nazwiska maja byc roznej dlugosci, a po zakonczeniu wypelniania tablicy nie moga zajmowac wiecej miejsca niz liczba znakow w nich + 1.
// W jednym rozwiazaniu prosze skorzystac z klasy string, a w drugim z napisow w stylu jezyka C.

void string_style()
{
    //Klasa string
    const int n = 4;
    string surnames[n];
    int i = 0;
    while (++i < n) {
        cin >> surnames[i];
    }

    //display
    i = 0;
    while (++i < n) {
        cout << surnames[i] << " " << surnames[i].length() << endl;
    }
}

void c_style()
{
    //Napisy w stylu jezyka C
    const int n = 4;
    char** surnames;
    surnames = new char* [n];
    string current;

    //read and store
    for (int i = 0; i < n; i++)
    {
        cin >> current;
        //cout << current.length() << endl;
        *(surnames + i) = new char[current.length() + 1];
        strcpy(*(surnames + i), current.c_str());
    }
    //display
    for (int i = 0; i < n; i++) {
        cout << surnames[i] << " " << strlen(surnames[i]) << endl;
    }
    //clean
    for (int i = 0; i < n; i++) {
        delete[](surnames[i]);
    }
    delete[] surnames;
}



int main() {


    string_style();
    c_style();

    return 0;
}
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;
using std::string;

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
    c_style();
    return 0;
}


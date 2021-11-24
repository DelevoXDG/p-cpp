#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;
using std::string;

void string_style()
{
    //Klasa string
    const int n = 4;
    string surnames[n];
    string tmp;
    int i = 0;
    while (i < n) {
        cin >> tmp;
        surnames[i] = tmp;
        i++;
    }

    //display
    i = 0;
    while (i < n) {
        cout << surnames[i] << " " << surnames[i].length() << endl;
        i++;
    }
}

int main() {
    string_style();
    return 0;
}
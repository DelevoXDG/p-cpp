// Maksim Zdobnikau
// Operacje tablicowe

// baca submit -f file.cpp -t 8 -l "C++ z obsluga plikow"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int* Reverse(int* ptr)
{

    return ptr;
}

int main()
{


    int pendingRounds = 0;
    cin >> pendingRounds;
    char selection = ' ';
    while (pendingRounds > 0)
    {
        int n = 0;
        cin >> n;
        int array[n];
        int* ptr = array;

        while (selection != 'F')
        {
            cin >> selection;
            switch (selection)
            {
            case 'R': //Note Reverse
            {
                break;
            }
            case 'C': //Note Move
            {
                break;
            }
            case 'S': //Note Swap
            {
                break;
            }
            case 'F': //Note Exit
            {
                break;
            }
            case 'T': //Temp
            {
                int i = 0;
                while (i < n)
                {
                    cout << array[i] << " ";
                }
                cout << endl;
                break;
            }
            }
        }

        pendingRounds--;
    }


    return 0;

}
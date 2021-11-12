// Maksim Zdobnikau
// https://baca.ii.uj.edu.pl/p12021/
// baca submit -f file.cpp -t 8 -l "C++ z obsluga plikow"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                for (int m = 0; m < 4; m++)
                {
                    for (int i1 = 0; i1 < 4; i1++)
                    {
                        for (int j1 = 0; j1 < 4; j1++)
                        {
                            for (int k1 = 0; k1 < 4; k1++)
                            {
                                for (int m1 = 0; m1 < 4; m1++)
                                {
                                    cout << "a " << i + 1 << " " << j + 1 << " " << k + 1 << " " << m + 1 << " b " << i1 + 1 << " " << j1 + 1 << " " << k1 + 1 << " " << m1 + 1 << endl;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}
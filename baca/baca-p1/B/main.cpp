// Maksim Zdobnikau
// Operacje tablicowe

#include <iostream>
using std::cin; using std::cout; using std::endl;

int main()
{
    int pendingRounds = 0;
    cin >> pendingRounds;
    char selection = ' ';

    while (pendingRounds > 0)
    {
        //SECTION INPUT
        int n = 0;
        cin >> n;
        int currentArray[n];
        int* array = currentArray;
        int iter = 0;
        int first = 0;
        int count = 0;
        int i = 0;

        while (iter < n)
        {
            cin >> array[iter];
            iter++;
        }
        //SECTION Display Array
        first = 0; count = 0; i = 0;
        i = first % n;

        while (count < n) {
            i = i % n;
            cout << array[i] << " ";
            i++; count++;
        }
        cout << endl;

        //SECTION Select Action
        selection = ' ';
        while (selection != 'F')
        {
            cin >> selection;

            if (selection == 'R')
            {
                //SECTION REVERSE
                int first = 0;

                int fragmentLength = 0;
                int gcd = 0;
                int unmoved = n;
                int shift = 0;

                cin >> first;
                cin >> fragmentLength;

                iter = (first % n + n) % n;

                while ((fragmentLength <= unmoved) && fragmentLength > 0)
                {
                    iter = iter % n;

                    int count = fragmentLength / 2;
                    int i = 0, j = i + fragmentLength - 1;

                    while (i < j) {
                        int acti = ((iter + i) % n + n) % n;
                        int actj = ((iter + j) % n + n) % n;

                        int temp = array[acti];
                        array[acti] = array[actj];
                        array[actj] = temp;
                        i++; j--;
                    }

                    unmoved -= fragmentLength;
                    iter += fragmentLength;
                }
                iter = (first % n + n) % n;

            } else if (selection == 'C')
            {
                //SECTION SHIFT 
                int first = 0;

                int fragmentLength = 0;
                int gcd = 0;
                int unmoved = n;
                int shift = 0;
                int inshift = 0; //Backup of initial shift

                cin >> first;
                cin >> fragmentLength;
                cin >> inshift;

                if (fragmentLength) {

                    if (inshift >= 0)
                        shift = fragmentLength - inshift % fragmentLength; //Note Shift right
                    else
                        shift = (-inshift) % fragmentLength; //Note Shift Left
                    iter = (first % n + n) % n;
                    while (unmoved > 0)
                    {
                        iter = iter % n;


                        if (unmoved < fragmentLength)
                        {
                            fragmentLength = unmoved;
                            if (inshift >= 0)
                                shift = fragmentLength - inshift % fragmentLength; //Note Shift right
                            else
                                shift = (-inshift) % fragmentLength; //Note Shift Left
                        }

                        int number = fragmentLength;
                        int divisor = shift;
                        if (shift != 0) {
                            while ((number % divisor) > 0) {
                                int R = number % divisor;
                                number = divisor;
                                divisor = R;
                            }
                        }
                        gcd = divisor;
                        int i = 0;
                        int j = 0;
                        while (i < gcd && shift != 0)
                        {


                            int tmp = array[(iter + i) % n];
                            j = i;
                            int dest = 0;
                            do
                            {
                                dest = (j + shift) % fragmentLength;

                                array[(iter + j) % n] = array[(iter + dest) % n]; unmoved--;
                                if (dest != i) j = dest;
                            } while (dest != i);
                            array[(j + iter) % n] = tmp;

                            i++;

                        }
                        if (shift == 0) unmoved -= fragmentLength;
                        iter += fragmentLength;
                    }
                }
            } else if (selection == 'S')
            {
                //SECTION SWAP 

                int first = 0;
                int count = 0;
                int fragmentLength = 0;
                int unmoved = n;

                cin >> first;
                cin >> fragmentLength;

                int i = 0;
                int j = 0;
                i = (first % n + n) % n;
                int dest = 0;
                if (fragmentLength)
                {
                    while ((unmoved - (2 * fragmentLength)) >= 0)
                    {
                        i = i % n;
                        j = 0; count = 0;

                        j = (i + j) % n;
                        while (count < fragmentLength)
                        {
                            j = j % n;
                            dest = (j + fragmentLength) % n;

                            int tmp = 0;
                            tmp = array[j];
                            array[j] = array[dest];
                            array[dest] = tmp;

                            j++; unmoved -= 2; count++;
                        }
                        i += 2 * fragmentLength;
                    }
                }
            }
        }
        //SECTION DISPLAY AGAIN 
        first = 0; count = 0; i = 0;
        i = first % n;

        while (count < n) {
            i = i % n;
            cout << array[i] << " ";
            i++; count++;
        }
        cout << endl;
        pendingRounds--;

    }
    return 0;
}
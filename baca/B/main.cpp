// Maksim Zdobnikau
// Operacje tablicowe

// baca submit -f file.cpp -t 8 -l "C++ z obsluga plikow"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    //SECTION INIT VARIABLES
    int pendingRounds = 0;
    cin >> pendingRounds;
    char selection = ' ';

    while (pendingRounds > 0)
    {
        //SECTION ARRAY SET UP
        int n = 0;
        cin >> n;
        int currentArray[n];
        int* array = currentArray;
        int iter = 0;
        int first = 0; // First Elemet
        int count = 0; // Makes sure we cycle once through the loop
        int i = 0;
        //Get Array
        while (iter < n)
        {
            cin >> array[iter];
            iter++;
        }

        //SECTION Display Array
        //TODO CANT BE ZERO!!!!
        first = 0; count = 0; i = 0; //Reset first, count that exits loop, and iterator
        i = first % n; //Set iterator to "actual" index

        while (count < n) {
            i = i % n; // Set iterator to "actual" index
            cout << array[i] << " ";
            i++; count++;
        }
        cout << endl;


        //SECTION Select Action
        selection = ' ';
        while (selection != 'F')
        {
            //selection = ' ';
            cin >> selection;

            if (selection == 'R')
            {
                //SECTION REVERSE
                int first = 0; // First Elemet

                int fragmentLength = 0; // Fragment length used in operation
                int gcd = 0; // Sets left to move
                int unmoved = n;
                int shift = 0; //Number of positions to be moved

                cin >> first;
                cin >> fragmentLength;

                iter = (first % n + n) % n; //Note Have to make sure we take care of negative first
                int dest = 0;

                while ((fragmentLength <= unmoved) && fragmentLength > 0)
                {
                    iter = iter % n;


                    // int start = iter, end = iter + fragmentLength;
                    int count = fragmentLength / 2;
                    int i = 0, j = i + fragmentLength - 1;

                    while (count--) {


                        // int acti = ((i % fragmentLength) % n + n) % n;
                        // int actj = ((i % fragmentLength) % n + n) % n;
                        int acti = ((iter + i) % n + n) % n;
                        int actj = ((iter + j) % n + n) % n;

                        int temp = array[acti];
                        array[acti] = array[actj];
                        array[actj] = temp;

                        // Update the i and j
                        i++; j--;

                        // If end equals to -1
                        // set end = N-1
                    }

                    unmoved -= fragmentLength;
                    iter += fragmentLength;
                }



                iter = (first % n + n) % n; //Note Have to make sure we take care of negative "first"

            }
            else if (selection == 'C')
            {
                //SECTION SHIFT 

                int first = 0; // First Elemet

                int fragmentLength = 0; // Fragment length used in operation
                int gcd = 0; // Sets left to move
                int unmoved = n;
                int shift = 0; //Number of positions to be moved
                int inshift = 0; //Backup of initial shift

                cin >> first;
                cin >> fragmentLength;
                cin >> inshift;

                if (fragmentLength) {

                    if (inshift >= 0)
                        shift = fragmentLength - inshift % fragmentLength; //Note Shift right
                    else
                        shift = (-inshift) % fragmentLength; //Note Shift Left




                    iter = (first % n + n) % n; //Note Have to make sure we take care of negative "first"
                    while (unmoved > 0)// Less than number of fragments
                    {
                        iter = iter % n; //current element in loop 0


                        if (unmoved < fragmentLength)
                        {
                            fragmentLength = unmoved;
                            if (inshift >= 0)
                                shift = fragmentLength - inshift % fragmentLength; //Note Shift right
                            else
                                shift = (-inshift) % fragmentLength; //Note Shift Left
                        }
                        int number = fragmentLength; int divisor = shift;
                        if (shift != 0) {
                            while ((number % divisor) > 0) {
                                int R = number % divisor; //a=b*k+r
                                number = divisor;
                                divisor = R;
                            }
                        }
                        gcd = divisor;
                        int i = 0; //pseudo sub-array in loop 1 (%shift)
                        int j = 0; //pseudo moving iterator in loop 2 (%shift)
                        //cout << "----------------------------------------------------------------" << endl;
                        while (i < gcd && shift != 0)
                        {


                            int tmp = array[(iter + i) % n];
                            j = i;
                            int dest = 0;
                            do
                            {
                                dest = (j + shift) % fragmentLength; //FIX

                                array[(iter + j) % n] = array[(iter + dest) % n]; unmoved--;
                                if (dest != i) j = dest;
                            } while (dest != i);
                            array[(j + iter) % n] = tmp;
                            //tmp TEST

                            //cout << endl;
                            //!tmp test
                            i++;

                        }
                        if (shift == 0) unmoved -= fragmentLength;
                        //gcd += fragmentLength;
                        //fragments--;
                        iter += fragmentLength;
                    }
                }




            }
            else if (selection == 'S')
            {
                //SECTION SWAP 

                int first = 0; // First Elemet
                int count = 0; // Makes sure we cycle once through the loop 2
                int fragmentLength = 0; // Fragment length used in operation 
                int unmoved = n; // Elements left to move

                cin >> first;
                cin >> fragmentLength;

                int i = 0; //Current Element
                int j = 0; //Iterator to swap all elements at given [i]
                i = (first % n + n) % n; //Note Have to make sure we take care of negative first
                int dest = 0;

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
            else if (selection == 'T')
            {
                //arrDisplay(ptr, n);

            }
        }
        //SECTION DISPLAY AGAIN 
        first = 0; count = 0; i = 0; //Reset first, count that exits loop, and iterator
        i = first % n; //Set iterator to "actual" index

        while (count < n) {
            i = i % n; // Set iterator to "actual" index
            cout << array[i] << " ";
            i++; count++;
        }

        pendingRounds--;

    }


    return 0;

}
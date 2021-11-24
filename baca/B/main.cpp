// Maksim Zdobnikau
// Operacje tablicowe

// baca submit -f file.cpp -t 8 -l "C++ z obsluga plikow"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;

void swap(int* ptr1, int* ptr2)
{
    int tmp = 0;
    tmp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = tmp;
}

void arrDisplay(int* ptr, int arraySize)
{
    //TODO DISABLE
    int* array = ptr; // Passing array
    int n = arraySize; // Passing array size

    int first = 0; // First Elemet
    int count = 0; // Makes sure we cycle once through the loop
    int i = 0;
    i = first % n;
    while (count < n)
    {
        i = i % n; // Converted to "actual" index
        cout << array[i] << " ";
        i++;
        count++;
    }
    cout << endl;
}

void arrSwap(int* ptr, int arraySize)
{
    int* array = ptr; // Passing array
    int n = arraySize; // Passing array size
    int first = 0; // First Elemet
    int count = 0; // Makes sure we cycle once through the loop 2
    int fragmentLength = 0; // Fragment length used in operation 
    int unmoved = n; // Elements left to move

    cin >> first;
    cin >> fragmentLength;

    int i = 0; //Current Element
    int j = 0; //Iterator to swap all elements at given [i]
    i = (first % n + n) % n;
    int destination = 0;
    //net

    while ((unmoved - (2 * fragmentLength)) >= 0)
    {
        i = i % n;
        j = 0;
        count = 0;
        //cout << "loop 0" << endl;

        j = (i + j) % n;
        while (count < fragmentLength)
        {

            j = j % n;
            destination = (j + fragmentLength) % n;
            //cout << "[" << j + 1 << "] " << array[j] << " [" << destination + 1 << "] " << array[destination] << endl;
            //cout << "swapped: " << endl;
            swap(&array[j], &array[destination]);
            //cout << "[" << j + 1 << "] " << array[j] << " [" << destination + 1 << "] " << array[destination] << endl;
            //cout << "----------------------------------------------------" << endl;
            j++;
            unmoved -= 2;
            count++;
        }
        i += 2 * fragmentLength;
    }


}



int* arrReverse(int* ptr, int arraySize)
{
    return ptr;
}




int main()
{
    //SECTION INIT VARIABLES
    //FIXME FUNCTIONS ARE NOT ALLOWED
    int pendingRounds = 0;
    cin >> pendingRounds;
    char selection = ' ';

    while (pendingRounds > 0)
    {
        //SECTION ARRAY SET UP
        int n = 0;
        cin >> n;
        int currentArray[n] = {};
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

        first = 0; count = 0; i = 0; //Reset first, count that breaks loop, and iterator
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

            }
            else if (selection == 'C')
            {
                //SECTION MOVE  
                //Note

                // input: R a b c
                // Операция в каждом фрагменте длины b и заданном индексе
                // первого элемента а переносит элементы на желамое количестве позиций
                //



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
                int destination = 0;

                while ((unmoved - (2 * fragmentLength)) >= 0)
                {
                    i = i % n;
                    j = 0; count = 0;

                    j = (i + j) % n;
                    while (count < fragmentLength)
                    {
                        j = j % n;
                        destination = (j + fragmentLength) % n;

                        int tmp = 0;
                        tmp = array[j];
                        array[j] = array[destination];
                        array[destination] = tmp;

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
        first = 0; count = 0; i = 0; //Reset first, count that breaks loop, and iterator
        i = first % n; //Set iterator to "actual" index

        while (count < n) {
            i = i % n; // Set iterator to "actual" index
            cout << array[i] << " ";
            i++; count++;
        }
        cout << endl;

        pendingRounds--;

    }


    return 0;

}
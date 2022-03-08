#include <iostream>
#include <ctime>
using std::cin;
using std::cout;
using std::endl;
using std::string;

//Zadanie wskazniki
//Prosze napisac funkcje, ktora bedzie wypisywac tablice dwuwymiarowa za pomoca petli for (wersja z int), za pomoca while (wersja z float).
//Poszczegolne elementy maja byc wypisywane za pomoca indes [ ] (wersja z int), oraz za pomoca arytmetyki wskanikow (wersja z float).


void arrDisplay(int** arr, int arrSizeX, int arrSizeY)
{
	for (int i = 0; i < arrSizeX; i++)
	{
		for (int j = 0;j < arrSizeY;j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

void arrDisplay(float** arr, int arrSizeX, int arrSizeY)
{
	int i = 0;
	while (i < arrSizeX)
	{
		int j = 0;
		while (j < arrSizeY) {
			//cout << *(*(arr + i) + j) << " ";
			cout << *(arr[i] + j) << " ";
			j++;
		}
		cout << endl;
		i++;
	}
}

//dla sprawdzenia

int randNum(int min, int max)
{
	int random = rand();
	int range = max - min;
	int result = min + (random % range);
	return result;
}

float randNum(float min, float max)
{
	float random = (float(rand()) / float((RAND_MAX)));
	float range = max - min;
	float result = min + (random * range);
	result = (int)(result * 100) / 100.0f;
	return result;
}

void arrFill(int** arr, int arrSizeX, int arrSizeY)
{
	for (int i = 0; i < arrSizeX; i++) {
		for (int j = 0; j < arrSizeY; j++)
		{
			arr[i][j] = randNum(0, 9);
		}
	}
}

void arrFill(float** arr, int arrSizeX, int arrSizeY)
{
	int i = 0;
	while (i < arrSizeX) {
		int j = 0;
		while (j < arrSizeY)
		{
			arr[i][j] = randNum(0.0f, 9.0f);
			j++;
		}
		i++;
	}
}

int main()
{
	srand(time(0));

	const int n = 5;
	//standard 
	int** intArray;
	intArray = new int* [n];

	for (int i = 0; i < n; i++) {
		intArray[i] = new int[n];
	}


	float** floatArray = new float* [n];
	for (int i = 0; i < n; i++) {
		floatArray[i] = new float[n];
	}


	//fill and display
	arrFill(intArray, n, n);
	cout << endl;
	arrFill(floatArray, n, n);
	cout << endl;

	arrDisplay(intArray, n, n);
	cout << endl;
	arrDisplay(floatArray, n, n);
}

//Maksim Zdobnikau

#include <iostream>
#include <stdlib.h>
//#include "header.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char* argv[])
{
	const int lim = 1000;
	string str = "";
	/*int max = atoi(argv[1]);
	int N = atoi(argv[2]);*/
	int N = 0;
	float max = 0, min = 0, suma = 0, current = 0;
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		max = 0; min = 0; suma = 0; current = 0;
		for (int j = 0; j < 5; j++)
		{
			cin >> current;
			if ((current > max) || (j == 0))
			{
				max = current;
			}
			if ((current < min) || (j == 0))
			{
				min = current;
			}
			suma += current;
		}
		cout << min;
		cout << ' ';
		cout << max;
		cout << ' ';
		cout << (suma / 5);
		cout << "\n";
		/*
		str += min;
		str += ' ';
		str += max;
		str += ' ';
		str += (suma / 5);
		str += "\n";*/
	}
	/*for (int i = 0; i < N; i++)
	{
		cout << str;
	}*/


	return 0;
}

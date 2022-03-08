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

	/*int max = atoi(argv[1]);
	int N = atoi(argv[2]);*/
	int max = 0, N = 0;
	cin >> max;
	cin >> N;

	//printf("N = %d, max = %d\n", N, max);
	int current = 0;
	for (int i = 0; i < N; i++)
	{
		cin >> current;
		if (max % current == 0)
		{
			cout << "TAK" << endl;
		}
		else
			cout << "NIE" << endl;
	}

	return 0;
}

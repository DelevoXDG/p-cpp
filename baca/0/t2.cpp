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
	int id[lim], cw[lim], baca[lim], fullmark[lim];
	/*int max = atoi(argv[1]);
	int N = atoi(argv[2]);*/
	int N = 0;

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> id[i];
		cin >> cw[i];
		cin >> baca[i];
	}

	for (int i = 0; i < N; i++)
	{
		fullmark[i] = cw[i] + baca[i];
		cout << id[i] << " " << fullmark[i] << "% ";
		if (fullmark[i] >= 90) cout << "bardzo dobry (5.0)";
		else if (fullmark[i] >= 80) cout << "dobry plus (4.5)";
		else if (fullmark[i] >= 70) cout << "dobry (4.0)";
		else if (fullmark[i] >= 60) cout << "dostateczny plus (3.5)";
		else if (fullmark[i] >= 50) cout << "dostateczny (3.0)";
		else if (fullmark[i] < 50) cout << "niedostateczny (2.0)";
		cout << endl;
	}

	return 0;
}

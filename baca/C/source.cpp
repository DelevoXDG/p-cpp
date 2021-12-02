// Maksim Zdobnikau
// https://baca.ii.uj.edu.pl/p12021/
// baca submit --file source.cpp --rename source.cpp --task-id 7 --language "C++" --zip

//#include "PPZ.h"
#include <iostream>
using std::cin; using std::cout; using std::endl; using std::string;

//SECTION TODO
//TODO RemoveDuplicates
//TODO CREATE



//SECTION HELPER FUNCTIONS	
void BasicSort(int in[], int arrSize) {

	for (int i = 0; i < arrSize; ++i)
	{
		for (int j = i + 1; j < arrSize; ++j)
		{
			if (in[i] > in[j])
			{
				int tmp = 0;
				tmp = in[i];
				in[i] = in[j];
				in[j] = tmp;
			}
		}
	}
}

int RemoveDuplicatesSorted(int arr[], int arrSize)
{

	int i = 0;
	int j = 0;
	if (arrSize == 0) return 0;
	for (j = 1; j < arrSize; j++)
	{
		if (arr[j] != arr[i]) {
			arr[++i] = arr[j];
		}
	}
	return i + 1;
}
//SECTION MAIN FUNCTIONS
void Create(int n, int in[], int out[])
{
	int i = 0; int o = 0;
	while (i < n)
	{
		if (in[i] <= 4095 && in[i] >= 1)
		{
			out[o] = in[i];
			o++;
		}
		i++;
	}
	if (o > 1)
	{
		BasicSort(out, o);
		o = RemoveDuplicatesSorted(out, o);
	}
	out[o] = -1;


}

// /*
int main(int argc, const char** argv)
{


	char q, D[100];
	int n, m;
	int mini, maxi, card;
	double a, h;
	int A[20000], B[5000], C[5000];

	std::cin >> q;
	if (q == 'B') {//Create
		std::cin >> n;
		for (int i = 0; i < n; ++i)
			std::cin >> A[i];
		Create(n, A, B);
		for (int i = 0; i < n; ++i)
			std::cout << A[i] << " ";
		std::cout << "\n";
		int x = 0;
		while (*(B + x) != -1)
			std::cout << *(B + x++) << " ";
		std::cout << *(B + x);
	}
	return 0;
}
// */
















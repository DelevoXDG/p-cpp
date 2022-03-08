#include <iostream>
#include "source.cpp"
using std::cin; using std::cout; using std::endl; using std::string;

int size(int* A) {
	int i = 0;
	while (*(A + i) != -1)
		++i;
	return i;
}


int main(int argc, const char** argv)
{


	char q, D[100];
	int n, m;
	int mini, maxi, card;
	double a, h;
	int A[20000], B[5000], C[5000];
	/* code */

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
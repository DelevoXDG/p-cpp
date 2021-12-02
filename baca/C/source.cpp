// Maksim Zdobnikau

#include <iostream>
using std::cin; using std::cout; using std::endl; using std::string;

//SECTION TODO
//[X] RemoveDuplicates
//[X] CREATE
//[ ] Add
//[ ] Create
//[ ] Union
//[ ] Intersection
//[ ] Difference
//[ ] Symmetric
//[ ] Complement;
//[ ] Subset;
//[ ] Equal;
//[ ] Empty;
//[ ] Nonempty;
//[ ] Element;
//[ ] Arithmetic;
//[ ] Harmonic;
//[ ] MinMax;
//[ ] Cardinality


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

int size(int in[]) {
	int i = 0;
	while (in[i] != -1)
		++i;
	return i;
}


//SECTION MAIN FUNCTIONS
void Add(int num, int out[])
{
	int in[] = { num };
	int n = 0;
	bool isAddable = false;
	if (num >= 1 && num <= 4095)
	{
		isAddable = true;
	}
	while ((out[n] != -1))
	{
		if (out[n++] == num) isAddable = false;
	}
	if (isAddable) {
		out[n] = num;
		n++;
		out[n] = -1;
	}
	if (n > 1) BasicSort(out, n);

}

void Create(int n, int in[], int out[])
{
	int i = 0; int o = 0;
	while (i < n)
	{
		bool isDuplicate = false;
		for (int d = 0;d < o;d++)
		{
			if (in[i] == out[d])
				isDuplicate = true;
		}
		if (in[i] <= 4095 && in[i] >= 1 && !isDuplicate)
		{
			out[o] = in[i];
			o++;
		}
		i++;
	}
	if (o > 1)
	{
		BasicSort(out, o);
	}
	out[o] = -1;


}

/*
int main(int argc, const char** argv)
{


	char q, D[100];
	int n, m;
	int mini, maxi, card;
	double a, h;
	int A[20000], B[5000], C[5000];

	std::cin >> q;
	if (q == 'A') {//Add
		int x = 0;
		while (true) {
			std::cin >> *(A + x);
			if (*(A + x++) == -1)
				break;
		}
		std::cin >> m;
		std::cout << m << "\n";
		Add(m, A);
		x = 0;
		while (*(A + x) != -1)
			std::cout << *(A + x++) << " ";
		std::cout << *(A + x) << "\n";

	}//Add
	else
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
*/
















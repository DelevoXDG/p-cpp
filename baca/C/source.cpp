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
	int n = 0;
	while (in[n] != -1)
		n++;
	return n;
}

void AddNoSort(int num, int out[])
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
void Union(int* A, int* B, int* out)
{
	int sizeA = size(A);
	int sizeB = size(B);
	Create(sizeA, A, out);
	for (int i = 0; i < sizeB; i++)
		AddNoSort(B[i], out);
	int o = size(out);
	BasicSort(out, o);
}

void Intersection(int* A, int* B, int* out)
{
	int sizeA = size(A);
	int sizeB = size(B);
	for (int i = 0; i < sizeA; i++)
	{

	}

}











// Maksim Zdobnikau

#include <iostream>
using std::cin; using std::cout; using std::endl; using std::string;

//SECTION HELPER FUNCTIONS	
void BasicSort(int* in, int arrSize) {

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

int size(int* in) {
	int n = 0;
	while (in[n] != -1)
		n++;
	return n;
}

void AddNoSort(int num, int* out)
{
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

//SECTION REQUIRED FUNCTIONS
void Add(int num, int* out)
{

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

void Create(int n, int* in, int* out)
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

void Intersection(int* A, int* B, int* C)
{
	int sizeA = size(A);
	int sizeB = size(B);
	int sizeC = 0;
	for (int i = 0; i < sizeA; i++)
	{
		bool isDuplicate = false;
		bool doesInterect = false;
		if (A[i] <= 4095 && A[i] >= 1)
		{
			for (int d = 0;d < sizeC;d++)
			{
				if (A[i] == C[d]) isDuplicate = true;
			}
			if (!isDuplicate)
			{
				for (int j = 0; j < sizeB;j++)
					if (B[j] == A[i]) doesInterect = true;
			}
			if (!isDuplicate && doesInterect)
			{
				C[sizeC] = A[i];
				sizeC++;
			}
		}
	}

	if (sizeC > 1)
	{
		BasicSort(C, sizeC);
	}
	C[sizeC] = -1;
}

void Difference(int* A, int* B, int* C)
{
	int sizeA = size(A);
	int sizeB = size(B);
	int sizeC = 0;
	for (int i = 0; i < sizeA; i++)
	{
		bool isDuplicate = false;
		bool doesInterect = false;
		if (A[i] <= 4095 && A[i] >= 1)
		{
			for (int d = 0;d < sizeC;d++)
			{
				if (A[i] == C[d]) isDuplicate = true;
			}
			if (!isDuplicate)
			{
				for (int j = 0; j < sizeB;j++)
					if (B[j] == A[i]) doesInterect = true;
			}
			if (!isDuplicate && !doesInterect)
			{
				C[sizeC] = A[i];
				sizeC++;
			}
		}
	}
	if (sizeC > 1)
	{
		BasicSort(C, sizeC);
	}
	C[sizeC] = -1;
}

void Symmetric(int* A, int* B, int* C)
{
	int sizeA = size(A);
	int sizeB = size(B);
	int sizeC = 0;
	for (int i = 0; i < sizeA; i++)
	{
		bool isDuplicate = false;
		bool doesInterect = false;
		if (A[i] <= 4095 && A[i] >= 1)
		{
			for (int d = 0;d < sizeC;d++)
			{
				if (A[i] == C[d]) isDuplicate = true;
			}
			for (int j = 0; j < sizeB;j++)
				if (B[j] == A[i]) doesInterect = true;
			if (!isDuplicate && !doesInterect)
			{
				C[sizeC] = A[i];
				sizeC++;
			}
		}
	}
	for (int i = 0; i < sizeB; i++)
	{
		bool isDuplicate = false;
		bool doesInterect = false;
		if (B[i] <= 4095 && B[i] >= 1)
		{
			for (int d = 0;d < sizeC;d++)
			{
				if (B[i] == C[d]) isDuplicate = true;
			}
			for (int j = 0; j < sizeA;j++)
				if (A[j] == B[i]) doesInterect = true;
			if (!isDuplicate && !doesInterect)
			{
				C[sizeC] = B[i];
				sizeC++;
			}
		}
	}

	if (sizeC > 1)
	{
		BasicSort(C, sizeC);
	}
	C[sizeC] = -1;
}

void Complement(int* A, int* C)
{
	int sizeA = size(A);
	int sizeC = 0;
	for (int i = 1; i <= 4095; i++)
	{
		bool isDuplicate = false;
		bool doesInterect = false;
		for (int d = 0;d < sizeC;d++)
		{
			if (i == C[d]) isDuplicate = true;
		}
		if (!isDuplicate)
		{
			int j = 0;
			while (j < sizeA && !doesInterect)
			{
				if (i == A[j]) doesInterect = true;
				j++;
			}
		}
		if (!isDuplicate && !doesInterect)
		{
			C[sizeC] = i;
			sizeC++;
		}
	}
	if (sizeC > 1)
	{
		BasicSort(C, sizeC);
	}
	C[sizeC] = -1;
}

bool Subset(int* A, int* B)
{

	int sizeA = size(A);
	int sizeB = size(B);
	int i = 0;
	bool isElement = true;
	while (i < sizeA && isElement)
	{
		isElement = false;
		for (int j = 0; j < sizeB;j++)
			if (A[i] == B[j]) isElement = true;
		i++;
	}
	return isElement;
}

bool Equal(int* A, int* B)
{

	int sizeA = size(A);
	int sizeB = size(B);
	int i = 0;
	bool isElement = true;
	while (i < sizeA && isElement)
	{
		isElement = false;
		for (int j = 0; j < sizeB;j++)
			if (A[i] == B[j]) isElement = true;
		i++;
	}
	i = 0;
	while (i < sizeB && isElement)
	{
		isElement = false;
		for (int j = 0; j < sizeA;j++)
			if (B[i] == A[j]) isElement = true;
		i++;
	}
	return isElement;
}

bool Empty(int* A)
{
	if (A[0] == -1) return 1;
	else return 0;
}

bool Nonempty(int* A)
{
	return (!Empty(A));
}

bool Element(int num, int* A)
{
	int sizeA = size(A);
	bool isElement = false;
	for (int j = 0; j < sizeA;j++)
		if (num == A[j]) isElement = true;
	return isElement;
}

double Arithmetic(int* A)
{
	int sizeA = size(A);
	if (Empty(A))  return 0;
	double sum = 0;
	for (int i = 0; i < sizeA;i++)
		sum += A[i];
	return sum / (sizeA);
}

double Harmonic(int* A)
{
	double sizeA = 1.0 * size(A);
	if (Empty(A)) return 1;
	double sum = 0;
	for (int i = 0; i < sizeA;i++)
		sum += (1 / (A[i] * 1.0));
	return (sizeA / sum);
}

void MinMax(int* A, int* min, int& max)
{
	int sizeA = size(A);
	if (Nonempty(A)) {
		*min = A[0];
		max = A[0];

		for (int i = 0; i < sizeA; i++)
		{
			if (A[i] > max)
				max = A[i];
			if (A[i] < *min)
				*min = A[i];
		}
	}
}

void Cardinality(int* A, int* power)
{
	*power = size(A);
}

void Properties(int* A, char* args, double& arithmetic, double* harmonic, int& min, int* max, int& power)
{
	int n = 0;
	while (args[n] != '\0') {
		n++;
	}
	for (int i = 0; i < n; i++)
	{
		if (args[i] == 'a') arithmetic = Arithmetic(A);
		else if (args[i] == 'h') *harmonic = Harmonic(A);
		else if (args[i] == 'm') MinMax(A, &min, *max);
		else if (args[i] == 'c') Cardinality(A, &power);
	}
}
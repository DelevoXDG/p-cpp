// Maksim Zdobnikau

#include <iostream>
using std::cin; using std::cout; using std::endl;

//SECTION GLOBAL VARIABLES
const short int max_size = 32;
long long int cube[max_size][max_size][max_size];
short int N = 0;

//SECTION FUNCTIONS DECLARATIONS
int Power(const long long int a);
void Shapes(const char selection);
long long Determinant(const long long int matrix[][max_size], const short int size);
long long Laplace(const long long matrix[][max_size], const short int size);

//SECTION MAIN
int main()
{
	char select = 0;
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				cin >> cube[i][j][k];
			}
		}
	}

	while (select != 'E') {
		cin >> select;
		switch (select)
		{
			case 'E': //Note Exit
			{
				break;
			}
			case 'D':
			{
				//Note Determinant

				char dimSelect = 0;
				int id = 0;
				cin >> dimSelect;
				cin >> id;

				long long int matrix[max_size][max_size];
				switch (dimSelect) {
					case 'l': //Note Pion
					{
						for (int i = 0; i < N; i++) {
							for (int j = 0; j < N; j++) {
								matrix[i][j] = cube[i][id][j];
							}
						}
						break;
					}
					case 'v': //Note Poziom
					{
						for (int i = 0; i < N; i++) {
							for (int j = 0; j < N; j++) {
								matrix[i][j] = cube[i][j][id];
							}
						}
						break;
					}
					case 'p': //Note Panel
					{
						for (int i = 0; i < N; i++) {
							for (int j = 0; j < N; j++) {
								matrix[i][j] = cube[id][i][j];
							}
						}
						break;
					}
				}

				cout << Determinant(matrix, N) << endl;
				break;
			}
			default: //Note Shapes
			{
				Shapes(select);
				break;
			}
		}
	}

	return 0;
}
//SECTION FUNCTIONS
void Shapes(const char selection)
{
	short int l = 0;
	short int v = 0;
	short int p = 0;
	short int h = 0;
	short int w = 0;
	short int d = 0;
	short int r = 0;

	int poziom = 0;
	int pion = 0;
	int panel = 0;
	short int tmp = 0;
	long long int sum = 0;

	if (selection == 'C') //Note Cuboid
	{
		cin >> l;
		cin >> v;
		cin >> p;
		cin >> h;
		cin >> w;
		cin >> d;
	}
	else if (selection == 'T' || selection == 'O') //Note Pyramid or Octal
	{
		cin >> l;
		cin >> v;
		cin >> p;
		cin >> r;
		h = r;
		w = r;
		d = r;
	}

	poziom = l < (N / 2) ? l + h : l - h;
	pion = v < (N / 2) ? v + w : v - w;
	panel = p < (N / 2) ? p + d : p - d;

	if (l > poziom) {
		tmp = poziom;
		poziom = l;
		l = tmp;
	}
	if (v > pion) {
		tmp = pion;
		pion = v;
		v = tmp;
	}
	if (p > panel) {
		tmp = panel;
		panel = p;
		p = tmp;
	}

	for (int i = p; i <= panel; i++) {
		for (int j = l; j <= poziom; j++) {
			for (int k = v; k <= pion; k++) {
				if (i >= 0 && j >= 0 && k >= 0 && i < N && j < N && k < N)
				{
					if (selection == 'C') {
						sum += cube[i][j][k];
					}
					else if (selection == 'T' && ((i - p) + (j - l) + (k - v) <= r)) {
						sum += cube[i][j][k];
					}
					else if (selection == 'O' && (Power(i - p) + Power(j - l) + Power(k - v) <= Power(r))) {
						sum += cube[i][j][k];
					}
				}
			}
		}
	}
	cout << sum << endl;
}

long long Determinant(const long long int mat[][max_size], const short int size)
{
	long long int det = 0;
	bool currentlySame = true;
	for (int i = 1; i < size;i++) {
		for (int j = 0; j < size && currentlySame;j++) {
			if (mat[i - 1][j] != mat[i][j]) {
				currentlySame = false;
			}
		}
		if (currentlySame)
			return 0;

	}
	return Laplace(mat, size);
}

long long Laplace(const long long mat[][max_size], const short int size)
{
	long long int det = 0;
	if (size == 1)
		return mat[0][0];
	else if (size == 2)
		return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
	else {
		long long int sub_mat[max_size][max_size];
		short int sign = 1;
		short int shift = 0;
		for (int row = 0; row < size; row++) {
			if (mat[row][0]) {
				shift = 0;
				for (int i = 0; i < size; i++) {
					if (i == row) {
						shift = 1; continue;
					}
					for (int j = 1; j < size; j++)
					{
						sub_mat[i - shift][j - 1] = mat[i][j];
					}
				}
				det += sign * mat[row][0] * Laplace(sub_mat, size - 1);
			}
			sign = -sign;
		}
		return det;
	}
}

int Power(const long long int a) {
	return a * a;
}
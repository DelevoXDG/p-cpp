// Maksim Zdobnikau

#include <iostream>
using std::cin; using std::cout; using std::endl;

//SECTION GLOBAL VARIABLES
const short int max_size = 32;
long long int cube[max_size][max_size][max_size];
short int N = 0;
short int center = 0;

//SECTION FUNCTIONS DECLARATIONS
long long Determinant(const long long int matrix[][max_size], const int size);
long long Laplace(const long long matrix[][max_size], const int size);
void display_array(const long long matrix[][max_size], const int size);
long long int Cuboid(short int l, short int v, short int p, short int h, short int w, short int d);
long long int Cuboid(short int l, short int v, short int p, short int e);



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
			{ break; }
			case 'D':
			{
				//Note Determinant

				char dimSelect = 0; //Dimension
				int n = 0; //Index
				cin >> dimSelect;
				cin >> n;

				long long int matrix[max_size][max_size];
				switch (dimSelect) {
					case 'l': //Note Pion
					{
						for (int i = 0; i < N; i++) {
							for (int j = 0; j < N; j++) {
								matrix[i][j] = cube[i][n][j];
							}
						}
						break;
					}
					case 'v': //Note Poziom
					{
						for (int i = 0; i < N; i++) {
							for (int j = 0; j < N; j++) {
								matrix[i][j] = cube[i][j][n];
							}
						}
						break;
					}
					case 'p': //Note Panel
					{
						for (int i = 0; i < N; i++) {
							for (int j = 0; j < N; j++) {
								matrix[i][j] = cube[n][i][j];
							}
						}
						break;
					}
				}

				cout << Determinant(matrix, N) << endl;
				break;
			}
			default:
			{
				short int l = 0;
				short int v = 0;
				short int p = 0;
				short int h = 0;
				short int w = 0;
				short int d = 0;
				short int e = 0;
				short int r = 0;
				switch (select)
				{
					case 'C': //Note Cuboid
					{
						cin >> l;
						cin >> v;
						cin >> p;
						cin >> h;
						cin >> w;
						cin >> d;
						cout << Cuboid(l, v, p, h, w, d) << endl;
						break;
					}
					case 'T': //Note Pyramid
					{
						cin >> l;
						cin >> v;
						cin >> p;
						cin >> r;
					}
					break;
				}

			}
		}
	}

	return 0;
}
//SECTION FUNCTIONS
long long int Cuboid(short int l, short int v, short int p, short int h, short int w, short int d)
{
	int poziom = 0;
	int pion = 0;
	int panel = 0;
	long long int sum = 0;

	poziom = l < (N / 2) ? l + h : l - h;
	pion = v < (N / 2) ? v + w : v - w;
	panel = p < (N / 2) ? p + d : p - d;

	if (l > poziom) {
		int tmp = poziom;
		poziom = l;
		l = tmp;
	}
	if (v > pion) {
		int tmp = pion;
		pion = v;
		v = tmp;
	}
	if (p > panel)
	{
		int tmp = panel;
		panel = p;
		p = tmp;
	}

	for (int i = p; i <= panel; i++) {
		for (int j = l; j <= poziom; j++) {
			for (int k = v; k <= pion; k++) {
				if (i >= 0 && j >= 0 && k >= 0 && i < N && j < N && k < N) {
					sum += cube[i][j][k];
				}
			}
		}
	}
	return sum;
}

long long Determinant(const long long int mat[][max_size], const int size)
{
	long long int det = 0;
	bool isSame = false;
	bool currentlySame = true;
	for (int i = 1; i < size && !isSame;i++) {
		for (int j = 0; j < size && !isSame && currentlySame;j++) {
			if (mat[i - 1][j] != mat[i][j]) {
				currentlySame = false;
			}
		}
		if (currentlySame) isSame = true;
	}
	if (isSame) return 0;
	else return Laplace(mat, size);
}

long long Laplace(const long long mat[][max_size], const int size)
{
	long long int det = 0;
	if (size == 1)
		return mat[0][0];
	else if (size == 2)
		return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
	else {
		long long sub_mat[max_size][max_size];
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

void display_array(const long long mat[][max_size], const int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
}


// Maksim Zdobnikau

#include <iostream>
using std::cin; using std::cout; using std::endl;

//SECTION GLOBAL VARIABLES
const short int max_size = 32;
long long int cube[max_size][max_size][max_size];
short int N = 0;
short int center = 0;

//SECTION FUNCTIONS DECLARATIONS
long long Laplace(long long matrix[][max_size], int size);
void display_array(long long matrix[][max_size], int size);

//SECTION MAIN
int main()
{
	char select = 0;

	short int l = 0;
	short int v = 0;
	short int p = 0;
	short int h = 0;
	short int w = 0;
	short int d = 0;

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
								matrix[j][i] = cube[i][n][j];
							}
						}
						break;
					}
					case 'v': //Note poziom
					{
						for (int i = 0; i < N; i++) {
							for (int j = 0; j < N; j++) {
								matrix[j][i] = cube[i][j][n];
							}
						}
						break;
					}
					case 'p': //Note panel
					{
						for (int i = 0; i < N; i++) {
							for (int j = 0; j < N; j++) {
								matrix[i][j] = cube[n][i][j];
							}
						}
						break;
					}
				}
				//display_array(matrix, N);
				cout << Laplace(matrix, N) << endl;
				break;
			}
		}
	}

	return 0;
}
//SECTION FUNCTIONS
long long Laplace(long long mat[][max_size], int size)
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
		for (int col = 0; col < size; col++) {
			if (mat[0][col]) {
				for (int i = 1; i < size; i++) {
					shift = 0;
					for (int j = 0; j < size; j++) {
						if (j != col)
						{
							sub_mat[i - 1][j - shift] = mat[i][j];
						}
						else
							shift = 1; //Skips over column and writes to proper cell
					}
				}
				det += sign * mat[0][col] * Laplace(sub_mat, size - 1);
				sign = -sign;
			}
		}
		return det;
	}
}

void display_array(long long arr[][max_size], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

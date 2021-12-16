// Maksim Zdobnikau

#include <iostream>
using std::cin; using std::cout; using std::endl; using std::string;

int main()
{
	unsigned short N;
	const int cube_size = 32;
	long long int cube[cube_size][cube_size][cube_size];
	char select = 0, K;
	short l, v, p, h, w, d;

	std::cin >> N;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < N; ++k) {
				std::cin >> cube[j][k][i]; // Changed order?!
			}
		}
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < N; ++k) {
				std::cout << cube[j][k][i]; // Changed order?!
			}
		}
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < N; ++k) {
				std::cin >> cube[i][j][k]; // Changed order?!
			}
		}
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < N; ++k) {
				std::cout << cube[i][j][k]; // Changed order?!
			}
		}
	}
	/*
	while (select != 'E') {
		std::cin >> select;
		if (select == 'D') {
			std::cin >> K >> l;
			det(cube, N, K, l);
		}
		else {
			std::cin >> l >> v >> p >> h;

			if (select == 'C') {
				std::cin >> w >> d;
				h++;
				w++;
				d++; // correction of values
			}
			else {
				w = d = ++h;
			}

			figures(cube, N, select, l, v, p, h, w, d);
		}
		std::cin >> select;
	}
*/
	return 0;
}
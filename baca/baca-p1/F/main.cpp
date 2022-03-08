#include <string>
#include <iostream>
#include "kod.hpp"
using namespace std;

int main()
{
	int x = 1;
	long long size;
	int number;
	string text = "test";
	string parameterOne{}, parameterTwo{}, parameterThree{};
	getline(cin, text);
	switch (x)
	{
	case 1:
		cin >> parameterOne >> parameterTwo >> parameterThree;
		cout << FormatujNapis(text, parameterOne, parameterTwo, parameterThree) << endl;
		break;
	case 2:
		cout << NajwiekszeSlowo(text) << endl;
		break;
	case 3:
		cout << NormalizujNapis(text) << endl;
		break;
	case 4:
		cin >> number;
		cout << UsunSlowo(text, number) << endl;
		break;
	default:
		break;
	}
}
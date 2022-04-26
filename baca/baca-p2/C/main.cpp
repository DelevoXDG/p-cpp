#include "source.cpp"

using namespace std;


int main(int argc, char const* argv[])
{
	// cout << sumTwo("12345", "1111111");
	cout << multTwo("1337", "228322") << endl;
	cout << sumTwo("0012345", "-0000111111") << endl;
	cout << sumTwo("12345", "111111") << endl;
	cout << sumTwo("-228", "1337") << endl;
	cout << sumTwo("0", "-678") << endl;
	cout << sumTwo("66666", "-399") << endl;
	string arr[] = { "11111", "-666", "-777" };
	// cout << sumMany(3, 0, arr) << endl;
	cout << Sum(3, "1337", "-228", "-322") << endl;
	cout << Sum(1, "1337") << endl;
	cout << Sum(5, "+0010", "-009", "-0000", "+3", "-8") << endl;
	std::string loh;
	std::string* result = &loh;

	Sum(result, 3, arr);
	cout << loh;
	return 0;
}

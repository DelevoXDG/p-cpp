// Maksim Zdobnikau
// https://baca.ii.uj.edu.pl/p12021/

#include <iostream>
#include <string>
#include <cstdarg>
typedef unsigned long long uint64, ull;

// Section Declarations
std::string Sum(int, const std::string*);
std::string Sum(int, ...);

void Sum(std::string*,
	int, const std::string*);
void Sum(std::string*,
	int, ...);

void Sum(std::string&, int,
	const std::string*);
void Sum(std::string&,
	int, ...);

std::string Mult(int, const std::string*);
std::string Mult(int, ...);

void Mult(std::string&, int, const std::string*);
void Mult(std::string&, int, ...);

std::string Operation(std::string(*)(int, const std::string*),
	int, const std::string*);
std::string Operation(std::string(*)(int,
	const std::string*), int, ...);

void Operation(std::string*, std::string(*)(int, const std::string*),
	int, const std::string*);
void Operation(std::string*, std::string(*)(int, const std::string*),
	int, ...);

void Operation(std::string&, void(*) (std::string*, int, const std::string*),
	int, const std::string*);
void Operation(std::string&, void(*) (std::string*, int, const std::string*),
	int, ...);

// Section Helpers
struct Comparison {
private:
	enum Result {
		varlesser,
		varequal,
		vargreater
	};
	Result res;
public:
	Result NumericCompare(const std::string& str1, const std::string& str2, size_t i = 0) {
		if (str1[i] < str2[i]) return varlesser;
		if (str1[i] > str2[i]) return vargreater;

		return NumericCompare(str1, str2, i + 1);
	}
	Comparison(const std::string& str1, const std::string& str2) {
		if (str1.length() < str2.length()) {
			res = varlesser;
		}
		else if (str1.length() > str2.length()) {
			res = vargreater;
		}
		else if (str1 == str2) {
			res = varequal;
		}
		else {
			res = NumericCompare(str1, str2, 0);
		}
	}
	bool greater() {
		return res == vargreater;
	}
	bool equal() {
		return res == varequal;
	}
	bool lesser() {
		return res == varlesser;
	}

};
inline bool isNegative(const std::string str) {
	return str[0] == '-';
}
std::string removeSign(const std::string str) {
	if (str[0] == '+' || str[0] == '-') {
		return str.substr(1, str.length());
	}

	return str;
}
std::string rmZeros(const std::string str, uint64 i = 0) {
	size_t size = str.length();
	if (i > size || str[i] != '0') { // Recursion exit condition
		return str.substr(i, size);
	}

	return rmZeros(str, i + 1);
}



std::string sumTwo(const std::string& inStr1, const std::string& inStr2) {
	std::string str1 = inStr1;
	std::string str2 = inStr2;

	str1 = removeSign(str1);
	str1 = rmZeros(str1);

	str2 = removeSign(str2);
	str2 = rmZeros(str2);

	Comparison cmpRes(str1, str2);

	if (str1 == "0") {
		if (str2 == "0") {
			return "0";
		}
		if (isNegative(inStr2)) {
			return "-" + str2;
		}
		return str2;
	}
	if (str2 == "0") {
		if (isNegative(inStr1)) {
			return "-" + str1;
		}
		return str1;
	}
	if ((!isNegative(inStr1) != !isNegative(inStr2))) {
		if (cmpRes.equal()) {
			return "0";
		}
		if (isNegative(inStr1)) {
			if (cmpRes.greater()) {
				return "-" + rmZeros(sub(str1, str2));
			}
			return rmZeros(sub(str2, str1));
		}
		else {
			if (cmpRes.lesser()) {
				return "-" + rmZeros(sub(str2, str1));
			}
			return rmZeros(sub(str1, str2));
			// return cmpRes.lesser() ? "-" + rmZeros(sub(str2, str1)) : rmZeros(sub(str1, str2));
		}
	}
	if (isNegative(inStr1) && isNegative(inStr2)) {
		return "-" + add(str1, str2);
	}

	return add(str1, str2);
}

std::string subSum(int argc, const std::string* args, int n) {
	if (n >= argc) {
		return "0";
	}

	return "0";
}
// Section Implementation
std::string Sum(int argCount, const std::string* args) {
	return subSum(argCount, args, 0);
}
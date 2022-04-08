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
bool isNegative(const std::string str) {
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
	i++;
	return rmZeros(str, i);
}
std::string strReverse(const std::string& str, size_t i = 0) {
	if (i >= str.size()) { // Exit condition
		return "";
	}

	return str[str.length() - 1 - i] + strReverse(str, i + 1);

}

std::string addNumStr(const std::string& strA, const std::string& strB, int carry = 0, size_t i = 0) {
	size_t sizeA = strA.length();
	size_t sizeB = strB.length();
	if (carry > 0 || (i < sizeA && i < sizeB)) {
		std::string tmp("");
		int curCarry = carry;
		if (i < sizeA) {
			curCarry += strA[sizeA - 1 - i] - carry - '0';
		}
		if (i < sizeB) {
			curCarry += strB[sizeB - 1 - i] - carry - '0';
		}
		if (curCarry >= 10) {
			curCarry = curCarry - 10;
			carry = 1;
		}
		else carry = 0;

		tmp = tmp + std::string(1, char(curCarry + '0')) + addNumStr(strA, strB, carry, i + 1);

		if (i != 0) {
			return tmp;
		}
		// End of first caller 
		return strReverse(tmp); // reverse final result
	}
	if (i < strA.length()) { // && >= b.length 
		return strReverse(strA.substr(0, strA.length() - i));
	}
	if (i < strB.length()) {
		return strReverse(strB.substr(0, strB.length() - i));
	}

	return "";
}
std::string SubNumStr(const std::string& strA, const std::string& strB, int carry = 0, size_t i = 0) {
	size_t sizeA = strA.length();
	size_t sizeB = strB.length();

	if (carry != 0 || i < strB.length()) {
		std::string tmp("");
		int curCarry = carry;

		if (i < sizeA) {
			curCarry += strA[sizeA - 1 - i] - carry - '0';
		}
		if (i < sizeB) {
			curCarry -= strA[sizeB - 1 - i] - '0';
		}
		if (curCarry >= 0)
			carry = 0;
		else {
			curCarry = curCarry + 10;
			carry = 1;
		}

		tmp = tmp + std::string(1, char(curCarry + '0')) + SubNumStr(strA, strB, carry, i + 1);

		if (i != 0) {
			return tmp;
		}
		// End of first caller 
		return strReverse(tmp); // reverse final result
	}
	if (i < strA.length()) { // && >= b.length 
		return strReverse(strA.substr(0, strA.length() - i));
	}

	return "";
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
	if ((!isNegative(inStr1) != !isNegative(inStr2))) { //xor
		if (cmpRes.equal()) {
			return "0";
		}
		if (isNegative(inStr1)) {
			if (cmpRes.greater()) {
				return "-" + rmZeros(SubNumStr(str1, str2));
			}
			return rmZeros(SubNumStr(str2, str1));
		}
		else {
			if (cmpRes.lesser()) {
				return "-" + rmZeros(SubNumStr(str2, str1));
			}
			return rmZeros(SubNumStr(str1, str2));
			// return cmpRes.lesser() ? "-" + rmZeros(sub(str2, str1)) : rmZeros(sub(str1, str2));
		}
	}
	if (isNegative(inStr1) && isNegative(inStr2)) {
		return "-" + addNumStr(str1, str2);
	}

	return addNumStr(str1, str2);
}

std::string subSum(const int argc, int i, const std::string* args) {
	if (i >= argc) {
		return "0";
	}
	return sumTwo(args[i], Sum(argc, i + 1, args));
}
std::string subSumVa(const int argc, int i, std::va_list va_args) {
	if (i >= argc) {
		return "0";
	}
	return sumTwo(va_arg(va_args, char*), subSumVa(argc, i + 1, va_args));
}

// Section Implementation
std::string Sum(int argc, const std::string* args) {
	std::string res = subSum(argc, 0, args);

	return res;
}
std::string Sum(int argc, ...) {
	std::va_list va_args;

	va_start(va_args, argc);
	std::string res = subSumVa(argc, 0, va_args);
	va_end(va_args);

	return res;
}
void Sum(std::string* res, int argc, const std::string* args) {
	res->clear();
	*res = subSum(argc, 0, args);
}
void Sum(std::string* res, int argc, ...) {
	res->clear();
	std::va_list va_args;

	va_start(va_args, argc);
	*res = subSumVa(argc, 0, va_args);
	va_end(va_args);

}
std::string Mult(int argc, const std::string* args) {
	std::string res = subMult(argc, 0, args);

	return res;
}
std::string Mult(int argc, ...) {
	std::va_list va_args;

	va_start(va_args, argc);
	std::string res = subMultVa(argc, 0, va_args);
	va_end(va_args);

	return res;
}



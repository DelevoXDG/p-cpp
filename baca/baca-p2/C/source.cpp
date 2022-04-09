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
	Result NumericCompare(const std::string& str1, const std::string& str2, uint64 i = 0) {
		if (str1[i] < str2[i]) return varlesser;
		if (str1[i] > str2[i]) return vargreater;

		i++;
		return NumericCompare(str1, str2, i);
	}
	Comparison(const std::string& str1, const std::string& str2) {
		if (str1.size() < str2.size()) {
			res = varlesser;
		}
		else if (str1.size() > str2.size()) {
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
		return str.substr(1, str.size());
	}

	return str;
}
std::string rmZeros(const std::string str, uint64 i = 0) {
	uint64 size = str.size();
	if (i > size || str[i] != '0') { // Recursion exit condition
		return str.substr(i, size);
	}
	i++;
	return rmZeros(str, i);
}
std::string strReverse(const std::string& str, uint64 i = 0) {
	if (i >= str.size()) { // Exit condition
		return "";
	}
	i++;
	return str[str.size() - i] + strReverse(str, i);

}

std::string addNumStr(const std::string& strA, const std::string& strB, int carry = 0, uint64 i = 0) {
	uint64 sizeA = strA.size();
	uint64 sizeB = strB.size();
	std::string tmp("");
	if ((i < sizeA && i < sizeB) || carry > 0) {
		int extraCarry = 0;
		if (i < sizeA) {
			extraCarry += int(strA[sizeA - 1 - i] - carry) - '0';
		}
		if (i < sizeB) {
			extraCarry += int(strB[sizeB - 1 - i] - carry) - '0';
		}
		int curCarry = 0;
		if (carry + extraCarry >= 10) {
			curCarry = carry + extraCarry - 10;
			carry = 1;
		}
		else { carry = 0; }

		tmp = tmp + std::string(1, char(curCarry + '0')) + addNumStr(strA, strB, carry, i + 1);

		if (i == 0) { // End of first caller 
			tmp = strReverse(tmp);
		}

		return tmp;
	}
	if (i >= strB.size() && i < strA.size()) {
		return strReverse(strA.substr(0, strA.size() - i));
	}
	if (i < strB.size() && i >= strA.size()) {
		return strReverse(strB.substr(0, strB.size() - i));
	}

	return "";
}
std::string SubNumStr(const std::string& strA, const std::string& strB, int carry = 0, uint64 i = 0) {
	uint64 sizeA = strA.size();
	uint64 sizeB = strB.size();
	std::string tmp("");
	if (i < strB.size() || carry > 0) {
		int extraCarry = 0;
		if (i < sizeA) {
			extraCarry += int(strA[sizeA - 1 - i] - carry) - '0';
		}
		if (i < sizeB) {
			extraCarry -= int(strA[sizeB - 1 - i]) - '0';
		}
		int curCarry = 0;
		if (carry + extraCarry < 0) {
			curCarry = carry + extraCarry + 10;
			carry = 1;
		}
		else { carry = 0; }

		tmp = tmp + std::string(1, char(curCarry + '0')) + SubNumStr(strA, strB, carry, i + 1);

		if (i == 0) { // End of first caller 
			tmp = strReverse(tmp);
		}

		return tmp;
	}
	if (i < strA.size()) {
		return strReverse(strA.substr(0, strA.size() - i));
	}

	return "";
}


std::string sumTwo(const std::string& inStr1, const std::string& inStr2) {
	std::string str1(inStr1);
	std::string str2(inStr2);

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
			str2 = "-" + str2;
		}
		return str2;
	}
	if (str2 == "0") {
		if (isNegative(inStr1)) {
			str1 = "-" + str1;
		}
		return str1;
	}
	if ((isNegative(inStr1) != isNegative(inStr2))) { //xor
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
		}
	}
	if (isNegative(inStr1) && isNegative(inStr2)) {
		return "-" + addNumStr(str1, str2);
	}

	return addNumStr(str1, str2);
}
std::string multNumChar(const std::string& a, const char& b, char c = 0, size_t n = 0)
{
	if (n < a.size() || c != 0) {
		char x = c;
		x += n < a.size() ? (*(a.rbegin() + n) - '0') * (b - '0') : 0;
		std::string temp = "";
		temp += x % 10 + '0';
		temp += multNumChar(a, b, x / 10, n + 1);
		return n == 0 ? strReverse(temp) : temp;
	}
	else {
		return "";
	}
}
std::string multNumStr(const std::string& strA, const std::string& strB, uint64 i) {
	uint64 sizeA = strA.size();
	uint64 sizeB = strB.size();
	if (i >= sizeB) {
		return "0";
	}
	std::string res("");
	std::string multA = multNumChar(strA, strB[sizeA - 1 - i], 0, 0);
	i++;
	std::string multB = multNumStr(strA, strB, i);
	res = addNumStr(multA, multB, 0, 0);

	return res;
}

std::string multTwo(std::string inStr1, std::string inStr2) {
	std::string str1(inStr1);
	std::string str2(inStr2);

	str1 = removeSign(str1);
	str1 = rmZeros(str1);
	if (str1 == "0") return "0";

	str2 = removeSign(str2);
	str2 = rmZeros(str2);
	if (str2 == "0") return "0";
	else {
		std::string res = multNumStr(str1, str2, "", 0);
		if (isNegative(inStr1) != isNegative(inStr2)) {
			res = "-" + res;
		}
		return res;
	}
}


std::string subSum(const int argc, int i, const std::string* args) {
	if (i >= argc) {
		return "0";
	}
	i++;
	return sumTwo(args[i - 1], Sum(argc, i, args));
}
std::string subSumVa(const int argc, int i, std::va_list va_args) {
	if (i >= argc) {
		return "0";
	}
	i++;
	return sumTwo(va_arg(va_args, char*), subSumVa(argc, i, va_args));
}
std::string Mult(int argc, const std::string* args, int i) {
	if (i >= argc) {
		return "1";
	}
	i++;
	// [ ] todo
	return "1";
}

// Section Implementation
std::string Sum(int argc, const std::string* args) {
	if (argc == 0) {
		return "0";
	}
	std::string res = subSum(argc, 0, args);

	return res;
}
std::string Sum(int argc, ...) {
	if (argc == 0) {
		return "0";
	}
	std::va_list va_args;

	va_start(va_args, argc);
	std::string res = subSumVa(argc, 0, va_args);
	va_end(va_args);

	return res;
}
void Sum(std::string* res, int argc, const std::string* args) {
	res->clear();
	if (argc == 0) {
		*res = "0";
	}
	*res = subSum(argc, 0, args);
}
void Sum(std::string* res, int argc, ...) {
	res->clear();
	if (argc == 0) {
		*res = "0";
	}
	std::va_list va_args;

	va_start(va_args, argc);
	*res = subSumVa(argc, 0, va_args);
	va_end(va_args);

}
std::string Mult(int argc, const std::string* args) {
	if (argc == 0) {
		return "0";
	}
	std::string res = subMult(argc, 0, args);

	return res;
}
std::string Mult(int argc, ...) {
	if (argc == 0) {
		return "0";
	}
	std::va_list va_args;

	va_start(va_args, argc);
	std::string res = subMultVa(argc, 0, va_args);
	va_end(va_args);

	return res;
}



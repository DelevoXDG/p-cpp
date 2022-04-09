// Maksim Zdobnikau
// https://baca.ii.uj.edu.pl/p12021/

#include <iostream>
#include <string>
#include <cstdarg>
typedef unsigned long long uint64, ull;
typedef unsigned long long int64, ll;

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
bool isNegative(const std::string& str) {
	return str[0] == '-';
}
std::string removeSign(const std::string& str) {
	if (str[0] == '+' || str[0] == '-') {
		return str.substr(1, str.size());
	}

	return str;
}
std::string rmZeros(const std::string& str, uint64 i = 0) {
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

std::string addNumStr(const std::string& strA, const std::string& strB, short int carry = 0, uint64 i = 0) {
	uint64 sizeA = strA.size();
	uint64 sizeB = strB.size();
	std::string tmp("");
	if ((i < sizeA && i < sizeB) || carry > 0) {
		short int digitSum = 0;
		if (i < sizeA) {
			digitSum += int(strA[sizeA - 1 - i] - '0');
		}
		if (i < sizeB) {
			digitSum += int(strB[sizeB - 1 - i] - '0');
		}
		short int reducedDigitSum = digitSum + carry;
		if (reducedDigitSum >= 10) {
			reducedDigitSum = reducedDigitSum - 10;
			carry = 1;
		}
		else {
			// reducedDigitSum = carry + digitSum;
			carry = 0;
		}

		tmp = tmp + std::string(1, char(reducedDigitSum + '0')) + addNumStr(strA, strB, carry, i + 1);

	}
	else if (i >= strB.size() && i < strA.size()) {
		tmp = strReverse(strA.substr(0, strA.size() - i));
	}
	else if (i < strB.size() && i >= strA.size()) {
		tmp = strReverse(strB.substr(0, strB.size() - i));
	}

	if (i == 0) { // End of first caller 
		tmp = strReverse(tmp);
	}

	return tmp;
}
std::string SubNumStr(const std::string& strA, const std::string& strB, short int carry = 0, uint64 i = 0) {
	uint64 sizeA = strA.size();
	uint64 sizeB = strB.size();
	std::string tmp("");
	if (i < strB.size() || carry > 0) {
		short int digitSum = 0;
		digitSum += int(strA[sizeA - 1 - i] - '0');
		if (i < sizeB) {	// Or nothing to subtract
			digitSum -= int(strB[sizeB - 1 - i] - '0');
		}
		short int reducedDigitSum = digitSum - carry;
		if (reducedDigitSum < 0) {
			reducedDigitSum = reducedDigitSum + 10;
			carry = 1;
		}
		else {
			carry = 0;
		}

		tmp = tmp + std::string(1, char(reducedDigitSum + '0'))
			+ SubNumStr(strA, strB, carry, i + 1);
	}
	else if (i < strA.size()) {
		tmp = strReverse(strA.substr(0, strA.size() - i));
	}
	if (i == 0) {// End of first caller 
		tmp = strReverse(tmp);
	}

	return tmp;
}


std::string sumTwo(const std::string& inStr1, const std::string& inStr2) {
	std::string str1(inStr1);
	std::string str2(inStr2);

	str1 = removeSign(str1);
	str1 = rmZeros(str1);

	str2 = removeSign(str2);
	str2 = rmZeros(str2);

	Comparison cmpRes(str1, str2);

	if ((isNegative(inStr1) != isNegative(inStr2))) { //xor
		if (cmpRes.equal()) {
			return "0";
		}
		if (isNegative(inStr2)) {
			if (cmpRes.greater()) {
				return rmZeros(SubNumStr(str1, str2));
			}
			return "-" + rmZeros(SubNumStr(str2, str1));
		}
		else {
			if (cmpRes.greater()) {
				return "-" + rmZeros(SubNumStr(str1, str2));
			}
			return rmZeros(SubNumStr(str2, str1));
		}
	}
	if (isNegative(inStr1) && isNegative(inStr2)) {
		return "-" + addNumStr(str1, str2);
	}

	return addNumStr(str1, str2);
}
std::string multNumbyDigit(const std::string& a, const char& b, short int c, uint64 i) {
	// [ ] todo
	if (i < a.size() || c != 0) {
		short int x = c;
		x += i < a.size() ? (*(a.rbegin() + i) - '0') * (b - '0') : 0;
		std::string temp = "";
		temp += x % 10 + '0';
		temp += multNumbyDigit(a, b, x / 10, i + 1);
		return i == 0 ? strReverse(temp) : temp;
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
	std::string digitMultRes =
		multNumbyDigit(strA, (short int)strB[sizeB - 1 - i], 0, 0)
		+ std::string(i, '0');							// * 10^i
	i++;
	std::string nextMult = multNumStr(strA, strB, i);
	res = addNumStr(nextMult, digitMultRes, 0, 0);

	return res;
}

std::string multTwo(const std::string& inStr1, const std::string& inStr2) {
	std::string str1(inStr1);
	std::string str2(inStr2);

	str1 = removeSign(str1);
	str1 = rmZeros(str1);
	if (str1 == "0") {
		return "0";
	}


	str2 = removeSign(str2);
	str2 = rmZeros(str2);
	if (str2 == "0") {
		return "0";
	}

	std::string res = multNumStr(str1, str2, 0);
	if (isNegative(inStr1) != isNegative(inStr2)) {
		res = "-" + res;
	}
	return res;
}

std::string Repeat(std::string(*f)(const std::string&, const std:: string&), int argc, int i, const std::string* args) {
	if (i >= argc) {
		if (f == sumTwo) return "0";
		if (f == multTwo) return "1";

		return "e";
	}
	std::string curElement = args[i];
	std::string nextValues = Repeat(f, argc, ++i, args);
	return f(nextValues, curElement);
}
std::string sumMany(const int argc, int i, const std::string* args) {
	if (i >= argc) {
		return "0";
	}
	std::string curElement = args[i];
	std::string nextSum = sumMany(argc, ++i, args);

	return sumTwo(nextSum, curElement);
}
std::string sumManyVa(const int argc, int i, std::va_list& va_args) {
	if (i >= argc) {
		return "0";
	}
	std::string curElement = std::string(va_arg(va_args, char*));
	std::string nextSum = sumManyVa(argc, ++i, va_args);
	return sumTwo(nextSum, curElement);
}
std::string multMany(int argc, int i, const std::string* args) {
	if (i >= argc) {
		return "1";
	}
	std::string curElement = args[i];
	std::string nextSum = multMany(argc, ++i, args);

	return multTwo(nextSum, curElement);
}
std::string multManyVa(const int argc, int i, std::va_list& va_args) {
	if (i >= argc) {
		return "0";
	}
	std::string curElement = std::string(va_arg(va_args, char*));
	std::string nextSum = multManyVa(argc, ++i, va_args);

	return multTwo(nextSum, curElement);
}
void fillVaArray(const int argc, int i, std::va_list& va_args, std::string* arr) {
	if (i >= argc) {
		return;
	}
	arr[i] = std::string(va_arg(va_args, char*));
	fillVaArray(argc, ++i, va_args, arr);
}

// Section Required functions
std::string Sum(int argc, const std::string* args) {
	if (argc == 0) {
		return "0";
	}
	std::string res = Repeat(sumTwo, argc, 0, args);

	return res;
}
std::string Sum(int argc, ...) {
	if (argc == 0) {
		return "0";
	}

	std::va_list va_args;
	std::string argsArr[argc];
	std::string* args = &argsArr[0];
	va_start(va_args, argc);
	fillVaArray(argc, 0, va_args, args);
	va_end(va_args);
	std::string res = Sum(argc, args);
	return res;
}
void Sum(std::string* res, int argc, const std::string* args) {
	res->clear();
	if (argc == 0) {
		*res = "0";
	}
	*res = sumMany(argc, 0, args);
}
void Sum(std::string* res, int argc, ...) {
	res->clear();
	if (argc == 0) {
		*res = "0";
	}
	std::va_list va_args;

	va_start(va_args, argc);
	*res = sumManyVa(argc, 0, va_args);
	va_end(va_args);

}
// std::string Mult(int argc, const std::string* args) {
// 	if (argc == 0) {
// 		return "0";
// 	}
// 	std::string res = subMult(argc, 0, args);

// 	return res;
// }
// std::string Mult(int argc, ...) {
// 	if (argc == 0) {
// 		return "0";
// 	}
// 	std::va_list va_args;

// 	va_start(va_args, argc);
// 	std::string res = subMultVa(argc, 0, va_args);
// 	va_end(va_args);

// 	return res;
// }



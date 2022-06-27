// Maksim Zdobnikau

typedef unsigned long long uint64, ull;

std::string Operation(std::string(*)(int, const std::string*),
	int, const std::string*);
#include <string>
#include <iostream>
#include <cstdarg>
// Section Helpers
struct Comparison {	// Compare two number abs values
private:
	enum Result {
		varlesser,
		varequal,
		vargreater
	};
	Result res;
public:
	Result DigitCompare(const std::string& str1, const std::string& str2, uint64 i = 0) {
		if (str1[i] < str2[i]) return varlesser;
		if (str1[i] > str2[i]) return vargreater;

		i++;
		return DigitCompare(str1, str2, i);
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
			res = DigitCompare(str1, str2, 0);
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
std::string rmZeros(const std::string& str, uint64 i = 0) {
	uint64 size = str.size();
	if (i + 1 >= size || str[i] != '0') {	// Rm all zeroes except last symbol
		return str.substr(i, size);
	}
	i++;
	return rmZeros(str, i);
}
bool isNegative(const std::string& str) {
	return str[0] == '-';
}
std::string removeSign(const std::string& str) {
	if (str[0] == '+' || str[0] == '-') {
		return str.substr(1, str.size());
	}

	return str;
}
std::string strReverse(const std::string& str, uint64 i = 0) {
	if (i >= str.size()) {
		return "";
	}
	i++;
	return str[str.size() - i] + strReverse(str, i);
}
void fillArrWithVaArgs(const int argc, int i, std::va_list& va_args, std::string* arr) {
	if (i >= argc) {
		return;
	}
	arr[i] = std::string(va_arg(va_args, char*));

	fillArrWithVaArgs(argc, ++i, va_args, arr);
}


std::string addNumStr(const std::string& strA, const std::string& strB, short int carry, uint64 i) {
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
			carry = 0;
		}
		std::string curSum = std::string(1, char(reducedDigitSum + '0'));
		std::string nextSum = addNumStr(strA, strB, carry, i + 1);
		tmp = tmp + curSum + nextSum;
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
std::string SubNumStr(const std::string& strA, const std::string& strB, short int carry, uint64 i) {
	uint64 sizeA = strA.size();
	uint64 sizeB = strB.size();
	std::string tmp("");

	if (i < strB.size() || carry < 0) {
		short int digitSum = 0;
		digitSum += int(strA[sizeA - 1 - i] - '0');
		if (i < sizeB) {	// Or nothing to subtract
			digitSum -= int(strB[sizeB - 1 - i] - '0');
		}
		short int reducedDigitSum = digitSum + carry;

		if (reducedDigitSum < 0) {
			reducedDigitSum = reducedDigitSum + 10;
			carry = -1;
		}
		else {
			carry = 0;
		}
		std::string cur = std::string(1, char(reducedDigitSum + '0'));
		std::string next = SubNumStr(strA, strB, carry, i + 1);
		tmp = tmp + cur + next;
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
				return rmZeros(SubNumStr(str1, str2, 0, 0));
			}
			return "-" + rmZeros(SubNumStr(str2, str1, 0, 0));
		}
		else {
			if (cmpRes.greater()) {
				return "-" + rmZeros(SubNumStr(str1, str2, 0, 0));
			}
			return rmZeros(SubNumStr(str2, str1, 0, 0));
		}
	}
	if (isNegative(inStr1) && isNegative(inStr2)) {
		return "-" + addNumStr(str1, str2, 0, 0);
	}

	return addNumStr(str1, str2, 0, 0);
}
std::string multNumbyDigit(const std::string& strA, const short int digit, short int carry, uint64 i) {
	uint64 sizeA = strA.size();
	std::string tmp("");
	if (i < strA.size() || carry > 0) {
		short int digitSum = 0;

		if (i < strA.size()) {
			digitSum += int(strA[sizeA - 1 - i] - '0') * digit;
		}
		short int reducedDigitSum = digitSum + carry;
		carry = reducedDigitSum / 10;
		reducedDigitSum = reducedDigitSum % 10;

		tmp = tmp + std::string(1, char(reducedDigitSum + '0')) +
			multNumbyDigit(strA, digit, carry, i + 1);

	}
	if (i == 0) {
		tmp = strReverse(tmp);
	}
	return tmp;
}

std::string multNumStr(const std::string& strA, const std::string& strB, uint64 i) {
	uint64 sizeA = strA.size();
	uint64 sizeB = strB.size();
	if (i >= sizeB) {
		return "0";
	}
	std::string res("");
	std::string digitMultRes =
		multNumbyDigit(strA, short(strB[sizeB - 1 - i] - '0'), 0, 0)
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

std::string Repeat(std::string(*func)(const std::string&, const std:: string&), int argc, int i, const std::string* args) {
	if (i >= argc) {
		if (func == sumTwo) return "0";		// Add zero
		if (func == multTwo) return "1";	// Multiply by one

		return "err";
	}
	std::string curElement = args[i];
	std::string nextValues = Repeat(func, argc, ++i, args);
	return func(nextValues, curElement);
}

// Section Required functions

// Section Sum

//Section String
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
	fillArrWithVaArgs(argc, 0, va_args, args);
	va_end(va_args);

	std::string res = Sum(argc, args);
	return res;
}
// Section Pointers
void Sum(std::string* res, int argc, const std::string* args) {
	if (res) {
		res->clear();
	}
	*res = Sum(argc, args);
	*res = Operation(Sum, argc, args);
}
void Sum(std::string* res, int argc, ...) {
	if (res) {
		res->clear();
	}
	if (argc == 0) {
		*res = "0";
	}
	std::va_list va_args;
	std::string argsArr[argc];
	std::string* args = &argsArr[0];

	va_start(va_args, argc);
	fillArrWithVaArgs(argc, 0, va_args, args);
	va_end(va_args);

	*res = Operation(Sum, argc, args);
}
// Section References
void Sum(std::string& res, int argc, const std::string* args) {
	if (!res.empty()) {
		res.clear();
	}
	res = Operation(Sum, argc, args);
}
void Sum(std::string& res, int argc, ...) {
	if (argc == 0) {
		res = "0";
		return;
	}
	std::va_list va_args;
	std::string argsArr[argc];
	std::string* args = &argsArr[0];

	va_start(va_args, argc);
	fillArrWithVaArgs(argc, 0, va_args, args);
	va_end(va_args);

	res = Operation(Sum, argc, args);
}
// Section Multiplication
std::string Mult(int argc, const std::string* args) {
	if (argc == 0) {
		return "0";
	}
	std::string res = Repeat(multTwo, argc, 0, args);

	return res;
}
std::string Mult(int argc, ...) {
	if (argc == 0) {
		return "0";
	}
	std::va_list va_args;
	std::string argsArr[argc];
	std::string* args = &argsArr[0];

	va_start(va_args, argc);
	fillArrWithVaArgs(argc, 0, va_args, args);
	va_end(va_args);

	std::string res = Operation(Mult, argc, args);
	return res;
}
// Section Pointers
void Mult(std::string* res, int argc, const std::string* args) {
	if (res && !(res->empty())) {
		res->clear();
	}
	*res = Operation(Mult, argc, args);
}
void Mult(std::string* res, int argc, ...) {
	if (res && !(res->empty())) {
		res->clear();
	}
	if (argc == 0) {
		*res = "0";
		return;
	}
	std::va_list va_args;
	std::string argsArr[argc];
	std::string* args = &argsArr[0];

	va_start(va_args, argc);
	fillArrWithVaArgs(argc, 0, va_args, args);
	va_end(va_args);

	*res = Operation(Mult, argc, args);
}
// Section References
void Mult(std::string& res, int argc, const std::string* args) {
	if (!(res.empty())) {
		res.clear();
	}
	res = Operation(Mult, argc, args);
}
void Mult(std::string& res, int argc, ...) {
	if (!(res.empty())) {
		res.clear();
	}
	std::va_list va_args;
	std::string argsArr[argc];
	std::string* args = &argsArr[0];

	va_start(va_args, argc);
	fillArrWithVaArgs(argc, 0, va_args, args);
	va_end(va_args);

	res = Operation(Mult, argc, args);
}
std::string Operation(std::string(*func)(int, const std::string*), int argc, const std::string* args) {
	if (argc == 0) {
		return "0";
	}

	return func(argc, args);
}
std::string Operation(std::string(*func)(int, const std::string*), int argc, ...) {
	if (argc == 0) {
		return "0";
	}

	std::va_list va_args;
	std::string argsArr[argc];
	std::string* args = &argsArr[0];

	va_start(va_args, argc);
	fillArrWithVaArgs(argc, 0, va_args, args);
	va_end(va_args);

	std::string res = func(argc, args);
	return res;
}
void Operation(std::string* res, std::string(*func) (int, const std::string*), int argc, const std::string* args) {
	if (res && !(res->empty())) {
		res->clear();
	}
	if (argc == 0) {
		*res = "0";
		return;
	}
	*res = func(argc, args);
}
void Operation(std::string* res, std::string(*func) (int, const std::string*), int argc, ...) {
	if (res && !(res->empty())) {
		res->clear();
	}
	if (argc == 0) {
		*res = "0";
		return;
	}
	std::va_list va_args;
	std::string argsArr[argc];
	std::string* args = &argsArr[0];

	va_start(va_args, argc);
	fillArrWithVaArgs(argc, 0, va_args, args);
	va_end(va_args);

	*res = func(argc, args);
}
void Operation(std::string& res, void(*func) (std::string*, int, const std::string*), int argc, const std::string* args) {
	if (!(res.empty())) {
		res.clear();
	}
	if (argc == 0) {
		res = "0";
		return;
	}
	std::string result("");
	std::string* rptr = &result;
	func(rptr, argc, args);

	res = result;
}
void Operation(std::string& res, void(*func) (std::string*, int, const std::string*), int argc, ...) {
	if (!(res.empty())) {
		res.clear();
	}
	if (argc == 0) {
		res = "0";
		return;
	}
	std::va_list va_args;
	std::string argsArr[argc];
	std::string* args = &argsArr[0];

	va_start(va_args, argc);
	fillArrWithVaArgs(argc, 0, va_args, args);
	va_end(va_args);

	std::string result("");
	std::string* rptr = &result;
	func(rptr, argc, args);

	res = result;
}
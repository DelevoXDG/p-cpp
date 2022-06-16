// Maksim Zdobnikau

#include <iostream>
#include <cstdarg>

#define nullptr 0

// b / a = (0), a = ()
// Heap buffer overflow
// Int overflow
// Multiply all
// [ ] uncomment this 

namespace Helpers {
	int abs(const int A) {
		return A < 0 ? -A : A;
	}
	int min(const int A, const int B) {
		return A < B ? A : B;
	}
	int max(const int A, const int B) {
		return A < B ? B : A;
	}
	int gcd(const int A, const int B) {
		if (A == 0 || B == 0) {
			return A == 0 ? B : A;
		}
		int num = abs(A);
		int div = abs(B);
		int rem = 0;

		while (div != 0) {
			rem = num % div;
			num = div;
			div = rem;
		}
		return num;
	}
	int lcm(const int A, const int B) {
		int numA = abs(A);
		int numB = abs(B);

		return (numA * numB) / gcd(numA, numB);
	}
	int gcd(long long* arr, const int size) {
		if (size == 0) {
			return 1;
		}
		int ans = arr[0];
		for (size_t i = 1; i < size && ans != 1; i++) {
			ans = gcd(ans, arr[i]);
		}
		return ans;
	}
}

struct frac {
public:
	long long NUM;
	long long den;

	frac(const long long NOM, const long long den) :NUM(NOM), den(den) {
		this->simplify();
	}
	long long num() { return this->NUM; }
	long long den() { return this->den; }
private:
	void simplify(void) {
		long long gcd = Helpers::gcd(NUM, den);
		NUM *= gcd;
		den *= gcd;
	}
};

struct Array {
private:
	long long* array;
	int length;
public:
	Array(const int = 0);
	Array(int* const, const int);
	Array(const Array&);
	Array(const int, std::va_list&);
	~Array();


	void divideAllBy(const int);
	long long& operator [] (const int&) const;
	Array& operator =(const Array&);
	int getLength() const { return this->length; }
	long long* getArray() { return this->array; }
	void setLength(int);
	int gcd();
};
class POLYNOMIAL {
public:
	static int overloaded;
private:
	Array coef;
public:
	POLYNOMIAL();
	// POLYNOMIAL(POLYNOMIAL&, int);
	// POLYNOMIAL(int = 0);
	POLYNOMIAL(int, ...);
	POLYNOMIAL(const POLYNOMIAL&);
	// ~POLYNOMIAL();

	void* operator new (size_t);
	void operator delete (void*);
	POLYNOMIAL operator+(const POLYNOMIAL&);
	POLYNOMIAL operator-(const POLYNOMIAL&);
	POLYNOMIAL operator-();
	POLYNOMIAL& operator*=(const int);
	POLYNOMIAL operator*(const POLYNOMIAL&);
	POLYNOMIAL& operator/=(const int);
	POLYNOMIAL operator/(const POLYNOMIAL&);
	POLYNOMIAL operator%(const POLYNOMIAL&);
	POLYNOMIAL operator<<(int);
	POLYNOMIAL operator>>(int);
	POLYNOMIAL& operator=(const POLYNOMIAL&);
	POLYNOMIAL& operator*=(const POLYNOMIAL&);
	POLYNOMIAL& operator/=(const POLYNOMIAL&);
	POLYNOMIAL& operator%=(const POLYNOMIAL&);
	POLYNOMIAL& operator<<=(const POLYNOMIAL&);
	POLYNOMIAL& operator>>=(const POLYNOMIAL&);
	POLYNOMIAL& operator++();
	POLYNOMIAL operator++(int);
	POLYNOMIAL& operator--();
	POLYNOMIAL operator--(int);
	friend bool operator==(const POLYNOMIAL&, const POLYNOMIAL&);
	friend bool operator!=(const POLYNOMIAL&, const POLYNOMIAL&);
	friend bool operator<(const POLYNOMIAL&, const POLYNOMIAL&);
	friend bool operator<=(const POLYNOMIAL&, const POLYNOMIAL&);
	friend bool operator>(const POLYNOMIAL&, const POLYNOMIAL&);
	friend bool operator>=(const POLYNOMIAL&, const POLYNOMIAL&);
	friend std::ostream& operator<<(std::ostream&, const POLYNOMIAL&);
	friend std::istream& operator>>(std::istream&, POLYNOMIAL&);

private:
	bool isZero() const;
	int deg() const;
	int  getLength() const { return this->coef.getLength(); }
	void simplify();
	void removeTrailingZeroCoeffs();
	void fillArrWithVaArgs(const int, std::va_list, int*);
	void setLength(int length) { this->coef.setLength(length); }
	int lead() const;
};
int POLYNOMIAL::overloaded = 0;

Array::Array(const int length) : array(nullptr), length(length) {
	if (length <= 0) {
		this->length = 0;
		return;
	}
	this->array = new long long[length];
	for (size_t i = 0; i < length; i++) {
		this->array[i] = 0;
	}
}
Array::Array(int* const arr, const int length) : array(nullptr), length(length) {
	if (length <= 0) {
		this->length = 0;
		return;
	}

	this->array = new long long[length];
	for (size_t i = 0; i < length; i++) {
		this->array[i] = arr[i];
	}
}
Array::Array(const Array& source) {
	this->length = source.length;
	this->array = new long long[this->length];
	for (size_t i = 0; i < source.length; i++) {
		this->array[i] = source.array[i];
	}
}
Array::~Array() {
	if (this->array != NULL) {
		delete[] this->array;
	}
	this->array = NULL;
	this->length = 0;
}
Array& Array::operator=(const Array& source) {
	if (this == &source) {
		return *this;
	}
	if (this->array != nullptr) {
		delete[] this->array;
	}

	this->length = source.length;
	this->array = new long long[source.length];
	for (int i = 0; i < source.length; i++) {
		array[i] = source[i];
	}
}
long long& Array::operator[] (const int& i) const {
	if (i >= this->length) {
		throw std::out_of_range("Index out of bounds");
	}
	return this->array[i];
}
Array::Array(const int length, std::va_list& va_args) {
	this->length = length;
	this->array = new long long[length];
	for (size_t i = 0; i < length; i++) {
		array[i] = va_arg(va_args, int);
	}
}
void Array::setLength(int length) {
	if (length <= 0) {
		if (this->array != nullptr) {
			delete[] this->array;
		}
		array = nullptr;
		this->length = 0;
		return;
	}

	long long* newArr = new long long[length];
	int toCopy = Helpers::min(this->length, length);
	for (size_t i = 0; i < toCopy; i++) {
		newArr[i] = this->array[i];
	}
	for (size_t i = toCopy; i < length; i++) {
		newArr[i] = 0;
	}
	if (this->array != nullptr) {
		delete[] this->array;
	}
	this->array = newArr;
	this->length = length;
}
int Array::gcd() {
	return Helpers::gcd(this->array, this->length);
}
void Array::divideAllBy(const int num) {
	if (num == 0) {
		throw std::runtime_error("Division by zero");
	}
	if (num == 1) {
		return;
	}
	for (size_t i = 0; i < this->length; i++) {
		this->array[i] /= num;
	}
}

void fillArrWithVaArgs(const int length, std::va_list va_args, int* dest) {
	for (size_t i = 0; i < length; i++) {
		dest[i] = va_arg(va_args, int);
	}
}

bool POLYNOMIAL::isZero() const {
	POLYNOMIAL copy = *this;
	copy.removeTrailingZeroCoeffs();
	return copy.deg() == 0 && copy.coef[0] == 0;
}
int POLYNOMIAL::lead() const {
	POLYNOMIAL copy = *this;
	copy.removeTrailingZeroCoeffs();
	if (copy.getLength() < 1) {
		throw std::out_of_range("Invalid polynomial length");
	}
	return copy.coef[copy.deg()];
}
int POLYNOMIAL::deg() const {
	POLYNOMIAL copy = (*this);
	copy.removeTrailingZeroCoeffs();
	return Helpers::min(copy.getLength() - 1, 0);
}
void POLYNOMIAL::removeTrailingZeroCoeffs() {
	int newLength = this->coef.getLength();
	if (newLength == 0) {
		return;
	}
	while (newLength > 1 && this->coef[newLength - 1] == 0) {
		newLength--;
	}
	this->coef.setLength(newLength);
}

void POLYNOMIAL::simplify() {
	this->removeTrailingZeroCoeffs();

	int gcd = this->coef.gcd();
	if (gcd != 0) {
		this->operator/= (gcd);
	}
}
POLYNOMIAL::POLYNOMIAL() {
	this->coef = Array(1);
}
// POLYNOMIAL::POLYNOMIAL(POLYNOMIAL& dummy, int length) {
// 	if (length < 1) {
// 		length = 1;
// 	}
// 	this->coef = Array(length);
// }

POLYNOMIAL::POLYNOMIAL(int degree, ...) {
	std::va_list va_args;
	if (degree < 0) {
		degree = 0;
	}
	int length = degree + 1;
	va_start(va_args, length);
	this->coef = Array(length, va_args);
	va_end(va_args);
	this->simplify();
}

POLYNOMIAL::POLYNOMIAL(const POLYNOMIAL& source) {
	this->coef = Array(source.coef);
	this->simplify();
}

void* POLYNOMIAL::operator new (size_t amount) {
	overloaded++;
	return ::operator new (amount);
}

void POLYNOMIAL::operator delete (void* ptr) {
	overloaded--;
	::operator delete (ptr);
}

POLYNOMIAL POLYNOMIAL::operator+(const POLYNOMIAL& arg) {
	POLYNOMIAL p = (*this);
	POLYNOMIAL q = arg;
	p.simplify();
	q.simplify();
	int sizeP = p.getLength();
	int sizeQ = q.getLength();
	int sizeRes = Helpers::max(sizeP, sizeQ);

	POLYNOMIAL res = POLYNOMIAL();
	res.setLength(sizeRes);
	for (size_t i = 0; i < sizeRes; i++) {
		res.coef[i] = 0;
	}
	for (size_t i = 0; i < sizeP; i++) {
		res.coef[i] += p.coef[i];
	}
	for (size_t i = 0; i < sizeQ; i++) {
		res.coef[i] += q.coef[i];
	}
	res.simplify();
	return res;
}

POLYNOMIAL POLYNOMIAL::operator-(const POLYNOMIAL& arg) {
	POLYNOMIAL p = (*this);
	POLYNOMIAL q = arg;
	p.simplify();
	q.simplify();
	int sizeP = p.getLength();
	int sizeQ = q.getLength();
	int sizeRes = Helpers::max(sizeP, sizeQ);

	POLYNOMIAL res = POLYNOMIAL();
	res.setLength(sizeRes);
	for (size_t i = 0; i < sizeRes; i++) {
		res.coef[i] = 0;
	}
	for (size_t i = 0; i < sizeP; i++) {
		res.coef[i] += p.coef[i];
	}
	for (size_t i = 0; i < sizeQ; i++) {
		res.coef[i] -= q.coef[i];
	}
	res.simplify();
	return res;
}

POLYNOMIAL POLYNOMIAL::operator-() {
	int length = this->getLength();
	POLYNOMIAL res = POLYNOMIAL();
	res.setLength(length);

	for (size_t i = 0; i < length; i++) {
		res.coef[i] = -this->coef[i];
	}
	res.simplify();
	return res;
}

POLYNOMIAL& POLYNOMIAL::operator*=(const int scalar) {
	for (int i = 0, N = this->getLength(); i < N; i++) {
		this->coef[i] *= scalar;
	}
	return *this;
}

POLYNOMIAL& POLYNOMIAL::operator/=(const int scalar) {
	for (int i = 0, N = this->getLength(); i < N; i++) {
		this->coef[i] /= scalar;
	}
	return *this;
}

POLYNOMIAL POLYNOMIAL::operator*(const POLYNOMIAL& arg) {
	POLYNOMIAL p = (*this);
	POLYNOMIAL q = arg;
	p.simplify();
	q.simplify();
	int sizeP = p.getLength();
	int sizeQ = q.getLength();

	int newLength = sizeP + sizeQ - 1;
	POLYNOMIAL res = POLYNOMIAL();
	res.setLength(newLength);

	for (size_t i = 0; i < newLength; i++) {
		res.coef[i] = 0;
	}
	for (int i = 0; i < sizeP; i++) {
		for (int j = 0; j < sizeQ; j++) {
			res.coef[i + j] = this->coef[i] * q.coef[j];
		}
	}

	res.simplify();
	return res;

}

POLYNOMIAL POLYNOMIAL::operator/(const POLYNOMIAL& arg) {
	// [ ] TODO
	POLYNOMIAL p = *this;
	POLYNOMIAL q = arg;
	p.simplify();
	q.simplify();
	int sizeP = p.getLength();
	int sizeQ = q.getLength();
	if (q.isZero()) {
		return POLYNOMIAL();
	}
	if (p.deg() < q.deg()) {
		return POLYNOMIAL();
	}
	if (q.deg() == 0) {
		return this->coef[0] < 0 ? -(*this) : (*this);
	}
	POLYNOMIAL res = POLYNOMIAL();
	int sizeRes = (p.getLength() - q.getLength() + 1);
	res.setLength(sizeRes);

	POLYNOMIAL rem = p;

	while (rem.isZero() == false && rem.deg() >= q.deg()) {
		// int lcm = Helpers::lcm(q.lead(), rem.lead());
		// int val = Helpers::abs(lcm / rem.lead());
		// rem *= val;
		// res *= val;
		frac tmp = frac(rem.lead(), q.lead());
		POLYNOMIAL t = POLYNOMIAL();
		long long sizeT = rem.deg() - q.deg() + 1;
		t.setLength(sizeT);
		t.coef[sizeT - 1] = tmp.num();

		q *= tmp.den;
		rem *= tmp.den;

		q = q + t;
		rem = rem - (t * q);
	}












}

POLYNOMIAL POLYNOMIAL::operator%(const POLYNOMIAL&) {

}

POLYNOMIAL POLYNOMIAL::operator<<(int) {

}

POLYNOMIAL POLYNOMIAL::operator>>(int) {

}

POLYNOMIAL& POLYNOMIAL::operator=(const POLYNOMIAL&) {

}

POLYNOMIAL& POLYNOMIAL::operator*=(const POLYNOMIAL&) {

}

POLYNOMIAL& POLYNOMIAL::operator/=(const POLYNOMIAL&) {

}

POLYNOMIAL& POLYNOMIAL::operator%=(const POLYNOMIAL&) {

}

POLYNOMIAL& POLYNOMIAL::operator<<=(const POLYNOMIAL&) {

}

POLYNOMIAL& POLYNOMIAL::operator>>=(const POLYNOMIAL&) {

}

POLYNOMIAL& POLYNOMIAL::operator++() {

}

POLYNOMIAL POLYNOMIAL::operator++(int) {

}

POLYNOMIAL& POLYNOMIAL::operator--() {

}

POLYNOMIAL POLYNOMIAL::operator--(int) {

}

bool operator==(const POLYNOMIAL&, const POLYNOMIAL&) {

}

bool operator!=(const POLYNOMIAL&, const POLYNOMIAL&) {

}

bool operator<(const POLYNOMIAL&, const POLYNOMIAL&) {

}

bool operator<=(const POLYNOMIAL&, const POLYNOMIAL&) {

}

bool operator>(const POLYNOMIAL&, const POLYNOMIAL&) {

}

bool operator>=(const POLYNOMIAL&, const POLYNOMIAL&) {

}

std::ostream& operator<<(std::ostream&, const POLYNOMIAL&) {

}

std::istream& operator>>(std::istream&, POLYNOMIAL&) {

}



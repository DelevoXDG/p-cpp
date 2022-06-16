// Maksim Zdobnikau

#include <iostream>
#include <cstdarg>

#define nullptr 0
// [ ] uncomment this 

namespace Helpers {
	long long  abs(const long long  A) {
		return A < 0 ? -A : A;
	}
	long long min(const long long A, const long long B) {
		return A < B ? A : B;
	}
	long long max(const long long A, const long long B) {
		return A < B ? B : A;
	}
	long long gcd(const long long A, const long long B) {
		if (A == 0 || B == 0) {
			return A == 0 ? B : A;
		}
		long long num = abs(A);
		long long div = abs(B);

		while (div != 0) {
			long long rem = num % div;
			num = div;
			div = rem;
		}
		return num;
	}
	long long gcd(long long* arr, const long long length) {
		if (length == 0) {
			return 1;
		}
		int ans = arr[0];
		for (long long i = 1; i < length && ans != 1; i++) {
			ans = gcd(ans, arr[i]);
		}
		return ans;
	}
}

struct simpleFraction {
public:
	long long numberer;
	long long denominator;

	simpleFraction(const long long numberer, const long long den)
		: numberer(numberer), denominator(den) {
		this->simplify();
	}
	long long num() const {
		return this->numberer;
	}
	long long den() const {
		return this->denominator;
	}

private:
	void simplify(void) {
		long long gcd = Helpers::gcd(numberer, denominator);
		numberer /= gcd;
		denominator /= gcd;
	}
};

struct Array {
private:
	long long* array;
	long long length;
public:
	Array(const long long = 0);
	Array(long long* const, const long long);
	Array(const Array&);
	Array(const int, std::va_list&);
	~Array();

	long long& operator [] (const long long&) const;
	Array& operator =(const Array&);
	int getLength() const { return this->length; }
	long long* getArray() const { return this->array; }
	void setLength(const long long);
	long long gcd();
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
	POLYNOMIAL& operator+=(const long long);
	POLYNOMIAL& operator-=(const long long);
	POLYNOMIAL& operator*=(const long long);
	POLYNOMIAL& operator/=(const long long);
	POLYNOMIAL operator*(const POLYNOMIAL&);
	POLYNOMIAL operator/(const POLYNOMIAL&);
	POLYNOMIAL operator%(const POLYNOMIAL&);
	POLYNOMIAL operator<<(int);
	POLYNOMIAL operator>>(int);
	// POLYNOMIAL& operator=(const POLYNOMIAL&);
	POLYNOMIAL& operator+=(const POLYNOMIAL&);
	POLYNOMIAL& operator-=(const POLYNOMIAL&);
	POLYNOMIAL& operator*=(const POLYNOMIAL&);
	POLYNOMIAL& operator/=(const POLYNOMIAL&);
	POLYNOMIAL& operator%=(const POLYNOMIAL&);
	POLYNOMIAL& operator<<=(int);
	POLYNOMIAL& operator>>=(int);
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
	// POLYNOMIAL div(const POLYNOMIAL&, POLYNOMIAL&, POLYNOMIAL&);
	POLYNOMIAL add(const POLYNOMIAL&);
	POLYNOMIAL sub(const POLYNOMIAL&);
	POLYNOMIAL mult(const POLYNOMIAL&);
	bool isZero() const;
	int deg() const;
	int  getLength() const { return this->coef.getLength(); }
	void simplify();
	void removeTrailingZeroCoeffs();
	void setLength(int length) { this->coef.setLength(length); }
	int lead() const;
	long long& operator[](const long long i) { return this->coef[i]; }
};

int POLYNOMIAL::overloaded = 0;
// []

Array::Array(const long long length) : array(nullptr), length(length) {
	if (length <= 0) {
		this->length = 0;
		if (this->array != nullptr) {
			delete[] this->array;
		}
		return;
	}
	this->array = new long long[length];
	for (long long i = 0; i < length; i++) {
		this->array[i] = 0;
	}
}

Array::Array(long long* const arr, const long long length) : array(nullptr), length(length) {
	if (length <= 0) {
		this->length = 0;
		if (this->array != nullptr) {
			delete[] this->array;
		}
		return;
	}

	this->array = new long long[length];
	for (long long i = 0; i < length; i++) {
		this->array[i] = arr[i];
	}
}

Array::Array(const Array& source) {
	this->length = source.length;
	this->array = new long long[this->length];
	for (long long i = 0; i < source.length; i++) {
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
	if (this != &source) {
		if (this->array != nullptr) {
			delete[] this->array;
		}

		this->length = source.length;
		this->array = new long long[source.length];
		for (long long i = 0; i < source.length; i++) {
			array[i] = source[i];
		}
	}
	return *this;
}

long long& Array::operator[] (const long long& i) const {
	if (i >= this->length) {
		throw std::out_of_range("Index out of bounds");
	}
	return this->array[i];
}Array::Array(const int length, std::va_list& va_args) {
	this->length = length;
	this->array = new long long[length];
	for (long long i = 0; i < length; i++) {
		array[i] = va_arg(va_args, int);
	}
}

void Array::setLength(const long long length) {
	if (length <= 0) {
		this->length = 0;
		if (this->array != nullptr) {
			delete[] this->array;
		}
		this->array = nullptr;
		return;
	}

	long long* newArr = new long long[length];
	int toCopy = Helpers::min(this->length, length);
	for (long long i = 0; i < toCopy; i++) {
		newArr[i] = this->array[i];
	}
	for (long long i = toCopy; i < length; i++) {
		newArr[i] = 0;
	}
	if (this->array != nullptr) {
		delete[] this->array;
	}
	this->array = newArr;
	this->length = length;
}

long long Array::gcd() {
	return Helpers::gcd(this->array, this->length);
}
bool POLYNOMIAL::isZero() const {
	POLYNOMIAL copy = *this;
	copy.removeTrailingZeroCoeffs();
	// return copy.deg() == 0 && copy.coef[0] == 0;
	return copy == POLYNOMIAL();
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
	return Helpers::max(copy.getLength() - 1, 0);
}

void POLYNOMIAL::removeTrailingZeroCoeffs() {
	int newLen = this->coef.getLength();
	if (newLen <= 1) {
		return;
	}
	while (newLen > 1 && this->coef[newLen - 1] == 0) {
		newLen--;
	}
	this->coef.setLength(newLen);
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

POLYNOMIAL::POLYNOMIAL(int deg, ...) {
	std::va_list va_args;
	if (deg < 0) {
		deg = 0;
	}
	int length = deg + 1;
	va_start(va_args, length);
	this->coef = Array(length, va_args);
	va_end(va_args);
	this->simplify();
}

POLYNOMIAL::POLYNOMIAL(const POLYNOMIAL& source) {
	this->coef = source.coef;
	// this->simplify();
}

void* POLYNOMIAL::operator new (size_t amount) {
	overloaded++;
	return ::operator new (amount);
}

void POLYNOMIAL::operator delete (void* ptr) {
	overloaded--;
	::operator delete (ptr);
}

POLYNOMIAL POLYNOMIAL::add(const POLYNOMIAL& arg) {
	POLYNOMIAL p = (*this);
	POLYNOMIAL q = arg;
	long long lenP = p.getLength();
	long long lenQ = q.getLength();
	long long lenR = Helpers::max(lenP, lenQ);

	POLYNOMIAL res = POLYNOMIAL();
	res.setLength(lenR);
	for (long long i = 0; i < lenR; i++) {
		res.coef[i] = 0;
	}
	for (long long i = 0; i < lenP; i++) {
		// std::cout << p.coef[i] << std::endl;
		res.coef[i] += p.coef[i];
	}
	for (long long i = 0; i < lenQ; i++) {
		// std::cout << q.coef[i] << std::endl;
		res.coef[i] += q.coef[i];
	}
	return res;
}

POLYNOMIAL POLYNOMIAL::sub(const POLYNOMIAL& arg) {
	POLYNOMIAL p = (*this);
	POLYNOMIAL q = arg;
	long long lenP = p.getLength();
	long long lenQ = q.getLength();
	long long lenR = Helpers::max(lenP, lenQ);

	POLYNOMIAL res = POLYNOMIAL();
	res.setLength(lenR);
	for (long long i = 0; i < lenR; i++) {
		res.coef[i] = 0;
	}
	for (long long i = 0; i < lenP; i++) {
		res.coef[i] += p.coef[i];
	}
	for (long long i = 0; i < lenQ; i++) {
		res.coef[i] -= q.coef[i];
	}
	return res;
}

POLYNOMIAL POLYNOMIAL::mult(const POLYNOMIAL& arg) {
	POLYNOMIAL p = (*this);
	POLYNOMIAL q = arg;
	long long lenP = p.getLength();
	long long lenQ = q.getLength();
	long long lenR = lenP + lenQ - 1;
	POLYNOMIAL res = POLYNOMIAL();
	res.setLength(lenR);

	for (long long i = 0; i < lenR; i++) {
		res.coef[i] = 0;
	}
	for (long long i = 0; i < lenP; i++) {
		for (long long j = 0; j < lenQ; j++) {
			res.coef[i + j] = this->coef[i] * q.coef[j];
		}
	}

	return res;
}

POLYNOMIAL POLYNOMIAL::operator+(const POLYNOMIAL& arg) {
	POLYNOMIAL p = (*this);
	POLYNOMIAL q = arg;
	p.simplify();
	q.simplify();
	long long lenP = p.getLength();
	long long lenQ = q.getLength();
	long long lenR = Helpers::max(lenP, lenQ);

	POLYNOMIAL res = POLYNOMIAL();
	res.setLength(lenR);
	for (long long i = 0; i < lenR; i++) {
		res.coef[i] = 0;
	}
	for (long long i = 0; i < lenP; i++) {
		res.coef[i] += p.coef[i];
	}
	for (long long i = 0; i < lenQ; i++) {
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
	long long lenP = p.getLength();
	long long lenQ = q.getLength();
	long long lenR = Helpers::max(lenP, lenQ);

	POLYNOMIAL res = POLYNOMIAL();
	res.setLength(lenR);
	for (long long i = 0; i < lenR; i++) {
		res.coef[i] = 0;
	}
	for (long long i = 0; i < lenP; i++) {
		res.coef[i] += p.coef[i];
	}
	for (long long i = 0; i < lenQ; i++) {
		res.coef[i] -= q.coef[i];
	}
	res.simplify();
	return res;
}

POLYNOMIAL POLYNOMIAL::operator-() {
	int length = this->getLength();
	POLYNOMIAL res = POLYNOMIAL();
	res.setLength(length);

	for (long long i = 0; i < length; i++) {
		res.coef[i] = -this->coef[i];
	}
	res.simplify();
	return res;
}

POLYNOMIAL& POLYNOMIAL::operator*=(const long long scalar) {
	if (scalar == 1) {
		return *this;
	}
	for (long long i = 0, N = this->getLength(); i < N; i++) {
		this->coef[i] *= scalar;
	}
	return *this;
}

POLYNOMIAL& POLYNOMIAL::operator/=(const long long scalar) {
	if (scalar == 0) {
		throw std::runtime_error("Divison by zero");
	}
	if (scalar == 1) {
		return *this;
	}
	for (long long i = 0, N = this->getLength(); i < N; i++) {
		this->coef[i] /= scalar;
	}
	return *this;
}

POLYNOMIAL& POLYNOMIAL::operator+=(const long long delta) {
	if (delta == 0) {
		return *this;
	}
	for (long long i = 0, N = this->getLength(); i < N; i++) {
		this->coef[i] += delta;
	}
	return *this;
}

POLYNOMIAL& POLYNOMIAL::operator-=(const long long delta) {
	if (delta == 0) {
		return *this;
	}
	for (long long i = 0, N = this->getLength(); i < N; i++) {
		this->coef[i] += delta;
	}
	return *this;
}

POLYNOMIAL POLYNOMIAL::operator*(const POLYNOMIAL& arg) {
	POLYNOMIAL p = (*this);
	POLYNOMIAL q = arg;
	p.simplify();
	q.simplify();
	long long lenP = p.getLength();
	long long lenQ = q.getLength();
	long long  lenR = lenP + lenQ - 1;

	POLYNOMIAL res = POLYNOMIAL();
	res.setLength(lenR);

	for (long long i = 0; i < lenR; i++) {
		res.coef[i] = 0;
	}
	for (long long i = 0; i < lenP; i++) {
		for (long long j = 0; j < lenQ; j++) {
			res.coef[i + j] = this->coef[i] * q.coef[j];
		}
	}

	res.simplify();
	return res;
}

// POLYNOMIAL POLYNOMIAL::div(const POLYNOMIAL& arg, POLYNOMIAL& res, POLYNOMIAL& r)

POLYNOMIAL POLYNOMIAL::operator/(const POLYNOMIAL& arg) {
	POLYNOMIAL p = *this;
	POLYNOMIAL div = arg;
	p.simplify();
	div.simplify();

	if (div.isZero()) {
		return POLYNOMIAL();
	}
	if (p.deg() < div.deg()) {
		return POLYNOMIAL();
	}
	if (div.deg() == 0) {
		return this->coef[0] < 0 ? -(*this) : (*this);
	}
	POLYNOMIAL q = POLYNOMIAL();
	POLYNOMIAL rem = p;

	while (rem.isZero() == false && rem.deg() >= div.deg()) {
		simpleFraction tmp = simpleFraction(rem.lead(), div.lead());

		POLYNOMIAL t = POLYNOMIAL();
		long long lenT = rem.deg() - div.deg() + 1;
		t.setLength(lenT);
		t.coef[lenT - 1] = tmp.num();

		q *= tmp.den();
		rem *= tmp.den();
		// std::cout << t << std::endl;
		// std::cout << q << std::endl;
		// std::cout << rem << std::endl;

		q = q.add(t);
		// std::cout << q << std::endl;
		q.removeTrailingZeroCoeffs();
		// std::cout << q << std::endl;

		rem = rem.sub(t.mult(div));
		// std::cout << rem << std::endl;
		rem.removeTrailingZeroCoeffs();
		// std::cout << rem << std::endl;
	}
	q.simplify();
	return q;
}

POLYNOMIAL POLYNOMIAL::operator%(const POLYNOMIAL& arg) {
	POLYNOMIAL p = *this;
	POLYNOMIAL div = arg;
	p.simplify();
	div.simplify();
	if (div.isZero()) {
		return POLYNOMIAL();
	}
	if (p.deg() < div.deg()) {
		return POLYNOMIAL();
	}
	if (div.deg() == 0) {
		return this->coef[0] < 0 ? -(*this) : (*this);
	}
	POLYNOMIAL q = POLYNOMIAL();
	POLYNOMIAL rem = p;
	while (rem.isZero() == false && rem.deg() >= div.deg()) {

		simpleFraction tmp = simpleFraction(rem.lead(), div.lead());

		POLYNOMIAL t = POLYNOMIAL();
		long long lenT = rem.deg() - div.deg() + 1;
		t.setLength(lenT);
		t.coef[lenT - 1] = tmp.num();

		q *= tmp.den();
		rem *= tmp.den();

		q = q.add(t);
		q.removeTrailingZeroCoeffs();

		rem = rem.sub(t.mult(div));
		rem.removeTrailingZeroCoeffs();
	}
	rem.simplify();
	return rem;
}

POLYNOMIAL POLYNOMIAL::operator<<(int shift) {
	if (shift < 0) {
		return POLYNOMIAL();
	}
	if (shift > this->deg()) {
		return POLYNOMIAL();
	}
	POLYNOMIAL res = *this;
	res.simplify();
	if (shift == 0) {
		return res;
	}

	long long oldLen = this->getLength();
	long long newLen = oldLen - shift;

	for (long long i = 0; i < newLen; i++) {
		res[i] = res[i + shift];
	}
	for (long long i = newLen; i < oldLen; i++) {
		res[i] = 0;
	}
	res.simplify();
	return res;
}

POLYNOMIAL POLYNOMIAL::operator>>(int shift) {
	if (shift < 0) {
		return POLYNOMIAL();
	}
	if (this -> isZero()) {
		return POLYNOMIAL();
	}
	POLYNOMIAL res = *this;
	res.simplify();
	if (shift == 0) {
		return res;
	}
	long long oldLen = this->getLength();
	long long newLen = oldLen + shift;

	res.setLength(newLen);

	for (long long i = shift; i < newLen; i++) {
		res[i] = res[i - shift];
	}
	for (long long i = 0; i < shift; i++) {
		res[i] = 0;
	}
	res.simplify();
	return res;
}

// POLYNOMIAL& POLYNOMIAL::operator=(const POLYNOMIAL&) {

// }

POLYNOMIAL& POLYNOMIAL::operator*=(const POLYNOMIAL& q) {
	*this = *this * q;
	return *this;
}

POLYNOMIAL& POLYNOMIAL::operator/=(const POLYNOMIAL& q) {
	*this = *this / q;
	return *this;
}

POLYNOMIAL& POLYNOMIAL::operator%=(const POLYNOMIAL& q) {
	*this = *this % q;
	return *this;
}

POLYNOMIAL& POLYNOMIAL::operator<<=(int shift) {
	*this = *this << shift;
	return *this;
}

POLYNOMIAL& POLYNOMIAL::operator>>=(int shift) {
	*this = *this >> shift;
	return *this;
}

POLYNOMIAL& POLYNOMIAL::operator++() {
	this->simplify();
	*this += 1;
	this->simplify();
	return *this;
}

POLYNOMIAL POLYNOMIAL::operator++(int) {
	this->simplify();
	POLYNOMIAL res = *this;
	*this += 1;
	this->simplify();
	return res;
}

POLYNOMIAL& POLYNOMIAL::operator--() {
	this->simplify();
	*this -= 1;
	this->simplify();
	return *this;
}

POLYNOMIAL POLYNOMIAL::operator--(int) {
	this->simplify();
	POLYNOMIAL res = *this;
	*this -= 1;

	this->simplify();
	return res;
}

bool operator==(const POLYNOMIAL& w1, const POLYNOMIAL& w2) {
	POLYNOMIAL p = w1;
	POLYNOMIAL q = w2;
	p.simplify();
	q.simplify();
	long long lenP = p.getLength();
	long long lenQ = q.getLength();
	if (lenP != lenQ) {
		return false;
	}
	for (long long i = lenP - 1; i >= 0; i--) {
		if (p[i] != q[i]) {
			return false;
		}
	}
	return true;
}

bool operator!=(const POLYNOMIAL& p, const POLYNOMIAL& q) {
	return (p == q) == false;
}

bool operator<(const POLYNOMIAL& w1, const POLYNOMIAL& w2) {
	POLYNOMIAL p = w1;
	POLYNOMIAL q = w2;
	p.simplify();
	q.simplify();
	long long lenP = p.getLength();
	long long lenQ = q.getLength();
	if (lenP != lenQ) {
		return lenP < lenQ;
	}
	for (long long i = lenP - 1; i >= 0; i--) {
		if (p[i] != q[i]) {
			return p[i] < q[i];
		}
	}
	return false;
}

bool operator<=(const POLYNOMIAL& p, const POLYNOMIAL& q) {
	if (p != q) {
		return p < q;
	}
	return true;
}

bool operator>(const POLYNOMIAL& p, const POLYNOMIAL& q) {
	return q < p;
}

bool operator>=(const POLYNOMIAL& p, const POLYNOMIAL& q) {
	return q <= p;
}

std::ostream& operator<<(std::ostream& os, const POLYNOMIAL& p) {
	POLYNOMIAL copy = p;
	copy.simplify();
	os << "( " << copy[0];
	for (long long i = 1; i < copy.getLength(); i++) {
		os << ", " << copy[i];
	}
	os << " ) ";
	return os;
}


std::istream& operator>>(std::istream& is, POLYNOMIAL& p) {
	int deg = 0;
	std::cin >> deg;

	p = POLYNOMIAL();
	if (deg < 0) {
		for (long long i = 0; i < deg; i++) {
			int dummy = 0;
			std::cin >> dummy;
		}
		return is;
	}
	p.setLength(deg + 1);
	for (long long i = 0; i < deg + 1; i++) {
		std::cin >> p[i];
	}

	p.simplify();

	return is;
}



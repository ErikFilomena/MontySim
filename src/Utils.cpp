#include "Utils.h"

void BaseExpansion(size_t* digits, size_t n, size_t base, size_t len) {
	while (n > 0) {
		*digits = n % base;
		n /= base;
		digits++;
		len--;
	}
	while (len > 0) {
		*digits = 0;
		digits++;
		len--;
	}
}

//Computes a^b mod p without overflow
int PowMod(int a, int b, int p) {
	if (b == 0)return 1;
	if (b == 1)return a % p;
	b--;
	int temp = a % p;
	a = a % p;
	while (b > 0) {
		temp = (temp * a) % p;
		b--;
	}
	return temp;
}

//Computes a^b
int Pow(int a, int b) {
	if (b == 0)return 1;
	if (b == 1)return a;
	b--;
	int temp = a;
	while (b > 0) {
		temp = (temp * a);
		b--;
	}
	return temp;
}


template double NumberFromDigits<double>(size_t* digits, size_t base, size_t len);
template float NumberFromDigits<float>(size_t* digits, size_t base, size_t len);

template <class NBR>
NBR NumberFromDigits(size_t* digits, size_t base, size_t len) {
	NBR b = 1 / (NBR)base;
	NBR result = 0;
	for (size_t i = 0; i < len; i++) {
		result += digits[i] * b;
		b /= base;
	}
	return result;
}



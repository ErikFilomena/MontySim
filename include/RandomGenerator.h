#pragma once

#include "Generator.h"

#include <time.h>



template <class NBR>
struct RandomGenerator :Generator<NBR> {

	size_t dim;

	unsigned long long  seed1 = time(0);
	unsigned long long  seed2 = time(0);
	unsigned long long  seed3 = time(0);
	
	inline RandomGenerator(int dim) :dim(dim) { this->type = RNG; }
	virtual ~RandomGenerator() {}

	NBR GenRnd() {
		seed1 = LCGAsm(seed1, 40692, 1002523, 2147483399);
		seed2 = LCGAsm(seed2, 39373, 1002523, 2147483647);
		seed3 = LCGAsm(seed3, 40014, 1002523, 2147483563);
		size_t x = (seed2 - seed1 + seed3) % (2147483646);
		if (x > 0) {
			return (NBR)x / 2147483647;
		}
		else {
			return 0.99999999953;
		}
	}
	NBR GenRange(NBR a, NBR b) {
		seed1 = LCGAsm(seed1, 40692, 1002523, 2147483399);
		seed2 = LCGAsm(seed2, 39373, 1002523, 2147483647);
		seed3 = LCGAsm(seed3, 40014, 1002523, 2147483563);
		int x = (seed2 - seed1 + seed3) % (2147483646);
		if (x > 0) {
			return (b-a)*((NBR)x / 2147483647);
		}
		else {
			return (b - a) * 0.99999999953;
		}
	}

	void seed(unsigned long long s) {
		seed1 = s;
		seed2 = s;
		seed3 = s;
	}

	void GenerateSequence(NBR* dst, size_t len) {
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < dim; j++) {
				dst[i * dim + j] = GenRnd();
			}
		}
	}
	void GenerateRange(NBR* dst, size_t len, NBR a, NBR b) {
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < dim; j++) {
				dst[i * dim + j] = GenRange(a,b);
			}
		}
	}
	size_t GetDim() {
		return dim;
	}
};
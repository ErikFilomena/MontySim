#pragma once

//Code stolen from https://en.wikipedia.org/wiki/Mersenne_Twister

#include "Generator.h"


#define mar_a 0x9908B0DF
#define mar_w 32
#define mar_n 624
#define mar_r 31
#define mar_m 397
#define mar_u 11
#define mar_s 7
#define mar_t 15
#define mar_l 18
#define mar_b 0x9D2C5680
#define mar_c 0xEFC60000
#define mar_f 1812433253


void InitArray(unsigned int* x, unsigned int seed);

void twist(unsigned int* arr);

unsigned int NextMersenne(unsigned int* x, size_t k);

template <class NBR>
struct MersenneTwisterGenerator :Generator<NBR> {

	size_t dim;
	size_t k = 0;
	unsigned int x[mar_n];
	size_t _seed;

	MersenneTwisterGenerator(int dim, size_t seed);
	virtual ~MersenneTwisterGenerator() {}

	NBR GenRnd();

	NBR operator()();

	unsigned int operator()(int);

	NBR GenRange(NBR a, NBR b);

	void seed(unsigned long long s);

	void GenerateSequence(NBR* dst, size_t len);

	void GenerateRange(NBR* dst, size_t len, NBR a, NBR b);

	size_t GetDim();
};



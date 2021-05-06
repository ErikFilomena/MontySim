#include "Defines.h"

extern "C" size_t _stdcall LCGAsm(unsigned long long int x, unsigned int a, unsigned int c, unsigned int m);


size_t seed = GLOBAL_RNG_SEED;

size_t GlobalRNG() {
	seed = LCGAsm(seed, 40692, 1002523, 2147483399);
	return seed;
}
void GlobalRNGSeed(size_t s) {
	seed = s;
}

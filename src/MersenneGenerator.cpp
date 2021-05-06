#include "MersenneGenerator.h"

template class MersenneTwisterGenerator<double>;
template class MersenneTwisterGenerator<float>;

void InitArray(unsigned int* x, unsigned int seed) {
	x[0] = seed;
	for (int i = 1; i < mar_n; i++) {
		x[i] = (mar_f * (x[i - 1] ^ (x[i - 1] >> 30)) + i);
	}
}

void twist(unsigned int* arr) {
	for (size_t i = 0; i < mar_n; i++) {
		unsigned int x = (arr[i] & 0x80000000) + (arr[(i + 1) % mar_n] & 0x7FFFFFFF);
		if (x & 1) {
			x = x >> 1;
			x = x ^ mar_a;
		}
		else {
			x = x >> 1;
		}
		arr[i] = arr[(i + mar_m) % mar_n] ^ x;
	}
}

unsigned int NextMersenne(unsigned int* x, size_t k) {

	if (k % mar_n == 0) {
		twist(x);
	}
	unsigned int next = x[k % mar_n];
	next = next ^ (next >> mar_u);
	next = next ^ ((next << mar_s) & mar_b);
	next = next ^ ((next << mar_t) & mar_c);
	next = next ^ (next >> mar_l);

	return next;
}

template<class NBR>
inline MersenneTwisterGenerator<NBR>::MersenneTwisterGenerator(int dim, size_t seed) :dim(dim), _seed(seed) {
	InitArray(x, seed);
	this->gentype = RNG;
}

template<class NBR>
NBR MersenneTwisterGenerator<NBR>::GenRnd() {
	NBR temp = (NBR)NextMersenne(x, k) / 0xFFFFFFFF;
	k++;
	return temp;
}

template<class NBR>
NBR MersenneTwisterGenerator<NBR>::operator()() {
	NBR temp = (NBR)NextMersenne(x, k) / 0xFFFFFFFF;
	k++;
	return temp;
}

template<class NBR>
unsigned int MersenneTwisterGenerator<NBR>::operator()(int) {
	unsigned int temp = NextMersenne(x, k);
	k++;
	return temp;
}

template<class NBR>
NBR MersenneTwisterGenerator<NBR>::GenRange(NBR a, NBR b) {
	NBR temp = (NBR)NextMersenne(x, k) / 0xFFFFFFFF;
	k++;
	return (b - a) * temp;
}

template<class NBR>
void MersenneTwisterGenerator<NBR>::seed(unsigned long long s) {
	_seed = s;
	k = 0;
	InitArray(x, s);
}

template<class NBR>
void MersenneTwisterGenerator<NBR>::GenerateSequence(NBR* dst, size_t len) {
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < dim; j++) {
			dst[i * dim + j] = GenRnd();
		}
	}
}

template<class NBR>
void MersenneTwisterGenerator<NBR>::GenerateRange(NBR* dst, size_t len, NBR a, NBR b) {
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < dim; j++) {
			dst[i * dim + j] = GenRange(a, b);
		}
	}
}

template<class NBR>
size_t MersenneTwisterGenerator<NBR>::GetDim()
{
	return dim;
}

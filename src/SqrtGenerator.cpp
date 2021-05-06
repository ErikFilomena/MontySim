#include "SqrtGenerator.h"
#include "PrimeList.h"
#include <math.h>
#include <stdio.h>

template class SqrtGenerator<float>;
template class SqrtGenerator<double>;

inline float Floor(float a) { return floorf(a); }
inline float Floor(double a) { return floor(a); }

template<class NBR>
inline SqrtGenerator<NBR>::SqrtGenerator(size_t dim,bool shuffle):
	dim(dim),shuffle(shuffle)
{
	sqrts = new NBR[dim];
	for (size_t i = 0; i < dim; i++) {
		sqrts[i] = sqrt(BLPN[i]);
	}
}



template<class NBR>
SqrtGenerator<NBR>::~SqrtGenerator()
{
	if (sqrts)delete[] sqrts;
}

template<class NBR>
void SqrtGenerator<NBR>::GenerateSequence(NBR* dst, size_t len)
{
	
	if (shuffle) Shuffle();
	size_t modulus = 1000 * len;
	int i = 0;
#pragma omp parallel for
	for (i = 0; i < len; i++) {
		NBR n = (NBR)i + 1;
		for (size_t j = 0; j < dim; j++) {
			dst[i * dim + j] = n* sqrts[j] - (NBR)(size_t( n* sqrts[j]));
		}
	}
}

template<class NBR>
void SqrtGenerator<NBR>::Shuffle()
{
	for (size_t i = 0; i < dim; i++) {
		sqrts[i] = sqrt(BLPN[GlobalRNG() % PRIME_MAX]);
	}
}

template<class NBR>
size_t SqrtGenerator<NBR>::GetDim()
{
	return dim;
}

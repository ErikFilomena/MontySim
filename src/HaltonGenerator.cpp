#include "HaltonGenerator.h"
#include "PrimeList.h"
#include "Utils.h"

#include <omp.h>


extern const unsigned int BLPN[PRIME_MAX];

template class HaltonGenerator<float>;
template class HaltonGenerator<double>;


template<class NBR>
inline HaltonGenerator<NBR>::~HaltonGenerator()
{

	if (shufflers.size()) {
		for (size_t i = 0; i < shufflers.size(); i++)delete[] shufflers[i];
	}

}

template<class NBR>
inline HaltonGenerator<NBR>::HaltonGenerator(size_t dim) :dim(dim)
{
	this->gentype = LDS;
}

template<class NBR>
inline HaltonGenerator<NBR>::HaltonGenerator(size_t dim, bool shuffle, PermuterType type)
	: dim(dim), shuffle(shuffle), pertype(type)
{
	if (shuffle) {
		shufflers = SHUFLIST(dim);
		int i;
#pragma omp parallel for
		for (i = 0; i < dim; i++) {
			shufflers[i] = CreatePermuter<size_t>(type, BLPN[i]);
		}
	}

	this->gentype = LDS;
}

template<class NBR>
inline void HaltonGenerator<NBR>::Dim(size_t dim)
{
	this->dim = dim;
	if (shuffle) {
		if (shufflers.size()) {
			for (size_t i = 0; i < shufflers.size(); i++)delete[] shufflers[i];
		}
		shufflers = SHUFLIST(dim);
		int i;
#pragma omp parallel for
		for (i = 0; i < dim; i++) {
			shufflers[i] = (CreatePermuter<size_t>(pertype, BLPN[i]));
			shufflers[i]->Shuffle();
		}
	}
}

template<class NBR>
inline void HaltonGenerator<NBR>::GenerateSequence(NBR* dst, size_t len)
{
#pragma omp parallel
	{
		size_t** digits = new size_t * [dim];
		for (size_t i = 0; i < dim; i++) {
			size_t nDigits = FastLog(len, BLPN[i]);
			digits[i] = new size_t[nDigits + 1];
			*digits[i] = nDigits;
		}

		int i;
#pragma omp for
		for (i = 0; i < len; i++) {
			for (int j = 0; j < dim; j++) {
				BaseExpansion(digits[j] + 1, i + 1, BLPN[j], *digits[j]);
				if (shuffle)shufflers[j]->Permute(digits[j] + 1, *digits[j]);
				dst[i * dim + j] = NumberFromDigits<NBR>(digits[j] + 1, BLPN[j], *digits[j]);
			}
		}
		for (size_t i = 0; i < dim; i++) {
			delete[] digits[i];
		}
		delete[] digits;
	}
}

template<class NBR>
inline void HaltonGenerator<NBR>::Shuffle()
{
	if (shuffle) {
		for (size_t i = 0; i < shufflers.size(); i++) {
			shufflers[i]->Shuffle();
		}
	}
}

template<class NBR>
size_t HaltonGenerator<NBR>::GetDim()
{
	return dim;
}



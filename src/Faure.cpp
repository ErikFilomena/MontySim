#include "Faure.h"
#include "PrimeList.h"
#include <math.h>
#include "Utils.h"
#include "PrimeList.h"

#include <omp.h>

extern const unsigned int BLPN[PRIME_MAX];

template class FaureGenerator<float>;
template class FaureGenerator<double>;


template<class NBR>
inline FaureGenerator<NBR>::FaureGenerator(size_t dim, bool skip) :dim(dim) {
	const unsigned int* prime = BLPN;
	this->permute = permute;
	while (*prime < dim) prime++;
	base = *prime;
	if (skip) this->skip = Pow(base, 4) - 1;
	this->gentype = LDS;
}

template<class NBR>
FaureGenerator<NBR>::FaureGenerator(size_t dim, bool permute, PermuterType type, bool skip) :dim(dim) {
	const unsigned int* prime = BLPN;
	this->permute = permute;
	while (*prime < dim) prime++;
	base = *prime;
	if (skip) this->skip = Pow(base, 4) - 1;
	this->gentype = LDS;
	if (permute) {
		shufflers = SHUFLIST(dim);
		int i;
#pragma omp parallel for
		for (i = 0; i < dim; i++) {
			shufflers[i] = CreatePermuter<size_t>(type, base);
		}
	}
}



template<class NBR>
FaureGenerator<NBR>::~FaureGenerator() {
	if (shufflers.size()) {
		for (size_t i = 0; i < shufflers.size(); i++)delete[] shufflers[i];
	}
}

template<class NBR>
inline void FaureGenerator<NBR>::GenerateSequence(NBR* dst, size_t len)
{
	size_t newMaxNDigits = FastLog(len + skip, base);
	if (newMaxNDigits != maxNDigits) {
		maxNDigits = newMaxNDigits;
		generators = GENLIST(dim);
		generators[0] = UpperTriangularEye<int>(maxNDigits);
		generators[1] = UpperPascalMatrixModP<int>(maxNDigits, base);
		int k;
#pragma omp parallel for
		for (k = 2; k < dim; k++) {
			generators[k] = Pk(generators[1], k, base);
		}
	}
	if (permute)Shuffle();
	int i;
#pragma omp parallel
	{
		size_t* digits = (size_t*)_malloca(maxNDigits * sizeof(NBR));
		size_t* digitsDimCoord = (size_t*) _malloca(maxNDigits * sizeof(NBR));

#pragma omp for
		for (i = 0; i < len; i++) {
			BaseExpansion(digits, i + skip, base, maxNDigits);
			for (int j = 0; j < dim; j++) {
				if (j) {
					generators[j].LeftMatrixVecMulMod(digitsDimCoord, digits, maxNDigits, base);
				}
				else {
					for (int k = 0; k < maxNDigits; k++)digitsDimCoord[k] = digits[k];
				}
				if (permute)shufflers[j]->Permute(digitsDimCoord, maxNDigits);
				dst[i * dim + j] = FaureNumber<NBR>(digitsDimCoord, base, maxNDigits);
			}
		}

		_freea(digits);
		_freea(digitsDimCoord);
	}

}

template<class NBR>
void FaureGenerator<NBR>::Shuffle()
{
	if (!permute)return;
	int i;
#pragma omp parallel for
	for (i = 0; i < dim; i++) {
		shufflers[i]->Shuffle();
	}
}

template<class NBR>
size_t FaureGenerator<NBR>::GetDim()
{
	return dim;
}


template<class NBR>
inline void FaureGenerator<NBR>::GenerateSequenceApply(NBR* dst, size_t len, NBR(*f) (NBR*), 
	NBR* targetMean,NBR* targetVar)
{
	size_t newMaxNDigits = FastLog(len + skip, base);
	if (newMaxNDigits != maxNDigits) {
		maxNDigits = newMaxNDigits;
		generators = GENLIST(dim);
		generators[0] = UpperTriangularEye<int>(maxNDigits);
		generators[1] = UpperPascalMatrixModP<int>(maxNDigits, base);
		int k;
#pragma omp parallel for
		for (k = 2; k < dim; k++) {
			generators[k] = Pk(generators[1], k, base);
		}
	}
	if (permute)Shuffle();
	NBR globalMean=0;
	int i;
#pragma omp parallel
	{

		size_t* digits = (size_t*) _malloca(maxNDigits*sizeof(NBR));
		size_t* digitsDimCoord = (size_t*)_malloca(maxNDigits * sizeof(NBR));
		NBR localMean = 0;
		NBR localVar = 0;
		NBR feval;
		size_t index = omp_get_thread_num()*dim;
#pragma omp for private(feval)
		for (i = 0; i < len; i++) {
			BaseExpansion(digits, i + skip, base, maxNDigits);
			for (int j = 0; j < dim; j++) {
				if (j) {
					generators[j].LeftMatrixVecMulMod(digitsDimCoord, digits, maxNDigits, base);
				}
				else {
					for (int k = 0; k < maxNDigits; k++)digitsDimCoord[k] = digits[k];
				}
				if (permute)shufflers[j]->Permute(digitsDimCoord, maxNDigits);
				dst[index + j] = FaureNumber<NBR>(digitsDimCoord, base, maxNDigits);
				
			}
			feval = f(dst + index);
			localMean += feval;
		}
#pragma omp critical
		{
			globalMean += localMean;
		}
		_freea(digits);
		_freea(digitsDimCoord);
	}

	
	globalMean /= len;
	*targetMean = globalMean;

	

}

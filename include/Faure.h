#pragma once


#include <vector>
#include "LinearAlgebra.h"
#include "Permuter.h"
#include "Generator.h"

typedef std::vector<INTUTMATRIX> GENLIST;


inline INTUTMATRIX Pk(const INTUTMATRIX& src, size_t k, size_t p) {
	INTUTMATRIX pk = src;
	for (int j = 1; j < pk.n; j++) {
		for (int i = 0; i <j; i++) {
			int val = PowMod(k, j - i, p);
			pk.set(i, j, (val * pk(i, j))%p);
		}
	}
	return pk;
}

template <class NBR>
inline NBR FaureNumber(size_t* digits, size_t base, size_t len) {
	NBR faureNumber = 0;
	NBR baseInv = 1.0 / (double)base;
	for (size_t i = 0; i < len; i++) {
		faureNumber += baseInv * (double)(digits[i]);
		baseInv /= base;
	}
	return faureNumber;
}

/**
	* Faure Generator class
**/
template <class NBR>
struct FaureGenerator:Generator<NBR> {

	size_t dim;
	size_t maxNDigits=0;
	size_t base;
	GENLIST generators;
	int skip = 1;
	size_t lastK=1;
	bool permute = false;
	SHUFLIST shufflers;

	/**
	* Construtor for FaureGernerator 
	* @param base the base for the number expansion
	* @param dim dimension of the tuples the generator outputs
	* @param maxNDigits maximum number of digits to be used in the expansion
	**/

	FaureGenerator(size_t dim, bool skip = false);

	FaureGenerator(size_t dim, bool permute, PermuterType type, bool skip = false);

	virtual ~FaureGenerator();

	//Assume that dst is a row-major matrix with dimentions dim x len
	inline void GenerateSequence(NBR* dst, size_t len);
	inline void GenerateSequenceApply(NBR* dst, size_t len,NBR (*f) (NBR*), NBR* targetMean, NBR* targetVar);

	inline void Shuffle();

	size_t GetDim();
};

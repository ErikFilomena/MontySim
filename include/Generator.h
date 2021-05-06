#pragma once

#include "Defines.h"
#include "Utils.h"

enum GENTYPE {LDS,RNG};

/**
* Interface for RNG and LDS generators
**/
template <class NBR>
struct Generator{


	GENTYPE gentype;
	/**
	* Generates a sequence of random numbers or a low discrepancy sequence 
	* @param dst the destination block of memoy (must be of size len*sizeof(NBR) * dim)
	**/
	virtual void GenerateSequence(NBR* dst, size_t len) {};


	/**
	* Generates a sequence of random numbers or a low discrepancy sequence and applies it to f
	* @param dst the destination block of memoy (must be of size len*sizeof(NBR) * dim)
	**/
	virtual void GenerateSequenceApply(NBR* dst, size_t len, NBR(*f) (NBR*), NBR* targetMean, NBR* targetVar) {};

	/**
	* Generates a sequence of random numbers in a range LDS generators should not implement this
	* @param dst the destination block of memoy (must be of size len*sizeof(NBR) * dim)
	**/
	virtual void GenerateRange(NBR* dst, size_t len, NBR a, NBR b) {};
	/**
	* Generates a single random, number. LDS generators should not implement this
	**/
	virtual NBR GenRnd() {
		return 0;
	}

	/**
	* Generates a random tupple of the next number in a LDS
	**/
	//virtual void GenRnd(NBR* dst) = 0;

	/**
	* Generates a random tupple of the next number in a LDS; then applies f to it
	**/
	//virtual NBR GenRnd(NBR* dst, NBR (*f) (*NBR)) = 0;

	/**
	* Generates a single random, number in a range. LDS generators should not implement this
	**/
	virtual NBR GenRange(NBR a, NBR b) {
		return 0;
	}

	virtual size_t GetDim() {
		return 0;
	};

	virtual void Shuffle() {};

};
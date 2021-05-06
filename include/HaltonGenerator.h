#pragma once

#include "Generator.h"
#include <vector>
#include "Permuter.h"


template <class NBR>
struct HaltonGenerator :Generator<NBR> {

	size_t dim;
	bool shuffle = false;
	PermuterType pertype;
	SHUFLIST shufflers;

	~HaltonGenerator();

	HaltonGenerator(size_t dim);

	HaltonGenerator(size_t dim, bool shuffle, PermuterType type);
	
	void Dim(size_t dim);

	virtual void GenerateSequence(NBR* dst, size_t len);

	void Shuffle();

	size_t GetDim();
};





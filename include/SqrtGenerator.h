#pragma once
#include "Generator.h"
#include <omp.h>

template <class NBR>
struct SqrtGenerator :Generator<NBR> {

	size_t dim;
	bool shuffle =false;
	NBR* sqrts=nullptr;

	SqrtGenerator(size_t dim, bool shuffle =false);
	~SqrtGenerator();

	inline void GenerateSequence(NBR* dst, size_t len);

	inline void Shuffle();
	size_t GetDim();

};


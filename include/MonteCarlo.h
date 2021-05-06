#pragma once

#include "Generator.h"
#include "RowDenseMatrix.h"

template <class NBR>
struct MonteCarlo {


	size_t dim;
	NBR (*f) (NBR* x);
	Generator<NBR> *gen;
	NBR* _samples = nullptr;
	NBR* _simValues=nullptr;
	NBR mean;
	NBR var;
	RowDenseMatrixInterface<NBR> samples;
	RowDenseMatrixInterface<NBR> simValues;
	size_t lastSize = 0;

	MonteCarlo(size_t dim, NBR(*f) (NBR* x), Generator<NBR>* gen);

	virtual ~MonteCarlo();

	void Simulate(int n);

	void FastSim(int n);

	void ClearSims();

};


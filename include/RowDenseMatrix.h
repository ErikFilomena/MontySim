#pragma once

#include "Matrix.h"

template<class NBR>
struct RowDenseMatrix :BaseMatrix<NBR> {
	size_t n;
	size_t m;
	NBR* data = nullptr;

	RowDenseMatrix();
	RowDenseMatrix(size_t n, size_t m, NBR* data);

	NBR operator()(size_t i, size_t j);

	void set(size_t i, size_t j, NBR val);

	NBR* row(size_t i);

	NBR* col(size_t j);

};


template<class NBR>
struct RowDenseMatrixInterface :BaseMatrix<NBR> {
	size_t *n;
	size_t *m;
	NBR** data = nullptr;

	RowDenseMatrixInterface();
	RowDenseMatrixInterface(size_t *n, size_t *m, NBR** data);

	NBR operator()(size_t i, size_t j);

	void set(size_t i, size_t j, NBR val);

	NBR* row(size_t i);

	NBR* col(size_t j);

};

typedef RowDenseMatrix<int> INTMATRIX;

typedef RowDenseMatrix<NUMBER> MATRIX;

typedef RowDenseMatrix<int> INTMATRIX;


#pragma once

#include "Matrix.h"

template<class NBR>
struct UpperTringularMatrix :BaseMatrix<NBR> {
	size_t n;
	size_t m;
	NBR* data = nullptr;

	UpperTringularMatrix(size_t n) :n(n) {
		m = ((n + 1) * n) / 2;
		data = new NBR[m];
		memset(data, 0, sizeof(NBR) * m);
	}

	UpperTringularMatrix() {}

	UpperTringularMatrix(const UpperTringularMatrix<NBR>& src) {
		n = src.n;
		m = src.m;
		data = new NBR[m];
		memmove(data, src.data, sizeof(NBR) * m);
	}

	UpperTringularMatrix& operator=(const UpperTringularMatrix<NBR>& src) {
		if (&src == this)return *this;
		if (data)delete[] data;
		n = src.n;
		m = src.m;
		data = new NBR[m];
		memmove(data, src.data, sizeof(NBR) * m);
	}

	virtual ~UpperTringularMatrix() { delete[] data; }

	NBR operator()(size_t i, size_t j) {
		if (j > n) {
			throw MatrixException(4, __LINE__, "main.cpp");
		}
		else if (i > n) {
			throw MatrixException(3, __LINE__, "main.cpp");
		}
		if (j < i) {
			return 0;
		}
		else {
			size_t offset = 0;
			size_t row = n;
			for (int k = 0; k < i; k++) {
				offset += row;
				row--;
			}
			offset = offset + j - i;
			return data[offset];
		}
	};

	void set(size_t i, size_t j, NBR val) {
		if (j > n) {
			throw MatrixException(4, __LINE__, "main.cpp");
		}
		else if (i > n) {
			throw MatrixException(3, __LINE__, "main.cpp");
		}
		if (j < i) {
			throw MatrixException(0, __LINE__, "main.cpp");
			return;
		}
		size_t offset = 0;
		size_t row = n;
		for (size_t k = 0; k < i; k++) {
			offset += row;
			row--;
		}
		offset = offset + j - i;
		data[offset] = val;
	}

	NBR* col(size_t i) { return nullptr; }
	NBR* row(size_t j) { return nullptr; }

	template<class NBR2>
	void LeftMatrixVecMulMod(NBR2* dst, NBR2* src, size_t len, size_t p) {
		int i;
#pragma omp parallel for
		for (i = 0; i < n; i++) {
			int offset = ((n - i + n) * (i + 1)) / 2 - n + i;
			dst[i] = 0;
			for (int j = i; j < n; j++) {
				dst[i] += (data[offset + j - i] * src[j]);
			}
			dst[i] = dst[i] % p;
		}
	}

	template<class NBR2>
	int LeftMatrixVecMul(NBR2* dst, NBR2* src, size_t len) {
		int i;
#pragma omp parallel for
		for (i = 0; i < n; i++) {
			int offset = ((n - i + n) * (i + 1)) / 2 - n + i;
			dst[i] = 0;
			for (size_t j = i; j < n; j++) {
				dst[i] += (data[offset + j - i] * src[j]);
			}
		}
	}


};






//TYPEDEFS

typedef UpperTringularMatrix<int> INTUTMATRIX;

typedef UpperTringularMatrix<NUMBER> UTMATRIX;



//UTILITY FUNCS


template <class NBR>
inline UpperTringularMatrix<NBR> UpperPascalMatrixModP(size_t n, size_t p) {
	UpperTringularMatrix<NBR> P(n);
	for (int i = 0; i < n; i++) {
		P.set(0, i, 1);
		P.set(i, i, 1);
	}

	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int a = j * P(i, j - 1);
			a /= j - i;
			P.set(i, j, a);
		}
	}


	for (size_t i = n; i < P.m; i++) {
		P.data[i] = P.data[i] % p;
	}
	return P;
}

//Fills an ut eye 
template <class NBR>
inline UpperTringularMatrix<NBR> UpperTriangularEye(size_t n) {
	UpperTringularMatrix<NBR> P(n);
	memset(P.data, 0, P.m);
	for (int i = 0; i < n; i++) {
		P.set(i, i, 1);
	}
	return P;
}


template<class NBR>
struct LowerTringularMatrix :BaseMatrix<NBR> {
	size_t n;
	size_t m;
	NBR* data = nullptr;

	LowerTringularMatrix(size_t n) :n(n) {
		m = ((n + 1) * n) / 2;
		data = new NBR[m];
		memset(data, 0, sizeof(NBR) * m);
	}

	LowerTringularMatrix() {}

	LowerTringularMatrix(const LowerTringularMatrix<NBR>& src) {
		n = src.n;
		m = src.m;
		data = new NBR[m];
		memmove(data, src.data, sizeof(NBR) * m);
	}

	LowerTringularMatrix& operator=(const UpperTringularMatrix<NBR>& src) {
		if (&src == this)return *this;
		if (data)delete[] data;
		n = src.n;
		m = src.m;
		data = new NBR[m];
		memmove(data, src.data, sizeof(NBR) * m);
	}

	virtual ~LowerTringularMatrix() { delete[] data; }

	NBR operator()(size_t i, size_t j) {
		if (j > n) {
			throw MatrixException(4, __LINE__, "main.cpp");
		}
		else if (i > n) {
			throw MatrixException(3, __LINE__, "main.cpp");
		}
		if (j > i) {
			return 0;
		}
		else {
			size_t offset = 0;
			size_t row = 1;
			for (int k = 0; k < i; k++) {
				offset += row;
				row++;
			}
			offset = offset + j;
			return data[offset];
		}
	};

	void set(size_t i, size_t j, NBR val) {
		if (j > n) {
			throw MatrixException(4, __LINE__, "main.cpp");
		}
		else if (i > n) {
			throw MatrixException(3, __LINE__, "main.cpp");
		}
		if (j < i) {
			throw MatrixException(0, __LINE__, "main.cpp");
			return;
		}
		size_t offset = 0;
		size_t row = n;
		for (size_t k = 0; k < i; k++) {
			offset += row;
			row--;
		}
		offset = offset + j - i;
		data[offset] = val;
	}

	NBR* col(size_t i) { return nullptr; }
	NBR* row(size_t j) { return nullptr; }

};
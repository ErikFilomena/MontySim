#include "RowDenseMatrix.h"

template class RowDenseMatrix<size_t>;
template class RowDenseMatrix<int>;
template class RowDenseMatrix<_int64>;
template class RowDenseMatrix<float>;
template class RowDenseMatrix<double>;

template class RowDenseMatrixInterface<size_t>;
template class RowDenseMatrixInterface<int>;
template class RowDenseMatrixInterface<_int64>;
template class RowDenseMatrixInterface<float>;
template class RowDenseMatrixInterface<double>;

template<class NBR>
RowDenseMatrix<NBR>::RowDenseMatrix()
{
}

template <class NBR>
inline RowDenseMatrix<NBR>::RowDenseMatrix(size_t n, size_t m, NBR* data) :n(n), m(m), data(data) {}

template <class NBR>
inline NBR RowDenseMatrix<NBR>::operator()(size_t i, size_t j) {
	if (i >  n) throw MatrixException(3, __LINE__, "RowDenseMatrix");
	if (j >  m) throw MatrixException(4, __LINE__, "RowDenseMatrix");
	return data[i * m + j];
};

template <class NBR>
inline void RowDenseMatrix<NBR>::set(size_t i, size_t j, NBR val) {
	if (i >  n) throw MatrixException(3, __LINE__, "RowDenseMatrix");
	if (j >  m) throw MatrixException(4, __LINE__, "RowDenseMatrix");
	data[i * m + j] = val;
}

template <class NBR>
inline NBR* RowDenseMatrix<NBR>::row(size_t i) {
	if (i >  n) throw MatrixException(3, __LINE__, "RowDenseMatrix");
	return data + i * m;
}

template <class NBR>
inline NBR* RowDenseMatrix<NBR>::col(size_t j) { return nullptr; }


template<class NBR>
RowDenseMatrixInterface<NBR>::RowDenseMatrixInterface()
{
}

template<class NBR>
inline RowDenseMatrixInterface<NBR>::RowDenseMatrixInterface(size_t *n, size_t *m, NBR** data)
:n(n),m(m),data(data){}

template<class NBR>
NBR RowDenseMatrixInterface<NBR>::operator()(size_t i, size_t j)
{
	if (i > *n) throw MatrixException(3, __LINE__, "RowDenseMatrix");
	if (j > *m) throw MatrixException(4, __LINE__, "RowDenseMatrix");
	int  k = i * (*m) + j;
	return (*data)[k];
}

template<class NBR>
void RowDenseMatrixInterface<NBR>::set(size_t i, size_t j, NBR val)
{
	if (i > * n) throw MatrixException(3, __LINE__, "RowDenseMatrix");
	if (j > * m) throw MatrixException(4, __LINE__, "RowDenseMatrix");
	*data[i * *m + j] = val;
}

template<class NBR>
NBR* RowDenseMatrixInterface<NBR>::row(size_t i)
{
	if (i > * n) throw MatrixException(3, __LINE__, "RowDenseMatrix");
	return *data + i * *m;
}

template<class NBR>
NBR* RowDenseMatrixInterface<NBR>::col(size_t j)
{
	return nullptr;
}


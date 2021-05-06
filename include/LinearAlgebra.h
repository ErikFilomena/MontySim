#pragma once
#ifndef NUMBER
#define NUMBER double
#define DOUBLE_PRECISION_NUMBER
#endif

#include <intrin.h>

#ifdef DOUBLE_PRECISION_NUMBER
#define mmMult _mm256_mul_pd
#define loopInc 4
#else
#define mmMult _mm256_mul_ps
#define loopInc 8
#endif

#define mmNbr __m256

#include "Vector.h";

#include "Matrix.h";
#include "RowDenseMatrix.h"
#include "TriangularMatrix.h"

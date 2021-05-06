#include "Vector.h"

#include <omp.h>
#include <intrin.h>



double Dot(double* x, double* y, size_t len) {

	int n = len % 4;
	double result = 0.0;
	switch (n) {
	case 1:
		result += x[0] * y[0];
		break;
	case 2:
		result += x[0] * y[0] + x[1] * y[1];
		break;
	case 3:
		result += x[0] * y[0] + x[1] * y[1] + x[2] * y[2];
		break;
	default:
		break;
	}
#ifdef __AVX2__
#pragma omp parallel 
	{
		double localResult = 0;
#pragma omp for
		for (int i = n; i < len; i += 4) {
			__m256d _ymm0 = _mm256_mul_pd(_mm256_load_pd(x + i), _mm256_load_pd(y + i));
			__m128d _xmm0 = _mm_add_pd(_mm256_extractf128_pd(_ymm0, 0), _mm256_extractf128_pd(_ymm0, 1));
			localResult += _xmm0.m128d_f64[0] + _xmm0.m128d_f64[1];
		}

#pragma omp critical
		result += localResult;

	}
	return result;
#else
#pragma omp parallel 
	{
		double localResult = 0;
#pragma omp for
		for (int i = n; i < len; i += 4) {
			localResult += x[i] * y[i];
			localResult += x[i+1] * y[i+1];
			localResult += x[i+2] * y[i+2];
			localResult += x[i+3] * y[i+3];
		}

#pragma omp critical
		result += localResult;

	}
	return result;
#endif
}

float Dot(float* x, float* y, size_t len) {

	float result = 0;
	switch (len % 4) {
	case 1:
		result += x[0] * y[0];
		x++;
		y++;
		len--;
		break;
	case 2:
		result += x[0] * y[0] + x[1] * y[1];
		x += 2;
		y += 2;
		len -= 2;
		break;
	case 3:
		result += x[0] * y[0] + x[1] * y[1] + x[2]*y[2];
		x += 3;
		y += 3;
		len -= 3;
		break;
	default: 
		break;
	}
	result += sDotAsm(x, y, len);
	return result;
}

#pragma once
#include "Generator.h"
#include <math.h>
#include "Defines.h"

template <class NBR>
struct BoxMullerGenerator:Generator<NBR> {
	Generator<NBR> *gen;

	BoxMullerGenerator(Generator<NBR>* gen) :gen(gen) {}

	void GenerateSequence(NBR* dst, size_t len) {
		gen->GenerateSequence(dst, len);
		int i;
		size_t dim = gen->GetDim();
#pragma omp parallel for
		for (i = 0; i < len; i++) {
			double u1 = dst[i * dim];
			double u2 = dst[i * dim + 1];
			if (!u1) {
				u1 = (double)GlobalRNG() / GLOBAL_RNG_MAX;
			}
			if (!u2) {
				u2 = (double)GlobalRNG() / GLOBAL_RNG_MAX;
			}
			//printf("%f %f\n", dst[i * 2], dst[i * 2 + 1]);
			dst[i * 2] = sqrt(-2.0 * log(u1))*cos(6.28318530718*u2);
			dst[i * 2 + 1] = sqrt(-2.0 * log(u1)) * sin(6.28318530718 * u2);
			//printf("%f %f\n", dst[i * 2], dst[i * 2 + 1]);
		}
	}

};
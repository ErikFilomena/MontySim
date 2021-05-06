#include "MonteCarlo.h"

#include <omp.h>

template class MonteCarlo<double>;
template class MonteCarlo<float>;

template<class NBR>
inline MonteCarlo<NBR>::MonteCarlo(size_t dim, NBR(*f)(NBR* x), Generator<NBR>* gen) :dim(dim), f(f), gen(gen) {
	samples.n = &lastSize;
	samples.m = &(*this).dim;
	samples.data = &_samples;
	simValues.n = &lastSize;
	simValues.m = new size_t;
	*simValues.m = 1;
	simValues.data = &_simValues;
}

template<class NBR>
inline MonteCarlo<NBR>::~MonteCarlo() {
	if (_samples) delete[] _samples;
	if (_simValues) delete[] _simValues;
	delete simValues.m;
}

template<class NBR>
inline void MonteCarlo<NBR>::Simulate(int n) {
	if (n == 0) throw 0;
	if (n != lastSize) {
		if (_samples) delete[] _samples;
		if (_simValues) delete[] _simValues;
		_simValues = new NBR[n];
		_samples = new NBR[n * dim];
		lastSize = n;
	}
	gen->GenerateSequence(_samples, n);
	int i;
	NBR localMean = 0;
#pragma omp parallel for reduction(+:localMean)
	for (i = 0; i < n; i++) {
		_simValues[i] = f(_samples + i * dim);
		localMean += _simValues[i];
	}

	mean = localMean / n;
}

template<class NBR>
void MonteCarlo<NBR>::FastSim(int n)
{
	if (n == 0) throw 0;
	if (n >= lastSize) {
		if (_samples) {
			ClearSims();
		}
		_samples = new NBR[omp_get_max_threads() * dim];
	}
	
	lastSize = 0;
	
	gen->GenerateSequenceApply(_samples, n, f, &mean, &var);
}

template<class NBR>
void MonteCarlo<NBR>::ClearSims()
{
	if (_samples) delete[] _samples;
	_samples = nullptr;
	if (_simValues) delete[] _simValues;
	_simValues = nullptr;
	lastSize = 0;

}

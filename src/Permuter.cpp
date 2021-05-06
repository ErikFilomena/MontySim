#include "Permuter.h"
#include "Defines.h"
#include "Utils.h"
#include <omp.h>

#define per_rnd(b) GlobalRNG() %b



template class DigitPermuter<size_t>;
template class DigitPermuter<unsigned int>;
template class LDSDigitPermuter<size_t>;
template class LDSDigitPermuter<unsigned int>;

template <class INT>
Permuter<INT>* CreatePermuter(PermuterType type, size_t base) {
	switch (type) {
	case DGTPER:
		return new DigitPermuter<INT>(base);
	case RNDSHFT:
		return new RandomShifter<INT>(base);
	case LDSDGT:
		return new LDSDigitPermuter<INT>(base);
	default:
		return nullptr;
	}
}

template Permuter<size_t>* CreatePermuter<size_t>(PermuterType type, size_t base);
template Permuter<unsigned int>* CreatePermuter<unsigned int>(PermuterType type, size_t base);



template<class INT>
inline DigitPermuter<INT>::DigitPermuter(INT base) :base(base) {
	permuted = new INT[base];
	for (size_t i = 0; i < base; i++) {
		permuted[i] = i;
	}
}

template<class INT>
inline DigitPermuter<INT>::~DigitPermuter() {
	if (permuted)delete[] permuted;
}

template<class INT>
inline void DigitPermuter<INT>::Shuffle() {
	/*for (INT i =0 ; i < base; i++) {
		permuted[i] = per_rnd(base);
	}*/
	for (INT i = 0; i < base; i++) {
		INT i1 = per_rnd(base);
		INT i2 = per_rnd(base);
		INT temp = permuted[i1];
		permuted[i1] = permuted[i2];
		permuted[i2] = temp;
	}

}

template<class INT>
inline void DigitPermuter<INT>::Permute(INT* list, size_t len) {
	for (size_t i = 0; i < len; i++) {
		list[i] = permuted[list[i]];
	}
}



template<class INT>
inline LDSDigitPermuter<INT>::LDSDigitPermuter(INT base) :base(base)
{

	maxDigits = FastLog(0xFFFFFFFF,base);
	permuted = std::vector< std::vector<INT> >(maxDigits);
	for (size_t i = 0; i < maxDigits; i++) {
		permuted.push_back(std::vector<INT>());
		for (size_t j = 0; j < base; j++) {
			permuted[i].push_back(j);
		}
	}
}

template<class INT>
inline LDSDigitPermuter<INT>::~LDSDigitPermuter()
{
	//if (permuted)delete[] permuted;
}

template<class INT>
inline void LDSDigitPermuter<INT>::Shuffle()
{
	
	for (size_t i = 0; i < maxDigits; i++) {
		for (size_t j = 0; j < base; j++) {
			INT i1 = per_rnd(base);
			INT i2 = per_rnd(base);
			INT temp = permuted[i][i1];
			permuted[i][i1] = permuted[i][i2];
			permuted[i][i2] = temp;
		}
	}

}

template<class INT>
inline void LDSDigitPermuter<INT>::Permute(INT* list, size_t len)
{
	for (size_t i = 0; i < len; i++) {
		
		list[i] = permuted[i][list[i]];
	}
}

#pragma once

#include <stdlib.h>
#include <vector>



enum PermuterType { DGTPER, RNDSHFT, LDSDGT };

template <class INT>
struct Permuter {
	virtual void Shuffle() = 0;
	virtual void Permute(INT* list, size_t len) = 0;
};



template <class INT>
struct LDSDigitPermuter :Permuter<INT> {

	INT base;
	std::vector< std::vector<INT> > permuted;
	size_t maxDigits;

	LDSDigitPermuter(INT base);

	~LDSDigitPermuter();

	void Shuffle();

	void Permute(INT* list, size_t len);

};

template <class INT>
struct DigitPermuter :Permuter<INT> {

	INT base;
	INT* permuted = nullptr;

	DigitPermuter(INT base);

	~DigitPermuter();


	void Shuffle();

	void Permute(INT* list, size_t len);
};

template <class INT>
struct RandomShifter :Permuter<INT> {

	RandomShifter(size_t base) {}
	void Shuffle() {}
	void Permute(INT* list, size_t len) {}
};

template <class INT>
Permuter<INT>* CreatePermuter(PermuterType type, size_t base);

#define SHUFLIST std::vector< Permuter<size_t>* >


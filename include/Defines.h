#pragma once
#ifndef NUMBER
#define NUMBER double
#define DOUBLE_PRECISION_NUMBER
#endif

#ifndef GLOBAL_RNG_SEED
#define GLOBAL_RNG_SEED 1524343405
#endif

#define GLOBAL_RNG_MAX 2147483399


#include <stdlib.h>
size_t GlobalRNG();
void GlobalRNGSeed(size_t);
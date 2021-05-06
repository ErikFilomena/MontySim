#pragma once
#include "Defines.h"
/**
* BaseLinear congruential generator x_n+1 = ax_n + c ~ m
* @param x the seed
* @param a the multiplier
* @param c the constant
* @param m the modulator
**/
extern "C" size_t _stdcall LCGAsm(unsigned long long int x, unsigned int a, unsigned int c, unsigned int m);

extern "C" int FastLogasm(size_t base,size_t val);
#define FastLog(val,base) FastLogasm(base,val)

void BaseExpansion(size_t* digits, size_t n, size_t base, size_t len);


//Computes a^b mod p without overflow
int PowMod(int a, int b, int p);

//Computes a^b
int Pow(int a, int b);

template <class NBR>
NBR NumberFromDigits(size_t* digits, size_t base, size_t len);


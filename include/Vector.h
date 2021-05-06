 #pragma once

#include "LinearAlgebra.h"

//Declarations

extern "C" float sDotAsm(float* x, float* y, size_t len);
extern "C" float sDotAsmAvx(float* x, float* y, size_t len);


double Dot(double* x, double* y, size_t len);
float Dot(float* x, float* y, size_t len);

void Had(float* x, float* y, size_t len);

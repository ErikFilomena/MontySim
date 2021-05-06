#pragma once
#include <cstddef>
#include <exception>
#include <iostream>
#include <string.h>
#include <omp.h>
#include <stdio.h>
#include "Defines.h"


struct MatrixException : std::exception {
	int code = 0;
	int line;
	const char* file;
	MatrixException(int code, int line, const char* file) :code(code),line(line), file(file) {}
	virtual const char* what() const throw() {
		switch (code) {
		case 1:
			std::cout << "Exception code " << code << " See file " << file << " line " << line << std::endl;
			return "Wrong Dimensions in operation";
		case 2:
			std::cout << "row or column index out of bounds " << code << " See file " << file << " line " << line << std::endl;
			return "Out of bounds indices";
		case 3:
			std::cout << " " << code << " See file " << file << " line " << line << std::endl;
			return "row index out of bounds";
		case 4:
			std::cout << " " << code << " See file " << file << " line " << line << std::endl;
			return "col index out of bounds";
		default:
			return "Unkown Exception";
		}
	}
};

template <class NBR>
struct BaseMatrix {
	
	virtual NBR operator()(size_t i, size_t j) =0;
	virtual void set(size_t i, size_t j, NBR val) = 0;
	virtual NBR* col(size_t i)=0;
	virtual NBR* row(size_t j) =0;

};






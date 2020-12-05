#include "matrix.h"
#include <string>
#include <cmath>
#include <iostream>

// Parameterized constructor
matrix::matrix(unsigned int rows, unsigned int cols):rows(rows),cols(cols) 
{  
	if (rows < 1 || cols < 1)
	{
		throw std::runtime_error("Parameterized constructor: bad arguments");
	}
	the_matrix = new double*[rows];
	for(unsigned i = 0; i < rows; i++){
		the_matrix[i] = new double[cols];
		for(unsigned j = 0; j < cols; j++){
			the_matrix[i][j] = 0;
		}
	}
}

// Copy constructor
matrix::matrix(const matrix& from):rows(from.rows),cols(from.cols)
{
	the_matrix = new double*[rows];
	for(unsigned i = 0; i < rows; i++){
		the_matrix[i] = new double[cols];
		for(unsigned j = 0; j < cols; j++){
			this->the_matrix[i][j] = from.the_matrix[i][j];
		}
	}
}

// Destructor
matrix::~matrix()
{
	for(unsigned i = 0; i < rows; i++){
		delete[] the_matrix[i];
	}
	delete[] the_matrix;
}

// Assignment operator
matrix& matrix::operator=(const matrix& rhs)
{
	if(this != &rhs){
		this->~matrix();
		this->rows = rhs.rows;
		this->cols = rhs.cols;
		the_matrix = new double*[rows];
		for(unsigned i = 0; i < rows; i++){
			the_matrix[i] = new double[cols];
			for(unsigned j = 0; j < cols; j++){
				this->the_matrix[i][j] = rhs.the_matrix[i][j];
			}
		}
	}
	return *this;
}

// Named constructor (static)
matrix matrix::identity(unsigned int size)
{
	// use p-constructor
	matrix id = matrix(size,size);
	for(unsigned i = 0; i < size; i++){
		id.the_matrix[i][i] = 1;
	}
	return id;
}
/*
void matrix::printMatrix(){
	std::cout << " " << std::endl;
	for(unsigned i = 0; i < rows; i++){
		std::cout << "|";
		for(unsigned j = 0; j < cols; j++){
			std::cout << this->the_matrix[i][j];
		}
		std::cout << "|" << std::endl;
	}
	std::cout << " " << std::endl;
}
*/

#include "matrix.h"
#include <string>
#include <cmath>

mrow::mrow(unsigned int size, double* matrix_row):size(size), matrix_row(matrix_row){}

double& mrow::operator[](unsigned int col)
{
	if(col >= this->size || col < 0){
		throw std::runtime_error("Accessing Invalid Matrix Col. Index out of bounds!");
	}
	return matrix_row[col];
}

double mrow::operator[](unsigned int col) const
{
	if(col >= this->size || col < 0){
		throw std::runtime_error("Accessing Invalid Matrix Col. Index out of bounds!");
	}
	return matrix_row[col];
}

// Default Constructor
matrix::matrix():rows(0),cols(0){}

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
	if(!(rows == 0 && cols == 0)){
		for(unsigned i = 0; i < rows; i++){
			delete[] the_matrix[i];
		}
		delete[] the_matrix;
	}
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


// Binary operations
matrix matrix::operator+(const matrix& rhs) const
{
	if (this->rows == rhs.rows && this->cols == rhs.cols){
		matrix retVal(rhs);
		for(unsigned i = 0; i < this->rows; i++){
			for(unsigned j = 0; j < this->cols; j++){
				retVal.the_matrix[i][j] += this->the_matrix[i][j];
			}
		}
		return retVal;
	} else {
		throw std::runtime_error("Matrix Addition Exception. Dimensions Invalid!");
	}
	
	if(!(rows == 0 && cols == 0)){
		
	} else {
		throw std::runtime_error("Cannot Multiply 0 dimension matrices!");
	}
}


matrix matrix::operator*(const matrix& rhs) const
{
	if(!(rows == 0 && cols == 0)){
		if (this->cols == rhs.rows){
			matrix retVal = matrix(this->rows, rhs.cols);
			for(unsigned i = 0; i < this->rows; i++){
				for(unsigned j = 0; j < rhs.cols; j++){
					for(unsigned k = 0; k < this->cols; k++){
						retVal.the_matrix[i][j] = retVal.the_matrix[i][j] 
						+ (this->the_matrix[i][k] * rhs.the_matrix[k][j]);
					}
				}
			}
			return retVal;
		} else {
			throw std::runtime_error("Matrix Multiplication Exception. Dimensions Invalid!");
		}
	} else {
		throw std::runtime_error("Cannot Multiply 0 dimension matrices!");
	}
}

matrix matrix::operator*(const double scale) const
{
	if(!(rows == 0 && cols == 0)){
		matrix retVal = matrix(*this);
		for(unsigned i = 0; i < this->rows; i++){
			for(unsigned j = 0; j < this->cols; j++){
				retVal.the_matrix[i][j] *= scale;
			}
		}
		return retVal;
	} else {
		throw std::runtime_error("Cannot Scale 0 dimension matrices!");
	}
}


// Unary operations
matrix matrix::operator~() const
{
	if(!(rows == 0 && cols == 0)){
		matrix retVal = matrix(this->cols, this->rows);
		for(unsigned i = 0; i < this->rows; i++){
			for(unsigned j = 0; j < this->cols; j++){
				retVal.the_matrix[j][i] = this->the_matrix[i][j];
			}
		}
		return retVal;
	} else {
		throw std::runtime_error("Cannot transpose 0 dimension matrices!");
	}
}
	

void matrix::clear()
{
	if(!(rows == 0 && cols == 0)){
		for(unsigned i = 0; i < this->rows; i++){
			for(unsigned j = 0; j < this->cols; j++){
				this->the_matrix[j][i] = 0;
			}
		}
		return;
	} else {
		throw std::runtime_error("Cannot Clear 0 dimension matrices!");
	}
}

mrow matrix::operator[](unsigned int row)
{
	if(row >= this->rows || row < 0){
		throw std::runtime_error("Accessing Invalid Matrix Row. Index out of bounds!");
	}
	mrow retVal = mrow(this->cols, this->the_matrix[row]);
	return retVal;
}

mrow matrix::operator[](unsigned int row) const
{
	if(row >= this->rows || row < 0){
		throw std::runtime_error("Accessing Invalid Matrix Row. Index out of bounds!");
	}
	mrow retVal = mrow(this->cols, this->the_matrix[row]);
	return retVal;
}

std::ostream& matrix::out(std::ostream& os) const
{
	if(rows == 0 && cols == 0){
		os << "[[]]" << std::endl;
	} else {
		os << "[";
		for(unsigned i = 0; i < this->rows; i++){
			os<< "[ ";
			for(unsigned j = 0; j < this->cols; j++){
				if(j == this->cols-1)
					os << this->the_matrix[i][j];
				else
					os << this->the_matrix[i][j] << ", ";
			}
			if(i == this->rows-1)
				os << "]]" << std::endl;
			else
				os << "]" << std::endl;
		}
	}
	return os;
}


// Global insertion and operator
std::ostream& operator<<(std::ostream& os, const matrix& rhs)
{
	rhs.out(os);
	return os;
}

// Global scalar multiplication
matrix operator*(const double scale, const matrix& rhs)
{
	matrix result = rhs * scale;
	return result;
}



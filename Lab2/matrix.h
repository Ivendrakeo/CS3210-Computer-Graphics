/*
 * matrix.h - declaration of matrix class.  This class will be
 * capable of representing a Matrix as a first-class type.
 * 
 * Do not change any public methods in this file unless otherwise
 * instructed.
 *
 * For CS321.  (c) 2015 Dr. Darrin Rothe
 * 2020 Varnell
 */
 
 
// compile guard 
#ifndef MATRIX_H
#define MATRIX_H
 
#include <iostream> // for std::ostream
#include <stdexcept>	// for std::runtime_error
#include <string>	// used in exception
 
 
class matrix
{
	public:
		// No default (no argument) constructor.  It doesn't really make
		// sense to have one as we cannot rely on a size.  This could trip
		// us up later, but it will lead to a better implementation.
		// matrix();
 
		// Constructor - create Matrix and clear cells.  If rows or
		// cols is < 1, throw a runtime error.  
		//
		matrix(unsigned int rows, unsigned int cols);
 
		// Copy constructor - make a new Matrix just like rhs
		matrix(const matrix& from);
 
		// Destructor.  Free allocated memory
		~matrix();
 
		// Assignment operator - make this just like rhs.  Must function
                // correctly even if rhs is a different size than this.
		matrix& operator=(const matrix& rhs);
 
		// "Named" constructor(s).  This is not a language mechanism, rather
		// a common programming idiom.  The underlying issue is that with
		// overloaded operators, you can loose sight of what various
		// combinations of arguments means.  For our design, constructor
		// arguments set the size of the matrix.  If we want to generate
		// "special" matrices, we are better off with statuc methods that 
		// will generate these and then we can give the metods meaningful
		// names.
		
		// Named Constructor - produce a square identity matrix of the
		// requested size.  Since we do not know how the object produced will
		// be used, we pretty much have to return by value.  A size of 0 
		// would not make sense and should throw a runtime error.
		//
		static matrix identity(unsigned int size);
		
		//void printMatrix();
		
	private:

		double** the_matrix;
		unsigned int rows;
		unsigned int cols;


  };
#endif

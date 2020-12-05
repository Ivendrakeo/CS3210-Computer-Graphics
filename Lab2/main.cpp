#include "matrix.h"
#include <iostream>
 
using namespace std;

int main(void)
{
	// test our matrix, valgrind should not find 
        // any memory leaks
	
	matrix m1(3,3);
	//m1.printMatrix();
    matrix m2 = matrix::identity(3);
	//m2.printMatrix();
	matrix m3(1, 6);
	//m3.printMatrix();
	m1 = m3;
	//m1.printMatrix();
	matrix m4 = m3;
	//m4.printMatrix();
	matrix m5(m3);
	//m5.printMatrix();
	return 0;
}	

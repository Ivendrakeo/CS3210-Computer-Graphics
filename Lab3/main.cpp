#include "matrix.h"
#include <iostream>
 
using namespace std;

int main(void)
{
	// test our matrix
	
	matrix m1(3,3);
	
	cout << "m1 - should be all zeros" << endl;
	cout << m1 << endl;
	
	matrix m2 = matrix::identity(3);

	cout << "m2 - should be 3 x 3 identity matrix" << endl;
	cout << m2 << endl;

	matrix m3 = m1 + m2;

	cout << "m3 - should be 3 x 3 identity matrix" << endl;
	cout << m3 << endl;
	
	cout << "should be 1: " << m3[0][0] << endl;
	
	matrix m4(2,6);
	m4[0][0] = 7;
	m4[1][4] = 3;

	cout << "m4 - should be 2 x 6 matrix" << endl;
	cout << m4 << endl;
	
	matrix m5 = ~m4;
	
	cout << "m5 - should be m4 transposed" << endl;
	cout << m5 << endl;
	
	cout << "m4 - should remain unchanged" << endl;
	cout << m4 << endl;
	
	matrix m6 = m2 * 5.0;

	cout << "m6 - should now be scaled by 5" << endl;
	cout << m6 << endl;
	
	cout << "m2 - should remain the same" << endl;
	cout << m2 << endl;
	
	m2.clear();
	
	cout << "m2 - should be cleared" << endl;
	cout << m2 << endl;
	
	m6 = 5.0 * m6;
	
	cout << "m6 - should now be scaled by 5 more" << endl;
	cout << m6 << endl;
	

	
	return 0;
}		

#include "matrix.h"
#include "Shape.h"

// compile guard 
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream> // for std::ostream
#include <array> // c++ array template library
#include "matrix.h"
#include "ViewContext.h"

class Triangle: public Shape{ // public inheritance from shape
	
	private:
	
		// Maintains the verticies of the triangle
		std::array<matrix, 3> verticies;
		
		// Maintains the centerpoint of the triangle.
		matrix centerpoint;
	
	public:
	
		// Default constructor assigns all points to (0,0) and black color
		Triangle();

		// Triangle paramertized constructor
		// defines a tirangle between coordinates (x0,y0),(x1,y1),(x2,y2)
		// with color 'color'
		Triangle(int x0, int y0, int x1, int y1, int x2, int y2,
				 unsigned int color);

		// Triangle's copy constructor. 
		// deep copies the features of 'from' Triangle into this Triangle
		Triangle(const Triangle& from);

		// Operator overload to set rhs Tirangle to this.triangle
		Triangle& operator=(const Triangle& rhs);
		
		// Triangle destructor
		~Triangle();
		
		// Draws the line using the supplied graphics context
		void draw(GraphicsContext* gc, ViewContext vc);

		// Dumps the Tirangle properties to the provided ostream
		std::ostream& out(std::ostream& os) const;
		
		// Read and set Triangle properties form a provided istream
		std::istream& in(std::istream& is);
	
		// Makes and returns a deep copy of this Triangle object
		Shape* clone();
		
		// Shifts the triangle along the X,Y,Z plane
		void translocate(int xShift, int yShift, int zShift);
		
		// Rotates the triangle on the X,Y plane
		void rotate(int degrees);
		
		// Scales the triangle by the provided factor
		void scale(int factor);

		// convertes the triangle device points to model points
		void deviceToModel(ViewContext vc);
	
};

#endif

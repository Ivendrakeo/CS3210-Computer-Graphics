#include "matrix.h"
#include "Shape.h"

// compile guard 
#ifndef LINE_H
#define LINE_H

#include <iostream> // for std::ostream
#include "x11context.h"
#include "ViewContext.h"
#include <array> // c++ array template library

class Line: public Shape{ // public inheritance from shape
	
	private:
	
		// Maintains the starting and ending coordinates of this line
		std::array<matrix, 2> coordinates;
		
		// Maintains the centerpoint of the triangle.
		matrix centerpoint;
	
	public:
	
		//Default constructor with black line of zero length at (0,0)
		Line();

		// Line paramertized constructor
		// defines a line between coordinates (x0,y0),(x1,y1)
		// with color 'color'
		Line(int x0, int y0, int x1, int y1, unsigned int color);

		// Line's copy constructor. 
		// deep copies the features of 'from' line into this line
		Line(const Line& from);

		// Operator overload to set rhs Line to this.Line
		Line& operator=(const Line& rhs);
		
		// Line destructor
		~Line();
		
		// Draws the line using the supplied graphics context
		void draw(GraphicsContext* gc, ViewContext vc);

		// Dumps the Line properties to the provided ostream
		std::ostream& out(std::ostream& os) const;
		
		// Read and set Line properties form a provided istream
		std::istream& in(std::istream& is);
	
		// Makes and returns a deep copy of this Line object
		Shape* clone();
		
		// Shifts the Line along the X,Y,Z plane
		void translocate(int xShift, int yShift, int zShift);
		
		// Rotates the Line on the X,Y plane
		void rotate(int degrees);
		
		// Scales the Line by the provided factor
		void scale(int factor);

		// convertes the device line points to model points
		void deviceToModel(ViewContext vc);
	
};

#endif

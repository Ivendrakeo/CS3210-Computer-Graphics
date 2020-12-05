#include "matrix.h"
#include "x11context.h"
#include "ViewContext.h"
#include <iostream> // for std::ostream

// compile guard 
#ifndef SHAPE_H
#define SHAPE_H

class Shape{

	protected:

		// 24-bit hex colorcode for the shape
		unsigned int color;

		// Shape '=' operator overload
		// set's this shape's properties equal to rhs
		Shape& operator=(const Shape& rhs);
		
	public:

		// Shape default constructor
		// Set's the color to default 0x000000
		Shape();
		
		// Shape paramertized constructor. 
		// Takes in a color and set's the shape's color
		Shape(unsigned int color);
		
		// Shape copy constructor. 
		// deep copies the features of 'from' shape into this shape
		Shape(const Shape& from);
		
		// Shape destructor
		virtual ~Shape();
		
		
		// Pure virtual method which draws the child shape
		// must be overwritten by child class!
		virtual void draw(GraphicsContext* gc, ViewContext vc) = 0;
		
		// Dumps the Shape properties to the provided ostream
		virtual std::ostream& out(std::ostream& os) const;
		
		// Read and set shape properties form a provided istream
		virtual std::istream& in(std::istream& is);
		
		// Makes and returns a deep copy of this Shape object
		virtual Shape* clone() = 0;

		// converts a shape's device coordinates to model coordinates
		virtual void deviceToModel(ViewContext vc) = 0;
	
};

#endif

// compile guard 
#ifndef IMAGE_H
#define IMAGE_H

#include <iostream> // for std::ostream
#include "Shape.h"
#include "ViewContext.h"
#include "matrix.h"
#include <vector> // c++ array template library

class Image{ // public inheritance from shape
	
	private:
	
		// vector (array list) of all shapes associated with the image
		std::vector<Shape*> shapes;
	
	public:
	
		// Default constructor creating an image without shapes
		Image();
		
		// Copy constructor for copying an image
		Image(const Image &from);
		
		// Destructor which deletes all shapes associated with image
		~Image();
		
		// Image '=' operator overload
		// set's this Image's properties equal to rhs
		Image& operator=(const Image& rhs);
		
		// Add's a new shape to the image
		void add(Shape* shape, ViewContext vc);
	
		// Draws all of the shapes associated with the image
		void draw(GraphicsContext* gc, ViewContext vc);
		
		// Dumps all the Image shape properties to the provided ostream
		std::ostream& out(std::ostream& os) const;
		
		// Read and set all the Image shape properties form a provided istream
		std::istream& in(std::istream& is);

		// Removes the last inserted Shape from the image
		void remove_last();
		
		// removes all the shapes from the image
		void erase();
	
};

#endif

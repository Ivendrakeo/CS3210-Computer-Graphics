/* This is an abstract base class representing a generic graphics
 * context.  Most implementation specifics will need to be provided by
 * a concrete implementation.  See header file for specifics. */

#define _USE_MATH_DEFINES	// for M_PI
#include <cmath>	// for trig functions
#include "gcontext.h"	
#include <iostream>

/*
 * Destructor - does nothing
 */
GraphicsContext::~GraphicsContext()
{
	// nothing to do
	// here to insure subclasses handle destruction properly
}


/* This is a naive implementation that uses floating-point math
 * and "setPixel" which will need to be provided by the concrete
 * implementation.
 * 
 * Parameters:
 * 	x0, y0 - origin of line
 *  x1, y1 - end of line
 * 
 * Returns: void
 */
void GraphicsContext::drawLine(int x0, int y0, int x1, int y1)
{
	
	// find slope
	int dx = x1-x0;
	int dy = y1-y0;
	
	// make sure we actually have a line
	if (dx != 0 || dy !=0)
	{
		if(dx < 0){
			int tmp = x0;
			x0 = x1;
			x1 = tmp;
			tmp = y0;
			y0 = y1;
			y1 = tmp;
			dx = dx*-1;
			dy = dy*-1;
		}
		bool posdy = (dy>0);
		dy = posdy ? dy : dy*-1;
		if(dx > dy){
			std::cout << "im here" << std::endl;
			int d = 2*dy - dx;
			int y = y0;
			for(int x = x0; x < x1; x++){
				if(d < 0){
					d = d + 2*dy;
				} else {
					d = d + 2*dy - 2*dx;
					y = posdy ? y + 1 : y - 1;
				}
				setPixel(x,y);
			}
		} else {
			int d = 2*dx - dy;
			int x = x0;
			if(posdy){ 
				for(int y = y0; y < y1; y++){
					if(d < 0){
						d = d + 2*dx;
					} else {
						d = d + 2*dx - 2*dy;
						x = x + 1;
					}
					setPixel(x,y);
				}
			} else { // mirrior if dy is negative
				for(int y = y0; y > y1; y--){
					if(d < 0){
						d = d + 2*dx;
					} else {
						d = d + 2*dx - 2*dy;
						x = x + 1;
					}
					setPixel(x,y);
				}
			}
		}
	}
	return;
}



/* This is a naive implementation that uses floating-point math
 * and "setPixel" which will need to be provided by the concrete
 * implementation.
 * 
 * Parameters:
 * 	x0, y0 - origin/center of circle
 *  radius - radius of circle
 * 
 * Returns: void
 */
void GraphicsContext::drawCircle(int x0, int y0, unsigned int radius)
{
	int d = 1-radius;
	int y = radius;
	double duration = radius*sqrt(2)/2;
	for(int x = 0; x < duration; x++){
		if(d < 0){
			d = d + 2*x + 3;
		} else {
			d = d +2*x - 2*y + 5;
			y = y - 1;
		}
		setPixel(x0+x,y0+y);
		setPixel(x0+y,y0+x);
		setPixel(x0-x,y0-y);
		setPixel(x0-y,y0-x);
		setPixel(x0+x,y0-y);
		setPixel(x0+y,y0-x);
		setPixel(x0-x,y0+y);
		setPixel(x0-y,y0+x);
	}
	return;	
}

void GraphicsContext::endLoop()
{
	run = false;
}



#include "x11context.h"
#include "Shape.h"
#include <iostream> // for std::ostream

Shape& Shape::operator=(const Shape& rhs){
	if(this != &rhs){
		this->~Shape();
		this->color = rhs.color;
	}
	return *this;	
}

Shape::Shape(){
	this->color = 0x000000;
}
	
Shape::Shape(unsigned int color){
		this->color = color;
}

Shape::Shape(const Shape& from):color(from.color){}

Shape::~Shape(){} // nothing to destruct for now

std::ostream& Shape::out(std::ostream& os) const{
		os << color << std::endl;
}

std::istream& Shape::in(std::istream& is){
		is >> color;
}

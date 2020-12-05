#include "Triangle.h"
#include "matrix.h"
#include <sstream> 
#include "x11context.h"
#include <string> // string library
#include <iostream> // for std::ostream
#include "ViewContext.h"

Triangle::Triangle(){
	this->color = 0;
	this->verticies[0] = matrix(4,1);
	this->verticies[1] = matrix(4,1);
	this->verticies[2] = matrix(4,1);
	this->centerpoint = matrix(4,1);
}

Triangle::Triangle(int x0, int y0, int x1, int y1, int x2, int y2,
				 unsigned int color){
	this->color = color;
	this->verticies[0] = matrix(4,1);
	this->verticies[0][0][0] = x0;
	this->verticies[0][1][0] = y0;
	this->verticies[0][2][0] = 0;
	this->verticies[0][3][0] = 1;
	this->verticies[1] = matrix(4,1);
	this->verticies[1][0][0] = x1;
	this->verticies[1][1][0] = y1;
	this->verticies[1][2][0] = 0;
	this->verticies[1][3][0] = 1;
	this->verticies[2] = matrix(4,1);
	this->verticies[2][0][0] = x2;
	this->verticies[2][1][0] = y2;
	this->verticies[2][2][0] = 0;
	this->verticies[2][3][0] = 1;
	this->centerpoint = matrix(4,1);
	this->centerpoint[0][0] = (x2+x1+x0)/3;
	this->centerpoint[1][0] = (y2+y1+y0)/3;
	this->centerpoint[2][0] = 0;
	this->centerpoint[3][0] = 1;
}

Triangle::Triangle(const Triangle& from){
	this->color = from.color;
	this->verticies[0] = matrix(from.verticies[0]);
	this->verticies[1] = matrix(from.verticies[1]);
	this->verticies[2] = matrix(from.verticies[2]);
	this->centerpoint = matrix(from.centerpoint);
}

Triangle& Triangle::operator=(const Triangle& rhs){
	if(this != &rhs){
		this->~Triangle();
		this->color = rhs.color;
        for(int i = 0; i < 3; i++){
            this->verticies[i] = rhs.verticies[i];
        }
	}
	return *this;
}

Triangle::~Triangle(){}

void Triangle::draw(GraphicsContext* gc, ViewContext vc){
	gc->setColor(this->color);
	matrix ptOne = vc.modelToDevice()*this->verticies[0];
	matrix ptTwo = vc.modelToDevice()*this->verticies[1];
	matrix ptThree = vc.modelToDevice()*this->verticies[2];
    gc->drawLine(ptOne[0][0], 
				 ptOne[1][0],
				 ptTwo[0][0],
				 ptTwo[1][0]);
	gc->drawLine(ptTwo[0][0], 
				 ptTwo[1][0],
				 ptThree[0][0],
				 ptThree[1][0]);
	gc->drawLine(ptThree[0][0], 
				 ptThree[1][0],
				 ptOne[0][0],
				 ptOne[1][0]);
}

std::ostream& Triangle::out(std::ostream& os) const{
	os << "Triangle" << std::endl;
	Shape::out(os);
	os << this->verticies[0][0][0] << " "
	   << this->verticies[0][1][0] << " "
	   << this->verticies[0][2][0]
	   << std::endl;
	os << this->verticies[1][0][0] << " "
	   << this->verticies[1][1][0] << " "
	   << this->verticies[1][2][0] 
	   << std::endl;
	os << this->verticies[2][0][0] << " "
	   << this->verticies[2][1][0] << " "
	   << this->verticies[2][2][0] 
	   << std::endl;
	return os;
}

std::istream& Triangle::in(std::istream& is){
	char line[256];
	is.getline(line, 256);
	std::istringstream ss(line);
	int color;
	ss >> color;
	this->color = color;
	for(int i = 0; i < 3; i++){
		is.getline(line, 256);
		std::istringstream ss1(line);
		int x, y, z;
		ss1 >> x >> y >> z;
		this->verticies[i][0][0] = x;
		this->verticies[i][1][0] = y;
		this->verticies[i][2][0] = z;
		this->verticies[i][3][0] = 1;
	}
	return is;
}

Shape* Triangle::clone(){
	Shape* triangle = new Triangle(this->verticies[0][0][0], 
						  this->verticies[0][1][0],
						  this->verticies[1][0][0],
						  this->verticies[1][1][0],
						  this->verticies[2][0][0],
						  this->verticies[2][1][0],
						  this->color);
	return triangle;
}

void Triangle::deviceToModel(ViewContext vc){
	for(int i = 0; i < 3; i++){
            this->verticies[i] = vc.deviceToModel()*this->verticies[i];
        }
}

void Triangle::translocate(int xShift, int yShift, int zShift){
	/*for(int i = 0; i < 3; i++){
		this->verticies[i][0][0] = this->verticies[i][0][0] + xShift;
		this->verticies[i][1][0] = this->verticies[i][1][0] + yShift;
		this->verticies[i][2][0] = this->verticies[i][2][0] + zShift;
	}
	this->centerpoint[0][0] = this->centerpoint[0][0] + xShift;
	this->centerpoint[1][0] = this->centerpoint[1][0] + yShift;
	this->centerpoint[2][0] = this->centerpoint[2][0] + zShift;*/
}

void Triangle::rotate(int degrees){}
void Triangle::scale(int factor){}

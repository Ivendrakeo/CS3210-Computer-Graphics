#include <sstream> 
#include <string> // string library
#include "Line.h"
#include "x11context.h"
#include "matrix.h"
#include "math.h"
#include "ViewContext.h"
#include <iostream> // for std::ostream

Line::Line(){
	this->color = 0;
	this->coordinates[0] = matrix(4,1);
	this->coordinates[1] = matrix(4,1);
	this->centerpoint = matrix(4,1);
}

Line::Line(int x0, int y0, int x1, int y1, unsigned int color){
		this->color = color;
		this->coordinates[0] = matrix(4,1);
		this->coordinates[0][0][0] = x0;
		this->coordinates[0][1][0] = y0;
		this->coordinates[0][2][0] = 0;
		this->coordinates[0][3][0] = 1;
		this->coordinates[1] = matrix(4,1);
		this->coordinates[1][0][0] = x1;
		this->coordinates[1][1][0] = y1;
		this->coordinates[1][2][0] = 0;
		this->coordinates[1][3][0] = 1;
		this->centerpoint = matrix(4,1);
		this->centerpoint[0][0] = (x1+x0)/2;
		this->centerpoint[1][0] = (y1+y0)/2;
		this->centerpoint[2][0] = 0;
		this->centerpoint[3][0] = 1;
}

Line::Line(const Line& from){
	this->color = from.color;
	this->coordinates[0] = matrix(from.coordinates[0]);
	this->coordinates[1] = matrix(from.coordinates[1]);
	this->centerpoint = matrix(from.centerpoint);
}

Line& Line::operator=(const Line& rhs){
	if(this != &rhs){
		this->~Line();
		this->color = rhs.color;
        for(int i = 0; i < 2; i++){
            this->coordinates[i] = rhs.coordinates[i];
        }
		this->centerpoint = rhs.centerpoint;
	}
	return *this;
}

Line::~Line(){}

void Line::draw(GraphicsContext* gc, ViewContext vc){
	gc->setColor(this->color);
	matrix ptOne = vc.modelToDevice()*this->coordinates[0];
	matrix ptTwo = vc.modelToDevice()*this->coordinates[1];
    gc->drawLine(ptOne[0][0], 
				 ptOne[1][0],
				 ptTwo[0][0],
				 ptTwo[1][0]);
}

std::ostream& Line::out(std::ostream& os) const{
	os << "Line" << std::endl;
	Shape::out(os);
	os << this->coordinates[0][0][0] << " "
	   << this->coordinates[0][1][0] << " "
	   << this->coordinates[0][2][0]
	   << std::endl;
	os << this->coordinates[1][0][0] << " "
	   << this->coordinates[1][1][0] << " "
	   << this->coordinates[1][2][0] 
	   << std::endl;
	return os;
}

std::istream& Line::in(std::istream& is){
	char line[256];
	is.getline(line, 256);
	std::istringstream ss(line);
	int color;
	ss >> color;
	this->color = color;
	is.getline(line, 256);
	std::istringstream ss1(line);
	int x, y, z;
	ss1 >> x >> y >> z;
	this->coordinates[0][0][0] = x;
	this->coordinates[0][1][0] = y;
	this->coordinates[0][2][0] = z;
	this->coordinates[0][3][0] = 1;
	is.getline(line, 256);
	std::istringstream ss2(line);
	ss2 >> x >> y >> z;
	this->coordinates[1][0][0] = x;
	this->coordinates[1][1][0] = y;
	this->coordinates[1][2][0] = z;
	this->coordinates[1][3][0] = 1;
	return is;
}

Shape* Line::clone(){
	Shape* line = new Line(this->coordinates[0][0][0], 
						  this->coordinates[0][1][0],
						  this->coordinates[1][0][0],
						  this->coordinates[1][1][0],
						  this->color);
	return line;
}

void Line::deviceToModel(ViewContext vc){
	for(int i = 0; i < 2; i++){
			matrix tmp = vc.deviceToModel()*this->coordinates[i];
            this->coordinates[i] = tmp;
        }
}

void Line::translocate(int xShift, int yShift, int zShift){
	/*this->coordinates[0][0][0] = this->coordinates[0][0][0] + xShift;
	this->coordinates[0][1][0] = this->coordinates[0][1][0] + yShift;
	this->coordinates[0][2][0] = this->coordinates[0][2][0] + zShift;
	this->coordinates[1][0][0] = this->coordinates[1][0][0] + xShift;
	this->coordinates[1][1][0] = this->coordinates[1][1][0] + yShift;
	this->coordinates[1][2][0] = this->coordinates[1][2][0] + zShift;
	this->centerpoint[0][0] = this->centerpoint[0][0] + xShift;
	this->centerpoint[1][0] = this->centerpoint[1][0] + yShift;
	this->centerpoint[2][0] = this->centerpoint[2][0] + zShift;*/
}

void Line::rotate(int degrees){
	/*int x = this->coordinates[0][0][0] - this->centerpoint[0][0];
	int y = this->coordinates[0][1][0] - this->centerpoint[1][0];
	this->coordinates[0].out(std::cout);
	this->centerpoint.out(std::cout);
	this->coordinates[0][0][0] = this->centerpoint[0][0] + x*cos(degrees)-y*sin(degrees);
	this->coordinates[0][1][0] = this->centerpoint[1][0] + y*cos(degrees)+x*sin(degrees);
	this->coordinates[0].out(std::cout);
	this->coordinates[1].out(std::cout);
	x = this->coordinates[1][0][0] - this->centerpoint[0][0];
	y = this->coordinates[1][1][0] - this->centerpoint[1][0];
	this->coordinates[1][0][0] = this->centerpoint[0][0] - x*cos(degrees)-y*sin(degrees);
	this->coordinates[1][1][0] = this->centerpoint[1][0] - y*cos(degrees)+x*sin(degrees);*/
}

void Line::scale(int factor){}

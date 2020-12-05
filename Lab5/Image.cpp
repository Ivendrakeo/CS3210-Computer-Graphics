#include <sstream> 
#include <string> // string library
#include <iostream> // for std::ostream
#include "Image.h"
#include "Shape.h"
#include "Line.h"
#include "Triangle.h"
#include "ViewContext.h"
#include <vector> // c++ array template library

Image::Image(){}
Image::Image(const Image &from){
    for(int i = 0; i < from.shapes.size(); i++){
        this->shapes.push_back(from.shapes[i]->clone());
    }
}

Image::~Image(){
    this->erase();
}

Image& Image::operator=(const Image& rhs){
    if(this != &rhs){
		this->~Image();
        this->erase();
        for(int i = 0; i < rhs.shapes.size(); i++){
            this->shapes.push_back(rhs.shapes[i]->clone());
        }
	}
	return *this;
}

void Image::add(Shape* shape, ViewContext vc){
    shape->deviceToModel(vc);
    this->shapes.push_back(shape->clone());
}

void Image::draw(GraphicsContext* gc, ViewContext vc){
    for(int i = 0; i < shapes.size(); i++){
        this->shapes[i]->draw(gc, vc);
    }
}

std::ostream& Image::out(std::ostream& os) const{
    os << "Image" << std::endl;
    for(int i = 0; i < shapes.size(); i++){
        this->shapes[i]->out(os);
    }
    os << "End_Image"  << std::endl;
    return os;
}

std::istream& Image::in(std::istream& is){
    char line[256];
    std::string word;
    is.getline(line, 256);
    std::istringstream ss(line);
    ss >> word;
    if(word.compare("Image") == 0){ // Ensure Image
        while(word.compare("End_Image") != 0){
            if(word.compare("Line") == 0){
                Line* l =  new Line();
                l->in(is);
                this->shapes.push_back(l);
            } else if(word.compare("Triangle") == 0){
                Triangle* t = new Triangle();
                t->in(is);
                this->shapes.push_back(t);
            }
            is.getline(line, 256);
            std::istringstream ss(line);
            ss >> word;
        }
    }
    return is;
}

void Image::erase(){
    for(int i = 0; i < this->shapes.size(); i++){
        delete this->shapes[i];
    }
    this->shapes.clear();
}

void Image::remove_last(){
    delete this->shapes[this->shapes.size()-1];
    this->shapes.pop_back();
}

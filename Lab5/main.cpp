#include "x11context.h"
#include <unistd.h>
#include <iostream>
#include "Line.h"
#include "Triangle.h"
#include "Image.h"
#include <fstream> // file library
#include <sstream> 
#include <string> // string library
#include "mydrawing.h"
 
int main(void)
{

    GraphicsContext* gc = new X11Context(800,600,GraphicsContext::BLACK);
    gc->setColor(GraphicsContext::GREEN);
    // make a drawing
    MyDrawing md(gc);
    // start event loop - this function will return when X is clicked
    // on window
    gc->runLoop(&md);
    delete gc;


	/*GraphicsContext* gc = new X11Context(800,600,GraphicsContext::BLACK);
    Line l1 = Line(0,0,100,100,GraphicsContext::GREEN);
    Line l2 = Line(100,100,200,200,GraphicsContext::BLUE);
    Line l3 = Line(200,200,300,300,GraphicsContext::RED);
    Line l4 = l3;
    l4.translocate(0,100,0);
    Triangle t1 = Triangle(200,200,500,200,200,500, GraphicsContext::CYAN);
    Image i1;
    i1.add(&l1);
    i1.add(&l2);
    i1.add(&l3);
    Image i2{i1};
    i1.erase();
    l2.translocate(50,0,0);
    Triangle t2 = t1;
    t2.translocate(100,100,0);
    i1.add(&t2);
    i1.add(&t1);
    i1.add(&l2);
    i2.add(&l4);
    Image i3 = i2;
    i2.erase();
    i1.draw(gc);
    i3.draw(gc);*/

    
    /*std::ofstream fileout;
    fileout.open("image1.txt");
    i1.out(fileout);
    fileout.close();

    Image i4 = Image();
    std::ifstream filein("image1.txt");
    i4.in(filein);
    filein.close();
    i4.draw(gc);*/


    //sleep(5);
	//delete gc; 
	//return 0;
}

#include "x11context.h"
#include <unistd.h>
#include <iostream>
 
int main(void)
{
	GraphicsContext* gc = new X11Context(800,600,GraphicsContext::BLACK);

for (int i = 0; i < 20000; i++){ 

gc->setColor(rand()%16777216); 

gc->drawLine((rand()%800), (rand()%600), (rand()%800),(rand()%600));
}

sleep(10);
/*
	gc->drawLine(0,0,100,200);
    gc->setColor(GraphicsContext::RED);
    gc->drawLine(0,0,200,100);
    gc->setColor(GraphicsContext::BLUE);
    gc->drawLine(500,500,100,200);
    gc->setColor(GraphicsContext::GREEN);
    gc->drawLine(500,500,200,100);
    gc->setColor(GraphicsContext::YELLOW);
    gc->drawLine(300,300,500,200);
    gc->setColor(GraphicsContext::MAGENTA);
    gc->drawLine(300,300,400,100);
    gc->setColor(GraphicsContext::CYAN);
    gc->drawLine(600,0,500,200);
    gc->setColor(GraphicsContext::GRAY);
    gc->drawLine(600,0,400,100);
    
    gc->setColor(GraphicsContext::RED);
    gc->drawLine(100,100,100,500);
    gc->drawLine(500,500,500,100);
    gc->drawLine(100,100,500,100);
    gc->drawLine(500,500,100,500);
    gc->setColor(GraphicsContext::MAGENTA);
	gc->drawCircle(300,300,200);*/
 
 
	// draw some lines
	/*gc->setColor(GraphicsContext::GREEN);
	gc->setPixel(10,10);
	gc->setPixel(30,30);
	gc->drawLine(100,100,100,500);
	gc->setColor(GraphicsContext::RED);
	gc->drawLine(100,500,500,500);
	gc->setColor(GraphicsContext::BLUE);
	gc->drawLine(500,500,500,100);
	gc->setColor(GraphicsContext::YELLOW);
	gc->drawLine(500,100,100,100);
	gc->setColor(GraphicsContext::MAGENTA);
	gc->drawCircle(300,300,200);*/
 
	delete gc;
 
	return 0;
}

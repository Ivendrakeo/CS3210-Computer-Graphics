#include "mydrawing.h"
#include "gcontext.h"
#include <iostream>
#include <fstream> // file library
#include "Image.h"
#include "Line.h"
#include "Shape.h"
#include "Triangle.h"

// Constructor
MyDrawing::MyDrawing(GraphicsContext* gc)
{
    x0 = x1 = y0 = y1 = x2 = y2 = 0; 
    mode = LINE; // start in line mode
    point = ZERO;
    image = Image();
    first_line = false;
    vc = ViewContext(gc);
    vc.backup();
    // User instructions
    std::cout << "Welcome to Draven-Paint!" << std::endl;
    std::cout << "Definitely not a worse MS Paint program" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "The following shortcuts are available:" << std::endl;
    std::cout << "s - save image" << std::endl;
    std::cout << "r - reset to saved image" << std::endl;
    std::cout << "t - cycle between drawable shapes" << std::endl;
    std::cout << "c - clear working image" << std::endl;
    std::cout << "left arrow - rotate image clockwise" << std::endl;
    std::cout << "right arrow - rotate image counterclockwise" << std::endl;
    std::cout << "up arrow - scale up" << std::endl;
    std::cout << "down arrow - scale down" << std::endl;

    return;
}

void MyDrawing::paint(GraphicsContext* gc)
{
    // for fun, let's draw a "fixed" shape in the middle of the screen // it will only show up after an exposure
    int middlex = gc->getWindowWidth()/2; int middley = gc->getWindowHeight()/2;

    gc->setColor(GraphicsContext::MAGENTA);

    for (int yi=middley-50;yi<=middley+50;yi++)
    {
        gc->drawLine(middlex-50,yi,middlex+50,yi);
    }
    gc->setColor(GraphicsContext::GREEN);

    // redraw the line if requested
    gc->drawLine(x0,y0,x1,y1);
    return;
}

void MyDrawing::mouseButtonDown(GraphicsContext* gc, unsigned int button, int x, int y) {
    // mouse button pushed down
    // - clear context
    // - set origin of new line // - set XOR mode for rubber-banding
    // - draw new line in XOR mode. Note, at this point, the line is
    // degenerate (0 length), but need to do it for consistency

    switch(point){
        case ZERO:
            x0 = x1 = x2 = x;
            y0 = y1 = x2 = y;
            gc->setMode(GraphicsContext::MODE_XOR);
            gc->drawLine(x0,y0,x1,y1);
            point = ONE_PRESS;
            break;
        case ONE_RELEASE:
            point = TWO_PRESS;
            break;
        default:
            std::cout << "ERROR POINT PRESS STATE: " << point << std::endl;
    }
    return;
}

void MyDrawing::mouseButtonUp(GraphicsContext* gc, unsigned int button, int x, int y)
{
    Line* tmp_line;
    Triangle* tmp_tri;
    switch(point){
        case ONE_PRESS:
            gc->drawLine(x0,y0,x1,y1);
            x1 = x;
            y1 = y;
            gc->setMode(GraphicsContext::MODE_NORMAL);
            gc->drawLine(x0,y0,x1,y1);
            tmp_line = new Line(x0,y0,x1,y1, GraphicsContext::GREEN);
            image.add(tmp_line, vc);
            delete tmp_line;
            gc->setMode(GraphicsContext::MODE_XOR);
            first_line = true;
            if(mode == LINE){
                point = ZERO;
            } else if (mode == TRIANGLE){
                point = ONE_RELEASE;
                gc->drawLine(x0,y0,x2,y2);
                gc->drawLine(x1,y1,x2,y2);
            }
            break;
        case TWO_PRESS:
            if(mode == TRIANGLE){
                gc->drawLine(x0,y0,x2,y2);
                gc->drawLine(x1,y1,x2,y2);
                x2 = x;
                y2 = y;
                gc->setMode(GraphicsContext::MODE_NORMAL);
                gc->drawLine(x0,y0,x2,y2);
                gc->drawLine(x1,y1,x2,y2);
                image.remove_last();
                tmp_tri = new Triangle(x0,y0,x1,y1,x2,y2, GraphicsContext::GREEN);
                image.add(tmp_tri, vc);
                delete tmp_tri;
                gc->setMode(GraphicsContext::MODE_XOR);
                first_line = false;
            }
            point = ZERO;
            break;
        default:
            std::cout << "ERROR POINT RELEASE STATE: " << point << std::endl;
    }
    return;
}

void MyDrawing::mouseMove(GraphicsContext* gc, int x, int y)
{
    switch(point){
        case ZERO:
            break;
        case ONE_PRESS:
            gc->drawLine(x0,y0,x1,y1);
            x1 = x;
            y1 = y;
            gc->drawLine(x0,y0,x1,y1);
            break;
        case ONE_RELEASE:
        case TWO_PRESS:
            if(mode == TRIANGLE){
                gc->drawLine(x0,y0,x2,y2);
                gc->drawLine(x1,y1,x2,y2);
                x2 = x;
                y2 = y;
                gc->drawLine(x0,y0,x2,y2);
                gc->drawLine(x1,y1,x2,y2);
            }
            break;
        case TWO_RELEASE:
            break;
        default:
            std::cout << "ERROR POINT MOVE STATE: " << point << std::endl;
            break;
    }
    return;
}

void MyDrawing::keyDown(GraphicsContext* gc, unsigned int keycode){
    // Handels the arrow keys (scaling and rotation)
    if(keycode == key_up_arrow || keycode == key_left_arrow || 
       keycode == key_down_arrow || keycode == key_right_arrow){
        // create temporary file to store data so that we can erase and 
        // redraw the image with transformed features.
        std::ofstream fileout;
        fileout.open("transform.txt");
        this->image.out(fileout);
        fileout.close();
        gc->clear();
        this->image.erase();
        x0 = x1 = y0 = y1 = x2 = y2 = 0; 
        first_line = false;
        // Apply transformation
        switch(keycode){
            case key_left_arrow:
                vc.rotate(-90);
                break;
            case key_right_arrow:
                vc.rotate(90);
                break;
            case key_up_arrow:
                vc.scale(1.1);
                break;
            case key_down_arrow:
                vc.scale(0.9);
                break;
        }
        // Reload image with transform.
        std::ifstream filein("transform.txt");
        if(filein){
            this->image.in(filein);
            gc->setMode(GraphicsContext::MODE_NORMAL);
            this->image.draw(gc, vc);
            gc->setMode(GraphicsContext::MODE_XOR);
        } else {
            std::cout << "No image available?" << std::endl;
        }
        filein.close();
    }
}

void MyDrawing::keyUp(GraphicsContext* gc, unsigned int keycode){
    // s - save image
    // r - reset to saved image
    // t - cycle between drawable shapes
    // c - clear working image
    
    if(keycode == key_s){
        std::ofstream fileout;
        fileout.open("image.txt");
        vc.backup();
        this->image.out(fileout);
        std::cout << "Image saved sucessfully!" << std::endl;
        fileout.close();
    }
    if(keycode == key_c || keycode == key_r){
        gc->clear();
        this->image.erase();
        x0 = x1 = y0 = y1 = x2 = y2 = 0; 
        first_line = false;
        if(keycode == key_c)
            std::cout << "Image cleared sucessfully!" << std::endl;
    }
    if(keycode == key_r){
        std::ifstream filein("image.txt");
        vc.restore();
        if(filein){
            this->image.in(filein);
            gc->setMode(GraphicsContext::MODE_NORMAL);
            this->image.draw(gc, vc);
            gc->setMode(GraphicsContext::MODE_XOR);
            std::cout << "Image loaded sucessfully!" << std::endl;
        } else {
            std::cout << "No saved image available!" << std::endl;
        }
        filein.close();
    }
    if(keycode == key_t){
        switch(mode){
            case LINE:
                mode = TRIANGLE;
                if(first_line && point == ZERO){
                    gc->drawLine(x0,y0,x2,y2);
                    gc->drawLine(x1,y1,x2,y2);
                    point = ONE_RELEASE;
                }
                std::cout << "draw mode: TRIANGLE" << std::endl;
                break;
            case TRIANGLE:
                mode = LINE;
                if(point == ONE_RELEASE){
                    gc->drawLine(x0,y0,x2,y2);
                    gc->drawLine(x1,y1,x2,y2);
                    point = ZERO;
                }
                std::cout << "draw mode: LINE" << std::endl;
                break;
        }
    }
}

MyDrawing::~MyDrawing(){
    std::remove("transform.txt"); // delete working image file if it exists
    image.erase();
}
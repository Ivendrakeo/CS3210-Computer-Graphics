#ifndef MYDRAWING_H
#define MYDRAWING_H

#include "drawbase.h"
#include "Image.h"
#include "ViewContext.h"

#define key_s 115
#define key_r 114
#define key_t 116
#define key_c 99
#define key_up_arrow 65362
#define key_left_arrow 65361
#define key_down_arrow 65364
#define key_right_arrow 65363

// forward reference
class GraphicsContext;

class MyDrawing : public DrawingBase
{
    public:
        MyDrawing(GraphicsContext* gc); 
        // we will override just these 
        virtual void paint(GraphicsContext* gc); 
        virtual void mouseButtonDown(GraphicsContext* gc, unsigned int button, int x, int y);
        virtual void mouseButtonUp(GraphicsContext* gc, unsigned int button, int x, int y); 
        virtual void mouseMove(GraphicsContext* gc, int x, int y); 
        virtual void keyDown(GraphicsContext* gc, unsigned int keycode);
        virtual void keyUp(GraphicsContext* gc, unsigned int keycode);
        ~MyDrawing();
    private: 
        // We will only support one "remembered" line 
        // In an actual implementation, we would also have one of our "image" 
        // objects here to store all of our drawn shapes.
        int x0; 
        int y0;
        int x1; 
        int y1;
        int x2;
        int y2;

        bool first_line; // flag for the first line of a new image drawn.

        // State Machine implementation for drawing lines/triangles. 
        // More robust and flexible than having multiple flag varriables.
        enum pointPos {ZERO, ONE_PRESS, ONE_RELEASE, TWO_PRESS, TWO_RELEASE}point; //working point state
        enum drawingMode {TRIANGLE, LINE}mode; // which drawing mode is the cursor in?
        Image image;
        ViewContext vc;
};
#endif
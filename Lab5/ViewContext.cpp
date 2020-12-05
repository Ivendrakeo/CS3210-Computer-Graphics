#include "ViewContext.h"
#include "drawbase.h"
#include "matrix.h"
#include <math.h>

ViewContext::ViewContext(){

}

ViewContext::ViewContext(GraphicsContext* gc){
    matrix translate = matrix::identity(4);
    translate[0][3] = gc->getWindowWidth()/2;
    translate[1][3] = gc->getWindowHeight()/2;
    matrix flip = matrix::identity(4);
    flip[1][1] = -1;
    model_to_device = translate*flip;
    translate[0][3] = -gc->getWindowWidth()/2;
    translate[1][3] = -gc->getWindowHeight()/2;
    device_to_model = flip*translate;
} 

matrix ViewContext::deviceToModel() const{
    return device_to_model;
}

matrix ViewContext::modelToDevice() const{
    return model_to_device;
}

void ViewContext::rotate(double degrees){
        matrix rotate = matrix::identity(4);
        rotate[0][0] = cos(degrees);
        rotate[0][1] = sin(degrees);
        rotate[1][0] = -sin(degrees);
        rotate[1][1] = cos(degrees);
        model_to_device = model_to_device*rotate;
        rotate[0][0] = cos(-degrees);
        rotate[0][1] = sin(-degrees);
        rotate[1][0] = -sin(-degrees);
        rotate[1][1] = cos(-degrees);
        device_to_model = rotate*device_to_model;
}

void ViewContext::scale(double size){
    matrix scale = matrix::identity(4);
    scale[0][0] = size;
    scale[1][1] = size;
    model_to_device = model_to_device*scale;
    scale[0][0] = 1/(size);
    scale[1][1] = 1/(size);
    device_to_model = scale*device_to_model;
}

void ViewContext::backup(){
    save_device_to_model = matrix(device_to_model);
    save_model_to_device = matrix(model_to_device);
}

void ViewContext::restore(){
    device_to_model = matrix(save_device_to_model);
    model_to_device = matrix(save_model_to_device);
}
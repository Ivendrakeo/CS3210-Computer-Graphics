#include "drawbase.h"
#include "Image.h"
#include "matrix.h"

#ifndef VIEWCONTEXT_H
#define VIEWCONTEXT_H

// forward reference
class GraphicsContext;

/*
 * The ViewContext class maintains composite matrixes which mapps
 * model->device coordinates and device->model coordinates.
 * Additionally controling transformation features such 
 * as scaling and rotating.
 * 
 */
class ViewContext: public DrawingBase{
    public:
        // default constructor needed to compile
        // DO NOT USE. The ViewContext constructor NEEDS the 
        // parameterized constructor to properly function
        ViewContext();

        // Parameterized constructor takes in an initialized graphics context 
        // which defines the screen region and sets up the initial composite matrixes
        ViewContext(GraphicsContext* gc); 

        // Rotates the model->device and device->model coordinates by 
        // the specified degree measure
        void rotate(double degrees);

        // Scales the model->device and device->model coordinates by
        // the specified size value.
        void scale(double size);

        // Returns the composite matrix device->model
        matrix deviceToModel() const;

        // Returns the composite matrix model->device
        matrix modelToDevice() const;

        // Backs up the internal composite matrixes
        void backup();

        // Restores from the backup the composite matrixes.
        // only can be called AFTER a backup!
        void restore();

    private: 
        matrix model_to_device;
        matrix device_to_model;

        matrix save_model_to_device;
        matrix save_device_to_model;
};
#endif
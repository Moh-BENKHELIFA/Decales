#ifndef TEST_DECALERECTANGLEFIELD2D_H
#define TEST_DECALERECTANGLEFIELD2D_H


#include "DecaleScalarField2D.h"


class DecaleRectangleField2D : public DecaleScalarField2D{

public:
    DecaleRectangleField2D(double posx, double posy, double radiusx, double radiusy,
                           unsigned int id, int z_index, unsigned int n=2);

//    void setSize(int w, int h);
//    void setSize(double w, double h);
//    void setWidth(int w);
//    void setWidth(double w);
//    void setHeight(int h);
//    void setHeight(double h);
    double variableRadius (double x, double y);
//    void scale(double scalex, double scaley);
//    double eval (const double x, const double y);

//    double dist (double x, double y);

//    double normalizedDist (double x, double y);
//    void computeDiscreteField ();
//    /**
//     * Update the field buffer of index indexField in the vector of field buffers with the Decale evaluation function.
//     * @param indexField: index of the buffer to recompute in the vector of field buffers.
//     */
//    void updateDiscreteField (unsigned int indexField);

//    /**
//     * Create and compute the (u,v) parameterization (in [0,1]*[0,1], or -1 = no image) in a buffer of Vector2D
//     * (u,v) computations are done from the field values stored in the list of field buffers at the index indexField.
//     * This buffer is stored in the Decale.
//     * @param indexField: Decale field buffer from which the (u,v) parameterization is computed.
//     */
//    void computeDiscreteUVField (unsigned int indexField);
//    /**
//     * Compute the (u,v) parameterization (in [0,1]*[0,1], or -1 = no image) in the decale UV-buffer
//     * (u,v) computations are done from the field values stored in the list of field buffers at the index indexField.
//     * @param indexField: Decale field buffer from which the (u,v) parameterization is computed.
//     */

//    void updateDiscreteUVField (unsigned int indexField);
//    /**
//     * Change the size of all the Decale buffers (field buffers and UV Buffer) according to the width and height Decale attributes.
//     * They all have to be recomputed (can be done with the updates of discrete fields = buffers).
//     */
//    void updateBuffersSize ();



};

#endif // DECALERECTANGLEFIELD2D_H

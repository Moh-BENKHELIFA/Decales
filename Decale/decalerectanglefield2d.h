#ifndef TEST_DECALERECTANGLEFIELD2D_H
#define TEST_DECALERECTANGLEFIELD2D_H

#include "DecaleScalarField2D.h"


class DecaleRectangleField2D : public DecaleScalarField2D{

public:
    DecaleRectangleField2D(double posx, double posy, double radius,unsigned int id, int z_index, unsigned int n);

    double variableRadius (double x, double y);
};

#endif // DECALERECTANGLEFIELD2D_H

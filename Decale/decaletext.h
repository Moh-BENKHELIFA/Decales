#ifndef TEST_DECALETEXT_H
#define TEST_DECALETEXT_H

#include "DecaleScalarField2D.h"

class DecaleText : public DecaleScalarField2D{

public:

    DecaleText(double posx, double posy, double radius, unsigned int id, int z_index, unsigned int n=2);

    //Square
    double variableRadius (double x, double y);

};

#endif // TEST_DECALETEXT_H




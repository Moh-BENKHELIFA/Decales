//
// Created by Loïc Barthe on 25/03/2020.
//

#include "DecaleSquareField2D.h"
#include <math.h>
#include <iostream>


DecaleSquareField2D::DecaleSquareField2D(double posx, double posy, double radius,unsigned int id, int z_index, unsigned int n)
        : DecaleScalarField2D(posx, posy, radius, id, z_index, n) {


}

//Square
double DecaleSquareField2D::variableRadius (double x, double y) {

    Vector2D p(x-posx,y-posy);
    double up = u*p*scaley;
    double vp = v*p*scalex;

    if (fabs(up) >= fabs(vp))
        return radiusx*scalex*p.norm()/fabs(p*u);
    return radiusy*scaley*p.norm()/fabs(p*v);
}

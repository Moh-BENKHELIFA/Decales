#include "DecaleRectangleField2d.h"
#include <math.h>




DecaleRectangleField2D::DecaleRectangleField2D(double posx, double posy, double radius,unsigned int id, int z_index, unsigned int n)
    : DecaleScalarField2D(posx, posy, radius, id, z_index, n) {

}

double DecaleRectangleField2D::variableRadius (double x, double y) {

    Vector2D p(x-posx,y-posy);
    double up = u*p*scaley;
    double vp = v*p*scalex;

    if (fabs(up) >= fabs(vp)) return radius*scalex*p.norm()/fabs(p*u);
    return radius*scaley*p.norm()/fabs(p*v);
}




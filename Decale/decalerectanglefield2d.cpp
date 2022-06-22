#include "DecaleRectangleField2d.h"
#include <math.h>




DecaleRectangleField2D::DecaleRectangleField2D(double posx, double posy, double radius,unsigned int id, int z_index, unsigned int n)
    : DecaleScalarField2D(posx, posy, radius, id, z_index, n) {

    int width = 200;
    int height = 100;

    setSizeX(width);
    setSizeY(height);

    double newScalex = scalex;
    double newScaley = scaley;

    if(width > height)
        newScalex = width/height;
    else
        newScaley = height/width;


//    scaley = height/width;

    scaleInit(newScalex, newScaley);

    scale(0.5, 0.5);

}

double DecaleRectangleField2D::variableRadius (double x, double y) {

    Vector2D p(x-posx,y-posy);
    double up = u*p*scaley;
    double vp = v*p*scalex;

    if (fabs(up) >= fabs(vp)) return radius*scalex*p.norm()/fabs(p*u);
    return radius*scaley*p.norm()/fabs(p*v);
}


void DecaleRectangleField2D::scaleInit(const double scalex, const double scaley) {


    /***********************************
    // Scale accumulation. Provides the scales from the rest pose.
    ***********************************/
    this->scalex = this->scalex * scalex;
    this->scaley = this->scaley * scaley;

    /***********************************
    // Accumulation of the width and height from scales.
    ***********************************/
    noRotateDWidthWithScale = noRotateDWidthWithScale * scalex;
    noRotateDHeightWithScale = noRotateDHeightWithScale * scaley;

    /***********************************
    // Conservative Decale overall size (up to 0-values) avoiding a too small size
    // when a scaled decale (larger) is rotated.
    ***********************************/
    if (hasRotated) dwidth = dheight = std::max(noRotateDWidthWithScale, noRotateDHeightWithScale);
    else {
        dwidth = noRotateDWidthWithScale;
        dheight = noRotateDHeightWithScale;
    }

    iwidth=(unsigned int)dwidth;
    iheight=(unsigned int)dheight;

    cornerx=(int)(posx - dwidth/2.);
    cornery=(int)(posy - dheight/2.);

    /***********************************
    // The field and UV buffer size need to be updates and buffers need to be re-computed
    ***********************************/
    needUpdateBuffersSize = true;
}




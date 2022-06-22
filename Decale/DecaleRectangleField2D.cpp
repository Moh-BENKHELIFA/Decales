#include "DecaleRectangleField2D.h"
#include <math.h>
#include <iostream>

DecaleRectangleField2D::DecaleRectangleField2D(double posx, double posy,
                                               double radiusx, double radiusy, unsigned int id, int z_index, unsigned int n)
    : DecaleScalarField2D(posx, posy, radiusx, radiusy, id, z_index, n) {


    double width = radiusx;
    double height = radiusy;


//    iheight=height;
//    iwidth=width;
//    dwidth=width;
//    dheight=height;

//    iheight=2*height;
//    iwidth=2*width;
//    dwidth=2*width;
//    dheight=2*height;


////    size = 70;
////      noRotateDWidthWithScale=237;

////    scalex = 2;

////    int ratio = 250/100;


//    scalex = (width/height);
//    scaley = (height/width);

//    if(width>height){
//        scalex = (width/height)/2;
////        width *= (width/height);
//    }else if(height>width){
//        scaley = (height/width)/2;
//    }


//    radiusx = width / invAtIso;
//    radiusy = height / invAtIso;
//    radius = 0;

//    std::cout<<"RADIUS: "<<radius<<std::endl;
//    std::cout<<"RADIUSX: "<<radiusx<<std::endl;

//    dwidth=2.*radiusx;
//    dheight=2.*radiusy;

//    iwidth=(unsigned int)dwidth;
//    iheight=(unsigned int) dheight;

//    noRotateDWidthWithScale=dwidth;
//    noRotateDHeightWithScale=dheight;


//    cornerx=(int)(posx-radiusx);
//    cornery=(int)(posy-radiusy);




//    scale(scalex, scaley);


    //TODO
    //Field 2D a jour
    //update le ratio etc pour avoir une bonne hitbox et voir si ca fonctionne bien
    /*
     * ça faisait quelque chose quand je divisais par deux mais je ne sais plus quoi
     * je crois que c'était plus nette au niveau du texte et moins déformé
     */
//    scalex = (width/height)/2;
//    scaley = (height/width)/2;


//    std::cout<<"SCALE X: "<<scalex<<std::endl;
//    std::cout<<"SCALE Y: "<<scaley<<std::endl;


}

//Rectangle
double DecaleRectangleField2D::variableRadius (double x, double y) {

    Vector2D p(x-posx,y-posy);
    double up = u*p*scaley;
    double vp = v*p*scalex;

    if (fabs(up) >= fabs(vp))
        return radiusx*scalex*p.norm()/fabs(p*u);
    return radiusy*scaley*p.norm()/fabs(p*v);
}

//void DecaleRectangleField2D::scale(const double scalex, const double scaley) {

//    /***********************************
//    // Scale accumulation. Provides the scales from the rest pose.
//    ***********************************/
//    this->scalex = this->scalex * scalex;
//    this->scaley = this->scaley * scaley;

//    /***********************************
//    // Accumulation of the width and height from scales.
//    ***********************************/
//    noRotateDWidthWithScale = noRotateDWidthWithScale * scalex;
//    noRotateDHeightWithScale = noRotateDHeightWithScale * scaley;

//    /***********************************
//    // Conservative Decale overall size (up to 0-values) avoiding a too small size
//    // when a scaled decale (larger) is rotated.
//    ***********************************/
//    if (hasRotated) dwidth = dheight = std::max(noRotateDWidthWithScale, noRotateDHeightWithScale);
//    else {
//        dwidth = noRotateDHeightWithScale;
//        dheight = noRotateDHeightWithScale;
//    }

//    iwidth=(unsigned int)dwidth;
//    iheight=(unsigned int)dheight;

//    cornerx=(int)(posx - dwidth/2.);
//    cornery=(int)(posy - dheight/2.);

//    /***********************************
//    // The field and UV buffer size need to be updates and buffers need to be re-computed
//    ***********************************/
//    needUpdateBuffersSize = true;

////    std::cout<<"Rectangle scale"<<std::endl;
//}

//double DecaleRectangleField2D::normalizedDist (double x, double y) {

////    std::cout<<"Rectangle normalizedDist"<<std::endl;
////    std::cout<<"VARIABLE RADIUS VALUE: "<<variableRadius(x,y)<<std::endl;

//    return dist(x,y)/variableRadius(x,y);
//}

//double DecaleRectangleField2D::dist (double x, double y) {
////    std::cout<<"Rectangle dist"<<std::endl;

//    return sqrt(pow((x-posx),2) + pow ((y-posy),2));
//}


//double DecaleRectangleField2D::eval(const double x, const double y) {

////    std::cout<<"Rectangle eval"<<std::endl;

//    double d=normalizedDist(x,y);
//    return fallOff (d);
//}

//void DecaleRectangleField2D::computeDiscreteField() {
//    std::cout<<"Rectangle computeDiscreteField"<<std::endl;


//    discreteField = new double [iwidth*iheight];

//    for (int i=0; i<iwidth; i++)
//        for (int j=0; j<iheight;j++)
//            discreteField[i*iheight+j]=eval(double(i)+posx-dwidth/2., double(j)+posy-dheight/2.);

//    discreteFields.push_back(discreteField);
//}

//void DecaleRectangleField2D::updateDiscreteField(unsigned int indexField) {
//    std::cout<<"Rectangle updateDiescreteField"<<std::endl;


//    for (int i=0; i<iwidth; i++)
//        for (int j=0; j<iheight;j++)
//            discreteFields[indexField][i*iheight+j]=eval(double(i)+posx-dwidth/2., double(j)+posy-dheight/2.);
//}

//void DecaleRectangleField2D::computeDiscreteUVField (unsigned int indexField){

//    std::cout<<"Rectangle computeDiscreteUVField"<<std::endl;


//    discreteUVField = new Vector2D [iwidth*iheight];
//    double x,y,valu,valv, valField;
//    Vector2D p,s;

//    for (int i=0; i<iwidth; i++)
//        for (int j=0; j<iheight;j++) {
//            valField = getDiscreteFieldValue(i,j,indexField);
//            if (valField >= iso) {
//                x = double(i)+posx-dwidth/2.;
//                y = double(j)+posy-dheight/2.;
//                p.x = x-posx;
//                p.y = y-posy;
//                p.normalize();
//                s = p * invFallOff(valField);
//                s = s * variableRadius(x,y);

//                valu = ((s * u) / (variableRadius(posx+u.x,posy+u.y) * invAtIso) + 1.) / 2.;
//                valv = ((s * v) / (variableRadius(posx+v.x,posy+v.y) * invAtIso) + 1.) / 2.;

//                discreteUVField[i*iheight+j] = Vector2D(valu,valv);
//            }
//            else
//                discreteUVField[i*iheight+j] = Vector2D(-1.,-1.);
//        }
//}
//void DecaleRectangleField2D::updateDiscreteUVField(unsigned int indexField) {

//    std::cout<<"Rectangle updateDiscreteUVField"<<std::endl;

//    double x,y,valu,valv, valField;
//    Vector2D p,s;

//    for (int i=0; i<iwidth; i++)
//        for (int j=0; j<iheight;j++) {
//            valField = getDiscreteFieldValue(i,j,indexField);
//            if (valField >= iso) {
//                x = double(i)+posx-dwidth/2.;
//                y = double(j)+posy-dheight/2.;
//                p.x = x-posx;
//                p.y = y-posy;
//                p.normalize();
//                s = p * invFallOff(valField);
//                s = s * variableRadius(x,y);

//                valu = ((s * u) / (variableRadius(posx+u.x,posy+u.y) * invAtIso) + 1.) / 2.;
//                valv = ((s * v) / (variableRadius(posx+v.x,posy+v.y) * invAtIso) + 1.) / 2.;

//                discreteUVField[i*iheight+j] = Vector2D(valu,valv);
//            }
//            else
//                discreteUVField[i*iheight+j] = Vector2D(-1.,-1.);
//        }
//}

//void DecaleRectangleField2D::updateBuffersSize() {

//    std::cout<<"Rectangle updateBufferSize"<<std::endl;


//    for (int i=0; i<discreteFields.size();i++){
//        delete(discreteFields[i]);
//        discreteFields[i] = new double [iwidth*iheight];
//    }
//    delete(discreteUVField);
//    discreteUVField = new Vector2D [iwidth*iheight];

//    needUpdateBuffersSize = false;
//}




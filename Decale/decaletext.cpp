#include "decaletext.h"
#include <math.h>

DecaleText::DecaleText(double posx, double posy, double radius,unsigned int id, int z_index, unsigned int n)
: DecaleScalarField2D(posx, posy, radius, id, z_index, n)
{

    double width = 100;
    double height = 50;

    iheight=height;
    iwidth=width;
    dwidth=width;
    dheight=height;

    iheight=2*height;
    iwidth=2*width;
    dwidth=2*width;
    dheight=2*height;


//    size = 70;
//      noRotateDWidthWithScale=237;

//    scalex = 2;

//    int ratio = 250/100;


    scalex = 1;
    scaley = 1;

    if(width>height){
        scalex = (width/height)/2;
//        width *= (width/height);
    }else if(height>width){
        scaley = (height/width)/2;
    }


//    radiusx = width / invAtIso;
//    radiusy = height / invAtIso;
    radius = 0;

//    std::cout<<"RADIUS: "<<radius<<std::endl;
//    std::cout<<"RADIUSX: "<<radiusx<<std::endl;

    dwidth=2.*radiusx;
    dheight=2.*radiusy;

    iwidth=(unsigned int)dwidth;
    iheight=(unsigned int) dheight;

    noRotateDWidthWithScale=dwidth;
    noRotateDHeightWithScale=dheight;


    cornerx=(int)(posx-radiusx);
    cornery=(int)(posy-radiusy);




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


//Square
double DecaleText::variableRadius (double x, double y) {

    Vector2D p(x-posx,y-posy);
    double up = u*p*scaley;
    double vp = v*p*scalex;

    if (fabs(up) >= fabs(vp))
        return radiusx*scalex*p.norm()/fabs(p*u);
    return radiusy*scaley*p.norm()/fabs(p*v);
}



//
// Created by Loïc Barthe on 27/03/2020.
//

#include "Field2D.h"
#include <math.h>
#include "iostream"


Field2D::Field2D (): size (1.), n(2), iso(0.5) {

    invAtIso = invFallOff(iso);
//    radius = size / invAtIso;
    radiusx = sizex / invAtIso;
    radiusy = sizey / invAtIso;
}

Field2D::Field2D (double size, unsigned int n)
        : size(size), n(n), iso(0.5), sizex(size), sizey(size) {

    invAtIso = invFallOff(iso);
    std::cout<<"Size: "<<size<<std::endl;
    std::cout<<"invAtIso: "<<invAtIso<<std::endl;
    std::cout<<"radius: "<<size / invAtIso<<std::endl;
    std::cout<<"------------------------: "<<std::endl;

//    radius = size / invAtIso;
    radiusx = sizex / invAtIso;
    radiusy = sizey / invAtIso;
}

Field2D::Field2D (double sizex, double sizey, unsigned int n)
        : sizex(sizex), sizey(sizey), n(n), iso(0.5) {

    invAtIso = invFallOff(iso);
//    std::cout<<"Size: "<<size<<std::endl;
//    std::cout<<"invAtIso: "<<invAtIso<<std::endl;
//    std::cout<<"radius: "<<size / invAtIso<<std::endl;
//    std::cout<<"------------------------: "<<std::endl;

    //TODO
//    size = 30; //LE SOUCI EST ICI IL FAUT REDEFINIR TOUT LE RESTE DU CODE ET AFFICHAGE PAR RAPPORT A SIZEX et SIZEY
//    radius = sizex/invAtIso;
//    radius = size/invAtIso;

    radiusx = sizex / invAtIso;
    radiusy = sizey / invAtIso;

    std::cout<<"radius X: "<<radiusx<<std::endl;
    std::cout<<"radius Y: "<<radiusy<<std::endl;
    std::cout<<"radius  : "<<radius<<std::endl;
}


double Field2D::normalizeField (double distanceFieldValue){

    return distanceFieldValue / radius;
}

double Field2D::fallOff (double normalizedField){

    if (normalizedField>=1.) return 0.;
    if (normalizedField>0.) return pow(1-normalizedField*normalizedField,n);
    return 1.;
}

double Field2D::invFallOff (double valFallOff){

    return sqrt(1.-pow(valFallOff,1./(double(n))));
}

void Field2D::setSize(double value)
{
    size = value;
}

double Field2D::getSize (){

    return sizex;
}

//double Field2d:

double Field2D::getN () {

    return n;
}

double Field2D::getIso (){

    return iso;
}

void Field2D::setIso (double iso){

    this->iso=iso;
}

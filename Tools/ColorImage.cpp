//
// Created by Loïc Barthe on 06/01/2022.
//

#include "ColorImage.h"
#include <iostream>
#include "QPainter"
#include "QLabel"
#include "QGraphicsScene"
#include "QTextCharFormat"
#include "QTextCursor"
#include "QGraphicsTextItem"
#include "QRect"
#include "QSize"
#include "QtCore"
#include "QPicture"


ColorImage::ColorImage (const QString &fileName, unsigned int decaleId){

    piximg = QPixmap(fileName);
    width = piximg.width();
    height = piximg.height();

    qimg = piximg.toImage();


//    qimg = label->pixmap().toImage();



    this->decaleId = decaleId;
}

ColorImage::ColorImage (const int w, const int h, unsigned int decaleId){
    piximg = QPixmap(w, h);
    width = w;
    height = h;

    this->decaleId = decaleId;

    QLabel *label = new QLabel();
    label->setGeometry(0,0,w,h);
//    label->setSizePolicy(QSizePolicy(10));
    label-> setWordWrap(true);
//    label->setText("Hello world!");
    label->setAlignment(Qt::AlignLeft );
    label->setStyleSheet("background: white; border:3px solid black");
    label->setMargin(5);


    QTextDocument doc;


//    QString text = "Hello world";
//    QFont font = label->font();
//    int fontSize = font.pointSize();
//    QFontMetrics fontMetrics(font);
//    QRect rectlbl = label->rect();
//    QRect rect = fontMetrics.boundingRect(label->rect(), Qt::TextWordWrap, text);
//    int step = rect.height() > label->height() ? -1 : 1;
//    for(;;){
//        font.setPointSize(fontSize + step);
//        QFontMetrics fontMetrics(font);
//        rect = fontMetrics.boundingRect(label->rect(), Qt::TextWordWrap, text);
//        if (fontSize <= 1) {
//          std::cout << "Font cannot be made smaller!" << std::endl;
//          break;
//        }
//        if (step < 0) {
//          fontSize += step;
//          if (rect.height() < label->height()) break;
//        } else {
//          if (rect.height() > label->height()) break;
//          fontSize += step;
//        }
//    }

//    font.setPointSize(fontSize);
////    label->setText(text);

//    label->setFont(font);

    QFont *font = new QFont("SansSerif", 8);//Size 8 = best smallest resolution
    font->setHintingPreference(QFont::PreferFullHinting);
    font->setStyleStrategy(QFont::PreferAntialias);
    label->setFont(*font);

//    QString text = "<font size=20><b>Abstract</b><br></font>"
//                   "<font size=3>"
//                   "    So hello there this is the abstract of this document we are presenting today."
//                   "    Je rajoute du texte en plus pour que ça soit plus long et que ça déborde comme il faut pour voir si ça redimensionne les choses ou non."
//                   "</font>";

//    QString text = "<font size=20><b>Abstract</b><br></font>"
//                   "<font size =1px>"
//                   "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque porttitor augue aliquam libero consequat consequat. Nullam luctus tincidunt eros eleifend efficitur. Fusce ultrices laoreet eleifend. Quisque non pharetra orci, et consectetur massa. Praesent iaculis pellentesque iaculis. Nunc ipsum ante, vulputate at mauris eget, commodo aliquet nisi. In bibendum vulputate libero nec interdum. Donec augue orci, pellentesque gravida enim vitae, dapibus eleifend arcu. Vestibulum augue lacus, tincidunt ut dignissim in, malesuada a tortor. Integer vitae nibh sit amet dolor rutrum semper sed ut nulla. Aliquam eu imperdiet turpis. Aenean non lorem ullamcorper, sollicitudin lectus in, vehicula mauris. Donec euismod interdum scelerisque. In sit amet eros scelerisque, accumsan turpis ut, vehicula ipsum. "
//                   "</font>";
    QString text = "Abstract\n"
                    "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque porttitor augue aliquam libero consequat consequat. Nullam luctus tincidunt eros eleifend efficitur. Fusce ultrices laoreet eleifend. Quisque non pharetra orci, et consectetur massa. Praesent iaculis pellentesque iaculis. Nunc ipsum ante, vulputate at mauris eget, commodo aliquet nisi. In bibendum vulputate libero nec interdum. Donec augue orci, pellentesque gravida enim vitae, dapibus eleifend arcu. Vestibulum augue lacus, tincidunt ut dignissim in, malesuada a tortor. Integer vitae nibh sit amet dolor rutrum semper sed ut nulla. Aliquam eu imperdiet turpis. Aenean non lorem ullamcorper, sollicitudin lectus in, vehicula mauris. Donec euismod interdum scelerisque. In sit amet eros scelerisque, accumsan turpis ut, vehicula ipsum. ";
//    QRect rectLbl = label->rect(); // wrong: contentsRect();
//    QFont font = label->font();
//    int size = font.pointSize();
//    QFontMetrics fontMetrics(font);
//    QRect rect = fontMetrics.boundingRect(rectLbl,
//    Qt::TextWordWrap, text);
//      // decide whether to increase or decrease
//    int step = rect.height() > rectLbl.height() ? -1 : 1;
//     // iterate until text fits best into rectangle of label
//    for (;;) {
//        font.setPointSize(size + step);
//        QFontMetrics fontMetrics(font);
//        rect = fontMetrics.boundingRect(rectLbl,
//          Qt::TextWordWrap, text);
//        if (size <= 1) {
//          std::cout << "Font cannot be made smaller!" << std::endl;
//          break;
//        }
//        if (step < 0) {
//          size += step;
//          if (rect.height() < rectLbl.height()) break;
//        } else {
//          if (rect.height() > rectLbl.height()) break;
//          size += step;
//        }
//      }
//      // apply result of iteration
//      font.setPointSize(size);
//      label->setFont(font);
      label->setText(text);



    piximg = label->pixmap();


    qimg = label->grab(*new QRect(QPoint(0,0), QSize(w,h))).toImage();

//    qimg = label->pixmap().toImage();    //Not working



}

//Gamut Image constructor
ColorImage::ColorImage (const int w, const int h){
    piximg = QPixmap(w, h);
    width = w;
    height = h;

    qimg = piximg.toImage();
    setBlack();


}

Color ColorImage::getColor (const unsigned int i, const unsigned int j){

    return Color(qimg.pixelColor(i, j));
}

void ColorImage::setPixelColor (const unsigned int i, const unsigned int j, Color c){

    QColor qc;
    qc.setRgbF(c.r, c.g, c.b);
    qimg.setPixelColor((int)i, (int)j, QColor(qc));
}

void ColorImage::setBlack(){

    QColor qc;
    qc.setRgbF(0.,0.,0.);

    for (int i=0; i<width; i++)
       for (int j=0; j<height; j++)
           qimg.setPixelColor(i, j, qc);
}

QPixmap &ColorImage::getQPixmap (){

    piximg=piximg.fromImage(qimg, Qt::AutoColor);
    return piximg;
}

void ColorImage::setBlackGamut(GamutField2D *gf) {

    QColor qc;
    qc.setRgbF(0.,0.,0.);

    for (int i=0; i<width; i++)
        for (int j=0; j<height; j++)
            if (gf->eval(i,j) < gf->getIso()) qimg.setPixelColor(i, j, qc);
}

void ColorImage::setColorGamut(GamutField2D *gf, Color c) {

    QColor qc;
    qc.setRgbF(c.r,c.g,c.b);

    for (int i=0; i<width; i++)
        for (int j=0; j<height; j++)
            if (gf->eval(i,j) < gf->getIso()) qimg.setPixelColor(i, j, qc);
}

void ColorImage::setColor(Color c) {

    QColor qc;
    qc.setRgbF(c.r,c.g,c.b);

    for (int i=0; i<width; i++)
        for (int j=0; j<height; j++)
           qimg.setPixelColor(i, j, qc);
}

void ColorImage::addColorImageWithDecaleUV(DecaleScalarField2D *decale, ColorImage *imgDecale) {







    QColor qc, qcwhite, qcgray, qcblack, qcred;
    qcwhite.setRgbF(1.,1.,1.);
    qcblack.setRgbF(0.,0.,0.);
    qcred.setRgbF(1.,0.,0.);
    qcgray.setRgbF(0.5,0.5,0.5);
    Vector2D uv;
    int xu, yu;



    for (int i=0; i<decale->getIWidth(); i++){
        for (int j=0; j<decale->getIHeight(); j++) {
            uv=decale->getUV(i,j);

            if ((uv.x >= 0.) && (uv.y >= 0.) && (uv.x < 2.) && (uv.y < 2.)
                && ((int)decale->getCornerX() + i> 0) && ((int)decale->getCornerY() + j > 0)
                && ((int)decale->getCornerX() + i< width) && ((int)decale->getCornerY() + j < height)) {
                xu = (int)(uv.x*imgDecale->getWidth());
                yu = (int)(uv.y*imgDecale->getHeight());
//                std::cout<<uv.x<<" "<<uv.y<<"  "<<decale->getSize()<<"  "<<imgDecale->getWidth()<<" "<<imgDecale->getHeight()<<std::endl;
                if(xu<imgDecale->getWidth() && yu<imgDecale->getHeight()){
                    Color c = imgDecale->getColor(xu,yu);
                    qc.setRgbF(c.r,c.g,c.b);
                    qimg.setPixelColor((int)decale->getCornerX() + i,(int)decale->getCornerY() + j, qc);
                }
            }
        }

    }


    if(decale->getId()==0){

//        for (int i=0; i<decale->getIWidth(); i++){
//            for (int j=0; j<decale->getIHeight(); j++) {
//                uv=decale->getUV(i,j);

//                if ((uv.x >= 0.) && (uv.y >= 0.) && (uv.x < 2.) && (uv.y < 2.)
//                    && ((int)decale->getCornerX() + i> 0) && ((int)decale->getCornerY() + j > 0)
//                    && ((int)decale->getCornerX() + i< width) && ((int)decale->getCornerY() + j < height)) {
//                    xu = (int)(uv.x*imgDecale->getWidth());
//                    yu = (int)(uv.y*imgDecale->getHeight());
////                    std::cout<<"x: "<<i<<" | "<<xu<<" :xu"<<std::endl;
////                    std::cout<<"y: "<<j<<" | "<<yu<<" :yu"<<std::endl;

//                        Color c = imgDecale->getColor(xu,yu);
//                        qc.setRgbF(c.r,c.g,c.b);
//                        qimg.setPixelColor((int)decale->getCornerX() + i,(int)decale->getCornerY() + j, qc);
//                    }
//                }
//            }

//        }



    std::cout<<"IWIDTH: "<<imgDecale->getWidth()<<std::endl;
    std::cout<<"IHEIGHT: "<<imgDecale->getHeight()<<std::endl;
    std::cout<<"DHEIGHT: "<<decale->getIHeight()<<std::endl;
    std::cout<<"DWIDTH: "<<decale->getIWidth()<<std::endl;


//        for (int i=00; i<decale->getIWidth(); i++){

//            for (int j=00; j<decale->getIHeight(); j++) {
//                uv=decale->getUV(i,j);

//                                xu = (int)(uv.x*imgDecale->getWidth());
//                yu = (int)(imgDecale->getHeight());
//    //                std::cout<<uv.x<<" "<<uv.y<<"  "<<decale->getSize()<<"  "<<imgDecale->getWidth()<<" "<<imgDecale->getHeight()<<std::endl;
//                if ((uv.x >= 0.) && (uv.y >= 0.) && (uv.x < 1.) && (uv.y < 1.)
//                               && ((int)decale->getCornerX() + i> 0) && ((int)decale->getCornerY() + j > 0)
//                               && ((int)decale->getCornerX() + i< width) && ((int)decale->getCornerY() + j < height)) {
//                Color c = (imgDecale->getColor(i,j));
//                qc.setRgbF(c.r,c.g,c.b);
//                qimg.setPixelColor((int)decale->getCornerX()+i,(int)decale->getCornerY()+j, qc);

//                  }
//              }
//          }
//    int t = decale->getPosx();

//    for (int i=0; i<decale->getIWidth(); i++){
//            qimg.setPixelColor(decale->getPosx()+i,(int)decale->getPosy(), Qt::green);
//    }

//    for (int i=0; i<decale->getIHeight(); i++){
//            qimg.setPixelColor(decale->getPosx(),(int)decale->getPosy()+i, Qt::gray);
//    }


//    int x2 = decale->getCornerX();
//    int y2 = decale->getCornerY();

//    for (int i=x2; i<x2+decale->getIWidth(); i++){
//            qimg.setPixelColor(i,y2, Qt::red);
//            qimg.setPixelColor(i,y2+decale->getCornerX(), Qt::red);


//    }

//    for (int i=y2; i<y2+decale->getIHeight(); i++){
//            qimg.setPixelColor(x2,i, Qt::blue);
//            qimg.setPixelColor(x2+decale->getCornerY(),i, Qt::blue);

//    }

    }
}

int ColorImage::getWidth() {

    return width;
}

int ColorImage::getHeight() {

    return height;
}

int ColorImage::getId(){
    return decaleId;
}

void ColorImage::clearDecaleColorImage(DecaleScalarField2D *decale, ColorImage *imgDecale, GamutField2D *gamut, Color gamutColor, Color bgColor) {

    Vector2D uv;
    QColor qgamutColor, qbgColor;
    qgamutColor.setRgbF(gamutColor.r,gamutColor.g,gamutColor.b);
    qbgColor.setRgbF(bgColor.r, bgColor.g, bgColor.b);

    for (int i=0; i<decale->getIWidth(); i++)
        for (int j=0; j<decale->getIHeight(); j++) {
            uv=decale->getUV(i,j);

            if ((uv.x > 0.) && (uv.y > 0.) && (uv.x < 1.) && (uv.y < 1.)
                && ((int)decale->getCornerX() + i > 0) && ((int)decale->getCornerY() + j > 0)
                && ((int)decale->getCornerX() + i < width) && ((int)decale->getCornerY() + j < height)){
                if (gamut->eval(decale->getCornerX() +i,decale->getCornerY() + j) > gamut->getIso())
                    qimg.setPixelColor(decale->getCornerX() + i, decale->getCornerY() + j, qbgColor);
                else
                    qimg.setPixelColor(decale->getCornerX() + i, decale->getCornerY() + j, qgamutColor);
            }


        }


}


void ColorImage::clearDecaleColorImage(DecaleScalarField2D *decale, GamutField2D *gamut, Color gamutColor, Color bgColor) {

    std::cout<<"ClearDecaleColorImage call"<<std::endl;
    Vector2D uv;
    QColor qgamutColor, qbgColor;
    qgamutColor.setRgbF(gamutColor.r,gamutColor.g,gamutColor.b);
    qbgColor.setRgbF(bgColor.r, bgColor.g, bgColor.b);

    for (int i=0; i<decale->getIWidth(); i++)
        for (int j=0; j<decale->getIHeight(); j++) {
            uv=decale->getUV(i,j);

            if ((uv.x > 0.) && (uv.y > 0.) && (uv.x < 1.) && (uv.y < 1.)
                && ((int)decale->getCornerX() + i > 0) && ((int)decale->getCornerY() + j > 0)
                && ((int)decale->getCornerX() + i < width) && ((int)decale->getCornerY() + j < height)){

                if (gamut->eval(decale->getCornerX() +i,decale->getCornerY() + j) > gamut->getIso()){
                    qimg.setPixelColor(decale->getCornerX() + i, decale->getCornerY() + j, qbgColor);

                }else{
                    qimg.setPixelColor(decale->getCornerX() + i, decale->getCornerY() + j, qgamutColor);

                }
            }
        }

    std::cout<<"ClearDecaleColorImage ENDcall"<<std::endl;

}

double ColorImage::getRatioHW() {


    return ((double)height) / ((double)width);
}

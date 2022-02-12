#include "qfunctionline.h"

QGraphicFunctionLine::QGraphicFunctionLine(int b, int e, string fn){
    function=fn;
    begin=b;
    end=e;
    prepare(function);
}

QGraphicFunctionLine::~QGraphicFunctionLine(){

}

QRectF QGraphicFunctionLine::boundingRect() const{
    return collisions;
}

void QGraphicFunctionLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget){
    painter->setPen(QPen(Qt::black));
    if(function.find("^")!=string::npos){
        collisions=QRectF(1000,1000,-1000,-1000);
        for(int i=begin; i<end;i++){
            painter->drawLine(QLineF(i,solve(i),i+1,solve(i+1)));
        }
    }else{
        collisions=QRectF(1000,1000,-1000,-1000);
        painter->drawLine(QLineF(begin,solve(begin),end,solve(end)));
    }
}

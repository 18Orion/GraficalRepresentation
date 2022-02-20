#include "include/qfunctionline.h"

QGraphicFunctionLine::QGraphicFunctionLine(int b, int e, string fn){
    function=fn;
    begin=b;
    end=e;
    if(function.find("y")!=string::npos){
        xVar=false;
        replace(function.begin(),function.end(),'y','x');
    }
    prepare(function);
}

QGraphicFunctionLine::~QGraphicFunctionLine(){

}

QRectF QGraphicFunctionLine::boundingRect() const{
    return QRectF(QPointF(-1000,-1000),QPointF(1000,1000));;
}

void QGraphicFunctionLine::rePaint(){
    if(function.find("y")!=string::npos){
        xVar=false;
        replace(function.begin(),function.end(),'y','x');
    }
    prepare(function);
    update();
}

void QGraphicFunctionLine::changeItem(int b, int e, string fn){
    function=fn;
    begin=b;
    end=e;
    if(function.find("y")!=string::npos){
        xVar=false;
        replace(function.begin(),function.end(),'y','x');
    }
    prepare(function);
    update();
}

void QGraphicFunctionLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget){
    painter->setPen(QPen(Qt::black,0.5));
    if(xVar){
        if(function.find("^")!=string::npos){
            for(int i=begin; i<end;i++){
                painter->drawLine(QLineF(i,solve(i),i+1,solve(i+1)));
            }
        }else{
            painter->drawLine(QLineF(begin,solve(begin),end,solve(end)));
        }
    }else if(!xVar){
        if(function.find("^")!=string::npos){
            for(int i=begin; i<end;i++){
                painter->drawLine(QLineF(solve(i),i,solve(i+1),i+1));
            }
        }else{
            painter->drawLine(QLineF(solve(begin),begin,solve(end),end));
        }
    }
}

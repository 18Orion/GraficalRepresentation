#ifndef QGRAPHICNET_H
#define QGRAPHICNET_H

#include <QGraphicsItem>
#include <QPainter>
#include <iostream>
#include "funcion.hpp"

class QGraphicFunctionLine : public QGraphicsItem, funcion
{
    public:
        QGraphicFunctionLine(int b, int e, string fn);
            ~QGraphicFunctionLine();
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);    //Paint
        QRectF boundingRect() const;                //Returns the collision
        void changeItem(int b, int e, string fn);   //Changes the item values and repaint
        void rePaint();     //Updates the painting
    private:
        int begin, end;     //Defines the begin and end of the printing
        string function;    //stores the function
        QRectF collisions;  //Stores the collision
        bool xVar=true;     //If  it is an x or y function
};
#endif // QGRAPHICNET_H

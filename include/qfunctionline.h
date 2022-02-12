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
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);
        QRectF boundingRect() const;
        void p();
    private:
        int begin, end;
        string function;
        QRectF collisions;
    protected:
};

#endif // QGRAPHICNET_H

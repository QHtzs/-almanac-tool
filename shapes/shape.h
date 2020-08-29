#ifndef SHAPE_H
#define SHAPE_H


#include "./shapebase.h"

class Shape: public ShapeBase
{
public:
    Shape();
    virtual ~Shape();

    virtual void SetStart(const QPoint &start);
    virtual void  SetEnd(const QPoint & end) ;
    virtual QPoint&  GetStart();
    virtual QPoint&  GetEnd();

    virtual void paint(QPainter& painter) = 0;

protected:
    QPoint _start;
    QPoint _end;

};

#endif // SHAPE_H

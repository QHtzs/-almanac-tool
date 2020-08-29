#ifndef SHAPEBASE_H
#define SHAPEBASE_H


#include <QPoint>
#include <QPainter>


class ShapeBase
{
public:
    ShapeBase();
    virtual ~ShapeBase();

    virtual void SetStart(const QPoint &start) = 0;
    virtual void  SetEnd(const QPoint & end) = 0;
    virtual QPoint&  GetStart() = 0;
    virtual QPoint&  GetEnd() = 0;

    virtual void paint(QPainter& painter) = 0;
};

#endif // SHAPEBASE_H

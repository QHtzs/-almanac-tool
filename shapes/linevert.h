#ifndef LINEVERT_H
#define LINEVERT_H


#include "./shape.h"

class LineVert : public Shape
{
public:
    LineVert();

    void paint(QPainter &painter);
};

#endif // LINEVERT_H

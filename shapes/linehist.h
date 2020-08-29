#ifndef LINEHIST_H
#define LINEHIST_H

#include "./shape.h"

class LineHist : public Shape
{
public:
    LineHist();

     void paint(QPainter &painter);
};

#endif // LINEHIST_H

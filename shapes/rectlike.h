#ifndef RECTLIKE_H
#define RECTLIKE_H

#include "./shape.h"

class RectLike : public Shape
{
public:
    RectLike();
    void paint(QPainter &painter);
};

#endif // RECTLIKE_H

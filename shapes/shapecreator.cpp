#include "shapecreator.h"

#include "./shapebase.h"
#include "./linehist.h"
#include "./linevert.h"
#include "./rectlike.h"

ShapeBase* ShapeCreator::CreateShape(ShapeCreator::ShapeType type)
{
    switch (type)
    {
     case ShapeCreator::LINE_H:
        return new LineHist;
    case ShapeCreator::LINE_W:
        return new LineVert;
    case ShapeCreator::RECT:
        return new RectLike;
    }
    return nullptr;
}



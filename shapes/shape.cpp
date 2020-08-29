#include "shape.h"

Shape::Shape()
{

}

Shape::~Shape()
{

}

void Shape::SetStart(const QPoint &start){
    _start = start;
}

void  Shape::SetEnd(const QPoint & end){
  _end = end;
}

QPoint&  Shape::GetStart(){
    return _start;
}

QPoint& Shape:: GetEnd(){
    return _end;
}

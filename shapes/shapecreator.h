#ifndef SHAPECREATOR_H
#define SHAPECREATOR_H

class ShapeBase;

class ShapeCreator
{
public:
    enum ShapeType{
        LINE_H = 0,
        LINE_W,
        RECT
    };

    static ShapeBase* CreateShape(ShapeCreator::ShapeType type);
};

#endif // SHAPECREATOR_H

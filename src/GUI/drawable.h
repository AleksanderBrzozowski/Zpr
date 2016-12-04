#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <QPainter>

class Drawable
{
public:
public:
    Drawable(unsigned int, bool);
    virtual ~Drawable() = 0;

    virtual void draw(QPainter &) = 0;
    virtual void setTo(int x, int y) = 0;
    int getLayer();
    bool isGhost();

private:
    unsigned int layer;
    bool ghost;
};

#endif // DRAWABLE_H

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <QPainter>

class Drawable
{
public:
public:
    Drawable(unsigned int);
    virtual ~Drawable() = 0;

    virtual void draw(QPainter &) = 0;
    virtual void setTo(int x, int y) = 0;
    int getLayer();

private:
    unsigned int layer;
};

#endif // DRAWABLE_H

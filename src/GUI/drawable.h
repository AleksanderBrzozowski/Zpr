#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <QPainter>

class Drawable
{
public:
public:
    Drawable(unsigned int, bool);
    virtual ~Drawable() = 0;

    virtual void draw(QPainter &) const = 0;
    virtual void setTo(unsigned int x, unsigned int y) = 0;
    virtual bool intersects(QRect& rectangle) const = 0;
    int getLayer() const;
    bool isGhost() const;

private:
    unsigned int layer;
    bool ghost;
};

#endif // DRAWABLE_H

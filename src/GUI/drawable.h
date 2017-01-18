#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <QPainter>

/*!
 * \brief The Drawable class.
 * \details Base class for all the objects that represents objects drawn
 * on screen. It has three purely virtual classes that needs to be implemented.
 * Its main purpouse is to create common interface of drawing all objects that
 * can be drawn.
 * \author Pawel Rybak
 */
class Drawable
{
public:
public:
    Drawable(bool);
    virtual ~Drawable() = 0;

    virtual void draw(QPainter &) const = 0;
    virtual void setTo(unsigned int x, unsigned int y) = 0;
    virtual bool intersects(QRect& rectangle) const = 0;
    bool isGhost() const;

private:
    bool ghost;
};

#endif // DRAWABLE_H

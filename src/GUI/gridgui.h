#ifndef GRIDGUI_H
#define GRIDGUI_H

#include "drawable.h"

/*!
 * \brief The GridGUI class.
 * \details Class represents grid drawn on the screen. most of objects are snapped to
 * this grid. It implements all necessary functions to be drawn. It also contains all
 * variables thet define look of the grid.
 * \author Pawel Rybak
 */
class GridGUI : public Drawable {
public:
    GridGUI(unsigned int width, unsigned int height);
    ~GridGUI();
    void draw(QPainter &painter) const override;
    void setTo(unsigned int x, unsigned int y) override;
    bool intersects(QRect &rectangle) const override;

    /**PROPERTIES**/
    static const QPen PEN;
    static const int SIZE;
private:
    unsigned int height;
    unsigned int width;
};

#endif // GRIDGUI_H

#ifndef GRIDGUI_H
#define GRIDGUI_H

#include "drawable.h"

class GridGUI : public Drawable {
public:
    GridGUI(unsigned int layer, unsigned int width, unsigned int height);
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

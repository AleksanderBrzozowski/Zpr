#ifndef GRIDGUI_H
#define GRIDGUI_H

#include "drawable.h"
#include "guiconstants.h"

class GridGUI : public Drawable {
public:
    GridGUI(unsigned int layer, unsigned int width, unsigned int height);
    ~GridGUI();
    void draw(QPainter &painter) override;
    void setTo(int x, int y) override;

private:
    unsigned int height;
    unsigned int width;
};

#endif // GRIDGUI_H

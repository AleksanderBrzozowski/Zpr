#ifndef ROADGUI_H
#define ROADGUI_H

#include "drawable.h"
#include "guiconstants.h"
#include "../Point.h"
#include <QRect>
#include <math.h>
#include <iostream>

class RoadGUI : public Drawable {
public:
    RoadGUI(unsigned int layer, Point begin, Point end);
    ~RoadGUI();
    void draw(QPainter &) override;
    void setTo(int x, int y) override;

private:
    QRect roadRect;
};

#endif // ROADGUI_H

#ifndef CARGUI_H
#define CARGUI_H

#include "drawable.h"
#include "guiconstants.h"


class CarGUI : public Drawable {
public:
    CarGUI(unsigned int layer, QRect carRect);
    CarGUI(unsigned int layer, int x, int y);
    ~CarGUI();
    void draw(QPainter &painter) override;
    void setTo(int x, int y) override;

private:
    QRect carRect;
};

#endif // CARGUI_H

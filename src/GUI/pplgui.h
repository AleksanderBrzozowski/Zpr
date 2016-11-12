#ifndef PPLGUI_H
#define PPLGUI_H

#include "drawable.h"
#include "guiconstants.h"

class PplGUI : public Drawable {
public:
    PplGUI(unsigned int layer, QRect pplRect);
    PplGUI(unsigned int layer, int x, int y);
    ~PplGUI();
    void draw(QPainter &painter) override;
    void setTo(int x, int y) override;

private:
    QRect pplRect;
};

#endif // PPLGUI_H

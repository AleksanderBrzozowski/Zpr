#ifndef PPLGUI_H
#define PPLGUI_H

#include "drawable.h"

class PplGUI : public Drawable {
public:
    PplGUI(unsigned int layer, QRect pplRect, bool ghost = false);
    PplGUI(unsigned int layer, int x, int y, bool ghost = false);
    ~PplGUI();
    void draw(QPainter &painter) override;
    void setTo(int x, int y) override;

    /**PROPERTIES**/
    static const int RADIUS;

    static const int PEN_WIDTH;
    static const Qt::PenStyle PEN_STYLE;
    static const Qt::PenCapStyle PEN_CAP;
    static const Qt::PenJoinStyle PEN_JOIN;
    static const QColor PEN_COLOR;

    static const QPen PEN;

    static const Qt::BrushStyle BRUSH_STYLE;
    static const QColor BRUSH_COLOR;

    static const QBrush BRUSH;

private:
    QRect pplRect;
};

#endif // PPLGUI_H

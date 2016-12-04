#ifndef CARGUI_H
#define CARGUI_H

#include "drawable.h"


class CarGUI : public Drawable {
public:
    CarGUI(unsigned int layer, QRect carRect, bool ghost = false);
    CarGUI(unsigned int layer, int x, int y, bool ghost = false);
    ~CarGUI();
    void draw(QPainter &painter) override;
    void setTo(int x, int y) override;

    /**PROPERTIES**/
    static const int WIDTH;
    static const int HEIGHT;

    static const int PEN_WIDTH;
    static const Qt::PenStyle PEN_STYLE;
    static const Qt::PenCapStyle PEN_CAP;
    static const Qt::PenJoinStyle PEN_JOIN;

    static const QColor PEN_COLOR;
    static const QColor GHOST_PEN_COLOR;

    static const QPen PEN;
    static const QPen GHOST_PEN;

    static const Qt::BrushStyle BRUSH_STYLE;
    static const QColor BRUSH_COLOR;
    static const QColor GHOST_BRUSH_COLOR;

    static const QBrush BRUSH;
    static const QBrush GHOST_BRUSH;
private:
    QRect carRect;
};

#endif // CARGUI_H

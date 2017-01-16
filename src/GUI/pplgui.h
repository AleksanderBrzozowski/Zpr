#ifndef PPLGUI_H
#define PPLGUI_H

#include "drawable.h"

class PplGUI : public Drawable {
public:
    PplGUI(unsigned int layer, QRect pplRect, bool ghost = false);
    PplGUI(unsigned int layer, unsigned int x, unsigned int y, bool ghost = false);
    ~PplGUI();
    void draw(QPainter &painter) const override;
    void setTo(unsigned int x, unsigned int y) override;
    bool intersects(QRect &rectangle) const override;

    /**PROPERTIES**/
    static const int RADIUS;

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
    QRect pplRect;
};

#endif // PPLGUI_H

#ifndef CARGUI_H
#define CARGUI_H

#include "drawable.h"

/*!
 * \brief The CarGUI class
 * \details Class holds all necessary information to draw car object on screen.
 * It implements functions from base class thar defines how car will look. It also
 * holds all variables that define look of the both types of car object on screen.
 * \author Pawel Rybak
 */
class CarGUI : public Drawable {
public:
    CarGUI(QRect carRect, bool fast = false, bool ghost = false);
    CarGUI(unsigned int x, unsigned int y, bool fast = false, bool ghost = false);
    ~CarGUI();
    void draw(QPainter &painter) const override;
    void setTo(unsigned int x, unsigned int y) override;
    bool intersects(QRect &rectangle) const override;

    /**PROPERTIES**/
    static const int WIDTH;
    static const int HEIGHT;
    static const int FAST_WIDTH;
    static const int FAST_HEIGHT;

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
    static const QColor FAST_BRUSH_COLOR;
    static const QColor GHOST_BRUSH_COLOR;
    static const QColor FAST_GHOST_BRUSH_COLOR;

    static const QBrush BRUSH;
    static const QBrush FAST_BRUSH;
    static const QBrush GHOST_BRUSH;
    static const QBrush FAST_GHOST_BRUSH;

    static const unsigned int CAR_SPEED;
    static const unsigned int FAST_CAR_SPEED;
private:
    QRect carRect;
    bool fast;
};

#endif // CARGUI_H

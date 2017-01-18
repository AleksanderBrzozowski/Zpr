#ifndef PPLGUI_H
#define PPLGUI_H

#include "drawable.h"
#include "gridgui.h"
#include "roadgui.h"

/*!
 * \brief The PplGUI class.
 * \details Class holds all necessary information to draw Human object on screen.
 * It implements functions from base class thar defines how Human will look. It also
 * holds all variables that define look of the Human object on screen.
 * \author Pawel Rybak
 */
class PplGUI : public Drawable {
public:
    PplGUI(QRect pplRect, bool ghost = false);
    PplGUI(unsigned int x, unsigned int y, bool ghost = false);
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

    static const int SPEED;
    static const int OFFSET;
private:
    QRect pplRect;
};

#endif // PPLGUI_H

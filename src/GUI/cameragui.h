#ifndef CAMERAGUI_H
#define CAMERAGUI_H

#include "drawable.h"
#include <Point.h>
#include <cmath>

class CameraGUI : public Drawable
{
public:
    CameraGUI(unsigned int x, unsigned int y,
              unsigned int span, int angle, unsigned int range,
              bool ghost = false);
    CameraGUI(Point position, Point range, int span, bool ghost = false);
    CameraGUI(Point position);

    void setRectangle(Point point);
    void setRectangle(Point first, Point second);

    ~CameraGUI();
    void draw(QPainter &) const;
    void setTo(unsigned int x, unsigned int y) override;
    bool intersects(QRect &rectangle) const;

    void decRange();
    void incRange();
    void rotClockwise();
    void rotCounterclockwise();
    void incSpan();
    void decSpan();
    int getSpan();
    int getAngle();
    int getRange();

    /**PROPERTIES**/
    static const unsigned int CAM_RADIUS;
    static const unsigned int MAX_RANGE;
    static const unsigned int MIN_RANGE;
    static const unsigned int MAX_SPAN;
    static const unsigned int MIN_SPAN;

    static const unsigned int DEFAULT_SPAN;
    static const unsigned int DEFAULT_ANGLE;
    static const unsigned int DEFAULT_RANGE;

    static const int CAM_PEN_WIDTH;
    static const Qt::PenStyle CAM_PEN_STYLE;
    static const Qt::PenCapStyle CAM_PEN_CAP;
    static const Qt::PenJoinStyle CAM_PEN_JOIN;

    static const QColor CAM_PEN_COLOR;
    static const QColor GHOST_CAM_PEN_COLOR;

    static const QPen CAM_PEN;
    static const QPen GHOST_CAM_PEN;

    static const Qt::BrushStyle CAM_BRUSH_STYLE;
    static const QColor CAM_BRUSH_COLOR;
    static const QColor GHOST_CAM_BRUSH_COLOR;

    static const QBrush CAM_BRUSH;
    static const QBrush GHOST_CAM_BRUSH;

    static const int RNG_PEN_WIDTH;
    static const Qt::PenStyle RNG_PEN_STYLE;
    static const Qt::PenCapStyle RNG_PEN_CAP;
    static const Qt::PenJoinStyle RNG_PEN_JOIN;

    static const QColor RNG_PEN_COLOR;
    static const QColor GHOST_RNG_PEN_COLOR;

    static const QPen RNG_PEN;
    static const QPen GHOST_RNG_PEN;

    static const Qt::BrushStyle RNG_BRUSH_STYLE;
    static const QColor RNG_BRUSH_COLOR;
    static const QColor GHOST_RNG_BRUSH_COLOR;

    static const QBrush RNG_BRUSH;
    static const QBrush GHOST_RNG_BRUSH;

private:
    QRect camRect;
    QRect rngRect;
    int span;
    int angle;
};

#endif // CAMERAGUI_H

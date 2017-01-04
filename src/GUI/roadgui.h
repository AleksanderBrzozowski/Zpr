#ifndef ROADGUI_H
#define ROADGUI_H

#include "drawable.h"
#include "../Point.h"
#include "gridgui.h"
#include <QRect>
#include <math.h>
#include <iostream>

class RoadGUI : public Drawable {
public:
    static void adjustPoints(Point& first, Point& second);

    RoadGUI(unsigned int layer, Point begin, Point end, bool ghost = false);
    RoadGUI(unsigned int layer, Point point);
    ~RoadGUI();
    void draw(QPainter &) override;
    void setTo(int x, int y) override;
    void setRectangle(Point first, Point second);
    void setRectangle(Point point);

    bool isVertical() const;
    std::tuple<Point, Point> getEnds() const;

    bool coincides(const RoadGUI&) const;
    bool intersects(const RoadGUI&) const;
    bool adjoins(const RoadGUI&) const;

    /**PROPERTIES**/
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
    QRect roadRect;
    Point start;
    Point end;
    bool vertical;
};

#endif // ROADGUI_H

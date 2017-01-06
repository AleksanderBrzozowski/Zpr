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
    void draw(QPainter &) const override;
    void setTo(unsigned int x, unsigned int y) override;
    bool intersects(QRect& rectangle) const override;
    void setRectangle(Point first, Point second);
    void setRectangle(Point point);
    void drawSidewalk(QPainter&) const;

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

    static const QColor SIDEWALK_BRUSH_COLOR;
    static const QBrush SIDEWALK_BRUSH;
    static const unsigned int SIDEWALK_WIDTH;

private:
    QRect roadRect;
    QRect sidewalkRect;
    Point start;
    Point end;
    bool vertical;
};

#endif // ROADGUI_H

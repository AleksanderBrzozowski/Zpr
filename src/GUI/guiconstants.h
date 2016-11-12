#ifndef GUICONSTANTS_H
#define GUICONSTANTS_H

#include <QPen>
#include <QBrush>

namespace GUI {
    /**********CAR**********/
    const int CAR_WIDTH = 10;
    const int CAR_HEIGHT = 10;

    const int CAR_PEN_WIDTH = 2;
    const Qt::PenStyle CAR_PEN_STYLE = Qt::SolidLine;
    const Qt::PenCapStyle CAR_PEN_CAP = Qt::SquareCap;
    const Qt::PenJoinStyle CAR_PEN_JOIN = Qt::RoundJoin;
    const QColor CAR_PEN_COLOR = Qt::black;

    const QPen CAR_PEN(CAR_PEN_COLOR, CAR_PEN_WIDTH, CAR_PEN_STYLE,
                       CAR_PEN_CAP, CAR_PEN_JOIN);

    const Qt::BrushStyle CAR_BRUSH_STYLE = Qt::SolidPattern;
    const QColor CAR_BRUSH_COLOR = Qt::blue;

    const QBrush CAR_BRUSH(CAR_BRUSH_COLOR, CAR_BRUSH_STYLE);

    /**********PPL**********/
    const int PPL_RADIUS = 5;

    const int PPL_PEN_WIDTH = 2;
    const Qt::PenStyle PPL_PEN_STYLE = Qt::SolidLine;
    const Qt::PenCapStyle PPL_PEN_CAP = Qt::SquareCap;
    const Qt::PenJoinStyle PPL_PEN_JOIN = Qt::RoundJoin;
    const QColor PPL_PEN_COLOR = Qt::black;

    const QPen PPL_PEN(PPL_PEN_COLOR, PPL_PEN_WIDTH, PPL_PEN_STYLE,
                       PPL_PEN_CAP, PPL_PEN_JOIN);

    const Qt::BrushStyle PPL_BRUSH_STYLE = Qt::SolidPattern;
    const QColor PPL_BRUSH_COLOR = Qt::green;

    const QBrush PPL_BRUSH(PPL_BRUSH_COLOR, PPL_BRUSH_STYLE);

    /*********ROAD**********/
    const int ROAD_PEN_WIDTH = 1;
    const Qt::PenStyle ROAD_PEN_STYLE = Qt::SolidLine;
    const Qt::PenCapStyle ROAD_PEN_CAP = Qt::SquareCap;
    const Qt::PenJoinStyle ROAD_PEN_JOIN = Qt::RoundJoin;
    const QColor ROAD_PEN_COLOR = Qt::darkGray;

    const QPen ROAD_PEN(ROAD_PEN_COLOR, ROAD_PEN_WIDTH, ROAD_PEN_STYLE,
                        ROAD_PEN_CAP, ROAD_PEN_JOIN);


    const Qt::BrushStyle ROAD_BRUSH_STYLE = Qt::SolidPattern;
    const QColor ROAD_BRUSH_COLOR = Qt::darkGray;

    const QBrush ROAD_BRUSH(ROAD_BRUSH_COLOR, ROAD_BRUSH_STYLE);

    /*********GRID**********/
    const QPen GRID_PEN(QColor(Qt::black));
    const int GRID_SIZE = 26;
}

#endif // GUICONSTANTS_H

#include "roadgui.h"

/**PROPERTIES INITIALIZE**/
const int RoadGUI::PEN_WIDTH = 0;
const Qt::PenStyle RoadGUI::PEN_STYLE = Qt::SolidLine;
const Qt::PenCapStyle RoadGUI::PEN_CAP = Qt::SquareCap;
const Qt::PenJoinStyle RoadGUI::PEN_JOIN = Qt::RoundJoin;

const QColor RoadGUI::PEN_COLOR = QColor(100, 100, 100, 0);
const QColor RoadGUI::GHOST_PEN_COLOR = QColor(100, 100, 100, 0);

const QPen RoadGUI::PEN(PEN_COLOR, PEN_WIDTH, PEN_STYLE, PEN_CAP, PEN_JOIN);
const QPen RoadGUI::GHOST_PEN(GHOST_PEN_COLOR, PEN_WIDTH, PEN_STYLE, PEN_CAP, PEN_JOIN);


const Qt::BrushStyle RoadGUI::BRUSH_STYLE = Qt::SolidPattern;
const QColor RoadGUI::BRUSH_COLOR = QColor(72, 72, 59);

const QColor RoadGUI::GHOST_BRUSH_COLOR = QColor(72, 72, 59, 127);

const QBrush RoadGUI::BRUSH(BRUSH_COLOR, BRUSH_STYLE);
const QBrush RoadGUI::GHOST_BRUSH(GHOST_BRUSH_COLOR, BRUSH_STYLE);

const unsigned int RoadGUI::SIDEWALK_WIDTH = 8;
const QColor RoadGUI::SIDEWALK_BRUSH_COLOR = QColor(155, 155, 132);
const QBrush RoadGUI::SIDEWALK_BRUSH(SIDEWALK_BRUSH_COLOR, BRUSH_STYLE);

RoadGUI::RoadGUI(unsigned int layer, Point firstPoint, Point secondPoint, bool ghost):
    Drawable(layer, ghost) {
    setRectangle(firstPoint, secondPoint);
}

RoadGUI::RoadGUI(unsigned int layer, Point point) : Drawable(layer, true) {
    setRectangle(point);
}

RoadGUI::~RoadGUI() {

}

void RoadGUI::setRectangle(Point first, Point second) {
    int diffX = second.getX() - first.getX();
    int diffY = second.getY() - first.getY();

    if (abs(diffX) < abs(diffY)) {
        vertical = true;
        if (diffY <= 0) {
            start = first;
            end = Point(first.getX(), second.getY());
        } else {
            start = Point(first.getX(), second.getY());
            end = first;
        }
    } else {
        vertical = false;
        if (diffX >= 0) {
            start = first;
            end = Point(second.getX(), first.getY());
        } else {
            start = Point(second.getX(), first.getY());
            end = first;
        }
    }

    roadRect = QRect(
                QPoint(start.getX() - (GridGUI::SIZE/2 - SIDEWALK_WIDTH),
                                       start.getY() + (GridGUI::SIZE/2 - SIDEWALK_WIDTH)),
                QPoint(end.getX() + (GridGUI::SIZE/2 - SIDEWALK_WIDTH),
                                     end.getY() - (GridGUI::SIZE/2 - SIDEWALK_WIDTH))
                );
    sidewalkRect = QRect(
                QPoint(start.getX() - GridGUI::SIZE/2,
                                       start.getY() + GridGUI::SIZE/2),
                QPoint(end.getX() + GridGUI::SIZE/2,
                                     end.getY() - GridGUI::SIZE/2)
                );
}

void RoadGUI::adjustPoints(Point& first, Point& second) {
    int diffX = second.getX() - first.getX();
    int diffY = second.getY() - first.getY();

    if (abs(diffX) < abs(diffY)) {
        second.setX(first.getX());
    } else {
        second.setY(first.getY());
    }

}

void RoadGUI::setRectangle(Point point) {
    if (!isGhost()) {
        throw std::exception();
    }
    roadRect = QRect(QPoint(point.getX() - (GridGUI::SIZE/2 - SIDEWALK_WIDTH),
                            point.getY() + (GridGUI::SIZE/2 - SIDEWALK_WIDTH)),
                     QPoint(point.getX() + (GridGUI::SIZE/2 - SIDEWALK_WIDTH),
                            point.getY() - (GridGUI::SIZE/2 - SIDEWALK_WIDTH))
                     );
}

void RoadGUI::drawSidewalk(QPainter &painter) const {
    painter.setPen(PEN);
    painter.setBrush(SIDEWALK_BRUSH);
    painter.drawRect(sidewalkRect);
}

void RoadGUI::draw(QPainter &painter) const {
    if(!isGhost()) {
        painter.setPen(PEN);
        painter.setBrush(BRUSH);
    } else {
        painter.setPen(GHOST_PEN);
        painter.setBrush(GHOST_BRUSH);
    }
    painter.drawRect(roadRect);
}

void RoadGUI::setTo(unsigned int x, unsigned int y) {
    /* DOES NOTHING ON PURPOSE */
    /* THEN DELETE IT */
}

bool RoadGUI::isVertical() const {
    return vertical;
}

std::tuple<Point, Point> RoadGUI::getEnds() const {
    return std::make_tuple(start, end);
}

bool RoadGUI::intersects(QRect &rectangle) const {
    return roadRect.intersects(rectangle);
}

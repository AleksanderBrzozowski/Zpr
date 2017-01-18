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

/*!
 * \brief RoadGUI::RoadGUI. Constructor.
 * \param firstPoint - One end of the road.
 * \param secondPoint - Other end of the road.
 * \param ghost - Bool flag tells whether object is ghost object.
 * \details Constructs object based on two points given as arguments.
 * Line created by points doesn't have to be horizontal or vertical.
 * Road is going to be made horizontal or vertical based on difference
 * between points (dx > dy).
 */
RoadGUI::RoadGUI(Point firstPoint, Point secondPoint, bool ghost):
    Drawable(ghost) {
    setRectangle(firstPoint, secondPoint);
}

/*!
 * \brief RoadGUI::RoadGUI. Constructor.
 * \param point - Point.
 * \details Creates temporary ghost road being just a square.
 */
RoadGUI::RoadGUI(Point point) : Drawable(true) {
    setRectangle(point);
}

RoadGUI::~RoadGUI() {

}

/*!
 * \brief RoadGUI::setRectangle.
 * \param first - One end of the road.
 * \param second - Other end of the road.
 * \details Function sets road to be between two given points.
 * Line created by points doesn't have to be horizontal or vertical.
 * Road is going to be made horizontal or vertical based on difference
 * between points (dx > dy).
 */
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

/*!
 * \brief RoadGUI::adjustPoints.
 * \param first - Reference to first point.
 * \param second - Reference to second point.
 * \details Function takes reference to two points and sets them in line
 * parallel to horizontal or vertical, based on difference between these
 * points (dx > dy).
 */
void RoadGUI::adjustPoints(Point& first, Point& second) {
    int diffX = second.getX() - first.getX();
    int diffY = second.getY() - first.getY();

    if (abs(diffX) < abs(diffY)) {
        second.setX(first.getX());
    } else {
        second.setY(first.getY());
    }

}

/*!
 * \brief RoadGUI::setRectangle.
 * \param point - Point of new road.
 * \details Function sets temporary ghost road in point given as argument.
 */
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

/*!
 * \brief RoadGUI::drawSidewalk.
 * \param painter - Reference to painter object.
 * \details Function draws sidewalk using painter given as an argument.
 * It uses brushes, and pens defined in object. Ghost roads doesnt have
 * sidewalks.
 */
void RoadGUI::drawSidewalk(QPainter &painter) const {
    painter.setPen(PEN);
    painter.setBrush(SIDEWALK_BRUSH);
    painter.drawRect(sidewalkRect);
}

/*!
 * \brief RoadGUI::draw
 * \param painter - Reference to painter object.
 * \details Function draws object using painter given as an argument.
 * It uses brushes, and pens defined in object, and base its choice on
 * whether it is ghost object or not.
 */
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
}

/*!
 * \brief RoadGUI::isVertical.
 * \return Returns flag whether function is vertical or not
 */
bool RoadGUI::isVertical() const {
    return vertical;
}

/*!
 * \brief RoadGUI::getEnds.
 * \return Returns tuple with two ends of road.
 */
std::tuple<Point, Point> RoadGUI::getEnds() const {
    return std::make_tuple(start, end);
}

/*!
 * \brief RoadGUI::intersects.
 * \param rectangle - QRect object that is being checked for intersection.
 * \return Bool value whether rectangles intersects.
 * \details Function checks whether current road's (not including sight range)
 * rectangle intersects rectangle given as argument and returns bool value.
 */
bool RoadGUI::intersects(QRect &rectangle) const {
    return roadRect.intersects(rectangle);
}

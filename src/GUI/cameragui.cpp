#include "cameragui.h"
#include "gridgui.h"

const unsigned int CameraGUI::CAM_RADIUS = 8;
const unsigned int CameraGUI::MAX_RANGE = 5 * GridGUI::SIZE;
const unsigned int CameraGUI::MIN_RANGE = 100;
const unsigned int CameraGUI::MAX_SPAN = 180;
const unsigned int CameraGUI::MIN_SPAN = 10;

const int CameraGUI::DEFAULT_SPAN = 60;
const int CameraGUI::DEFAULT_ANGLE = -DEFAULT_SPAN/2;
const unsigned int CameraGUI::DEFAULT_RANGE = 200;

const int CameraGUI::CAM_PEN_WIDTH = 2;
const Qt::PenStyle CameraGUI::CAM_PEN_STYLE = Qt::SolidLine;
const Qt::PenCapStyle CameraGUI::CAM_PEN_CAP = Qt::SquareCap;
const Qt::PenJoinStyle CameraGUI::CAM_PEN_JOIN = Qt::RoundJoin;

const QColor CameraGUI::CAM_PEN_COLOR = QColor(0, 0, 0);
const QColor CameraGUI::GHOST_CAM_PEN_COLOR = QColor(0, 0, 0, 127);

const QPen CameraGUI::CAM_PEN(CAM_PEN_COLOR, CAM_PEN_WIDTH, CAM_PEN_STYLE,
                   CAM_PEN_CAP, CAM_PEN_JOIN);
const QPen CameraGUI::GHOST_CAM_PEN(GHOST_CAM_PEN_COLOR, CAM_PEN_WIDTH,
                                    CAM_PEN_STYLE, CAM_PEN_CAP, CAM_PEN_JOIN);

const Qt::BrushStyle CameraGUI::CAM_BRUSH_STYLE = Qt::SolidPattern;
const QColor CameraGUI::CAM_BRUSH_COLOR = QColor(103, 74, 158);
const QColor CameraGUI::GHOST_CAM_BRUSH_COLOR = QColor(103, 74, 158, 127);

const QBrush CameraGUI::CAM_BRUSH(CAM_BRUSH_COLOR, CAM_BRUSH_STYLE);
const QBrush CameraGUI::GHOST_CAM_BRUSH(GHOST_CAM_BRUSH_COLOR, CAM_BRUSH_STYLE);

const int CameraGUI::RNG_PEN_WIDTH = 0;
const Qt::PenStyle CameraGUI::RNG_PEN_STYLE = Qt::SolidLine;
const Qt::PenCapStyle CameraGUI::RNG_PEN_CAP = Qt::SquareCap;
const Qt::PenJoinStyle CameraGUI::RNG_PEN_JOIN = Qt::RoundJoin;

const QColor CameraGUI::RNG_PEN_COLOR = QColor(0, 0, 0, 0);
const QColor CameraGUI::GHOST_RNG_PEN_COLOR = QColor(0, 0, 0, 0);

const QPen CameraGUI::RNG_PEN(RNG_PEN_COLOR, RNG_PEN_WIDTH, RNG_PEN_STYLE,
                   RNG_PEN_CAP, RNG_PEN_JOIN);
const QPen CameraGUI::GHOST_RNG_PEN(GHOST_RNG_PEN_COLOR, RNG_PEN_WIDTH, RNG_PEN_STYLE,
                                    RNG_PEN_CAP, RNG_PEN_JOIN);

const Qt::BrushStyle CameraGUI::RNG_BRUSH_STYLE = Qt::SolidPattern;
const QColor CameraGUI::RNG_BRUSH_COLOR = QColor(177, 156, 217, 127);
const QColor CameraGUI::GHOST_RNG_BRUSH_COLOR = QColor(177, 156, 217, 64);

const QBrush CameraGUI::RNG_BRUSH(RNG_BRUSH_COLOR, RNG_BRUSH_STYLE);
const QBrush CameraGUI::GHOST_RNG_BRUSH(GHOST_RNG_BRUSH_COLOR, RNG_BRUSH_STYLE);

/*!
 * \brief CameraGUI::CameraGUI. Constructor.
 * \param x - Position X of camera.
 * \param y - Position Y of camera.
 * \param span - camera's sight span. Unit is 1/16th of a degree.
 * \param angle - Direction of camera's sigh. Angle 0 is bottom of
 * sight starts paralell to x axis to the left. Increasing turns it
 * counterclockwise. Unit is 1/16th of a degree.
 * \param range - Camera's range of view.
 * \param ghost - Boolean tells whether object is ghost object or not.
 * \details Constructor creates camera object centered at point X, Y
 * given as parameters.
 */
CameraGUI::CameraGUI(unsigned int x, unsigned int y,
                     unsigned int span, int angle, unsigned int range,
                     bool ghost) : Drawable(ghost), span(16*span), angle(16*angle),
                     camRect(x - CAM_RADIUS/2, y - CAM_RADIUS/2, CAM_RADIUS, CAM_RADIUS),
                     rngRect(x - range, y - range, 2*range, 2*range) {

}

/*!
 * \brief CameraGUI::CameraGUI. Constructor.
 * \param position - Position of a camera.
 * \details Constructor creates camera centered at a position given as
 * parameter. It's range of view is set to zero. Object constructed
 * with that function is always ghost object.
 */
CameraGUI::CameraGUI(Point position) : Drawable(true) {
    setRectangle(position);
}

/*!
 * \brief CameraGUI::CameraGUI. Constructor.
 * \param position - Position of a camera.
 * \param range - Point where camera's range ends.
 * \param span - cmaera's cpan. Unit is 1/16th of a degree.
 * \param ghost - Boolean tells whether object is ghost object or not.
 * \details Constructor creates camera a given point with range ending and
 * another point given as argument.
 */
CameraGUI::CameraGUI(Point position, Point range, int span, bool ghost) :
    Drawable(ghost), span(span) {
    setRectangle(position, range);
}

CameraGUI::~CameraGUI() {

}

/*!
 * \brief CameraGUI::draw.
 * \param painter - Reference to painter object.
 * \details Function draws object using painter given as an argument.
 * It uses brushes, and pens defined in object, and base its choice on
 * whether it is ghost object or not.
 */
void CameraGUI::draw(QPainter &painter) const {
    if (!isGhost()) {
        painter.setPen(RNG_PEN);
        painter.setBrush(RNG_BRUSH);
    } else {
        painter.setPen(GHOST_RNG_PEN);
        painter.setBrush(GHOST_RNG_BRUSH);
    }
    painter.drawPie(rngRect, angle, span);
    if (!isGhost()) {
        painter.setPen(CAM_PEN);
        painter.setBrush(CAM_BRUSH);
    } else {
        painter.setPen(GHOST_CAM_PEN);
        painter.setBrush(GHOST_CAM_BRUSH);
    }
    painter.drawEllipse(camRect);
}


/*!
 * \brief CameraGUI::intersects.
 * \param rectangle - QRect object that is being checked for intersection.
 * \return Bool value whether rectangles intersects.
 * \details Function checks whether current camera's (not including sight range)
 * rectangle intersects rectangle given as argument and returns bool value.
 */
bool CameraGUI::intersects(QRect &rectangle) const {
    return camRect.intersects(rectangle);
}

/*!
 * \brief CameraGUI::decRange.
 * \details Decrements range by 10 pixels unless it is minimum already.
 * Limits are defined in object.
 */
void CameraGUI::decRange() {
	if (rngRect.width() > 2 * MIN_RANGE) {
		int x1;
		int y1;
		int x2;
		int y2;
		rngRect.getCoords(&x1, &y1, &x2, &y2);
		rngRect.setCoords(x1 + 10, y1 + 10, x2 - 10, y2 - 10);
	}
}

/*!
 * \brief CameraGUI::incRange.
 * \details Increments range by 10 pixels unless it is maximum already.
 * Limits are defined in object.
 */
void CameraGUI::incRange() {
	if (static_cast<unsigned int>(rngRect.width()) < 2 * MAX_RANGE) {
		int x1;
		int y1;
		int x2;
		int y2;
		rngRect.getCoords(&x1, &y1, &x2, &y2);
		rngRect.setCoords(x1 - 10, y1 - 10, x2 + 10, y2 + 10);
	}
}

/*!
 * \brief CameraGUI::rotClockwise.
 * \details Rotates camera's view by 1 degree clockwise.
 */
void CameraGUI::rotClockwise() {
    angle -= 16;
    if (angle < -16*180)
        angle = 16*180;
}

/*!
 * \brief CameraGUI::rotCounterclockwise
 * \details Rotates camera's view by 1 degree counterclockwise.
 */
void CameraGUI::rotCounterclockwise() {
    angle += 16;
    if (angle > 16*180)
        angle = - 16*180;
}

/*!
 * \brief CameraGUI::incSpan.
 * \brief Increments camera's view span by 1 degree unless it is maximum already.
 * Limits are defined in object.
 */
void CameraGUI::incSpan() {
	if (span < 16 * MAX_SPAN) {
		span += 16;
		angle -= 8;
	}
}

/*!
 * \brief CameraGUI::decSpan.
 * \details Decrements camera's view span by 1 degree unless it is minimum already.
 * Limits are defined in object.
 */
void CameraGUI::decSpan() {
	if (span > 16 * MIN_SPAN) {
		span -= 16;
		angle += 8;
	}
}

/*!
 * \brief CameraGUI::getAngle
 * \return Returns current angle. Unit is 1/16th of degree.
 */
int CameraGUI::getAngle() {
    return angle;
}

/*!
 * \brief CameraGUI::getSpan
 * \return Returns current span. Unit is 1/16th of degree.
 */
int CameraGUI::getSpan() {
    return span;
}

/*!
 * \brief CameraGUI::getRange
 * \return Returns current range. Units are pixels.
 */
int CameraGUI::getRange() {
    return rngRect.width()/2;
}

void CameraGUI::setTo(unsigned int x, unsigned int y) {
}

/*!
 * \brief CameraGUI::setRectangle.
 * \param point - New location of camera.
 * \details Sets camera to given point and resets its range to 0.
 */
void CameraGUI::setRectangle(Point point) {
    camRect.setCoords(point.getX() - CAM_RADIUS/2, point.getY() - CAM_RADIUS/2,
                      point.getX() + CAM_RADIUS/2, point.getY() + CAM_RADIUS/2);
    rngRect.setCoords(point.getX() - CAM_RADIUS/2, point.getY() - CAM_RADIUS/2,
                      point.getX() + CAM_RADIUS/2, point.getY() + CAM_RADIUS/2);
}

/*!
 * \brief CameraGUI::setRectangle.
 * \param first - New location of camera.
 * \param second - Furthest point seen by camera.
 * \details Sets camera to point given as first parameter. It's range is given
 * by second parameter.
 */
void CameraGUI::setRectangle(Point first, Point second) {
    camRect.setCoords(first.getX() - CAM_RADIUS/2, first.getY() - CAM_RADIUS/2,
                      first.getX() + CAM_RADIUS/2, first.getY() + CAM_RADIUS/2);
    int dx = first.getX() - second.getX();
    int dy = first.getY() - second.getY();
    int range = static_cast<int>(sqrt(static_cast<double>(dx * dx + dy * dy)));
    rngRect.setCoords(first.getX() - range, first.getY() - range,
                  first.getX() + range, first.getY() + range);
        angle = -(std::atan2(dy, dx) * 16 * 180 / M_PI) - span/2 + 180 * 16;
}

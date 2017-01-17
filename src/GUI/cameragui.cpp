#include "cameragui.h"
#include "gridgui.h"

const unsigned int CameraGUI::CAM_RADIUS = 8;
const unsigned int CameraGUI::MAX_RANGE = 5 * GridGUI::SIZE;
const unsigned int CameraGUI::MIN_RANGE = 100;
const unsigned int CameraGUI::MAX_SPAN = 180;
const unsigned int CameraGUI::MIN_SPAN = 10;

const unsigned int CameraGUI::DEFAULT_SPAN = 60;
const unsigned int CameraGUI::DEFAULT_ANGLE = -DEFAULT_SPAN/2;
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

CameraGUI::CameraGUI(unsigned int layer, unsigned int x, unsigned int y,
                     unsigned int span, int angle, unsigned int range,
                     bool ghost) : Drawable(layer, ghost), span(16*span), angle(16*angle),
                     camRect(x - CAM_RADIUS/2, y - CAM_RADIUS/2, CAM_RADIUS, CAM_RADIUS),
                     rngRect(x - range, y - range, 2*range, 2*range) {

}

CameraGUI::CameraGUI(unsigned int layer, Point position) : Drawable(layer, true) {
    setRectangle(position);
}

CameraGUI::CameraGUI(unsigned int layer, Point position, Point range, int span, bool ghost) :
    Drawable(layer, ghost), span(span) {
    setRectangle(position, range);
}

CameraGUI::~CameraGUI() {

}

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

bool CameraGUI::intersects(QRect &rectangle) const {
    return camRect.intersects(rectangle);
}

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

void CameraGUI::incRange() {
	if (rngRect.width() < 2 * MAX_RANGE) {
		int x1;
		int y1;
		int x2;
		int y2;
		rngRect.getCoords(&x1, &y1, &x2, &y2);
		rngRect.setCoords(x1 - 10, y1 - 10, x2 + 10, y2 + 10);
	}
}

void CameraGUI::rotClockwise() {
    angle -= 16;
    if (angle < -16*180)
        angle = 16*180;
}

void CameraGUI::rotCounterclockwise() {
    angle += 16;
    if (angle > 16*180)
        angle = - 16*180;
}

void CameraGUI::incSpan() {
	if (span < 16 * MAX_SPAN) {
		span += 16;
		angle -= 8;
	}
}

void CameraGUI::decSpan() {
	if (span > 16 * MIN_SPAN) {
		span -= 16;
		angle += 8;
	}
}

int CameraGUI::getAngle() {
    return angle;
}

int CameraGUI::getSpan() {
    return span;
}

int CameraGUI::getRange() {
    return rngRect.width()/2;
}

void CameraGUI::setTo(unsigned int x, unsigned int y) {

}

void CameraGUI::setRectangle(Point point) {
    camRect.moveTo(point.getX() - CAM_RADIUS/2, point.getY() - CAM_RADIUS/2);
    rngRect.moveTo(point.getX() - rngRect.width()/2, point.getY() - rngRect.height()/2);
}

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

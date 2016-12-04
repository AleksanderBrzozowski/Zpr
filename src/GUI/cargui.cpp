#include "cargui.h"


/**PROPERTIES INITIALIZATION**/
const int CarGUI::WIDTH = 10;
const int CarGUI::HEIGHT = 10;

const int CarGUI::PEN_WIDTH = 2;
const Qt::PenStyle CarGUI::PEN_STYLE = Qt::SolidLine;
const Qt::PenCapStyle CarGUI::PEN_CAP = Qt::SquareCap;
const Qt::PenJoinStyle CarGUI::PEN_JOIN = Qt::RoundJoin;

const QColor CarGUI::PEN_COLOR = QColor(0, 0, 0);
const QColor CarGUI::GHOST_PEN_COLOR = QColor(0, 0, 0, 127);

const QPen CarGUI::PEN(PEN_COLOR, PEN_WIDTH, PEN_STYLE,
                           PEN_CAP, PEN_JOIN);
const QPen CarGUI::GHOST_PEN(GHOST_PEN_COLOR, PEN_WIDTH,
                           PEN_STYLE, PEN_CAP, PEN_JOIN);

const Qt::BrushStyle CarGUI::BRUSH_STYLE = Qt::SolidPattern;
const QColor CarGUI::BRUSH_COLOR = QColor(0, 0, 200);
const QColor CarGUI::GHOST_BRUSH_COLOR = QColor(0, 0, 200, 127);

const QBrush CarGUI::BRUSH(BRUSH_COLOR, BRUSH_STYLE);
const QBrush CarGUI::GHOST_BRUSH(GHOST_BRUSH_COLOR, BRUSH_STYLE);



CarGUI::CarGUI(unsigned int layer, QRect carRect, bool ghost) :
    Drawable(layer, ghost), carRect(carRect) {

}

CarGUI::CarGUI(unsigned int layer, int x, int y, bool ghost) :
    Drawable(layer, ghost),
    carRect(x - WIDTH/2, y - HEIGHT/2,
            WIDTH, HEIGHT) {

}

CarGUI::~CarGUI() {

}

void CarGUI::setTo(int x, int y) {
    carRect.setCoords(x - WIDTH/2, y - HEIGHT/2,
                      x + WIDTH/2, y + HEIGHT/2);
}

void CarGUI::draw(QPainter &painter) {
    if(!isGhost()) {
        painter.setPen(PEN);
        painter.setBrush(BRUSH);
    } else {
        painter.setPen(GHOST_PEN);
        painter.setBrush(GHOST_BRUSH);
    }
    painter.drawRect(carRect);
}

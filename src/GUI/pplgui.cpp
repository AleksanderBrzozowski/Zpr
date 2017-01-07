#include "pplgui.h"

/**PROPERTIES INITIALIZATION**/
const int PplGUI::RADIUS = 5;

const int PplGUI::PEN_WIDTH = 2;
const Qt::PenStyle PplGUI::PEN_STYLE = Qt::SolidLine;
const Qt::PenCapStyle PplGUI::PEN_CAP = Qt::SquareCap;
const Qt::PenJoinStyle PplGUI::PEN_JOIN = Qt::RoundJoin;
const QColor PplGUI::PEN_COLOR = Qt::black;

const QPen PplGUI::PEN(PEN_COLOR, PEN_WIDTH, PEN_STYLE,
                   PEN_CAP, PEN_JOIN);

const Qt::BrushStyle PplGUI::BRUSH_STYLE = Qt::SolidPattern;
const QColor PplGUI::BRUSH_COLOR = QColor(255, 105, 97);

const QBrush PplGUI::BRUSH(BRUSH_COLOR, BRUSH_STYLE);

PplGUI::PplGUI(unsigned int layer, QRect pplRect, bool ghost) :
    Drawable(layer, ghost), pplRect(pplRect){

}

PplGUI::PplGUI(unsigned int layer, unsigned int x, unsigned int y, bool ghost) :
    Drawable(layer, ghost),
    pplRect(x - RADIUS/2, y - RADIUS/2,
            RADIUS, RADIUS) {

}

PplGUI::~PplGUI() {

}

void PplGUI::setTo(unsigned int x, unsigned int y) {
    pplRect.setCoords(x - RADIUS/2, y - RADIUS/2,
                      x + RADIUS/2, y + RADIUS/2);
}

void PplGUI::draw(QPainter &painter) const {
    painter.setPen(PEN);
    painter.setBrush(BRUSH);
    painter.drawEllipse(pplRect);
}

bool PplGUI::intersects(QRect &rectangle) const {
    return pplRect.intersects(rectangle);
}

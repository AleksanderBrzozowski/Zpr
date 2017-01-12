#include "buildinggui.h"

/**PROPERTIES INITIALIZE**/
const int BuildingGUI::PEN_WIDTH = 2;
const Qt::PenStyle BuildingGUI::PEN_STYLE = Qt::SolidLine;
const Qt::PenCapStyle BuildingGUI::PEN_CAP = Qt::RoundCap;
const Qt::PenJoinStyle BuildingGUI::PEN_JOIN = Qt::RoundJoin;

const QColor BuildingGUI::PEN_COLOR = QColor(0, 0, 0, 255);
const QColor BuildingGUI::GHOST_PEN_COLOR = QColor(0, 0, 0, 127);

const QPen BuildingGUI::PEN(PEN_COLOR, PEN_WIDTH, PEN_STYLE, PEN_CAP, PEN_JOIN);
const QPen BuildingGUI::GHOST_PEN(GHOST_PEN_COLOR, PEN_WIDTH, PEN_STYLE, PEN_CAP, PEN_JOIN);


const Qt::BrushStyle BuildingGUI::BRUSH_STYLE = Qt::SolidPattern;
const QColor BuildingGUI::BRUSH_COLOR = QColor(255, 179, 71);

const QColor BuildingGUI::GHOST_BRUSH_COLOR = QColor(255, 179, 71, 127);

const QBrush BuildingGUI::BRUSH(BRUSH_COLOR, BRUSH_STYLE);
const QBrush BuildingGUI::GHOST_BRUSH(GHOST_BRUSH_COLOR, BRUSH_STYLE);

BuildingGUI::BuildingGUI(unsigned int layer, QRect buildingRect, bool ghost) :
    Drawable(layer, ghost), buildingRect(buildingRect) {

}

BuildingGUI::BuildingGUI(unsigned int layer, unsigned int x, unsigned int y,
                         unsigned int width, unsigned int height, bool ghost) :
    Drawable(layer, ghost), buildingRect(x - GridGUI::SIZE/2, y - GridGUI::SIZE/2, width, height) {

}

BuildingGUI::~BuildingGUI() {

}

void BuildingGUI::draw(QPainter &painter) const {
    if(!isGhost()) {
        painter.setPen(PEN);
        painter.setBrush(BRUSH);
    } else {
        painter.setPen(GHOST_PEN);
        painter.setBrush(GHOST_BRUSH);
    }
    painter.drawRect(buildingRect);
}

void BuildingGUI::setTo(unsigned int x, unsigned int y) {
//    buildingRect.setCoords(x - buildingRect.width()/2, y - buildingRect.height()/2,
//                           x + buildingRect.width()/2, y + buildingRect.height()/2);
    buildingRect.moveTo(x - GridGUI::SIZE/2, y - GridGUI::SIZE/2);
}

bool BuildingGUI::intersects(QRect &rectangle) const {
    return buildingRect.intersects(rectangle);
}

#include "gridgui.h"

/**INITIALIZE PROPERTIES**/
const QPen GridGUI::PEN(QColor(255, 255, 255, 80));
const int GridGUI::SIZE = 32;

GridGUI::GridGUI(unsigned int width, unsigned int height) :
    Drawable(false), height(height), width(width) {
}

GridGUI::~GridGUI() {

}

void GridGUI::draw(QPainter &painter) const {
    painter.setPen(PEN);
    for (int x = 0; x < width; x += SIZE) {
        painter.drawLine(x, 0, x, height);
    }
    for (int y = 0; y < height; y += SIZE) {
        painter.drawLine(0, y, width, y);
    }
}

void GridGUI::setTo(unsigned int x, unsigned int y) {

}

bool GridGUI::intersects(QRect &rectangle) const {
    return false;
}

#include "gridgui.h"

/**INITIALIZE PROPERTIES**/
const QPen GridGUI::PEN(QColor(255, 255, 255, 80));
const int GridGUI::SIZE = 26;

GridGUI::GridGUI(unsigned int layer, unsigned int width, unsigned int height) :
    Drawable(layer, false), height(height), width(width) {
}

GridGUI::~GridGUI() {

}

void GridGUI::draw(QPainter &painter) {
    painter.setPen(PEN);
    for (int x = 0; x < width; x += SIZE) {
        painter.drawLine(x, 0, x, height);
    }
    for (int y = 0; y < height; y += SIZE) {
        painter.drawLine(0, y, width, y);
    }
}

void GridGUI::setTo(int x, int y) {

}

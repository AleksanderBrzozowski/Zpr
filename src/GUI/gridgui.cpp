#include "gridgui.h"

GridGUI::GridGUI(unsigned int layer, unsigned int width, unsigned int height) :
    Drawable(layer), height(height), width(width) {
}

GridGUI::~GridGUI() {

}

void GridGUI::draw(QPainter &painter) {
    painter.setPen(GUI::GRID_PEN);
    for (int x = 0; x < width; x += GUI::GRID_SIZE) {
        painter.drawLine(x, 0, x, height);
    }
    for (int y = 0; y < height; y += GUI::GRID_SIZE) {
        painter.drawLine(0, y, width, y);
    }
}

void GridGUI::setTo(int x, int y) {

}

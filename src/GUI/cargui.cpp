#include "cargui.h"

CarGUI::CarGUI(unsigned int layer, QRect carRect) :
    Drawable(layer), carRect(carRect) {

}

CarGUI::CarGUI(unsigned int layer, int x, int y) :
    Drawable(layer),
    carRect(x - GUI::CAR_WIDTH/2, y - GUI::CAR_HEIGHT/2,
            GUI::CAR_WIDTH, GUI::CAR_HEIGHT) {

}

CarGUI::~CarGUI() {

}

void CarGUI::setTo(int x, int y) {
    carRect.setCoords(x - GUI::CAR_WIDTH/2, y - GUI::CAR_HEIGHT/2,
                      x + GUI::CAR_WIDTH/2, y + GUI::CAR_HEIGHT/2);
}

void CarGUI::draw(QPainter &painter) {
    painter.setPen(GUI::CAR_PEN);
    painter.setBrush(GUI::CAR_BRUSH);
    painter.drawRect(carRect);
}

#include "pplgui.h"

PplGUI::PplGUI(unsigned int layer, QRect pplRect) :
    Drawable(layer), pplRect(pplRect){

}

PplGUI::PplGUI(unsigned int layer, int x, int y) :
    Drawable(layer),
    pplRect(x - GUI::PPL_RADIUS/2, y - GUI::PPL_RADIUS/2,
            GUI::PPL_RADIUS, GUI::PPL_RADIUS) {

}

PplGUI::~PplGUI() {

}

void PplGUI::setTo(int x, int y) {
    pplRect.setCoords(x - GUI::PPL_RADIUS/2, y - GUI::PPL_RADIUS/2,
                      x + GUI::PPL_RADIUS/2, y + GUI::PPL_RADIUS/2);
}

void PplGUI::draw(QPainter &painter) {
    painter.setPen(GUI::PPL_PEN);
    painter.setBrush(GUI::PPL_BRUSH);
    painter.drawEllipse(pplRect);
}

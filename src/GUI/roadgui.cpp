#include "roadgui.h"

RoadGUI::RoadGUI(unsigned int layer, Point begin, Point end) : Drawable(layer) {
    int diffX = begin.getX() - end.getX();
    int diffY = begin.getY() - end.getY();

    int sgnDiffX = diffX >= 0 ? 1 : -1;
    int sgnDiffY = diffY >= 0 ? 1 : -1;

    if (abs(diffX) > abs(diffY)) {
        roadRect = QRect(
                    QPoint(begin.getX() + sgnDiffX * GUI::GRID_SIZE/2,
                           begin.getY() + sgnDiffX * GUI::GRID_SIZE/2),
                    QPoint(end.getX() - sgnDiffX * GUI::GRID_SIZE/2,
                           begin.getY() - sgnDiffX * GUI::GRID_SIZE/2));
    }
    else {
        roadRect = QRect(
                    QPoint(begin.getX() + sgnDiffY * GUI::GRID_SIZE/2,
                           begin.getY() + sgnDiffY * GUI::GRID_SIZE/2),
                    QPoint(begin.getX() - sgnDiffY * GUI::GRID_SIZE/2,
                           end.getY() - sgnDiffY * GUI::GRID_SIZE/2));
    }


}

RoadGUI::~RoadGUI() {

}

void RoadGUI::draw(QPainter &painter) {
    painter.setPen(GUI::ROAD_PEN);
    painter.setBrush(GUI::ROAD_BRUSH);
    painter.drawRect(roadRect);
}

void RoadGUI::setTo(int x, int y) {
    /* DOES NOTHING ON PURPOSE */
}

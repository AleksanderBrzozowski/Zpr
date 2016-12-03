#include "roadgui.h"

RoadGUI::RoadGUI(unsigned int layer, Point first, Point second) : Drawable(layer) {
    int diffX = first.getX() - second.getX();
    int diffY = first.getY() - second.getY();

    if (abs(diffX) < abs(diffY)) {
        if (diffX >= 0) {
            start = first;
            end = Point(first.getX(), second.getY());
        } else {
            start = Point(first.getX(), second.getY());
            end = first;
        }
    } else {
        if (diffY >= 0) {
            start = first;
            end = Point(second.getX(), first.getY());
        } else {
            start = Point(second.getX(), first.getY());
            end = first;
        }
    }
    int sgnDiffX = diffX >= 0 ? 1 : -1;
    int sgnDiffY = diffY >= 0 ? 1 : -1;

    roadRect = QRect(
                QPoint(start.getX() - GUI::GRID_SIZE/2, start.getY() + GUI::GRID_SIZE/2),
                QPoint(end.getX() + GUI::GRID_SIZE/2, end.getY() - GUI::GRID_SIZE/2)
                );

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

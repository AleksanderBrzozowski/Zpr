#include "eventinterpreter.h"

EventInterpreter::EventInterpreter() : currentOption(Option::optionDoNothing) {

}

std::shared_ptr<Drawable> EventInterpreter::setCurrentOption(Option option) {
    currentOption = option;
    switch(option) {
        case Option::optionSetRoad:
            ghostRoad = std::shared_ptr<RoadGUI>(new RoadGUI(0, Point(0, 0)));
            hasAnchor = false;
            return ghostRoad;
            break;
        case Option::optionSetCar:
            ghostObject = std::shared_ptr<Drawable>(new CarGUI(0, 0, 0, true));
            hasAnchor = false;
            return ghostObject;
            break;
        case Option::optionDoNothing:
        default:
            ghostObject.reset();
            ghostRoad.reset();
            hasAnchor = false;
            return std::shared_ptr<Drawable>(nullptr);
            break;
    }
}

void EventInterpreter::mouseClicked(int x, int y) {
    switch(currentOption) {
        case Option::optionSetRoad:
            if (!hasAnchor) {
                anchor = Point(x, y);
                snapToGrid(anchor);
                hasAnchor = true;
            } else {
                Point end(x, y);
                snapToGrid(end);
                emit roadCreated(new RoadGUI(3, anchor, end));
                hasAnchor = false;
            }
            break;
        case Option::optionSetCar:
            emit drawableCreated(new CarGUI(2, x, y));
            hasAnchor = false;
            break;
        case Option::optionDoNothing:
        default:
            hasAnchor = false;
            break;
    }
}

void EventInterpreter::snapToGrid(Point &point) {
    int x = point.getX() / GridGUI::SIZE;
    int y = point.getY() / GridGUI::SIZE;
    point.setX(x * GridGUI::SIZE + GridGUI::SIZE/2);
    point.setY(y * GridGUI::SIZE + GridGUI::SIZE/2);
}

void EventInterpreter::mouseMoved(int x, int y) {
    Point point(x, y);
    switch(currentOption) {
        case Option::optionSetRoad:
            snapToGrid(point);
            if (!hasAnchor) {
                ghostRoad->setRectangle(point);
            } else {
                ghostRoad->setRectangle(anchor, point);
            }
            break;
        case Option::optionSetCar:
            ghostObject->setTo(x, y);
            break;
        case Option::optionDoNothing:
        default:
            break;
    }

}

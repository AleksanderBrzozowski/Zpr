#include "eventinterpreter.h"

EventInterpreter::EventInterpreter() : currentOption(Option::doNothing) {

}

std::shared_ptr<Drawable> EventInterpreter::setCurrentOption(Option option) {
    if (trafficControl == nullptr)
        currentOption = Option::doNothing;
    else
        currentOption = option;

    switch(option) {
    case Option::setRoad:
        ghostRoad = std::shared_ptr<RoadGUI>(new RoadGUI(0, Point(0, 0)));
        hasAnchor = false;
        return ghostRoad;
        break;
    case Option::setCar:
        ghostObject = std::shared_ptr<Drawable>(new CarGUI(0, 0, 0, false, true));
        hasAnchor = false;
        return ghostObject;
        break;
    case Option::setFastCar:
        ghostObject = std::shared_ptr<Drawable>(new CarGUI(0, 0, 0, true, true));
        hasAnchor = false;
        return ghostObject;
        break;
    case Option::doNothing:
    default:
        ghostObject.reset();
        ghostRoad.reset();
        hasAnchor = false;
        return std::shared_ptr<Drawable>(nullptr);
        break;
    }
}

EventInterpreter::Option EventInterpreter::getCurrentOption() {
    return currentOption;
}

void EventInterpreter::mouseClicked(int x, int y) {
    Point point(x, y);
    snapToGrid(point);
    switch(currentOption) {
    case Option::setRoad:
        if (!hasAnchor) {
            anchor = point;
            hasAnchor = true;
        } else {
            RoadGUI::adjustPoints(anchor, point);
            PtrToConstPoint srcPtr = std::make_shared<Point>(anchor.getX(), anchor.getY());
            PtrToConstPoint dstPtr = std::make_shared<Point>(point.getX(), point.getY());
            trafficControl->createRoute(srcPtr, dstPtr);
            emit roadCreated(new RoadGUI(3, anchor, point));
            hasAnchor = false;
        }
        break;
    case Option::setCar:
        if (!hasAnchor) {
            anchor = point;
            hasAnchor = true;
        } else {
            //emit drawableCreated(new CarGUI(2, anchor.getX(), anchor.getY()));
            PtrToConstPoint srcPtr = std::make_shared<Point>(anchor.getX(), anchor.getY());
            PtrToConstPoint dstPtr = std::make_shared<Point>(point.getX(), point.getY());
            trafficControl->createNewCar(srcPtr, dstPtr, CarGUI::CAR_SPEED);
            hasAnchor = false;
        }
        break;
    case Option::setFastCar:
        if (!hasAnchor) {
            anchor = point;
            hasAnchor = true;
        } else {
            //emit drawableCreated(new CarGUI(2, anchor.getX(), anchor.getY()));
            PtrToConstPoint srcPtr = std::make_shared<Point>(anchor.getX(), anchor.getY());
            PtrToConstPoint dstPtr = std::make_shared<Point>(point.getX(), point.getY());
            trafficControl->createNewCar(srcPtr, dstPtr, CarGUI::FAST_CAR_SPEED);
            hasAnchor = false;
        }
        break;
    case Option::doNothing:
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
    snapToGrid(point);
    switch(currentOption) {
    case Option::setRoad:
        if (!hasAnchor) {
            ghostRoad->setRectangle(point);
        } else {
            ghostRoad->setRectangle(anchor, point);
        }
        break;
    case Option::setFastCar:
    case Option::setCar:
        ghostObject->setTo(x, y);
        if (!hasAnchor) {
            ghostObject->setTo(point.getX(), point.getY());
        } else {
            ghostObject->setTo(anchor.getX(), anchor.getY());
        }
        break;
    case Option::doNothing:
    default:
        break;
    }

}

void EventInterpreter::setTrafficControl(std::shared_ptr<TrafficControl> tc) {
    trafficControl = tc;
}

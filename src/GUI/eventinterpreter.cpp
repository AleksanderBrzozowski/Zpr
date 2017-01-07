#include "eventinterpreter.h"
#include "mainwindow.h"

EventInterpreter::EventInterpreter() : currentOption(Option::doNothing), anchorValid(false) {

}

std::shared_ptr<Drawable> EventInterpreter::setCurrentOption(Option option) {
    if (trafficControl == nullptr)
        currentOption = Option::doNothing;
    else
        currentOption = option;

    switch(option) {
    case Option::setRoad:
        ghostRoad = std::shared_ptr<RoadGUI>(new RoadGUI(0, Point(0, 0)));
        anchorValid = false;
        return ghostRoad;
        break;
    case Option::setCar:
        ghostObject = std::shared_ptr<Drawable>(new CarGUI(0, 0, 0, false, true));
        anchorValid = false;
        return ghostObject;
        break;
    case Option::setFastCar:
        ghostObject = std::shared_ptr<Drawable>(new CarGUI(0, 0, 0, true, true));
        anchorValid = false;
        return ghostObject;
        break;
    case Option::setBuilding:
        ghostObject = std::shared_ptr<Drawable>(new BuildingGUI(0, 0, 0, GridGUI::SIZE,
                                                               GridGUI::SIZE, true));
        anchorValid = false;
        return ghostObject;
        break;
    case Option::doNothing:
    default:
        ghostObject.reset();
        ghostRoad.reset();
        MainWindow::getInstance().resetLabel();
        anchorValid = false;
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
        if (!anchorValid) {
            anchor = point;
            anchorValid = true;
        } else {
            RoadGUI::adjustPoints(anchor, point);
            PtrToConstPoint srcPtr = std::make_shared<Point>(anchor.getX(), anchor.getY());
            PtrToConstPoint dstPtr = std::make_shared<Point>(point.getX(), point.getY());
            trafficControl->createRoute(srcPtr, dstPtr);
            emit roadCreated(new RoadGUI(3, anchor, point));
            anchorValid = false;
        }
        break;
    case Option::setCar:
        if (!anchorValid) {
            anchor = point;
            anchorValid = true;
        } else {
            //emit drawableCreated(new CarGUI(2, anchor.getX(), anchor.getY()));
            PtrToConstPoint srcPtr = std::make_shared<Point>(anchor.getX(), anchor.getY());
            PtrToConstPoint dstPtr = std::make_shared<Point>(point.getX(), point.getY());
            trafficControl->createNewCar(srcPtr, dstPtr, CarGUI::CAR_SPEED);
            anchorValid = false;
        }
        break;
    case Option::setFastCar:
        if (!anchorValid) {
            anchor = point;
            anchorValid = true;
        } else {
            //emit drawableCreated(new CarGUI(2, anchor.getX(), anchor.getY()));
            PtrToConstPoint srcPtr = std::make_shared<Point>(anchor.getX(), anchor.getY());
            PtrToConstPoint dstPtr = std::make_shared<Point>(point.getX(), point.getY());
            trafficControl->createNewCar(srcPtr, dstPtr, CarGUI::FAST_CAR_SPEED);
            anchorValid = false;
        }
        break;
    case Option::setBuilding:

        break;
    case Option::doNothing:
    default:
        anchorValid = false;
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
        if (!anchorValid) {
            ghostRoad->setRectangle(point);
        } else {
            ghostRoad->setRectangle(anchor, point);
        }
        break;
    case Option::setFastCar:
    case Option::setCar:
        ghostObject->setTo(x, y);
        if (!anchorValid) {
            ghostObject->setTo(point.getX(), point.getY());
        } else {
            ghostObject->setTo(anchor.getX(), anchor.getY());
        }
        break;
    case Option::setBuilding:
        ghostObject->setTo(point.getX(), point.getY());
        break;
    case Option::doNothing:
    default:
        break;
    }

}

void EventInterpreter::setTrafficControl(std::shared_ptr<TrafficControl> tc) {
    trafficControl = tc;
}

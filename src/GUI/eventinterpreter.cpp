#include "eventinterpreter.h"
#include "mainwindow.h"

EventInterpreter::EventInterpreter() : currentOption(Option::doNothing), anchorValid(false) {

}

std::shared_ptr<Drawable> EventInterpreter::setCurrentOption(Option option) {
    if (map == nullptr)
        currentOption = Option::doNothing;
    else
        currentOption = option;

    anchorValid = false;
    switch(option) {
    case Option::setRoad:
        ghostRoad = std::shared_ptr<RoadGUI>(new RoadGUI(0, Point(0, 0)));
        return ghostRoad;
        break;
    case Option::setCar:
        ghostObject = std::shared_ptr<Drawable>(new CarGUI(0, 0, 0, false, true));
        return ghostObject;
        break;
    case Option::setFastCar:
        ghostObject = std::shared_ptr<Drawable>(new CarGUI(0, 0, 0, true, true));
        return ghostObject;
        break;
    case Option::setBuilding:
        ghostObject = std::shared_ptr<Drawable>(new BuildingGUI(0, 0, 0, GridGUI::SIZE,
                                                               GridGUI::SIZE, true));
        return ghostObject;
        break;
    case Option::setCamera:
        ghostCamera = std::shared_ptr<CameraGUI>(new CameraGUI(0, 0, 0, CameraGUI::DEFAULT_SPAN,
                                                              CameraGUI::DEFAULT_ANGLE,
                                                              CameraGUI::DEFAULT_RANGE, true));
        return ghostCamera;
        break;
    case Option::setHuman:
        ghostObject = std::shared_ptr<Drawable>(new PplGUI(0, 0, 0, true));
        return ghostObject;
        break;
    case Option::doNothing:
    default:
        ghostObject.reset();
        ghostRoad.reset();
        ghostCamera.reset();
        MainWindow::getInstance().resetLabel();
        return std::shared_ptr<Drawable>(nullptr);
        break;
    }
}

EventInterpreter::Option EventInterpreter::getCurrentOption() {
    return currentOption;
}

void EventInterpreter::mouseClicked(int x, int y) {
    Point point(x, y);
    switch(currentOption) {
    case Option::setRoad:
        snapToGridCenter(point);
        if (!anchorValid) {
            anchor = point;
            anchorValid = true;
        } else {
            RoadGUI::adjustPoints(anchor, point);
            PtrToConstPoint srcPtr = std::make_shared<Point>(anchor.getX(), anchor.getY());
            PtrToConstPoint dstPtr = std::make_shared<Point>(point.getX(), point.getY());
            if (map->createRoad(srcPtr, dstPtr))
                emit roadCreated(new RoadGUI(3, anchor, point));
            anchorValid = false;
        }
        break;
    case Option::setCar:
        snapToGridCenter(point);
        if (!anchorValid) {
            anchor = point;
            anchorValid = true;
        } else {
            //emit drawableCreated(new CarGUI(2, anchor.getX(), anchor.getY()));
            PtrToConstPoint srcPtr = std::make_shared<Point>(anchor.getX(), anchor.getY());
            PtrToConstPoint dstPtr = std::make_shared<Point>(point.getX(), point.getY());
            map->createCar(srcPtr, dstPtr, CarGUI::CAR_SPEED);
            anchorValid = false;
        }
        break;
    case Option::setFastCar:
        snapToGridCenter(point);
        snapToGridCenter(point);
        if (!anchorValid) {
            anchor = point;
            anchorValid = true;
        } else {
            //emit drawableCreated(new CarGUI(2, anchor.getX(), anchor.getY()));
            PtrToConstPoint srcPtr = std::make_shared<Point>(anchor.getX(), anchor.getY());
            PtrToConstPoint dstPtr = std::make_shared<Point>(point.getX(), point.getY());
            map->createCar(srcPtr, dstPtr, CarGUI::FAST_CAR_SPEED);
            anchorValid = false;
        }
        break;
    case Option::setBuilding:
        snapToGridCenter(point);
        if (map->createBuilding(Point(point.getX() - GridGUI::SIZE/2, point.getY() + GridGUI::SIZE/2),
                            Point(point.getX() + GridGUI::SIZE/2, point.getY() - GridGUI::SIZE/2)))
            emit drawableCreated(new BuildingGUI(1, point.getX(), point.getY()));
        anchorValid = false;
        break;
    case Option::setHuman:
        snapToGridCenter(point);
        if (!anchorValid) {
            anchor = point;
            anchorValid = true;
        } else {
            //emit drawableCreated(new CarGUI(2, anchor.getX(), anchor.getY()));
            PtrToConstPoint srcPtr = std::make_shared<Point>(anchor.getX(), anchor.getY());
            PtrToConstPoint dstPtr = std::make_shared<Point>(point.getX(), point.getY());
            map->createHuman(srcPtr, dstPtr, PplGUI::SPEED);
            anchorValid = false;
        }
        break;
    case Option::setCamera:
        snapToGridIntersect(point);
        if (!anchorValid) {
            anchor = point;
            anchorValid = true;
        } else {
            map->createCamera(anchor, point, ghostCamera->getSpan()/16);
            emit cameraCreated(new CameraGUI(0, anchor, point, ghostCamera->getSpan()));
            anchorValid = false;
        }
        break;
    case Option::doNothing:
    default:
        anchorValid = false;
        break;
    }
}

void EventInterpreter::steerCamera(int keyCode) {
    if (currentOption != Option::setCamera)
        return;

    switch (keyCode) {
    case Qt::Key_Left:
		ghostCamera->decSpan();
        break;
    case Qt::Key_Right:
		ghostCamera->incSpan();
        break;
    default:
        break;
    }
}


void EventInterpreter::snapToGridCenter(Point &point) const {
    int x = point.getX() / GridGUI::SIZE;
    int y = point.getY() / GridGUI::SIZE;
    point.setX(x * GridGUI::SIZE + GridGUI::SIZE/2);
    point.setY(y * GridGUI::SIZE + GridGUI::SIZE/2);
}

void EventInterpreter::snapToGridIntersect(Point &point) const {
    double x = static_cast<double>(point.getX()) / static_cast<double>(GridGUI::SIZE);
    double y = static_cast<double>(point.getY()) / static_cast<double>(GridGUI::SIZE);
    point.setX(round(x) * GridGUI::SIZE);
    point.setY(round(y) * GridGUI::SIZE);
}

void EventInterpreter::mouseMoved(int x, int y) {
    Point point(x, y);
    switch(currentOption) {
    case Option::setRoad:
        snapToGridCenter(point);
        if (!anchorValid) {
            ghostRoad->setRectangle(point);
        } else {
            ghostRoad->setRectangle(anchor, point);
        }
        break;
    case Option::setFastCar:
    case Option::setCar:
        snapToGridCenter(point);
        ghostObject->setTo(x, y);
        if (!anchorValid) {
            ghostObject->setTo(point.getX(), point.getY());
        } else {
            ghostObject->setTo(anchor.getX(), anchor.getY());
        }
        break;
    case Option::setCamera:
        if (!anchorValid) {
            snapToGridIntersect(point);
            ghostCamera->setRectangle(point);
        } else {
            ghostCamera->setRectangle(anchor, point);
        }
        break;
        break;
    case Option::setBuilding:
        snapToGridCenter(point);
        ghostObject->setTo(point.getX(), point.getY());
        break;
    case Option::setHuman:
        snapToGridCenter(point);
        ghostObject->setTo(x, y);
        if (!anchorValid) {
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

void EventInterpreter::setMap(std::shared_ptr<Map> map) {
    this->map = map;
}

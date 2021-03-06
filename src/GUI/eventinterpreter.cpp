#include "eventinterpreter.h"
#include "mainwindow.h"

/*!
 * \brief EventInterpreter::EventInterpreter.
 * \details Constructor. Initiats object's fields.
 */
EventInterpreter::EventInterpreter() : currentOption(Option::doNothing), anchorValid(false) {

}

/*!
 * \brief EventInterpreter::setCurrentOption.
 * \param option - Option to be set. Its type is EventInterpreter::Option.
 * \return Shared pointer to appropriate ghost object to be drawn.
 * \details Object will set current option unless there isn't valid pointer
 * to map object. If pointer to map is invalid it won't take any effect.
 * Function also sets pointer to appropriate ghost object, so it can be changed
 * due to mouse/keyboard events. It also returns this ghost object as shared pointer
 * casted Drawable object, so MapArea object can draw it.
 */
std::shared_ptr<Drawable> EventInterpreter::setCurrentOption(Option option) {
    if (map == nullptr)
        currentOption = Option::doNothing;
    else
        currentOption = option;

    anchorValid = false;
    switch(option) {
    case Option::setRoad:
        ghostRoad = std::shared_ptr<RoadGUI>(new RoadGUI(Point(-50, -50)));
        return ghostRoad;
        break;
    case Option::setCar:
        ghostObject = std::shared_ptr<Drawable>(new CarGUI(-50, -50, false, true));
        return ghostObject;
        break;
    case Option::setFastCar:
        ghostObject = std::shared_ptr<Drawable>(new CarGUI(-50, -50, true, true));
        return ghostObject;
        break;
    case Option::setBuilding:
        ghostObject = std::shared_ptr<Drawable>(new BuildingGUI(-50, -50, GridGUI::SIZE,
                                                               GridGUI::SIZE, true));
        return ghostObject;
        break;
    case Option::setCamera:
        ghostCamera = std::shared_ptr<CameraGUI>(new CameraGUI(-50, -50, CameraGUI::DEFAULT_SPAN,
                                                              CameraGUI::DEFAULT_ANGLE,
                                                              0, true));
        return ghostCamera;
        break;
    case Option::setHuman:
        ghostObject = std::shared_ptr<Drawable>(new PplGUI(-50, -50, true));
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

/*!
 * \brief EventInterpreter::getCurrentOption.
 * \return Returns current option.
 */
EventInterpreter::Option EventInterpreter::getCurrentOption() {
    return currentOption;
}

/*!
 * \brief EventInterpreter::mouseClicked.
 * \param x - mouse position X.
 * \param y - mouse position Y.
 * \details Interprets mouse click events. It is based on current option and whether
 * anchor point is valid. Unless current tool needs only one point to be created,
 * first click sets anchor field, and second calls function to construct object that
 * takes two points in constructor.
 */
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
                emit roadCreated(new RoadGUI(anchor, point));
            anchorValid = false;
        }
        break;
    case Option::setCar:
        snapToGridCenter(point);
        if (!anchorValid) {
            anchor = point;
            anchorValid = true;
        } else {
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
            emit drawableCreated(new BuildingGUI(point.getX(), point.getY()));
        anchorValid = false;
        break;
    case Option::setHuman:
        snapToGridCenter(point);
        if (!anchorValid) {
            anchor = point;
            anchorValid = true;
        } else {
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
            emit cameraCreated(new CameraGUI(anchor, point, ghostCamera->getSpan()));
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

/*!
 * \brief EventInterpreter::snapToGridCenter.
 * \param point - point to be snapped.
 * \details Function takes reference to point as an argument and modifies
 * it so it will be in the center of the grid piece point is in.
 */
void EventInterpreter::snapToGridCenter(Point &point) const {
    int x = point.getX() / GridGUI::SIZE;
    int y = point.getY() / GridGUI::SIZE;
    point.setX(x * GridGUI::SIZE + GridGUI::SIZE/2);
    point.setY(y * GridGUI::SIZE + GridGUI::SIZE/2);
}

/*!
 * \brief EventInterpreter::snapToGridIntersect.
 * \param point - point to be snapped.
 * \details Function takes reference to point as an argument and modifies
 * it so it will be on the closest intersect of grid lines.
 */
void EventInterpreter::snapToGridIntersect(Point &point) const {
    double x = static_cast<double>(point.getX()) / static_cast<double>(GridGUI::SIZE);
    double y = static_cast<double>(point.getY()) / static_cast<double>(GridGUI::SIZE);
    point.setX(round(x) * GridGUI::SIZE);
    point.setY(round(y) * GridGUI::SIZE);
}

/*!
 * \brief EventInterpreter::mouseMoved.
 * \param x - mouse position X.
 * \param y - mouse position Y.
 * \details Function called when mouse is moved. It takes current mouse position as
 * arguments. Depending on current option and validity of anchor point. It modifies
 * currently shown ghost object, so it will look the same as would object when mouse
 * is clicked now.
 */
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

/*!
 * \brief EventInterpreter::setMap.
 * \param map - shared pointer to map object.
 * \details Function sets object's pointer to map object. Map is used to notify
 * app's model about user input. Without it any input won't change anything, but
 * objects can still be drawn on map area by calling appropriate functions.
 */
void EventInterpreter::setMap(std::shared_ptr<Map> map) {
    this->map = map;
}

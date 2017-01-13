//
// Created by aleksander on 09.01.17.
//

#include "Facilities.h"

Facilities::Facilities() {}

const std::vector<PtrCamera> &Facilities::getCameras() const {
    return cameras;
}

void Facilities::scan(std::vector<PtrMovable> &movables) {
    for (PtrCamera &camera : cameras) {
        for(PtrMovable &movable : movables) {
            Point movablePoint = movable->getActualPoint();
            if (isMovableSeenByCamera(camera, movablePoint) &&
                    !isMovableHiddenByBuilding(camera, movable, movablePoint)) {
                camera->addSeenMovable(movable);
            }
        }
    }
}

bool Facilities::isMovableHiddenByBuilding(PtrCamera &camera, const PtrMovable &movable, const Point &movablePoint) {
    StraightLine straightLine(camera->getStartPoint(), movablePoint);
    for (PtrBuilding &building : buildings) {
        if (building->isCommonPointInsideBuilding(straightLine))
            return true;
    }
    return false;
}

bool Facilities::isMovableSeenByCamera(PtrCamera &camera, const Point &movablePoint) const {
    return camera->isInRange(movablePoint) && camera->isInAngle(movablePoint);
}

PtrBuilding Facilities::addBuilding(const Point &upperLeft, const Point &lowerRight) {
    PtrBuilding building(new Building(upperLeft, lowerRight));
    buildings.push_back(building);
    return building;
}

PtrCamera Facilities::addCamera(const Point &startPoint, const Point &endPoint, double angle, int accuracy) {
    PtrCamera camera(new Camera(startPoint, endPoint, angle, accuracy));
    cameras.push_back(camera);
    return camera;
}

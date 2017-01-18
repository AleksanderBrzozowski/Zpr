//
// Created by aleksander on 09.01.17.
//

#include "Facilities.h"

Facilities::Facilities() {}

const std::vector<PtrCamera> &Facilities::getCameras() const {
    return cameras;
}

void Facilities::scan(const std::vector<PtrConstCar> &cars, const std::vector<PtrConstHuman> &humans) {
    for (PtrCamera &camera : cameras) {
        camera->clearSeenMovables();
        for(const PtrConstCar & car : cars) {
            Point carPoint = car->getActualPoint();
            if (isMovableSeen(carPoint, camera))
                camera->addSeenCar(car);
        }
        for (const PtrConstHuman & human : humans) {
            Point humanPoint = human->getActualPoint();
            if(isMovableSeen(humanPoint, camera))
                camera->addSeenHuman(human);
        }
    }
}

bool Facilities::isMovableSeen(const Point &carPoint, PtrCamera &camera) {
    return isMovableSeenByCamera(camera, carPoint) &&
           !isMovableHiddenByBuilding(camera, carPoint);
}

bool Facilities::isMovableHiddenByBuilding(PtrCamera &camera, const Point &movablePoint) {
    LineSegment straightLine(camera->getStartPoint(), movablePoint);
    for (PtrBuilding &building : buildings) {
        if (building->hasIntersection(straightLine))
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

const std::vector<PtrBuilding> &Facilities::getBuildings() const {
    return buildings;
}

//
// Created by Aleksander on 30.10.2016.
//

#include "Movable.h"

Movable::Movable(Point actualPoint, const int speed, std::vector<Point *> &route)
        : actualPoint(actualPoint), maxSpeed(speed), route(new Route(route)),
          routeVector(this->route->getVector(actualPoint)){
    if(speed < 1)
        throw std::invalid_argument("Car speed must be positive value higher than 0");
    riding = false;
}

Movable::~Movable() {
    delete route;
}

void Movable::nextTurn() {
    setSpeedAndRiding();
    if(riding)
        move();
}

void Movable::move(){
    actualPoint.setX(actualSpeed * routeVector.getX() + actualPoint.getX());
    actualPoint.setY(actualSpeed * routeVector.getY() + actualPoint.getY());
}

void Movable::setSpeedAndRiding() {
    if (!route->isEnd()) {
        int distance = route->getDistance(actualPoint);
        if (distance == 0) {
            route->nextPoint();
            if (route->isEnd()) {
                actualSpeed = 0;
                riding = false;
            } else {
                routeVector = route->getVector(actualPoint);
                setSpeedAndRiding();
            }
        } else {
            riding = true;
            actualSpeed = distance < maxSpeed ? distance : maxSpeed;
        }
    }
}

const Point &Movable::getActualPoint() const {
    return actualPoint;
}

bool Movable::isRiding() const {
    return riding;
}



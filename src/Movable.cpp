//
// Created by Aleksander on 30.10.2016.
//

#include "Movable.h"

Movable::Movable(Point actualPoint, const int speed, std::vector<Point *> &route)
        : actualPoint(actualPoint), maxSpeed(speed), route(new Route(route)),
          routeVector(this->route->getVector(actualPoint)){
    if(speed < 1)
        throw std::invalid_argument("Car speed must be positive value higher than 0");
}

Movable::~Movable() {
    delete route;
}

const Point &Movable::getActualPoint() const {
    return actualPoint;
}

bool Movable::move() {
    if(route->isEnd())
        return false;
    else{
        int distance = route->getDistance(actualPoint);
        if(distance == 0){
            route->nextPoint();
            if(route->isEnd())
                return false;
            else{
                routeVector = route->getVector(actualPoint);
                distance = route->getDistance(actualPoint);
            }
        }
        int distanceToGo = distance > maxSpeed ? maxSpeed : distance;
        actualPoint.setX(distanceToGo * routeVector.getX() + actualPoint.getX());
        actualPoint.setY(distanceToGo * routeVector.getY() + actualPoint.getY());
        return true;
    }
}



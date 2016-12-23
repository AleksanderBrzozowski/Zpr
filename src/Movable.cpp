//
// Created by Aleksander on 12.12.2016.
//

#include "Movable.h"

Movable::Movable(Route &route, Point actualPoint, const int speed)
        : route(route), actualPoint(actualPoint), speed(speed){}

bool Movable::move() {
    if(route.isEnd())
        return false;
    else{
        int distance = route.getDistance(actualPoint);
        if(distance == 0){
            route.nextPoint(); // switch to next point
            if(route.isEnd())
                return false;
            else{
                routeVector = route.getRouteVector(actualPoint);
                distance = route.getDistance(actualPoint); //calculate new distance
            }
        }
        // calculate distance to go
        int distanceToGo = distance > speed ? speed : distance;
        actualPoint = Point(
                distanceToGo * routeVector.getX() + actualPoint.getX(),
                distanceToGo * routeVector.getY() + actualPoint.getY()
        );
        return true;
    }
}

Point Movable::getActualPoint() const {
    return actualPoint;
}

Car::Car(CarRoute &route, const Point &actualPoint, const int speed) : Movable(route, actualPoint, speed) {}

Human::Human(HumanRoute &route, const Point &actualPoint, const int speed) : Movable(route, actualPoint, speed) {}

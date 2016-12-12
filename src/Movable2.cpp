//
// Created by Aleksander on 12.12.2016.
//

#include "Movable2.h"

Movable2::Movable2(Route2 &route, Point actualPoint, const int speed)
        : route(route), actualPoint(actualPoint), speed(speed),
          routeVector(route.getRouteVector(actualPoint)) {}

bool Movable2::move() {
    if(route.isLastPoint(actualPoint))
        return false;
    else{
        int distance = route.getDistance(actualPoint);
        if(distance == 0){
            route.nextPoint(); // switch to next point
            if(route.isLastPoint(actualPoint))
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

bool Movable2::isEnd() const {
    return route.isLastPoint(actualPoint);
}

const Point &Movable2::getActualPoint() const {
    return actualPoint;
}

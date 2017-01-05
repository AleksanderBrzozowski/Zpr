//
// Created by Aleksander on 12.12.2016.
//

#include "Movable.h"

Movable::Movable(Route *route, const Point &actualPoint, const int speed, const unsigned int id)
        : route(std::move(route)), actualPoint(actualPoint), speed(speed), id(id) {}

bool Movable::move() {
    if(route->isEnd())
        return false;
    else{
        int distance = route->getDistance(actualPoint);
        if(distance == 0){
            route->nextPoint(); // switch to next point
            if(route->isEnd())
                return false;
            else{
                routeVector = route->getRouteVector(actualPoint);
                distance = route->getDistance(actualPoint); //calculate new distance
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

unsigned int Movable::getId() const {
    return id;
}

Car::Car(CarRoute *route, const Point &actualPoint, const int speed, const unsigned int id) :
        Movable(route, actualPoint, speed, id) {}

Human::Human(HumanRoute *route, const Point &actualPoint, const int speed, const unsigned int id) :
        Movable(route, actualPoint, speed, id) {}

PtrHuman createHuman(const Point &startPoint, const std::vector<PtrToConstPoint> &points, const int speed,
                   const unsigned int id) {
    return std::make_shared<Human>(new HumanRoute(points), startPoint, speed, id);
}

PtrCar createCar(const Point &startPoint, const std::vector<PtrToConstPoint> &points, const int speed,
               const unsigned int id) {
    return std::make_shared<Car>(new CarRoute(points), startPoint, speed, id);
}

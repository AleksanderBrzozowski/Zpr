//
// Created by Aleksander on 12.12.2016.
//

#ifndef ZPR_MOVABLE2_H
#define ZPR_MOVABLE2_H


#include "Route.h"
#include "CarRoute.h"
#include "HumanRoute.h"

class Movable {
public:
    Movable(Route &route, Point actualPoint, const int speed);

    bool move();
    Point getActualPoint() const;
private:
    Route& route;
    Point actualPoint;
    const int speed;
    RouteVector routeVector;
};


class Car : public Movable{
public:
    Car(CarRoute &route, const Point &actualPoint, const int speed);
};

class Human : public Movable{
public:
    Human(HumanRoute &route, const Point &actualPoint, const int speed);
};

#endif //ZPR_MOVABLE2_H

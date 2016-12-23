//
// Created by Aleksander on 12.12.2016.
//

#ifndef ZPR_MOVABLE2_H
#define ZPR_MOVABLE2_H


#include "Route2.h"
#include "CarRoute.h"
#include "HumanRoute.h"

class Movable2 {
public:
    Movable2(Route2 &route, Point actualPoint, const int speed);

    bool move();
    Point getActualPoint() const;
private:
    Route2& route;
    Point actualPoint;
    const int speed;
    RouteVector routeVector;
};


class Car : public Movable2{
public:
    Car(CarRoute &route, const Point &actualPoint, const int speed);
};

class Human : public Movable2{
public:
    Human(HumanRoute &route, const Point &actualPoint, const int speed);
};

#endif //ZPR_MOVABLE2_H

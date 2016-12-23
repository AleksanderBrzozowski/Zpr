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
    Movable(Route &route, const Point &actualPoint, const int speed, unsigned int id);

    bool move();
    Point getActualPoint() const;
    unsigned int getId() const;
private:
    Route& route;
    Point actualPoint;
    const int speed;
    RouteVector routeVector;
    unsigned int id;
};


class Car : public Movable{
public:
    Car(Route &route, const Point &actualPoint, const int speed, unsigned int id);
};

class Human : public Movable{
public:
    Human(Route &route, const Point &actualPoint, const int speed, unsigned int id);
};

#endif //ZPR_MOVABLE2_H

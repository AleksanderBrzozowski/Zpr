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
    Movable(Route *route, const Point &actualPoint, const int speed, const unsigned int id);

    bool move();
    Point getActualPoint() const;
    unsigned int getId() const;
private:
    std::unique_ptr<Route> route;
    Point actualPoint;
    const int speed;
    RouteVector routeVector;
    const unsigned int id;
};

class Car : public Movable{
public:
    Car(CarRoute *route, const Point &actualPoint, const int speed, const unsigned int id);

};

class Human : public Movable{
public:
    Human(HumanRoute *route, const Point &actualPoint, const int speed, const unsigned int id);

};

PtrHuman createHuman(const Point &startPoint, const std::vector<PtrToConstPoint> &points, const int speed,
                   const unsigned int id);

PtrCar createCar(const Point &startPoint, const std::vector<PtrToConstPoint> &points, const int speed,
               const unsigned int id);

#endif //ZPR_MOVABLE2_H

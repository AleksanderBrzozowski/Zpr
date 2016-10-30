//
// Created by Aleksander on 30.10.2016.
//

#ifndef ZPR_MOVABLE_H
#define ZPR_MOVABLE_H


#include "Point.h"
#include "Route.h"

class Movable {
private:
    Point actualPoint;
    const int maxSpeed;
    Route* route;

    RouteVector routeVector;
    int actualSpeed;
    bool riding;

    void setSpeedAndRiding();
    void move();
public:
    Movable(Point actualPoint, const int speed, std::vector<Point *> &route);
    virtual ~Movable();
    void nextTurn();

    const Point &getActualPoint() const;
    bool isRiding() const;
};


#endif //ZPR_MOVABLE_H

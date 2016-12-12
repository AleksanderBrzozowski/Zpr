//
// Created by Aleksander on 12.12.2016.
//

#ifndef ZPR_MOVABLE2_H
#define ZPR_MOVABLE2_H


#include "Route2.h"

class Movable2 {
public:
    Movable2(Route2 &route, Point actualPoint, const int speed);

    bool move();
    bool isEnd() const;

    const Point &getActualPoint() const;
private:
    Route2& route;
    Point& actualPoint;
    const int speed;
    RouteVector routeVector;
};


#endif //ZPR_MOVABLE2_H

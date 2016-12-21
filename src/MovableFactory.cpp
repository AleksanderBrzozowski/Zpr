//
// Created by Aleksander on 12.12.2016.
//

#include <deque>
#include <stack>
#include "MovableFactory.h"
#include "HumanRoute.h"
#include "CarRoute.h"

Movable2 *MovableFactory::createCar(const int speed, std::vector<std::shared_ptr<Point const>> &points) {
    CarRoute carRoute1(points);
    return new Movable2(carRoute1, *points[0], speed);
}

Movable2 *MovableFactory::createHuman(const int speed, std::vector<std::shared_ptr<Point const>> &points) {
    HumanRoute humanRoute(points);
    return new Movable2(humanRoute, *points[0], speed);
}

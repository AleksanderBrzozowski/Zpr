//
// Created by Aleksander on 12.12.2016.
//

#include <deque>
#include <stack>
#include "MovableFactory.h"
#include "HumanRoute.h"
#include "CarRoute.h"

Movable2 *MovableFactory::createCar(const Point &startPoint, const int speed,
                                     std::vector<std::shared_ptr<Point const>> &points) {
    const std::stack<std::shared_ptr<Point const>> pointsStack = std::stack<std::shared_ptr<Point const>>
                    (std::deque<std::shared_ptr<const Point>>(points.begin(), points.end()));
    CarRoute carRoute1(pointsStack);
    return new Movable2(carRoute1, startPoint, speed);
}

Movable2 *MovableFactory::createHuman(const Point &startPoint, const int speed,
                                       std::vector<std::shared_ptr<Point const>> &points) {
    HumanRoute humanRoute(points);
    return new Movable2(humanRoute, startPoint, speed);
}

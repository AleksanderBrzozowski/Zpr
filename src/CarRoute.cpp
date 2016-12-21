//
// Created by Aleksander on 12.12.2016.
//

#include "CarRoute.h"

CarRoute::CarRoute(const std::stack<std::shared_ptr<const Point>> &points) : points(points) {
    if(points.empty())
        throw std::runtime_error("points cannot be empty!");
}

CarRoute::~CarRoute() {}

bool CarRoute::nextPoint() {
    if(points.size() < 1)
        return false;
    else{
        points.pop();
        return true;
    }
}

const Point &CarRoute::getActualPoint() const {
    return *points.top();
}

bool CarRoute::isEnd() {
    return points.empty();
}

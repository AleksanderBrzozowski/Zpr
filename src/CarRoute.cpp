//
// Created by Aleksander on 12.12.2016.
//

#include "CarRoute.h"

CarRoute::CarRoute(const std::vector<PtrToConstPoint> &points) {
    this->points = std::stack<PtrToConstPoint>
            (std::deque<PtrToConstPoint>(points.crbegin(), points.crend()));
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

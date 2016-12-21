//
// Created by Aleksander on 12.12.2016.
//

#include "HumanRoute.h"

HumanRoute::HumanRoute(const std::vector<std::shared_ptr<Point const>> &points)
        : points(points), pointsIterator(points.begin()) {
    if(points.empty())
        throw std::runtime_error("points cannot be empty!");
}

HumanRoute::~HumanRoute() {}

bool HumanRoute::nextPoint() {
    static bool forward = true;
    if (forward) {
        if(pointsIterator != (points.end() - 1))
            ++pointsIterator;
        else{
            forward = false;
            --pointsIterator;
        }
    } else {
        if(pointsIterator != points.begin())
            --pointsIterator;
        else
            forward = true;
    }
    return true;
}

const Point &HumanRoute::getActualPoint() const {
    return *(*pointsIterator).get();
}

bool HumanRoute::isEnd() {
    return false;
}



//
// Created by Aleksander on 12.12.2016.
//

#include "HumanRoute.h"

HumanRoute::HumanRoute(const std::vector<PtrToConstPoint> &points)
        : points(points), pointsIterator(points.begin()) {
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
        else{
            forward = true;
            ++pointsIterator;
        }
    }
    return true;
}

const Point &HumanRoute::getActualPoint() const {
    return *(*pointsIterator).get();
}

bool HumanRoute::isEnd() {
    return false;
}



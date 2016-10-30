//
// Created by Aleksander on 29.10.2016.
//


#include "Route.h"

Route::Route(std::vector<Point*> &points) : points(points) {
    for (int i = 1; i < points.size(); i++)
        RouteVector(*points[i - 1], *points[i]);
    this->points = points;
}

RouteVector Route::getVector(const Point &point) const {
    checkIsAnyPointToGo();
    return RouteVector(point, *points[0]);
}

int Route::getDistance(const Point &point) const {
    checkIsAnyPointToGo();
    return abs(
            point.getY() == points[0]->getY() ?
            point.getX() - points[0]->getX() :
            point.getY() - points[0]->getY()
    );
}

bool Route::isEnd() const {
    return points.empty();
}

void Route::nextPoint() {
    checkIsAnyPointToGo();
    points.erase(points.begin());
}

void Route::checkIsAnyPointToGo() const {
    if(points.empty())
        throw std::runtime_error("No more points to go!");
}






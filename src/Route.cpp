//
// Created by Aleksander on 12.12.2016.
//

#include <cstdlib>
#include "Route.h"

Route::~Route() {}

RouteVector Route::getRouteVector(const Point &point) const {
    return RouteVector(point, getActualPoint());
}

int Route::getDistance(const Point &point) const {
    Point actualPoint = getActualPoint();
    return abs(
            actualPoint.getX() == point.getX() ?
            actualPoint.getY() - point.getY() :
            actualPoint.getX() - point.getX()
    );
    ;
}

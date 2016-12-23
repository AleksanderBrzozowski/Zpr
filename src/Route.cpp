//
// Created by Aleksander on 12.12.2016.
//

#include "Route.h"

RouteVector Route::getRouteVector(const Point &point) const {
    return RouteVector(point, getActualPoint());
}

int Route::getDistance(const Point &point) const {
    return getActualPoint().absDistance(point);
}

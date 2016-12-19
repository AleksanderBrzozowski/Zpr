//
// Created by Aleksander on 12.12.2016.
//

#include "Route2.h"

RouteVector Route2::getRouteVector(const Point &point) const {
    return RouteVector(getActualPoint(), point);
}

int Route2::getDistance(const Point &point) const {
    return getActualPoint().absDistance(point);
}

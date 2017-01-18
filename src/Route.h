//
// Created by Aleksander on 12.12.2016.
//

#ifndef ZPR_ROUTE2_H
#define ZPR_ROUTE2_H


#include "RouteVector.h"
#include "Point.h"

/*!
 * This class represents route(GPS).
 * @author Aleksander Brzozowski
 */
class Route {
public:
    virtual ~Route();
    /*!
     * Computes vector between actual point of Route and passed point.
     * @param point Point to which vector will be computed
     * @return      Vector to fallow
     */
    RouteVector getRouteVector(const Point& point) const;
    /*!
     * Computes distance between point and actual point of Route.
     * @param point Point to which distance will be computed
     * @return      Distance between point and actual point of Route
     */
    int getDistance(const Point& point) const;
    /*!
     * Switches to the next point of route.
     * @return Is next point of route
     */
    virtual bool nextPoint() = 0;
    /*!
     * Checks is it end of Route.
     * @return is end of Route
     */
    virtual bool isEnd() = 0;
private:
    virtual const Point &getActualPoint() const = 0;
};


#endif //ZPR_ROUTE2_H

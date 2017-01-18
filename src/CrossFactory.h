/**
 * @file CrossFactory.h
 * @Author PiotrKuc (piotr.kuc29@gmail.com)
 * @date December, 2017
 * @brief CrossFactory class methods declaration
 *
 */
#ifndef ZPR_CROSSFACTORY_H
#define ZPR_CROSSFACTORY_H


#include "Point.h"
#include "Cross.h"
#include "Types.h"
#include <algorithm>

/**
 * @class CrossFactory class
 * @brief Factory creating crosses from given roads.
 * @details Factory is able to create new crosses and update
 * their neighbours. If new road crosses the road that already exists
 * new crosses at the crosses are created and neighbours are updated.
 */

class CrossFactory {

private:
    std::vector<PtrCross>crosses;

public:
    ///Find the cross that has the same position as the given as the argument
    PtrCross findCrossByPoint(const PtrToConstPoint&) const;

    ///Creating new cross if it doesn't exist
    PtrCross createNewCross(const PtrToConstPoint&);

    ///Updating crosses, creating new crosses from the given road
    void createRoad(const PtrToConstPoint&, const PtrToConstPoint&);

    ///Updates crosses if new road crosses the existed one verticaly
    void vertCrossedRoad(const PtrToConstPoint&, const PtrToConstPoint&);

    ///Updates crosses if new road crosses the existed one horizontaly
    void horizCrossedRoad(const PtrToConstPoint&, const PtrToConstPoint&);

    ///X value of cross position comparator for sorting
    static bool cmpCrossX(const PtrCross&, const PtrCross& );

    ///Y value of cross position comparator for sorting
    static bool cmpCrossY(const PtrCross&, const PtrCross& );

    ///Updates crosses if new road hide the existing, both roads are horizontaly
    void twoHorizRoads(const PtrToConstPoint&, const PtrToConstPoint&);

    ///Updates crosses if new road hide the existing, both roads are verticaly
    void twoVertRoads(const PtrToConstPoint&, const PtrToConstPoint&);
    
    std::vector<PtrCross>& getCrosses();

};


#endif //ZPR_CROSSFACTORY_H

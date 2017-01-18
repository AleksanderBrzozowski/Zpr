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
 * their neighbours. If new road crosses the road that already exists,
 * new crosses at the crosses are created and neighbours are updated.
 */

class CrossFactory {

private:
    std::vector<PtrCross>crosses;

public:

    PtrCross findCrossByPoint(const PtrToConstPoint&) const;

    PtrCross createNewCross(const PtrToConstPoint&);

    void createRoad(const PtrToConstPoint&, const PtrToConstPoint&);

    void vertCrossedRoad(const PtrToConstPoint&, const PtrToConstPoint&);

    void horizCrossedRoad(const PtrToConstPoint&, const PtrToConstPoint&);

    static bool cmpCrossX(const PtrCross&, const PtrCross& );

    static bool cmpCrossY(const PtrCross&, const PtrCross& );

    void twoHorizRoads(const PtrToConstPoint&, const PtrToConstPoint&);

    void twoVertRoads(const PtrToConstPoint&, const PtrToConstPoint&);
    
    std::vector<PtrCross>& getCrosses();

};


#endif //ZPR_CROSSFACTORY_H

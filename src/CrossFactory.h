//
// Created by kuco on 13.12.16.
//

#ifndef ZPR_CROSSFACTORY_H
#define ZPR_CROSSFACTORY_H


#include "Point.h"
#include "Cross.h"
#include "Types.h"
#include <algorithm>

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

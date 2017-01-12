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
    std::vector<PtrCross>&crosses;

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
    CrossFactory(std::vector<PtrCross>&);


    /*
private:
    static std::vector<PtrCross>::size_type findCrossIndex(PtrToConstPoint, const std::vector<PtrCross>&);
    static void insertVerticalyRoad(PtrToConstPoint, PtrToConstPoint, PtrCross, PtrCross, std::vector<PtrCross>&);
    static void findCrossedRoads(PtrToConstPoint, PtrToConstPoint, std::vector<PtrCross>&);
    static void createCrossesFromSingleRoad( PtrToConstPoint, PtrToConstPoint, std::vector<PtrCross>&);
    static void updateNeighbours(PtrCross, PtrCross, PtrCross);
    static PtrCross createCross(PtrToConstPoint, std::vector<PtrCross>&);
public:
    static void createRoute(PtrToConstPoint, PtrToConstPoint, std::vector<PtrCross>&);
*/
};


#endif //ZPR_CROSSFACTORY_H

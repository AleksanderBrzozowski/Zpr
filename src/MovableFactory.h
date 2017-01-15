//
// Created by kuco on 12.01.17.
//

#ifndef ZPR_MOVABLEFACTORY_H
#define ZPR_MOVABLEFACTORY_H


#include "Types.h"
#include <list>
#include <vector>
#include "Movable.h"
#include "Cross.h"

class MovableFactory {

private:
    std::list<PtrMovable>movables;
public:

    void findRoute(PtrToConstPoint, PtrToConstPoint, std::vector<PtrToConstPoint>&, std::vector<PtrCross>&);
    void prepareRouteFinding(std::vector<PtrCross>&);
    bool pointMeetsCross(PtrToConstPoint, PtrCross, const std::vector<PtrCross>&) const;
    PtrCross findNearestCross(PtrToConstPoint, const std::vector<PtrCross>&)const;

    unsigned int getMovableId();

    bool createCar(PtrToConstPoint, PtrToConstPoint, int, std::vector<PtrCross>&);

    std::list<PtrMovable>& getMovables();
};


#endif //ZPR_MOVABLEFACTORY_H

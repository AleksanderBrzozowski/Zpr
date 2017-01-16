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
#include "GUI/pplgui.h"

class MovableFactory {

private:
    std::list<PtrHuman>humans;
    std::list<PtrCar> cars;
public:

    void findRoute(PtrToConstPoint, PtrToConstPoint, std::vector<PtrToConstPoint>&, std::vector<PtrCross>&);
    void prepareRouteFinding(std::vector<PtrCross>&);
    bool pointMeetsCross(PtrToConstPoint, PtrCross, const std::vector<PtrCross>&) const;
    PtrCross findNearestCross(PtrToConstPoint, const std::vector<PtrCross>&)const;

    unsigned int getMovableId();

    bool createCar(PtrToConstPoint, PtrToConstPoint, int, std::vector<PtrCross>&);
    bool createHuman(PtrToConstPoint, PtrToConstPoint, int, std::vector<PtrCross>&);
    void moveHumansOnSidewalks(std::vector<PtrToConstPoint>&);

    std::list<PtrCar>& getCars();
    std::list<PtrHuman>& getHumans();
};


#endif //ZPR_MOVABLEFACTORY_H

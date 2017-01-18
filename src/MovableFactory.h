/**
 * @file MovableFactory.h
 * @Author PiotrKuc (piotr.kuc29@gmail.com)
 * @date January, 2017
 * @brief MovableFactory class declaration
 */

#ifndef ZPR_MOVABLEFACTORY_H
#define ZPR_MOVABLEFACTORY_H


#include "Types.h"
#include <list>
#include <vector>
#include "Movable.h"
#include "Cross.h"
#include "GUI/pplgui.h"

/**
 * @class MovableFactory
 * @brief Factory of movables (cars and humans) with algorithms to finding routes.
 * @details The factory prepares proper routes between given points for cars and humans.
 * Cars have to run on streets.
 * Humans have to walk on sidewalks.
 */

class MovableFactory {

private:
    std::list<PtrHuman>humans;      ///<list of humans
    std::list<PtrCar> cars;         ///<list of cars
public:

    void findRoute(PtrToConstPoint, PtrToConstPoint, std::vector<PtrToConstPoint>&, std::vector<PtrCross>&);
    void prepareRouteFinding(std::vector<PtrCross>&);
    bool pointMeetsCross(PtrToConstPoint, PtrCross) const;

    PtrCross findNearestCross(PtrToConstPoint, const std::vector<PtrCross>&)const;


    unsigned int getMovableId();


    bool createCar(PtrToConstPoint, PtrToConstPoint, int, std::vector<PtrCross>&);
    bool createHuman(PtrToConstPoint, PtrToConstPoint, int, std::vector<PtrCross>&);

    void moveHumansOnSidewalks(std::vector<PtrToConstPoint>&);

    std::list<PtrCar>& getCars();
    std::list<PtrHuman>& getHumans();
};


#endif //ZPR_MOVABLEFACTORY_H

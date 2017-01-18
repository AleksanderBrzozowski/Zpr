/**
 * @file Map.h
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

    ///Finds route betweend two points on the map.
    void findRoute(PtrToConstPoint, PtrToConstPoint, std::vector<PtrToConstPoint>&, std::vector<PtrCross>&);

    ///Prepare crosses for running finding route algorithm.
    void prepareRouteFinding(std::vector<PtrCross>&);

    ///Checking if given point directly "sees" the given cross.
    bool pointMeetsCross(PtrToConstPoint, PtrCross) const;

    ///Looking for a cross that directly "sees" the given point.
    PtrCross findNearestCross(PtrToConstPoint, const std::vector<PtrCross>&)const;


    ///Get unique id for new movable.
    unsigned int getMovableId();

    ///Creating new car running from point to point at set speed.
    bool createCar(PtrToConstPoint, PtrToConstPoint, int, std::vector<PtrCross>&);

    ///Creating new human running from point to point at set speed.
    bool createHuman(PtrToConstPoint, PtrToConstPoint, int, std::vector<PtrCross>&);

    ///Transforming found route for humans to be set on sidewalks.
    void moveHumansOnSidewalks(std::vector<PtrToConstPoint>&);

    std::list<PtrCar>& getCars();
    std::list<PtrHuman>& getHumans();
};


#endif //ZPR_MOVABLEFACTORY_H

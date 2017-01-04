//
// Created by kuco on 08.12.16.
//

#ifndef ZPR_TRAFFICCONTROL_H
#define ZPR_TRAFFICCONTROL_H


#include "Movable.h"
#include "Cross.h"
#include <algorithm>
#include <stack>
#include <list>
#include "Point.h"
#include "CrossFactory.h"
#include "Types.h"
#include <thread>
#include <chrono>



class TrafficControl {

private:

    std::vector<PtrCross> crosses;
    std::list<PtrCar> cars;
    std::list<PtrHuman> humans;

    bool movableAllowedToMove;


public:

    void run();

    std::vector<PtrCross>::size_type findCrossByPoint(PtrToConstPoint);
    void prepareFinding();
    void findRoute(PtrToConstPoint, PtrToConstPoint, std::vector<PtrToConstPoint>&);

    unsigned int getNextCarId();
    unsigned int getNextHumanId();

    bool createNewCar(PtrToConstPoint, PtrToConstPoint, const int&);
    void createRoute(PtrToConstPoint, PtrToConstPoint);

    void setMovableAllowedToMove(const bool&);

    TrafficControl();
    ~TrafficControl();


};


#endif //ZPR_TRAFFICCONTROL_H

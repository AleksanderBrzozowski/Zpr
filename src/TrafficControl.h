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

class TrafficControl {

private:

    std::vector<PtrCross> crosses;
    std::list<PtrMovable> movables;

public:

    std::vector<PtrCross>::size_type findCrossByPoint(PtrToConstPoint);
    void prepareFinding();
    void findRoute(PtrToConstPoint, PtrToConstPoint, std::vector<PtrToConstPoint>&);



    bool createNewMovable(PtrToConstPoint, PtrToConstPoint, const int&);
    void createRoute(PtrToConstPoint, PtrToConstPoint);

    TrafficControl();

    ~TrafficControl();


};


#endif //ZPR_TRAFFICCONTROL_H

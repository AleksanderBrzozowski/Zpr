//
// Created by kuco on 08.12.16.
//

#ifndef ZPR_TRAFFICCONTROL_H
#define ZPR_TRAFFICCONTROL_H


#include "Movable.h"
#include "Cross.h"
#include <algorithm>
#include <stack>
#include "Point.h"

class TrafficControl {

private:
    std::vector<Cross*> crosses;
    std::vector<Movable*> movables;


public:
    void createNewMovable(const unsigned int&, const unsigned int&, const int&);

    void prepareFinding();
    void findRoute(const unsigned int&, const unsigned int& , std::vector<Point*>&);

    TrafficControl();

    ~TrafficControl();


};


#endif //ZPR_TRAFFICCONTROL_H

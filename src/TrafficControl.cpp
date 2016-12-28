//
// Created by kuco on 08.12.16.
//

#include "TrafficControl.h"


TrafficControl::TrafficControl() {}

TrafficControl::~TrafficControl() {}

bool TrafficControl::createNewMovable(PtrToConstPoint src, PtrToConstPoint dst, const int& speed){
    std::vector<PtrToConstPoint>route;

    findRoute(src, dst, route);
    std::vector<PtrToConstPoint>::size_type src_index = findCrossByPoint(src);

    if(src_index>=crosses.size() || route.empty() || speed<=0)
        return false;
    //Movable* tempMovable = new Movable(*(crosses[src_index]->getPosition()), speed, route, 0);
   // movables.push_back(tempMovable);

    return true;
}

void TrafficControl::createRoute(PtrToConstPoint src, PtrToConstPoint dst) {
    CrossFactory::createRoute(src, dst, crosses);
}

std::vector<PtrCross>::size_type TrafficControl::findCrossByPoint(PtrToConstPoint point) {

    for(std::vector<PtrCross>::size_type i =0; i<crosses.size(); ++i)
        if(*(crosses[i]->getPosition()) == *(point))
            return i;
    return crosses.size();
}


void TrafficControl::findRoute(PtrToConstPoint src, PtrToConstPoint dst, std::vector<PtrToConstPoint>&readyRoute) {

    std::stack<PtrCross>foundRoute;
    prepareFinding();   //setting crosses as not visited

    std::vector<PtrToConstPoint>::size_type src_index=findCrossByPoint(src);
    if(!src_index)
        return;
    crosses[src_index]->setVisited(true);
    foundRoute.push(crosses[src_index]);

    PtrToConstPoint currentPoint = foundRoute.top()->getPosition();

    while(*currentPoint != *dst){

        PtrCross currentCross = foundRoute.top()->getNotVisitedNeighbours();
        if(!currentCross){
            if(!foundRoute.empty())
                foundRoute.pop();
        }

        else{
            foundRoute.push(currentCross);
            currentCross->setVisited(true);
        }
        if(foundRoute.empty()) break;
        currentPoint = foundRoute.top()->getPosition();
    }

    while(!foundRoute.empty()){
        readyRoute.push_back(foundRoute.top()->getPosition());
        foundRoute.pop();
    }

    std::reverse(readyRoute.begin(), readyRoute.end());
}

void TrafficControl::prepareFinding() {
    for (std::vector<PtrCross>::size_type i=0; i<crosses.size(); ++i){
        crosses[i]->setVisited(false);
    }
}
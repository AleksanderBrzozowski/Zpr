//
// Created by kuco on 08.12.16.
//

#include "TrafficControl.h"


TrafficControl::TrafficControl() {}

TrafficControl::~TrafficControl() {
    for(int i =0; i< (int)movables.size();++i)delete movables[i];
    for(int i =0; i< (int)crosses.size();++i)delete crosses[i];
}

void TrafficControl::createNewMovable(const unsigned int& src, const unsigned int& dst, const int& speed){
    std::vector<Point*>route;
    findRoute(src, dst, route);
    Movable* tempMovable = new Movable( *(crosses[src]->getPosition()) ,  speed,   route);
    movables.push_back(tempMovable);
}

void TrafficControl::findRoute(const unsigned int & src, const unsigned int & dst, std::vector<Point*>&readyRoute) {

    std::stack<std::pair<Cross*, Point*>*>foundRoute;
    prepareFinding();   //setting crosses not visited

    foundRoute.push(crosses[src]->getNotVisitedNeighbours());
    while(foundRoute.top()->first->getId() != crosses[dst]->getId()){

        if(!foundRoute.top()->first->getNotVisitedNeighbours())foundRoute.pop();
        else{
            foundRoute.push(foundRoute.top()->first->getNotVisitedNeighbours());
            foundRoute.top()->first->setVisited(true);
        }
        if(foundRoute.empty()) break;
    }

    while(!foundRoute.empty()){
        readyRoute.push_back(foundRoute.top()->second);
        foundRoute.pop();
    }
    std::reverse(readyRoute.begin(), readyRoute.end());
}

void TrafficControl::prepareFinding() {
    for(int i =0; i<(int)crosses.size();++i){
        crosses[i]->setVisited(false);
    }
}
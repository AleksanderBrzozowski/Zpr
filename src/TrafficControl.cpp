//
// Created by kuco on 08.12.16.
//

#include "TrafficControl.h"


TrafficControl::TrafficControl() {}

TrafficControl::~TrafficControl() {
    for(std::list<Movable*>::iterator iter; iter!=movables.end();++iter)
        delete *iter;
    for(int i =0; i< (int)crosses.size();++i)
        delete crosses[i];
}

bool TrafficControl::createNewMovable(Point* src, Point* dst, const int& speed){
    std::vector<Point*>route;

    findRoute(src, dst, route);
    Movable* tempMovable = new Movable( *src ,  speed,   route);
    movables.push_back(tempMovable);
    return true;
}

void TrafficControl::createRoute(Point * src, Point * dst) {
    CrossFactory::createRoute(src, dst, crosses);
}

int TrafficControl::findCrossByPoint(Point* point) {

    for(int i =0;i<(int)crosses.size();++i)
        if(crosses[i]->getPosition() == point)
            return i;
    return -1;
}


void TrafficControl::findRoute(Point* src, Point* dst, std::vector<Point*>&readyRoute) {

    std::stack<Cross*>foundRoute;
    prepareFinding();   //setting crosses as not visited

    int src_index=findCrossByPoint(src);
    if(src_index<0)
        return;
    foundRoute.push(crosses[src_index]->getNotVisitedNeighbours());

    while(foundRoute.top()->getPosition() != dst){

        if(!foundRoute.top()->getNotVisitedNeighbours())
            foundRoute.pop();
        else{
            foundRoute.push(foundRoute.top()->getNotVisitedNeighbours());
            foundRoute.top()->setVisited(true);
        }
        if(foundRoute.empty()) break;
    }

    while(!foundRoute.empty()){
        readyRoute.push_back(foundRoute.top()->getPosition());
        foundRoute.pop();
    }

    std::reverse(readyRoute.begin(), readyRoute.end());
}

void TrafficControl::prepareFinding() {
    for(int i =0; i<(int)crosses.size();++i){
        crosses[i]->setVisited(false);
    }
}
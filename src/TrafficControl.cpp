//
// Created by kuco on 08.12.16.
//

#include "TrafficControl.h"
#include <GUI/mainwindow.h>


TrafficControl::TrafficControl() : movableAllowedToMove(false) {
    crossFactory = new CrossFactory(crosses);
}


TrafficControl::~TrafficControl() {
    delete crossFactory;
}

void TrafficControl::setMovableAllowedToMove(const bool& decision){
    if(movableAllowedToMove==decision)return;
    movableAllowedToMove = decision;
    if(decision)
        runningSimulation = std::thread(&TrafficControl::run, this);
    else{
        runningSimulation.join();
    }

}

unsigned int TrafficControl::getNextCarId() {
    static unsigned int id=0;
    return id++;
}

unsigned int TrafficControl::getNextHumanId() {
    static unsigned int id=0;
    return id++;
}


void TrafficControl::run() {

    while(movableAllowedToMove){
        for(std::list<PtrCar>::iterator iter = cars.begin(); iter!=cars.end(); ++iter){
            if(!(*iter)->move()){
                iter = cars.erase(iter);
                --iter;
            }
            MainWindow::getInstance().setCar((*iter)->getId(),  (*iter)->getActualPoint().getX(), (*iter)->getActualPoint().getY());
        }

        std::this_thread::sleep_for (std::chrono::milliseconds(50));
    }
}

bool TrafficControl::createNewCar(PtrToConstPoint src, PtrToConstPoint dst, const int& speed){
    std::vector<PtrToConstPoint>route;

    findRoute(src, dst, route);
    std::vector<PtrToConstPoint>::size_type src_index = findCrossByPoint(src);

    if(src_index>=crosses.size() || route.empty() || speed<=0)
        return false;

    cars.push_back( createCar(*(crosses[src_index]->getPosition()), route, speed, getNextCarId()) );

    return true;
}



void TrafficControl::createRoute(PtrToConstPoint src, PtrToConstPoint dst) {
    crossFactory->createRoad(src, dst);
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
    if(src_index>=crosses.size() || crosses.empty())
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

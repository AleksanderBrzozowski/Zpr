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

        std::list<PtrCar>::iterator iter = cars.begin();
        while(iter!=cars.end()){
            if(!(*iter)->move())
                iter = cars.erase(iter);
            else {
                MainWindow::getInstance().setCar((*iter)->getId(),  (*iter)->getActualPoint().getX(), (*iter)->getActualPoint().getY());
                ++iter;
            }
        }

        std::this_thread::sleep_for (std::chrono::milliseconds(50));
    }
}

bool TrafficControl::createNewCar(PtrToConstPoint src, PtrToConstPoint dst, const int& speed){
    std::vector<PtrToConstPoint>route;

    findRoute(src, dst, route);

    if(route.empty() || speed<=0)
        return false;

    //PtrToConstPoint beginPoint = route[0];
    //route.erase(route.begin());
    cars.push_back( createCar(*route[0], route, speed, getNextCarId()) );

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
    PtrCross currentCross = findNearestCross(src);
    if(currentCross == nullptr)
        return;
    prepareFinding();
    currentCross->setVisited(true);
    foundRoute.push(currentCross);

    while(!checkPointMeetsCross(dst, foundRoute.top())){

        currentCross = foundRoute.top()->getNotVisitedNeighbours();
        if(!currentCross){
                foundRoute.pop();
        }

        else{
            foundRoute.push(currentCross);
            currentCross->setVisited(true);
        }
        if(foundRoute.empty()) return;
    }



    if(*(foundRoute.top()->getPosition()) != *dst){
        readyRoute.push_back(dst);
    }
    if(!checkPointMeetsCross(src, foundRoute.top())){
        while(!foundRoute.empty()){
            readyRoute.push_back(foundRoute.top()->getPosition());
            if(checkPointMeetsCross(src, foundRoute.top()))break;
            foundRoute.pop();
        }
    }

    if(*readyRoute.back() != *src)
        readyRoute.push_back(src);
    std::reverse(readyRoute.begin(), readyRoute.end());
}

void TrafficControl::prepareFinding() {

    for (std::vector<PtrCross>::size_type i=0; i<crosses.size(); ++i){
        crosses[i]->setVisited(false);
    }
}

bool TrafficControl::checkPointMeetsCross(const PtrToConstPoint &point, const PtrCross &cross) const{

    if(*cross->getPosition() == *point)
        return true;

    else if(cross->getPosition()->getX() == point->getX()){
        if(cross->getPosition()->getY() > point->getY() && cross->getNorthNeighbour() != nullptr){
            if(point->getY() > cross->getNorthNeighbour()->getPosition()->getY())
                return true;
        }

        else if(cross->getPosition()->getY() < point->getY() && cross->getSouthNeighbour() != nullptr){
            if(point->getY() < cross->getSouthNeighbour()->getPosition()->getY())
                return true;
        }
    }

    else if(cross->getPosition()->getY() == point->getY()){
        if(cross->getPosition()->getX() > point->getX() && cross->getWestNeighbour() != nullptr){
            if(point->getX() > cross->getWestNeighbour()->getPosition()->getX())
                return true;
        }

        else if(cross->getPosition()->getX() < point->getX() && cross->getEastNeighbour() != nullptr){
            if(point->getX() < cross->getEastNeighbour()->getPosition()->getX())
                return true;
        }
    }
    return false;
}

PtrCross TrafficControl::findNearestCross(const PtrToConstPoint &point) const{
    for(std::vector<PtrCross>::size_type i = 0; i<crosses.size(); ++i){

        if(*crosses[i]->getPosition() == *point)
            return crosses[i];

        else if(crosses[i]->getPosition()->getX() == point->getX()){
            if(crosses[i]->getPosition()->getY() > point->getY() && crosses[i]->getNorthNeighbour() != nullptr){
                if(point->getY() > crosses[i]->getNorthNeighbour()->getPosition()->getY())
                    return crosses[i];
            }

            else if(crosses[i]->getPosition()->getY() < point->getY() && crosses[i]->getSouthNeighbour() != nullptr){
                if(point->getY() < crosses[i]->getSouthNeighbour()->getPosition()->getY())
                    return crosses[i];
            }
        }

        else if(crosses[i]->getPosition()->getY() == point->getY()){
            if(crosses[i]->getPosition()->getX() > point->getX() && crosses[i]->getWestNeighbour() != nullptr){
                if(point->getX() > crosses[i]->getWestNeighbour()->getPosition()->getX())
                    return crosses[i];
            }

            else if(crosses[i]->getPosition()->getX() < point->getX() && crosses[i]->getEastNeighbour() != nullptr){
                if(point->getX() < crosses[i]->getEastNeighbour()->getPosition()->getX())
                    return crosses[i];
            }
        }

        /*else if(crosses[i]->getEastNeighbour() != nullptr){
            if(crosses[i]->getPosition()->getX() <= point->getX() && point->getX() <=crosses[i]->getEastNeighbour()->getPosition()->getX()
               && point->getY()  == crosses[i]->getPosition()->getY())
                return crosses[i];
        }

        else if (crosses[i]->getNorthNeighbour() != nullptr){
            if(crosses[i]->getPosition()->getY() <= point->getY() && point->getY() <=crosses[i]->getSouthNeighbour()->getPosition()->getY()
               && point->getX()  == crosses[i]->getPosition()->getX())
                return crosses[i];
        }

        else if (crosses[i]->getSouthNeighbour() != nullptr){
            if(crosses[i]->getPosition()->getY() <= point->getY() && point->getY() <=crosses[i]->getNorthNeighbour()->getPosition()->getY()
               && point->getX()  == crosses[i]->getPosition()->getX())
                return crosses[i];
        }

        else if (crosses[i]->getSouthNeighbour() != nullptr){
            if(crosses[i]->getPosition()->getY() <= point->getY() && point->getY() <=crosses[i]->getSouthNeighbour()->getPosition()->getY()
               && point->getX()  == crosses[i]->getPosition()->getX())
                return crosses[i];
        }*/
    }
    return nullptr;
}
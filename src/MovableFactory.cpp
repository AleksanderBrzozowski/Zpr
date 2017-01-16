//
// Created by kuco on 12.01.17.
//


#include <algorithm>
#include "MovableFactory.h"

unsigned int MovableFactory::getMovableId() {
    static unsigned int id=0;
    return id++;
}

std::list<PtrCar>& MovableFactory::getCars(){
    return cars;
}

std::list<PtrHuman>& MovableFactory::getHumans(){
    return humans;
}

bool MovableFactory::createCar(PtrToConstPoint src, PtrToConstPoint dst, int speed, std::vector<PtrCross> &crosses){
    std::vector<PtrToConstPoint>route;

    findRoute(src, dst, route, crosses);

    if(route.empty() || speed<=0)
        return false;

    cars.push_back( Car::createCar(*route[0], route, speed, getMovableId()) );

    return true;
}

bool MovableFactory::createHuman(PtrToConstPoint src, PtrToConstPoint dst, int speed, std::vector<PtrCross> &crosses) {
    std::vector<PtrToConstPoint>route;

    findRoute(src, dst, route, crosses);

    if(route.empty() || speed<=0)
        return false;

    humans.push_back( Human::createHuman(*route[0], route, speed, getMovableId()) );

    return true;

}

void MovableFactory::findRoute(PtrToConstPoint src, PtrToConstPoint dst, std::vector<PtrToConstPoint>&readyRoute, std::vector<PtrCross> &crosses) {

    std::stack<PtrCross>foundRoute;
    PtrCross currentCross = findNearestCross(src, crosses);
    if(currentCross == nullptr)
        return;

    prepareRouteFinding(crosses);
    currentCross->setVisited(true);
    foundRoute.push(currentCross);


    while(!pointMeetsCross(dst, foundRoute.top(), crosses)){

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

    while(!foundRoute.empty()){
        readyRoute.push_back(foundRoute.top()->getPosition());
        if(pointMeetsCross(src, foundRoute.top(), crosses))break;
        foundRoute.pop();
    }

    if(readyRoute.empty() || *readyRoute.back() != *src)
        readyRoute.push_back(src);
    std::reverse(readyRoute.begin(), readyRoute.end());
    if(*readyRoute.back() != *dst);
    readyRoute.push_back(dst);
}

void MovableFactory::prepareRouteFinding(std::vector<PtrCross> &crosses) {

    for (std::vector<PtrCross>::size_type i=0; i<crosses.size(); ++i){
        crosses[i]->setVisited(false);
    }
}

bool MovableFactory::pointMeetsCross(PtrToConstPoint point, PtrCross cross, const std::vector<PtrCross> &crosses) const{

    if(*cross->getPosition() == *point)
        return true;

    else if(cross->getPosition()->getX() == point->getX()){
        if(cross->getPosition()->getY() >= point->getY() && cross->getNorthNeighbour() != nullptr){
            if(point->getY() >= cross->getNorthNeighbour()->getPosition()->getY())
                return true;
        }

        else if(cross->getPosition()->getY() <= point->getY() && cross->getSouthNeighbour() != nullptr){
            if(point->getY() <= cross->getSouthNeighbour()->getPosition()->getY())
                return true;
        }
    }

    else if(cross->getPosition()->getY() == point->getY()){
        if(cross->getPosition()->getX() >= point->getX() && cross->getWestNeighbour() != nullptr){
            if(point->getX() >= cross->getWestNeighbour()->getPosition()->getX())
                return true;
        }

        else if(cross->getPosition()->getX() <= point->getX() && cross->getEastNeighbour() != nullptr){
            if(point->getX() <= cross->getEastNeighbour()->getPosition()->getX())
                return true;
        }
    }
    return false;
}

PtrCross MovableFactory::findNearestCross(PtrToConstPoint point, const std::vector<PtrCross> &crosses) const{
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
    }
    return nullptr;
}
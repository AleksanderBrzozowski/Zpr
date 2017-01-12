//
// Created by kuco on 02.11.16.
//

#include <stdexcept>
#include "Cross.h"

Cross::Cross(PtrToConstPoint pos): position(pos), southNeighbour(nullptr),
    eastNeighbour(nullptr), northNeighbour(nullptr), westNeighbour(nullptr){}


bool Cross::setVisited(const bool& wasVisited) {
    visited = wasVisited;
    return visited;
}

bool Cross::getVisited() const {return visited;}

PtrCross Cross::getNotVisitedNeighbours() const{

    if(northNeighbour!=nullptr)
        if(!northNeighbour->getVisited())
            return northNeighbour;
    if(westNeighbour!=nullptr)
        if(!westNeighbour->getVisited())
            return westNeighbour;
    if(eastNeighbour!=nullptr)
        if(!eastNeighbour->getVisited())
            return eastNeighbour;
    if(southNeighbour!=nullptr)
        if(!southNeighbour->getVisited())
            return southNeighbour;

    return nullptr;
}

PtrToConstPoint Cross::getPosition() const {return position;}

PtrCross Cross::getEastNeighbour() const {return eastNeighbour;}
PtrCross Cross::getWestNeighbour() const {return westNeighbour;}
PtrCross Cross::getNorthNeighbour() const {return northNeighbour;}
PtrCross Cross::getSouthNeighbour() const {return southNeighbour;}

void Cross::addNeighbour(PtrCross cr) {
    if(*(cr->getPosition()) == *position) return;

    if(cr->getPosition()->getX() == this->position->getX())
        if(cr->getPosition()->getY() < this->position->getY())
            northNeighbour = cr;
        else
            southNeighbour = cr;

    if(cr->getPosition()->getY() == this->position->getY())
        if(cr->getPosition()->getX() < this->position->getX())
            westNeighbour = cr;
        else
            eastNeighbour = cr;
}

bool Cross::operator==(const Cross &rhs) const{
    return *this->position.get() == *rhs.position.get();
}

bool Cross::operator!=(const Cross &rhs) const{
    return !(*this->position.get() == *rhs.position.get());
}

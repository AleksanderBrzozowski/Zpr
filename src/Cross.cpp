/**
 * @file Cross.cpp
 * @Author PiotrKuc (piotr.kuc29@gmail.com)
 * @date November, 2017
 * @brief Cross class methods implementation
 *
 */

#include <stdexcept>
#include "Cross.h"

///Contructor for Cross
Cross::Cross(PtrToConstPoint pos): position(pos), southNeighbour(nullptr),
    eastNeighbour(nullptr), northNeighbour(nullptr), westNeighbour(nullptr){}

/**
 * @brief Changes the wasVisited parameter by the finding route algorithm.
 * @param wasVisited - describes if the cross was used by the finding route algorithm and cannot be reused.
 * @return the new value of wasVisited parameter.
 */
bool Cross::setVisited(const bool& wasVisited) {
    visited = wasVisited;
    return visited;
}

bool Cross::getVisited() const {return visited;}

/**
 * @brief Get this cross' neighbour that wasn't be used so far.
 * @return not visited neighbour of this cross.
 */
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

/**
 * @brief Adding new neighbour and deciding if the new neighbour is on the north, east, west or south.
 * @param cr - new neighbour.
 */

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


///@return Returns true if two crosses have the same position.


bool Cross::operator==(const Cross &rhs) const{
    return *this->position.get() == *rhs.position.get();
}

///@return Returns true if two crosses have different positions.
bool Cross::operator!=(const Cross &rhs) const{
    return !(*this->position.get() == *rhs.position.get());
}

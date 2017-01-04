//
// Created by kuco on 02.11.16.
//

#include <stdexcept>
#include "Cross.h"

Cross::Cross(PtrToConstPoint pos): position(pos) {}


bool Cross::setVisited(const bool& wasVisited) {
    visited = wasVisited;
    return visited;
}

bool Cross::getVisited() const {return visited;}

PtrCross Cross::getNotVisitedNeighbours() {
    for(std::vector<PtrCross>::size_type i=0;i<neighbours.size();++i){
        if(!neighbours[i]->getVisited())
            return  neighbours[i];
    }
    return nullptr;
}

PtrToConstPoint Cross::getPosition() const {return position;}

void Cross::addNeighbour(PtrCross cr) {
        neighbours.push_back(cr);
}

bool Cross::operator==(const Cross &rhs) const{
    return *this->position.get() == *rhs.position.get();
}

bool Cross::operator!=(const Cross &rhs) const{
    return !(*this->position.get() == *rhs.position.get());
}
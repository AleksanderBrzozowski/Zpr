//
// Created by kuco on 02.11.16.
//

#include <stdexcept>
#include "Cross.h"

Cross::Cross(const unsigned int& crossId, Point* pos): id(crossId), position(pos) {}


bool Cross::setVisited(const bool& wasVisited) {
    visited = wasVisited;
    return visited;
}

bool Cross::getVisited() const {return visited;}

Cross* Cross::getNotVisitedNeighbours() {
    for(int i=0;i<(int)neighbours.size();++i){
        if(!neighbours[i]->getVisited())
            return  neighbours[i];
    }
    return nullptr;
}

unsigned int Cross::getId() const {return id;}

Point* Cross::getPosition() const {return position;}

void Cross::addNeighbour(Cross* cr) {
        neighbours.push_back(cr);
}
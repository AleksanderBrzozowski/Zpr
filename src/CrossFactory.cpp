//
// Created by kuco on 13.12.16.
//

#include "CrossFactory.h"


bool CrossFactory::cmpCrossX(const PtrCross &cr1, const PtrCross &cr2){

    if(cr1->getPosition()->getX() == cr2->getPosition()->getX())
        return cr1->getPosition()->getY()<cr2->getPosition()->getY();

    return cr1->getPosition()->getX()<cr2->getPosition()->getX();
}
bool CrossFactory::cmpCrossY(const PtrCross &cr1, const PtrCross &cr2){
    if(cr1->getPosition()->getY() == cr2->getPosition()->getY())
        return cr1->getPosition()->getX()<cr2->getPosition()->getX();
    return cr1->getPosition()->getY()<cr2->getPosition()->getY();
}


std::vector<PtrCross>& CrossFactory::getCrosses(){
    return crosses;
}


PtrCross CrossFactory::findCrossByPoint(const PtrToConstPoint &point) const {

    for(std::vector<PtrCross>::size_type i = 0; i<crosses.size(); ++i ){
        if(*(crosses[i]->getPosition()) == *point){
            return crosses[i];
        }
    }
    return nullptr;
}

PtrCross CrossFactory::createNewCross(const PtrToConstPoint &point) {
    PtrCross newCross = findCrossByPoint(point);
    if(newCross == nullptr) {
        newCross = std::make_shared<Cross>(point);
        crosses.push_back(newCross);
        return newCross;
    }
    return newCross;
}

void CrossFactory::twoVertRoads(const PtrToConstPoint &begin, const PtrToConstPoint &end) {
    std::sort(crosses.begin(), crosses.end(), CrossFactory::cmpCrossX);
    for(std::vector<PtrCross>::size_type i = 0; i<crosses.size(); ++i ){
        if(crosses[i]->getPosition()->getX() == begin->getX()
                && crosses[i]->getPosition()->getY() >= begin->getY()
                && crosses[i]->getPosition()->getY() <= end->getY()){
            PtrCross currentCross = crosses[i];
            PtrCross newCross = createNewCross(begin);
            while(currentCross->getNorthNeighbour()!= nullptr){
                if(currentCross->getNorthNeighbour()->getPosition()->getY()<=begin->getY())
                    break;
                else
                    currentCross=currentCross->getNorthNeighbour();
            }
            newCross->addNeighbour(currentCross);
            currentCross->addNeighbour(newCross);
            currentCross=newCross;
            newCross = createNewCross(end);
            while(currentCross->getSouthNeighbour()!= nullptr){
                if(currentCross->getSouthNeighbour()->getPosition()->getY()>=end->getY())
                    break;
                else
                    currentCross=currentCross->getSouthNeighbour();
            }
            newCross->addNeighbour(currentCross);
            currentCross->addNeighbour(newCross);

            break;
        }
    }
}

void CrossFactory::twoHorizRoads(const PtrToConstPoint &begin, const PtrToConstPoint &end) {
    std::sort(crosses.begin(), crosses.end(), CrossFactory::cmpCrossY);
    for(std::vector<PtrCross>::size_type i = 0; i<crosses.size(); ++i ){
        if(crosses[i]->getPosition()->getY() == begin->getY()
           && crosses[i]->getPosition()->getX() >= begin->getX()
           && crosses[i]->getPosition()->getX() <= end->getX()){
            PtrCross currentCross = crosses[i];
            PtrCross newCross = createNewCross(begin);
            while(currentCross->getWestNeighbour()!= nullptr){
                if(currentCross->getWestNeighbour()->getPosition()->getX()<=begin->getX())
                    break;
                else
                    currentCross=currentCross->getWestNeighbour();
            }
            newCross->addNeighbour(currentCross);
            currentCross->addNeighbour(newCross);
            currentCross=newCross;
            newCross = createNewCross(end);
            while(currentCross->getEastNeighbour()!= nullptr){
                if(currentCross->getEastNeighbour()->getPosition()->getX()>=end->getX())
                    break;
                else
                    currentCross=currentCross->getEastNeighbour();
            }
            newCross->addNeighbour(currentCross);
            currentCross->addNeighbour(newCross);

            break;
        }
    }
}

void CrossFactory::vertCrossedRoad(const PtrToConstPoint &begin, const PtrToConstPoint &end){

    std::sort(crosses.begin(), crosses.end(), cmpCrossY);
    PtrCross currentNorth = createNewCross(begin);

    std::vector<PtrCross>::size_type nbCrosses = crosses.size();
    for(std::vector<PtrCross>::size_type i = 0; i<nbCrosses; ++i ){

        PtrCross left = crosses[i];
        PtrCross right = left->getEastNeighbour();

        //checking only eastNeighbour
        if(right == nullptr) continue;

        //if new road crosses with the other that already exists
        if( left->getPosition()->getX() <= currentNorth->getPosition()->getX() && currentNorth->getPosition()->getX() <= right->getPosition()->getX()
            && currentNorth->getPosition()->getY() <= left->getPosition()->getY() && left->getPosition()->getY() <= end->getY()){

                PtrCross newCross = createNewCross( std::make_shared<Point>(currentNorth->getPosition()->getX(), left->getPosition()->getY()) );
                left->addNeighbour(newCross);
                right->addNeighbour(newCross);
                newCross->addNeighbour(left);
                newCross->addNeighbour(right);
                if(newCross != currentNorth){
                    currentNorth->addNeighbour(newCross);
                    newCross->addNeighbour(currentNorth);
                    currentNorth = newCross;
                }
        }
    }
    PtrCross newCross = createNewCross(end);
    if(newCross != currentNorth){
        currentNorth->addNeighbour(newCross);
        newCross->addNeighbour(currentNorth);
    }
}

void CrossFactory::horizCrossedRoad(const PtrToConstPoint &begin, const PtrToConstPoint &end){

    std::sort(crosses.begin(), crosses.end(), CrossFactory::cmpCrossX);

    PtrCross currentWest = createNewCross(begin);

    std::vector<PtrCross>::size_type nbCrosses = crosses.size();
    for(std::vector<PtrCross>::size_type i = 0; i<nbCrosses; ++i ){

        PtrCross top = crosses[i];
        PtrCross bottom = top->getSouthNeighbour();

        //checking only southNeighbour
        if(bottom == nullptr) continue;

        //if new road crosses with the other that already exists
        if( top->getPosition()->getY() <= currentWest->getPosition()->getY() && currentWest->getPosition()->getY() <= bottom->getPosition()->getY()
            && currentWest->getPosition()->getX() <= top->getPosition()->getX() && top->getPosition()->getX() <= end->getX()){

            PtrCross newCross = createNewCross( std::make_shared<Point>(top->getPosition()->getX(), currentWest->getPosition()->getY() ));
            top->addNeighbour(newCross);
            bottom->addNeighbour(newCross);
            newCross->addNeighbour(top);
            newCross->addNeighbour(bottom);
            if(newCross != currentWest){
                currentWest->addNeighbour(newCross);
                newCross->addNeighbour(currentWest);
                currentWest = newCross;
            }
        }
    }
    PtrCross newCross = createNewCross(end);
    if(newCross != currentWest) {
        currentWest->addNeighbour(newCross);
        newCross->addNeighbour(currentWest);
    }
}

void CrossFactory::createRoad(const PtrToConstPoint &begin, const PtrToConstPoint &end) {
    //deciding if new road is horizontal of vertical, begin must nearer top left corner
    if(begin->getX() == end->getX()){
        if(begin->getY() > end->getY()){
            vertCrossedRoad(end, begin);
            twoVertRoads(end,begin);
        }
        else if(begin->getY() < end->getY()){
            vertCrossedRoad(begin, end);
            twoVertRoads(begin,end);
        }
    }
    else if(begin->getY() == end->getY()){
        if(begin->getX() > end->getX()){
            horizCrossedRoad(end, begin);
            twoHorizRoads(end, begin);
        }

        else if(begin->getX() < end->getX()){
            horizCrossedRoad(begin, end);
            twoHorizRoads(begin, end);
        }
    }
}


//
// Created by kuco on 13.12.16.
//

#include <iostream>
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

CrossFactory::CrossFactory(std::vector<PtrCross> & cr) : crosses(cr) {}

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


void CrossFactory::verticalRoad(const PtrToConstPoint &begin, const PtrToConstPoint &end){

    std::sort(crosses.begin(), crosses.end(), cmpCrossX);
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

void CrossFactory::horizontalRoad(const PtrToConstPoint &begin, const PtrToConstPoint &end){

    std::sort(crosses.begin(), crosses.end(), CrossFactory::cmpCrossY);

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
        if(begin->getY() > end->getY())
            verticalRoad(end, begin);
        else if(begin->getY() < end->getY())
            verticalRoad(begin, end);
    }
    else if(begin->getY() == end->getY()){
        if(begin->getX() > end->getX())
            horizontalRoad(end, begin);
        else if(begin->getX() < end->getX())
            horizontalRoad(begin, end);
    }
}

/*
PtrCross CrossFactory::createCross(PtrToConstPoint point, std::vector<PtrCross>& crosses){
    std::vector<PtrCross>::size_type cross_index = findCrossIndex(point, crosses);
    if( cross_index == crosses.size() ){
        PtrCross  newCross = std::make_shared<Cross>(point->getX(), point->getY());
        crosses.push_back(newCross);
        return newCross;
    }
    return crosses[cross_index];
}

PtrCross CrossFactory::insertCrossVerticaly(PtrToConstPoint begin, PtrToConstPoint end, PtrCross cr1, PtrCross cr2, std::vector<PtrCross>&crosses) {

    PtrCross tempNeighbour = std::make_shared<Cross>(begin->getX(), cr1->getPosition()->getY());
    crosses.push_back(tempNeighbour);
    cr1->addNeighbour(tempNeighbour);

}


void CrossFactory::findCrossedRoads(PtrToConstPoint begin, PtrToConstPoint end, std::vector<PtrCross>& crosses){

    //if new road is vertical
    if(begin->getY() == end->getY()){

        PtrCross nearestNorthNeigh= createCross(begin, crosses);

        for(std::vector<PtrCross>::size_type i = 0; i<crosses.size(); ++i ){

            //checking only eastNeighbour
            if(crosses[i]->getEastNeighbour() == nullptr) continue;

            //if new road crosses with the other that already exists
            if( crosses[i]->getPosition()->getX() <= begin->getX() <= crosses[i]->getEastNeighbour()->getPosition()->getX()
                && begin->getY() <= crosses[i]->getPosition()->getY() <= end->getY()){

            }
        }
    }

    //else if new road is horizontal
    else if(begin->getX() == end->getX()){
        for(std::vector<PtrCross>::size_type i =0; i<crosses.size(); ++i){

            //checking only southNeighbour
            if(crosses[i]->getSouthNeighbour() == nullptr) continue;

            //if new road crosses with the other that already exists
            if( crosses[i]->getPosition()->getY() <= begin->getY() <= crosses[i]->getSouthNeighbour()->getPosition()->getY()
                    && begin->getX() <= crosses[i]->getPosition()->getX() <= end->getX()){
                //TODO
            }
        }
    }
}

void CrossFactory::createCrossesFromSingleRoad( PtrToConstPoint begin, PtrToConstPoint end, std::vector<PtrCross>& crosses){

    std::vector<PtrCross>::size_type tempCross1Index = findCrossIndex(begin, crosses);
    std::vector<PtrCross>::size_type tempCross2Index = findCrossIndex(end  , crosses);

    if(tempCross1Index>=crosses.size() && tempCross2Index>=crosses.size()){
        PtrCross newCross1 = std::make_shared<Cross>(begin);
        PtrCross newCross2 = std::make_shared<Cross>(end);
        newCross1->addNeighbour(newCross2);
        newCross2->addNeighbour(newCross1);
        crosses.push_back(newCross1);
        crosses.push_back(newCross2);
    }

    else if(tempCross1Index>=crosses.size() && tempCross2Index<crosses.size()){
        PtrCross newCross = std::make_shared<Cross>(begin);
        crosses[tempCross2Index]->addNeighbour(newCross);
        newCross->addNeighbour(crosses[tempCross2Index]);
        crosses.push_back(newCross);
    }


    else if(tempCross2Index>=crosses.size() && tempCross1Index<crosses.size()) {
        PtrCross newCross = std::make_shared<Cross>(end);
        crosses[tempCross1Index]->addNeighbour(newCross);
        newCross->addNeighbour(crosses[tempCross1Index]);
        crosses.push_back(newCross);
    }
    else{
        crosses[tempCross2Index]->addNeighbour(crosses[tempCross1Index]);
        crosses[tempCross1Index]->addNeighbour(crosses[tempCross2Index]);
    }
}

void CrossFactory::createRoute(PtrToConstPoint begin, PtrToConstPoint end,  std::vector<PtrCross>&crosses) {

    /*before calling next methods begin must be nearer top left corner than end, if not -> replace them
     * while calling methods*/
  /*  if((begin->getX() == end->getX() && begin->getY() > end->getY())
            || begin->getY() == end->getY() && begin->getX() > end->getX()){

        findCrossedRoads(end, begin, crosses);
        createCrossesFromSingleRoad(end, begin, crosses);
    }

    else{
        findCrossedRoads(begin, end, crosses);
        createCrossesFromSingleRoad(begin, end, crosses);
    }



}

std::vector<PtrCross>::size_type CrossFactory::findCrossIndex(PtrToConstPoint point, const std::vector<PtrCross>& crosses) {

    for(std::vector<PtrCross>::size_type i = 0; i<crosses.size(); ++i ){
        if(*(crosses[i]->getPosition()) == *point){
            return i;
        }
    }
    return crosses.size();
}
*/


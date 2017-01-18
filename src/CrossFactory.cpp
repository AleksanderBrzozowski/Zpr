/**
 * @file CrossFactory.cpp
 * @Author PiotrKuc (piotr.kuc29@gmail.com)
 * @date December, 2017
 * @brief CrossFactory class methods implementation
 *
 */

#include "CrossFactory.h"

/**
 * @brief X value of cross position comparator for sorting.
 * @details Returns true if cross1 is nearer left. If both crosses have the same x, returns true if cross1 has smaller y than cross2.
 * @param cr1 - first cross.
 * @param cr2 - second cross.
 * @return true if x value of cross 1 is smaller than x value of cross 2, if both x values are the
 * same, returns true if y value of cross 1 is smaller.
 */

bool CrossFactory::cmpCrossX(const PtrCross &cr1, const PtrCross &cr2){

    if(cr1->getPosition()->getX() == cr2->getPosition()->getX())
        return cr1->getPosition()->getY()<cr2->getPosition()->getY();

    return cr1->getPosition()->getX()<cr2->getPosition()->getX();
}

/**
 * @brief Y value of cross position comparator for sorting.
 * @details Returns true if cross1 is nearer top. If both crosses have the same y, returns true if cross1 has smaller x than cross2.
 * @param cr1 - first cross.
 * @param cr2 - second cross.
 * @return true if y value of cross1 is smaller than y value of cross2, if both y values are the
 * same, returns true if x value of cross1 is smaller.
 */

bool CrossFactory::cmpCrossY(const PtrCross &cr1, const PtrCross &cr2){
    if(cr1->getPosition()->getY() == cr2->getPosition()->getY())
        return cr1->getPosition()->getX()<cr2->getPosition()->getX();
    return cr1->getPosition()->getY()<cr2->getPosition()->getY();
}


std::vector<PtrCross>& CrossFactory::getCrosses(){
    return crosses;
}

/**
 * @brief Find the cross that has the same position as the given point as the argument
 * @details Return cross that has the same position as given.
 * @param point - given point to search.
 * @return cross that has the same point as given.
 */
PtrCross CrossFactory::findCrossByPoint(const PtrToConstPoint &point) const {

    for(std::vector<PtrCross>::size_type i = 0; i<crosses.size(); ++i ){
        if(*(crosses[i]->getPosition()) == *point){
            return crosses[i];
        }
    }
    return nullptr;
}

/**
 * @brief Creating new cross if it doesn't exist.
 * @details Checking if cross at given position already exists. If not creates new cross.
 * @param point - point at which we want to create new cross.
 * @return cross at given point.
 */

PtrCross CrossFactory::createNewCross(const PtrToConstPoint &point) {
    PtrCross newCross = findCrossByPoint(point);
    if(newCross == nullptr) {
        newCross = std::make_shared<Cross>(point);
        crosses.push_back(newCross);
        return newCross;
    }
    return newCross;
}

/**
 * @brief Updates crosses if new road hide the existing, both roads are verticaly.
 * @details Check if two roads are vertical and both of roads have the same x value.
 * (If one road hides another road).
 * At first crosses are sorted. First cross should has the smallest x value of the position
 * Then we look for the two crosses, between which the new road is being tried to set.
 * If found, we create new crosses and update neighbours from the north to the south.
 * @param begin - point on the north of the new road.
 * @param end - point on the south of the new road.
 */

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

/**
 * @brief Updates crosses if new road hide the existing, both roads are horizontaly
 * @details Check if two roads are horizontal and both of roads have the same y value.
 * (If one road hides another road).
 * At first crosses are sorted. First cross should has the smallest y value of the position.
 * Then we look for the two crosses, between which the new road is being tried to set.
 * If found, we create new crosses and update neighbours from the west to the east.
 * @param begin - point on the west of the new road.
 * @param end - point on the east of the new road.
 */


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

/**
 * @brief Updates crosses if new road crosses the existed one verticaly.
 * @details This method creates new crosses if the new road crosses with the another roads.
 * The new road is vertical.
 * At first, crosses are sorted. The first is cross that has the smallest y value of the position.
 * Then we check each pair of cross and it's east neighbour, if the new road doesn't cross the road
 * between these pair of crosses. If it crosses, new crosses are added and neighbours are updated.
 * @param begin - point on the north of the new road.
 * @param end - point on the south of the new road.
 */

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

/**
 * @brief Updates crosses if new road crosses the existed one horizontaly
 * @details This method creates new crosses if the new road crosses with the another roads.
 * The new road is horizontal.
 * At first, crosses are sorted. The first is cross that has the smallest x value of the position.
 * Then we check each pair of cross and it's south neighbour, if the new road doesn't cross the road
 * between these pair of crosses. If it crosses, new crosses are added and neighbours are updated.
 * @param begin - point on the west of the new road.
 * @param end - point on the east of the new road.
 */

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

/**
 * @brief Updating crosses, creating new crosses from the given road
 * @details Reverses the begin and ending point of the road if the ending point is nearer top left corner of the map.
 * Then calls methods if the new road is horizontal or vertical.
 * @param begin - starting point of the new road.
 * @param end - ending point of the new road.
 */

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


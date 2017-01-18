/**
 * @file Map.cpp
 * @Author PiotrKuc (piotr.kuc29@gmail.com)
 * @date January, 2017
 * @brief MovableFactory class methods implementation
 *
 */


#include <algorithm>
#include "MovableFactory.h"

/**
 * Method creating new ID for movables.
 * @return new Id for movables
 */

unsigned int MovableFactory::getMovableId() {
    static unsigned int id=0;
    if(id == std::numeric_limits<unsigned int>::max()){
        unsigned int newId = 0;
        std::for_each(humans.begin(), humans.end(), [&](PtrHuman h){if(h->getId()>newId)newId=h->getId()-1;});
        return newId;
    }

    return id++;
}

std::list<PtrCar>& MovableFactory::getCars(){
    return cars;
}

std::list<PtrHuman>& MovableFactory::getHumans(){
    return humans;
}

/**
 * Method at first looks for a route between starting and ending points.
 * If route was found, creates car and includes it to the simulation.
 * @param src as shared_ptr to const Point type object, starting point of the car's route
 * @param dst as shared_ptr to const Point type object, ending point of the car's route
 * @param speed integer argument, speed of car
 * @param crosses vector of shared_ptr to Crosses type objects, needed to make route for car
 * @return true if route betweend starting and ending points was found and car was created
 */

bool MovableFactory::createCar(PtrToConstPoint src, PtrToConstPoint dst, int speed, std::vector<PtrCross> &crosses){
    std::vector<PtrToConstPoint>route;

    findRoute(src, dst, route, crosses);

    if(route.empty() || speed<=0)
        return false;

    cars.push_back( Car::createCar(*route[0], route, speed, getMovableId()) );

    return true;
}

/**
 * Method at first looks for a route between starting and ending points.
 * If route was found, creates human and includes it to the simulation.
 * @param src as shared_ptr to const Point type object, starting point of the human's route
 * @param dst as shared_ptr to const Point type object, ending point of the human's route
 * @param speed integer argument, speed of human
 * @param crosses vector of shared_ptr to Crosses type objects, needed to make route for human
 * @return true if route betweend starting and ending points was found and human was created
 */

bool MovableFactory::createHuman(PtrToConstPoint src, PtrToConstPoint dst, int speed, std::vector<PtrCross> &crosses) {
    std::vector<PtrToConstPoint>route;

    findRoute(src, dst, route, crosses);

    if(route.empty() || speed<=0)
        return false;
    moveHumansOnSidewalks(route);
    humans.push_back( Human::createHuman(*route[0], route, speed, getMovableId()) );

    return true;

}

/**
 * Adding offset between the street and sidewalk to every point in the found route to
 * make humans walking on the sidewalks.
 * @param route as vector of shared_ptr to const Point type objects to add to each point offset between streets and sidewalks
 */

void MovableFactory::moveHumansOnSidewalks(std::vector<PtrToConstPoint> & route) {
    for(std::vector<PtrToConstPoint>::size_type i = 0; i<route.size(); ++i){
            int newX =  humans.size()%2 == 0 ? route[i]->getX() - PplGUI::OFFSET  :  route[i]->getX() + PplGUI::OFFSET;
            int newY =  humans.size()%2 == 0 ? route[i]->getY() - PplGUI::OFFSET  :  route[i]->getY() + PplGUI::OFFSET;;
            PtrToConstPoint newPoint = std::make_shared<Point>(newX, newY);
            route[i] = newPoint;
    }
}

/**
 * Finding route between starting point and ending point.
 * Finding route algorith runs similar to the DFS algorith in graphs.
 * @param src starting point as shared_ptr<Point>
 * @param dst endign point as shared_ptr<Point>
 * @param readyRoute vector to which new points will be written
 * @param crosses vector of crosses to find route
 */

void MovableFactory::findRoute(PtrToConstPoint src, PtrToConstPoint dst, std::vector<PtrToConstPoint>&readyRoute, std::vector<PtrCross> &crosses) {

    std::stack<PtrCross>foundRoute;
    PtrCross currentCross = findNearestCross(src, crosses);
    if(currentCross == nullptr)
        return;

    prepareRouteFinding(crosses);
    currentCross->setVisited(true);
    foundRoute.push(currentCross);


    while(!pointMeetsCross(dst, foundRoute.top())){

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
        if(pointMeetsCross(src, foundRoute.top()))break;
        foundRoute.pop();
    }

    if(readyRoute.empty() || *readyRoute.back() != *src)
        readyRoute.push_back(src);
    std::reverse(readyRoute.begin(), readyRoute.end());
    if(*readyRoute.back() != *dst);
    readyRoute.push_back(dst);
}

/**
 * Preparing crosses to be used by the finding route algorith.
 * @param crosses to change crosses parametr
 */

void MovableFactory::prepareRouteFinding(std::vector<PtrCross> &crosses) {

    for (std::vector<PtrCross>::size_type i=0; i<crosses.size(); ++i){
        crosses[i]->setVisited(false);
    }
}

/**
 * Checking if point has direct route to the given cross (without any crosses (on the way)
 * @param point as shared_ptr<Point>, which point we want to check
 * @param cross as shared_ptr<Cross>, wchoch cross we want to check
 * @return true if given point has direct route to given cross
 */

bool MovableFactory::pointMeetsCross(PtrToConstPoint point, PtrCross cross) const{

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

/**
 * Finds the cross that has direct route to the given point.
 * @param point as shared_ptr<Point>, given point
 * @param crosses as vector of shared_ptr<Cross> consisting of every existing crosses
 * @return shared_ptr<Cross> of the cross that directly "sees" the given point
 */

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
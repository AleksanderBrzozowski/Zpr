/**
 * @file Map.cpp
 * @Author PiotrKuc (piotr.kuc29@gmail.com)
 * @date January, 2017
 * @brief Map class methods implementation
 *
 */

#include "Map.h"
#include <GUI/mainwindow.h>

Map::Map() {
    runningMovablePermission = false;
    cameraScanningPermission = false;
}

/**
 * @brief Calls creating methods in object of MovableFactory type.
 * @param startingPoint as shared_ptr to Point.
 * @param endingPoint as shared_ptr to Point.
 * @param speed  as integer argument.
 */


void Map::createCar(PtrToConstPoint startingPoint, PtrToConstPoint endingPoint, int speed) {
    criticalSection.lock();
    movableFactory.createCar(startingPoint, endingPoint, speed, crossFactory.getCrosses());
    criticalSection.unlock();
}

/**
 * @brief Creating new road and crosses from starting to ending point.
 * @details Checking if road may be created (for example checking if none of buildings
 * is between these two points). If not -> method returns false.
 * In other case: calling crosses creating methods from object of CrossFactory type.
 * @param begin as shared_ptr to Point.
 * @param end as shared_ptr to Point.
 * @return bool value. If true -> new road was created.
 */

bool Map::createRoad(PtrToConstPoint begin, PtrToConstPoint end) {
    criticalSection.lock();
    if(*begin == *end) {
        criticalSection.unlock();
        return false;
    }
    LineSegment lineSegment(*begin, *end);
    for (const PtrBuilding &building : facilities.getBuildings()) {
        if(building->hasIntersection(lineSegment)){
            criticalSection.unlock();
            return false;
        }
    }
    crossFactory.createRoad(begin, end);
    criticalSection.unlock();
    return true;
}

/**
 * @brief Running new thread for movables.
 * @details If permission is true, new thread is created, where all of the movables
 * run. If permission is false, the thread finishes.
 * @param permission says if running thread has to start or to stop.
 */

void Map::setRunningMovablePermission(bool permission) {
    if (runningMovablePermission == permission) return;
    runningMovablePermission = permission;
    if (runningMovablePermission)
        runningMovables = std::thread(&Map::runRunningMovables, this);
    else
        runningMovables.join();
}

/**
 * @brief Running new thread for cameras.
 * @details If permission is true, new thread is created, where all of the movables
 * run. If permission is false, the thread finishes.
 * @param permission says if running thread has to start or stop.
 */

void Map::setCameraScanningPermission(bool permission) {
    if (cameraScanningPermission == permission) return;
    cameraScanningPermission = permission;
    if (cameraScanningPermission)
        camerasScanning = std::thread(&Map::runCamerasScanning, this);
    else
        camerasScanning.join();
}

/*!
     * Adds Building represented by arguments of function.
     * @param upperLeft     Point in the upper left of building
     * @param lowerRight    Point in the lower right of building
     * @return              Is building created
     */

bool Map::createBuilding(const Point &upperLeft, const Point &lowerRight) {
    criticalSection.lock();
    Building building(upperLeft, lowerRight);
    for (PtrCross &cross : crossFactory.getCrosses()) {
        PtrToConstPoint startPoint = cross->getPosition();
        PtrCross south = cross->getSouthNeighbour();
        PtrCross east = cross->getEastNeighbour();
        if (east != nullptr && building.hasIntersection(LineSegment(*startPoint, *(east->getPosition()))) ||
            south != nullptr && building.hasIntersection(LineSegment(*startPoint, *(south->getPosition())))){
            criticalSection.unlock();
            return false;
        }
    }
    facilities.addBuilding(upperLeft, lowerRight);
    criticalSection.unlock();
    return true;
}

/**
 * @brief Main method for running movables thread.
 * @details All of the movables are asked to make the next move.
 * If movables end their journey, they are removed from the memory and GUI.
 * At the end, thread falls asleep for the time set in GUI const values.
 *
 */

void Map::runRunningMovables(){
    while(runningMovablePermission){
        criticalSection.lock();
        std::list<PtrCar> &cars = movableFactory.getCars();
        std::list<PtrCar>::iterator cars_iter = cars.begin();
        while(cars_iter!=cars.end()){
            if(!(*cars_iter)->move()){
                MainWindow::getInstance().removeObject((*cars_iter)->getId());
                cars_iter= cars.erase(cars_iter);
            }

            else {
                MainWindow::getInstance().setCar(
                        (*cars_iter)->getId(),
                        static_cast<unsigned int>((*cars_iter)->getActualPoint().getX()),
                        static_cast<unsigned int>((*cars_iter)->getActualPoint().getY()),
                        (*cars_iter)->isFast());
                ++cars_iter;
            }
        }

        std::list<PtrHuman> &humans= movableFactory.getHumans();
        std::list<PtrHuman>::iterator humans_iter = humans.begin();
        while(humans_iter!=humans.end()){
            if(!(*humans_iter)->move()){
                MainWindow::getInstance().removeObject((*humans_iter)->getId());
                humans_iter = humans.erase(humans_iter);
            }

            else {
                MainWindow::getInstance().setPpl(
                        (*humans_iter)->getId(),
                        static_cast<unsigned int>((*humans_iter)->getActualPoint().getX()),
                        static_cast<unsigned int>((*humans_iter)->getActualPoint().getY()));
                ++humans_iter;
            }
        }
        criticalSection.unlock();
        MainWindow::getInstance().refresh();

        std::this_thread::sleep_for (MainWindow::getInstance().REFRESH_TIME);
    }
}


/**
 * @brief Calls creating methods in object of MovableFactory type.
 * @param src as shared_ptr on Point type object, starting point.
 * @param dst as shared_ptr on Point type object, ending point.
 * @param speed as integer argument, speed of human.
 */

void Map::createHuman(PtrToConstPoint src, PtrToConstPoint dst, int speed){
    criticalSection.lock();
    movableFactory.createHuman(src, dst, speed, crossFactory.getCrosses());
    criticalSection.unlock();
}

/**
 * @brief Method runs cameras scanning in new thread.
 */

void Map::runCamerasScanning() {
    while (cameraScanningPermission) {
        criticalSection.lock();
        std::vector<PtrConstCar> cars(movableFactory.getCars().begin(), movableFactory.getCars().end());
        std::vector<PtrConstHuman> humans(movableFactory.getHumans().begin(), movableFactory.getHumans().end());
        facilities.scan(cars, humans);
        criticalSection.unlock();
        for (const PtrCamera &camera : facilities.getCameras()) {
            for(const PtrToConstPoint &point : camera->getSeenCars())
                std::cout << "I see car: " << *point << std::endl;
            for(const PtrToConstPoint &point : camera->getSeenHumans())
                std::cout << "I see human: " << *point << std::endl;
        }
        std::this_thread::sleep_for (MainWindow::CAMERA_SCAN_FREQ);
    }
}

/*!
     * Adds Camera represented by arguments of function.
     * @param startPoint    Camera's start point
     * @param endPoint      Camera's end point
     * @param angle         Camera's angle
     * @param accuracy      Camera's accuracy
     */


void Map::createCamera(const Point &startPoint, const Point &endPoint, double angle) {
    criticalSection.lock();
    facilities.addCamera(startPoint, endPoint, angle, 1);
    criticalSection.unlock();
}

//
// Created by kuco on 12.01.17.
//

#include "Map.h"
#include <GUI/mainwindow.h>


void Map::createCar(PtrToConstPoint startingPoint, PtrToConstPoint endingPoint, int speed) {
    movableFactory.createCar(startingPoint, endingPoint, speed, crossFactory.getCrosses());
}

void Map::createRoad(PtrToConstPoint begin, PtrToConstPoint end) {
    crossFactory.createRoad(begin, end);
}

void Map::setRunningMovablePermission(bool permission) {
    if (runningMovablePermission == permission) return;
    runningMovablePermission = permission;
    if (runningMovablePermission)
        runningMovables = std::thread(&Map::runRunningMovables, this);
    else
        runningMovables.join();
}

void Map::setCameraScanningPermission(bool permission) {
    if (cameraScanningPermission == permission) return;
    cameraScanningPermission = permission;
    if (cameraScanningPermission)
        camerasScanning = std::thread(&Map::runCamerasScanning, this);
    else
        camerasScanning.join();
}

bool Map::createBuilding(const Point &upperLeft, const Point &lowerRight) {
    Building building(upperLeft, lowerRight);
    for (PtrCross &cross : crossFactory.getCrosses()) {
        PtrToConstPoint startPoint = cross->getPosition();
        PtrCross south = cross->getSouthNeighbour();
        PtrCross east = cross->getEastNeighbour();
        if (east != nullptr && building.isCommonPointInsideBuilding(StraightLine(*startPoint, *(east->getPosition()))) ||
            south != nullptr && building.isCommonPointInsideBuilding(StraightLine(*startPoint, *(south->getPosition()))))
            return false;
    }
    facilities.addBuilding(upperLeft, lowerRight);
    return true;
}

void Map::runRunningMovables(){
    while(runningMovablePermission){
        std::list<PtrCar> &cars = movableFactory.getCars();
        std::list<PtrCar>::iterator cars_iter = cars.begin();
        while(cars_iter!=cars.end()){
            if(!(*cars_iter)->move())
                cars_iter= cars.erase(cars_iter);
            else {
                MainWindow::getInstance().setCar(
                        (*cars_iter)->getId(),
                        static_cast<unsigned int>((*cars_iter)->getActualPoint().getX()),
                        static_cast<unsigned int>((*cars_iter)->getActualPoint().getY()));
                ++cars_iter;
            }
        }

        std::list<PtrHuman> &humans= movableFactory.getHumans();
        std::list<PtrHuman>::iterator humans_iter = humans.begin();
        while(humans_iter!=humans.end()){
            if(!(*humans_iter)->move())
                humans_iter = humans.erase(humans_iter);
            else {
                MainWindow::getInstance().setPpl(
                        (*humans_iter)->getId(),
                        static_cast<unsigned int>((*humans_iter)->getActualPoint().getX()),
                        static_cast<unsigned int>((*humans_iter)->getActualPoint().getY()));
                ++humans_iter;
            }
        }
        MainWindow::getInstance().refresh();
        std::this_thread::sleep_for (std::chrono::milliseconds(50));
    }
}

void Map::createHuman(PtrToConstPoint src, PtrToConstPoint dst, int speed){
    movableFactory.createHuman(src, dst, speed, crossFactory.getCrosses());
}

void Map::runCamerasScanning() {

}

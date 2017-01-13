//
// Created by kuco on 12.01.17.
//

#include "Map.h"


void Map::createCar(PtrToConstPoint startingPoint, PtrToConstPoint endingPoint, int speed) {
    movableFactory.createCar(startingPoint, endingPoint, speed, crossFactory.getCrosses());
}

void Map::createRoad(PtrToConstPoint begin, PtrToConstPoint end) {
    crossFactory.createRoad(begin, end);
}

void Map::setRunningMovablePermission(bool permission){
    if(runningMovablePermission == permission) return;
    runningMovablePermission = permission;
    if(runningMovablePermission)
        runningMovables = std::thread(&Map::runRunningMovables, this);
    else
        runningMovables.join();
}

void Map::setCameraScanningPermission(bool permission){
    if(cameraScanningPermission == permission) return;
    cameraScanningPermission = permission;
    if(cameraScanningPermission)
        camerasScanning = std::thread(&Map::runCamerasScanning, this);
    else
        camerasScanning.join();
}

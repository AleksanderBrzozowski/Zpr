//
// Created by kuco on 12.01.17.
//

#ifndef ZPR_MAP_H
#define ZPR_MAP_H


#include "MovableFactory.h"
#include "CrossFactory.h"
#include <thread>
#include <chrono>
#include <GUI/mainwindow.h>

class Map {

private:

    MovableFactory movableFactory;
    CrossFactory crossFactory;
    std::thread runningMovables;
    std::thread camerasScanning;
    bool runningMovablePermission;
    bool cameraScanningPermission;

public:
    void createRoad(PtrToConstPoint, PtrToConstPoint);
    void createCar(PtrToConstPoint, PtrToConstPoint, int);
    void setRunningMovablePermission(bool);
    void setCameraScanningPermission(bool);
    void runRunningMovables();
    void runCamerasScanning();


};


#endif //ZPR_MAP_H
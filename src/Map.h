/**
 * @file Map.h
 * @Author PiotrKuc (piotr.kuc29@gmail.com)
 * @date January, 2017
 * @brief Map class declaration
 *
 */

#ifndef ZPR_MAP_H
#define ZPR_MAP_H


#include "MovableFactory.h"
#include "CrossFactory.h"
#include <thread>
#include <chrono>
#include <mutex>
#include "Types.h"
#include "Building.h"
#include "Facilities.h"

/**
 * @class Map
 * @brief Class allowing to create map and simulate traffics.
 * @details Contains crosses and movables factories allowing
 * GUI eassily creating map and threads to run the simulation
 */

class Map {

private:

    MovableFactory movableFactory;      ///<Object to make movables(humans and cars)
    CrossFactory crossFactory;          ///<Object to make crosses
    Facilities facilities;              ///<Object to make facilities(buildings and cameras)
    std::thread runningMovables;        ///<thread refreshing movables' positions
    std::thread camerasScanning;        ///<thread allowing cameras scanning
    bool runningMovablePermission;      ///<permision for running the thread of movables moving
    bool cameraScanningPermission;      ///<permision for cameras scanning
    std::mutex criticalSection;         ///<mutex to make thread-safe methods

public:

    bool createRoad(PtrToConstPoint, PtrToConstPoint);

    void createCar(PtrToConstPoint, PtrToConstPoint, int);

    void createHuman(PtrToConstPoint, PtrToConstPoint, int);
    bool createBuilding(const Point &upperLeft, const Point &lowerRight);
    void createCamera(const Point &startPoint, const Point &endPoint, double angle);


    void setRunningMovablePermission(bool);

    void setCameraScanningPermission(bool);

    void runRunningMovables();
    void runCamerasScanning();


};


#endif //ZPR_MAP_H

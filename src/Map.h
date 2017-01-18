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
 * @class Map
 */

class Map {

private:

    MovableFactory movableFactory;      ///<Object to make movables(humans and cars)
    CrossFactory crossFactory;          ///<Object to make crosses
    Facilities facilities;              ///<Object to make facilities(buildings and cameras)
    std::thread runningMovables;        ///<thread refreshing movables; positions
    std::thread camerasScanning;        ///<thread allowing cameras scanning
    bool runningMovablePermission;      ///<permision for running the thread of movables moving
    bool cameraScanningPermission;      ///<permision for cameras scanning
    std::mutex criticalSection;         ///<mutex to make thread-safe methods

public:
    /*!
     * Empty constructor.
     */
    Map();

    ///Creats new crosses between two points.
    bool createRoad(PtrToConstPoint, PtrToConstPoint);

    ///Creating new car in simulation.
    void createCar(PtrToConstPoint, PtrToConstPoint, int);

    ///Creating new human in simulation.
    void createHuman(PtrToConstPoint, PtrToConstPoint, int);
    /*!
     * Adds Building represented by arguments of function.
     * @param upperLeft     Point in the upper left of building
     * @param lowerRight    Point in the lower right of building
     * @return              Is building created
     */
    bool createBuilding(const Point &upperLeft, const Point &lowerRight);
    /*!
     * Adds Camera represented by arguments of function.
     * @param startPoint    Camera's start point
     * @param endPoint      Camera's end point
     * @param angle         Camera's angle
     * @param accuracy      Camera's accuracy
     */
    void createCamera(const Point &startPoint, const Point &endPoint, double angle);

    ///Method runs cars and humans in new thread.
    void setRunningMovablePermission(bool);

    ///Method runs cameras scanning in new thread.
    void setCameraScanningPermission(bool);

    ///Movables' running in new thread.
    void runRunningMovables();
    void runCamerasScanning();


};


#endif //ZPR_MAP_H

//
// Created by Aleksander on 21.12.2016.
//

#ifndef ZPR_TYPES_H
#define ZPR_TYPES_H

#include <memory>

class Point;
class Camera;
class Building;
class Cross;
class Car;
class Human;
class Movable;

typedef std::shared_ptr<const Point> PtrToConstPoint;
typedef std::shared_ptr<Cross> PtrCross;
typedef std::shared_ptr<Car> PtrCar;
typedef std::shared_ptr<Human> PtrHuman;
typedef std::shared_ptr<Building> PtrBuilding;
typedef std::shared_ptr<Camera> PtrCamera;
typedef std::shared_ptr<Movable> PtrMovable;
typedef std::shared_ptr<const Car> PtrConstCar;
typedef std::shared_ptr<const Human> PtrConstHuman;

#endif //ZPR_TYPES_H


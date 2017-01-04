//
// Created by Aleksander on 21.12.2016.
//

#ifndef ZPR_TYPES_H
#define ZPR_TYPES_H

#include <memory>
#include "Point.h"

class Cross;
class Car;
class Human;

typedef std::shared_ptr<const Point> PtrToConstPoint;
typedef std::shared_ptr<Cross> PtrCross;
typedef std::shared_ptr<Car> PtrCar;
typedef std::shared_ptr<Human> PtrHuman;

#endif //ZPR_TYPES_H


//
// Created by Aleksander on 12.12.2016.
//

#ifndef ZPR_MOVABLEFACTORY_H
#define ZPR_MOVABLEFACTORY_H


#include <memory>
#include "Movable.h"
#include "Movable2.h"

class MovableFactory {
public:
    Movable2 *createCar(const Point &startPoint, const int speed, std::vector<std::shared_ptr<Point const>> &points);
    Movable2 *createHuman(const Point &startPoint, const int speed, std::vector<std::shared_ptr<Point const>> &points);
};


#endif //ZPR_MOVABLEFACTORY_H

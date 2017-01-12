//
// Created by aleksander on 09.01.17.
//

#ifndef ZPR_FACILITIES_H
#define ZPR_FACILITIES_H


#include <vector>
#include "Types.h"
#include "Camera.h"
#include "Building.h"
#include "Movable.h"

class Facilities {
public:
    Facilities();

    PtrBuilding addBuilding(const Point &upperLeft, const Point &lowerRight);
    PtrCamera addCamera(const Point &startPoint, const Point &endPoint, double angle, int accuracy);
    void scan(std::vector<PtrMovable> &movables);
    const std::vector<PtrCamera> &getCameras() const;
private:
    std::vector<PtrBuilding> buildings;
    std::vector<PtrCamera> cameras;

    bool isMovableSeenByCamera(PtrCamera &camera, const Point &movablePoint) const;

    bool isMovableHiddenByBuilding(PtrCamera &camera, const PtrMovable &movable, const Point &movablePoint);
};


#endif //ZPR_FACILITIES_H

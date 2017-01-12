//
// Created by Aleksander on 23.12.2016.
//

#ifndef ZPR_CAMERA_H
#define ZPR_CAMERA_H


#include "Point.h"
#include "Types.h"
#include <vector>

class Camera {
public:
    Camera(const Point &startPoint, const Point &endPoint, double angle, int accuracy);

    bool isInRange(const Point &point);
    bool isInAngle(const Point &point);

    void addSeenMovable(PtrMovable movable);
    const std::vector<PtrMovable> &getSeenMovables() const;

    const Point &getStartPoint() const;
private:
    const Point startPoint;
    const Point endPoint;
    const int accuracy;
    int raySquare;
    double upperAngle;
    double lowerAngle;

    std::vector<PtrMovable> seenMovables;

    int distanceSquare(const Point &point, const Point &point1);
};

#endif //ZPR_CAMERA_H

//
// Created by Aleksander on 23.12.2016.
//

#ifndef ZPR_CAMERA_H
#define ZPR_CAMERA_H


#include "Point.h"

class Camera {
public:
    Camera(const Point startPoint, const Point endPoint, const double angle, const int accuracy);

    bool isInRange(const Point &point);

    bool isInAngle(const Point &point);

private:
    const Point startPoint;
    const Point endPoint;
    const int accuracy;
    int raySquare;
    double upperAngle;
    double lowerAngle;

    int distanceSquare(const Point &point, const Point &point1);
};

#endif //ZPR_CAMERA_H

//
// Created by Aleksander on 23.12.2016.
//

#define _USE_MATH_DEFINES
#include <cstdlib>
#include <cmath>
#include "Camera.h"

Camera::Camera(const Point &startPoint, const Point &endPoint, double angle, int accuracy) :
        startPoint(startPoint), endPoint(endPoint), accuracy(accuracy){
    double mainAngle = atan2(endPoint.getY() - startPoint.getY(), endPoint.getX() - startPoint.getX());
    double halfAngle = M_PI * angle / 360;
    upperAngle = mainAngle + halfAngle;
    lowerAngle = mainAngle - halfAngle;
    raySquare = distanceSquare(startPoint, endPoint);

}

bool Camera::isInRange(const Point &point) {
    int pointDistanceSquare = distanceSquare(startPoint, point);
    return pointDistanceSquare <= raySquare;
}

int Camera::distanceSquare(const Point &point, const Point &point1) {
    int absX = abs(point.getX() - point1.getX());
    int absY = abs(point.getY() - point1.getY());
    return absX * absX + absY * absY;
}

bool Camera::isInAngle(const Point &point) {
    if(point == startPoint)
        return true;
    else{
        double angle = atan2(point.getY() - startPoint.getY(), point.getX() - startPoint.getX());
        return angle >= lowerAngle && angle <= upperAngle;
    }
}

void Camera::addSeenCar(PtrConstCar car) {
    seenCars.push_back(car);
}

const std::vector<PtrConstCar> &Camera::getSeenCars() const {
    return seenCars;
}

const Point &Camera::getStartPoint() const {
    return startPoint;
}

void Camera::addSeenHuman(PtrConstHuman human) {
    seenHumans.push_back(human);
}

const std::vector<PtrConstHuman> &Camera::getSeenHumans() const {
    return seenHumans;
}

void Camera::clearSeenMovables() {
    seenHumans.clear();
    seenCars.clear();
}


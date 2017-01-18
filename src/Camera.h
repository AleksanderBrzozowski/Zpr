//
// Created by Aleksander on 23.12.2016.
//

#ifndef ZPR_CAMERA_H
#define ZPR_CAMERA_H


#include "Point.h"
#include "Types.h"
#include <vector>

/*!
 * This class represents Camera as point, angle and ray.
 * Camera stores seen cars and humans.
 * @author Aleksander Brzozowski
 */
class Camera {
public:
    /*!
     * Constructs camera.
     * @param startPoint    Point where camera stands
     * @param endPoint
     * @param angle         Visible angle
     * @param accuracy      Camera's accuracy, higher accuracy generates preciser visible points
     */
    Camera(const Point &startPoint, const Point &endPoint, double angle, int accuracy);

    /*!
     * Checks whether a point is in camera's range.
     * @param point Checked point
     * @return      Is in camera range
     */
    bool isInRange(const Point &point);
    /*!
     * Checks whether a point is in camera's angle.
     * @param point Checked point
     * @return      Is in camera angle
     */
    bool isInAngle(const Point &point);

    /*!
     * Adds car to camera's seen cars.
     * @param car Car to be added
     */
    void addSeenCar(PtrConstCar car);
    const std::vector<PtrConstCar> &getSeenCars() const;
    /*!
     * Adds human to camera's seen humans.
     * @param human Human to be added
     */
    void addSeenHuman(PtrConstHuman human);
    const std::vector<PtrConstHuman> &getSeenHumans() const;

    const Point &getStartPoint() const;
    /*!
     * Clears all seen cars and humans by camera.
     */
    void clearSeenMovables();
private:
    const Point startPoint;
    const Point endPoint;
    const int accuracy;
    int raySquare;
    double upperAngle;
    double lowerAngle;

    std::vector<PtrConstCar> seenCars;
    std::vector<PtrConstHuman> seenHumans;

    int distanceSquare(const Point &point, const Point &point1);
};

#endif //ZPR_CAMERA_H

#ifndef ZPR_FACILITIES_H
#define ZPR_FACILITIES_H


#include <vector>
#include "Types.h"
#include "Camera.h"
#include "Building.h"
#include "Movable.h"

/*!
 * Class stores buildings and cameras. Provides operations to add building, camera and scan cameras.
 * @author Aleksander Brzozowski
 */
class Facilities {
public:
    /*!
     * Empty constructor
     */
    Facilities();

    /*!
     * Adds Building represented by arguments of function.
     * @param upperLeft     Point in the upper left of building
     * @param lowerRight    Point in the lower right of building
     * @return              Created and added building
     */
    PtrBuilding addBuilding(const Point &upperLeft, const Point &lowerRight);
    /*!
     * Adds Camera represented by arguments of function.
     * @param startPoint    Camera's start point
     * @param endPoint      Camera's end point
     * @param angle         Camera's angle
     * @param accuracy      Camera's accuracy
     * @return              Created and added camera
     */
    PtrCamera addCamera(const Point &startPoint, const Point &endPoint, double angle, int accuracy);
    /*!
     * Invokes scan on cameras using passed humans and cars.
     * @param cars      Possible visible cars for cameras
     * @param humans    Possible visible humans for cameras
     */
    void scan(const std::vector<PtrConstCar> &cars, const std::vector<PtrConstHuman> &humans);
    const std::vector<PtrCamera> &getCameras() const;
    const std::vector<PtrBuilding> &getBuildings() const;

private:
    std::vector<PtrBuilding> buildings;
    std::vector<PtrCamera> cameras;

    bool isMovableSeenByCamera(PtrCamera &camera, const Point &movablePoint) const;

    bool isMovableHiddenByBuilding(PtrCamera &camera, const Point &movablePoint);

    bool isMovableSeen(const Point &carPoint, PtrCamera &camera);
};


#endif //ZPR_FACILITIES_H

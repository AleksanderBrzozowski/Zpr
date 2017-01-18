#ifndef ZPR_MOVABLE2_H
#define ZPR_MOVABLE2_H


#include "Route.h"
#include "CarRoute.h"
#include "HumanRoute.h"
#include "Types.h"

/*!
 * Represents object that can move.
 * @author Aleksander Brzozowski
 */
class Movable {
public:
    /*!
     * Moves movable.
     * @return whether movable was moved
     */
    bool move();
    Point getActualPoint() const;
    unsigned int getId() const;
    bool isFast() const;

protected:
    Movable(Route *route, const Point &actualPoint, const int speed, const unsigned int id);

private:
    std::unique_ptr<Route> route;
    Point actualPoint;
    const int speed;
    RouteVector routeVector;
    const unsigned int id;
};

/*!
 * Represents car.
 * @author Aleksander Brzozowski
 */
class Car : public Movable{
private:
    Car(CarRoute *route, const Point &actualPoint, const int speed, const unsigned int id);

public:
    /*!
     * Constructs Car.
     * @param startPoint    Point in which car will start
     * @param points        Points to follow by car
     * @param speed         Car's speed
     * @param id            Car's id
     * @return              Created car
     */
    static PtrCar createCar(const Point &startPoint, const std::vector<PtrToConstPoint> &points, const int speed,
                            const unsigned int id);
};

/*!
 * Represents human.
 * @author Aleksander Brzozowski
 */
class Human : public Movable{
private:
    Human(HumanRoute *route, const Point &actualPoint, const int speed, const unsigned int id);

public:
    /*!
    * Constructs Human.
    * @param startPoint    Point in which human will start
    * @param points        Points to follow by human
    * @param speed         Human's speed
    * @param id            Human's id
    * @return              Created human
    */
    static PtrHuman createHuman(const Point &startPoint, const std::vector<PtrToConstPoint> &points, const int speed,
                         const unsigned int id);
};



#endif //ZPR_MOVABLE2_H

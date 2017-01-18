#ifndef ZPR_CARROUTE_H
#define ZPR_CARROUTE_H


#include <stack>
#include <vector>
#include "Route.h"
#include "Types.h"

/*!
 * Represents route for car.
 * @author Aleksander Brzozowski
 */
class CarRoute : public Route {
public:
    /*!
    * Constructs HumanRoute.
    * @param points Points to fallow by route
    */
    CarRoute(const std::vector<PtrToConstPoint> &points);
    virtual ~CarRoute();

    bool nextPoint() override;
    bool isEnd() override;
private:
    std::stack<PtrToConstPoint> points;

    const Point &getActualPoint() const override;
};


#endif //ZPR_CARROUTE_H

#ifndef ZPR_HUMANROUTE_H
#define ZPR_HUMANROUTE_H


#include <vector>
#include "Route.h"
#include "Types.h"

/*!
 * Represents route for Human.
 * @author Aleksander Brzozowski
 */
class HumanRoute : public Route{
public:
    /*!
     * Constructs HumanRoute.
     * @param points Points to fallow by route.
     */
    HumanRoute(const std::vector<PtrToConstPoint> &points);
    virtual ~HumanRoute();

    bool nextPoint() override;
    bool isEnd() override;
private:
    const std::vector<PtrToConstPoint> points;
    std::vector<PtrToConstPoint>::const_iterator pointsIterator;

    const Point &getActualPoint() const override;
};


#endif //ZPR_HUMANROUTE_H

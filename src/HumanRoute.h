//
// Created by Aleksander on 12.12.2016.
//

#ifndef ZPR_HUMANROUTE_H
#define ZPR_HUMANROUTE_H


#include <vector>
#include "Route.h"
#include "Types.h"

class HumanRoute : public Route{
public:
    HumanRoute(const std::vector<PtrToConstPoint> &points);
    virtual ~HumanRoute();

    bool nextPoint() override;
    bool isEnd() override;
private:
    const std::vector<PtrToConstPoint>& points;
    std::vector<PtrToConstPoint>::const_iterator pointsIterator;

    const Point &getActualPoint() const override;
};


#endif //ZPR_HUMANROUTE_H

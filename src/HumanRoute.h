//
// Created by Aleksander on 12.12.2016.
//

#ifndef ZPR_HUMANROUTE_H
#define ZPR_HUMANROUTE_H


#include <memory>
#include <vector>
#include "Route2.h"
#include "exception"
#include <cstdlib>

class HumanRoute : public Route2{
public:
    HumanRoute(const std::vector<std::shared_ptr<Point const>> &points);
    virtual ~HumanRoute();

    bool nextPoint() override;
    bool isEnd() override;
private:
    const std::vector<std::shared_ptr<Point const>>& points;
    std::vector<std::shared_ptr<Point const>>::const_iterator pointsIterator;

    const Point &getActualPoint() const override;
};


#endif //ZPR_HUMANROUTE_H

//
// Created by Aleksander on 12.12.2016.
//

#ifndef ZPR_CARROUTE_H
#define ZPR_CARROUTE_H


#include <stack>
#include <memory>
#include <cstdlib>
#include <vector>
#include "Route2.h"
#include "Types.h"

class CarRoute : public Route2 {
public:
    CarRoute(const std::vector<PtrToConstPoint> &points);
    virtual ~CarRoute();

    bool nextPoint() override;
    bool isEnd() override;
private:
    std::stack<PtrToConstPoint> points;

    const Point &getActualPoint() const override;
};


#endif //ZPR_CARROUTE_H

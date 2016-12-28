//
// Created by kuco on 13.12.16.
//

#ifndef ZPR_CROSSFACTORY_H
#define ZPR_CROSSFACTORY_H


#include "Point.h"
#include "Cross.h"
#include "Types.h"

class CrossFactory {

private:
    static std::vector<PtrCross>::size_type findCrossIndex(PtrToConstPoint, const std::vector<PtrCross>&);

public:
    static void createRoute(PtrToConstPoint, PtrToConstPoint, std::vector<PtrCross>&);

};


#endif //ZPR_CROSSFACTORY_H

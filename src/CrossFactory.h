//
// Created by kuco on 13.12.16.
//

#ifndef ZPR_CROSSFACTORY_H
#define ZPR_CROSSFACTORY_H


#include "Point.h"
#include "Cross.h"

class CrossFactory {
private:
    static int findCrossIndex(Point*, const std::vector<Cross*>&);

public:
    static void createRoute(Point*, Point*, std::vector<Cross*>&);
};


#endif //ZPR_CROSSFACTORY_H

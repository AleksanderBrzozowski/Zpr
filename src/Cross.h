//
// Created by kuco on 02.11.16.
//

#ifndef ZPR_CROSS_H
#define ZPR_CROSS_H

#include <vector>
#include "Point.h"
#include "Types.h"

class Cross {

private:

    PtrCross northNeighbour;
    PtrCross westNeighbour;
    PtrCross eastNeighbour;
    PtrCross southNeighbour;
    bool visited;
    PtrToConstPoint position;

public:

    Cross(PtrToConstPoint);
    PtrCross getNotVisitedNeighbours() const;
    void addNeighbour(PtrCross);
    bool setVisited(const bool&);
    bool getVisited() const;
    PtrToConstPoint getPosition() const ;

    PtrCross getNorthNeighbour() const;
    PtrCross getSouthNeighbour() const;
    PtrCross getEastNeighbour() const;
    PtrCross getWestNeighbour() const;

    bool operator==(const Cross &rhs) const;
    bool operator!=(const Cross &rhs) const;

};


#endif //ZPR_CROSS_H

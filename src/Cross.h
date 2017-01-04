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
    std::vector<PtrCross>neighbours;
    bool visited;
    PtrToConstPoint position;

public:

    Cross(PtrToConstPoint);
    PtrCross getNotVisitedNeighbours();
    void addNeighbour(PtrCross);
    bool setVisited(const bool&);
    bool getVisited() const;
    PtrToConstPoint getPosition() const ;

    bool operator==(const Cross &rhs) const;
    bool operator!=(const Cross &rhs) const;

};


#endif //ZPR_CROSS_H

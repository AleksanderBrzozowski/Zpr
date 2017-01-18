/**
 * @file Cross.h
 * @Author PiotrKuc (piotr.kuc29@gmail.com)
 * @date November, 2017
 * @brief Cross class methods declaration
 *
 */

#ifndef ZPR_CROSS_H
#define ZPR_CROSS_H

#include <vector>
#include "Point.h"
#include "Types.h"

/**
 * @class Cross class
 * @brief Cross represents vertices in the graph that describes map.
 * @details Each cross has it's neighbours and parameter that says if it was already used
 * by the finding route algorithm and shouldn't be used again.
 */

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

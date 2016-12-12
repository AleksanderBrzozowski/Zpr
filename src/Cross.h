//
// Created by kuco on 02.11.16.
//

#ifndef ZPR_CROSS_H
#define ZPR_CROSS_H

#include <vector>
#include "Point.h"

class Cross {

    const unsigned int id;
    std::vector<std::pair<Cross*, Point*> >neighbours;
    bool visited;
    Point* position;

public:
    Cross(const unsigned int&, Point*);
    std::pair<Cross*, Point*>* getNotVisitedNeighbours();
    void createNeighbourhood(const std::vector<std::pair<Cross*, Point*>>&);
    bool setVisited(const bool&);
    bool getVisited() const;
    unsigned int getId() const;
    Point* getPosition() const ;
};


#endif //ZPR_CROSS_H

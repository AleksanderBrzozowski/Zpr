//
// Created by kuco on 13.12.16.
//

#include "CrossFactory.h"



void CrossFactory::createRoute(Point * begin, Point * end,  std::vector<Cross*>&crosses) {

    int tempCross1Index = findCrossIndex(begin, crosses);
    int tempCross2Index = findCrossIndex(end, crosses);

    if(tempCross1Index<0 && tempCross2Index<0){
        Cross* newCross1 = new Cross((int)crosses.size(), begin);
        Cross* newCross2 = new Cross((int)crosses.size(), end);
        newCross1->addNeighbour(newCross2);
        newCross2->addNeighbour(newCross1);
        crosses.push_back(newCross1);
        crosses.push_back(newCross2);
    }

    else if(tempCross1Index<0 && tempCross2Index>=0){
        Cross* newCross = new Cross((int)crosses.size(), begin);
        crosses[tempCross2Index]->addNeighbour(newCross);
        crosses[tempCross1Index]->addNeighbour(crosses[tempCross2Index]);
        crosses.push_back(newCross);
        delete end;
    }


    else if(tempCross2Index<0 && tempCross1Index>=0) {
        Cross *newCross = new Cross((int) crosses.size(), end);
        crosses[tempCross1Index]->addNeighbour(newCross);
        crosses[tempCross2Index]->addNeighbour(crosses[tempCross1Index]);
        crosses.push_back(newCross);
        delete begin;
    }
}

int CrossFactory::findCrossIndex(Point * point, const std::vector<Cross*>& crosses) {

    for(int i =0;i<(int)crosses.size();++i){
        if(crosses[i]->getPosition() == point){
            return i;
        }
    }
    return -1;
}
//
// Created by kuco on 13.12.16.
//

#include "CrossFactory.h"


void CrossFactory::createRoute(PtrToConstPoint begin, PtrToConstPoint end,  std::vector<PtrCross>&crosses) {

    std::vector<PtrCross>::size_type tempCross1Index = findCrossIndex(begin, crosses);
    std::vector<PtrCross>::size_type tempCross2Index = findCrossIndex(end  , crosses);

    if(tempCross1Index>=crosses.size() && tempCross2Index>=crosses.size()){
        PtrCross newCross1 = std::make_shared<Cross>(begin);
        PtrCross newCross2 = std::make_shared<Cross>(end);
        newCross1->addNeighbour(newCross2);
        newCross2->addNeighbour(newCross1);
        crosses.push_back(newCross1);
        crosses.push_back(newCross2);
    }

    else if(tempCross1Index>=crosses.size() && tempCross2Index<crosses.size()){
        PtrCross newCross = std::make_shared<Cross>(begin);
        crosses[tempCross2Index]->addNeighbour(newCross);
        newCross->addNeighbour(crosses[tempCross2Index]);
        crosses.push_back(newCross);
    }


    else if(tempCross2Index>=crosses.size() && tempCross1Index<crosses.size()) {
        PtrCross newCross = std::make_shared<Cross>(end);
        crosses[tempCross1Index]->addNeighbour(newCross);
        newCross->addNeighbour(crosses[tempCross1Index]);
        crosses.push_back(newCross);
    }
    else{
        crosses[tempCross2Index]->addNeighbour(crosses[tempCross1Index]);
        crosses[tempCross1Index]->addNeighbour(crosses[tempCross2Index]);
    }
}

std::vector<PtrCross>::size_type CrossFactory::findCrossIndex(PtrToConstPoint point, const std::vector<PtrCross>& crosses) {

    for(std::vector<PtrCross>::size_type i = 0; i<crosses.size(); ++i ){
        if(*(crosses[i]->getPosition()) == *point){
            return i;
        }
    }
    return crosses.size();
}
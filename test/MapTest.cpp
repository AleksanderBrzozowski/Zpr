//
// Created by kuco on 16.01.17.
//

#include <include/gtest/gtest.h>
#include <Map.h>

class MapTest : public ::testing::Test{

public:
    Map map;
    void createRoad(){
        map.createRoad(std::make_shared<Point>(0,0), std::make_shared<Point>(10,0));
    };
    void createCar(){
        map.createCar(std::make_shared<Point>(0,0), std::make_shared<Point>(10,0), 10);
    }

};

TEST_F(MapTest, newRoadFromMap){
    createRoad();
}

TEST_F(MapTest, newCarFromMap){
    createRoad();
    createCar();
}


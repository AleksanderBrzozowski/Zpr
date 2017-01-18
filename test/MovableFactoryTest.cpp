//
// Created by kuco on 13.01.17.
//


#include<gtest/gtest.h>
#include <Cross.h>
#include <MovableFactory.h>
#include <CrossFactory.h>

class MovableFactoryTest : public ::testing::Test{

public:

    MovableFactory movableFactory;
    CrossFactory crossFactory;

    void createCrosses(){
        crossFactory.createRoad(std::make_shared<Point>(-10,-10), std::make_shared<Point>(-10,0));
        crossFactory.createRoad(std::make_shared<Point>(0,-10), std::make_shared<Point>(0,0));
        crossFactory.createRoad(std::make_shared<Point>(0,0), std::make_shared<Point>(-10,0));
        crossFactory.createRoad(std::make_shared<Point>(0,0), std::make_shared<Point>(10,0));
        crossFactory.createRoad(std::make_shared<Point>(10,10), std::make_shared<Point>(10,0));
        crossFactory.createRoad(std::make_shared<Point>(0,10), std::make_shared<Point>(0,0));
        crossFactory.createRoad(std::make_shared<Point>(0,10), std::make_shared<Point>(10,10));
    }

};

TEST_F(MovableFactoryTest, checkLongRouteFindingBegin){
    createCrosses();
    std::vector<PtrToConstPoint>route;
    PtrToConstPoint point1 = std::make_shared<Point>(-10,0);
    PtrToConstPoint point2 = std::make_shared<Point>(10,15);
    movableFactory.findRoute(point1, point2, route, crossFactory.getCrosses());
    EXPECT_TRUE(route.empty());
}


TEST_F(MovableFactoryTest, creatingMovableWithoutCrosses){

    movableFactory.createCar(std::make_shared<Point>(0,-10), std::make_shared<Point>(0,0), 10, crossFactory.getCrosses());
}

TEST_F(MovableFactoryTest, creatingMovableShortRoute){
    createCrosses();
    movableFactory.createCar(std::make_shared<Point>(0,-10), std::make_shared<Point>(0,0), 10, crossFactory.getCrosses());
}

TEST_F(MovableFactoryTest, creatingMovableMidRoute){
    createCrosses();
    movableFactory.createCar(std::make_shared<Point>(0,-10), std::make_shared<Point>(0,20), 10, crossFactory.getCrosses());
}

TEST_F(MovableFactoryTest, creatingMovableLongRoute){
    createCrosses();
    movableFactory.createCar(std::make_shared<Point>(-10,0), std::make_shared<Point>(10,15), 10, crossFactory.getCrosses());
}

TEST_F(MovableFactoryTest, checkRouteFindingBegin){
    createCrosses();
    std::vector<PtrToConstPoint>route;
    PtrToConstPoint point1 = std::make_shared<Point>(0,-10);
    PtrToConstPoint point2 = std::make_shared<Point>(-10,-10);
    movableFactory.findRoute(point1, point2, route, crossFactory.getCrosses());
    EXPECT_TRUE(*route[0] == *point1);
}

TEST_F(MovableFactoryTest, checkRouteFindingEnd){
    createCrosses();
    std::vector<PtrToConstPoint>route;
    PtrToConstPoint point1 = std::make_shared<Point>(0,-10);
    PtrToConstPoint point2 = std::make_shared<Point>(-10,-10);
    movableFactory.findRoute(point1, point2, route, crossFactory.getCrosses());
    EXPECT_TRUE(*route[route.size()-1] == *point2);
    EXPECT_TRUE(*route[0] == *point1);
}

TEST_F(MovableFactoryTest, checkRouteFinding4Points){
    createCrosses();
    std::vector<PtrToConstPoint>route;
    PtrToConstPoint point1 = std::make_shared<Point>(0,-10);
    PtrToConstPoint point2 = std::make_shared<Point>(-10,-10);
    movableFactory.findRoute(point1, point2, route, crossFactory.getCrosses());
    EXPECT_TRUE(*route[route.size()-1] == *point2);
    EXPECT_TRUE(*route[0] == *point1);
}

TEST_F(MovableFactoryTest, checkRouteFinding5Points){
    createCrosses();
    std::vector<PtrToConstPoint>route;
    PtrToConstPoint point1 = std::make_shared<Point>(0,-10);
    PtrToConstPoint point2 = std::make_shared<Point>(10,10);
    movableFactory.findRoute(point1, point2, route, crossFactory.getCrosses());
    EXPECT_TRUE(*route[route.size()-1] == *point2);
    EXPECT_TRUE(*route[0] == *point1);
}

TEST_F(MovableFactoryTest, checkRouteFinding2Points){
    crossFactory.createRoad(std::make_shared<Point>(91,221), std::make_shared<Point>(663,221));
    std::vector<PtrToConstPoint>route;
    PtrToConstPoint point1 = std::make_shared<Point>(91,221);
    PtrToConstPoint point2 = std::make_shared<Point>(663,221);
    movableFactory.findRoute(point2, point1, route, crossFactory.getCrosses());
    EXPECT_EQ(route.size(), 2);
}

TEST_F(MovableFactoryTest, findingNoNearestCross){
    createCrosses();
    PtrCross foundCross = movableFactory.findNearestCross(std::make_shared<Point>(91,221), crossFactory.getCrosses());
    EXPECT_EQ(foundCross, nullptr);
}

TEST_F(MovableFactoryTest, findingNearestCross){
    createCrosses();
    PtrToConstPoint point = std::make_shared<Point>(-10,-5);
    PtrToConstPoint crossPos2 = std::make_shared<Point>(-10,-10);
    PtrToConstPoint crossPos1 = std::make_shared<Point>(-10,-0);
    PtrCross foundCross = movableFactory.findNearestCross(point, crossFactory.getCrosses());
    EXPECT_TRUE(*foundCross->getPosition() == *crossPos1 || *foundCross->getPosition() == *crossPos2);
}

TEST_F(MovableFactoryTest, checkPointMeetsCross){
    createCrosses();
    PtrToConstPoint point = std::make_shared<Point>(5,0);
    PtrToConstPoint crossPoint = std::make_shared<Point>(10,0);
    EXPECT_TRUE(movableFactory.pointMeetsCross(point,movableFactory.findNearestCross(crossPoint, crossFactory.getCrosses())));
}

TEST_F(MovableFactoryTest, checkRouteFindingRandom2Points){
    crossFactory.createRoad(std::make_shared<Point>(91,221), std::make_shared<Point>(663,221));
    std::vector<PtrToConstPoint>route;
    PtrToConstPoint point1 = std::make_shared<Point>(500,221);
    PtrToConstPoint point2 = std::make_shared<Point>(600,221);
    movableFactory.findRoute(point1, point2, route, crossFactory.getCrosses());
    EXPECT_EQ(route[0]->getX(), 500);
    EXPECT_EQ(route[route.size()-1]->getX(), 600);
}

TEST_F(MovableFactoryTest, checkRouteFindingRandomPointsRectangle){
    crossFactory.createRoad(std::make_shared<Point>(0,0), std::make_shared<Point>(10,0));
    crossFactory.createRoad(std::make_shared<Point>(0,10), std::make_shared<Point>(10,10));
    crossFactory.createRoad(std::make_shared<Point>(0,0), std::make_shared<Point>(0,10));
    crossFactory.createRoad(std::make_shared<Point>(10,10), std::make_shared<Point>(10,0));
    std::vector<PtrToConstPoint>route;
    PtrToConstPoint point1 = std::make_shared<Point>(5,10);
    PtrToConstPoint point2 = std::make_shared<Point>(3,0);
    movableFactory.findRoute(point1, point2, route, crossFactory.getCrosses());
    EXPECT_EQ(route[0]->getX(), 5);
    EXPECT_EQ(route[0]->getY(), 10);
    EXPECT_EQ(route[route.size()-1]->getX(), 3);
    EXPECT_EQ(route[route.size()-1]->getY(), 0);
}


TEST_F(MovableFactoryTest, checkRouteFindingRandomPointsBigMap){
    createCrosses();
    std::vector<PtrToConstPoint>route;
    PtrToConstPoint point1 = std::make_shared<Point>(-10,-5);
    PtrToConstPoint point2 = std::make_shared<Point>(10,2);
    movableFactory.findRoute(point1, point2, route, crossFactory.getCrosses());
    EXPECT_EQ(route[0]->getX(), -10);
    EXPECT_EQ(route[0]->getY(), -5);
    EXPECT_EQ(route[route.size()-1]->getX(), 10);
    EXPECT_EQ(route[route.size()-1]->getY(), 2);
}

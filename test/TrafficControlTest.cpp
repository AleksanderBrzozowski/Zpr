//
// Created by kuco on 14.12.16.
//

#include<gtest/gtest.h>
#include <Cross.h>
#include <TrafficControl.h>

class TrafficControlTest : public ::testing::Test{

public:

    TrafficControlTest(){
        trafficControl=new TrafficControl();
    };
    TrafficControl* trafficControl;

    void createCrosses(){
        trafficControl->createRoute(std::make_shared<Point>(-10,-10), std::make_shared<Point>(-10,0));
        trafficControl->createRoute(std::make_shared<Point>(0,-10), std::make_shared<Point>(0,0));
        trafficControl->createRoute(std::make_shared<Point>(0,0), std::make_shared<Point>(-10,0));
        trafficControl->createRoute(std::make_shared<Point>(0,0), std::make_shared<Point>(10,0));
        trafficControl->createRoute(std::make_shared<Point>(10,10), std::make_shared<Point>(10,0));
        trafficControl->createRoute(std::make_shared<Point>(0,10), std::make_shared<Point>(0,0));
        trafficControl->createRoute(std::make_shared<Point>(0,10), std::make_shared<Point>(10,10));
    }

    ~TrafficControlTest(){
        delete trafficControl;
    }

};

TEST_F(TrafficControlTest, checkLongRouteFindingBegin){
    createCrosses();
    std::vector<PtrToConstPoint>route;
    PtrToConstPoint point1 = std::make_shared<Point>(-10,0);
    PtrToConstPoint point2 = std::make_shared<Point>(10,15);
    trafficControl->findRoute(point1, point2, route);
    EXPECT_TRUE(route.empty());
}


TEST_F(TrafficControlTest, creatingMovableWithoutCrosses){

    trafficControl->createNewCar(std::make_shared<Point>(0,-10), std::make_shared<Point>(0,0), 10);
}

TEST_F(TrafficControlTest, creatingMovableShortRoute){
    createCrosses();
    trafficControl->createNewCar(std::make_shared<Point>(0,-10), std::make_shared<Point>(0,0), 10);
}

TEST_F(TrafficControlTest, creatingMovableMidRoute){
    createCrosses();
    trafficControl->createNewCar(std::make_shared<Point>(0,-10), std::make_shared<Point>(0,20), 10);
}

TEST_F(TrafficControlTest, creatingMovableLongRoute){
    createCrosses();
    trafficControl->createNewCar(std::make_shared<Point>(-10,0), std::make_shared<Point>(10,15), 10);
}

TEST_F(TrafficControlTest, checkRouteFindingBegin){
    createCrosses();
    std::vector<PtrToConstPoint>route;
    PtrToConstPoint point1 = std::make_shared<Point>(0,-10);
    PtrToConstPoint point2 = std::make_shared<Point>(-10,-10);
    trafficControl->findRoute(point1, point2, route);
    EXPECT_TRUE(*route[0] == *point1);
}

TEST_F(TrafficControlTest, checkRouteFindingEnd){
    createCrosses();
    std::vector<PtrToConstPoint>route;
    PtrToConstPoint point1 = std::make_shared<Point>(0,-10);
    PtrToConstPoint point2 = std::make_shared<Point>(-10,-10);
    trafficControl->findRoute(point1, point2, route);
    EXPECT_TRUE(*route[3] == *point2);
}

TEST_F(TrafficControlTest, checkRouteFinding4Points){
    createCrosses();
    std::vector<PtrToConstPoint>route;
    PtrToConstPoint point1 = std::make_shared<Point>(0,-10);
    PtrToConstPoint point2 = std::make_shared<Point>(-10,-10);
    trafficControl->findRoute(point1, point2, route);
    EXPECT_EQ(route.size(), 4);
}

TEST_F(TrafficControlTest, checkRouteFinding5Points){
    createCrosses();
    std::vector<PtrToConstPoint>route;
    PtrToConstPoint point1 = std::make_shared<Point>(0,-10);
    PtrToConstPoint point2 = std::make_shared<Point>(10,10);
    trafficControl->findRoute(point1, point2, route);
    EXPECT_EQ(route.size(), 4);
}

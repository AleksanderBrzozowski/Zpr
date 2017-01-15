//
// Created by kuco on 14.12.16.
//

#include<gtest/gtest.h>
#include <Cross.h>
#include <TrafficControl.h>

class TrafficControlTest : public ::testing::Test{

public:

    TrafficControlTest(){
        cf = new CrossFactory();
        trafficControl=new TrafficControl(cf, cf->getCrosses());
    };
    TrafficControl* trafficControl;
    CrossFactory* cf;

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
    PtrToConstPoint point2 = std::make_shared<Point>(100,15);
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
    EXPECT_TRUE(*route[route.size()-1] == *point2);
    EXPECT_TRUE(*route[0] == *point1);
}

TEST_F(TrafficControlTest, checkRouteFinding4Points){
    createCrosses();
    std::vector<PtrToConstPoint>route;
    PtrToConstPoint point1 = std::make_shared<Point>(0,-10);
    PtrToConstPoint point2 = std::make_shared<Point>(-10,-10);
    trafficControl->findRoute(point1, point2, route);
    EXPECT_TRUE(*route[route.size()-1] == *point2);
    EXPECT_TRUE(*route[0] == *point1);
}

TEST_F(TrafficControlTest, checkRouteFinding5Points){
    createCrosses();
    std::vector<PtrToConstPoint>route;
    PtrToConstPoint point1 = std::make_shared<Point>(0,-10);
    PtrToConstPoint point2 = std::make_shared<Point>(10,10);
    trafficControl->findRoute(point1, point2, route);
    EXPECT_TRUE(*route[route.size()-1] == *point2);
    EXPECT_TRUE(*route[0] == *point1);
}

TEST_F(TrafficControlTest, checkRouteFinding2Points){
    trafficControl->createRoute(std::make_shared<Point>(91,221), std::make_shared<Point>(663,221));
    std::vector<PtrToConstPoint>route;
    PtrToConstPoint point1 = std::make_shared<Point>(91,221);
    PtrToConstPoint point2 = std::make_shared<Point>(663,221);
    trafficControl->findRoute(point2, point1, route);
    EXPECT_EQ(route.size(), 2);
}

TEST_F(TrafficControlTest, findingNoNearestCross){
    createCrosses();
    PtrCross foundCross = trafficControl->findNearestCross(std::make_shared<Point>(91,221));
    EXPECT_EQ(foundCross, nullptr);
}

TEST_F(TrafficControlTest, findingNearestCross){
    createCrosses();
    PtrToConstPoint point = std::make_shared<Point>(-10,-5);
    PtrToConstPoint crossPos2 = std::make_shared<Point>(-10,-10);
    PtrToConstPoint crossPos1 = std::make_shared<Point>(-10,-0);
    PtrCross foundCross = trafficControl->findNearestCross(point);
    EXPECT_TRUE(*foundCross->getPosition() == *crossPos1 || *foundCross->getPosition() == *crossPos2);
}

TEST_F(TrafficControlTest, checkPointMeetsCross){
    createCrosses();
    PtrToConstPoint point = std::make_shared<Point>(5,0);
    PtrToConstPoint crossPoint = std::make_shared<Point>(10,0);
    EXPECT_TRUE(trafficControl->checkPointMeetsCross(point,trafficControl->findNearestCross(crossPoint)));
}

TEST_F(TrafficControlTest, checkRouteFindingRandom2Points){
    trafficControl->createRoute(std::make_shared<Point>(91,221), std::make_shared<Point>(663,221));
    std::vector<PtrToConstPoint>route;
    PtrToConstPoint point1 = std::make_shared<Point>(500,221);
    PtrToConstPoint point2 = std::make_shared<Point>(600,221);
    trafficControl->findRoute(point1, point2, route);
    EXPECT_EQ(route[0]->getX(), 500);
    EXPECT_EQ(route[route.size()-1]->getX(), 600);
}

TEST_F(TrafficControlTest, checkRouteFindingRandomPointsRectangle){
    trafficControl->createRoute(std::make_shared<Point>(0,0), std::make_shared<Point>(10,0));
    trafficControl->createRoute(std::make_shared<Point>(0,10), std::make_shared<Point>(10,10));
    trafficControl->createRoute(std::make_shared<Point>(0,0), std::make_shared<Point>(0,10));
    trafficControl->createRoute(std::make_shared<Point>(10,10), std::make_shared<Point>(10,0));
    std::vector<PtrToConstPoint>route;
    PtrToConstPoint point1 = std::make_shared<Point>(5,10);
    PtrToConstPoint point2 = std::make_shared<Point>(3,0);
    trafficControl->findRoute(point1, point2, route);
    EXPECT_EQ(route[0]->getX(), 5);
    EXPECT_EQ(route[0]->getY(), 10);
    EXPECT_EQ(route[route.size()-1]->getX(), 3);
    EXPECT_EQ(route[route.size()-1]->getY(), 0);
}


TEST_F(TrafficControlTest, checkRouteFindingRandomPointsBigMap){
    createCrosses();
    std::vector<PtrToConstPoint>route;
    PtrToConstPoint point1 = std::make_shared<Point>(-10,-5);
    PtrToConstPoint point2 = std::make_shared<Point>(10,2);
    trafficControl->findRoute(point1, point2, route);
    EXPECT_EQ(route[0]->getX(), -10);
    EXPECT_EQ(route[0]->getY(), -5);
    EXPECT_EQ(route[route.size()-1]->getX(), 10);
    EXPECT_EQ(route[route.size()-1]->getY(), 2);
}

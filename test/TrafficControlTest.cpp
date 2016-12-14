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
        trafficControl->createRoute(new Point(-10,-10), new Point(-10,0));
        trafficControl->createRoute(new Point(0,-10), new Point(0,0));
        trafficControl->createRoute(new Point(0,0), new Point(-10,0));
        trafficControl->createRoute(new Point(0,0), new Point(10,0));
        trafficControl->createRoute(new Point(10,10), new Point(10,0));
        trafficControl->createRoute(new Point(0,10), new Point(0,0));
        trafficControl->createRoute(new Point(0,10), new Point(10,10));
    }

    ~TrafficControlTest(){
        delete trafficControl;
    }

};

TEST_F(TrafficControlTest, checkLongRouteFindingBegin){
    createCrosses();
    std::vector<Point*>route;
    Point* point1 = new Point(-10,0);
    Point* point2 = new Point(10,15);
    trafficControl->findRoute(point1, point2, route);
    EXPECT_TRUE(route.empty());
}


TEST_F(TrafficControlTest, creatingMovableWithoutCrosses){

    trafficControl->createNewMovable(new Point(0,-10), new Point(0,0), 10);
}

TEST_F(TrafficControlTest, creatingMovableShortRoute){
    createCrosses();
    trafficControl->createNewMovable(new Point(0,-10), new Point(0,0), 10);
}

TEST_F(TrafficControlTest, creatingMovableMidRoute){
    createCrosses();
    trafficControl->createNewMovable(new Point(0,-10), new Point(0,20), 10);
}

TEST_F(TrafficControlTest, creatingMovableLongRoute){
    createCrosses();
    trafficControl->createNewMovable(new Point(-10,0), new Point(10,15), 10);
}

TEST_F(TrafficControlTest, checkRouteFindingBegin){
    createCrosses();
    std::vector<Point*>route;
    Point* point1 = new Point(0,-10);
    Point* point2 = new Point(-10,-10);
    trafficControl->findRoute(point1, point2, route);
    EXPECT_TRUE(*route[0] == *point1);
}

TEST_F(TrafficControlTest, checkRouteFindingEnd){
    createCrosses();
    std::vector<Point*>route;
    Point* point1 = new Point(0,-10);
    Point* point2 = new Point(-10,-10);
    trafficControl->findRoute(point1, point2, route);
    EXPECT_TRUE(*route[3] == *point2);
}

TEST_F(TrafficControlTest, checkRouteFinding4Points){
    createCrosses();
    std::vector<Point*>route;
    Point* point1 = new Point(0,-10);
    Point* point2 = new Point(-10,-10);
    trafficControl->findRoute(point1, point2, route);
    EXPECT_EQ(route.size(), 4);
}

TEST_F(TrafficControlTest, checkRouteFinding5Points){
    createCrosses();
    std::vector<Point*>route;
    Point* point1 = new Point(0,-10);
    Point* point2 = new Point(10,10);
    trafficControl->findRoute(point1, point2, route);
    EXPECT_EQ(route.size(), 4);
}

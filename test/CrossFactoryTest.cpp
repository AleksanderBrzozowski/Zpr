//
// Created by kuco on 14.12.16.
//

#include <gtest/gtest.h>
#include <Cross.h>
#include <CrossFactory.h>

class CrossFactoryTest : public ::testing::Test{
public:
    CrossFactory crossFactory;

    void createRoute(PtrToConstPoint src, PtrToConstPoint dst){
        crossFactory.createRoad(src, dst);
    }

    void createCrosses(){
        /*Map looks like:
         * |_|_
         *   |_|
        */
        ;
        crossFactory.createRoad(std::make_shared<Point>(-10,-10), std::make_shared<Point>(-10,0));
        crossFactory.createRoad(std::make_shared<Point>(0,-10), std::make_shared<Point>(0,0));
        crossFactory.createRoad(std::make_shared<Point>(0,0), std::make_shared<Point>(-10,0));
        crossFactory.createRoad(std::make_shared<Point>(0,0), std::make_shared<Point>(10,0));
        crossFactory.createRoad(std::make_shared<Point>(10,10), std::make_shared<Point>(10,0));
        crossFactory.createRoad(std::make_shared<Point>(0,10), std::make_shared<Point>(0,0));
        crossFactory.createRoad(std::make_shared<Point>(0,10), std::make_shared<Point>(10,10));
    }

    void createMoreCrosses(){
        /*Map looks like:
         *   _
         *  | |_|_
         *  |___|_|
         *      |_|
         *      |_|
         */
        crossFactory.createRoad(std::make_shared<Point>(-20,-10), std::make_shared<Point>(-10,-10));
        crossFactory.createRoad(std::make_shared<Point>(-20,-10), std::make_shared<Point>(-20,10));
        crossFactory.createRoad(std::make_shared<Point>(0,10), std::make_shared<Point>(-20,10));
        crossFactory.createRoad(std::make_shared<Point>(0,20), std::make_shared<Point>(10,20));
        crossFactory.createRoad(std::make_shared<Point>(0,20), std::make_shared<Point>(0,15));
        crossFactory.createRoad(std::make_shared<Point>(0,10), std::make_shared<Point>(0,15));
        crossFactory.createRoad(std::make_shared<Point>(10,10), std::make_shared<Point>(10,15));
        crossFactory.createRoad(std::make_shared<Point>(10,20), std::make_shared<Point>(10,15));
        crossFactory.createRoad(std::make_shared<Point>(0,15), std::make_shared<Point>(10,15));
    }

    ~CrossFactoryTest(){}
};

TEST_F(CrossFactoryTest, creatingRoute){
    createRoute(std::make_shared<Point>(100,200), std::make_shared<Point>(100,300));
    EXPECT_TRUE(crossFactory.getCrosses().size() == 2);
}

TEST_F(CrossFactoryTest, creatingRoutes){
    createCrosses();
    EXPECT_EQ(crossFactory.getCrosses().size(), 7);
}

TEST_F(CrossFactoryTest, creatingMoreRoutes){
    createCrosses();
    createMoreCrosses();
    EXPECT_EQ(crossFactory.getCrosses().size(), 13);
}


TEST_F(CrossFactoryTest, twoRoadsCrossed){
    crossFactory.createRoad(std::make_shared<Point>(0,0), std::make_shared<Point>(0,10));
    crossFactory.createRoad(std::make_shared<Point>(-5,5), std::make_shared<Point>(5,5));
    EXPECT_EQ(crossFactory.getCrosses().size(), 5);

    crossFactory.createRoad(std::make_shared<Point>(0,0), std::make_shared<Point>(0,10));
    crossFactory.createRoad(std::make_shared<Point>(5,5), std::make_shared<Point>(-5,5));
    EXPECT_EQ(crossFactory.getCrosses().size(), 5);

    crossFactory.createRoad(std::make_shared<Point>(0,0), std::make_shared<Point>(0,0));
    crossFactory.createRoad(std::make_shared<Point>(-5,5), std::make_shared<Point>(5,5));
    EXPECT_EQ(crossFactory.getCrosses().size(), 5);
}

TEST_F(CrossFactoryTest, threeRoadsCrossed){
    crossFactory.createRoad(std::make_shared<Point>(0,0), std::make_shared<Point>(0,10));
    crossFactory.createRoad(std::make_shared<Point>(-5,5), std::make_shared<Point>(5,5));
    crossFactory.createRoad(std::make_shared<Point>(3,0), std::make_shared<Point>(3,10));

    EXPECT_EQ(crossFactory.getCrosses().size(), 8);
}

TEST_F(CrossFactoryTest, fourRoadsCrossed){
    crossFactory.createRoad(std::make_shared<Point>(0,0), std::make_shared<Point>(0,10));
    crossFactory.createRoad(std::make_shared<Point>(-5,5), std::make_shared<Point>(5,5));
    crossFactory.createRoad(std::make_shared<Point>(3,0), std::make_shared<Point>(3,10));
    crossFactory.createRoad(std::make_shared<Point>(-5,7), std::make_shared<Point>(5,7));
    crossFactory.createRoad(std::make_shared<Point>(-5,3), std::make_shared<Point>(5,3));
    crossFactory.createRoad(std::make_shared<Point>(-3,0), std::make_shared<Point>(-3,10));

    EXPECT_EQ(crossFactory.getCrosses().size(), 21);
}


TEST_F(CrossFactoryTest, littleRoads){
    crossFactory.createRoad(std::make_shared<Point>(48,48), std::make_shared<Point>(80,48));
    crossFactory.createRoad(std::make_shared<Point>(16,112), std::make_shared<Point>(80,112));
    crossFactory.createRoad(std::make_shared<Point>(80,16), std::make_shared<Point>(80,144));

    EXPECT_EQ(crossFactory.getCrosses().size(), 6);
}

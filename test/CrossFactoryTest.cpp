//
// Created by kuco on 14.12.16.
//

#include <gtest/gtest.h>
#include <Cross.h>
#include <CrossFactory.h>

class CrossFactoryTest : public ::testing::Test{
public:
    std::vector<Cross*> crosses;
    CrossFactoryTest(){};

    void createRoute(Point* src, Point* dst){
        CrossFactory::createRoute(src, dst, crosses);
    }

    void createCrosses(){
        /*Map looks like:
         * |_|_
         *   |_|
        */
        CrossFactory::createRoute(new Point(-10,-10), new Point(-10,0), crosses);
        CrossFactory::createRoute(new Point(0,-10), new Point(0,0), crosses);
        CrossFactory::createRoute(new Point(0,0), new Point(-10,0), crosses);
        CrossFactory::createRoute(new Point(0,0), new Point(10,0), crosses);
        CrossFactory::createRoute(new Point(10,10), new Point(10,0), crosses);
        CrossFactory::createRoute(new Point(0,10), new Point(0,0), crosses);
        CrossFactory::createRoute(new Point(0,10), new Point(10,10), crosses);
    }

    void createMoreCrosses(){
        /*Map looks like:
         *   _
         *  | |_|_
         *  |___|_|
         *      |_|
         *      |_|
         */
        CrossFactory::createRoute(new Point(-20,-10), new Point(-10,-10), crosses);
        CrossFactory::createRoute(new Point(-20,-10), new Point(-20,10), crosses);
        CrossFactory::createRoute(new Point(0,10), new Point(-20,10), crosses);
        CrossFactory::createRoute(new Point(0,20), new Point(10,20), crosses);
        CrossFactory::createRoute(new Point(0,20), new Point(0,15), crosses);
        CrossFactory::createRoute(new Point(0,10), new Point(0,15), crosses);
        CrossFactory::createRoute(new Point(10,10), new Point(10,15), crosses);
        CrossFactory::createRoute(new Point(10,20), new Point(10,15), crosses);
        CrossFactory::createRoute(new Point(0,15), new Point(10,15), crosses);
    }

    ~CrossFactoryTest(){
        for(Cross* cross : crosses)
            delete cross;
    }
};

TEST_F(CrossFactoryTest, creatingRoute){
    createRoute(new Point(100,200), new Point(100,300));
    EXPECT_TRUE(crosses.size() == 2);
}

TEST_F(CrossFactoryTest, creatingRoutes){
    createCrosses();
    EXPECT_EQ(crosses.size(), 7);
}

TEST_F(CrossFactoryTest, creatingMoreRoutes){
    createCrosses();
    createMoreCrosses();
    EXPECT_EQ(crosses.size(), 13);
}





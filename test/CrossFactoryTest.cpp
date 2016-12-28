//
// Created by kuco on 14.12.16.
//

#include <gtest/gtest.h>
#include <Cross.h>
#include <CrossFactory.h>

class CrossFactoryTest : public ::testing::Test{
public:
    std::vector<PtrCross> crosses;
    CrossFactoryTest(){};

    void createRoute(PtrToConstPoint src, PtrToConstPoint dst){
        CrossFactory::createRoute(src, dst, crosses);
    }

    void createCrosses(){
        /*Map looks like:
         * |_|_
         *   |_|
        */
        ;
        CrossFactory::createRoute(std::make_shared<Point>(-10,-10), std::make_shared<Point>(-10,0), crosses);
        CrossFactory::createRoute(std::make_shared<Point>(0,-10), std::make_shared<Point>(0,0), crosses);
        CrossFactory::createRoute(std::make_shared<Point>(0,0), std::make_shared<Point>(-10,0), crosses);
        CrossFactory::createRoute(std::make_shared<Point>(0,0), std::make_shared<Point>(10,0), crosses);
        CrossFactory::createRoute(std::make_shared<Point>(10,10), std::make_shared<Point>(10,0), crosses);
        CrossFactory::createRoute(std::make_shared<Point>(0,10), std::make_shared<Point>(0,0), crosses);
        CrossFactory::createRoute(std::make_shared<Point>(0,10), std::make_shared<Point>(10,10), crosses);
    }

    void createMoreCrosses(){
        /*Map looks like:
         *   _
         *  | |_|_
         *  |___|_|
         *      |_|
         *      |_|
         */
        CrossFactory::createRoute(std::make_shared<Point>(-20,-10), std::make_shared<Point>(-10,-10), crosses);
        CrossFactory::createRoute(std::make_shared<Point>(-20,-10), std::make_shared<Point>(-20,10), crosses);
        CrossFactory::createRoute(std::make_shared<Point>(0,10), std::make_shared<Point>(-20,10), crosses);
        CrossFactory::createRoute(std::make_shared<Point>(0,20), std::make_shared<Point>(10,20), crosses);
        CrossFactory::createRoute(std::make_shared<Point>(0,20), std::make_shared<Point>(0,15), crosses);
        CrossFactory::createRoute(std::make_shared<Point>(0,10), std::make_shared<Point>(0,15), crosses);
        CrossFactory::createRoute(std::make_shared<Point>(10,10), std::make_shared<Point>(10,15), crosses);
        CrossFactory::createRoute(std::make_shared<Point>(10,20), std::make_shared<Point>(10,15), crosses);
        CrossFactory::createRoute(std::make_shared<Point>(0,15), std::make_shared<Point>(10,15), crosses);
    }

    ~CrossFactoryTest(){}
};

TEST_F(CrossFactoryTest, creatingRoute){
    createRoute(std::make_shared<Point>(100,200), std::make_shared<Point>(100,300));
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





//
// Created by kuco on 03.01.17.
//

#include <gtest/gtest.h>
#include <Cross.h>

class CrossTest : public ::testing::Test{

public:
    CrossTest(){
        cross1 = new Cross(std::make_shared<Point>(0,0));
        cross2 = new Cross(std::make_shared<Point>(0,0));
        cross3 = new Cross(std::make_shared<Point>(0,0));
        cross4 = new Cross(std::make_shared<Point>(0,0));
        cross5 = new Cross(std::make_shared<Point>(0,0));
    }
    ~CrossTest(){
        delete cross1;
        delete cross2;
        delete cross3;
        delete cross4;
        delete cross5;
    }

    Cross* cross1;
    Cross* cross2;
    Cross* cross3;
    Cross* cross4;
    Cross* cross5;

    void make_neighbours(){
        cross1->addNeighbour(std::make_shared<Cross>(*cross2));
        cross1->addNeighbour(std::make_shared<Cross>(*cross3));
        cross1->addNeighbour(std::make_shared<Cross>(*cross4));
        cross1->addNeighbour(std::make_shared<Cross>(*cross5));

    }

};

TEST_F(CrossTest, checkCrossConstructor){
    PtrToConstPoint point = std::make_shared<Point>(10,-10);
    Cross cross(point);
    EXPECT_TRUE(cross.getPosition()->getX() == 10 && cross.getPosition()->getY()==-10);
}

TEST_F(CrossTest, checkCrossEqualsCross){
    PtrToConstPoint point1 = std::make_shared<Point>(10,-10);
    PtrToConstPoint point2 = std::make_shared<Point>(10,-10);
    Cross cr1(point1);
    Cross cr2(point2);
    EXPECT_TRUE(cr1 == cr2);
}

TEST_F(CrossTest, checkCrossNotEqualsCross){
    PtrToConstPoint point1 = std::make_shared<Point>(10,-10);
    PtrToConstPoint point2 = std::make_shared<Point>(10,10);
    Cross cr1(point1);
    Cross cr2(point2);
    EXPECT_TRUE(cr1 != cr2);
}


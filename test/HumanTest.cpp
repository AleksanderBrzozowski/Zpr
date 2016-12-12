//
// Created by Aleksander on 12.12.2016.
//

#include<gtest/gtest.h>
#include <memory>
#include <Point.h>

class HumanTest : public ::testing::Test {
public:
    std::shared_ptr<Point const> lastPoint;

    HumanTest() : lastPoint(new Point(10, 20)){};

};

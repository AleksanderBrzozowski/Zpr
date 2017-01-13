//
// Created by aleksander on 09.01.17.
//

#include<gtest/gtest.h>
#include <Facilities.h>


class FacilitiesTest : public ::testing::Test {
public:
    Facilities facilities;
};

/**
 * [ ] - represents building
 *   y
 *   |    *MOV/CAM_END
 * [ |]    [ ]
 *   |*CAM[  ]
 * ---------x
 */
TEST_F(FacilitiesTest, SeenMovable) {
    facilities.addBuilding(Point(-2, 3), Point(1, 2));
    facilities.addBuilding(Point(3, 4), Point(4, 3));
    facilities.addBuilding(Point(2, 1), Point(5, 0));

    facilities.addCamera(Point(1, 1), Point(2, 5), 10, 10);

    PtrMovable movable = Car::createCar(Point(2, 5), std::vector<PtrToConstPoint>{PtrToConstPoint(new Point(2, 6))}, 10, 1);
    std::vector<PtrMovable> movables{movable};

    facilities.scan(movables);

    ASSERT_EQ(movables[0], facilities.getCameras()[0]->getSeenMovables()[0]);
}


/**
 * [ ] - represents building
 *   y
 *   |    *MOV/CAM_END
 *   |[   ] [ ]
 *   |*CAM[  ]
 * ---------x
 */
TEST_F(FacilitiesTest, NotSeenMovable) {
    facilities.addBuilding(Point(-2, 3), Point(2, 2));
    facilities.addBuilding(Point(3, 4), Point(4, 3));
    facilities.addBuilding(Point(2, 1), Point(5, 0));

    facilities.addCamera(Point(1, 1), Point(2, 5), 10, 10);

    PtrMovable movable = Car::createCar(Point(2, 5), std::vector<PtrToConstPoint>{PtrToConstPoint(new Point(2, 6))}, 10, 1);
    std::vector<PtrMovable> movables{movable};

    facilities.scan(movables);

    ASSERT_TRUE(facilities.getCameras()[0]->getSeenMovables().empty());
}

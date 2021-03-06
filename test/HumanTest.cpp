//
// Created by Aleksander on 23.12.2016.
//

#include<gtest/gtest.h>
#include <Types.h>
#include <Movable.h>

TEST(HumanTest, SampleRoute) {
    std::vector<PtrToConstPoint> points = {
            PtrToConstPoint(new Point(1, 1)),
            PtrToConstPoint(new Point(-10, 1)),
            PtrToConstPoint(new Point(-10, 11))
    };
    PtrHuman human = Human::createHuman(*points[0], points, 7, 0);
    std::vector<PtrToConstPoint> pointsToFallow = {
            PtrToConstPoint(new Point(1, 1)),
            PtrToConstPoint(new Point(-6, 1)),
            PtrToConstPoint(new Point(-10, 1)),
            PtrToConstPoint(new Point(-10, 8)),
            PtrToConstPoint(new Point(-10, 11)),
            PtrToConstPoint(new Point(-10, 4)),
            PtrToConstPoint(new Point(-10, 1)),
            PtrToConstPoint(new Point(-3, 1))
    };

    for (PtrToConstPoint &point : pointsToFallow) {
        ASSERT_EQ(*point, human->getActualPoint());
        ASSERT_TRUE(human->move());
    }
    ASSERT_EQ(*points[0], human->getActualPoint());

    // once again, human never stops
    for (PtrToConstPoint &point : pointsToFallow) {
        ASSERT_EQ(*point, human->getActualPoint());
        ASSERT_TRUE(human->move());
    }
    ASSERT_EQ(*points[0], human->getActualPoint());
}

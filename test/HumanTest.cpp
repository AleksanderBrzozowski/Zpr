//
// Created by Aleksander on 23.12.2016.
//

#include<gtest/gtest.h>
#include <Types.h>
#include <HumanRoute.h>
#include <Movable2.h>

TEST(HumanTest, SampleRoute) {
    std::vector<PtrToConstPoint> points = {
            PtrToConstPoint(new Point(1, 1)),
            PtrToConstPoint(new Point(-10, 1)),
            PtrToConstPoint(new Point(-10, 11))
    };
    HumanRoute humanRoute(points);
    Human human(humanRoute, *points[0], 7);
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
        ASSERT_EQ(*point, human.getActualPoint());
        ASSERT_TRUE(human.move());
    }
    ASSERT_EQ(*points[0], human.getActualPoint());

    // once again, human never stops
    for (PtrToConstPoint &point : pointsToFallow) {
        ASSERT_EQ(*point, human.getActualPoint());
        ASSERT_TRUE(human.move());
    }
    ASSERT_EQ(*points[0], human.getActualPoint());
}

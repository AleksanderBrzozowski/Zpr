//
// Created by Aleksander on 21.12.2016.
//

#include<gtest/gtest.h>
#include <Types.h>
#include <CarRoute.h>
#include <Movable.h>

TEST(CarTest, SampleRoute) {
    std::vector<PtrToConstPoint> points = {
            PtrToConstPoint(new Point(20, 20)),
            PtrToConstPoint(new Point(31, 20)),
            PtrToConstPoint(new Point(31, -2))
    };
    PtrCar car = Car::createCar(*points[0], points, 3, 0);
    std::vector<PtrToConstPoint> pointsToFallow = {
            PtrToConstPoint(new Point(20, 20)),
            PtrToConstPoint(new Point(23, 20)),
            PtrToConstPoint(new Point(26, 20)),
            PtrToConstPoint(new Point(29, 20)),
            PtrToConstPoint(new Point(31, 20)),
            PtrToConstPoint(new Point(31, 17)),
            PtrToConstPoint(new Point(31, 14)),
            PtrToConstPoint(new Point(31, 11)),
            PtrToConstPoint(new Point(31, 8)),
            PtrToConstPoint(new Point(31, 5)),
            PtrToConstPoint(new Point(31, 2)),
            PtrToConstPoint(new Point(31, -1))
            // last point which is 31, -2 omitted
    };


    for (PtrToConstPoint &point : pointsToFallow) {
        ASSERT_EQ(*point, car->getActualPoint());
        ASSERT_TRUE(car->move());
    }

    // check last point
    ASSERT_EQ(*points[2], car->getActualPoint());
    // check is end
    ASSERT_FALSE(car->move());
}

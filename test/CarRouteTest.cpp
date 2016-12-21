//
// Created by Aleksander on 21.12.2016.
//

#include <gtest/gtest.h>
#include <Types.h>
#include <CarRoute.h>

TEST(CarRouteTest, SampleRoute) {
    std::vector<PtrToConstPoint> points = {
            PtrToConstPoint(new Point(10, 10)),
            PtrToConstPoint(new Point(50, 10)),
            PtrToConstPoint(new Point(50, -110)),
            PtrToConstPoint(new Point(50, 0))
    };
    CarRoute carRoute(points);

    ASSERT_FALSE(carRoute.isEnd());
    ASSERT_EQ(RouteVector(0, 0), carRoute.getRouteVector(*points[0]));

    carRoute.nextPoint();
    ASSERT_FALSE(carRoute.isEnd());
    ASSERT_EQ(RouteVector(1, 0), carRoute.getRouteVector(*points[0]));
    ASSERT_EQ(RouteVector(1, 0), carRoute.getRouteVector(Point(20, 10)));
    ASSERT_EQ(RouteVector(0, 0), carRoute.getRouteVector(*points[1]));

    carRoute.nextPoint();
    ASSERT_FALSE(carRoute.isEnd());
    ASSERT_EQ(RouteVector(0, -1), carRoute.getRouteVector(*points[1]));
    ASSERT_EQ(RouteVector(0, -1), carRoute.getRouteVector(Point(50, -19)));
    ASSERT_EQ(RouteVector(0, 0), carRoute.getRouteVector(*points[2]));

    carRoute.nextPoint();
    ASSERT_FALSE(carRoute.isEnd());
    ASSERT_EQ(RouteVector(0, 1), carRoute.getRouteVector(*points[2]));
    ASSERT_EQ(RouteVector(0, 1), carRoute.getRouteVector(Point(50, - 5)));
    ASSERT_EQ(RouteVector(0, 0), carRoute.getRouteVector(*points[3]));

    carRoute.nextPoint();
    ASSERT_TRUE(carRoute.isEnd());
}


TEST(CarRouteTest, RouteVectorOk) {
    std::vector<PtrToConstPoint> points = {
            PtrToConstPoint(new Point(10, 10))
    };
    CarRoute carRoute(points);

    ASSERT_EQ(RouteVector(0, 0), carRoute.getRouteVector(*points[0]));
    ASSERT_EQ(RouteVector(-1, 0), carRoute.getRouteVector(Point(20, 10)));
    ASSERT_EQ(RouteVector(1, 0), carRoute.getRouteVector(Point(-10, 10)));
    ASSERT_EQ(RouteVector(0, -1), carRoute.getRouteVector(Point(10, 20)));
    ASSERT_EQ(RouteVector(0, 1), carRoute.getRouteVector(Point(10, -20)));
}

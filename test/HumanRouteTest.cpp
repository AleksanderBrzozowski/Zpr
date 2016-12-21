//
// Created by Aleksander on 21.12.2016.
//

#include<gtest/gtest.h>
#include <HumanRoute.h>
#include <Types.h>

void forwardWay(HumanRoute &humanRoute, const std::vector<PtrToConstPoint>& points);

void reverseWay(HumanRoute &humanRoute, const std::vector<PtrToConstPoint>& points);

TEST(HumanRouteTest, sampleRoute) {
    std::vector<PtrToConstPoint> points = {
            PtrToConstPoint(new Point(5, 20)),
            PtrToConstPoint(new Point(20, 20)),
            PtrToConstPoint(new Point(-10, 20)),
            PtrToConstPoint(new Point(-10, -5))
    };
    HumanRoute humanRoute(points);

    for (int i = 0; i < 2; ++i) {
        forwardWay(humanRoute, points);
        humanRoute.nextPoint(); // reverse way
        reverseWay(humanRoute, points);
        humanRoute.nextPoint(); // forward way
    }
}


TEST(HumanRouteTest, routeVectorOk) {
    std::vector<PtrToConstPoint> points = {
            PtrToConstPoint(new Point(5, 5))
    };
    HumanRoute humanRoute(points);
    ASSERT_EQ(RouteVector(1, 0), humanRoute.getRouteVector(Point(0, 5)));
    ASSERT_EQ(RouteVector(-1, 0), humanRoute.getRouteVector(Point(10, 5)));
    ASSERT_EQ(RouteVector(0, 1), humanRoute.getRouteVector(Point(5, -10)));
    ASSERT_EQ(RouteVector(0, -1), humanRoute.getRouteVector(Point(5, 10)));
    ASSERT_EQ(RouteVector(0, 0), humanRoute.getRouteVector(*points[0]));

}

void forwardWay(HumanRoute &humanRoute, const std::vector<PtrToConstPoint> &points) {
    ASSERT_FALSE(humanRoute.isEnd());
    ASSERT_EQ(RouteVector(0, 1), humanRoute.getRouteVector(Point(5, 15)));
    ASSERT_EQ(RouteVector(0, 0), humanRoute.getRouteVector(*points[0]));

    humanRoute.nextPoint();
    ASSERT_FALSE(humanRoute.isEnd());
    ASSERT_EQ(RouteVector(1, 0), humanRoute.getRouteVector(*points[0]));
    ASSERT_EQ(RouteVector(1, 0), humanRoute.getRouteVector(Point(10, 20)));
    ASSERT_EQ(RouteVector(0, 0), humanRoute.getRouteVector(*points[1]));

    humanRoute.nextPoint();
    ASSERT_FALSE(humanRoute.isEnd());
    ASSERT_EQ(RouteVector(-1, 0), humanRoute.getRouteVector(*points[1]));
    ASSERT_EQ(RouteVector(-1, 0), humanRoute.getRouteVector(Point(-5, 20)));
    ASSERT_EQ(RouteVector(0, 0), humanRoute.getRouteVector(*points[2]));

    humanRoute.nextPoint();
    ASSERT_FALSE(humanRoute.isEnd());
    ASSERT_EQ(RouteVector(0, -1), humanRoute.getRouteVector(*points[2]));
    ASSERT_EQ(RouteVector(0, -1), humanRoute.getRouteVector(Point(-10, 0)));
    ASSERT_EQ(RouteVector(0, 0), humanRoute.getRouteVector(*points[3]));
}

void reverseWay(HumanRoute &humanRoute, const std::vector<PtrToConstPoint> &points) {
    ASSERT_FALSE(humanRoute.isEnd());
    ASSERT_EQ(RouteVector(0, 1), humanRoute.getRouteVector(Point(-10, 5)));
    ASSERT_EQ(RouteVector(0, 0), humanRoute.getRouteVector(*points[2]));

    humanRoute.nextPoint();
    ASSERT_FALSE(humanRoute.isEnd());
    ASSERT_EQ(RouteVector(1, 0), humanRoute.getRouteVector(*points[2]));
    ASSERT_EQ(RouteVector(1, 0), humanRoute.getRouteVector(Point(0, 20)));
    ASSERT_EQ(RouteVector(0, 0), humanRoute.getRouteVector(*points[1]));

    humanRoute.nextPoint();
    ASSERT_FALSE(humanRoute.isEnd());
    ASSERT_EQ(RouteVector(-1, 0), humanRoute.getRouteVector(*points[1]));
    ASSERT_EQ(RouteVector(-1, 0), humanRoute.getRouteVector(Point(10, 20)));
    ASSERT_EQ(RouteVector(0, 0), humanRoute.getRouteVector(*points[0]));
}






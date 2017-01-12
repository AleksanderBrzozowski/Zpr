//
// Created by Aleksander on 24.12.2016.
//

#include <gtest/gtest.h>
#include <Camera.h>
#include <Movable.h>

TEST(CameraTest, range) {
    Camera camera(Point(1, 1), Point(3, 3), 30, 1);

    ASSERT_TRUE(camera.isInRange(Point(2, 2)));
    ASSERT_TRUE(camera.isInRange(Point(1, 1)));
    ASSERT_TRUE(camera.isInRange(Point(0, 0)));
    ASSERT_TRUE(camera.isInRange(Point(-1, -1)));

    ASSERT_FALSE(camera.isInRange(Point(4, 3)));
    ASSERT_FALSE(camera.isInRange(Point(4, 4)));
    ASSERT_FALSE(camera.isInRange(Point(-3, -3)));
};

/**
 * y
 * |   END
 * |
 * ST-------x
 * ANGLE 0 to 90 degrees
 */
TEST(CameraTest, angle0_90_degrees){
    Camera camera(Point(0, 0), Point(2, 2), 90, 1);

    ASSERT_TRUE(camera.isInAngle(Point(1, 1)));
    ASSERT_TRUE(camera.isInAngle(Point(0, 0)));
    ASSERT_TRUE(camera.isInAngle(Point(2, 2)));
    ASSERT_TRUE(camera.isInAngle(Point(500, 100)));

    ASSERT_FALSE(camera.isInAngle(Point(-100, 0)));
    ASSERT_FALSE(camera.isInAngle(Point(0, -100)));
    ASSERT_FALSE(camera.isInAngle(Point(-100, -100)));
    ASSERT_FALSE(camera.isInAngle(Point(-1, -10)));
    ASSERT_FALSE(camera.isInAngle(Point(-100, -1)));
}

/**         y
 *          |
 *          |
 *          |
 *    -----------------x
 *    END   |
 *          |
 *          |
 *        ST|
 */
TEST(CameraTest, angle90_3_140_3_degrees){
    Camera camera(Point(-1, -20), Point(-10, -1), 50, 1);

    ASSERT_TRUE(camera.isInAngle(Point(-10, -10)));
    ASSERT_TRUE(camera.isInAngle(Point(-3, 2)));

    ASSERT_FALSE(camera.isInAngle(Point(10, 10)));
    ASSERT_FALSE(camera.isInAngle(Point(10, -10)));
    ASSERT_FALSE(camera.isInAngle(Point(-1, -11)));

}


TEST(CameraTest, putMovables) {
    Camera camera(Point(-1, 1), Point(-10, 1), 50, 1);

    PtrConstMovable movable = createCar(Point(1, 1), std::vector<PtrToConstPoint>{PtrToConstPoint(new Point(1, 2))}, 10, 1);
    PtrConstMovable movable1 = createCar(Point(1, 1), std::vector<PtrToConstPoint>{PtrToConstPoint(new Point(1, 2))}, 10, 2);
    PtrConstMovable movable2 = createHuman(Point(1, 1), std::vector<PtrToConstPoint>{PtrToConstPoint(new Point(1, 2))}, 10, 2);

    camera.addSeenMovable(movable);
    camera.addSeenMovable(movable1);
    camera.addSeenMovable(movable2);

    std::vector<PtrConstMovable> movables = camera.getSeenMovables();

    ASSERT_EQ(movable, movables[0]);
    ASSERT_EQ(movable1, movables[1]);
    ASSERT_EQ(movable2, movables[2]);
}

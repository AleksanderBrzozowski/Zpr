cmake_minimum_required(VERSION 3.6)
project(Zpr)

set(GTEST_DIR googletest/googletest)

add_library(gtest ${GTEST_DIR}/src/gtest-all.cc ${GTEST_DIR}/src/gtest_main.cc)
target_include_directories(gtest PUBLIC ${GTEST_DIR} ${GTEST_DIR}/include)

find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(SOURCE_FILES example.cpp RouteVectorTest.cpp PointTest.cpp CrossFactoryTest.cpp HumanRouteTest.cpp CarRouteTest.cpp CarTest.cpp HumanTest.cpp CameraTest.cpp TrafficControlTest.cpp CrossTest.cpp BuildingTest.cpp StraightLineTest.cpp FacilitiesTest.cpp MovableFactoryTest.cpp)
add_executable(Tests ${SOURCE_FILES})
target_link_libraries(Tests src gtest)
target_link_libraries(Tests Threads::Threads)

cmake_minimum_required(VERSION 3.6)
project(Zpr)

add_subdirectory(googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include)
include_directories(src1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(SOURCE_FILES example.cpp RouteTest.cpp RouteVectorTest.cpp PointTest.cpp)
add_executable(Tests ${SOURCE_FILES})
target_link_libraries(Tests gtest gtest_main)
target_link_libraries(Tests src)

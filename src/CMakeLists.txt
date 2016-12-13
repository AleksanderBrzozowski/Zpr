cmake_minimum_required(VERSION 3.6)

set(SOURCE_FILES Point.cpp Point.h Route.cpp Route.h RouteVector.cpp RouteVector.h Movable.cpp Movable.h Cross.cpp Cross.h TrafficControl.cpp TrafficControl.h CrossFactory.cpp CrossFactory.h)

add_library(src ${SOURCE_FILES})
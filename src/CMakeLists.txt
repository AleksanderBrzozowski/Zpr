cmake_minimum_required(VERSION 3.6)

link_libraries(GUI)
set(SOURCE_FILES Point.cpp Point.h RouteVector.cpp RouteVector.h Cross.cpp Cross.h CrossFactory.cpp CrossFactory.h CarRoute.cpp CarRoute.h HumanRoute.cpp HumanRoute.h Route.cpp Route.h Movable.cpp Movable.h Types.h Camera.cpp Camera.h Building.cpp Building.h LineSegment.cpp LineSegment.h Facilities.cpp Facilities.h Map.cpp Map.h MovableFactory.cpp MovableFactory.h)
add_library(src ${SOURCE_FILES})
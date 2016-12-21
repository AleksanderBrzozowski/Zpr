cmake_minimum_required(VERSION 3.6)

link_libraries(GUI)
set(SOURCE_FILES Point.cpp Point.h Route.cpp Route.h RouteVector.cpp RouteVector.h Movable.cpp Movable.h Cross.cpp Cross.h TrafficControl.cpp TrafficControl.h CrossFactory.cpp CrossFactory.h CarRoute.cpp CarRoute.h HumanRoute.cpp HumanRoute.h Route2.cpp Route2.h MovableFactory.cpp MovableFactory.h Movable2.cpp Movable2.h Types.h)
add_library(src ${SOURCE_FILES})
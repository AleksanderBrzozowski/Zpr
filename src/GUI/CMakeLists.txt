cmake_minimum_required(VERSION 3.6)

set(SOURCE_FILES cargui.cpp eventinterpreter.cpp mainwindow.h pplgui.h cargui.h
    eventinterpreter.h mainwindow.ui roadgui.cpp gridgui.cpp maparea.cpp roadgui.h
    drawable.cpp gridgui.h maparea.h ui_mainwindow.h drawable.h mainwindow.cpp pplgui.cpp
    buildinggui.cpp buildinggui.h cameragui.h cameragui.cpp ../Point.h ../Point.cpp)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)

add_library(GUI ${SOURCE_FILES})

target_link_libraries(GUI Qt5::Widgets)
target_link_libraries(GUI Qt5::Gui)


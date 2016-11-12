cmake_minimum_required(VERSION 3.6)

set(SOURCE_FILES guiconstants.h mainwindow.h mainwindow.cpp maparea.h maparea.cpp drawable.cpp drawable.h
        gridgui.cpp gridgui.h pplgui.cpp pplgui.h roadgui.cpp roadgui.h cargui.cpp cargui.h ../Point.h ../Point.cpp ui_mainwindow.h)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)

add_library(GUI ${SOURCE_FILES})

target_link_libraries(GUI Qt5::Widgets)
target_link_libraries(GUI Qt5::Gui)


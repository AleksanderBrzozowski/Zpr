cmake_minimum_required(VERSION 3.6)
project(Zpr)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(SOURCE_FILES main.cpp)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

add_executable(Zpr_run ${SOURCE_FILES})

include_directories(src)

find_package(Threads REQUIRED)

add_subdirectory(src)
add_subdirectory(src/GUI)
add_subdirectory(test)

target_link_libraries(Zpr_run src)
target_link_libraries(Zpr_run GUI)
target_link_libraries(Zpr_run Threads::Threads)

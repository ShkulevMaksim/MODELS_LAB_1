cmake_minimum_required(VERSION 3.21)
project(untitled1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

add_executable(untitled1 main.cpp)
target_link_libraries(untitled1
        Qt5::Core
        )

target_link_libraries(untitled1 Qt5::Gui)
target_link_libraries(untitled1 Qt5::Widgets)


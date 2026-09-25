cmake_minimum_required(VERSION 3.16)
project(WorldPopulationApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(WorldPopulationApp
    main.cpp
    WorldPopulationModel.h
    WorldPopulationController.h
    InputDialog.h
    MainWindow.h
)

target_link_libraries(WorldPopulationApp PRIVATE Qt6::Widgets)
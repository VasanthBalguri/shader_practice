cmake_minimum_required(VERSION 3.1.0)

project(shader_test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets OpenGL REQUIRED)
FIND_PACKAGE( OpenSceneGraph COMPONENTS osgDB osgGA osgViewer osg osgUtil osgText)

include_directories(${OCE_INCLUDE_DIRS})

add_executable(shader_test
    mainwindow.ui
    qtosgwidget.cpp
    mainwindow.cpp
    shader_dialog.cpp
    main.cpp
)

target_link_libraries(shader_test Qt5::Widgets ${OPENSCENEGRAPH_LIBRARIES})

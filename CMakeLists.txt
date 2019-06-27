cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 11)

project(BicycleTool)

# include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

find_package(OpenCV REQUIRED)
if(OpenCV_VERSION VERSION_LESS "4.0")
	message( FATAL_ERROR "opencv version must upper then 4" )
endif()

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(SOURCE_FILE
    main.cpp
    mainwindow.cpp
    graphicscene.cpp
    graphicwidget.cpp
    socketgraphicsitem.cpp
    convertimage.cpp
	GraphicsData.cpp
	GraphicsItemWithVector.cpp
  )

set(INCLUDE_FILE
    mainwindow.h
    graphicscene.h
    graphicwidget.h
    socketgraphicsitem.h
    convertimage.h
	MouseRectEvent.h
	GraphicsData.h
	GraphicsItemWithVector.h
  )

set(QT_FORMS
    mainwindow.ui
    graphicwidget.ui
  )

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PROTOBUF_INCLUDE_DIR})

add_executable(Drawings ${SOURCE_FILE} ${INCLUDE_FILE} ${QT_FORMS} ${RESOURCES} ${PROTO_HDRS} ${PROTO_SRCS})
target_link_libraries(Drawings ${PROTOBUF_LIBRARIES} ${OpenCV_LIBS}  Qt5::Core Qt5::Widgets)
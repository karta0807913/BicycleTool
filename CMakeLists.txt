cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 11)

project(BicycleTool)

include_directories("./include/")

# include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

find_package(OpenCV REQUIRED)
if(OpenCV_VERSION VERSION_LESS "4.0")
	message( FATAL_ERROR "opencv version must upper then 4" )
endif()

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Protobuf REQUIRED)

set(SOURCE_FILE
    src/main.cpp
    src/mainwindow.cpp
    src/graphicscene.cpp
    src/graphicwidget.cpp
    src/socketgraphicsitem.cpp
    src/convertimage.cpp
	src/GraphicsItemWithVector.cpp
  )

set(INCLUDE_FILE
    include/mainwindow.h
    include/graphicscene.h
    include/graphicwidget.h
    include/socketgraphicsitem.h
    include/convertimage.h
	include/MouseRectEvent.h
	include/GraphicsItemWithVector.h
  )

set(PROTO
    include/DataType.proto
    )

set(QT_FORMS
    src/mainwindow.ui
    src/graphicwidget.ui
  )

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PROTOBUF_INCLUDE_DIR})

if(UNIX)
    protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS "${PROTO}")
endif(UNIX)

add_executable(Drawings ${SOURCE_FILE} ${INCLUDE_FILE} ${QT_FORMS} ${RESOURCES} ${PROTO_HDRS} ${PROTO_SRCS})
target_link_libraries(Drawings ${PROTOBUF_LIBRARIES} ${OpenCV_LIBS}  Qt5::Core Qt5::Widgets)

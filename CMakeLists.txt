cmake_minimum_required(VERSION 3.20)

project(render)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/Sources")
set(SOURCES
  ${SRC_DIR}/main.cpp
  ${SRC_DIR}/Camera.cpp
  ${SRC_DIR}/Figures.cpp
  ${SRC_DIR}/Line.cpp
  ${SRC_DIR}/Movements.cpp
  ${SRC_DIR}/MyDouble.cpp
  ${SRC_DIR}/Plane.cpp
  ${SRC_DIR}/Player.cpp
  ${SRC_DIR}/Point.cpp
  ${SRC_DIR}/Polygon.cpp
  ${SRC_DIR}/SoLE.cpp
)

find_package(SFML COMPONENTS window graphics system)

add_executable(render ${SOURCES})

target_include_directories(render PRIVATE "${PROJECT_SOURCE_DIR}/Headers")

set_target_properties(render
  PROPERTIES
    INSTALL_RPATH_USE_LINK_PATH TRUE)

target_link_libraries(render sfml-graphics)
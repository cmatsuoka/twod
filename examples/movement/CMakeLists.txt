cmake_minimum_required (VERSION 2.8.1)
include_directories(../../twoD/base ../../twoD/objects)
link_directories(../../twoD)
project(libtwod-examples-movement)
include(../common.cmake)
add_executable(movement
	ctrl_square.cpp
	info.cpp
	movement.cpp
	moving_square.cpp
	wall.cpp
)
target_link_libraries(movement libtwod.so)

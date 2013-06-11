cmake_minimum_required (VERSION 2.8.1)
project(libtwod-examples-movement)
add_executable(movement
	ctrl_square.cpp
	info.cpp
	movement.cpp
	moving_square.cpp
	wall.cpp
)
include_directories(../../twoD/base ../../twoD/objects)
target_link_libraries(movement libtwod.so)

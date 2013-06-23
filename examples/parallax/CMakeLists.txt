cmake_minimum_required (VERSION 2.8.1)
project(libtwod-examples-parallax)
include(../common.cmake)
add_executable(parallax
	info.cpp
	parallax.cpp
	spaceship.cpp
)
include_directories(../../twoD/base ../../twoD/objects)
target_link_libraries(parallax libtwod.so)

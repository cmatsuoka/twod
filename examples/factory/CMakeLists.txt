cmake_minimum_required (VERSION 2.8.1)
include_directories(../../twoD/base ../../twoD/objects)
link_directories(../../twoD)
project(libtwod-examples-factory)
include(../common.cmake)
add_executable(factory
	character.cpp
	factory_example.cpp
	info.cpp
	obj_factory.cpp
	wall.cpp
)
target_link_libraries(factory libtwod.so)

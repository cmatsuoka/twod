cmake_minimum_required (VERSION 2.8.1)
project(libtwod-examples-factory)
add_executable(factory
	character.cpp
	factory_example.cpp
	info.cpp
	obj_factory.cpp
	wall.cpp
)
include_directories(../../twoD/base ../../twoD/objects)
target_link_libraries(factory libtwod.so)

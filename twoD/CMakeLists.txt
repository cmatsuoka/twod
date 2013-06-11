cmake_minimum_required (VERSION 2.6)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules/")
project(libtwod)
find_package(Allegro REQUIRED)
set(LIBS ${LIBS} ${ALLEGRO_LIBRARIES})
add_library(twod SHARED
	engine.cpp
	base/background.cpp
	base/color.cpp
	base/image.cpp
	base/movement.cpp
	base/primitive.cpp
	base/sound.cpp
	base/sprite.cpp
	base/text.cpp
	base/tileset.cpp
	objects/block.cpp
	objects/border.cpp
	objects/image_map.cpp
	objects/platform.cpp
	objects/tile_map.cpp
)
set_target_properties(twod
	PROPERTIES
	VERSION 0.1.0
	SOVERSION 0.1
)
target_link_libraries(twod
	${LIBS}
)

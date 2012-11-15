#include<string>
#include<iostream>
using namespace std;

#include "../../twoD/engine.h"
#include "../../twoD/base/image.h"
#include "../../twoD/base/tileset.h"
#include "../../twoD/base/background.h"
#include "../../twoD/objects/tile_map.h"

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 600

#define TILESET_FILE string("resources/tileset/side_platform1.bmp")
#define NUM_TILES 198
#define NUM_TILES_LINE 18
#define TILE_SIZE 16
#define TILE_SPACING 1
#define TILE_FIRSTID 0
#define TILESET_ALPHA "black"
#define BASE_Y 200

// spaceship with parallax background example
int main(int argc, char *argv[]){
	twoDEngine *engine;
	twoDTileset *tileset;
	twoDBackground *background;
	twoDTileMap *map;
	int x = 0, y = 0;

	engine = new twoDEngine(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	background = new twoDBackground(new twoDColor("white"));
	engine->setBackground(background);

	tileset = new twoDTileset(TILESET_FILE, TILE_SIZE, TILE_SIZE, TILE_SPACING, TILE_FIRSTID, new twoDColor(TILESET_ALPHA));

	map = new twoDTileMap();
	for(int i=0; i<NUM_TILES; i++){
		x = (i % NUM_TILES_LINE) * TILE_SIZE + TILE_SPACING;
		y = (i / NUM_TILES_LINE) * TILE_SIZE + TILE_SPACING + BASE_Y;
		map->addTile(tileset->getTile(i), x, y);
	}
	map->setParallax(true);
	map->setRepeat(true);

	engine->addObject((twoDObject*)map,15);
	engine->main();

	return 0;
}


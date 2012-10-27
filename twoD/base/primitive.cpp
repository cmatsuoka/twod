#include "primitive.h"

static bool ALLEGRO_PRIMITIVE_ADDON_INIT = false;

twoDPrimitive::~twoDPrimitive(){
	if(this->texture != NULL)
		delete this->texture;
}

twoDPrimitive::twoDPrimitive(){
	if(!ALLEGRO_PRIMITIVE_ADDON_INIT){
		al_init_primitives_addon();
		ALLEGRO_PRIMITIVE_ADDON_INIT = true;
	}

	this->numVertices = 0;
	this->type = TWOD_PRIMITIVE_LINE_LOOP;
	this->texture = NULL;
	this->color = new twoDColor("white");
}

void twoDPrimitive::addVertex(float x, float y, float u, float v){
	struct ALLEGRO_VERTEX vertex;
	vertex.x = x;
	vertex.y = y;
	vertex.z = 0;
	vertex.u = u;
	vertex.v = v;
	vertex.color = this->color->map();
	this->vertices[this->numVertices++] = vertex;
}

void twoDPrimitive::addVertex(float x, float y){
	this->addVertex(x, y, 0.0, 0.0);
}

void twoDPrimitive::draw(){
	ALLEGRO_BITMAP* texture = NULL;

	if(this->texture != NULL)
		texture = this->texture->getBitmap();

	al_draw_prim(this->vertices, NULL, texture, 0, this->numVertices, this->type);
}

void twoDPrimitive::setTexture(string texturefile){
	this->texture = new twoDImage(texturefile);
}

void twoDPrimitive::move(float x, float y){
	for(int i=0; i<this->numVertices; i++){
		this->vertices[i].x += x;
		this->vertices[i].y += y;
	}
}



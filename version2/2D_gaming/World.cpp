#include "World.h"

World::World(int FPS = 60, int width = 500, int height = 500){
	timer = Timer(); 
	this->FPS = FPS;
	this->screen_width = width;
	this->screen_height = height;
}

World::~World() {};

bool World::tick() {
	return timer.oneFramePassed(FPS);
}

int World::getWidth() const {
	return screen_width;
}
int World::getHeight() const {
	return screen_height;
}
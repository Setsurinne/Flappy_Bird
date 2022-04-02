#pragma once
#include "object.h"

class Ground : public object2D {
public:
	void update();
};

class Pipe : public object2D {
public:
	void update();
	void draw();
};

class Bird : public object2D {
public:
	void draw();
	int SPEED_UP = -12;
};
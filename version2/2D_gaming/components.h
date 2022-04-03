#pragma once
#include "object.h"
extern int pivot;

class Ground : public object2D {
public:
	void update();
};

class Pipe : public object2D {
public:
	Pipe();
	Pipe(int is_buttom);
	void update();
	bool is_buttom = false;
};

class Bird : public object2D {
public:
	void draw();
	int SPEED_UP = -12;
};

class Score : public object2D {
public:
	void draw();
	void update();

private:
	int point = 0;
};
#pragma once
#include "Object2D.h"
#include "Object2DPhysical.h"
extern int pivot;

class Ground : public Object2DPhysical {
public:
	Ground();
	void update();
};

class Pipe : public Object2DPhysical {
public:
	Pipe();
	Pipe(int is_buttom);
	void update();
	bool is_buttom = false;
};

class Bird : public Object2DPhysical {
public:
	Bird();
	void update();
	void draw() const;
	int SPEED_UP = -12;

protected:
	IMAGE rotated_image;
	IMAGE rotated_mask;
	virtual void setCollisionBoxX();
	virtual void setCollisionBoxY();
};

class Score : public Object2D {
public:
	void draw() const;
	void update();
	void setPoint(int);

private:
	int point = 0;
};

class OpenText : public Object2D {
public:
	void update();
};


class EndText : public Object2D {
public:
	EndText();
	void update();
};
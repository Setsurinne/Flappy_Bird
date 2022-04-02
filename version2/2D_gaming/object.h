#pragma once
#include <easyx.h>
#include <graphics.h>
#include <iostream>
#include <vector>
class object2D
{
public:
	object2D();

	int getX();
	int getY();
	int getSpeedX();
	int getSpeedY();
	int getAccX();
	int getAccY();
	int getHeight();
	int getWidth();

	void setX(int val);
	void setY(int val);
	void setSpeedX(int val);
	void setSpeedY(int val);
	void setAccX(int val);
	void setAccY(int val);

	virtual void loadImage(LPCTSTR address);
	virtual void draw();
	virtual void update();
	virtual bool collision(object2D other_obj);

	void(*clickAction)();
	void receiveEvent(int cx, int cy);

private:
	int x;
	int y;

	int speed_x;
	int speed_y;

	int acceleration_x;
	int acceleration_y;

	int height;
	int width;
	int frame;

	bool clickable;
	bool visiable;

	std::vector<IMAGE> image;
	std::vector<IMAGE> mask;

	bool isClickMe(int cx, int cy);
};
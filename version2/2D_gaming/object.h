#pragma once
#include <easyx.h>
#include <graphics.h>
#include <iostream>
#include <algorithm>
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
	int getNumImage();

	bool isVisiable();
	bool isClickable();
	bool isTransparent();

	void setValue(int x = 0,
		int y = 0,
		int acceleration_x = 0,
		int acceleration_y = 0,
		int speed_x = 0,
		int speed_y = 0);

	void setX(int val);
	void setY(int val);
	void setSpeedX(int val);
	void setSpeedY(int val);
	void setAccX(int val);
	void setAccY(int val);
	void setVisibility(bool val);
	void setClickability(bool val);

	virtual void loadImage(LPCTSTR address, 
		LPCTSTR mask_address = NULL,
		int nWidth = 0,			// 图片的拉伸宽度
		int nHeight = 0,		// 图片的拉伸高度
		bool bResize = false	// 是否调整 IMAGE 的大小以适应图片);
	);

	virtual void draw();
	virtual void update();
	virtual bool collision(object2D other_obj);

	void(*clickAction)();
	void receiveEvent(int cx, int cy);

protected:
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
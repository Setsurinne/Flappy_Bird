#pragma once
#include <easyx.h>
#include <graphics.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

class Object2D
{
public:
	Object2D();

	int getX() const;
	int getY() const;
	int getHeight() const;
	int getWidth() const;
	int getNumImage() const;

	bool isVisiable() const;
	bool isClickable() const;
	bool isTransparent() const;

	virtual void setValue(int x = 0, int y = 0);

	virtual void setX(int val);
	virtual void setY(int val);
	void setHeight(int val);
	void setWidth(int val);

	void setVisibility(bool val);
	void setClickability(bool val);

	void(*clickAction)();
	void receiveEvent(int cx, int cy);
	bool overlay(const Object2D& other_obj) const;

	virtual void loadImage(LPCTSTR address, 
		LPCTSTR mask_address = NULL,
		int nWidth = 0,			// ͼƬ��������
		int nHeight = 0,		// ͼƬ������߶�
		bool bResize = false	// �Ƿ���� IMAGE �Ĵ�С����ӦͼƬ);
	);

	virtual void useImage(IMAGE* img, IMAGE* msk = NULL);

	virtual void draw() const;
	virtual void update();


protected:
	int x;
	int y;
	int height;
	int width;
	int frame;

	bool clickable;
	bool visiable;

	std::vector<IMAGE*> image;
	std::vector<IMAGE*> mask;

	bool isClickMe(int cx, int cy);
};
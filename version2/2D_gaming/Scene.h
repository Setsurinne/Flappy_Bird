#pragma once
#include <vector>
#include "Object2D.h"

class Scene
{
public:
	Scene(Object2D*, bool visiable = false, bool clickable = false, void (*beginCallBack)() = NULL, void (*endCallBack)() = NULL);
	Scene(std::vector<Object2D*>&, bool visiable = false, bool clickable = false, void (*beginCallBack)() = NULL, void (*endCallBack)() = NULL);
	~Scene();

	void addElement(Object2D*);

	void draw();
	void updateByTick();

	void sceneBegin();
	void sceneEnd();

protected:
	bool pause;
	bool clickable;
	bool visiable;
	void (*beginCallBack)();
	void (*endCallBack)();

	std::vector<Object2D*> elements;
};


#pragma once
#include <vector>
#include "Object2D.h"

class Scene
{
public:
	Scene();
	Scene(Object2D*, bool visiable = false, bool clickable = false, void (*beginCallBack)() = NULL, void (*endCallBack)() = NULL);
	Scene(std::vector<Object2D*>&, bool visiable = false, bool clickable = false, void (*beginCallBack)() = NULL, void (*endCallBack)() = NULL);
	~Scene();

	void addElement(Object2D*);

	void setUpdatable(bool);
	void setClickability(bool);
	void setVisibility(bool);

	bool isUpdatable() const;

	void draw();
	virtual void updateByTick();
	void leftButtonClick(const MOUSEMSG&);

	void sceneBegin();
	void sceneEnd();


protected:
	bool updatable;
	bool clickable;
	bool visiable;
	void (*beginCallBack)();
	void (*endCallBack)();

	std::vector<Object2D*> elements;
};


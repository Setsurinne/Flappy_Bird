#pragma once
#include <vector>
#include "Object2D.h"

/// <summary>
/// A scene is a collection of Object2D
/// With Scene, user could control a serious of related Object2D at the same time
/// </summary>
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

	/// <summary>
	/// Begin event of the scene
	/// </summary>
	void sceneBegin();

	/// <summary>
	/// End event of the scene
	/// </summary>
	void sceneEnd();


protected:
	bool updatable;
	bool clickable;
	bool visiable;
	void (*beginCallBack)();
	void (*endCallBack)();

	std::vector<Object2D*> elements;
};


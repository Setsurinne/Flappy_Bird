#include "SceneCollidable.h"

SceneCollidable::SceneCollidable() {
	this->elements = std::vector<Object2DPhysical*>();
	this->visiable = false;
	this->updatable = false;
	this->clickable = false;
	this->beginCallBack = NULL;
	this->endCallBack = NULL;
}
SceneCollidable::SceneCollidable(Object2DPhysical* obj, bool visiable, bool clickable, void (*beginCallBack)(), void (*endCallBack)()) {
	this->elements = std::vector<Object2DPhysical*>();
	elements.push_back(obj);
	this->visiable = visiable;
	this->clickable = clickable;
	this->updatable = true;

	this->beginCallBack = beginCallBack;
	this->endCallBack = endCallBack;
}
SceneCollidable::SceneCollidable(std::vector<Object2DPhysical*>& input_val, bool visiable, bool clickable, void (*beginCallBack)(), void (*endCallBack)()) {
	this->elements = std::vector<Object2DPhysical*>(input_val.begin(), input_val.end());
	this->visiable = visiable;
	this->clickable = clickable;
	this->updatable = true;

	this->beginCallBack = beginCallBack;
	this->endCallBack = endCallBack;
}

void SceneCollidable::updateByTick() {
	Scene::updateByTick();
	if (!isCollidable()) return;
	for (int i = 0; i < elements.size() - 1; i++) {
		for (int j = i + 1; j < elements.size(); j++) {
			elements[i]->collision(*elements[j]);
		}
	}
}
bool SceneCollidable::isCollidable() const {
	return this->collidable;
}

void SceneCollidable::setCollidability(bool val) {
	this->collidable = val;
}
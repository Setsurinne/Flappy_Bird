#include "Scene.h"

Scene::Scene(Object2D* input_val, bool visiable, bool clickable, void (* beginCallBack)(), void (*endCallBack)()) {
	this->elements = std::vector<Object2D*>();
	elements.push_back(input_val);
	this->visiable = visiable;
	this->clickable = clickable;

	this->beginCallBack = beginCallBack;
	this->endCallBack = endCallBack;
}

Scene::Scene(std::vector<Object2D*>& input_val, bool visiable, bool clickable, void (*beginCallBack)(), void (*endCallBack)()) {
	this->elements = std::vector<Object2D*>(input_val.begin(), input_val.end());
	this->visiable = visiable;
	this->clickable = clickable;
	this->beginCallBack = beginCallBack;
	this->endCallBack = endCallBack;
}

Scene::~Scene() {}



void Scene::addElement(Object2D* val) {
	this->elements.push_back(val);
}

void Scene::draw() {
	if (!visiable) return;
	for (Object2D* obj : this->elements) {
		obj->draw();
	}
}

void Scene::updateByTick() {
	if (pause) return;
	for (Object2D* obj : this->elements) {
		obj->update();
	}
}

void Scene::sceneBegin() {
	visiable = true;
	clickable = true;
	if (beginCallBack) {
		beginCallBack();
	}
};

void Scene::sceneEnd() {
	visiable = false;
	clickable = false;
	if (endCallBack) {
		endCallBack();
	}
};

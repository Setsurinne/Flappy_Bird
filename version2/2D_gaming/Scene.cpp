#include "Scene.h"

Scene::Scene() {
	this->visiable = false;
	this->updatable = false;
	this->clickable = false;
	this->beginCallBack = NULL;
	this->endCallBack = NULL;
};

Scene::Scene(Object2D* input_val, bool visiable, bool clickable, void (* beginCallBack)(), void (*endCallBack)()) {
	this->elements = std::vector<Object2D*>();
	elements.push_back(input_val);
	this->visiable = visiable;
	this->clickable = clickable;
	this->updatable = true;

	this->beginCallBack = beginCallBack;
	this->endCallBack = endCallBack;
}

Scene::Scene(std::vector<Object2D*>& input_val, bool visiable, bool clickable, void (*beginCallBack)(), void (*endCallBack)()) {
	this->elements = std::vector<Object2D*>(input_val.begin(), input_val.end());
	this->visiable = visiable;
	this->clickable = clickable;
	this->updatable = true;

	this->beginCallBack = beginCallBack;
	this->endCallBack = endCallBack;
}

Scene::~Scene() {}


void Scene::addElement(Object2D* val) {
	this->elements.push_back(val);
}

void Scene::setUpdatable(bool val) {
	this->updatable = val;
}

void Scene::setClickability(bool val) {
	this->clickable = val;
}

void Scene::setVisibility(bool val) {
	this->visiable = val;
}

bool Scene::isUpdatable() const {
	return this->updatable;
}

void Scene::draw() {
	if (!visiable) return;
	for (Object2D* obj : this->elements) {
		obj->draw();
	}
}

void Scene::updateByTick() {
	if (!isUpdatable()) return;
	for (Object2D* obj : this->elements) {
		obj->update();
	}
}


void Scene::leftButtonClick(const MOUSEMSG& msg) {
	if (!clickable) return;
	for (Object2D* obj : this->elements) {
		obj->receiveEvent(msg.x, msg.y);
	}
}

void Scene::sceneBegin() {
	visiable = true;
	clickable = true;
	updatable = true;
	if (beginCallBack) {
		beginCallBack();
	}
};

void Scene::sceneEnd() {
	visiable = false;
	clickable = false;
	updatable = false;
	if (endCallBack) {
		endCallBack();
	}
};


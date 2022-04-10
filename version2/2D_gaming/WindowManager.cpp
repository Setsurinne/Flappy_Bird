#include "WindowManager.h"


WindowManager::WindowManager(World& world) { this->WORLD = &world; }
WindowManager::~WindowManager() {};

void WindowManager::sendMessageTo() {};
void WindowManager::sendMessageToList() {};


void WindowManager::windowDraw() {
	BeginBatchDraw();
	for (Scene* ptr : scenes) {
		ptr->draw();
	}
	EndBatchDraw();
}

void WindowManager::windowUpdateByTick() {
	for (Scene* ptr : scenes) {
		ptr->updateByTick();
	}
}

void WindowManager::windowUserInput() {}


void WindowManager::windowLoop() {
	while (true) {
		windowUserInput();

		if (!WORLD->tick()) continue;
		windowUpdateByTick();
		windowDraw();
	}
}

const World* WindowManager::getWorld() const{
	return this->WORLD;
}

void WindowManager::addScene(Scene& scene) {
	scenes.push_back(&scene);
}
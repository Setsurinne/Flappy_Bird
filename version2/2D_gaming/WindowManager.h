#pragma once
#include "SceneCollidable.h"
#include "World.h"

class WindowManager
{
public:
	WindowManager(World& world);
	~WindowManager();
	
	void sendMessageTo();
	void sendMessageToList();

	void windowDraw();
	void windowUpdateByTick();
	virtual void windowUserInput();

	void windowLoop();
	const World* getWorld() const;
	void addScene(Scene&);
protected:
	std::vector<Scene*> scenes;
	World* WORLD;
};


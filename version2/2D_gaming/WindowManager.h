#pragma once
#include "SceneCollidable.h"
#include "World.h"

/// <summary>
/// A WindowManager managers a collections of Scenes, which should appears in one game window/stage
/// </summary>
class WindowManager
{
public:
	WindowManager(World& world);
	~WindowManager();
	
	void sendMessageTo();
	void sendMessageToList();


	/// <summary>
	/// Main Loop of the window, will update & draw the scenes by frame
	/// </summary>
	void windowLoop();

	/// <summary>
	/// Draw all Scenes
	/// </summary>
	void windowDraw();

	/// <summary>
	/// Update all Scenes by 
	/// </summary>
	void windowUpdateByTick();

	/// <summary>
	/// Handle user input
	/// </summary>
	virtual void windowUserInput();
	const World* getWorld() const;

	void addScene(Scene&);
protected:
	std::vector<Scene*> scenes;
	World* WORLD;
};


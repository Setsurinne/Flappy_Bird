#pragma once
#include "WindowManager.h"
#include "components.h"
#include <iostream>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// Flappy Bird window manager
class FBWindowManager : public WindowManager {

public:
	FBWindowManager(World&);
	~FBWindowManager();

	void initResources();
	void initValue();
	void windowUserInput();

private:
	// Call back functions
	void startGame();
	void flyBird();
	void restartGame();
	void updateScore();
	void birdCollision(Object2D&, Object2D&);

	// Resources
	Object2D* background;
	Ground* ground;
	Bird* bird;
	Score* score;

	Pipe* pipe_up_1;
	Pipe* pipe_up_2;
	Pipe* pipe_buttom_1;
	Pipe* pipe_buttom_2;
	std::vector<Pipe*> pipes;
	IMAGE pipe_img[4];

	Object2D* tutorial;
	Object2D* title;
	Object2D* button_play;
	Object2D* game_over;

	std::vector<Object2D*> resource_before;
	std::vector<Object2D*> resource_onplay;
	std::vector<Object2D*> resource_end;
	std::vector<Object2DPhysical*> resource_collidable;

	Scene scene_before;
	Scene scene_onplay;
	Scene scene_end;
	SceneCollidable scene_collidable;
};


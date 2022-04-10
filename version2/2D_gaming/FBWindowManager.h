#pragma once
#include "WindowManager.h"
#include "components.h"
class FBWindowManager : public WindowManager {

public:
	FBWindowManager(World&);
	~FBWindowManager();

	void initResources();
	void windowUserInput();

private:
	// Call back functions
	void startGame();
	void flyBird();
	void buttonClick();
	void birdCollision(Object2D&, Object2D&);
	void turnEnd();
	void turnStart();

	// Resources
	Object2D* background;
	Ground* ground;
	Bird* bird;
	Score* score;


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


#if 0
	// 2 pairs of pipes
	Pipe* pipe_up_1;
	Pipe* pipe_up_2;
	Pipe* pipe_buttom_1;
	Pipe* pipe_buttom_2;
	Pipe* pipe_pair[2][2];
	Pipe* pipes[4];
	IMAGE       pipe[4];
	int         pivot = 0;

	Score* score = new Score();

	Object2D* tutorial = new Object2D();
	Object2D* title = new Object2D();
	Object2D* button_play = new Object2D();
	Object2D* game_over = new Object2D();


	// Scenes
	std::vector<Object2D*> resource_before;
	std::vector<Object2D*> resource_onplay;
	std::vector<Object2D*> resource_end;

	Scene scene_before;
	Scene scene_onplay;
	Scene scene_end;
#endif
};


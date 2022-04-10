#include "FBWindowManager.h"
#include <iostream>


FBWindowManager::FBWindowManager(World& world) : WindowManager(world) {
	// Resources
	background		= new Object2D();
	ground			= new Ground();
	bird			= new Bird();
	score			= new Score();

	tutorial		= new Object2D();
	title			= new Object2D();
	game_over		= new Object2D();
	button_play		= new Object2D();

	resource_before = std::vector<Object2D*>{ title, tutorial };
	resource_onplay = std::vector<Object2D*>{ background, ground, bird, score};
	resource_end	= std::vector<Object2D*>{ game_over, button_play };
	resource_collidable = std::vector<Object2DPhysical*>{ ground, bird};

	scene_onplay	= Scene(resource_onplay, true, true);
	scene_before	= Scene(resource_before, true, false);
	scene_end		= Scene(resource_end, false, false);
	scene_collidable= SceneCollidable(resource_collidable, false, false);
	scene_collidable.setUpdatable(false);

	scenes = std::vector<Scene*>{ &scene_onplay, &scene_collidable, &scene_before, &scene_end};

	this->initResources();


#if 0
	// 2 pairs of pipes
	Pipe* pipe_up_1 = new Pipe(0);
	Pipe* pipe_up_2 = new Pipe(0);
	Pipe* pipe_buttom_1 = new Pipe(1);
	Pipe* pipe_buttom_2 = new Pipe(1);
	Pipe* pipe_pair[2][2] = { {pipe_up_1, pipe_buttom_1}, {pipe_up_2, pipe_buttom_2} };
	Pipe* pipes[4] = { pipe_up_1, pipe_buttom_1, pipe_up_2, pipe_buttom_2 };
	IMAGE       pipe[4];
	int         pivot = 0;

	Object2D* tutorial = new Object2D();
	Object2D* title = new Object2D();
	Object2D* button_play = new Object2D();
	Object2D* game_over = new Object2D();


	// Scenes
	std::vector<Object2D*> resource_onplay{ background, pipe_up_1, pipe_buttom_1, pipe_up_2, pipe_buttom_2, ground, bird, score };
	std::vector<Object2D*> resource_end{ button_play, game_over };
	std::vector<Object2D*> resource_before{ title, tutorial };

	Scene scene_onplay(resource_onplay, true, false);
	Scene scene_before(resource_before, true, true, NULL, NULL);
	Scene scene_end(resource_end, false, false, NULL, NULL);

#endif
}

FBWindowManager::~FBWindowManager() {}

void FBWindowManager::initResources() {
	// background
	background->loadImage(_T("img\\background.png"));
	background->setClickability(true);
	background->clickAction = [this]() {this->startGame();};

	// ground
	ground->loadImage(_T("img\\ground.png"));
	ground->setValue(0, 420, 0, 0, -3, 0);

	// bird
	for (int i = 0; i < 3; i++) {
		char address[30], mask_address[30];
		sprintf_s(address, "img\\bird\\bird_1_%d.png", i);
		sprintf_s(mask_address, "img\\bird\\bird_1_%d_mask.png", i);

		bird->loadImage(address, mask_address);
	}
	bird->setValue(30, 200);
	bird->setCollisionBoxHeight(bird->getHeight() * 0.6);
	bird->setCollisionBoxWidth(bird->getWidth() * 0.75);
	bird->setCollideAction([this](Object2D& obj1, Object2D& obj2) {this->birdCollision(obj1, obj2);});


	// score
	for (int i = 0; i < 10; i++) {
		char address[30], mask_address[30];
		sprintf_s(address, "img\\score\\%d.png", i);
		sprintf_s(mask_address, "img\\score\\%d_mask.png", i);
		score->loadImage(address, mask_address);
	}
	score->setValue(this->getWorld()->getWidth() / 2, 5);
	score->setPoint(0);
	score->setVisibility(false);

	// Texts
	title->loadImage(_T("img\\text\\title.png"), _T("img\\text\\title_mask.png"));
	tutorial->loadImage(_T("img\\text\\tutorial.png"), _T("img\\text\\tutorial_mask.png"));

	title->setValue((this->getWorld()->getWidth() - title->getWidth()) / 2, this->getWorld()->getHeight() * 0.1);
	tutorial->setValue((this->getWorld()->getWidth() - tutorial->getWidth()) / 2, this->getWorld()->getHeight() * 0.5);
}

void FBWindowManager::windowUserInput() {
	//std::cout << "check user input" << std::endl;
	MOUSEMSG msg = { 0 };
	if (MouseHit()) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN) {
			for (Scene* ptr : scenes) {
				ptr->leftButtonClick(msg);
			}
		}
	}
}

// Call back functions
void FBWindowManager::startGame() {
	this->scene_before.sceneEnd();
	this->bird->setAccY(1);
	this->score->setVisibility(true);
	this->background->clickAction = [this]() {this->flyBird();};
}


void FBWindowManager::turnEnd() {
	this->scene_end.sceneBegin();
}

void FBWindowManager::flyBird() {
	bird->setSpeedY(bird->SPEED_UP);
}


void FBWindowManager::birdCollision(Object2D& obj1, Object2D& obj2) {
	std::cout << "Collision" << std::endl;
	if (typeid(obj1) == typeid(Ground) || typeid(obj2) == typeid(Ground)) {
		std::cout << "ground col" << std::endl;
		scene_onplay.sceneEnd();
		scene_onplay.setVisibility(true);
	}

	if (typeid(obj1) == typeid(Pipe) || typeid(obj2) == typeid(Pipe)) {
		std::cout << "pipe col" << std::endl;
	}
}

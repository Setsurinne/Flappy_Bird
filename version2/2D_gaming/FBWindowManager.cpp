#include "FBWindowManager.h"


FBWindowManager::FBWindowManager(World& world) : WindowManager(world) {
	// Resources
	background		= new Object2D();
	ground			= new Ground();
	bird			= new Bird();
	score			= new Score();

	pipe_up_1		= new Pipe(0);
	pipe_up_2		= new Pipe(0);
	pipe_buttom_1	= new Pipe(1);
	pipe_buttom_2	= new Pipe(1);
	pipes			= std::vector<Pipe*>{ pipe_up_1, pipe_buttom_1, pipe_up_2, pipe_buttom_2 };

	tutorial		= new Object2D();
	title			= new Object2D();
	game_over		= new Object2D();
	button_play		= new Object2D();

	resource_before = std::vector<Object2D*>{ title, tutorial };
	resource_onplay = std::vector<Object2D*>{ background, pipe_up_1, pipe_up_2, pipe_buttom_1, pipe_buttom_2, ground, bird, score};
	resource_end	= std::vector<Object2D*>{ game_over, button_play };
	resource_collidable = std::vector<Object2DPhysical*>{ ground, bird, pipe_up_1, pipe_up_2, pipe_buttom_1, pipe_buttom_2 };

	scene_onplay	= Scene(resource_onplay, true, true);
	scene_before	= Scene(resource_before, true, false);
	scene_end		= Scene(resource_end, false, false);
	scene_collidable= SceneCollidable(resource_collidable, false, false);
	scene_collidable.setUpdatable(false);

	scenes = std::vector<Scene*>{ &scene_onplay, &scene_collidable, &scene_before, &scene_end};

	this->initResources();
}

FBWindowManager::~FBWindowManager() {}

void FBWindowManager::initResources() {
	// background
	background->loadImage(_T("img\\background.png"));

	// ground
	ground->loadImage(_T("img\\ground.png"));

	// bird
	for (int i = 0; i < 3; i++) {
		char address[30], mask_address[30];
		sprintf_s(address, "img\\bird\\bird_1_%d.png", i);
		sprintf_s(mask_address, "img\\bird\\bird_1_%d_mask.png", i);

		bird->loadImage(address, mask_address);
	}
	bird->setCollideAction([this](Object2D& obj1, Object2D& obj2) {this->birdCollision(obj1, obj2);});


	// score
	for (int i = 0; i < 10; i++) {
		char address[30], mask_address[30];
		sprintf_s(address, "img\\score\\%d.png", i);
		sprintf_s(mask_address, "img\\score\\%d_mask.png", i);
		score->loadImage(address, mask_address);
	}

	// Pipe
	pipe_buttom_1->pair = pipe_up_1;
	pipe_buttom_2->pair = pipe_up_2;
	pipe_buttom_1->updateAction = [this]() {this->updateScore();};
	pipe_buttom_2->updateAction = [this]() {this->updateScore();};

	loadimage(&pipe_img[0], _T("img\\pipe_green_top.png"));
	loadimage(&pipe_img[1], _T("img\\pipe_green_top_mask.png"));
	loadimage(&pipe_img[2], _T("img\\pipe_green_down.png"));
	loadimage(&pipe_img[3], _T("img\\pipe_green_down_mask.png"));
	Pipe* pipe_pair[2][2] = { {pipe_up_1, pipe_buttom_1}, {pipe_up_2, pipe_buttom_2} };
	for (Pipe** i : pipe_pair) {
		i[0]->useImage(&pipe_img[0], &pipe_img[1]);
		i[1]->useImage(&pipe_img[2], &pipe_img[3]);
	}

	// Texts
	title		->loadImage(_T("img\\text\\title.png"),				_T("img\\text\\title_mask.png"));
	tutorial	->loadImage(_T("img\\text\\tutorial.png"),			_T("img\\text\\tutorial_mask.png"));
	game_over	->loadImage(_T("img\\text\\text_game_over.png"),	_T("img\\text\\text_game_over_mask.png"));
	button_play	->loadImage(_T("img\\text\\button_play.png"),		_T("img\\text\\button_play_mask.png"));

	button_play->clickAction = [this]() {this->restartGame();};

	// BGM
	int rc = mciSendString("open sound\\bgm2.wav alias bgm TYPE MPEGVideo ", 0, 0, 0);
	rc = mciSendString("open sound\\jump.mp3 alias jump", 0, 0, 0);

	initValue();
}

void FBWindowManager::initValue() {
	background->setClickability(true);
	background->clickAction = [this]() {this->startGame();};

	ground->setValue(0, 420, 0, 0, -3, 0);
	ground->setPause(false);

	bird->setValue(30, 200);
	bird->setCollisionBoxHeight(bird->getHeight() * 0.6);
	bird->setCollisionBoxWidth(bird->getWidth() * 0.75);

	score->setValue(this->getWorld()->getWidth() / 2, 5);
	score->setPoint(0);
	score->setVisibility(false);

	int pivot = rand() % 250;
	pipe_up_1		->setValue(this->getWorld()->getWidth(), pivot - 305);
	pipe_buttom_1	->setValue(this->getWorld()->getWidth(), pivot + 165);
	pivot = rand() % 250;
	pipe_up_2		->setValue(this->getWorld()->getWidth() + 190, pivot - 305);
	pipe_buttom_2	->setValue(this->getWorld()->getWidth() + 190, pivot + 165);
	for (Pipe* p : pipes) {
		p->setCollidability(true);
		p->setPause(false);
	}

	title->setValue((this->getWorld()->getWidth() - title->getWidth()) / 2, this->getWorld()->getHeight() * 0.1);
	tutorial->setValue((this->getWorld()->getWidth() - tutorial->getWidth()) / 2, this->getWorld()->getHeight() * 0.5);
	button_play->setValue((this->getWorld()->getWidth() - button_play->getWidth()) / 2, this->getWorld()->getHeight() * 0.8);
	game_over->setValue((this->getWorld()->getWidth() - game_over->getWidth()) / 2, this->getWorld()->getHeight() * 0.1);
	button_play->setClickability(true);

	// BGM
	mciSendString("seek bgm to start", 0, 0, 0);
	mciSendString("play bgm repeat", 0, 0, 0);
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
	for (Pipe* pipe : pipes) {
		pipe->setSpeedX(-3);
	}
	this->score->setVisibility(true);
	this->background->clickAction = [this]() {this->flyBird();};
}


void FBWindowManager::restartGame() {
	this->initValue();
	scene_end.sceneEnd();
	scene_before.sceneBegin();
	scene_onplay.sceneBegin();
	scene_collidable.setCollidability(true);
}


void FBWindowManager::updateScore() {
	score->setPoint(score->getPoint() + 1);
}


void FBWindowManager::flyBird() {
	bird->setSpeedY(bird->SPEED_UP);
	mciSendString("seek jump to start", 0, 0, 0);           // Reset jump sound to begin
	mciSendString("play jump", 0, 0, 0);                    // Play jump sound
}


void FBWindowManager::birdCollision(Object2D& obj1, Object2D& obj2) {
	std::cout << "collision" << std::endl;

	if (typeid(obj1) == typeid(Ground) || typeid(obj2) == typeid(Ground)) {
		std::cout << "ground col" << std::endl;
		score->setY(250);
		scene_collidable.setCollidability(false);
		scene_onplay.sceneEnd();
		scene_onplay.setVisibility(true);
		scene_end.sceneBegin();
	}

	else if (typeid(obj1) == typeid(Pipe) || typeid(obj2) == typeid(Pipe)) {
		std::cout << "pipe col" << std::endl;
		bird->setSpeedY(bird->SPEED_UP / 2);
		scene_onplay.setClickability(false);
		for (Pipe* p : pipes) {
			p->setCollidability(false);
			p->setPause(true);
		}
		ground->setPause(true);
	}
}

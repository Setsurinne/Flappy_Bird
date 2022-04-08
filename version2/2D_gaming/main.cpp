#include "Scene.h"
#include "components.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

bool GAME_START = false;
bool GAME_END = false;

void gameInitResource();
void gameInitValue();
void gameUpdate();
void gameClick();
void gameDraw();

void buttonClick();
void backgroundClick();

void turnStart();
void turnEnd();
void turnRestart();

// Time
unsigned long   time1, time2;
int             FPS = 60;

// Resources
Object2D*   background      = new Object2D();
Ground*     ground          = new Ground();
Bird*       bird            = new Bird();

// 2 pairs of pipes
Pipe*       pipe_up_1       = new Pipe(0);
Pipe*       pipe_up_2       = new Pipe(0);
Pipe*       pipe_buttom_1   = new Pipe(1);
Pipe*       pipe_buttom_2   = new Pipe(1);
Pipe*       pipe_pair[2][2] = { {pipe_up_1, pipe_buttom_1}, {pipe_up_2, pipe_buttom_2} };
Pipe*       pipes[4]        = { pipe_up_1, pipe_buttom_1, pipe_up_2, pipe_buttom_2 };
IMAGE       pipe[4];
int         pivot           = 0;

Score*      score           = new Score();

Object2D*   tutorial        = new Object2D();
Object2D*   title           = new Object2D();
Object2D*   button_play     = new Object2D();
Object2D*   game_over       = new Object2D();


// Scenes
std::vector<Object2D*> resource_onplay  { background, pipe_up_1, pipe_buttom_1, pipe_up_2, pipe_buttom_2, ground, bird, score};
std::vector<Object2D*> resource_end     { button_play, game_over };
std::vector<Object2D*> resource_before  { title, tutorial };

Scene scene_onplay(resource_onplay, true, false);
Scene scene_before(resource_before, true, true, NULL, turnStart);
Scene scene_end(resource_end, false, false, turnEnd, turnRestart);

void buttonClick() {
    scene_end.sceneEnd();
}

void backgroundClick() {
    scene_before.sceneEnd();
    if (!GAME_START) {
        GAME_START = true;
    }
    else {
        bird->setSpeedY(bird->SPEED_UP);
        mciSendString("seek jump to start", 0, 0, 0);           // Reset jump sound to begin
        mciSendString("play jump", 0, 0, 0);                    // Play jump sound
    }
}

void turnStart() {
    bird->setAccY(1);
    score->setVisibility(true);
    for (Pipe* pipe : pipes) {
        pipe->setSpeedX(-3);
    }
}

void turnEnd() {
    GAME_END = true;
    score->setY(250);
    for (Pipe* pipe : pipes) {
        pipe->setPause(true);
        pipe->setCollidability(false);
    }
    ground->setPause(true);
}


void turnRestart() {
    GAME_END = false;
    GAME_START = false;
    gameInitValue();
    scene_before.sceneBegin();
}

void gameInitResource() {
    // Background
    background->setClickability(true);
    background->clickAction = backgroundClick;
    background->loadImage(_T("img\\background.png"));


    // Initiate the graph
    initgraph(background->getWidth(), background->getHeight(), 1);


    // Ground
    ground->loadImage(_T("img\\ground.png"));

    // Bird
    for (int i = 0; i < 3; i++) {
        char address[30], mask_address[30];
        sprintf_s(address,      "img\\bird\\bird_1_%d.png", i);
        sprintf_s(mask_address, "img\\bird\\bird_1_%d_mask.png", i);

        bird->loadImage(address, mask_address);
    }

    // Pipe
    loadimage(&pipe[0], _T("img\\pipe_green_top.png"));
    loadimage(&pipe[1], _T("img\\pipe_green_top_mask.png"));
    loadimage(&pipe[2], _T("img\\pipe_green_down.png"));
    loadimage(&pipe[3], _T("img\\pipe_green_down_mask.png"));
    for (Pipe** i : pipe_pair) {
        i[0]->useImage(&pipe[0], &pipe[1]);
        i[1]->useImage(&pipe[2], &pipe[3]);
    }

    // score
    for (int i = 0; i < 10; i++) {
        char address[30], mask_address[30];
        sprintf_s(address,      "img\\score\\%d.png", i);
        sprintf_s(mask_address, "img\\score\\%d_mask.png", i);
        score->loadImage(address, mask_address);
    }


    // Texts
    title       ->  loadImage(_T("img\\text\\title.png"),           _T("img\\text\\title_mask.png"));
    tutorial    ->  loadImage(_T("img\\text\\tutorial.png"),        _T("img\\text\\tutorial_mask.png"));
    game_over   ->  loadImage(_T("img\\text\\text_game_over.png"),  _T("img\\text\\text_game_over_mask.png"));
    button_play ->  loadImage(_T("img\\text\\button_play.png"),     _T("img\\text\\button_play_mask.png"));
    button_play ->  clickAction = buttonClick;
    button_play ->  setClickability(true);

    // BGM
    int rc = mciSendString("open sound\\bgm2.wav alias bgm TYPE MPEGVideo ", 0, 0, 0);
    rc = mciSendString("open sound\\jump.mp3 alias jump", 0, 0, 0);
}


void gameInitValue() {
    srand(time(0));

    // Ground
    ground->setValue(0, 420, 0, 0, -3, 0);
    ground->setPause(false);

    // Bird
    bird->setValue(30, 200, 0, 0);
    bird->setCollisionBoxHeight(bird->getHeight() * 0.6);
    bird->setCollisionBoxWidth(bird->getWidth() * 0.75);

    // Score
    score->setValue(background->getWidth() / 2, 5);
    score->setPoint(0);
    score->setVisibility(false);

    // Pipe
    pivot = rand() % 250;
    pipe_pair[0][0]->setValue(background->getWidth(),       pivot - 305);
    pipe_pair[0][1]->setValue(background->getWidth(),       pivot + 165);

    pivot = rand() % 250;
    pipe_pair[1][0]->setValue(background->getWidth() + 190, pivot - 305);
    pipe_pair[1][1]->setValue(background->getWidth() + 190, pivot + 165);

    for (Pipe* pipe : pipes) {
        pipe->setPause(false);
        pipe->setCollidability(true);
    }

    // Texts
    tutorial    ->setValue((background->getWidth() - tutorial   ->getWidth())/ 2, background->getHeight() * 0.5);
    title       ->setValue((background->getWidth() - title      ->getWidth())/ 2, background->getHeight() * 0.1);
    button_play ->setValue((background->getWidth() - button_play->getWidth())/ 2, background->getHeight() * 0.8);
    game_over   ->setValue((background->getWidth() - game_over  ->getWidth())/ 2, background->getHeight() * 0.1);

    // Time
    time1 = GetTickCount();
    time2 = GetTickCount();

    // BGM
    mciSendString("seek bgm to start", 0, 0, 0);
    mciSendString("play bgm repeat", 0, 0, 0);

}


void gameDraw() {
    BeginBatchDraw();                                               // Start drawing
    scene_onplay.draw();
    scene_before.draw();
    scene_end.draw();
    EndBatchDraw();
}


void gameClick() {
    MOUSEMSG msg = { 0 };
    if (MouseHit()) {
        msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN) {
            if (GAME_END) {
                button_play->receiveEvent(msg.x, msg.y);
            }
            else {
                background->clickAction();
            }
        }
    }
}


void gameUpdate() {
    // Player update
    gameClick();

    // Update by frame
    time2 = GetTickCount();
    if ((int) time2 - time1 > 1000 / FPS) {
        scene_onplay.updateByTick();
        scene_before.updateByTick();
        scene_end.updateByTick();
        
        time1 = time2;
    }

    // Check collision
    if (bird->collision(*ground)) {
        scene_end.sceneBegin();
    }

    for (Pipe* i : pipes) {
        if (bird->collision(*i)) {
            bird->setSpeedY(bird->SPEED_UP / 2);
            scene_end.sceneBegin();
            break;
        }
    }
}


int main() {
    gameInitResource();
    gameInitValue();

    while (1) {
        gameDraw();
        gameUpdate();
    }

    closegraph();
    return EXIT_SUCCESS;
}
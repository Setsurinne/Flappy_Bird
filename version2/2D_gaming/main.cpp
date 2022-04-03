#include "object.h"
#include "components.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// Time
unsigned long time1, time2;
int FPS = 60;

// Resources
std::vector<object2D*> resources;
object2D* background = new object2D();
Ground* ground = new Ground();
Bird* bird = new Bird();

Pipe* pipe_up_1 = new Pipe(0);
Pipe* pipe_up_2 = new Pipe(0);
Pipe* pipe_buttom_1 = new Pipe(1);
Pipe* pipe_buttom_2 = new Pipe(1);
Pipe* pipe_pair[2][2] = { {pipe_up_1, pipe_buttom_1}, {pipe_up_2, pipe_buttom_2} };
IMAGE pipe[4];

Score* score = new Score();

void gameInitResource() {
    // Background
    background->loadImage(_T("img\\background.png"));
    // Initiate the graph
    initgraph(background->getWidth(), background->getHeight(), 1);


    // Ground
    ground->loadImage(_T("img\\ground.png"));

    // Bird
    for (int i = 0; i < 3; i++) {
        char address[30], mask_address[30];
        sprintf_s(address, "img\\bird\\bird_1_%d.png", i);
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
        sprintf_s(address, "img\\score\\%d.png", i);
        sprintf_s(mask_address, "img\\score\\%d_mask.png", i);
        score->loadImage(address, mask_address);
    }

    // Push resources to the vector to draw&update together
    resources.push_back(background);
    for (Pipe** i : pipe_pair) {
        resources.push_back(i[0]);
        resources.push_back(i[1]);
    }
    resources.push_back(ground);
    resources.push_back(bird);
    resources.push_back(score);

    // BGM
    int rc = mciSendString("open sound\\bgm2.wav alias bgm TYPE MPEGVideo ", 0, 0, 0);
    rc = mciSendString("play bgm repeat", 0, 0, 0);
    rc = mciSendString("open sound\\jump.mp3 alias jump", 0, 0, 0);
}


void gameInitValue() {
    srand(time(0));
    ground->setValue(0, 420, 0, 0, -3, 0);
    bird->setValue(30, 200, 0, 1);
    score->setValue(background->getWidth() / 2, 5);
    pipe_pair[0][0]->setValue(background->getWidth(), rand() % 250 - 305, 0, 0, -3, 0);
    pipe_pair[0][1]->setValue(background->getWidth(), pipe_pair[0][0]->getY() + 305 + 165, 0, 0, -3, 0);
    pipe_pair[1][0]->setValue(background->getWidth() + 190, rand() % 250 - 305, 0, 0, -3, 0);
    pipe_pair[1][1]->setValue(background->getWidth() + 190, pipe_pair[1][0]->getY() + 305 + 165, 0, 0, -3, 0);

    // Time
    time1 = GetTickCount();
    time2 = GetTickCount();
}


void gameDraw() {
    BeginBatchDraw();                                               // Start drawing

    for (object2D* ptr : resources) {
        ptr->draw();
    }

    EndBatchDraw();
}

void gameUpdate() {
    // Player update
    MOUSEMSG msg = { 0 };
    if (MouseHit()) {
        msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN) {
            bird->setSpeedY(bird->SPEED_UP);
            mciSendString("seek jump to start", 0, 0, 0);           // Reset jump sound to begin
            mciSendString("play jump", 0, 0, 0);                    // Play jump sound
        }
    }


    time2 = GetTickCount();
    if (time2 - time1 <= 1000 / FPS) {
        return;
    }
    for (object2D* ptr : resources) {
        ptr->update();
    }
    time1 = time2;
}

int main() {
    gameInitResource();
    gameInitValue();
    while (1) {
        gameDraw();
        gameUpdate();
    }
}
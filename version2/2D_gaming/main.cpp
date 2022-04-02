#ifndef object2D_H
#ifndef component_H
#define object2D_H
#define component_H

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

void gameInitResource() {
    background->loadImage(_T("img\\background.png"));
    ground->loadImage(_T("img\\ground.png"));
    for (int i = 0; i < 3; i++) {
        char address[30], mask_address[30];

        sprintf_s(address, "img\\bird\\bird_1_%d.png", i);
        sprintf_s(mask_address, "img\\bird\\bird_1_%d_mask.png", i);

        bird->loadImage(address, mask_address);
    }

    initgraph(background->getWidth(), background->getHeight(), 1);
    resources.push_back(background);
    resources.push_back(ground);
    resources.push_back(bird);

    int rc = mciSendString("open sound\\bgm2.wav alias bgm TYPE MPEGVideo ", 0, 0, 0);
    rc = mciSendString("play bgm repeat", 0, 0, 0);
    rc = mciSendString("open sound\\jump.mp3 alias jump", 0, 0, 0);
}


void gameInitValue() {
    ground->setValue(0, 420, 0, 0, -3, 0);
    bird->setValue(30, 200, 0, 1, 0, 0);

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

#endif
#endif
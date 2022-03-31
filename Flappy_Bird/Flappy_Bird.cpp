﻿// Flappy_Bird.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <easyx.h>
#include <graphics.h>
#include <iostream>
#include <stdio.h>
#include <string> 
#include <string.h>
#include <algorithm>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// Resources
#define PI 3.14159265359
bool GAME_START = FALSE;        // To check if game has started, i.e. a mouse click happened
bool GAME_END = FALSE;          // To check if game has end, i.e. a collision occured

// Window


// Background
IMAGE  background;

// Ground
struct Ground
{
    int x = 0;
    int y = 420;
    int speed = 2;
    IMAGE image;
} ground;


// Time
unsigned long time1, time2;
int FPS = 60;


// Bird
typedef struct Bird
{
    int x = 20;
    int y = 200;
    int size_x = 0;
    int size_y = 0;
    int speed = 0;
    int frame = 0;
    int g = 0;
    int num_image = 3;
    IMAGE image[3];
    IMAGE image_rotated[3];
};
int SPEED_UP = -12;
int G = 1;
Bird bird;


// Pipe
typedef struct Pipe
{
    int x[2];
    int y[2];
    int size_x[2];
    int size_y[2];
    int offset[2];
    int speed = 0;
    IMAGE image[2];
};
int SPEED_PIPE = 2;
Pipe pipe_green;


// Score
struct Score
{
    int point = 0;
    IMAGE image[10];
} score;



void gameInit() {
    srand(time(0));

    // BGM
    int rc = mciSendString("open sound\\bgm2.wav alias bgm TYPE MPEGVideo ", 0, 0, 0);
    rc = mciSendString("play bgm repeat", 0, 0, 0);
    rc = mciSendString("open sound\\jump.mp3 alias jump", 0, 0, 0);

    // Background
    loadimage(&background, "img\\background.png");
    int WIDTH = background.getwidth();
    int HEIGHT = background.getheight();

    // Window
    initgraph(WIDTH, HEIGHT, 1);

    // Ground
    loadimage(&ground.image, "img/ground.png");

    // Time
    time1 = GetTickCount();
    time2 = GetTickCount();

    // Bird
    loadimage(&bird.image[0], "img/bird_1_0.png");
    loadimage(&bird.image_rotated[0], "img/bird_1_0.png");
    loadimage(&bird.image[1], "img/bird_1_1.png");
    loadimage(&bird.image_rotated[1], "img/bird_1_1.png");
    loadimage(&bird.image[2], "img/bird_1_2.png");
    loadimage(&bird.image_rotated[2], "img/bird_1_2.png");
    bird.size_x = bird.image[0].getwidth() * 0.8;
    bird.size_y = bird.image[0].getheight() * 0.8;

    // Pipe
    loadimage(&pipe_green.image[0], "img/pipe_green_top.png");
    loadimage(&pipe_green.image[1], "img/pipe_green_down.png");
    pipe_green.x[0] = WIDTH;
    pipe_green.x[1] = WIDTH + 190;
    pipe_green.y[0] = rand() % 250;
    pipe_green.y[1] = rand() % 250;
    pipe_green.size_x[0] = pipe_green.image[0].getwidth();
    pipe_green.size_y[0] = pipe_green.image[0].getheight();
    pipe_green.size_x[1] = pipe_green.image[1].getwidth();
    pipe_green.size_y[1] = pipe_green.image[1].getheight();
    pipe_green.offset[0] = -305;
    pipe_green.offset[1] = 165;

    // score
    for (int i = 0; i < 10; i++) {
        char address[20];
        sprintf_s(address, "img\\score\\%d.png", i);
        loadimage(&score.image[i], address);
    }
};


void gameDraw() {
    BeginBatchDraw();                                               // Start drawing
    putimage(0, 0, &background);

    for (int i = 0; i < 2; i++) {
        putimage(pipe_green.x[i], pipe_green.y[i] + pipe_green.offset[0], &pipe_green.image[0]);        // Put upper pipe
        putimage(pipe_green.x[i], pipe_green.y[i] + pipe_green.offset[1], &pipe_green.image[1]);        // Put buttom pipe
    }

    putimage(ground.x, ground.y, &ground.image);

    putimage(bird.x, bird.y, &bird.image_rotated[bird.frame]);

    std::string credit = std::to_string(score.point);                                                   // Put score
    for (int i = 0; i < credit.size(); i++) {
        putimage(background.getwidth() / 2 - ((int)credit.size() / 2 - i + 0.5) * score.image[0].getwidth(),
                5,
                &score.image[credit[i] - 48]
        );
    }

    EndBatchDraw();                                                 // End drawing
};


void gameUpdate() {
    // Player update
    MOUSEMSG msg = { 0 };
    if (!GAME_END && MouseHit()) {
        msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN) {
            if (!GAME_START) {                                          // First-time click ==> Start play
                GAME_START = TRUE;
                bird.g = G;
                pipe_green.speed = SPEED_PIPE;
            }
            else {
                bird.speed = SPEED_UP;

                mciSendString("seek jump to start", 0, 0, 0);           // Reset jump sound to begin
                mciSendString("play jump", 0, 0, 0);                    // Play jump sound
            }
        }
    }



    // Automatically update each frame
    time2 = GetTickCount();
    while ((int)time2 - time1 > 1000 / FPS) {

        // Bird speed & location
        // Bird will always fall, until reach the ground
        if (bird.y + bird.size_y < ground.y) {
            bird.y += bird.speed;
            bird.speed += bird.g;
        }
        else {
            GAME_END = TRUE;
        }

        if (GAME_END) {
            time1 = time2;
            break;
        }

        // Bird frame
        if (++bird.frame >= 3) {
            bird.frame = 0;
        }


        // Bird rotation
        float angle = 0;
        if (bird.speed != 0) {
            angle = PI / 3 * max(-1, (float)bird.speed / SPEED_UP);
        }
        else if (bird.speed < 0) {
            angle = PI / 3.5 * ((float) bird.speed / SPEED_UP);
        }
        for (int i = 0; i < bird.num_image; i++) {
            rotateimage(&bird.image_rotated[i], &bird.image[i], angle);
        }


        // Bird collision with pipe
        for (int i = 0; i < 2; i++) {
            if (bird.x + bird.image[0].getwidth() * 0.1 <= pipe_green.x[i] + pipe_green.size_x[i] &&
                bird.x + bird.size_x >= pipe_green.x[i] &&
                    (   bird.y + bird.image[0].getheight() * 0.1 <= pipe_green.y[i] + pipe_green.offset[0] + pipe_green.size_y[0] ||
                        bird.y + bird.size_y >= pipe_green.y[i] + pipe_green.offset[1]
                    )
                ) {

#if 0
                std::cout << bird.y << ' ' << pipe_green.y[0] << ' ' << pipe_green.size_y[0] << std::endl;
                std::cout << "collision" << std::endl;
#endif
                bird.speed = SPEED_UP / 2;              // Add a little jump as ending scene
                GAME_END = TRUE;
            }
        }


        // Update ground
        if (ground.x < -20) {                                       // Reset ground
            ground.x = 0;
        }
        else {
            ground.x -= ground.speed;
        }


        // Pipe
        for (int i = 0; i < 2; i++) {
            pipe_green.x[i] -= pipe_green.speed;
            if (pipe_green.x[i] < -52) {
                int j = i;
                if (++j > 1) {
                    j = 0;
                }
                pipe_green.x[i] = pipe_green.x[j] + 190;
                pipe_green.y[i] = rand() % 250;                     // Reset pipe location
                score.point += 1;                                   // Update score
            }
        }
        time1 = time2;
    }

};

int main()
{   
    gameInit();

    while (1) {
        gameDraw();
        gameUpdate();
    }

    closegraph();
    return EXIT_SUCCESS;
}




// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

// Flappy_Bird.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <easyx.h>
#include <graphics.h>
#include <iostream>
#include <stdio.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// Resources
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
    int speed = 0;
    int frame = 0;
    int g = 1;
    IMAGE image[3];
};

Bird bird;

// Pipe
typedef struct Pipe
{
    int x1, y1, x2, y2;
    int speed = 2;
    IMAGE image[2];
};

Pipe pipe_green;


// Score




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
    initgraph(WIDTH, HEIGHT);

    // Ground
    loadimage(&ground.image, "img/ground.png");

    // Time
    time1 = GetTickCount();
    time2 = GetTickCount();

    // Bird
    loadimage(&bird.image[0], "img/bird_1_0.png");
    loadimage(&bird.image[1], "img/bird_1_1.png");
    loadimage(&bird.image[2], "img/bird_1_2.png");

    // Pipe
    loadimage(&pipe_green.image[0], "img/pipe_green_top.png");
    loadimage(&pipe_green.image[1], "img/pipe_green_down.png");
    pipe_green.x1 = WIDTH;
    pipe_green.x2 = WIDTH + 190;
    pipe_green.y1 = rand() % 250;
    pipe_green.y2 = rand() % 250;

};


void gameDraw() {
    BeginBatchDraw();                                               // Start drawing
    putimage(0, 0, &background);

    putimage(bird.x, bird.y, &bird.image[bird.frame]);

    putimage(pipe_green.x1, pipe_green.y1 - 300, &pipe_green.image[0]);
    putimage(pipe_green.x1, pipe_green.y1 + 160, &pipe_green.image[1]);
    putimage(pipe_green.x2, pipe_green.y2 - 300, &pipe_green.image[0]);
    putimage(pipe_green.x2, pipe_green.y2 + 160, &pipe_green.image[1]);

    putimage(ground.x, ground.y, &ground.image);

    EndBatchDraw();                                                 // End drawing
};


void gameUpdate() {
    // Player update
    MOUSEMSG msg = { 0 };
    if (MouseHit()) {
        msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN) {
            bird.speed = -12;

            mciSendString("seek jump to start", 0, 0, 0);           // Reset jump sound to begin
            mciSendString("play jump", 0, 0, 0);                    // Play jump sound
        }
    }



    // Automatically update each frame
    time2 = GetTickCount();
    if (time2 - time1 > 1000 / FPS) {


        // Update ground
        if (ground.x < -20) {
            ground.x = 0;
        }
        else {
            ground.x -= ground.speed;
        }
        

        // Bird frame
        if (++bird.frame >= 3) {
            bird.frame = 0;
        }

        // Bird speed & location
        bird.y += bird.speed;
        bird.speed += bird.g;

        // Pipe
        pipe_green.x1 -= pipe_green.speed;
        pipe_green.x2 -= pipe_green.speed;

        if (pipe_green.x1 < -52) {
            pipe_green.x1 = pipe_green.x2 + 190;
            pipe_green.y1 = rand() % 250;                   // Reset pipe location
        }
        if (pipe_green.x2 < -52) {
            pipe_green.x2 = pipe_green.x1 + 190;
            pipe_green.y2 = rand() % 250;
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

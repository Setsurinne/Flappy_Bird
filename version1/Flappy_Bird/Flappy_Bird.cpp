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
int WIDTH = 0;
int HEIGHT = 0;

// Background
IMAGE  background;

// Ground
struct Ground
{
    int x = 0;
    int y = 420;
    int speed = 3;
    IMAGE image;
} ground;


// Time
unsigned long time1, time2;
int FPS = 60;


// Bird
typedef struct Bird
{
    int x = 30;
    int y = 200;
    int size_x = 0;
    int size_y = 0;
    int speed = 0;
    int frame = 0;
    int g = 0;
    int num_image = 3;
    IMAGE image[3][2];
    IMAGE image_rotated[3][2];
};
int SPEED_UP = -12;
int G = 1;
Bird bird;


// Pipe
// Two pair of pipes, each pair combines the top one and the buttom one
typedef struct Pipe
{
    int x[2] = {0, 0};
    int y[2] = { 0, 0 };
    int size_x[2] = { 0, 0 };
    int size_y[2] = { 0, 0 };
    int offset[2] = { 0, 0 };           // To decide the distence between the top one and the buttom one
    int speed = 0;
    IMAGE image[2];
    IMAGE mask[2];
};
int SPEED_PIPE = 3;
Pipe pipe_green;


// Score
struct Score
{
    int point = 0;
    int y = 5;
    IMAGE image[10];
    IMAGE mask[10];
} score;


// Text
typedef struct Text {
    int x = 0;
    int y = 0;
    //bool display = true;
    IMAGE image = NULL;
    IMAGE mask = NULL;
};
Text game_over;
Text tutorial;
Text title;
Text button_play;


void gameInitResource() {
    // BGM
    int rc = mciSendString("open sound\\bgm2.wav alias bgm TYPE MPEGVideo ", 0, 0, 0);
    rc = mciSendString("play bgm repeat", 0, 0, 0);
    rc = mciSendString("open sound\\jump.mp3 alias jump", 0, 0, 0);

    // Background
    loadimage(&background, "img\\background.png");
    WIDTH = background.getwidth();
    HEIGHT = background.getheight();

    // Window
    initgraph(WIDTH, HEIGHT, 1);

    // Ground
    loadimage(&ground.image, "img/ground.png");

    // Bird
    for (int i = 0; i < 3; i++) {
        char address[30];

        sprintf_s(address, "img\\bird\\bird_1_%d.png", i);
        loadimage(&bird.image[i][0], address);
        loadimage(&bird.image_rotated[i][0], address);

        sprintf_s(address, "img\\bird\\bird_1_%d_mask.png", i);
        loadimage(&bird.image[i][1], address);
        loadimage(&bird.image_rotated[i][1], address);
    }


    // Pipe
    loadimage(&pipe_green.image[0], "img/pipe_green_top.png");
    loadimage(&pipe_green.mask[0], "img/pipe_green_top_mask.png");
    loadimage(&pipe_green.image[1], "img/pipe_green_down.png");
    loadimage(&pipe_green.mask[1], "img/pipe_green_down_mask.png");


    // score
    for (int i = 0; i < 10; i++) {
        char address[30];

        sprintf_s(address, "img\\score\\%d.png", i);
        loadimage(&score.image[i], address);

        sprintf_s(address, "img\\score\\%d_mask.png", i);
        loadimage(&score.mask[i], address);
    }


    // text
    loadimage(&game_over.image, "img\\text\\text_game_over.png");
    loadimage(&game_over.mask, "img\\text\\text_game_over_mask.png");

    loadimage(&tutorial.image, "img\\text\\tutorial.png");
    loadimage(&tutorial.mask, "img\\text\\tutorial_mask.png");

    loadimage(&button_play.image, "img\\text\\button_play.png");
    loadimage(&button_play.mask, "img\\text\\button_play_mask.png");

    loadimage(&title.image, "img\\text\\title.png");
    loadimage(&title.mask, "img\\text\\title_mask.png");
};


void gameInitValue() {
    srand(time(0));

    GAME_START = FALSE;
    GAME_END = FALSE;

    // score
    score.point = 0;
    score.y = 5;

    // pipe
    pipe_green.speed = 0;
    pipe_green.x[0] = ground.image.getwidth();
    pipe_green.x[1] = ground.image.getwidth() + 190;
    pipe_green.y[0] = rand() % 250;
    pipe_green.y[1] = rand() % 250;
    pipe_green.offset[0] = -305;
    pipe_green.offset[1] = 165;
    pipe_green.size_x[0] = pipe_green.image[0].getwidth();
    pipe_green.size_y[0] = pipe_green.image[0].getheight();
    pipe_green.size_x[1] = pipe_green.image[1].getwidth();
    pipe_green.size_y[1] = pipe_green.image[1].getheight();

    // bird
    bird.x = 30;
    bird.y = 200;
    bird.g = 0;
    bird.speed = 0;
    bird.frame = 0;
    bird.size_x = bird.image[0][0].getwidth() * 0.8;
    bird.size_y = bird.image[0][0].getheight() * 0.8;

    // Time
    time1 = GetTickCount();
    time2 = GetTickCount();

    // Text
    button_play.x = (WIDTH - button_play.image.getwidth()) / 2;
    button_play.y = HEIGHT * 0.8;
    tutorial.x = (WIDTH - tutorial.image.getwidth()) / 2;
    tutorial.y = HEIGHT * 0.5;
    title.x = (WIDTH - title.image.getwidth()) / 2;
    title.y = HEIGHT * 0.1;
    game_over.x = (WIDTH - game_over.image.getwidth()) / 2;
    game_over.y = HEIGHT * 0.1;
}

void gameDraw() {
    BeginBatchDraw();                                               // Start drawing
    putimage(0, 0, &background);


    // Put mask first with AND operation ==> Will make whiet area transparent and leave central black area
    // Put the original graph with OR operation ==> Will overlay the black area
    for (int i = 0; i < 2; i++) {
        putimage(pipe_green.x[i], pipe_green.y[i] + pipe_green.offset[0], &pipe_green.mask[0], SRCAND);         // Put upper pipe
        putimage(pipe_green.x[i], pipe_green.y[i] + pipe_green.offset[0], &pipe_green.image[0], SRCPAINT);        
        putimage(pipe_green.x[i], pipe_green.y[i] + pipe_green.offset[1], &pipe_green.mask[1], SRCAND);         // Put buttom pipe
        putimage(pipe_green.x[i], pipe_green.y[i] + pipe_green.offset[1], &pipe_green.image[1], SRCPAINT);        
    }

    putimage(ground.x, ground.y, &ground.image);

    putimage(bird.x, bird.y, &bird.image_rotated[bird.frame][1], SRCAND);
    putimage(bird.x, bird.y, &bird.image_rotated[bird.frame][0], SRCPAINT);


    if (GAME_START) {                                                                                           // Put score
        std::string credit = std::to_string(score.point);
        for (int i = 0; i < credit.size(); i++) {
            putimage(background.getwidth() / 2 - ((int)credit.size() / 2 - i + 0.5) * score.mask[0].getwidth(),
                score.y,
                &score.mask[credit[i] - 48],
                SRCAND
            );

            putimage(background.getwidth() / 2 - ((int)credit.size() / 2 - i + 0.5) * score.image[0].getwidth(),
                score.y,
                &score.image[credit[i] - 48],
                SRCPAINT
            );
        }
    }



    // Text
    if (!GAME_START) {
        putimage(tutorial.x, tutorial.y, &tutorial.mask, SRCAND);
        putimage(tutorial.x, tutorial.y, &tutorial.image, SRCPAINT);

        putimage(title.x, title.y, &title.mask, SRCAND);
        putimage(title.x, title.y, &title.image, SRCPAINT);
    }
    if (GAME_END) {
        putimage(button_play.x, button_play.y, &button_play.mask, SRCAND);
        putimage(button_play.x, button_play.y, &button_play.image, SRCPAINT);

        putimage(game_over.x, game_over.y, &game_over.mask, SRCAND);
        putimage(game_over.x, game_over.y, &game_over.image, SRCPAINT);
    }


    EndBatchDraw();                                                 // End drawing
};


void gameUpdate() {
    // Player update
    MOUSEMSG msg = { 0 };
    if (MouseHit()) {
        msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN) {
            if (!GAME_START) {                                          // First-time click ==> Start play
                GAME_START = TRUE;
                bird.g = G;
                pipe_green.speed = SPEED_PIPE;
            }
            else if (GAME_END) {                                        // Restart the game
                if ((msg.x > button_play.x && msg.x < button_play.x + button_play.image.getwidth()) && 
                    (msg.y > button_play.y && msg.y < button_play.y + button_play.image.getheight())) {

                    gameInitValue();
                    mciSendString("seek bgm to start", 0, 0, 0);
                    mciSendString("play bgm repeat", 0, 0, 0);
                }
            }
            else {
                bird.speed = SPEED_UP;
                mciSendString("seek jump to start", 0, 0, 0);           // Reset jump sound to begin
                mciSendString("play jump", 0, 0, 0);                    // Play jump sound
            }
        }
    }



    // Automatically update during each frame
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
            score.y = HEIGHT * 0.6;                                 // Put the socre in the middle of the screen
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
            rotateimage(&bird.image_rotated[i][0], &bird.image[i][0], angle);
            rotateimage(&bird.image_rotated[i][1], &bird.image[i][1], angle, WHITE);            // Rotate and set background color as white
        }


        // Bird collision with pipe
        for (int i = 0; i < 2; i++) {
            if (bird.x + bird.image[0][0].getwidth() * 0.1 <= pipe_green.x[i] + pipe_green.size_x[i] &&
                bird.x + bird.size_x >= pipe_green.x[i] &&
                    (   bird.y + bird.image[0][0].getheight() * 0.1 <= pipe_green.y[i] + pipe_green.offset[0] + pipe_green.size_y[0] ||
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
    gameInitResource();
    gameInitValue();

    while (1) {
        gameDraw();
        gameUpdate();
    }

    closegraph();
    return EXIT_SUCCESS;
}

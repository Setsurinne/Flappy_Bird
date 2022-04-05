#include "components.h"

extern bool GAME_START;
extern bool GAME_END;
extern int pivot;
bool update_score = false;

//---------------------------------------------------------------------------------------
// Ground
Ground::Ground() : Object2DPhysical() {}
void Ground::update() { 
#if 0
    std::cout << "ground update" << getX() << std::endl;
#endif
    if (GAME_END) return;

    if (getX() < -20) {                                       // Reset ground
        setX(0);
    }
    else {
        Object2DPhysical::update();
    }
}

//---------------------------------------------------------------------------------------
// Bird
Bird::Bird() : Object2DPhysical() {}

void Bird::update() {
    Object2DPhysical::update();

    if (GAME_END) return;
    int PI = 3.14159265359;
    float angle = 0;

    if (getSpeedY() != 0) {
        angle = PI / 3 * max(-1, (float)getSpeedY() / SPEED_UP);
    }
    else if (getSpeedY() < 0) {
        angle = PI / 3.5 * ((float)getSpeedY() / SPEED_UP);
    }

    rotateimage(&rotated_image, image[frame], angle);
    rotateimage(&rotated_mask, mask[frame], angle, WHITE);
}

void Bird::draw() const{
    if (!isVisiable()) return;

    putimage(x, y, &rotated_mask, SRCAND);
    putimage(x, y, &rotated_image, SRCPAINT);
}

void Bird::setCollisionBoxX() {
    collision_box.setX(getX() + getWidth() * 0.12);
}
void Bird::setCollisionBoxY() {
    collision_box.setY(getY() + getHeight() * 0.2);
}

//---------------------------------------------------------------------------------------
// Pipe
Pipe::Pipe() :Object2DPhysical() {};

Pipe::Pipe(int is_buttom):Pipe() {
    if (is_buttom) {
        this->is_buttom = true;
    }
    else {
        this->is_buttom = false;
    }
}

void Pipe::update() {
    if (GAME_END || !GAME_START) {
        return;
    }
    Object2DPhysical::update();
    if (this->getX() < 0 - this->getWidth()) {
        this->setX(310);

        if (this->is_buttom) {
            this->setY(pivot + 165);
        }
        else{                                   // Update pivot when the upper one is reset
            pivot = rand() % 250;
            update_score = true;
            this->setY(pivot - 305);
        }
    }
}


//---------------------------------------------------------------------------------------
// Score
void Score::draw() const{
    if (!isVisiable()) return;
    std::string credit = std::to_string(this->point);
    for (int i = 0; i < credit.size(); i++) {
        putimage(getX() - ((int)credit.size() / 2 - i + 0.5) * (this->mask[0]->getwidth()),
            this->getY(),
            this->mask[credit[i] - 48],
            SRCAND
        );

        putimage(getX() - ((int)credit.size() / 2 - i + 0.5) * this->image[0]->getwidth(),
            this->getY(),
            this->image[credit[i] - 48],
            SRCPAINT
        );
    }
}

void Score::update() {
    if (GAME_START && !isVisiable()) {
        setVisibility(true);
    }
    if (GAME_END) {
        setY(250);
        return;
    }

    if (update_score) {
        point += 1;
        update_score = false;
    }
}

void Score::setPoint(int val) {
    this->point = val;
}


void OpenText::update() {
    if (GAME_START && isVisiable()) {
        setVisibility(false);
        setClickability(false);
    }
    if (!GAME_START && !isVisiable()) {
        setVisibility(true);
        setClickability(true);
    }
}


EndText::EndText() : Object2D() {
    setVisibility(false);
}

void EndText::update() {
    if (!GAME_END && isVisiable()) {
        setVisibility(false);
        setClickability(false);
    }
    if (GAME_END && !isVisiable()) {
        setVisibility(true);
        setClickability(true);
    }
}
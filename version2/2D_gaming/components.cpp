#include "components.h"

int pivot = rand() % 250;
bool update_score = false;

void Ground::update() { 

#if 0
    std::cout << "ground update" << getX() << std::endl;
#endif

    if (getX() < -20) {                                       // Reset ground
        setX(0);
    }
    else {
        object2D::update();
    }
}


void Bird::draw() {

    int PI = 3.14159265359;
    float angle = 0;

    if (getSpeedY() != 0) {
        angle = PI / 3 * max(-1, (float)getSpeedY() / SPEED_UP);
    }
    else if (getSpeedY() < 0) {
        angle = PI / 3.5 * ((float)getSpeedY() / SPEED_UP);
    }

    IMAGE current_image;
    IMAGE current_mask;
    rotateimage(&current_image, image[frame], angle);
    rotateimage(&current_mask, mask[frame], angle, WHITE);

    putimage(x, y, &current_mask, SRCAND);
    putimage(x, y, &current_image, SRCPAINT);
}

Pipe::Pipe() :object2D() {};
Pipe::Pipe(int is_buttom):object2D() {
    if (is_buttom) {
        this->is_buttom = true;
    }
    else {
        this->is_buttom = false;
    }
}

void Pipe::update() {
    object2D::update();
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


void Score::draw() {
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
    if (update_score) {
        point += 1;
        update_score = false;
    }
}
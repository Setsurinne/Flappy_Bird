#include "object.h"

object2D::object2D(){
    x = 0;
    y = 0;

    speed_x = 0;
    speed_y = 0;

    acceleration_x = 0;
    acceleration_y = 0;

    height = 0;
    width = 0;
    frame = 0;

    clickable = false;
    visiable = true;

    clickAction = NULL;
}

int object2D::getX() {
    return x;
}

int object2D::getY() {
    return y;
}

int object2D::getSpeedX() {
    return speed_x;
}

int object2D::getSpeedY() {
    return speed_y;
}

int object2D::getAccX() {
    return acceleration_x;
}

int object2D::getAccY() {
    return acceleration_y;
}

int object2D::getWidth() {
    return width;
}

int object2D::getHeight() {
    return height;
}

void object2D::setX(int val) {
    x = val;
}

void object2D::setY(int val) {
    y = val;
}

void object2D::setSpeedX(int val) {
    speed_x = val;
}

void object2D::setSpeedY(int val) {
    speed_y = val;
}

void object2D::setAccX(int val) {
    acceleration_x = val;
}

void object2D::setAccY(int val) {
    acceleration_y = val;
}

void object2D::loadImage(LPCTSTR address) {
    IMAGE temp;
    loadimage(&temp, address);
    image.push_back(std::move(temp));
    width = image[0].getwidth();
    height = image[0].getheight();
}

void object2D::draw() {
    if (!visiable) return;
    if (mask.empty()) {
        putimage(x, y, &image[frame]);
    }
    else {
        putimage(x, y, &mask[frame], SRCAND);
        putimage(x, y, &image[frame], SRCPAINT);
    }
}

void object2D::update() {
    setSpeedX(getSpeedX() + getAccX());
    setX(getSpeedX() + getX());

    setSpeedY(getSpeedY() + getAccY());
    setY(getSpeedY() + getY());
}

bool object2D::collision(object2D other_obj) {
    return	false;
}

bool object2D::isClickMe(int cx, int cy)
{
    return cx >= x && cy >= y && x + width >= cx && y + height >= cy;
}

void object2D::receiveEvent(int cx, int cy) {
    if (isClickMe(cx, cy))
    {
        clickAction();
    }
}
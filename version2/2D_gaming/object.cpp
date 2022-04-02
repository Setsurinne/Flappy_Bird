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

int object2D::getNumImage() {
    return image.size();
}

bool object2D::isVisiable() {
    return visiable;
}

bool object2D::isClickable() {
    return clickable;
}

bool object2D::isTransparent() {
    return mask.empty();
}

void object2D::setValue(
        int x,
        int y,
        int acceleration_x,
        int acceleration_y,
        int speed_x,
        int speed_y)
{
    this->x = x;
    this->y = y;
    this->acceleration_x = acceleration_x;
    this->acceleration_y = acceleration_y;
    this->speed_x = speed_x;
    this->speed_y = speed_y;
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

void object2D::setVisibility(bool val) {
    visiable = val;
}

void object2D::setClickability(bool val) {
    clickable = val;
}

void object2D::loadImage(LPCTSTR address, LPCTSTR mask_address, int nWidth, int nHeight, bool bResize) {
    IMAGE temp;
    loadimage(&temp, address, nWidth, nHeight, bResize);
    image.push_back(std::move(temp));
    width = image[0].getwidth();
    height = image[0].getheight();

    if (!mask_address) return;
    loadimage(&temp, mask_address, nWidth, nHeight, bResize);
    mask.push_back(std::move(temp));
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

    if (++frame >= getNumImage()) {
        frame = 0;
    }
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
#include "Object2D.h"

extern bool GAME_START;
extern bool GAME_END;

Object2D::Object2D(){
    x = 0;
    y = 0;

    height = 0;
    width = 0;
    frame = 0;

    clickable = false;
    visiable = true;
    pause = false;

    clickAction = NULL;
    updateAction = NULL;
}

Object2D::Object2D(float x, float y, bool visiable, bool clickable) {
    this->x = x;
    this->y = y;
    this->clickable = clickable;
    this->visiable = visiable;
    this->clickAction = NULL;
    this->pause = false;

    this->height = 0;
    this->width = 0;
    this->frame = 0;
}


Object2D::~Object2D() {}

void Object2D::destroy() {
    this->~Object2D();
}

float Object2D::getX() const {
    return x;
}

float Object2D::getY() const {
    return y;
}

float Object2D::getWidth() const {
    return width;
}

float Object2D::getHeight() const {
    return height;
}

int Object2D::getNumImage() const {
    return image.size();
}

const Object2D* Object2D::getType() const {
    return this;
}


bool Object2D::isVisiable() const {
    return visiable;
}

bool Object2D::isClickable() const {
    return clickable;
}

bool Object2D::isTransparent() const {
    return mask.empty();
}


bool Object2D::isPaused() const {
    return pause;
}

void Object2D::setValue(float x, float y)
{
    this->x = x;
    this->y = y;
}


void Object2D::setX(float val) {
    x = val;
}

void Object2D::setY(float val) {
    y = val;
}

void Object2D::setHeight(float val) {
    height = val;
}

void Object2D::setWidth(float val) {
    width = val;
}

void Object2D::setVisibility(bool val) {
    visiable = val;
}

void Object2D::setClickability(bool val) {
    clickable = val;
}

void Object2D::setPause(bool val) {
    pause = val;
}

void Object2D::loadImage(LPCTSTR address, LPCTSTR mask_address, int nWidth, int nHeight, bool bResize) {
    IMAGE* temp = new IMAGE();
    loadimage(temp, address, nWidth, nHeight, bResize);
    image.push_back(std::move(temp));

    if (mask_address) {
        temp = new IMAGE();
        loadimage(temp, mask_address, nWidth, nHeight, bResize);
        mask.push_back(std::move(temp));
    }

    if (getNumImage() == 1) {
        width = image[0]->getwidth();
        height = image[0]->getheight();
    }
}

void Object2D::useImage(IMAGE* img, IMAGE* msk){
    image.push_back(img);
    if (msk) {
        mask.push_back(msk);
    }

    if (getNumImage() == 1) {
        width = image[0]->getwidth();
        height = image[0]->getheight();
    }
}


void Object2D::draw() const {
    if (!isVisiable()) return;
    if (mask.empty()) {
        putimage(x, y, image[frame]);
    }
    else {
        putimage(x, y, mask[frame], SRCAND);
        putimage(x, y, image[frame], SRCPAINT);
    }
}

void Object2D::update() {
    if (isPaused()) return;
    if (++frame >= getNumImage()) {
        frame = 0;
    }
}

bool Object2D::overlay(const Object2D& other_obj) const {
    return
        abs(getX() - other_obj.getX()) < (getX() < other_obj.getX() ? getWidth() : other_obj.getWidth()) &&
        abs(getY() - other_obj.getY()) < (getY() < other_obj.getY() ? getHeight() : other_obj.getHeight());
}


bool Object2D::isClickMe(float cx, float cy)
{
    return cx >= x && cy >= y && x + width >= cx && y + height >= cy;
}

void Object2D::receiveEvent(float cx, float cy) {
    if (isClickable() && clickAction && isClickMe(cx, cy))
    {
        clickAction();
    }
}
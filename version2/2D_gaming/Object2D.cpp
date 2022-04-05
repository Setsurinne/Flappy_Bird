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

    clickAction = NULL;
}

Object2D::~Object2D() {}

void Object2D::destroy() {
    this->~Object2D();
}

int Object2D::getX() const {
    return x;
}

int Object2D::getY() const {
    return y;
}

int Object2D::getWidth() const {
    return width;
}

int Object2D::getHeight() const {
    return height;
}

int Object2D::getNumImage() const {
    return image.size();
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


void Object2D::setValue(int x, int y)
{
    this->x = x;
    this->y = y;
}


void Object2D::setX(int val) {
    x = val;
}

void Object2D::setY(int val) {
    y = val;
}

void Object2D::setHeight(int val) {
    height = val;
}

void Object2D::setWidth(int val) {
    width = val;
}

void Object2D::setVisibility(bool val) {
    visiable = val;
}

void Object2D::setClickability(bool val) {
    clickable = val;
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
    if (++frame >= getNumImage()) {
        frame = 0;
    }
}

bool Object2D::overlay(const Object2D& other_obj) const {
    return
        abs(getX() - other_obj.getX()) < (getX() < other_obj.getX() ? getWidth() : other_obj.getWidth()) &&
        abs(getY() - other_obj.getY()) < (getY() < other_obj.getY() ? getHeight() : other_obj.getHeight());
}


bool Object2D::isClickMe(int cx, int cy)
{
    return cx >= x && cy >= y && x + width >= cx && y + height >= cy;
}

void Object2D::receiveEvent(int cx, int cy) {
    if (isClickable() && clickAction && isClickMe(cx, cy))
    {
        clickAction();
    }
}
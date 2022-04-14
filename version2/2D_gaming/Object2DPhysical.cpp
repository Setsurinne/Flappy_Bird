#include "Object2DPhysical.h"

Object2DPhysical::Object2DPhysical(
    float x, float y, bool visiable, bool clickable, bool collidable,
    float acceleration_x, float acceleration_y, float speed_x, float speed_y) : Object2D(x, y, visiable, clickable) {

    this->collidable = collidable;
    this->actionCollision = NULL;
    this->setValue(x, y, acceleration_x, acceleration_y, speed_x, speed_y);
    collision_box.setWidth(-1);
    collision_box.setHeight(-1);
    collision_box.setVisibility(false);
}

float Object2DPhysical::getSpeedX() const {
    return speed_x;
}

float Object2DPhysical::getSpeedY() const {
    return speed_y;
}

float Object2DPhysical::getAccX() const {
    return acceleration_x;
}

float Object2DPhysical::getAccY() const {
    return acceleration_y;
}

bool Object2DPhysical::isCollidable() const {
    return collidable;
}

void Object2DPhysical::setX(float val) {
    Object2D::setX(val);
    setCollisionBoxX();
}

void Object2DPhysical::setY(float val) {
    Object2D::setY(val);
    setCollisionBoxY();
}

void Object2DPhysical::setSpeedX(float val) {
    speed_x = val;
}

void Object2DPhysical::setSpeedY(float val) {
    speed_y = val;
}

void Object2DPhysical::setAccX(float val) {
    acceleration_x = val;
}

void Object2DPhysical::setAccY(float val) {
    acceleration_y = val;
}

void Object2DPhysical::setCollidability(bool val) {
    collidable = val;
}

void Object2DPhysical::setCollideAction(std::function<void(Object2D&, Object2D&)> fun) {
    this->actionCollision = fun;
}


void Object2DPhysical::setValue(
    float x,
    float y,
    float acceleration_x,
    float acceleration_y,
    float speed_x,
    float speed_y)
{
    setX(x);
    setY(y);
    this->acceleration_x = acceleration_x;
    this->acceleration_y = acceleration_y;
    this->speed_x = speed_x;
    this->speed_y = speed_y;
}


void Object2DPhysical::update() {
    Object2D::update();

    setSpeedX(getSpeedX() + getAccX());
    setX(getSpeedX() + getX());

    setSpeedY(getSpeedY() + getAccY());
    setY(getSpeedY() + getY());
}

bool Object2DPhysical::collision(Object2DPhysical& other_obj) {
    if (!(isCollidable() && other_obj.isCollidable())) {
        return false;
    }

    if (collision_box.getHeight() < 0) {
        setCollisionBoxHeight(getHeight());
        setCollisionBoxWidth(getWidth());
    }
    if (other_obj.collision_box.getHeight() < 0) {
        other_obj.collision(*this);
    }

    if (collision_box.overlay(other_obj.collision_box)) {
        if (actionCollision) this->actionCollision(*this, other_obj);
        if (other_obj.actionCollision) other_obj.actionCollision(other_obj, *this);
        return true;
    }
    return false;
}

void Object2DPhysical::setCollisionBoxX() {
    collision_box.setX(x);
}

void Object2DPhysical::setCollisionBoxY() {
    collision_box.setY(y);
}

void Object2DPhysical::setCollisionBoxWidth(float val){
    collision_box.setWidth(val);
}

void Object2DPhysical::setCollisionBoxHeight(float val) {
    collision_box.setHeight(val);
}
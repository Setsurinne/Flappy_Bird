#pragma once
#include "Object2D.h"
class Object2DPhysical : public Object2D{
public:
    Object2DPhysical();
    int getSpeedX() const;
    int getSpeedY() const;
    int getAccX() const;
    int getAccY() const;

    bool isCollidable() const;


    virtual void setX(int val);
    virtual void setY(int val);
    void setSpeedX(int val);
    void setSpeedY(int val);
    void setAccX(int val);
    void setAccY(int val);

    virtual void setCollisionBoxWidth(int val);
    virtual void setCollisionBoxHeight(int val);

    void setCollidability(bool val);

    virtual void setValue(int x = 0,
        int y = 0,
        int acceleration_x = 0,
        int acceleration_y = 0,
        int speed_x = 0,
        int speed_y = 0
    );

    virtual void update();
    virtual bool collision(Object2DPhysical& other_obj);


protected:
    int speed_x;
    int speed_y;

    int acceleration_x;
    int acceleration_y;

    bool collidable = true;

    Object2D collision_box;

    virtual void setCollisionBoxX();
    virtual void setCollisionBoxY();
};


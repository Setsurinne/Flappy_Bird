#pragma once
#include "Object2D.h"

/// <summary>
/// 2D object with more physical property, provide basic function to make the object movable and collidable.
/// </summary>
class Object2DPhysical : public Object2D{
public:
    Object2DPhysical(
        float x = 0,
        float y = 0,
        bool visiable = true,
        bool clickable = false,
        bool collidable = true,
        float acceleration_x = 0,
        float acceleration_y = 0,
        float speed_x = 0,
        float speed_y = 0);

// To get properties of othe object
    float             getSpeedX()                     const;
    float             getSpeedY()                     const;
    float             getAccX()                       const;
    float             getAccY()                       const;

    bool            isCollidable()                  const;


// To modify properties of the object
    virtual void    setX(float val);
    virtual void    setY(float val);
    void            setSpeedX(float val);
    void            setSpeedY(float val);
    void            setAccX(float val);
    void            setAccY(float val);

    virtual void    setCollisionBoxWidth(float val);
    virtual void    setCollisionBoxHeight(float val);

    void            setCollidability(bool val);
    void            setCollideAction(std::function<void(Object2D&, Object2D&)>);
    /// <summary>
    /// To set multiple value of current object at once
    /// </summary>
    /// <param name="x">: If indicated, represents x location of current object </param>
    /// <param name="y">: If indicated, represents y location of current object </param>
    /// <param name="acceleration_x">: If indicated, represents acceleration in direction of x </param>
    /// <param name="acceleration_y">: If indicated, represents acceleration in direction of y </param>
    /// <param name="speed_x">: If indicated, represents speed in direction of x </param>
    /// <param name="speed_y">: If indicated, represents speed in direction of xy</param>
    virtual void    setValue(
        float x = 0,
        float y = 0,
        float acceleration_x = 0,
        float acceleration_y = 0,
        float speed_x = 0,
        float speed_y = 0
    );

    /// <summary>
    /// Update properties of current object (generaly frame by frame), including update frame of image, the effect of accleration and speed, and the location.
    /// </summary>
    virtual void    update();

    /// <summary>
    /// Check if current object is collide with other
    /// </summary>
    /// <param name="other_obj">: One other object to check if collision occurs </param>
    /// <returns> True iff both object is collidable and the collision happened </returns>
    virtual bool    collision(Object2DPhysical& other_obj);

    std::function<void(Object2D&, Object2D&)> actionCollision;

protected:
    float speed_x;
    float speed_y;

    float acceleration_x;
    float acceleration_y;

    /// <summary>
    /// Decide if current object is responsive to collision and continous effects
    /// </summary>
    bool collidable = true;

    /// <summary>
    /// An 2D object, represents the box of collision.
    /// This is the box the class uses to determine collision.
    /// </summary>
    Object2D collision_box;

    virtual void setCollisionBoxX();
    virtual void setCollisionBoxY();
};


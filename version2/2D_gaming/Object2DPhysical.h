#pragma once
#include "Object2D.h"

/// <summary>
/// 2D object with more physical property, provide basic function to make the object movable and collidable.
/// </summary>
class Object2DPhysical : public Object2D{
public:
    Object2DPhysical();

// To get properties of othe object
    int             getSpeedX()                     const;
    int             getSpeedY()                     const;
    int             getAccX()                       const;
    int             getAccY()                       const;

    bool            isCollidable()                  const;


// To modify properties of the object
    virtual void    setX(int val);
    virtual void    setY(int val);
    void            setSpeedX(int val);
    void            setSpeedY(int val);
    void            setAccX(int val);
    void            setAccY(int val);

    virtual void    setCollisionBoxWidth(int val);
    virtual void    setCollisionBoxHeight(int val);

    void            setCollidability(bool val);

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
        int x = 0,
        int y = 0,
        int acceleration_x = 0,
        int acceleration_y = 0,
        int speed_x = 0,
        int speed_y = 0
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


protected:
    int speed_x;
    int speed_y;

    int acceleration_x;
    int acceleration_y;

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


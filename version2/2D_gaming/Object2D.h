#pragma once
#include <easyx.h>
#include <graphics.h>
#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>
//#include <signal.h>

/// <summary>
/// Base class for the 2D object, provide basic function to get/update its properties and draw it out.
/// </summary>
class Object2D
{
public:
    Object2D();
    Object2D(int x, int y, bool visiable = true, bool clickable = false);
    ~Object2D();

    virtual void    destroy();

// To get properties of othe object
    int				getX()							const;
    int				getY()							const;
    int				getHeight()						const;
    int				getWidth()						const;
    int				getNumImage()					const;

    bool			isVisiable()					const;
    bool			isClickable()					const;
    bool			isTransparent()					const;
    bool			isPaused()					    const;

    virtual const Object2D*     getType()           const;

// To modify properties of othe object

    virtual void	setValue(int x = 0, int y = 0);

    virtual void	setX(int val);
    virtual void	setY(int val);
    void			setHeight(int val);
    void			setWidth(int val);

    void			setVisibility(bool val);
    void			setClickability(bool val);
    void			setPause(bool val);

    /// <summary>
    /// Action after been clicked, to be defined by the user
    /// </summary>
    std::function<void()> clickAction;

    /// <summary>
    /// Action after been updated, to be defined by the user
    /// </summary>
    std::function<void()> updateAction;


    /// <summary>
    /// Use the x-y value of a click action, determine if current object is going to do feedback
    /// </summary>
    /// <param name="cx"> x value of a click action </param>
    /// <param name="cy"> y value of a click action </param>
    void            receiveEvent(int cx, int cy);


    /// <summary>
    /// Check if current object overlay with other_obj
    /// </summary>
    /// 
    /// <param name="other_obj"> Other object to check overlay</param>
    /// 
    /// <returns> True iff two object has overlay </returns>
    bool            overlay(const Object2D& other_obj) const;


    /// <summary>
    /// Load image for this object, image can be used to draw this object
    /// </summary>
    /// 
    /// <param name="address"> The address of the image </param>
    /// <param name="mask_address"> If indicated, will be the address of the mask if want to be transparent </param>
    /// <param name="nWidth"> If indicated, will be the width of the image to reshape </param>
    /// <param name="nHeight"> If indicated, will be the height of the image to reshape </param>
    /// <param name="bResize"> If need to justify the size of IMAGE to match the size of the loaded image </param>
    virtual void    loadImage(
        LPCTSTR address, 
        LPCTSTR mask_address = NULL,
        int nWidth = 0,
        int nHeight = 0,
        bool bResize = false
    );
    
    /// <summary>
    /// Let this object use loaded image
    /// </summary>
    /// <param name="img"> ptr of a image</param>
    /// <param name="msk"> If indicated, should be a ptr of a mask image to enable transparent drawing </param>
    virtual void    useImage(IMAGE* img, IMAGE* msk = NULL);

    
    /// <summary>
    /// Draw the image of current object if its visiable and has image available to draw
    /// </summary>
    virtual void    draw() const;

    /// <summary>
    /// Update current object (frame of image, location, ...), generally activated frame by frame.
    /// </summary>
    virtual void    update();


protected:
// Basic properties
    int x;
    int y;
    int height;
    int width;
    int frame;

    /// <summary>
    /// To decide if current object is responsive to any click action
    /// </summary>
    bool clickable;

    /// <summary>
    /// To decide if current object is responsive to any draw action
    /// </summary>
    bool visiable;

    /// <summary>
    /// To decide if current object is responsive to any update action
    /// </summary>
    bool pause;

    std::vector<IMAGE*> image;
    std::vector<IMAGE*> mask;

    /// <summary>
    /// Check if a click action is happened in the location of current object
    /// </summary>
    /// <param name="cx"> x value of a click action </param>
    /// <param name="cy"> y value of a click action </param>
    /// <returns> True iff current object is clickable and the click action is on current object </returns>
    bool isClickMe(int cx, int cy);
};
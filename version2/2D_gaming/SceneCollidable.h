#pragma once
#include "Scene.h"
#include "Object2DPhysical.h"
class SceneCollidable :public Scene{
public:
    SceneCollidable();
    SceneCollidable(Object2DPhysical*, bool visiable = false, bool clickable = false, void (*beginCallBack)() = NULL, void (*endCallBack)() = NULL);
    SceneCollidable(std::vector<Object2DPhysical*>&, bool visiable = false, bool clickable = false, void (*beginCallBack)() = NULL, void (*endCallBack)() = NULL);
    void updateByTick();
    bool isCollidable() const;
    void setCollidability(bool val);

private:
    bool collidable = true;
    std::vector<Object2DPhysical*> elements;
};


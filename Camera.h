#pragma once
#include "Engine/GameObject.h"
class Camera :
    public GameObject
{
public:
    Camera();
    ~Camera();

    void SetValue(int v){ value = v; }
};


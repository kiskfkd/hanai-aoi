#pragma once
#include "Engine/GameObject.h"
#include <DirectXMath.h>

using namespace DirectX;

class Platform
{
public:
    Platform(XMFLOAT3 pos, bool active);

    void SetActive(bool active);
    bool IsActive() const;
    void ToggleActive();

    bool IsColliding(int x, int y) const;

    XMFLOAT3 position;
    //bool isActive;
private:
    bool isActive;
};
#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Platform
{
public:
    Platform(XMFLOAT3 pos, bool active, int lifetime);

    void SetActive(bool active);
    bool IsActive() const;
    void ToggleActive();
    void DecreaseLifetime();
    bool IsExpired() const;

    bool IsColliding(int x, int y) const;

    XMFLOAT3 position;
    bool isActive;
    int lifetime; // ë´èÍÇÃéıñΩ
};

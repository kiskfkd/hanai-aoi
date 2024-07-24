#include "Platform.h"

Platform::Platform(XMFLOAT3 pos, bool active, int lifetime)
    : position(pos), isActive(active), lifetime(lifetime)
{
}

void Platform::SetActive(bool active)
{
    isActive = active;
}

bool Platform::IsActive() const
{
    return isActive;
}

void Platform::ToggleActive()
{
    isActive = !isActive;
}

void Platform::DecreaseLifetime()
{
    if (lifetime > 0)
    {
        --lifetime;
    }
}

bool Platform::IsExpired() const
{
    return lifetime <= 0;
}

bool Platform::IsColliding(int x, int y) const
{
    if (!isActive) return false;

    int platformX = (int)position.x;
    int platformY = (int)position.y;
    int platformWidth = 32; // プラットフォームの幅（ピクセル）
    int platformHeight = 32; // プラットフォームの高さ（ピクセル）

    return (x >= platformX && x < platformX + platformWidth &&
        y >= platformY && y < platformY + platformHeight);
}

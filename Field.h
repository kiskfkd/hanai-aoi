#pragma once
#include "Engine/GameObject.h"
#include "Platform.h"
#include <vector>

class Field : public GameObject
{
public:
    Field(GameObject* scene);
    ~Field();
    void Reset();
    void Update() override;
    void Draw() override;

    int CollisionRight(int x, int y);
    int CollisionLight(int x, int y);
    int CollisionDown(int x, int y);
    int CollisionUp(int x, int y);

private:
    int hImage;
    int hPlatformImage;
    bool IsWallBlock(int x, int y);
    int* Map;
    int width;
    int height;
    static std::vector<Platform> platforms;

    bool IsPlatformBlock(int x, int y);

    void TogglePlatforms();
};
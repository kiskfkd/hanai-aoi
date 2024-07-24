#pragma once
#include "Engine/GameObject.h"
#include "Platform.h"
#include <DirectXMath.h>
#include <vector>

using namespace DirectX;

class TANK : public GameObject
{
public:
    TANK(GameObject* scene);
    ~TANK();

    void Update() override;
    void Draw() override;
    void SetPosition(XMFLOAT3 pos);

    void CreatePlatform(XMFLOAT3 pos, bool isActive);

    static std::vector<Platform> platforms; // クラス内のstaticメンバーとして宣言
private:
    int hImage;
    int hTankImage;
    int timer;
};

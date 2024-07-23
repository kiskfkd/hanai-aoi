
#pragma once
#include "Engine/GameObject.h"
#include "Platform.h"
#include <vector>
#include <d3d11.h>

class TANK : public GameObject {
public:
    TANK(GameObject* scene);
    ~TANK();

    void Update() override;
    void Draw() override;
    void SetPosition(XMFLOAT3 pos);
    void CreatePlatform(XMFLOAT3 pos, bool isActive);

private:
    int hImage;
    int hTankImage;  // TANKの画像を保持するメンバ変数
    int timer;
    static std::vector<Platform> platforms; // 静的メンバ変数としてplatformsを定義する
};
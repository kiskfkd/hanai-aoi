#ifndef TANK_H
#define TANK_H

#pragma once
#include "Engine/GameObject.h"
#include "Platform.h" // Platformクラスのヘッダーをインクルードする
#include <vector>

class TANK : public GameObject {
public:
    TANK(GameObject* scene);
    ~TANK();

    void Update();
    void Draw();
    void SetPosition(XMFLOAT3 pos);
    void CreatePlatform(XMFLOAT3 pos, int duration);

private:
    int hImage;
    int timer;
    static std::vector<Platform> platforms; // 静的メンバ変数としてplatformsを定義する
};
#endif // TANK_H
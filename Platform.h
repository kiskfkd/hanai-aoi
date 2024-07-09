#pragma once
#include "Engine/GameObject.h"

struct Platform : public GameObject {
    XMFLOAT3 position;
    int timer; // 残りの表示時間（フレーム数）

    Platform(XMFLOAT3 pos, int duration) : position(pos), timer(duration) {}
};


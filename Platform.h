#pragma once
#include "Engine/GameObject.h"

struct Platform : public GameObject {
    XMFLOAT3 position;
    int timer; // �c��̕\�����ԁi�t���[�����j

    Platform(XMFLOAT3 pos, int duration) : position(pos), timer(duration) {}
};


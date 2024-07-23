#include "TANK.h"
#include <DxLib.h>
#include <assert.h>
#include"Camera.h"
std::vector<Platform> TANK::platforms;

TANK::TANK(GameObject* scene) : GameObject(scene), hImage(-1), hTankImage(-1), timer(0) {
    hImage = LoadGraph("Assets/TANK.png");  // TANK‚Ì‰æ‘œ‚ð“Ç‚Ýž‚Þ
    assert(hImage > 0);
}

TANK::~TANK() {
    if (hImage > 0) {
        DeleteGraph(hImage);
    }
    if (hTankImage > 0) {
        DeleteGraph(hTankImage);  // TANK‚Ì‰æ‘œ‚ð‰ð•ú‚·‚é
    }
}

void TANK::Update() {
    // TANK‚ÌXVˆ—
}

void TANK::Draw() {
    int x = (int)transform_.position_.x;
    int y = (int)transform_.position_.y;
    Camera* cam = GetParent()->FindGameObject<Camera>();
    if (cam != nullptr) {
        x -= cam->GetValue();
    }
    DrawGraph(x, y, hImage, TRUE);  // TANK‚Ì‰æ‘œ‚ð•`‰æ
}

void TANK::SetPosition(XMFLOAT3 pos) {
    transform_.position_ = pos;
}

void TANK::CreatePlatform(XMFLOAT3 pos, bool isActive) {
    platforms.push_back(Platform(pos, isActive));
}
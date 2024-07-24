#include "TANK.h"
#include <DxLib.h>
#include <assert.h>
#include "Camera.h"
#include "Platform.h"

std::vector<Platform> TANK::platforms;

TANK::TANK(GameObject* scene) : GameObject(scene), hImage(-1), hTankImage(-1), timer(0) {
    hImage = LoadGraph("Assets/TANK.png");  // TANKの画像を読み込む
    assert(hImage > 0);
}

TANK::~TANK() {
    if (hImage > 0) {
        DeleteGraph(hImage);
    }
    if (hTankImage > 0) {
        DeleteGraph(hTankImage);  // TANKの画像を解放する
    }
}

void TANK::Update() {
    // TANKの更新処理
}

void TANK::Draw() {
    int x = (int)transform_.position_.x;
    int y = (int)transform_.position_.y;
    Camera* cam = GetParent()->FindGameObject<Camera>();
    if (cam != nullptr) {
        x -= cam->GetValue();
    }
    DrawGraph(x, y, hImage, TRUE);  // TANKの画像を描画
}

void TANK::SetPosition(XMFLOAT3 pos) {
    transform_.position_ = pos;
}

void TANK::CreatePlatform(XMFLOAT3 pos, bool isActive) {
    platforms.push_back(Platform(pos, isActive, 180)); // 足場の寿命を180フレームに設定
}

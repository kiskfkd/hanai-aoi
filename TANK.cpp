#include "TANK.h"
#include <DxLib.h>
#include <assert.h>
#include"Camera.h"
std::vector<Platform> TANK::platforms;

TANK::TANK(GameObject* scene) : GameObject(scene), hImage(-1), hTankImage(-1), timer(0) {
    hImage = LoadGraph("Assets/TANK.png");  // TANK�̉摜��ǂݍ���
    assert(hImage > 0);
}

TANK::~TANK() {
    if (hImage > 0) {
        DeleteGraph(hImage);
    }
    if (hTankImage > 0) {
        DeleteGraph(hTankImage);  // TANK�̉摜���������
    }
}

void TANK::Update() {
    // TANK�̍X�V����
}

void TANK::Draw() {
    int x = (int)transform_.position_.x;
    int y = (int)transform_.position_.y;
    Camera* cam = GetParent()->FindGameObject<Camera>();
    if (cam != nullptr) {
        x -= cam->GetValue();
    }
    DrawGraph(x, y, hImage, TRUE);  // TANK�̉摜��`��
}

void TANK::SetPosition(XMFLOAT3 pos) {
    transform_.position_ = pos;
}

void TANK::CreatePlatform(XMFLOAT3 pos, bool isActive) {
    platforms.push_back(Platform(pos, isActive));
}
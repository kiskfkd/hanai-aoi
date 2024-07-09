#ifndef TANK_H
#define TANK_H

#pragma once
#include "Engine/GameObject.h"
#include "Platform.h" // Platform�N���X�̃w�b�_�[���C���N���[�h����
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
    static std::vector<Platform> platforms; // �ÓI�����o�ϐ��Ƃ���platforms���`����
};
#endif // TANK_H
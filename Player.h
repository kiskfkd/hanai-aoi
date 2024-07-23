#pragma once
#include "Engine/GameObject.h"
#include <DirectXMath.h>
#include <vector>

using namespace DirectX;

class Player : public GameObject {
public:
    Player(GameObject* parent);
    ~Player();

    void Update();
    void Draw();
    void SetPosition(int x, int y);

private:
    int hImage;
    float jumpSpeed;
    bool onGround;
    int animType;
    int animFrame;
    int frameCounter;
    enum State { S_Walk, S_Cry } state;
    bool tactive;
    bool eactive;
    bool sactive;
    bool prevSpaceKey;
    int timer;
    int ttimer;  // TANK�p�̃^�C�}�[
    int etimer;  // EMP�p�̃^�C�}�[
    int stimer;  // SOLDIER�p�̃^�C�}�[
};
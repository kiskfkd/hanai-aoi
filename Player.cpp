#include "Player.h"
#include <DxLib.h>
#include <assert.h>
#include "Camera.h"
#include "Field.h"
#include "Bird.h"
#include "TestScene.h"
#include "EMP.h"
#include "TANK.h"
#include "SOLDIER.h"

namespace {
    const float MOVE_SPEED = 1.0f;
    const float GROUND = 400.0f;
    const float JUMP_HEIGHT = 64.0f * 4.0f;
    const float GRAVITY = 9.8f / 60.0f;
}

Player::Player(GameObject* parent) : GameObject(parent)
{
    hImage = LoadGraph("Assets/aoi.png");
    assert(hImage > 0);
    transform_.position_.x = 10.0f;
    transform_.position_.y = GROUND;
    jumpSpeed = 0.0f;
    onGround = true;
    animType = 0;
    animFrame = 0;
    frameCounter = 0;
    state = S_Walk;
    tactive = true;
    eactive = true;
    sactive = true;
    ttimer = 0; // 初期化
    etimer = 0; // 初期化
    stimer = 0; // 初期化
    prevSpaceKey = false;
}

Player::~Player()
{
    if (hImage > 0)
    {
        DeleteGraph(hImage);
    }
}

void Player::Update()
{
    Field* pField = GetParent()->FindGameObject<Field>();
    if (state == S_Cry) {
        frameCounter++;
        if (frameCounter >= 8) {
            frameCounter = 0;
            animFrame = (animFrame + 1) % 2;
        }
        return;
    }
    TestScene* scene = dynamic_cast<TestScene*>(GetParent());
    if (!scene->CanMove())
        return;

    // 移動
    transform_.position_.x += MOVE_SPEED;
    if (++frameCounter >= 8) {
        animFrame = (animFrame + 1) % 4;
        frameCounter = 0;
    }
    int hitX = transform_.position_.x + 50;
    int hitY = transform_.position_.y + 63;
    if (pField != nullptr) {
        int push = pField->CollisionRight(hitX, hitY);
        transform_.position_.x -= push;
    }

    // ジャンプ
    if (CheckHitKey(KEY_INPUT_SPACE)) {
        if (prevSpaceKey == false) {
            if (onGround) {
                jumpSpeed = -sqrtf(2 * GRAVITY * JUMP_HEIGHT);
                onGround = false;
            }
        }
        prevSpaceKey = true;
    }
    else {
        prevSpaceKey = false;
    }
    jumpSpeed += GRAVITY;
    transform_.position_.y += jumpSpeed;
    if (pField != nullptr) {
        int pushR = pField->CollisionDown(transform_.position_.x + 50, transform_.position_.y + 64);
        int pushL = pField->CollisionDown(transform_.position_.x + 14, transform_.position_.y + 64);
        int push = max(pushR, pushL);
        if (push >= 1) {
            transform_.position_.y -= push - 1;
            jumpSpeed = 0.0f;
            onGround = true;
        }
        else {
            onGround = false;
        }
    }

    // TANKの足場を作成するロジック
    if (CheckHitKey(KEY_INPUT_A)) {
        if (tactive) {
            TANK* tank = new TANK(GetParent());
            // トグル可能な足場を作成
            tank->CreatePlatform(XMFLOAT3(transform_.position_.x + 100.0f, transform_.position_.y + 100.0f, 0.0f), true);
            tactive = false;
            ttimer = 180;
        }
    }

    if (--ttimer <= 0) {
        tactive = true;
    }

    // EMP作成ロジック
    if (CheckHitKey(KEY_INPUT_S)) {
        if (eactive) {
            EMP* emp = Instantiate<EMP>(GetParent());
            emp->SetPosition(transform_.position_);
           eactive = false;
            etimer = 180;
        }
    }

    if (--etimer <= 0) {
        eactive = true;
    }

    // SOLDIER作成ロジック
    if (CheckHitKey(KEY_INPUT_D)) {
        if (sactive) {
            SOLDIER* so = Instantiate<SOLDIER>(GetParent());
            so->SetPosition(transform_.position_);
            sactive = false;
            stimer = 180;
        }
    }

    if (--stimer <= 0) {
        sactive = true;
    }

    std::list<Bird*> pBirds = GetParent()->FindGameObjects<Bird>();
    for (Bird* pBird : pBirds) {
        if (pBird->CollideCircle(transform_.position_.x + 32.0f, transform_.position_.y + 32.0f, 20.0f)) {
            animType = 4;
            animFrame = 0;
            state = S_Cry;
            scene->StartDead();
        }
    }

    // カメラ位置の調整
    Camera* cam = GetParent()->FindGameObject<Camera>();
    int x = (int)transform_.position_.x - cam->GetValue();
    if (x > 400) {
        x = 400;
        cam->SetValue((int)transform_.position_.x - x);
    }
}

void Player::Draw()
{
    int x = (int)transform_.position_.x;
    int y = (int)transform_.position_.y;
    Camera* cam = GetParent()->FindGameObject<Camera>();
    if (cam != nullptr) {
        x -= cam->GetValue();
    }
    DrawRectGraph(x, y, animFrame * 64, animType * 64, 64, 64, hImage, TRUE);
}

void Player::SetPosition(int x, int y)
{
    transform_.position_.x = x;
    transform_.position_.y = y;
}
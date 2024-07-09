#include "TANK.h"
#include <assert.h>
#include "Camera.h"

const float speed = 2.0f;

std::vector<Platform> TANK::platforms; // 静的メンバ変数の実体を定義する

TANK::TANK(GameObject* scene) : GameObject(scene)
{
    hImage = LoadGraph("Assets/stone.png");
    assert(hImage > 0);

    // 初期位置に足場を設置する例
    platforms.push_back(Platform(XMFLOAT3(200.0f, 400.0f, 0.0f), 300)); // (200, 400)に足場を設置、300フレームの制限時間
}

TANK::~TANK()
{
    if (hImage > 0)
    {
        DeleteGraph(hImage);
    }
}

void TANK::Update()
{
    transform_.position_.x += speed;
    if (--timer <= 0)
    {
        KillMe();
    }

    // 足場のタイマーを更新し、時間が経過したら削除する
    for (auto it = platforms.begin(); it != platforms.end(); )
    {
        it->timer--;
        if (it->timer <= 0)
        {
            it = platforms.erase(it); // 足場を削除
        }
        else
        {
            ++it;
        }
    }
}

void TANK::Draw()
{
    int x = (int)transform_.position_.x;
    int y = (int)transform_.position_.y;
    Camera* cam = GetParent()->FindGameObject<Camera>();
    if (cam != nullptr) {
        x -= cam->GetValue();
    }
    DrawGraph(x, y, hImage, TRUE);

    // 足場を描画する
    for (auto& platform : platforms)
    {
        int px = (int)platform.position.x;
        int py = (int)platform.position.y;
        DrawBox(px, py, px + 50, py + 10, GetColor(255, 255, 0), TRUE); // 例えば黄色の箱として描画
    }
}

void TANK::SetPosition(XMFLOAT3 pos)
{
    transform_.position_ = pos;
    timer = 180;
}

// 新しい足場を作成する関数
void TANK::CreatePlatform(XMFLOAT3 pos, int duration)
{
    platforms.push_back(Platform(pos, duration));
}
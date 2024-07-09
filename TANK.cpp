#include "TANK.h"
#include <assert.h>
#include "Camera.h"

const float speed = 2.0f;

std::vector<Platform> TANK::platforms; // �ÓI�����o�ϐ��̎��̂��`����

TANK::TANK(GameObject* scene) : GameObject(scene)
{
    hImage = LoadGraph("Assets/stone.png");
    assert(hImage > 0);

    // �����ʒu�ɑ����ݒu�����
    platforms.push_back(Platform(XMFLOAT3(200.0f, 400.0f, 0.0f), 300)); // (200, 400)�ɑ����ݒu�A300�t���[���̐�������
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

    // ����̃^�C�}�[���X�V���A���Ԃ��o�߂�����폜����
    for (auto it = platforms.begin(); it != platforms.end(); )
    {
        it->timer--;
        if (it->timer <= 0)
        {
            it = platforms.erase(it); // ������폜
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

    // �����`�悷��
    for (auto& platform : platforms)
    {
        int px = (int)platform.position.x;
        int py = (int)platform.position.y;
        DrawBox(px, py, px + 50, py + 10, GetColor(255, 255, 0), TRUE); // �Ⴆ�Ή��F�̔��Ƃ��ĕ`��
    }
}

void TANK::SetPosition(XMFLOAT3 pos)
{
    transform_.position_ = pos;
    timer = 180;
}

// �V����������쐬����֐�
void TANK::CreatePlatform(XMFLOAT3 pos, int duration)
{
    platforms.push_back(Platform(pos, duration));
}
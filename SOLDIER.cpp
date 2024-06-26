#include "SOLDIER.h"
#include <assert.h>
#include "Camera.h"
namespace {
	const float speed = 2.0f;
}

SOLDIER::SOLDIER(GameObject* scene) : GameObject(scene)
{
	hImage = LoadGraph("Assets/stone.png");
	assert(hImage > 0);
}

SOLDIER::~SOLDIER()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

void SOLDIER::Update()
{
	transform_.position_.x += speed;
	if (--timer <= 0)
	{
		KillMe();
	}
}

void SOLDIER::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}
	DrawGraph(x, y, hImage, TRUE);
}

void SOLDIER::SetPosition(XMFLOAT3 pos)
{
	transform_.position_ = pos;
	timer = 180;
}
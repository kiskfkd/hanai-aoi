#include "TANK.h"
#include <assert.h>
#include "Camera.h"
namespace {
	const float speed = 2.0f;
}

TANK::TANK(GameObject* scene) : GameObject(scene)
{
	hImage = LoadGraph("Assets/stone.png");
	assert(hImage > 0);
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
}

void TANK::SetPosition(XMFLOAT3 pos)
{
	transform_.position_ = pos;
	timer = 180;
}

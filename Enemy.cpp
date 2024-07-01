#include "Enemy.h"
#include <assert.h>
#include "Camera.h"
#include "TestScene.h"
#include"EMP.h"

namespace {
	static const int SCREEN_WIDTH = 1280;
};

Enemy::Enemy(GameObject* scene)
{
	hImage = LoadGraph("Assets/mob.png");
	assert(hImage > 0);
	transform_.position_.x = 800.0f;
	transform_.position_.y = 500.0f;
}
Enemy::~Enemy()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

#include "Bird.h"
#include <assert.h>
#include "Camera.h"
#include "TestScene.h"
#include"SOLDIER.h"
namespace {
	static const int SCREEN_WIDTH = 1280;
};

Bird::Bird(GameObject* scene)
{
	hImage = LoadGraph("Assets/mob.png");
	assert(hImage > 0);
	transform_.position_.x = 800.0f;
	transform_.position_.y = 500.0f;
}

Bird::~Bird()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

void Bird::Update()
{
	int x = (int)transform_.position_.x;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	TestScene* scene = dynamic_cast<TestScene*>(GetParent());
	if (!scene->CanMove())
		return;

	if (x > SCREEN_WIDTH) //即値、マジックナンバー
		return;
	else if (x < 0 - 64) {
		KillMe();
		return;
	}
	transform_.position_.x -= 1.0f;
	sinAngle += 3.0f;//度
	float sinValue = sinf(sinAngle * DX_PI_F / 180.0f);
	transform_.position_.y = baseY + sinValue * 50;

	std::list<SOLDIER*> psoldiers = GetParent()->FindGameObjects<SOLDIER>();
	for (SOLDIER* psoldier : psoldiers) {
		if (psoldier->CollideCircle(transform_.position_.x + 32.0f, transform_.position_.y + 32.0f, 20.0f)) {
			KillMe();
		}
	}
}

void Bird::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}
	DrawRectGraph(x, y, 0, 0, 64, 64, hImage, TRUE);
	//DrawCircle(x + 32.0f, y + 32.0f, 24.0f, GetColor(255, 0, 0),0);
}

bool Bird::CollideCircle(float x, float y, float r)
{
	//x,y,rが相手の円の情報
	//自分の円の情報
	float myCenterX = transform_.position_.x + 32.0f;
	float myCenterY = transform_.position_.y + 32.0f;
	float myR = 24.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if ((dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}

void Bird::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
	baseY = y;
}

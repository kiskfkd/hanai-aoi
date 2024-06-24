#include "Player.h"
#include <DxLib.h>
#include <assert.h>
#include "Stone.h"
#include "Camera.h"
#include "Field.h"
#include "Bird.h"
#include "TestScene.h"

namespace {
	const float MOVE_SPEED = 1.0f;
	const float GROUND = 400.0f;
	const float JUMP_HEIGHT = 64.0f * 4.0f;//ジャンプの高さ
	const float GRAVITY = 9.8f / 60.0f;//重力加速度
	//const float INITIALVELOCITY = 18.0f;

}
Player::Player(GameObject* parent) : GameObject(sceneTop)
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
	active = true;
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
	//移動
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

	//if (CheckHitKey(KEY_INPUT_D)) {
	//	transform_.position_.x += MOVE_SPEED;
	//	if (++frameCounter >= 8) {
	//		animFrame = (animFrame + 1) % 4;
	//		frameCounter = 0;
	//	}
	//	int hitX = transform_.position_.x + 50;
	//	int hitY = transform_.position_.y + 63;
	//	if (pField != nullptr) {
	//		int push = pField->CollisionRight(hitX, hitY);
	//		transform_.position_.x -= push;
	//	}
	//}
	//else if (CheckHitKey(KEY_INPUT_A)) {
	//	transform_.position_.x -= MOVE_SPEED;
	//	if (++frameCounter >= 8) {
	//		animFrame = (animFrame + 1) % 4;
	//		frameCounter = 0;
	//	}
	//}
	//else {
	//	animFrame = 0;
	//	frameCounter = 0;
	//}

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		if (prevSpaceKey == false) {
			if (onGround) {
				jumpSpeed = -sqrtf(2 * (GRAVITY)*JUMP_HEIGHT);
				onGround = false;
			}
		}
		prevSpaceKey = true;
	}
	else {
		prevSpaceKey = false;
	}
	jumpSpeed += GRAVITY;//速度 += 加速度
	transform_.position_.y += jumpSpeed; //座標 += 速度
	if (pField != nullptr) {
		//(50,64)と(14,64)も見る
		int pushR = pField->CollisionDown(transform_.position_.x + 50, transform_.position_.y + 64);
		int pushL = pField->CollisionDown(transform_.position_.x + 14, transform_.position_.y + 64);
		int push = max(pushR, pushL);//２つの足元のめり込みの大きい方
		if (push >= 1) {
			transform_.position_.y -= push - 1;
			jumpSpeed = 0.0f;
			onGround = true;
		}
		else {
			onGround = false;
		}
	}

	/*if (CheckHitKey(KEY_INPUT_SPACE)) {
		canJump = false;
	}
	if (canJump == false) {
		transform_.position_.y = 0.5 * GRAVITY * time_ * time_ - INITIALVELOCITY * time_ + GROUND;
		time_ += 0.5f;
		if (transform_.position_.y > GROUND) {
			transform_.position_.y = GROUND;
			time_ = 0.0f;
			canJump = true;
		}
	}*/
	if (CheckHitKey(KEY_INPUT_A)) {
		if (onactive == false) {
			if (active)
			{
				Stone* st = Instantiate<Stone>(GetParent());
				st->SetPosition(transform_.position_);
				active = false;
			}
			onactive = true;
		}
	}
	else {
		onactive = false;
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		if (onactive == false) {
			if (active)
			{
				Stone* st = Instantiate<Stone>(GetParent());
				st->SetPosition(transform_.position_);
				active = false;
			}
			onactive = true;
		}
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		if (onactive == false) {
			if (active)
			{
				Stone* st = Instantiate<Stone>(GetParent());
				st->SetPosition(transform_.position_);
				active = false;
			}
			onactive = true;
		}
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

	//ここでカメラ位置の調整
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

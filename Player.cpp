#include "Player.h"
#include <DxLib.h>
#include <assert.h>
#include "Stone.h"
#include"Camera.h"
#include"Field.h"
namespace
{
	const float MOVE_SPEED = 4.0f;
	const float GROUND = 575.0f;
	const float JUMP_HEIGHT = 64.0f * 4.0f;
	const float GRAVITY = 9.8f / 60.0f;
}

Player::Player(GameObject* parent) : GameObject(sceneTop)
{
	hImage = LoadGraph("Assets/aoi.png");
	assert(hImage > 0);
	transform_.position_.x = 10.0f;
	transform_.position_.y = GROUND;
	jumpSpeed = 0.0f;
	//jumpflag = false;
	onGround = true;
	frameCounter = 0;
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
	if (CheckHitKey(KEY_INPUT_D))
	{
		transform_.position_.x += MOVE_SPEED;
		if (++frameCounter >= 8) {
			animeFrame = (animeFrame + 1) % 4;
			frameCounter = 0;
		}
		int hitX = transform_.position_.x + 50;
		int hitY = transform_.position_.y + 63;
		Field* pField = GetParent()->FindChildObject<Field>();
	if(pField !=nullptr){
		int push = pField->CollsionRight(hitX, hitY);
		transform_.position_.x
	}
	}
	else if (CheckHitKey(KEY_INPUT_A))
	{
		transform_.position_.x -= MOVE_SPEED;
		if (++frameCounter >= 8) {
			animeFrame = (animeFrame + 1) % 4;
			frameCounter = 0;
		}

	}
	else {
		animeFrame = 0;
		frameCounter=0;
	}
	
	
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		//if (jumpflag == false)
		if (prevSpaceKey == false) {
			if (onGround){
				jumpSpeed = -sqrtf(2 * GRAVITY * JUMP_HEIGHT);
				onGround = false;
			}
		}
		prevSpaceKey = true;

		//jumpflag = true;
	}
	else {
		prevSpaceKey = false;
	}

	jumpSpeed += GRAVITY;
	transform_.position_.y +=jumpSpeed ;
	if (pField != nullptr) {
		int push = pField->CollisionDown(transform_.position_.x+50,transform_.position_.y+63)
			if (push > 0)
			{
				transform_.posision_.y -= push;
				jumpspeed = 0.0f;
				onGround = true;
		}
	}
	if (transform_.position_.y >= GROUND) {
		transform_.position_.y = GROUND;
		jumpSpeed = 0.0f;
		//jumpflag = false;
		onGround = true;
	}

	if (CheckHitKey(KEY_INPUT_M))
	{
		Stone* st = Instantiate<Stone>(GetParent());
		st->SetPosition(transform_.position_);
		Camera* cam = GetParent()->FindGameObject<Camera>();
		cam->SetValue(cam->SetValue());
	}
}
Camera* cam = GetParent()->FindGameObject<Camera>();
int x = (int)transform_.position_.x - cam->SetValue();
if (x > 400) {

}

void Player::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->SetValue();
	}
	DrawRectGraph(x, y, animeFrame*64, 0, 64, 64, hImage, TRUE);
}

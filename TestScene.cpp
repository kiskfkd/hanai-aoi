#include "TestScene.h"
#include "Player.h"
#include "Bird.h"
#include "Field.h"
#include "Camera.h"
#include "Banner.h"

//コンストラクタ
TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	Instantiate<Camera>(this);
	Field* pField = Instantiate<Field>(this);
	Instantiate<Player>(this);
	pField->Reset();
	Instantiate<Banner>(this);
	StartReady();
}

//更新
void TestScene::Update()
{
	switch (state) {
	case S_Ready:UpdateReady(); break;
	case S_Play:UpdatePlay(); break;
	case S_Clear: UpdateClear(); break;
	case S_Dead: UpdateDead(); break;
	}
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}

bool TestScene::CanMove()
{
	return (state == S_Play);
}

void TestScene::StartReady()
{
	state = S_Ready;
	readyTimer = 2.0f;//Readyの表示時間
	Banner* bn = FindGameObject<Banner>();
	bn->View(Banner::ViewID::V_Start);
	//Playerの初期化
	//敵の初期化
}

void TestScene::UpdateReady()
{
	readyTimer -= 1.0f / 60.0f;
	if (readyTimer <= 0.0f) {
		StartPlay();
	}
}

void TestScene::StartPlay()
{
	state = S_Play;
	Banner* bn = FindGameObject<Banner>();
	bn->View(Banner::ViewID::V_Nothing);
}

void TestScene::UpdatePlay()
{
}

void TestScene::UpdateClear()
{
}

void TestScene::StartDead()
{
	state = S_Dead;
	Banner* bn = FindGameObject<Banner>();
	bn->View(Banner::ViewID::V_GameOver);
}

void TestScene::UpdateDead()
{
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		StartReady();
	}
}

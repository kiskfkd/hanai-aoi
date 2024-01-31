#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// プレイヤーキャラ
/// </summary>
class Player : public GameObject
{
public:
	Player(GameObject* scene);
	~Player();
	void Update() override;
	void Draw() override;
private:
	int hImage;
	GameObject* sceneTop;
	bool prevSpaceKey;
	double jumpSpeed;
	bool jumpflag;
	bool onGround;
	int animeType;
	int animeFrame;
	int frameCounter;
};
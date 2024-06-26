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

	/// <summary>
	/// プレイヤーの座標をセットする
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	void SetPosition(int x, int y);
private:
	int hImage;
	GameObject* sceneTop;
	bool prevSpaceKey;
	float jumpSpeed;
	bool onGround;
	int animType; //状況
	int animFrame;//コマ
	int frameCounter;
	bool active;
	enum State {
		S_Walk = 0,
		S_Cry,
	};
	State state;
	int ttimer;
	int etimer;
	int stimer;
};
#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// ロボット（敵）
/// </summary>
class Enemy : public GameObject
{
public:
	Enemy(GameObject* scene);
	~Enemy();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// ロボットの座標をセットする
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	void SetPosition(int x, int y);

	//円の当たり判定をする
	bool CollideCircle(float x, float y, float r);
private:
	float sinAngle;
	int hImage;
	float baseY;//生成時のY座標
};


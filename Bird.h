#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// 鳥（敵）
/// </summary>
class Bird : public GameObject
{
public:
	Bird(GameObject* scene);
	~Bird();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// 鳥の座標をセットする
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

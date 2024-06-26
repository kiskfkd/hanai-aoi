#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// プレイヤーが投げる石
/// </summary>
class SOLDIER : public GameObject
{


public:
	SOLDIER(GameObject* scene);
	~SOLDIER();
	void Update() override;
	void Draw() override;
	void SetPosition(XMFLOAT3 pos);
	//円の当たり判定をする
	bool CollideCircle(float x, float y, float r);
private:
	int hImage;
	int timer;

};
#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// ƒvƒŒƒCƒ„[‚ª“Š‚°‚éÎ
/// </summary>
class SOLDIER : public GameObject
{


public:
	SOLDIER(GameObject* scene);
	~SOLDIER();
	void Update() override;
	void Draw() override;
	void SetPosition(XMFLOAT3 pos);
	//‰~‚Ì“–‚½‚è”»’è‚ğ‚·‚é
	bool CollideCircle(float x, float y, float r);
private:
	int hImage;
	int timer;

};
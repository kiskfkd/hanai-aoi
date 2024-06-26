#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// ƒvƒŒƒCƒ„[‚ª“Š‚°‚éÎ
/// </summary>
class TANK : public GameObject
{


public:
	TANK(GameObject* scene);
	~TANK();
	void Update() override;
	void Draw() override;
	void SetPosition(XMFLOAT3 pos);

private:
	int hImage;
	int timer;

};

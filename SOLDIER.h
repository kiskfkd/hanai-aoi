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

private:
	int hImage;
	int timer;

};
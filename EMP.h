#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// �v���C���[���������
/// </summary>
class EMP : public GameObject
{


public:
	EMP(GameObject* scene);
	~EMP();
	void Update() override;
	void Draw() override;
	void SetPosition(XMFLOAT3 pos);

private:
	int hImage;
	int timer;

};
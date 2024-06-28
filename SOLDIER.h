#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// �v���C���[���������
/// </summary>
class SOLDIER : public GameObject
{


public:
	SOLDIER(GameObject* scene);
	~SOLDIER();
	void Update() override;
	void Draw() override;
	void SetPosition(XMFLOAT3 pos);
	//�~�̓����蔻�������
	bool CollideCircle(float x, float y, float r);
private:
	int hImage;
	int timer;

};
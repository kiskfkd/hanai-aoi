#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// ���{�b�g�i�G�j
/// </summary>
class Enemy : public GameObject
{
public:
	Enemy(GameObject* scene);
	~Enemy();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// ���{�b�g�̍��W���Z�b�g����
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	void SetPosition(int x, int y);

	//�~�̓����蔻�������
	bool CollideCircle(float x, float y, float r);
private:
	float sinAngle;
	int hImage;
	float baseY;//��������Y���W
};


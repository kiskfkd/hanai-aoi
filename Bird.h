#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// ���i�G�j
/// </summary>
class Bird : public GameObject
{
public:
	Bird(GameObject* scene);
	~Bird();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// ���̍��W���Z�b�g����
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

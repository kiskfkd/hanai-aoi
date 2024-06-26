#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// �v���C���[�L����
/// </summary>
class Player : public GameObject
{
public:
	Player(GameObject* scene);
	~Player();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// �v���C���[�̍��W���Z�b�g����
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	void SetPosition(int x, int y);
private:
	int hImage;
	GameObject* sceneTop;
	bool prevSpaceKey;
	float jumpSpeed;
	bool onGround;
	int animType; //��
	int animFrame;//�R�}
	int frameCounter;
	bool active;
	enum State {
		S_Walk = 0,
		S_Cry,
	};
	State state;
	int ttimer;
	int etimer;
	int stimer;
};
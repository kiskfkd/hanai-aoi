#pragma once
#include "Engine/GameObject.h"

class Banner :public GameObject
{
public:
	Banner(GameObject* scene);
	~Banner();
	void Update() override;
	void Draw() override;
	enum ViewID {
		V_Start = 0,
		V_Clear,
		V_GameOver,
		V_Nothing,
	};
	void View(ViewID id);
private:
	int hImage;
	ViewID view;
	//�Q�[���I�[�o�[�\���p
	float transparency;//�����x
	float goY;//�Q�[���I�[�o�[�̎���Y���W
	float overTime;
};

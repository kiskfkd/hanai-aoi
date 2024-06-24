#pragma once
#include "Engine/GameObject.h"

//�e�X�g�V�[�����Ǘ�����N���X
class TestScene : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TestScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	bool CanMove();
private:
	enum State {
		S_Ready, //Ready�\����(2�b�Ԃ����[�Ƃ�\��)
		S_Play, //�Q�[����
		S_Clear, //�Q�[���N���A(�N���A��\�����ă{�^�����������܂ő҂�)
		S_Dead, //���S(�Q�[���I�[�o�[��\�����ă{�^�����������܂ő҂�)
	};
	State state; //�X�e�[�g�̒l��ێ�
	float readyTimer;
	void StartReady();
	void UpdateReady();
	void StartPlay();
	void UpdatePlay();
	void UpdateClear();
public:
	void StartDead();
private:
	void UpdateDead();
};
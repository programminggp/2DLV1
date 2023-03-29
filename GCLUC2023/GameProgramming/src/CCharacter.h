#pragma once
#include"CTask.h"
#include"CRectangle.h"
#include"CTexture.h"

#define VELOCITY 4.0f	//�ړ����x
/*
�L�����N�^�[�N���X
�Q�[���L�����N�^�̊�{�I�ȋ@�\���`����
*/
class CCharacterManager;

class CCharacter : public CRectangle, public CTask
{
	friend CTask;
	friend CCharacterManager;

public:
	enum class EState	//���
	{
		ENULL,     //��
		EMOVE,	   //�ړ�
		EMOVE2,    //�ړ�2
		EJUMP,	   //�W�����v
		EIDLING,   //�A�C�h�����O
		EATTACK,   //�U��
		EATTACK2,  //�U��2
		EDAMAGE,   //�_���[�W��
		EDEATH,    //���S
	};

private:
	CTexture* mpTexture;
	int mLeft,	mRight,mBottom,mTop;
	bool mEnabled;

protected:
	EState mState;
	float mVx;  //X�����x
	float mVy;  //Y�����x

public:
	//�R���X�g���N�^
	CCharacter(int priority);
	//�f�X�g���N�^
	~CCharacter();
	//��Ԃ��擾����
	EState State();

	//�`�揈��
	void Render();
	CTexture* Texture();
	void Texture(CTexture* pTexture,
		int left, int right, int bottom, int top);

	//�Փˏ���
	virtual void Collision(CCharacter* m, CCharacter* o) {}
	//�Փˏ���2
	virtual void Collision() {};

	bool Enabled();
	virtual void Update() = 0;
};
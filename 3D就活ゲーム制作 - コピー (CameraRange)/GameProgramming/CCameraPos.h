#ifndef CCAMERAPOS_H
#define CCAMERAPOS_H
#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"

class CCameraPos :public CCharacter{
public:
	static CCameraPos*mpCamera;
	//�f�t�H���g�R���X�g���N�^
	CCameraPos();

	//�X�V
	void Update();

	//�J�����̓����蔻��
	CCollider mColCam;
	
	//�Փˏ���
	void Collision(CCollider *mc, CCollider *yc);

	float mCameraSpeed;
	bool CanMove;//�v���C���[������\���ۂ�(�J�E���g�_�E���O�E�S�[����Ȃǂ͔�)
	
	//�R���C�_�̍X�V
	void TaskCollision();

	CVector mVPoint;
	float mVCamY;//�J�����̕���
};


#endif
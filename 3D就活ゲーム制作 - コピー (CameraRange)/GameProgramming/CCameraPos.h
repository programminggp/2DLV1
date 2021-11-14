#ifndef CCAMERAPOS_H
#define CCAMERAPOS_H
#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"

class CCameraPos :public CCharacter{
private:
	float mZoom_distance;
	float mCameraSpeed;
	//�J�����̓����蔻��
	CCollider mColCam;
public:
	static CCameraPos*mpCamera;	
	//�f�t�H���g�R���X�g���N�^
	CCameraPos();
	//�X�V����
	void Update();	
	//�Փˏ���
	void Collision(CCollider *mc, CCollider *yc);		
	//�R���C�_�̍X�V
	void TaskCollision();	
};


#endif
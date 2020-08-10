#ifndef CPLAYER_H
#define CPLAYER_H

#include "CCharacter.h"
//06
#include "CCollider.h"

#include "CXAudio2.h"

class CPlayer : public CCharacter {
public:
	CXAudio2 mAudio;
	CXAudio2 mAudio2;
	//12
	float mVelovcityJump;
	
	//06
	//�R���C�_�̒ǉ�
	CCollider mColBody;
	//�R���X�g���N�^�ŏ����ݒ�
	CPlayer();

	void Update();

	void Collision(CCollider *mycol, CCollider *youcol);

};

#endif

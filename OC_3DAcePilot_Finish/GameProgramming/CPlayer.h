#ifndef CPLAYER_H
#define CPLAYER_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
//
#include "CCollider.h"
/*
�v���C���[�N���X
�L�����N�^�N���X���p��
*/
class CPlayer : public CCharacter {
public:
	static CPlayer *sPlayer;
	//�R���C�_
	CCollider mLine[4];//�����R���C�_
	CCollider mCollider;
	CCollider mSearch;
	CCharacter *mpTarget;
	int mFireMissile;
	int mFireBullet;
	float mVelocity;
	//�f�t�H���g�R���X�g���N�^
	CPlayer();
	//�X�V����
	void Update();
	//�Փˏ���
	void Collision(CCollider *mc, CCollider *yc);

};

#endif

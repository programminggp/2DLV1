#ifndef CPLAYER_H
#define CPLAYER_H
//�L�����N�^�[�N���X�̃C���N���[�h
#include"CCharacter.h"
//�e�N���X�̃C���N���[�h
#include"CBullet.h"
//�����R���C�_�N���X�̃C���N���[�h
#include"CColliderLine.h"
//
#include "CText.h"

/*
�v���C���[�N���X
�L�����N�^�[�N���X���p��
*/

class CPlayer : public CCharacter {
public:
	//CBullet�N���X�̃C���X�^���X�ϐ�
	/*CBullet bullet;*/
	CPlayer();
	//�X�V����
	void Update();
	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);
	//
	void CPlayer::TaskCollision();
	//
	void Render();
	//
	static CPlayer* Get();
private:

	CColliderLine mLine; //�����R���C�_
	CColliderLine mLine2; //�����R���C�_2
	CColliderLine mLine3; //�����R���C�_3
	CCollider mCollider;	//�{�̗p�R���C�_

	CText mText;

	//�v���C���[�̃C���X�^���X
	static CPlayer* spInstance;
};
#endif 


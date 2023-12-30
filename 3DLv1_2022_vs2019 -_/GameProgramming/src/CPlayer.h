#ifndef CPLAYER_H
#define CPLAYER_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter3.h"
#include "CInput.h"
#include "CBullet.h"
#include "CColliderLine.h"

/*
�v���C���[�N���X
�L�����N�^�N���X���p��
*/
class CPlayer : public CCharacter3 {
public:
	static int Botan();
	static int Gate();
	//�C���X�^���X�̃|�C���^�̎擾
	static CPlayer* Instance();
	void Collision();
	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);
	CPlayer::CPlayer()
		: mLine1(this, &mMatrix, CVector(0.0f, 0.0f, -14.0f), CVector(0.0f, 0.0f, 17.0f))
		, mLine2(this, &mMatrix, CVector(0.0f, 5.0f, -8.0f), CVector(0.0f, -3.0f, -8.0f))
		, mLine3(this, &mMatrix, CVector(9.0f, 0.0f, -8.0f), CVector(-9.0f, 0.0f, -8.0f))
	{
		//�C���X�^���X�̐ݒ�
		spInstance = this;
	}
	//CPlayer(�ʒu�A��]�A�X�P�[��)
	CPlayer(const CVector& pos, const CVector& rot, const CVector& scale);
	//�X�V����
	void Update();
private:
	static int sBotan;
	static int sGate;
	//�v���C���[�̃C���X�^���X
	static CPlayer* spInstance;
	CColliderLine mLine1;//�����R���C�_
	CColliderLine mLine2;//�����R���C�_
	CColliderLine mLine3;//�����R���C�_
	CInput mInput;
};

#endif
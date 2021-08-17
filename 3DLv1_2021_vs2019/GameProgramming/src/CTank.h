#ifndef CTANK_H
#define CTANK_H

//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
//�R���C�_�N���X�̃C���N���[�h
#include "CCollider.h"

/*
��C�N���X
*/
class CTank3 : public CCharacter
{
public:
	CTank3(CCharacter* parent);
	void Update();
//	void Render();
private:
	static CModel mModel;
	CCharacter* mpParent;
	CMatrix mOffset;
};

//class CTank2 : public CTransform
/*
�C���N���X
*/
class CTank2 : public CCharacter
{
public:
	CTank2(CCharacter* parent);
	void Update();
private:
	static CModel mModel;
	CCharacter* mpParent;
	CMatrix mOffset;
};

/*
��ԃN���X
�L�����N�^�N���X���p��
*/
class CTank : public CCharacter {
public:
	//�R���X�g���N�^
	CTank();
	//Tank(�ʒu, ��], �g�k)
	CTank(const CVector& position, const CVector& rotation, const CVector& scale);
	//�X�V����
	void Update();
	//�Փˏ���
	//Collision(�R���C�_1, �R���C�_2)
	void Collision(CCollider* m, CCollider* o);
	void TaskCollision();
	CCharacter* Tank();
private:
	//���f���f�[�^
	static CModel mModel;
	//�R���C�_
	CCollider mCollider;
	int mHp;	//�q�b�g�|�C���g
	int mFireCount;
	CTank2 *mpTank2;
};


#endif


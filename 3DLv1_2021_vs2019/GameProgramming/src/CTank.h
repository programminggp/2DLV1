#ifndef CTANK_H
#define CTANK_H

//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
//�R���C�_�N���X�̃C���N���[�h
#include "CCollider.h"


class CTank3 : public CTransform
{
public:
	CTank3(CTransform* parent);
	void Update();
	void Render();
private:
	static CModel mModel;
	CTransform* mpParent;
	CMatrix mOffset;
};

class CTank2 : public CTransform
{
public:
	CTank2(CTransform* parent);
	void Update();
	void Render();
private:
	static CModel mModel;
	CTransform* mpParent;
	CTank3 mTank;
	CMatrix mOffset;
};

/*
�G�l�~�[�N���X
�L�����N�^�N���X���p��
*/
class CTank : public CCharacter {
public:
	//�R���X�g���N�^
	CTank();
	//CEnemy(�ʒu, ��], �g�k)
	CTank(const CVector& position, const CVector& rotation, const CVector& scale);
	//�X�V����
	void Update();
	void Render();
	//�Փˏ���
	//Collision(�R���C�_1, �R���C�_2)
	void Collision(CCollider* m, CCollider* o);
	void TaskCollision();
	CTransform* Tank();
private:
	//���f���f�[�^
	static CModel mModel;
	//�R���C�_
	CCollider mCollider;
	CCharacter* mpPlayer;	//�v���C���[�̃|�C���^
	CCollider mColSearch;	//�T�[�`�p�R���C�_
	int mHp;	//�q�b�g�|�C���g
	int mFireCount;
	CVector mPoint;	//�ڕW�n�_
	CTank2 mTank2;
};


#endif


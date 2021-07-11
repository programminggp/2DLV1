#ifndef CCOLLIDER_H
#define CCOLLIDER_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
//�g�����X�t�H�[���N���X�̃C���N���[�h
#include "CTransform.h"
/*
�R���C�_�N���X
�Փ˔���f�[�^
*/
class CCollider : public CTransform, public CTask {
public:
	enum ETag
	{
		EBODY,		//�{��
		ESEARCH,	//�T�[�`�p
	};
	ETag mTag;
	//�R���C�_�^�C�v
	enum EType {
		ESPHERE,//���R���C�_
		ETRIANGLE,//�O�p�R���C�_
		ELINE, //�����R���C�_
	};
	EType mType;//�R���C�_�^�C�v
	//���_
	CVector mV[3];

	CCharacter *mpParent;//�e
	CMatrix *mpMatrix;//�e�s��
	float mRadius;	//���a

	//�f�t�H���g�R���X�g���N�^
	CCollider();

	//�R���X�g���N�^
	//CCollider(�e, �s��, �ʒu, ���a)
	CCollider(CCharacter *parent, CMatrix *matrix, CVector position, float radius);
	//�`��
	void Render();
	~CCollider();
	//�Փ˔���
	//Collision(�R���C�_1, �R���C�_2)
	//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
	static bool Collision(CCollider *m, CCollider *o);
	//CollisionTriangleLine(�O�p�R���C�_, �����R���C�_, �����l)
	//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
	//�����l:�Փ˂��Ȃ��ʒu�܂Ŗ߂��l
	static bool CollisionTriangleLine(CCollider *triangle, CCollider *line, CVector *adjust);
	//CollisionTriangleSphere(�O�p�R���C�_, ���R���C�_, �����l)
	//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
	//�����l:�Փ˂��Ȃ��ʒu�܂Ŗ߂��l
	static bool CollisionTriangleSphere(CCollider *triangle, CCollider *sphere, CVector *adjust);
	//�D��x�̕ύX
	virtual void ChangePriority();
};

#endif

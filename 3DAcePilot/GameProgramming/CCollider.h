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
	//�R���C�_�̎��
	enum ETag {
		ENONE,
		EBODY,//�@��
		ESEARCH,//�T�[�`
	};
	ETag mTag;
	//�R���C�_�^�C�v
	enum EType {
		ESPHERE,
		ETRIANGLE,
		ELINE, //�����R���C�_
	};
	EType mType;
	//���_
	CVector mV[3];
	CCharacter *mpParent;//�e
	float mRadius;	//���a
	//?
	//�f�t�H���g�R���X�g���N�^
	CCollider();
	//�R���X�g���N�^
	//CCollider(�e, �ʒu, ��], �g�k, ���a)
	CCollider(CCharacter *parent, CVector position, CVector rotation, CVector scale, float radius);
	//�R���X�g���N�^�i�O�p�R���C�_�j
	//CCollider(�e, ���_1, ���_2, ���_3)
	CCollider(CCharacter *parent, const CVector &v0, const CVector &v1, const CVector &v2);
	//�O�p�R���C�_�̐ݒ�
	//SetTriangle(�e, ���_1, ���_2, ���_3)
	void SetTriangle(CCharacter *parent, const CVector &v0, const CVector &v1, const CVector &v2);
	//�R���X�g���N�^�i�����R���C�_�j
	//CCollider(�e, ���_1, ���_2)
	CCollider(CCharacter *parent, const CVector &v0, const CVector &v1);
	//�����R���C�_�̐ݒ�
	//SetLine(�e, ���_1, ���_2)
	void SetLine(CCharacter *parent, const CVector &v0, const CVector &v1);
	~CCollider();
	//�`��
	void Render();
	//�Փ˔���
	//Collision(�R���C�_1, �R���C�_2)
	//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
	static bool Collision(CCollider *m, CCollider *y);
	//CollisionTriangleLine(�O�p�R���C�_, �����R���C�_, �����l)
	//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
	//�����l:�Փ˂��Ȃ��ʒu�܂Ŗ߂��l
	static bool CollisionTriangleLine(CCollider *triangle, CCollider *line , CVector *adjust);
};

#endif

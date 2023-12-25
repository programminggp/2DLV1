#ifndef CCOLLIDER_H
#define CCOLLIDER_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
//�g�����X�t�H�[���N���X�̃C���N���[�h
#include "CTransform.h"
class CCollisionManager;
class CColliderTask;
/*
�R���C�_�N���X
�Փ˔���f�[�^
*/
class CCollider : public CTransform, public CTask {
	friend CCollisionManager;
public:
	//�R���C�_�^�C�v
	enum EType {
		ESPHERE,//���R���C�_
		ETRIANGLE,//�O�p�R���C�_
		ELINE, //�����R���C�_
		ECAPSUL, //�J�v�Z���R���C�_
	};
	//�e�|�C���^�̎擾
	CCharacter* Parent();
	enum ETag
	{
		EBODY,		//�{��
		ESEARCH,	//�T�[�`�p
		EWEAPON,	//����
		EGROUND,	//�n��
	};

	//�f�t�H���g�R���X�g���N�^
	CCollider();
//	CCollider(bool flgAdd);

	//�R���X�g���N�^
	//CCollider(�e, �s��, �ʒu, ���a)
	CCollider(CCharacter *parent, CMatrix *matrix, const CVector& position, float radius);
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
	static bool CollisionTriangleSphere(CCollider* triangle, CCollider* sphere, CVector* adjust);
	//CollisionCapsule(�J�v�Z���R���C�_�P, �J�v�Z���R���C�_�Q, �����l)
	//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
	//�����l:�J�v�Z���R���C�_�P���Փ˂��Ȃ��ʒu�܂Ŗ߂��l
	static bool CollisionCapsule(CCollider* m, CCollider* o, CVector* adjust);

	//VectorLineMinDist(���P�J�n, ���P�I��, ���Q�J�n, ���Q�I��)
	//return:���Ɛ��Ƃ̍ŒZ�x�N�g��
	static CVector VectorLineMinDist(const CVector& Start1, const CVector& End1, const CVector& Start2, const CVector& End2);
	//�D��x�̕ύX
	virtual void ChangePriority();
	//�R���C�_��ނ̎擾
	EType Type();
	//�^�O�̎擾
	ETag Tag();
	//�^�O�̐ݒ�
	//Tag(�^�O)
	void Tag(ETag tag);
	//Matrix(CMatrix* p)
	void Matrix(CMatrix* p);

	void Update();
	CVector mCenter;

	CColliderTask* mpColliderTask[9];
	void Radius(float r)
	{
		mRadius = r;
	}
protected:
	CCharacter* mpParent;//�e
	CMatrix* mpMatrix;//�e�s��
	float mRadius;	//���a
	EType mType;//�R���C�_�^�C�v
	//���_
	CVector mV[4];
	ETag mTag;
};

class CColliderTask : public CTask
{
public:
	CColliderTask(CCollider* col);
	CCollider* Collider();
	void Collider(CCollider* col);
	~CColliderTask();
private:
	CCollider* mpCollider;
};

#endif
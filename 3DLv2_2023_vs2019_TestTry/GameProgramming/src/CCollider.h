#ifndef CCOLLIDER_H
#define CCOLLIDER_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter3.h"
class CCollisionManager;
/*
�R���C�_�N���X
�Փ˔���f�[�^
*/
class CCollider : public CTransform,public CTask {
	friend CCollisionManager;
public:
	//
	static bool CollisionCapsuleTriangle(CCollider* capsule, CCollider* triangle, CVector* adjust);
	//CVector* V()
	//{
	//	return mV;
	//}
	const CVector& V(int i)
	{
		return mV[i];
	}
	//�J�v�Z���R���C�_�ƃJ�v�Z���R���C�_�̏Փ˔���
	//static bool CollisionCapsuleCapsule(�J�v�Z��1, �J�v�Z��2, �����l)
	//�����l�F�Փ˂��Ă��Ώꍇ�A�J�v�Z��1���Փ˂��Ȃ��ʒu�܂ňړ�����ړ���
	//�߂�l�Ftrue�@�Փ˂��Ă���@false�@�Փ˂��Ă��Ȃ�
	static bool CollisionCapsuleCapsule(CCollider* m, CCollider* o, CVector* adjust);
	enum class ETag {
		EBODY,	//��
		ESWORD,	//��
	};
	ETag Tag();// �^�O�̎擾

	void Matrix(CMatrix* m);
	//�D��x�̕ύX
	virtual void ChangePriority();
	//�D��x�̕ύX
	void ChangePriority(int priority);
	//�R���C�_�^�C�v
	enum EType {
		ESPHERE,//���R���C�_
		ETRIANGLE,//�O�p�R���C�_
		ELINE, //�����R���C�_
		ECAPSULE, //�J�v�Z���R���C�_
	};

	EType Type();
	//CollisionTriangleLine(�O�p�R���C�_, �����R���C�_, �����l)
	//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
	//�����l:�Փ˂��Ȃ��ʒu�܂Ŗ߂��l
	static bool CollisionTriangleLine(CCollider* triangle, CCollider* line, CVector* adjust);
	//CollisionTriangleSphere(�O�p�R���C�_, ���R���C�_, �����l)
	//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
	//�����l:�Փ˂��Ȃ��ʒu�܂Ŗ߂��l
	static bool CollisionTriangleSphere(CCollider* triangle, CCollider* sphere, CVector* adjust);

	//�f�t�H���g�R���X�g���N�^
	CCollider();

	//�Փ˔���
	//Collision(�R���C�_1, �R���C�_2)
	//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
	static bool Collision(CCollider* m, CCollider* o);

	~CCollider();
	//�R���X�g���N�^
	//CCollider(�e, �e�s��, �ʒu, ���a)
	CCollider(CCharacter3* parent, CMatrix* matrix,
		const CVector& position, float radius, ETag tag = ETag::EBODY);
	//�e�|�C���^�̎擾
	CCharacter3* Parent();
	//�`��
	void Render();

protected:
	ETag mTag;//�^�O
	EType mType;//�R���C�_�^�C�v
	//���_
	CVector mV[4];

	CCharacter3* mpParent;//�e
	CMatrix* mpMatrix;//�e�s��
	float mRadius;	//���a
};
#endif
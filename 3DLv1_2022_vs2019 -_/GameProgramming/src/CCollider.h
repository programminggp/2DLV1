#ifndef CCOLLIDER_H
#define CCOLLIDER_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter3.h"

#define COLLIDERTASK_SIZE 27

/*
�R���C�_�N���X
�Փ˔���f�[�^
*/
class CCollisionManager;
class CCollisionManager2;
class CColliderTask;

class CCollider : public CTransform,public CTask {
	friend CCollisionManager;
	friend CCollisionManager2;
public:
	//�D��x�̕ύX
	virtual void ChangePriority();
	//�D��x�̕ύX
	void ChangePriority(int priority);
	//ColliderTriangleSphere(�O�p�R���C�_�A���R���C�_�A�����l)
	//return:true(�Փ˂��Ă���)false(�Փ˂��Ă��Ȃ�)
	// �����l:�Փ˂��Ȃ��ʒu�܂Ŗ߂��l
	static bool CCollider::CollisionTriangleSphere(CCollider* triangle, CCollider* sphere,
		CVector* adjust);
	//CollisionTriangleLine(�O�p�R���C�_�A�����R���C�_�A�����l)
	// return:true(�Փ˂��Ă���)false(�Փ˂��Ă��Ȃ�)
	// �����l:�Փˎs���ʒu�܂Ŗ߂��l
	static bool CollisionTriangleLine(CCollider* triangle, CCollider* line, CVector* adjust);
	//CollisionTriangleBotan(�O�p�R���C�_�A�{�^���R���C�_�A�����l)
	// return:true(�Փ˂��Ă���)false(�Փ˂��Ă��Ȃ�)
	// �����l:�Փˎs���ʒu�܂Ŗ߂��l
	static bool CollisionTriangleBotan(CCollider* triangle, CCollider* botan, CVector* adjust);
	//�R���C�_�^�C�v
	enum EType {
		ESPHERE,//���R���C�_
		ETRIANGLE,//�O�p�R���C�_
		ELINE,//�����R���C�_
		EBOTAN,//�{�^��
	};
	//�f�t�H���g�R���X�g���N�^
	CCollider();
	//�Փ˔���
	//Collision(�R���C�_�P�A�R���C�_�Q)
	//return:ture(�Փ˂��Ă���)false(�Փ˂��Ă��Ȃ�)
	static bool Collision(CCollider* m, CCollider* o);
	~CCollider();
	//�R���X�g���N�^
	//CCollider(�e�A�e�s��A�ʒu�A���a)
	CCollider(CCharacter3* parent, CMatrix* matrix,
		const CVector& position, float radius);
	//�e�|�C���^�̎擾
	CCharacter3* Parent();
	//�`��
	void Render();
protected:
	CVector mCenter;
	CColliderTask* mpColliderTask[COLLIDERTASK_SIZE];
	EType mType;//�R���C�_�^�C�v
	//���_
	CVector mV[4];
	CCharacter3* mpParent; //�e
	CMatrix* mpMatrix; //�e�s��
	float mRadius; //���a
public:
	EType Type();
};
#endif

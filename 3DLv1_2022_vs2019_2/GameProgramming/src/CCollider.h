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
	//�Փ˔���
	//Collision(�R���C�_1, �R���C�_2)
	//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
	static bool Collision(CCollider* m, CCollider* o);

	~CCollider();
	//�R���X�g���N�^
	//CCollider(�e, �e�s��, �ʒu, ���a)
	CCollider(CCharacter3* parent, CMatrix* matrix,
		const CVector& position, float radius);
	//�e�|�C���^�̎擾
	CCharacter3* Parent();
	//�`��
	void Render();
protected:
	CCharacter3* mpParent;//�e
	CMatrix* mpMatrix;//�e�s��
	float mRadius;	//���a
};
#endif

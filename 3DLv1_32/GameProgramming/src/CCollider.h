#ifndef CCOLLIDER_H
#define CCOLLIDER_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
//�g�����X�t�H�[���N���X�̃C���N���[�h
#include"CTransform.h"
//�^�X�N�N���X�̃C���N���[�h
#include"CTask.h"
//�R���W�����}�l�[�W���N���X�̐錾
class CCollisionManager;
/*
�R���C�_�N���X
�Փ˔���N���X
*/
class CCollider : public CTransform,public CTask {
public:
	//�R���C�_�^�C�v
	enum EType {
		ESPHERE,//���R���C�_
		ETRIANGLE,//�O�p�R���C�_
		ELINE,//�����R���C�_
	};
	//�f�t�H���g�R���X�g���N�^
	CCollider();
	//friend �R���W�����}�l�[�W���N���X
	friend CCollisionManager;
	//CollisionTriangleLine(�O�p�R���C�_,�����R���C�_,�����l)
	//retrun:true(�Փ˂��Ă���)false(�Փ˂��Ă��Ȃ�)
	//�����l:�Փ˂��Ȃ��ʒu�܂Ŗ߂��l
	static bool CollisionTriangleLine(CCollider* triangle, CCollider* line, CVector* adjust);
	//�R���X�g���N�^
	//CCollider(�e,�e�s��,�ʒu,���a)
	CCollider(CCharacter* parent, CMatrix* matrix,
		const CVector& position, float radius);
	//�f�X�g���N�^
	~CCollider();
	//�e�|�C���^�̎擾
	CCharacter* Parent();
	//�`��
	void Render();
	//�Փ˔���
	//Collision(�R���C�_1,�R���C�_2)
	//retrun:true(�Փ˂��Ă���)false(�Փ˂��Ă��Ȃ�)
	static bool Collision(CCollider* m, CCollider* o);
	//Type���\�b�h(mType�̒l��Ԃ�)
	int Type();
protected:
	EType mType;//�R���C�_�^�C�v
	//���_
	CVector mV[3];
	CCharacter* mpParent;//�e
	CMatrix* mpMatrix;//�e�s��
	float mRadius;//���a

};
#endif 


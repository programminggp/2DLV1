#ifndef CCHARACTER_H
#define CCHARACTER_H
//�x�N�g���N���X�̃C���N���[�h
#include "CVector.h"
//���f���N���X�̃C���N���[�h
#include "CModel.h"
//�}�g���N�X�N���X�̃C���N���[�h
#include "CMatrix.h"
//�^�X�N�N���X�̃C���N���[�h
#include "CTask.h"
//#include "CCollider.h"
//�R���C�_�N���X�̐錾
class CCollider;
/*
�L�����N�^�[�N���X
�Q�[���L�����N�^�̊�{�I�ȋ@�\���`����
*/
class CCharacter : public CTask {
public:
	//���
	enum ETag {
		ENONE,	//�����l
		EPOINT,	//�|�C���g
		EPLAYER,//�v���C���[
		EAIRBASE,//��R��n
		EMISSILE,//�~�T�C��
		EENEMY, //�G
	};
	ETag mTag;
//	CCharacter *mpParent;	//�e
	CVector mPosition; //�ʒu
	CVector mRotation; //��]
	CVector mScale; //�g��k��
	CModel *mpModel; //���f���̃|�C���^
	CMatrix mMatrix; //�����s��
	CMatrix mMatrixTranslate; //���s�ړ��s��
	CMatrix mMatrixRotate; //��]�s��
	CMatrix mMatrixScale; //�g��k���s��
	//22
	CCharacter();
	~CCharacter();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
	//�Փˏ���
	virtual void Collision(CCollider *mycol, CCollider *youcol) {}
	//
	//void ChangePriority(int priority);
};

#endif

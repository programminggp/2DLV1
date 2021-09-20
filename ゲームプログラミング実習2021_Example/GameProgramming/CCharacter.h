#ifndef CCHARACTER_H
#define CCHARACTER_H
//�ϊ��s��N���X�̃C���N���[�h
#include "CTransform.h"
//���f���N���X�̃C���N���[�h
#include "CModel.h"
//
#include "CTask.h"
//�R���C�_�N���X�̐錾
class CCollider;

/*
�L�����N�^�[�N���X
�Q�[���L�����N�^�̊�{�I�ȋ@�\���`����
*/
class CCharacter : public CTransform ,public CTask {
public:
	enum ETag 
	{
		EZERO,		//�����l
		EPLAYER,	//�v���C���[
		EENEMY,		//�G
		EBULLETPLAYER,	//�v���C���[�e
		EBULLETENEMY,	//�G�e
	};
	ETag mTag;
	CModel *mpModel; //���f���̃|�C���^
	//�`�揈��
	void Render();
	//�f�X�g���N�^
	~CCharacter();
	//�R���X�g���N�^
	CCharacter();
	//�Փˏ���
	virtual void Collision(CCollider *m, CCollider *o) {}

};

#endif

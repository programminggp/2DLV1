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
	//���f���̐ݒ�
	//Model(���f���N���X�̃|�C���^)
	void Model(CModel *m);
	//�^�O�̎擾
	ETag Tag();
	//�`�揈��
	void Render();
	//�f�X�g���N�^
	~CCharacter();
	//�R���X�g���N�^
	CCharacter();
	//�Փˏ���
	virtual void Collision(CCollider *m, CCollider *o) {}
protected:
	CModel* mpModel; //���f���̃|�C���^
	ETag mTag;
};

#endif

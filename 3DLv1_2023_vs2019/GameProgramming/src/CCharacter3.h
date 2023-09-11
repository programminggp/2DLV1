#ifndef CCHARACTER3_H
#define CCHARACTER3_H
//�ϊ��s��N���X�̃C���N���[�h
#include "CTransform.h"
//���f���N���X�̃C���N���[�h
#include "CModel.h"
#include "CTask.h"
//�R���C�_�N���X�̐錾
class CCollider;

/*
�L�����N�^�[�N���X
�Q�[���L�����N�^�̊�{�I�ȋ@�\���`����
*/
class CCharacter3 : public CTransform, public CTask {
public:
	//�Փˏ���
	virtual void Collision(CCollider* m, CCollider* o) {}
	//�R���X�g���N�^
	CCharacter3();
	//�R���X�g���N�^
	CCharacter3(int priority);
	//�f�X�g���N�^
	~CCharacter3();
	//���f���̐ݒ�
	//Model(���f���N���X�̃|�C���^)
	void Model(CModel* m);
	//�`�揈��
	void Render();
protected:
	CModel* mpModel; //���f���̃|�C���^
};

#endif

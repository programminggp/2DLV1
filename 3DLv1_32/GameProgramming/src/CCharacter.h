#ifndef CCHARACTER_H
#define CCHARACTER_H

//�ϊ��s��N���X�̃C���N���[�h
#include"CTransform.h"
//���f���N���X�̃C���N���[�h
#include"CModel.h"
//�^�X�N�N���X�̃C���N���[�h
#include"CTask.h"
//�R���C�_�N���X�̐錾
class CCollider;
/*
�L�����N�^�[�N���X
�Q�[���L�����N�^�̊�{�I�ȋ@�\���`����
*/

class CCharacter : public CTransform,public CTask{
protected:
	CModel* mpModel; //���f���̃|�C���^
public:
	//���f���̐ݒ�
	//Model(���f���N���X�̃|�C���^)
	void Model(CModel* m);
	//�`�揈��
	void Render();
	//�R���X�g���N�^
	CCharacter();
	//�f�X�g���N�^
	~CCharacter();
	//�Փˏ���
	virtual void Collision(CCollider *m,CCollider *o){}
};
#endif 



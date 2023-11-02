#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H
//�^�X�N�N���X�̃C���N���[�h
#include "CTask.h"
#include "CCollider.h"

//�Փˏ����͈͂�藣��Ă���R���C�_�͏Փˏ������Ȃ�
#define COLLISIONRANGE 30

/*
�^�X�N�}�l�[�W��
�^�X�N���X�g�̊Ǘ�
*/
class CTaskManager {
public:
	void Collision(CCollider* c, int range);

	//�f�t�H���g�R���X�g���N�^
	CTaskManager();
	void Collision();
	//�^�X�N�̍폜
	void Delete();
	//���X�g����폜
	//Remove(�^�X�N�̃|�C���^)
	void Remove(CTask* task);
	//�f�X�g���N�^
	virtual ~CTaskManager();
	//���X�g�ɒǉ�
	//Add(�^�X�N�̃|�C���^)
	void Add(CTask* addTask);
	//�X�V
	void Update();
	//�`��
	void Render();
protected:
	CTask mHead;//�擪�^�X�N
	CTask mTail;//�ŏI�^�X�N
};

#endif

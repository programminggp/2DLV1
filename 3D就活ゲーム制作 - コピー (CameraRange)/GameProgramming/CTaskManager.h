#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H
//�^�X�N�N���X�̃C���N���[�h
#include "CTask.h"

/*
�^�X�N�}�l�[�W��
�^�X�N���X�g�̊Ǘ�
*/
class CTaskManager {
private:
	static CTaskManager *instance;
protected:
	CTask *mpHead;	//�擪�|�C���^
public:
	static CTaskManager *Get();

//	CTask *mpTail;	//�Ō�|�C���^
	//�f�t�H���g�R���X�g���N�^
	CTaskManager();
	//�f�X�g���N�^
	virtual ~CTaskManager();
	//���X�g�ɒǉ�
	//Add(�^�X�N�̃|�C���^)
	void Add(CTask *task);
	//�X�V
	void Update();
	//�`��
	void Render();
	//22
	//���X�g����폜
	//Remove(�^�X�N�̃|�C���^)
	void Remove(CTask *task);
	//22
	//�^�X�N�̍폜
	void Delete();
	//
	void ChangePriority(CTask *t, int p);//�u���[�N�|�C���g�̌����H

	
	
	void Destroy();

	void Disabled();

	void TaskCollision();
};

//�^�X�N�}�l�[�W��y�̊O���Q��
extern CTaskManager TaskManager;

#endif

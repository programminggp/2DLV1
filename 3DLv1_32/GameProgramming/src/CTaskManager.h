#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H
//�^�X�N�N���X�̃C���N���[�h
#include"CTask.h"

/*
* �^�X�N�}�l�[�W��
* �^�X�N���X�g�̊Ǘ�
*/
class CTaskManager{
public:
	//�C���X�^���X�̎擾
	static CTaskManager* Get();
	
	//�f�X�g���N�^
	virtual ~CTaskManager();
	//���X�g�ɒǉ�
	//Add(�^�X�N�̃|�C���^)
	void Add(CTask* addTask);
	//�X�V
	void Update();
	//�`��
	void Render();
	//���X�g����̍폜
	//Remove(�^�X�N�̃|�C���^)
	void Remove(CTask* task);
	//�^�X�N�̍폜
	void Delete();

protected:
	//�f�t�H���g�R���X�g���N�^
	CTaskManager();
	CTask mHead;//�擪�^�X�N
	CTask mTail;//�ŏI�^�X�N

private:
	//�^�X�N�}�l�[�W���̃C���X�^���X
	static CTaskManager* mpInstance;
};



#endif


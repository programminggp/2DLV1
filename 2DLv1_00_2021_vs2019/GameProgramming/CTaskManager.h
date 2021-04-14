#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H

//�^�X�N�N���X�C���N���[�h
#include"CTask.h"

//�^�X�N�}�l�[�W���̊O���Q��

/*
�^�X�N�}�l�[�W��
�^�X�N���X�g�Ǘ�
*/
class CTaskManager{
public:
	CTask *mpHead;//�擪�|�C���g
	CTask *mpRHead;//�擪�|�C���g

	//�f�t�H���g�R���X�g���N�^
	CTaskManager();

	//�f�X�g���N�^
	virtual~CTaskManager();

	//���X�g�������
	void Remove(CTask*task);
	void RemoveR(CTask*task);

	//���X�g�ɒǉ�
	//Add(�^�X�N�̃|�C���^)
	void Add(CTask *task, int priority, int priorityr);
	void Add(CTask *task);
	void AddR(CTask *task);

	void Collision();

	void AllDisable();
	//�X�V
	void Update();

	//�`��
	void Render();

	////�����̊m�F
	//void DeleteCheck();

	//�^�X�N����
	void Delete();

	//�^�X�N�̗D��x�̕ύX
	void Changepriority(CTask*task,int priority);

	//�^�X�N�S����
	void AllDelete();

};

extern CTaskManager TaskManager;

#endif
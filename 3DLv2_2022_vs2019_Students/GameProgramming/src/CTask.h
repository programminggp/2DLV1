#ifndef CTASK_H
#define CTASK_H

class CTaskManager;
class CCollisionManager;

/*
�^�X�N�N���X
�^�X�N���X�g�̗v�f
*/
class CTask {
	friend CTaskManager;
	friend CCollisionManager;
public:
	//�f�t�H���g�R���X�g���N�^
	CTask()
		: mpNext(nullptr), mpPrev(nullptr), mPriority(0), mEnabled(true) {}
	//�f�X�g���N�^ virtual�ɂ��Ȃ��Ǝq�N���X�̃f�X�g���N�^���Ă΂�Ȃ�
	virtual ~CTask() {}
	//�X�V
	virtual void Update() {}
	//�`��
	virtual void Render() {}
	//�Փˏ���
	virtual void TaskCollision() {}
protected:
	int mPriority;	//�D��x
	bool mEnabled;	//�L���t���O
private:
	CTask* mpNext;//���̃|�C���^
	CTask* mpPrev;//�O�̃|�C���^
};

#endif

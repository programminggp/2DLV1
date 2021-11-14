#ifndef CTASK_H
#define CTASK_H

class CTaskManager;
class CCollisionManager;
/*
�^�X�N�N���X
�^�X�N���X�g�̗v�f
*/
class CTask {
private:
	CTask *mpNext;	//���̃|�C���^
	CTask *mpPrev;	//�O�̃|�C���^
	int mPriority;	//�D��x
	bool mEnabled;	//�L���t���O
public:
	void SetPriority(int priority){
		mPriority = priority;
	}
	int GetPriority(){
		return mPriority;
	}
	void SetEnabled(bool enabled){
		mEnabled = enabled;
	}
	bool GetEnabled(){
		return mEnabled;
	}
	//�t�����h�N���X�̃N���X�ł�private�g�p�\
	friend CTaskManager;
	friend CCollisionManager;

	//�f�t�H���g�R���X�g���N�^
	CTask()
		: mpNext(0), mpPrev(0), mPriority(0), mEnabled(true) {}
	//�f�X�g���N�^
	virtual ~CTask() {}
	//�X�V
	virtual void Update() {}
	//�`��
	virtual void Render() {}

	virtual void TaskCollision() {}
};

#endif

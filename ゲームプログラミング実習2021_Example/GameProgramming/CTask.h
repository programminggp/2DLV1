#ifndef CTASK_H
#define CTASK_H
/*
�^�X�N�N���X
�^�X�N���X�g�̗v�f
*/
class CTask {
public:
	CTask *mpNext;//���̃|�C���^
	CTask *mpPrev;//�O�̃|�C���^
	int mPriority;	//�D��x
	bool mEnabled;	//�L���t���O
	//�f�t�H���g�R���X�g���N�^
	CTask()
		: mpNext(0), mpPrev(0), mPriority(0), mEnabled(true) {}
	//�f�X�g���N�^ virtual�ɂ��Ȃ��Ǝq�N���X�̃f�X�g���N�^���Ă΂�Ȃ�
	virtual ~CTask() {}
	//�X�V
	virtual void Update() {}
	//�`��
	virtual void Render() {}
	//�Փˏ���
	virtual void TaskCollision() {}
};

#endif

#ifndef CTASK_H
#define CTASK_H

class CTask
{
public:

	CTask*mpNext; //���|�C���^
	
	CTask*mpPrev; //�O�|�C���^

	int mPriority;//�D��x

	CTask*mpRNext; //���|�C���^

	CTask*mpRPrev; //�O�|�C���^

	int mRPriority;//�D��x

	bool mEnabled;//�D���x


	//�f�t�H���g�R���X�g���N�^
	CTask()
		:mpNext(0), mpPrev(0), mPriority(0), mpRNext(0), mpRPrev(0), mRPriority(0), mEnabled(true) {}
	CTask(CTask *task)
		:mpNext(0), mpPrev(0), mPriority(0), mpRNext(0), mpRPrev(0), mRPriority(0), mEnabled(true) {}
	//�f�X�g���N�^�@virtual�ɂ��Ȃ��Ǝq�N���X�̃f�X�g���N�^���Ă΂�Ȃ�
	virtual~CTask(){}

	virtual void Update(){ }
	
	virtual void Render(){ }

	virtual void Collision(CTask*task){ }

};
#endif


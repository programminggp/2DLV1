#ifndef CTASK_H
#define CTASK_H

#include "CVector3.h"

class CCollider;
#define COLROW 24	//�s��
#define COLSIZE 12	//��ӂ̑傫��
/*
�^�X�N�̊��N���X
*/
class CTask {
public:
	static bool mShadowMap; //�V���h�E�}�b�v�@true:�}�b�v�쐬��
	enum EPRI {
		ENONE,
		ELOW,
		EMID,
		EHIGH,
	};
	CTask *mpPrev;	//�O
	CTask *mpNext;	//��
	bool mEnabled;	//true:�L��
	int mPriority;	//�D��x ��F����

	CTask()
		: mpPrev(0), mpNext(0), mEnabled(true), mPriority(ENONE) {
	}
	virtual ~CTask() {}
	virtual void Render(){}
	virtual void Update(){}
};

class CCollisionList {
	int mCount;
public:
	CTask *mpHead;
	CTask *mpTail;
	CCollisionList()
		: mpHead(0), mpTail(0), mCount(0) {}
	//�^�X�N�ǉ�
	void Add(CCollider*);
	//27 �X�V����
	void Update(CCollider *c);
	//35 �S�Ă��폜
	void Destroy();
	//�폜����
	CTask* Remove(CTask*);
	//�폜����
	void Remove();
};

/*
�R���W�����}�l�[�W��
*/
class CCollisionManager {
	enum EAREA {
		EXPZP,
		EXPZM,
		EXMZP,
		EXMZM,
		EMOVE,
	};
	//�V���O���g���@�B��̃C���X�^���X
	static CCollisionManager *sInstance;
	CTask *mpHead;	//�擪
	CTask *mpTail;	//�Ō�
	CCollisionManager()
		: mpHead(0), mpTail(0), mCount(0) {
	}
//	CCollisionList mCollisionList[EMOVE + 1];
	CCollisionList mCollisionList[COLROW * COLROW];
	int mCount;
public:
	//�C���X�^���X�̎擾
	static CCollisionManager* Get();
	//�^�X�N�ǉ�
	void Add(CTask*);
	//27 �X�V����
	void Update();
	//35 �S�Ă��폜
	void Destroy();
	//�폜����
	CTask* Remove(CTask*);
	//�폜����
	void Remove();

	int GetIndex(const CVector3& v) {
		int col = ((int)(v.x)) / COLSIZE + COLROW / 2;
		int row = ((int)(v.z)) / COLSIZE + COLROW / 2;
		return row * COLROW + col;
	}

};


/*
�^�X�N�}�l�[�W��
*/
class CTaskManager {
	//�V���O���g���@�B��̃C���X�^���X
	static CTaskManager *sInstance;
	CTask *mpHead;	//�擪
	CTask *mpTail;	//�Ō�
	CTaskManager()
		: mpHead(0), mpTail(0) {
	}
public:
	//�C���X�^���X�̎擾
	static CTaskManager* Get();
	//�^�X�N�ǉ�
	void Add(CTask*);
	//�X�V����
	void Update();
	//�S�Ă��폜
	void Destroy();
	//�`�揈��
	void Render();
	//�폜����
	CTask* Remove(CTask*);
	//�폜����
	void Remove();
};


#endif

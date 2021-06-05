#include <stdio.h>
#include "CTask.h"
//27
#include "CCollision.h"

//�V���O���g���@�B��̃C���X�^���X
CCollisionManager *CCollisionManager::sInstance = 0;

bool CTask::mShadowMap = false; //�V���h�E�}�b�v�@true:�}�b�v�쐬��

CCollisionManager* CCollisionManager::Get() {
	if (!sInstance) {
		//�C���X�^���X�������ꍇ�͐���
		sInstance = new CCollisionManager();
	}
	return sInstance;
}
/*
Add
�R���C�_�̃��X�g�ɒǉ�����
�D��x�͑傫���l����
*/
#define MGN 5.0f
void CCollisionManager::Add(CTask *task) {
	mCount++;
	if (((CCollider*)task)->mColParts < CCollider::ENONE) {
		int index = GetIndex(((CCollider*)task)->mPosition);
		if (0 <= index && index < COLROW * COLROW) {
			mCollisionList[index].Add((CCollider*)task);
		}
		else {
			printf("Index:%d", index);
		}
		//if (((CCollider*)task)->mPosition.x > -MGN) {
		//	if (((CCollider*)task)->mPosition.z > -MGN) {
		//		mCollisionList[EXPZP].Add((CCollider*)task);
		//	}
		//	if (((CCollider*)task)->mPosition.z < MGN) {
		//		mCollisionList[EXPZM].Add((CCollider*)task);
		//	}
		//}
		//if (((CCollider*)task)->mPosition.x < MGN) {
		//	if (((CCollider*)task)->mPosition.z > -MGN) {
		//		mCollisionList[EXMZP].Add((CCollider*)task);
		//	}
		//	if (((CCollider*)task)->mPosition.z < MGN) {
		//		mCollisionList[EXMZM].Add((CCollider*)task);
		//	}
		//}
	}
	if (mpHead) {
		//2���ڈȍ~�̏���
		//�J�����gc�ɐ擪��������
		CTask *c = mpHead;
		//�擪�ɒǉ��̏ꍇ
		if (task->mPriority >= c->mPriority) {
			//�擪�͈����̃^�X�N
			mpHead = task;
			//�擪�̑O�͂Ȃ�
			task->mpPrev = 0;
			//�擪�̎��́A�J�����gc
			task->mpNext = c;
			//���̑O�͈����̃^�X�N
			c->mpPrev = task;
//			return;
		} //�擪�ɒǉ��̏I���
		else {
			c = c->mpNext;
			//�擪�ȍ~�ɒǉ�
			while (c) {
				if (task->mPriority >= c->mPriority) {
					//�J�����g�̑O�̎��������̃^�X�N�ɂ���
					c->mpPrev->mpNext = task;
					//�����̃^�X�N�̑O���J�����g�̑O��
					task->mpPrev = c->mpPrev;
					//�����̃^�X�N�̎����J�����g��
					task->mpNext = c;
					//�J�����g�̑O�������̃^�X�N��
					c->mpPrev = task;
					break;
				}
				c = c->mpNext;
			} //�r���ɒǉ��I��
			if (!c) {
				//�Ō�ɒǉ�
				//�Ō�̎��������̃^�X�N�ɂ���
				mpTail->mpNext = task;
				//�����̃^�X�N�̑O���A���̍Ō�ɂ���
				task->mpPrev = mpTail;
				//�����̃^�X�N�̎���0�ɂ���
				task->mpNext = 0;
				//�Ō�Ɉ����̃^�X�N��������
				mpTail = task;
			}
		}
	}
	else {	//0�͋U
		//1���ڂ̏���
		//�擪�������̃^�X�N�ɂ���
		mpHead = task;
		//�擪�̑O��0�ɂ���
		task->mpPrev = 0;
		//�擪�̎���0�ɂ���
		task->mpNext = 0;
		//�Ō�Ɉ����̃^�X�N��������
		mpTail = task;
	}
	return;
}

void CCollisionList::Add(CCollider *t) {
	mCount++;
	CCollider *task = new CCollider();
	*task = *t;
	if (mpHead) {
		//2���ڈȍ~�̏���
		//�J�����gc�ɐ擪��������
		CTask *c = mpHead;
		//�擪�ɒǉ��̏ꍇ
		if (task->mPriority >= c->mPriority) {
			//�擪�͈����̃^�X�N
			mpHead = task;
			//�擪�̑O�͂Ȃ�
			task->mpPrev = 0;
			//�擪�̎��́A�J�����gc
			task->mpNext = c;
			//���̑O�͈����̃^�X�N
			c->mpPrev = task;
			return;
		} //�擪�ɒǉ��̏I���
		c = c->mpNext;
		//�擪�ȍ~�ɒǉ�
		while (c) {
			if (task->mPriority >= c->mPriority) {
				//�J�����g�̑O�̎��������̃^�X�N�ɂ���
				c->mpPrev->mpNext = task;
				//�����̃^�X�N�̑O���J�����g�̑O��
				task->mpPrev = c->mpPrev;
				//�����̃^�X�N�̎����J�����g��
				task->mpNext = c;
				//�J�����g�̑O�������̃^�X�N��
				c->mpPrev = task;
				return;
			}
			c = c->mpNext;
		} //�r���ɒǉ��I��
		//�Ō�ɒǉ�
		//�Ō�̎��������̃^�X�N�ɂ���
		mpTail->mpNext = task;
		//�����̃^�X�N�̑O���A���̍Ō�ɂ���
		task->mpPrev = mpTail;
		//�����̃^�X�N�̎���0�ɂ���
		task->mpNext = 0;
		//�Ō�Ɉ����̃^�X�N��������
		mpTail = task;
	}
	else {	//0�͋U
		//1���ڂ̏���
		//�擪�������̃^�X�N�ɂ���
		mpHead = task;
		//�擪�̑O��0�ɂ���
		task->mpPrev = 0;
		//�擪�̎���0�ɂ���
		task->mpNext = 0;
		//�Ō�Ɉ����̃^�X�N��������
		mpTail = task;
	}
}

/*27
Update
�R���W�����̏Փˏ���
*/
void CCollisionManager::Update(){
	//�J�����gc��擪�ɂ���
	CCollider *c = (CCollider*)mpHead;
	//�J�����gc��0�ɂȂ�����I��
	while (c && c->mPriority >= CCollider::ENONE) {
//	while (c && c->mpParent) {
		if (c->mpParent) {
			int index = GetIndex(((CCollider*)c)->mpParent->mPosition);
			mCollisionList[index - COLROW - 1].Update(c);
			mCollisionList[index - COLROW].Update(c);
			mCollisionList[index - COLROW + 1].Update(c);
			mCollisionList[index - 1].Update(c);
			mCollisionList[index].Update(c);
			mCollisionList[index + 1].Update(c);
			mCollisionList[index + COLROW - 1].Update(c);
			mCollisionList[index + COLROW].Update(c);
			mCollisionList[index + COLROW + 1].Update(c);
		}
		//�R���C�_�̎�ޔ���
		switch (c->mTag) {
		case CCollider::ECOLSPHERE://���R���C�_�̎�
		{//29
			//�擪����Փ˔���
			CCollider *y = (CCollider*)mpHead;
			//���[���h���W�̋��R���C�_�𓾂�
			CSphereCollider m = ((CSphereCollider*)c)->GetWorld();
			while (y && y->mPriority >= CCollider::ENONE) {
//			while (y) {
				//�����e�̃R���C�_�̓X�L�b�v
				if (y->mpParent != c->mpParent) {
					//�e�̏Փ˔�����Ă�
					m.mpParent->Collision(&m, y);
				}
				//���̑����
				y = (CCollider*)y->mpNext;
			}
		}//29
			break;//29
			//29
		case CCollider::ECOLCAPSULE://�J�v�Z���R���C�_�̎�
		{
			//�擪����Փ˔���
			CCollider *y = (CCollider*)mpHead;
			//���[���h���W�̋��R���C�_�𓾂�
			CCapsuleCollider m = ((CCapsuleCollider*)c)->GetWorld();
			while (y && y->mPriority >= CCollider::ENONE) {
//			while (y) {
				//�����e�̃R���C�_�̓X�L�b�v
				if (y->mpParent != c->mpParent) {
					//�e�̏Փ˔�����Ă�
					m.mpParent->Collision(&m, y);
				}
				//���̑����
				y = (CCollider*)y->mpNext;
			}
		}
			break;
		}
#ifdef _DEBUG
		//�J�����gc��`��
//		c->Render();
#endif
		//�J�����g������
		c = (CCollider*)c->mpNext;
	}
}

void CCollisionList::Update(CCollider *c){
	//�J�����gc��擪�ɂ���
//	CCollider *c = (CCollider*)mpHead;
	//�J�����gc��0�ɂȂ�����I��
	while(c && c->mPriority >= CCollider::ENONE) {
		//�R���C�_�̎�ޔ���
		switch (c->mTag) {
		case CCollider::ECOLSPHERE://���R���C�_�̎�
			{//29
				//�擪����Փ˔���
				CCollider *y = (CCollider*)mpHead;
				//���[���h���W�̋��R���C�_�𓾂�
				CSphereCollider m = ((CSphereCollider*)c)->GetWorld();
				while (y) {
					//�����e�̃R���C�_�̓X�L�b�v
					if (y->mpParent != c->mpParent) {
						//�e�̏Փ˔�����Ă�
						m.mpParent->Collision(&m, y);
					}
					//���̑����
					y = (CCollider*)y->mpNext;
				}
			}//29
			break;//29
		//29
		case CCollider::ECOLCAPSULE://�J�v�Z���R���C�_�̎�
			{
				//�擪����Փ˔���
				CCollider *y = (CCollider*)mpHead;
				//���[���h���W�̋��R���C�_�𓾂�
				CCapsuleCollider m = ((CCapsuleCollider*)c)->GetWorld();
				while (y) {
					//�����e�̃R���C�_�̓X�L�b�v
					if (y->mpParent != c->mpParent) {
						//�e�̏Փ˔�����Ă�
						m.mpParent->Collision(&m, y);
					}
					//���̑����
					y = (CCollider*)y->mpNext;
				}
			}
			break;
		}
#ifdef _DEBUG
		//�J�����gc��`��
		c->Render();
#endif
		//�J�����g������
		c = (CCollider*)c->mpNext;
	}
}

/*35
Destory
���X�g��S�č폜���A
���g���폜����
*/
void CCollisionManager::Destroy(){
	for (int i = 0; i < COLROW * COLROW; i++) {
		mCollisionList[i].Destroy();
	}
	//mCollisionList[1].Destroy();
	//mCollisionList[2].Destroy();
	//mCollisionList[3].Destroy();
	//�J�����gc��擪�ɂ���
	CTask *c = mpHead;
	//�J�����g��0�ɂȂ�����I��
	while (c) {
		//�J�����g�����ɂ���
		c = c->mpNext;
		//�擪���폜
		delete mpHead;
		//�擪�ɃJ�����g��������
		mpHead = c;
	}
	//�Ō��0�ɂ���
	mpTail = 0;
	//�������g���폜
	if (sInstance)
		delete sInstance;
	sInstance = 0;
}

void CCollisionList::Destroy(){
#ifdef _DEBUG
	printf("CollisionList:%d\n", mCount);
#endif
	//�J�����gc��擪�ɂ���
	CTask *c = mpHead;
	//�J�����g��0�ɂȂ�����I��
	while (c) {
		//�J�����g�����ɂ���
		c = c->mpNext;
		//�擪���폜
		delete mpHead;
		//�擪�ɃJ�����g��������
		mpHead = c;
	}
	//�Ō��0�ɂ���
	mpTail = 0;
}

//�V���O���g���@�B��̃C���X�^���X
CTaskManager *CTaskManager::sInstance = 0;

CTaskManager* CTaskManager::Get() {
	if (!sInstance) {
		//�C���X�^���X�������ꍇ�͐���
		sInstance = new CTaskManager();
	}
	return sInstance;
}
/*
Add
���X�g�ɒǉ�����
�D��x�͑傫���l����
*/
void CTaskManager::Add(CTask *task) {
	if (mpHead) {
		//2���ڈȍ~�̏���
		//�J�����gc�ɐ擪��������
		CTask *c = mpHead;
		//�擪�ɒǉ��̏ꍇ
		if (task->mPriority >= c->mPriority) {
			//�擪�͈����̃^�X�N
			mpHead = task;
			//�擪�̑O�͂Ȃ�
			task->mpPrev = 0;
			//�擪�̎��́A�J�����gc
			task->mpNext = c;
			//���̑O�͈����̃^�X�N
			c->mpPrev = task;
			return;
		} //�擪�ɒǉ��̏I���
		c = c->mpNext;
		//�擪�ȍ~�ɒǉ�
		while (c) {
			if (task->mPriority >= c->mPriority) {
				//�J�����g�̑O�̎��������̃^�X�N�ɂ���
				c->mpPrev->mpNext = task;
				//�����̃^�X�N�̑O���J�����g�̑O��
				task->mpPrev = c->mpPrev;
				//�����̃^�X�N�̎����J�����g��
				task->mpNext = c;
				//�J�����g�̑O�������̃^�X�N��
				c->mpPrev = task;
				return;
			}
			c = c->mpNext;
		} //�r���ɒǉ��I��
		//�Ō�ɒǉ�
		//�Ō�̎��������̃^�X�N�ɂ���
		mpTail->mpNext = task;
		//�����̃^�X�N�̑O���A���̍Ō�ɂ���
		task->mpPrev = mpTail;
		//�����̃^�X�N�̎���0�ɂ���
		task->mpNext = 0;
		//�Ō�Ɉ����̃^�X�N��������
		mpTail = task;
	}
	else {	//0�͋U
		//1���ڂ̏���
		//�擪�������̃^�X�N�ɂ���
		mpHead = task;
		//�擪�̑O��0�ɂ���
		task->mpPrev = 0;
		//�擪�̎���0�ɂ���
		task->mpNext = 0;
		//�Ō�Ɉ����̃^�X�N��������
		mpTail = task;
	}
}

/*
Update
�X�V����
*/
void CTaskManager::Update(){
	//�J�����gc��擪�ɂ���
	CXCharacter *c = (CXCharacter*)mpHead;
	//�J�����gc��0�ɂȂ�����I��
	while (c) {
		//�X�V����
		c->Update();
		//�J�����g������
		c = (CXCharacter*)c->mpNext;
	}
}

/*
Render
�X�V����
*/
void CTaskManager::Render(){
	//�J�����gc��擪�ɂ���
	CXCharacter *c = (CXCharacter*)mpHead;
	//�J�����gc��0�ɂȂ�����I��
	while (c) {
		//�`�悷��
		c->Render();
		//�J�����g������
		c = (CXCharacter*)c->mpNext;
	}
}

/*
Destory
���X�g��S�č폜���A
���g���폜����
*/
void CTaskManager::Destroy(){
	//�J�����gc��擪�ɂ���
	CTask *c = mpHead;
	//�J�����g��0�ɂȂ�����I��
	while (c) {
		//�J�����g�����ɂ���
		c = c->mpNext;
		//�擪���폜
		delete mpHead;
		//�擪�ɃJ�����g��������
		mpHead = c;
	}
	//�Ō��0�ɂ���
	mpTail = 0;
	//�������g���폜
	if (sInstance)
		delete sInstance;
	sInstance = 0;
}
/*
�����̃^�X�N�����X�g����폜���܂�
*/
CTask* CTaskManager::Remove(CTask *task) {
	//�폜���鎟�̃^�X�N��ޔ�
	CTask *rtn = task->mpNext;
	//�폜���X�g���擪�̎�
	if (mpHead == task) {
		//����擪�ɂ���
		mpHead = task->mpNext;
	}
	//�폜���X�g���Ō�̎�
	if (mpTail == task) {
		//�O���Ō�ɂ���
		mpTail = task->mpPrev;
	}
	//�폜���X�g�ɑO�����鎞
	if (task->mpPrev) {
		//�O�̎����A�폜���X�g�̎��ɂ���
		task->mpPrev->mpNext = task->mpNext;
	}
	//�폜���X�g�Ɏ�������ꍇ
	if (task->mpNext) {
		//���̑O���A�폜���X�g�̑O�ɂ���
		task->mpNext->mpPrev = task->mpPrev;
	}
	//�^�X�N�̍폜
	delete task;
	//����Ԃ�
	return rtn;
}
/*
�����ȃ^�X�N���폜���܂�
*/
void CTaskManager::Remove() {
	//�J�����gc��擪�ɂ���
	CTask *c = (CTask*)mpHead;
	//�J�����gc��0�ɂȂ�����I��
	while (c) {
		if (c->mEnabled) {
			//�L���Ȏ��͎���
			c = c->mpNext;
		}
		else {
			//�����ȃ^�X�N�͍폜
			c = Remove(c);
		}
	}
}
/*
�����̃^�X�N�����X�g����폜���܂�
*/
CTask* CCollisionManager::Remove(CTask *task) {
	//�폜���鎟�̃^�X�N��ޔ�
	CTask *rtn = task->mpNext;
	//�폜���X�g���擪�̎�
	if (mpHead == task) {
		//����擪�ɂ���
		mpHead = task->mpNext;
	}
	//�폜���X�g���Ō�̎�
	if (mpTail == task) {
		//�O���Ō�ɂ���
		mpTail = task->mpPrev;
	}
	//�폜���X�g�ɑO�����鎞
	if (task->mpPrev) {
		//�O�̎����A�폜���X�g�̎��ɂ���
		task->mpPrev->mpNext = task->mpNext;
	}
	//�폜���X�g�Ɏ�������ꍇ
	if (task->mpNext) {
		//���̑O���A�폜���X�g�̑O�ɂ���
		task->mpNext->mpPrev = task->mpPrev;
	}
	//�^�X�N�̍폜
	delete task;
	//����Ԃ�
	return rtn;
}

CTask* CCollisionList::Remove(CTask *task) {
	//�폜���鎟�̃^�X�N��ޔ�
	CTask *rtn = task->mpNext;
	//�폜���X�g���擪�̎�
	if (mpHead == task) {
		//����擪�ɂ���
		mpHead = task->mpNext;
	}
	//�폜���X�g���Ō�̎�
	if (mpTail == task) {
		//�O���Ō�ɂ���
		mpTail = task->mpPrev;
	}
	//�폜���X�g�ɑO�����鎞
	if (task->mpPrev) {
		//�O�̎����A�폜���X�g�̎��ɂ���
		task->mpPrev->mpNext = task->mpNext;
	}
	//�폜���X�g�Ɏ�������ꍇ
	if (task->mpNext) {
		//���̑O���A�폜���X�g�̑O�ɂ���
		task->mpNext->mpPrev = task->mpPrev;
	}
	//�^�X�N�̍폜
	delete task;
	//����Ԃ�
	return rtn;
}
/*
�����ȃ^�X�N���폜���܂�
*/
void CCollisionManager::Remove() {
	//mCollisionList[0].Remove();
	//mCollisionList[1].Remove();
	//mCollisionList[2].Remove();
	//mCollisionList[3].Remove();
	//�J�����gc��擪�ɂ���
	CCollider *c = (CCollider*)mpHead;
	//�J�����gc��0�ɂȂ�����I��
	while (c && c->mPriority >= CCollider::ENONE) {
		//�e���L��
		if (c->mpParent) {
			if (!c->mpParent->mEnabled) {
				//�����ȃ^�X�N�͍폜
				c = (CCollider*)Remove(c);
				//���[�v�̐擪��
				continue;
			}
		}
		//����
		c = (CCollider*)c->mpNext;
	}
}

void CCollisionList::Remove() {
	//�J�����gc��擪�ɂ���
	CCollider *c = (CCollider*)mpHead;
	//�J�����gc��0�ɂȂ�����I��
	while (c) {
		//�e���L��
		if (c->mpParent) {
			if (!c->mpParent->mEnabled) {
				//�����ȃ^�X�N�͍폜
				c = (CCollider*)Remove(c);
				//���[�v�̐擪��
				continue;
			}
		}
		//����
		c = (CCollider*)c->mpNext;
	}
}

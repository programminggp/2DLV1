#include"CTaskManager.h"
//�^�X�N�}�l�[�W���̊O���ϐ�
CTaskManager TaskManager;

CTaskManager::CTaskManager()
:mpHead(0), mpRHead(0)
{}

CTaskManager::~CTaskManager(){}


void CTaskManager::Add(CTask *task, int priority, int priorityr) {
	task->mPriority = priority;
	task->mRPriority = priorityr;
	Add(task);
	AddR(task);
}


//�^�X�N�ǉ�
void CTaskManager::Add(CTask*task){

	if (mpHead == 0){

		mpHead = task;

		task->mpPrev = 0;

		task->mpNext = 0;
	}
	else{

		CTask*pos = mpHead;

		while (task->mPriority < pos->mPriority){

			if (pos->mpNext != 0){

				pos = pos->mpNext;

			}

			else{

				break;

			}

		}

		if (pos->mpPrev == 0){

			task->mpNext = mpHead;

			mpHead->mpPrev = task;

			mpHead = task;

			mpHead->mpPrev = 0;

		}

		else if (pos->mpNext == 0){

			task->mpNext = 0;

			task->mpPrev = pos;

			pos->mpNext = task;

		}

		else{

			task->mpNext = pos;

			task->mpPrev = pos->mpPrev;

			pos->mpPrev = task;

			task->mpPrev->mpNext = task;

		}
	}

	AddR(task);
}

void CTaskManager::AddR(CTask*task){

	if (mpRHead == 0){

		mpRHead = task;

		task->mpRPrev = 0;

		task->mpRNext = 0;
	}
	else{

		CTask*pos = mpRHead;

		while (task->mRPriority < pos->mRPriority){

			if (pos->mpRNext != 0){

				pos = pos->mpRNext;

			}

			else{

				break;

			}

		}

		if (pos->mpRPrev == 0){

			task->mpRNext = mpRHead;

			mpRHead->mpRPrev = task;

			mpRHead = task;

			mpRHead->mpRPrev = 0;

		}

		else if (pos->mpRNext == 0){

			task->mpRNext = 0;

			task->mpRPrev = pos;

			pos->mpRNext = task;

		}

		else{

			task->mpRNext = pos;

			task->mpRPrev = pos->mpRPrev;

			pos->mpRPrev = task;

			task->mpRPrev->mpRNext = task;

		}

	}
}

void CTaskManager::AllDisable(){
	CTask*pos = mpHead;

	while (pos)
	{
		//�X�V�����̌Ăяo��

		pos->mEnabled=false;

		//���֍s��
		pos = pos->mpNext;
	}

}
void CTaskManager::Changepriority(CTask*task, int priority){

	RemoveR(task);
	task->mRPriority = priority;
	AddR(task);
}

void CTaskManager::Remove(CTask*task){
	//1��task�����X�g����폜
	if (task->mpPrev == 0){
		mpHead = task->mpNext;
	}
	else{
		task->mpPrev->mpNext = task->mpNext;
	}
	if (task->mpNext != 0){
		task->mpNext->mpPrev = task->mpPrev;
	}

	RemoveR(task);
}

void CTaskManager::RemoveR(CTask*task){
	//1��task�����X�g����폜
	if (task->mpRPrev == 0){
		mpRHead = task->mpRNext;
	}
	else{
		task->mpRPrev->mpRNext = task->mpRNext;
	}
	if (task->mpRNext != 0){
		task->mpRNext->mpRPrev = task->mpRPrev;
	}
}

////�����m�F
//void CTaskManager::DeleteCheck(){
//	//�擪����Ō�܂ŌJ��Ԃ�
//	CTask*pos = mpHead;
//	while (pos){
//		CTask*mpMine = pos;
//		//����
//		pos = pos->mpNext;
//		//mSurvivalConfirmation(�����m�F)��false�Ȃ�폜
//		if (mpMine->mSurvivalConfirmation == false){
//			delete mpMine;
//		}
//	}
//}

void CTaskManager::Delete(){

	CTask*pos = mpHead;

	while (pos){
		CTask*del = pos;
		//����
		pos = pos->mpNext;
		//mEnabled��false�Ȃ����

		if (del->mEnabled == false){
			Remove(del);
			delete del;
		}
	}

}


void CTaskManager::Update(){

	CTask*pos = mpHead;

	while (pos)
	{
		//�X�V�����̌Ăяo��

		pos->Update();

		//���֍s��
		pos = pos->mpNext;
	}

}

void CTaskManager::Collision(){
	//���݈ʒu��擪�ɂ���
	CTask*pos = (CTask*)mpHead;
	//�Ō�܂łł�����I������
	while (pos ->mpNext!=0 ){
		//���݈ʒu�̎������߂�
		CTask*next = (CTask*)pos->mpNext;
		//����0�ɂȂ�����I��
		while (next){
			//�e�̏Փˏ������Ăяo��
			//�����̏Փˏ���
			pos->Collision(next);
			//����̏Փˏ���
			next->Collision(pos);
			//�������߂�
			next = next->mpNext;
		}
		//���݈ʒu�����ɂ���
		pos = pos->mpNext;
	}
}

void CTaskManager::Render(){

	CTask*pos = mpRHead;

	while (pos)
	{
		//�`�揈���̌Ăяo��

		pos->Render();

		//���֍s��
		pos = pos->mpRNext;
	}

}

//void CTaskManager::AllDelete(){
//
//	CTask*pos = mpHead;
//
//	while (pos){
//		CTask*del = pos;
//		//����
//		pos = pos->mpNext;
//		//mEnabled��false�Ȃ����
//
//			delete del;
//
//	}
//
//}
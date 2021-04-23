#include "CCollisionManager.h"
//�R���C�_�N���X�̃C���N���[�h
#include "CCollider.h"
//���Ŏg�p�ł���悤�ɊO���ϐ��ō쐬
CCollisionManager CollisionManager;

//�Փˏ���
void CCollisionManager::Collision() {
	//���݈ʒu��擪�ɂ���
	CCollider *pos = (CCollider*)mpHead->mpNext;
	//�Ō�܂ł�����I������
//?	while (pos != mpTail) {
	while (pos) {
			//���݈ʒu�̎������߂�
		CCollider *next = (CCollider*)pos->mpNext;
		//����0�ɂȂ�����I��
		while (next) {
			//�e�̏Փˏ������Ăяo��
			//�����̏Փˏ���
			pos->mpParent->Collision(pos, next);
			//����̏Փˏ���
			next->mpParent->Collision(next, pos);
			//�������߂�
			next = (CCollider*)next->mpNext;
		}
		//���݈ʒu�����ɂ���
		pos = (CCollider*)pos->mpNext;
	}
}

//Collision(�R���C�_�j
//�R���C�_�Ƃ̏Փˏ��������s����
void CCollisionManager::Collision(CCollider *collider)
{
	int sPri = collider->mPriority + 900; //�J�n�ʒu�i��j
	int ePri = collider->mPriority - 900; //�I���ʒu�i���j
	//���݈ʒu��擪�ɂ���
	CCollider *pos = (CCollider*)mpHead->mpNext;
	//�J�n�ʒu�܂ł�����I������
	while (pos && pos->mPriority > sPri) {
		//���݈ʒu�����ɂ���
		pos = (CCollider*)pos->mpNext;
	}
	if (pos) {
		//�I���ʒu�܂ŌJ��Ԃ�
		while (pos && pos->mPriority >= ePri) {
			//�e�̏Փˏ������Ăяo��
			collider->mpParent->Collision(collider, pos);
			//�������߂�
			pos = (CCollider*)pos->mpNext;
		}
	}
	//�D��x0�Ƃ͏Փ˔��肳����
	while (pos && pos->mPriority) {
		//���݈ʒu�����ɂ���
		pos = (CCollider*)pos->mpNext;
	}
	if (pos) {
		//�I���ʒu�܂ŌJ��Ԃ�
		while (pos && pos->mPriority <= 0) {
			//�e�̏Փˏ������Ăяo��
			collider->mpParent->Collision(collider, pos);
			//�������߂�
			pos = (CCollider*)pos->mpNext;
		}
	}
}



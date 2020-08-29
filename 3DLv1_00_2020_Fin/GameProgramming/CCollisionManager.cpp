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

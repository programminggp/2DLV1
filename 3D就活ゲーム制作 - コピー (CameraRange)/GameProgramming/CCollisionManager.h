#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H
//�^�X�N�}�l�[�W���̃C���N���[�h
#include "CTaskManager.h"
class CCollider;

/*
�R���W�����}�l�[�W��
�R���C�_�̃��X�g�Ǘ�
*/
class CCollisionManager : public CTaskManager {
public:
	//�Փˏ���
	void Collision();

	void Collision(CCollider *collider);
};
//���Ŏg����悤�ɊO���Q�Ƃ���
extern CCollisionManager CollisionManager;

#endif

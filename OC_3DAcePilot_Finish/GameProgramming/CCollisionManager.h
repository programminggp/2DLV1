#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H
//�^�X�N�}�l�[�W���̃C���N���[�h
#include "CTaskManager.h"
/*
�R���W�����}�l�[�W��
�R���C�_�̃��X�g�Ǘ�
*/
class CCollisionManager : public CTaskManager {
public:
	//�Փˏ���
	void Collision();
};
//���Ŏg����悤�ɊO���Q��
extern CCollisionManager CollisionManager;

#endif

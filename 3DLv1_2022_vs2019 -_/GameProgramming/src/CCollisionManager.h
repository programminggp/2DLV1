#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H

#include "CTaskManager.h"
#include "CCollider.h"
#define COLLISIONRANGE 30

class CCollisionManager : public CTaskManager
{
public:
	//�Փˏ���
	void Collision();
	//�C���X�^���X�̎擾
	static CCollisionManager* Instance();
	//�Փˏ���
	//Collision(�R���C�_�A�͈�)
	//�R���C�_�̗D��x�{�͈́`�D��x�[�͈͂܂ł̃R���C�_�ƏՓ˔�������s����
	void Collision(CCollider* c, int range);
private:
	//�}�l�[�W���̃C���X�^���X
	static CCollisionManager* mpInstance;
};

#endif

#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H

#include "CTaskManager.h"
#include "CCollider.h"

//�Փˏ����͈͂�藣��Ă���R���C�_�͏Փˏ������Ȃ�
#define COLLISIONRANGE 30

class CCollisionManager : public CTaskManager
{
public:
	//�Փˏ���
	//Collision(�R���C�_, �͈�)
	//�R���C�_�̗D��x+�͈́`�D��x-�͈͂܂ł̃R���C�_�ƏՓ˔�������s����
	void Collision(CCollider* c, int range);
	//�Փˏ���
	void Collision();
	//�C���X�^���X�̎擾
	static CCollisionManager* Instance();
private:
	//�}�l�[�W���̃C���X�^���X
	static CCollisionManager* mpInstance;
};

#endif

#ifndef CCOLLISIONMANAGER
#define CCOLLISIONMANAGER

//�^�X�N�}�l�[�W���̃N���X�̃C���N���[�h
#include "CTaskManager.h"
//�Փˏ����͈͂�藣��Ă���R���C�_�͏Փˏ������Ȃ�
#define COLLISIONRANGE 30

/*
�R���W�����}�l�[�W���N���X
�e:CTaskManager�N���X�@�q:CCollisionManager�N���X
*/
class CCollisionManager : public CTaskManager
{
public:
	//�C���X�^���X�̎擾
	static CCollisionManager* Get();
	//�Փˏ���
	void Collision();
	//
	void CCollisionManager::Collision(CCollider* c, int range);
private:
	//�}�l�[�W���̃C���X�^���X
	static CCollisionManager* mpInstance;

};
#endif


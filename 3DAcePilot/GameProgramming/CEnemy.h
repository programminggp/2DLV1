#ifndef CENEMY_H
#define CENEMY_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
//�R���C�_�N���X�̃C���N���[�h
#include "CCollider.h"

/*
�G�l�~�[�N���X
�L�����N�^�N���X���p��
*/
class CEnemy : public CCharacter {
public:
	int mHp;				//HP
	CCollider mCollider;	//�Փ˔���p�R���C�_
	CCollider mSearch;		//���G�p�R���C�_
	CVector *mpTarget;		//�ڎw���^�[�Q�b�g
	CVector mPoint;			//�ڎw���|�C���g
	int mPointCnt;			//�|�C���g�̃J�E���^
	int mFireBullet;		//���ˊԊu
	float mVelocity;		//��s���x

	//�R���X�g���N�^
	//CEnemy(���f��, �ʒu, ��], �g�k)
	CEnemy(CModel *model, CVector position, CVector rotation, CVector scale);
	//�X�V����
	void Update();
	//�Փˏ���
	void Collision(CCollider *m, CCollider *y);
};

#endif

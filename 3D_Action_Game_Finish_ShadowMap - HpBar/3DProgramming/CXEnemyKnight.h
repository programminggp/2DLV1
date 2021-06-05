#ifndef CXENEMYKNIGHT_H
#define CXENEMYKNIGHT_H

#include "CXCharacter.h"
#include "CCollision.h"
#include "CBillBoard.h"
#include "CHpBar.h"
#include "main.h"
#include <vector>

class CXEnemyKnight : public CXCharacter {
public:
	//�R���C�_
	std::vector<CCollider*> mColliders;

	CHPBar mHpBar;//HP�Q�[�W

	CXCharacter *mpPlayer;	//�v���C���[�|�C���^
	//�����������̉�]�Ɏg�p
	float radian;

	CXEnemyKnight()
		: mpPlayer(0)
		, radian(0.0f)
		, mHpBar(CVector3(), CVector2(30,2), 100, 100)
	{
		mTag = EENEMY;	//27 �^�O�ɓG�ݒ�
	}

	CXEnemyKnight(CModelX *m, CVector3 pos)
		: CXEnemyKnight() {
		Init(m); //����������
		mPosition = pos; //�ʒu�ݒ�
		//Task�}�l�[�W���ɒǉ�
		CTaskManager::Get()->Add(this);
	}

	~CXEnemyKnight() {
		for (int i = 0; i < mColliders.size(); i++) {
			CCollisionManager::Get()->Remove(mColliders[i]);
		}
		mColliders.clear();
	}

	void Init(CModelX*);
	void Update();
	bool Collision(CCollider *m, CCollider *y);
	void Render();
};

#endif

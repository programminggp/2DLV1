#ifndef CROCK_H
#define CROCK_H
#include "CCharacter.h"
#include "CCollider.h"

class CRock : public CCharacter{
public:
	//�f�t�H���g�R���X�g���N�^
	CRock();

	CRock(CModel *model, CVector position, CVector rotation, CVector scale);

	CCollider mColBody;

	//�Փˏ���
	void Collision(CCollider *m, CCollider *y);
};

#endif
#ifndef COBJFLOOR_H
#define COBJFLOOR_H
#include "CObj.h"

class CObjFloor :public CObj{
public:
	//�R���X�g���N�^�ŏ����ݒ�
	CObjFloor(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale);

	////CObj���ŏՓˏ����c�͈ȑO�A���������d�ɂȂ����̂ł��Ȃ��A���Ȃ��A��肽���Ȃ�
	//void Collision(CCollider *m, CCollider *y);
	////�X�V�����̃I�[�o�[���C�h
	//void Update();
};
#endif

#ifndef COBJWATER_H
#define COBJWATER_H
#include "CObj.h"

class CObjWater :public CObj{
public:
	//�R���X�g���N�^�ŏ����ݒ�
	CObjWater(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale);
};
#endif
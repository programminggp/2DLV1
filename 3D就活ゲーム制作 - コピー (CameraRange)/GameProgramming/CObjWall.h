#ifndef COBJWALL_H
#define COBJWALL_H
#include "CObj.h"

class CObjWall :public CObj{
public:
	//�R���X�g���N�^�ŏ����ݒ�
	CObjWall(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale);
};
#endif



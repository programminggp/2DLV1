#ifndef COBJGRASS_H
#define COBJGRASS_H
#include "CObj.h"

class CObjGrass :public CObj{
public:
	//�R���X�g���N�^�ŏ����ݒ�
	CObjGrass(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale);
};
#endif

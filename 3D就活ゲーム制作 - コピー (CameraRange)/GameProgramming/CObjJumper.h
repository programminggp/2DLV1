#ifndef COBJJUMPER_H
#define COBJJUMPER_H
#include "CObj.h"

class CObjJumper :public CObj{
public:
	//�R���X�g���N�^�ŏ����ݒ�
	CObjJumper(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale);
};
#endif

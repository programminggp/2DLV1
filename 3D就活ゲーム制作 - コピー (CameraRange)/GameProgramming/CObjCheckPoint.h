#ifndef COBJCHECKPOINT_H
#define COBJCHECKPOINT_H

#include "CObj.h"

class CObjCheckPoint :public CObj{
public:
	//�R���X�g���N�^�ŏ����ݒ�
	CObjCheckPoint(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale, int checkpoint_number);

	//
	int cpnumber;
};
#endif
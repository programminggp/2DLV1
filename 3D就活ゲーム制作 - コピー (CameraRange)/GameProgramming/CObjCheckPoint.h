#ifndef COBJCHECKPOINT_H
#define COBJCHECKPOINT_H

#include "CObj.h"

class CObjCheckPoint :public CObj{
public:
	//コンストラクタで初期設定
	CObjCheckPoint(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale, int checkpoint_number);

	//
	int cpnumber;

	void Render(){};//チェックポイントは描画しない
};
#endif
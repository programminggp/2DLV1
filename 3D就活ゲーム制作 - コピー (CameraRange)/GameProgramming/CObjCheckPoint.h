#ifndef COBJCHECKPOINT_H
#define COBJCHECKPOINT_H

#include "CObj.h"

class CObjCheckPoint :public CObj{
public:
	//コンストラクタで初期設定
	CObjCheckPoint(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale, int checkpoint_number);

	void Render(){};//チェックポイントは描画しない

private:
	//中間ポイントの番号
	int cpnumber;
};
#endif
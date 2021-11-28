#ifndef CRACECOURCEC_H
#define CRACECOURCEC_H
#include "CSceneRace.h"
#include "CModel.h"


class CRaceCourceC : public CSceneRace {
public:
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
};

#endif
#ifndef CRACECOURCED_H
#define CRACECOURCED_H
#include "CSceneRace.h"
#include "CModel.h"


class CRaceCourceD : public CSceneRace {
public:
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
};

#endif
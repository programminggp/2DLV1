#ifndef CRACECOURCED_H
#define CRACECOURCED_H

#include "CModel.h"
#include "CSceneRace.h"

class CRaceCourceD : public CSceneRace {
public:
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
};

#endif
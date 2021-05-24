#ifndef CRACECOURCEETEST_H
#define CRACECOURCEETEST_H

#include "CModel.h"
#include "CSceneRace.h"

class CRaceCourceETest : public CSceneRace {
public:
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
};

#endif
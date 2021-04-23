#ifndef CRACECOURCEF_H
#define CRACECOURCEF_H

#include "CModel.h"
#include "CSceneRace.h"

class CRaceCourceF : public CSceneRace {
public:
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
};

#endif
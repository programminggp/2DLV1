#ifndef CRACECOURCEB_H
#define CRACECOURCEB_H

#include "CModel.h"
#include "CSceneRace.h"

class CRaceCourceB : public CSceneRace {
public:
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
};

#endif
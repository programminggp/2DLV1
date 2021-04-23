#ifndef CRACECOURCEE_H
#define CRACECOURCEE_H

#include "CModel.h"
#include "CSceneRace.h"

class CRaceCourceE : public CSceneRace {
public:
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
};

#endif